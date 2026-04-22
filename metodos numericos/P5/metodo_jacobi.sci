//metodo jacobi 

//xi**{k+1}=
//1/aii (bi-sum_{j=1,j/=i}**{n}*aij xj**{k})

function x=jacobi(A,b,x0,eps)
    n=size(A,1)
    iteraciones=0;
    operaciones=0;
    x=x0;
    xk=x;
    for  i=1:n
        suma=0;
        for j=1:n
            if (j<>i)then
                suma=suma+A(i,j)*xk(j);
                operaciones= operaciones +2;
            end
        end
        x(i)=(1/A(i,i))*(b(i)-suma);
        operaciones= operaciones +1;
    end
    iteraciones= iteraciones + 1;
    while (norm(x-xk)>eps)
       xk=x;
        for  i=1:n
            suma=0;
            for j=1:n
                if (j<>i)then
                    suma=suma+A(i,j)*xk(j);
                    operaciones= operaciones +2;
                end
            end
            x(i)=(1/A(i,i))*(b(i)-suma);
            operaciones= operaciones +1;
        end
        iteraciones= iteraciones + 1;
    end
  disp("Iteraciones: ",iteraciones);
  disp("Operaciones",operaciones);
endfunction

//jacobi en fora matricial
function x=jacobi2(A,b,x0,eps)
  n=size(A,1)
  x(1)=(b(1)-A(1,2:n)*x0(2:n))/A(1,1);
  for i=2:n-1
    x(i)=(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);
  end
  x(n)=(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
  cont=1
  while norm(x0-x,2)>eps
   x0=x
   x(1)=(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
    for i=2:n-1
      x(i)=(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);
    end
  x(n)=(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
  cont=cont+1
end
disp(cont)
endfunction


//Gauss-Seidel
//xi**{k+1}=
//1/aii (bi-sum_{j=1,j/=i}:{n}*aij xj**{k})
//         -sum(j=i+1,n)**n aij**(k+1))

function x=seidel(A,b,x0,eps)
    n=size(A,1)
    iteraciones=0;
    operaciones=0;
    
    x=x0;
    xk=x
    for  i=1:n
        suma=0;
        for j=1:n
            if (j<>i)
                suma=suma+A(i,j)*x(j);//cambio 
                operaciones= operaciones + 2;
                
            end
        end
        x(i)=1/A(i,i)*(b(i)-suma);
        operaciones= operaciones + 1;
    end
    iteraciones=iteraciones+1;
    
    while norm(x-xk)>eps
             xk=x
        for  i=1:n
            suma=0;
            for j=1:n
                if (j<>i)
                    suma=suma+A(i,j)*x(j);//cambio
                    operaciones= operaciones + 2;
                end
            end
            x(i)=1/A(i,i)*(b(i)-suma);
            operaciones= operaciones + 1;
        end
        iteraciones=iteraciones+1;
    end
    disp("Iteraciones: ",iteraciones);
    disp("Operaciones",operaciones);
endfunction

//Seidel forma matricial
function x=seidel2(A,b,x0,eps)
  n=size(A,1)
  operaciones=0;
  x(1)=(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
  operaciones=operaciones+3
  
  for i=2:n-1
    x(i)=(b(i)-A(i,1:i-1)*x(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);
    operaciones=operaciones+5
  end
  x(n)=(b(n)-A(n,1:n-1)*x(1:n-1))/A(n,n)
  operaciones=operaciones+3
  iteraciones=1;
  while norm(x0-x,2)>eps
   x0=x
   x(1)=(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
   operaciones=operaciones+3
    for i=2:n-1
      x(i)=(b(i)-A(i,1:i-1)*x(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);
      operaciones=operaciones+5
      iteraciones= iteraciones + 1;
    end
  x(n)=(b(n)-A(n,1:n-1)*x(1:n-1))/A(n,n)
  operaciones=operaciones+3
end
disp(iteraciones,"iteraciones")
disp(operaciones,"operaciones")
endfunction

//Gauss_seidel_tridiag, practica 5 compl
// ej,-1,2-1
function x=gauss_seidel_tridiag(A,b,x0,eps)
n=size(A,1);

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
endfunction

//condiciones de convergencia 

function [b1,b2]=condicion_convergencia(A)
  n=size(A,1)
  I=eye(n,n)
  N1=diag(diag(A))
  N2=zeros(n,n)
  for k=1:n
    N2(k:n,k)=A(k:n,k)
  end
  
  b1=norm(I-(N1**-1).*A)
  b2=norm(I-(N2**-1).*A)
  
endfunction







