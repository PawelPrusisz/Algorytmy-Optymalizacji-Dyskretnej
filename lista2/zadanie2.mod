#Paweł Prusisz
param n, integer, >= 2;

set V, default {1..n};

set E within V cross V;

param time {(i,j) in E};

param cost {(i,j) in E};

param s, symbolic, in V, default 1;

param t, symbolic, in V, != s, default n;

param T, integer, default 1e9;

var X{(i, j) in E}, >= 0,  <= T, binary;



minimize totalCost : sum{(i, j) in E} X[i,j]*cost[i,j];

subject to Ttime : sum {(i,j) in E} X[i,j] * time[i,j] <= T;
subject to r{i in 1..n}: sum{(j,i) in E} X[j,i] + (if i = s then 1) =
                   sum{(i,j) in E} X[i,j] + (if i = t then 1);


solve;

display totalCost;
display Ttime;

for{(i,j) in E}
{
    printf (if X[i, j] > 0 then i else "");
    printf (if X[i, j] > 0 then " " else "");
    printf (if X[i, j] > 0 then j else "");
    printf (if X[i, j] > 0 then " " else "");
    printf (if X[i, j] > 0 then X[i,j] else "");
    printf (if X[i, j] > 0 then "\n" else "");

}