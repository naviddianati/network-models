#! /usr/bin/gnuplot

set term pdf color round font 'Source Sans Pro Bold'

name = "degrees-200"
filename = name.'.txt'
tablename = name.'.table'

binwidth =1
set grid

bin(x,width)=width*floor(x/width)

#set xrange [70000:200000]


set table tablename
plot filename using (bin($1,binwidth)):(1) smooth freq  with boxes
unset table

set logscale xy;
load 'Paired.plt'
set style fill transparent solid 0.1
set samples 10000


lambda = 100000.0 
alpha = 10.0

sigma = sqrt(pi*lambda/2.0)/alpha
mu = 2.0*pi*lambda/alpha/alpha
N = 100000.0





f(x) = a*x+b
g(x) = 10**b*(x**a)

h(x) = sqrt(2*pi)/x
fit  [0:1.1] f(x) tablename using (log10($1)):(log10($2)) via a,b


set output name.'.pdf'

#plot [0.0001:] [10:]  tablename using 1:($2):(binwidth)  with boxes ls 5  title 'Degree distribution'
plot  []  tablename using 1:($2):(binwidth)  with points ls 2 pt 2 ps 0.5 lw 3  title 'Degree distribution',\
    g(x) with lines lt 1 lc rgb "#33ff4500"  lw 6  title 'Fit: '.sprintf("a = %1.2f; b = %1.2f",a,b);
    
reset
set term pdf color round font 'Source Sans Pro Bold' size 5,5

set output name.'-graph.pdf'
set size square
set style fill transparent solid 0.3 noborder

#set palette rgbformulae 34,35,36;
#set palette rgbformulae 33,13,10;
set palette rgbformulae 21,22,23;
unset xtics
unset ytics
unset colorbox
set bmargin 2
plot [-1:1][-1:1] filename every 40 using 2:3:(($1)**(0.1)/100):1 with circles palette lw 5 notitle,\
    '' every 40 using 2:3:(log($1)) with points ls 7 lc rgb "#33ff4500" ps 0.01 notitle
   

