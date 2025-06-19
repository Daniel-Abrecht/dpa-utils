


//// from any

/*
// This is the clean way to do it
dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_any(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  const dpa_u_bo_t*restrict bo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    if(type & DPA_U_BO_HASHED){
      cmem->rh = *dpa_u_container_of(bo, const dpa__u_bo_refcounted_hashed_t, rbo.bo);
    }else{
      cmem->rh.rbo = *dpa_u_container_of(bo, const dpa__u_bo_refcounted_t, bo);
    }
    return DPA__U_BO_TAG(&cmem->rh.rbo.bo, type);
  }else{
    if(type & DPA_U_BO_HASHED){
      cmem->hr.hashed = *dpa_u_container_of(bo, const dpa__u_bo_hashed_t, bo);
    }else{
      cmem->hr.hashed.bo = *bo;
    }
    return DPA__U_BO_TAG(&cmem->hr.hashed.bo, type);
  }
}
extern dpa__u_boptr_t dpa__u_bo__alloc_p_any_any(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem);
*/

// This is the hacky way to do it. It results in less instructins, though.
dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_any(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  dpa_u_bo_t*restrict dbo = type & DPA_U_BO_REFCOUNTED ? &cmem->rh.rbo.bo : &cmem->hr.hashed.bo;
  if(type & DPA_U_BO_REFCOUNTED)
    dpa_u_container_of(dbo, dpa__u_bo_refcounted_t, bo)->refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  *dbo = *sbo;
  if(type & DPA_U_BO_HASHED)
    *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(dbo, type);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_any_do_hash(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  dpa_u_bo_t*restrict dbo = type & DPA_U_BO_REFCOUNTED ? &cmem->rh.rbo.bo : &cmem->hr.hashed.bo;
  if(type & DPA_U_BO_REFCOUNTED)
    dpa_u_container_of(dbo, dpa__u_bo_refcounted_t, bo)->refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  *dbo = *sbo;
  if(type & DPA_U_BO_HASHED){
    *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(dbo, type | DPA_U_BO_HASHED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_gc_any(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED)
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_gc_any_do_hash(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED){
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    cmem->hash = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED | DPA_U_BO_HASHED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_hashed_any_do_hash(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(type & DPA_U_BO_UNIQUE)
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  if(!(type & DPA_U_BO_SIMPLE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  dpa_u_bo_t*restrict dbo = type & DPA_U_BO_REFCOUNTED ? &cmem->rh.rbo.bo : &cmem->hr.hashed.bo;
  if(type & DPA_U_BO_REFCOUNTED)
    dpa_u_container_of(dbo, dpa__u_bo_refcounted_t, bo)->refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  *dbo = *sbo;
  if(type & DPA_U_BO_HASHED){
    *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(dbo, type | DPA_U_BO_HASHED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_refcounted_any(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)) || (type & DPA_U_BO_UNIQUE))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED)
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_refcounted_any_do_hash(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)) || (type & DPA_U_BO_UNIQUE))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED){
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    cmem->hash = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED | DPA_U_BO_HASHED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_unique_any(dpa__u_boptr_t boptr){
  if(!dpa_u_bo_is_any_type(boptr, DPA_U_BO_UNIQUE))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  return boptr;
}
#define dpa__u_bo__alloc_p_unique_any_do_hash dpa__u_bo__alloc_p_unique_any

//// from gc


#define dpa__u_bo__alloc_p_any_gc dpa__u_bo__alloc_p_any_any
#define dpa__u_bo__alloc_p_any_gc_do_hash dpa__u_bo__alloc_p_any_any_do_hash

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_gc_gc(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED)
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_gc_gc_do_hash(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE) || (type & DPA_U_BO_UNIQUE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED){
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    cmem->hash = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED | DPA_U_BO_HASHED);
}

#define dpa__u_bo__alloc_p_hashed_gc dpa__u_bo__alloc_p_hashed_any
#define dpa__u_bo__alloc_p_hashed_gc_do_hash dpa__u_bo__alloc_p_hashed_any_do_hash
#define dpa__u_bo__alloc_p_refcounted_gc dpa__u_bo__alloc_p_refcounted_any
#define dpa__u_bo__alloc_p_refcounted_gc_do_hash dpa__u_bo__alloc_p_refcounted_any_do_hash
#define dpa__u_bo__alloc_p_unique_gc dpa__u_bo__alloc_p_unique_any
#define dpa__u_bo__alloc_p_unique_gc_do_hash dpa__u_bo__alloc_p_unique_any_do_hash



//// from refcounted

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_refcounted(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED)
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_refcounted_do_hash(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  if(type & DPA_U_BO_HASHED){
    cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  }else{
    cmem->hash = dpa__u_bo_hash(*sbo);
  }
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED | DPA_U_BO_HASHED);
}

#define dpa__u_bo__alloc_p_gc_refcounted dpa__u_bo__alloc_p_gc_any
#define dpa__u_bo__alloc_p_gc_refcounted_do_hash dpa__u_bo__alloc_p_gc_any_do_hash

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_hashed_refcounted(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_HASHED))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}

#define dpa__u_bo__alloc_p_hashed_refcounted_do_hash dpa__u_bo__alloc_p_refcounted_any_do_hash
#define dpa__u_bo__alloc_p_refcounted_refcounted dpa__u_bo__alloc_p_any_refcounted
#define dpa__u_bo__alloc_p_refcounted_refcounted_do_hash dpa__u_bo__alloc_p_any_refcounted_do_hash


// From hashed

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_hashed(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_HASHED))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  dpa_u_bo_t*restrict dbo = type & DPA_U_BO_REFCOUNTED ? &cmem->rh.rbo.bo : &cmem->hr.hashed.bo;
  if(type & DPA_U_BO_REFCOUNTED)
    dpa_u_container_of(dbo, dpa__u_bo_refcounted_t, bo)->refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  *dbo = *sbo;
  *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(dbo, type);
}
#define dpa__u_bo__alloc_p_any_hashed_do_hash dpa__u_bo__alloc_p_any_hashed

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_gc_hashed(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}
#define dpa__u_bo__alloc_p_gc_hashed_do_hash dpa__u_bo__alloc_p_gc_hashed

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_hashed_hashed(dpa__u_boptr_t boptr, union dpa__u_bo_cmem*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & DPA_U_BO_SIMPLE))
    return boptr;
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  dpa_u_bo_t*restrict dbo = type & DPA_U_BO_REFCOUNTED ? &cmem->rh.rbo.bo : &cmem->hr.hashed.bo;
  if(type & DPA_U_BO_REFCOUNTED)
    dpa_u_container_of(dbo, dpa__u_bo_refcounted_t, bo)->refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  *dbo = *sbo;
  *(uint64_t*restrict)(((char*)dbo) + offsetof(dpa__u_bo_hashed_t, hash)) = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(dbo, type);
}
#define dpa__u_bo__alloc_p_hashed_hashed_do_hash dpa__u_bo__alloc_p_hashed_hashed

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_refcounted_hashed(dpa__u_boptr_t boptr, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  const unsigned type = dpa_u_bo_get_type(boptr);
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
  const dpa_u_bo_t*restrict sbo = DPA__U_BO_UNTAG(const dpa_u_bo_t*restrict, boptr);
  if(type & DPA_U_BO_REFCOUNTED){
    cmem->rbo.refcount = dpa_u_container_of(sbo, const dpa__u_bo_refcounted_t, bo)->refcount;
  }else{
    cmem->rbo.refcount = &dpa_u_refcount_static_v_freeable;
  }
  cmem->rbo.bo = *sbo;
  cmem->hash = *(uint64_t*restrict)(((char*)sbo) + offsetof(dpa__u_bo_hashed_t, hash));
  return DPA__U_BO_TAG(&cmem->rbo.bo, type | DPA_U_BO_REFCOUNTED);
}
#define dpa__u_bo__alloc_p_refcounted_hashed_do_hash dpa__u_bo__alloc_p_refcounted_hashed


// from bo

dpa__u_api inline dpa__u_bo_hashed_t dpa__u_bo__alloc_p_any_bo_do_hash(dpa_u_bo_t bo){
  return (dpa__u_bo_hashed_t){
    .bo = bo,
    .hash = dpa__u_bo_hash(bo),
  };
}
#define dpa__u_bo__alloc_p_hashed_bo_do_hash dpa__u_bo__alloc_p_any_bo_do_hash

dpa__u_api inline dpa__u_bo_refcounted_hashed_t dpa__u_bo__alloc_p_refcounted_static_bo_do_hash(dpa_u_bo_t bo){
  return (dpa__u_bo_refcounted_hashed_t){
    .rbo = {
      .refcount = &dpa_u_refcount_static_v_freeable,
      .bo = bo,
    },
    .hash = dpa__u_bo_hash(bo),
  };
}


dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash(dpa_u_bo_t bo, dpa_u_refcount_freeable_t* refcount, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  *cmem = (dpa__u_bo_refcounted_hashed_t){
    .rbo = {
      .refcount = refcount,
      .bo = bo,
    },
    .hash = dpa__u_bo_hash(bo),
  };
  return DPA__U_BO_TAG(
    &cmem->rbo.bo, 
    dpa_u_refcount_is_static_p(&refcount->refcount)
     ? DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC
     : DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED
  );
}
#define dpa__u_bo__alloc_p_gc_bo_with_refcount_do_hash dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash
#define dpa__u_bo__alloc_p_refcounted_bo_with_refcount_do_hash dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash
#define dpa__u_bo__alloc_p_hashed_bo_with_refcount_do_hash dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_bo_with_refcount_hash(dpa_u_bo_t bo, dpa_u_refcount_freeable_t* refcount, uint64_t hash, dpa__u_bo_refcounted_hashed_t*restrict cmem){
  *cmem = (dpa__u_bo_refcounted_hashed_t){
    .rbo = {
      .refcount = refcount,
      .bo = bo,
    },
    .hash = hash,
  };
  return DPA__U_BO_TAG(
    &cmem->rbo.bo, 
    dpa_u_refcount_is_static_p(&refcount->refcount)
     ? DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC
     : DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED
  );
}
#define dpa__u_bo__alloc_p_gc_bo_with_refcount_hash dpa__u_bo__alloc_p_any_bo_with_refcount_hash
#define dpa__u_bo__alloc_p_refcounted_bo_with_refcount_hash dpa__u_bo__alloc_p_any_bo_with_refcount_hash
#define dpa__u_bo__alloc_p_hashed_bo_with_refcount_hash dpa__u_bo__alloc_p_any_bo_with_refcount_hash

dpa__u_api inline dpa__u_boptr_t dpa__u_bo__alloc_p_any_bo_with_refcount(dpa_u_bo_t bo, dpa_u_refcount_freeable_t* refcount, dpa__u_bo_refcounted_t*restrict cmem){
  *cmem = (dpa__u_bo_refcounted_t){
    .refcount = refcount,
    .bo = bo,
  };
  return DPA__U_BO_TAG(
    &cmem->bo, 
    dpa_u_refcount_is_static_p(&refcount->refcount)
     ? DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC
     : DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED
  );
}
#define dpa__u_bo__alloc_p_gc_bo_with_refcount dpa__u_bo__alloc_p_any_bo_with_refcount
#define dpa__u_bo__alloc_p_refcounted_bo_with_refcount dpa__u_bo__alloc_p_any_bo_with_refcount


