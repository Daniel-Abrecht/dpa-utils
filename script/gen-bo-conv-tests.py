#!/usr/bin/env python3

import json

# STATIC UNIQUE REFCOUNTED HASHED SIMPLE

types={
  "bo": {
    "tags": frozenset({
      frozenset({"SIMPLE"})
    }),
    "conv_macros": False
  },
  "a_bo_unique": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
    }),
    "conv_macros": False
  },
  "a_bo_any": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
      frozenset({"SIMPLE"}),
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_gc": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_refcounted": {
    "tags": frozenset({
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_hashed": {
    "tags": frozenset({
      frozenset({"SIMPLE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  }
}
for name, entry in types.items():
  entry["name"] = name

def get_bo(datatype, tags, value=None, refcount=None):
  tags = frozenset(tags)
  typeinfo = types.get(datatype)
  if not typeinfo:
    return None
  if tags not in typeinfo['tags']:
    return None
  if 'UNIQUE' in tags:
    if 'SIMPLE' not in tags:
      if len(value) > 7:
        return None
    elif 'HASHED' in tags:
      if len(value) < 64:
        return None
    else:
      if len(value) <= 7:
        return None
    stags = 'DPA_U_BO_SIMPLE'
    if 'STATIC' in tags:
      stags = 'DPA_U_BO_SIMPLE|DPA_U_BO_STATIC'
    return f'((dpa_u_{datatype}_t){{dpa__u_bo_intern_h(((dpa_u_a_bo_any_t){{DPA__U_BO_TAG(&bo, {stags})}})).p}})'
  if datatype == 'bo':
    if tags != frozenset({'SIMPLE'}):
      return None
    return 'bo'
  if not refcount and 'REFCOUNTED' in tags:
    if 'STATIC' in tags:
      refcount = "&dpa_u_refcount_static_v_freeable"
    else:
      refcount = '&refdata->refcount'
  if 'HASHED' in tags and 'REFCOUNTED' in tags:
    return f'''((dpa_u_{datatype}_t){{DPA__U_BO_TAG((&(struct dpa__u_bo_refcounted_hashed){{
  .rbo = {{
    .refcount = {refcount},
    .bo = bo
  }},
  .hash = dpa__u_bo_hash(bo)
}}.rbo.bo), {"|".join("DPA_U_BO_"+x for x in tags)})}})'''
  if 'REFCOUNTED' in tags:
    return f'''((dpa_u_{datatype}_t){{DPA__U_BO_TAG((&(struct dpa__u_bo_refcounted){{
  .refcount = {refcount},
  .bo = bo
}}.bo), {"|".join("DPA_U_BO_"+x for x in tags)})}})'''
  if 'HASHED' in tags:
    return f'''((dpa_u_{datatype}_t){{DPA__U_BO_TAG((&(struct dpa__u_bo_hashed){{
  .bo = bo,
  .hash = dpa__u_bo_hash(bo)
}}.bo), {"|".join("DPA_U_BO_"+x for x in tags)})}})'''
  return  f'((dpa_u_{datatype}_t){{DPA__U_BO_TAG(&bo, {"|".join("DPA_U_BO_"+x for x in tags)})}})'

vi=0
def gen_testcase(f, outbo, inbo=types['bo'], intags=frozenset({'SIMPLE'}), outtags=None):
  global vi
  if not outtags:
    outtags = intags
  with_refcount = 'with_refcount' in f or 'with_refcount_hash' in f
  with_hash = 'with_hash' in f or 'with_refcount_hash' in f
  args=['inbo']
  if with_refcount:
    args.append('refcount')
  if with_hash:
    args.append('hash')
  args=f'({", ".join(args)})'
  intags = frozenset(intags)
  outtags = frozenset(outtags)
  vi += 1
  if 'UNIQUE' in intags:
    if 'SIMPLE' not in intags:
      value = str(vi)
    elif 'HASHED' in intags:
      value = str(vi) + ' ' * 64
    else:
      value = str(vi) + ' ' * 7
  else:
    value = str(vi)

  s = f"""\
#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \\
  if(!(X)){{ \\
    fprintf(stderr, "assertion failed: %s\\n", #X); \\
    exit(1); \\
  }}

int main(){{
"""

  if (with_refcount or 'REFCOUNTED' in intags) and 'UNIQUE' not in intags and 'STATIC' not in intags:
    s += f"""\
  dpa_u_refcount_freeable_data_t* refdata = dpa_u_refcount_freeable_copy({json.dumps(value)}, {len(value)}, 1);
  const dpa_u_bo_t bo = {{
    .size={len(value)},
    .data=refdata->data
  }};
"""
  else:
    s += f"""\
  const dpa_u_bo_t bo = {{
    .size={len(value)},
    .data={json.dumps(value)}
  }};
"""
  sinbo = get_bo(inbo['name'], intags, value)
  s += f"const dpa_u_{inbo['name']}_t inbo = {sinbo};\n"
  if with_refcount:
    if 'STATIC' in intags:
      s += f'  dpa_u_refcount_freeable_t* refcount = &dpa_u_refcount_static_v_freeable;\n';
    else:
      s += f'  dpa_u_refcount_freeable_t* refcount = &refdata->refcount;\n';
  if with_hash:
    s += f'  const uint64_t hash = dpa__u_bo_hash(bo);\n';
  s += f"""\
  const dpa_u_{outbo['name']}_t outbo = {f}{args};
  expect((dpa_u_bo_get_type(outbo) & 0xF8) == ({"|".join("DPA_U_BO_"+x for x in outtags)}));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
}}
"""
  name=f'test/gen/{f}-from-{inbo["name"]}-{"-".join(sorted(intags))}.c'
  with open(name, 'w') as f:
    print(s, file=f)
  print(name)

def gen_testcases():
  for f in "dpa_u_make_", : # , "dpa_u_alloc_":
    for a in types.values():
      if not a['conv_macros']:
        continue
      if frozenset({"SIMPLE","REFCOUNTED"}) in a["tags"]:
        gen_testcase(f'{f}{a["name"]}_with_refcount', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"REFCOUNTED"})
      if frozenset({"SIMPLE","HASHED"}) in a["tags"]:
        gen_testcase(f'{f}{a["name"]}_with_hash', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"HASHED"})
      if frozenset({"SIMPLE","HASHED","REFCOUNTED"}) in a["tags"]:
        gen_testcase(f'{f}{a["name"]}_with_refcount_hash', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"REFCOUNTED","HASHED"})
        gen_testcase(f'{f}{a["name"]}_with_refcount_do_hash', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"REFCOUNTED","HASHED"})
      if frozenset({"SIMPLE","HASHED","STATIC"}) in a["tags"]:
        gen_testcase(f'{f}{a["name"]}_static_with_hash', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"HASHED","STATIC"})
        gen_testcase(f'{f}{a["name"]}_static_do_hash', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"HASHED","STATIC"})
      if frozenset({"SIMPLE","STATIC"}) in a["tags"]:
        gen_testcase(f'{f}{a["name"]}_static', a, types['bo'], {'SIMPLE'}, {'SIMPLE',"STATIC"})
      for b in types.values():
        common_tags = a["tags"].intersection(b["tags"])
        if len(common_tags) == 0:
          continue
        for tags in common_tags:
          if a["name"] != 'bo':
            gen_testcase(f'{f}{a["name"]}_do_hash', a, b, tags, tags if 'UNIQUE' in tags else frozenset({*tags,'HASHED'}))
          gen_testcase(f'{f}{a["name"]}', a, b, tags)

gen_testcases()
