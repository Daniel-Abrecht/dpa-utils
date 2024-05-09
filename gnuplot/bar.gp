#!/usr/bin/gnuplot -c

input=ARG1

set term svg size 960,540 dynamic

set grid ytics mytics
set ytics 0.5
set autoscale fix
set key outside

set style data histogram
set style histogram cluster gap 1
set style fill solid
set boxwidth 1

set datafile separator '\t'
n = system("grep -v '^#' '".input."' | head -n 1 | tr '\t' '\n' | wc -l")
plot for[i=2:n] "<(grep -v '^#' ".input.")" using i:xtic(1) title columnhead(i)
