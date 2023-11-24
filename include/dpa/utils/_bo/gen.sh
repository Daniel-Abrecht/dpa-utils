#!/bin/bash
shopt -s globstar nullglob

cd "$(dirname "$0")"
for d in */
do (
  exec >"${d%/}.h"
  cd "$d"
  incpath="$(realpath . | sed -n 's .*/include/  p')"
  for f in **/*.h
  do
    [ "$f" != 'all.h' ] || continue
    printf "#include <%s/%s>\n" "$incpath" "$f"
  done
); done
