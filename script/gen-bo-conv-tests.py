#!/usr/bin/env python3

import json

from bo_types import types

# STATIC UNIQUE REFCOUNTED HASHED SIMPLE

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
}}.rbo.bo), {"|".join("DPA_U_BO_"+x for x in sorted(tags))})}})'''
  if 'REFCOUNTED' in tags:
    return f'''((dpa_u_{datatype}_t){{DPA__U_BO_TAG((&(struct dpa__u_bo_refcounted){{
  .refcount = {refcount},
  .bo = bo
}}.bo), {"|".join("DPA_U_BO_"+x for x in sorted(tags))})}})'''
  if 'HASHED' in tags:
    return f'''((dpa_u_{datatype}_t){{DPA__U_BO_TAG((&(struct dpa__u_bo_hashed){{
  .bo = bo,
  .hash = dpa__u_bo_hash(bo)
}}.bo), {"|".join("DPA_U_BO_"+x for x in sorted(tags))})}})'''
  return  f'((dpa_u_{datatype}_t){{DPA__U_BO_TAG(&bo, {"|".join("DPA_U_BO_"+x for x in sorted(tags))})}})'

def gen_testcase(f, outbo, inbo=types['bo'], intags=frozenset({'SIMPLE'}), outtags=None):
  if outtags == None:
    outtags = intags
  do_free = '_alloc_' in f
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
  vi="test 1"
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
  s += f"  const dpa_u_{inbo['name']}_t inbo = {sinbo};\n"
  if with_refcount:
    if 'STATIC' in intags:
      s += f'  dpa_u_refcount_freeable_t* refcount = &dpa_u_refcount_static_v_freeable;\n';
    else:
      s += f'  dpa_u_refcount_freeable_t* refcount = &refdata->refcount;\n';
  if with_hash:
    s += f'  const uint64_t hash = dpa__u_bo_hash(bo);\n';
  s += f"""  const dpa_u_{outbo['name']}_t outbo = {f}{args};\n"""
  if not outtags:
    s += f"""\
  expect(dpa_u_bo_is_error(outbo));
  dpa_u_bo_put(inbo);
"""
  else:
    if 'STATIC' in outtags: # If a bo is static, it is always optional for it to have a refcount, because it'd always be a static refcount anyway
      s += f"""  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == ({"|".join("DPA_U_BO_"+x for x in sorted(outtags - {'REFCOUNTED'}))}));\n"""
    else:
      s += f"""  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_REFCOUNTED|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == ({"|".join("DPA_U_BO_"+x for x in sorted(outtags))}));\n"""
    s += f"""\
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
"""
    if do_free:
      s += '  dpa_u_bo_free(outbo);\n';
  s += "}\n"
  name=f'test/gen/{f}-from-{inbo["name"]}-{"-".join(sorted(intags))}.c'
  with open(name, 'w') as f:
    print(s, file=f)
  print(name)

def gen_testcases():
  for f in "dpa_u_make_", "dpa_u_alloc_":
    for a in sorted(types.values(), key=lambda x: x['name']):
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
      for b in sorted(types.values(), key=lambda x: x['name']):
        common_tags = a["tags"].intersection(b["tags"])
        if len(common_tags) == 0:
          continue
        for tags in sorted(b['tags'], key=lambda x: sorted(x)):
          otags = tags if 'UNIQUE' in tags else frozenset({*tags,'HASHED'})
          if a["name"] != 'bo':
            otags = tags if 'UNIQUE' in tags else frozenset({*tags,'HASHED'})
            gen_testcase(f'{f}{a["name"]}_do_hash', a, b, tags, otags if otags in a["tags"] else frozenset())
          if a["name"] != 'a_bo_hashed':
            otags = tags
          gen_testcase(f'{f}{a["name"]}', a, b, tags, otags if otags in a["tags"] else frozenset())

gen_testcases()
