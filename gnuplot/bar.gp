#!/usr/bin/gnuplot -c

input=ARG1

set term svg size 960,540 dynamic

set grid ytics mytics
set key off
set xtics rotate by 90 right noenhance nomirror

set style fill solid
set boxwidth 0.5

set style data boxes

set datafile separator '\t'
n=system("grep -v '^#' '".input."' | wc -l")
plot input using 0:3:xtic(2)
