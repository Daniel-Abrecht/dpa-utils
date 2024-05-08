#!/usr/bin/gnuplot -c

input=ARG1

set term svg size 960,540 dynamic

set grid xtics ytics mxtics mytics
set logscale
set autoscale fix
set key top left
#set xtics 2
#set ytics 2

set format x "10^{%T}"
set format y "10^{%T}"

set datafile separator '\0'
n=system("grep -v '^#' '".input."' | wc -l")
plot for [i=1:n] "<(grep -v '^#' '".input."' | sed -n '".i."s/\\t/\\n/gp')" \
  using 0:1 with linespoints \
  title columnhead(1) noenhance
