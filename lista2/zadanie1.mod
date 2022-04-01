#Paweł Prusisz
set I;
set J;

param a {i in I};

param b {i in J};

param c {i in I, j in J};

var X {i in I, j in J} >= 0;

minimize Total_cost : sum {i in I, j in J} X[i,j] * c[i,j];

subject to Constraint1 {i in I} : sum {j in J} X[i,j] <= a[i];
subject to Constraint2 {j in J} : sum {i in I} X[i,j] >= b[j];

solve;

display X;
display Total_cost;

for{i in I}
{
    for{j in J}
    {
        printf X[i, j];
        printf " ";
    }
    printf "\n";
}
