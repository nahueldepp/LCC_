//ejercicio 2 parcial 

A=[10 5 0 0;5 10 -4 0;0 -4 8 -1; 0 0 -1 5]
w = omega_tridiag(A)

function x = r_SOR(w)
  A=[10 5 0 0;5 10 -4 0;0 -4 8 -1; 0 0 -1 5]
  l=length(w)
  n=size(A,1)
  L=zeros(n,n)
  D=diag(diag(A))
  U=zeros(n,n)
  
  for i=2:n
    L(i:n,1:i-1)=A(i:n,1:i-1)
  end
  for i=2:n
    U(1:i-1,i:n)=A(1:i-1,i:n)
  end
 Tw=inv(D+w*L)*((1-w)*D-w*U)
 
 x=max(abs(spec(Tw)))
endfunction

function y=G_sor(x)
  n=length(x)
  for i=1:n
    y(i)=r_SOR(x(i))
  end
endfunction
//b

rango=[0:0.01:2]

plot2d(rango,G_sor(rango))


//c

x0=[0 0 0 0]'
eps=10^-6
b=[6 25 -11 -11]'
x=seidel2(A,b,x0,eps)

//d
iter_max=1000

x2 = SOR(A,b,x0,iter_max,eps,w)
disp(x2)
