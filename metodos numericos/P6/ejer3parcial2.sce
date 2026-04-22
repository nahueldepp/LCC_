//ejer 3 parcial 2

A=[10 1 1; 1 4 2; 1 2 1]
gres(A)
eps=10^-5
z1=[1,1,1]'
z2=[-0.462,-4.357,8.989]'
z3=[0,100,1000]'
iter=100
[valor1,zn1]=mpotencia(A,z1,eps,iter)
[valor2,zn2]=mpotencia(A,z2,eps,iter)
[valor3,zn3]=mpotencia(A,z3,eps,iter)

disp(valor1)
disp(valor2)
disp(valor3)
