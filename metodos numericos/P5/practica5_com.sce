
//Practica complementaria 

//x^{k+1}=(I-N^-1*A)x^{k}+N^-1*b
//Para Gauss-Seidel N=L+D, para una matriz tridiagonal
//Nij=Aij si i=j o i=j+1
//Nij=0 si i~j o i~j+1

function N=matriz_iter_(A)
  n=size(A,1)
  for i=1:n
    for j=1:n
      if(i==j)||(i==j+1)||(i==n)then
        N(i,j)=A(i,j)
      end
    end
  end
endfunction

//Ej 1
//xi = −n/4 + i/2, i = 1, 2, . . . , n.

function [A,b,x0]=make_tridiag(N,p)
  C=zeros(N,N);
  C(1,N)=1;
  C(N,1)=1;
  A=p*eye(N,N)-1*diag(ones(N-1,1),1)-1*diag(ones(N-1,1),-1)+C
  b=zeros(N,1);
  b(N)=1;
  x0=zeros(N,1);
endfunction


//Gauss_seidel_tridiag, practica 5 compl
// ejem,-1,2-1
function x=gauss_seidel_tridiag(A,b,x0,eps)
n=size(A,1);
  x=x0
  x(1)=(1/2)*(x0(2)-x(n));
  for i=2:n-1
    x(i)=(1/2)*(x(i-1)+x0(i+1));
  end
  x(n)=(1/2)*(1+x(n-1)-x(1));
  cont=1;
  while(norm(x-x0)>eps)
    x0=x;
    x(1)=(1/2)*(x0(2)-x(n));
    for i=2:n-1
        x(i)=(1/2)*(x(i-1)+x0(i+1));
     end
    x(n)=(1/2)*(1+x(n-1)-x(1));
    cont=cont+1;
  end
  disp(cont);
endfunction
//xi = −n/4 + i/2, i = 1, 2, . . . , n.

function x=tridiag_esp(A)
  n=size(A,1);
  for i=1:n
    x(i)=-(n/4)+(i/2);
  end
  
endfunction

//b
function esp=espectro_iter(N)
  esp=spec(N);
endfunction

//Ej 4
function [A,b,x0]=make_tridiag_2(N,c)
  A=(1+2*c)*eye(N,N)-c*diag(ones(N-1,1),1)-c*diag(ones(N-1,1),-1)
  b=zeros(N,1);
  b(N)=1;
  x0=zeros(N,1);
endfunction

function [L,U] =doolittle(A)
    [n, m] = size(A);
    if n<>m then
        error('doolittle - La matriz A debe ser cuadrada');
        abort;
    end;
    
    L = eye(n, n);
    U = zeros(n, n);
    
    U(1,:) = A(1,:);
    L(:,1) = A(:,1) / U(1,1);
    for k = 2:n
        U(k,k:n) = A(k,k:n) - L(k,1:k-1) * U(1:k-1,k:n);
        for j = k+1:n
            L(j, k) = (A(j, k) - L(j,1:k-1) * U(1:k-1,k)) / U(k,k);
        end
    end
endfunction

function x=eje_5b()
 [A]=make_tridiag_2(5,1);
 [L,U]=doolittle(A)
 disp(L)
 disp(U)
endfunction
