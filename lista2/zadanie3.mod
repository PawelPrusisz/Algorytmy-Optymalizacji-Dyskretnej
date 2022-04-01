#Paweł Prusisz
param n, integer, default 3;
param m, integer, default 3;

param minis {i in 1..n, j in 1..m};
param maks {i in 1..n, j in 1..m};

set mp;
set mz;

param minP {i in mp};
param minZ {j in mz};

var X {i in 1..n, j in 1..m};

minimize radjowozy : sum { i in 1..n, j in 1..m} X[i,j];

subject to shift {i in 1..n} : sum{j in 1..m} X[i, j] >= minP[i];
subject to dist {j in 1..m} : sum {i in 1..n} X[i, j] >= minZ[j];
subject to gen {i in 1..n, j in 1..m} : minis[i,j] <= X[i,j] <= maks[i,j]; 


solve;





for{i in 1..n}
{
    for{j in 1..m}
    {
        printf X[i,j];
        printf " "; 
    }
    printf "\n";
}
printf "--------\n";
for{i in 1..n}
{
    printf shift[i];
    printf " ";
}
printf "\n--------\n";
for{i in 1..m}
{
    printf dist[i];
    printf " ";
}
printf "\n";
display radjowozy;