#!/usr/bin/env python3

import sys

x=[]
y=[]
data=[]
first = True

with sys.stdin as f:
  for line in f:
    if len(line)==0 or line[0] == '#':
      continue
    if first:
      first = False
      continue
    p = line.split('\t')
    lx = p[0].strip()
    ly = p[1].strip()
    p = p[2:]
    if ly in y:
      yi = y.index(ly)
    else:
      yi = len(y)
      y.append(ly)
    if lx in x:
      xi = x.index(lx)
    else:
      xi = len(x)
      x.append(lx)
    xi+=1
    yi+=1
    while len(data) < yi+1:
      data.append([])
    while len(data[yi]) < xi+1:
      data[yi].append(None)
    data[yi][xi] = p[0].strip()

data[0] = [None,*x]
for i,e in enumerate(y):
  data[i+1][0] = e

for r in data:
  print('\t'.join([str(x) for x in r]))
