#Paweł Prusisz
param n, integer, >= 2, default 10;
param m, integer, >= 2, default 10;

set cnt;
set ctn;

param conteners {i in cnt, j in ctn}, binary;

param k, integer >= 1;

var c {1..n, 1..m}, binary ;

minimize cameras : sum {i in 1..n, j in 1..m} c[i,j];

subject to cam {i in 1..n, j in 1..m} : conteners[i,j] + c[i,j] <= 1;

subject to cover {i in 1..n, j in 1..m} :
    sum {a in 1..n, b in 1..m} 
        if 
        (
            ( (abs(a-i) <= k) and (j = b) ) 
            or 
            ( (abs(b-j) <= k) and (i = a) ) 
        )
        then c[a,b] else 0 >= if conteners[i,j] >=1 then 1 else 0;

solve;

display cameras;
printf "\nconteners:\n";
for{i in 1..n}
{
    for{j in 1..m}
    {
        printf conteners[i,j];
        printf " ";
    }
    printf"\n";
}
printf "\ncameras:\n";
for{i in 1..n}
{
    for{j in 1..m}
    {
        printf c[i,j];
        printf " ";
    }
    printf"\n";
}
printf "\ncover\n";
for{i in 1..n}
{
    for{j in 1..m}
    {
        printf cover[i,j];
        printf " ";
    }
    printf"\n";
}