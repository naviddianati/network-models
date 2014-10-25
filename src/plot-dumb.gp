#! /usr/bin/gnuplot

#set term pdf color round font 'Source Sans Pro Bold'
#set term pdf color round font 'Source Sans Pro Bold' size 4,3
#set term pdf color round font 'Dosis' size 4,3

set term dumb size 80,40

name = "degrees-200"
name = "degrees-1200-100"
filename = name.'.txt'
tablename = name.'.table'

binwidth =1
#set grid

bin(x,width)=width*floor(x/width)

#set xrange [10:200]


set table tablename
plot filename using (bin($1,binwidth)):(1) smooth freq  with boxes
unset table

#load 'Paired.plt'
set style fill transparent solid 0.1
set samples 10000


lambda = 100000.0 
alpha = 10.0

sigma = sqrt(pi*lambda/2.0)/alpha
mu = 2.0*pi*lambda/alpha/alpha
N = 100000.0

set xtics scale 2
set ytics scale 2
set mytics 10
set mxtics 10

#set format y "10^{%T}"
#set format x "10^{%T}"
set border lw 3 lc rgb "#555555"

set key spacing 1.5 box lw 3 lc rgb "#555555"  textcolor rgb "#555555"

#f(x) = a*x+b
#g(x) = 10**b*(x**a)

#h(x) = sqrt(2*pi)/x
#poiss(n,lambda) = lambda**n * exp(-lambda)/(gamma(n+1))
poiss(x,lambda) = (lambda*1.0/x)**x *exp(x*1.0-lambda)/sqrt(2*pi*x)
#fit  poiss(x) tablename using 1:2 via lambda

#set output name.'.pdf'

s = 300*10000


#set logscale xy;
#plot   tablename using 1:($2):(binwidth)  with boxes ls 5  title 'Degree distribution'
plot   tablename using ($1):($2/freq1_sum/binwidth):(binwidth)  with points ls 7 pt 7 ps 0.5 lc rgb "#333333"   lw 0.5  title 'Agent-based model',\
      poiss(x,620) with lines lt 1 lc rgb "#ff4500"  lw 6  title 'Fit: '.sprintf("a = %1.2f; b = %1.2f",1,1);

   

