#! /usr/bin/gnuplot

set term pdf color round font 'Source Sans Pro Bold'

binwidth =1 
bin(x,width)=width*floor(x/width)

#set xrange [70000:200000]


set table 'degrees.table'
plot 'degrees.txt' using (bin($1,binwidth)):(1) smooth freq  with boxes
unset table

set logscale xy;
load 'Paired.plt'
set style fill transparent solid 0.5
set samples 10000


lambda = 100000.0 
alpha = 10.0

sigma = sqrt(pi*lambda/2.0)/alpha
mu = 2.0*pi*lambda/alpha/alpha
N = 100000.0



f(x)=1.0/(sigma*sqrt(2*pi)) *exp(-1.0/2*((x-mu)/sigma)**2)


set output 'degrees.pdf'

plot [0.0001:] [10:]  'degrees.table' using 1:($2):(binwidth)  with boxes ls 5  title 'Degree distribution'
#plot [0.0001:]  'degrees.table' using 1:($2/N):(binwidth)  with boxes ls 5  title 'Degree distribution'
