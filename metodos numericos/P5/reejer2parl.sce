// re ejer2 parcial

A=[10 5 0 0;5 10 -4 0; 0 -4 8 -1;0 0 -1 5];
b=[6 25 -11 -11]'


function w=omega_opt(A)
  //A es una matriz definida positiva y tridiagonal 
  [n,m]=size(A);
  T_j=eye(n,n)-diag(1./diag(A))*A;
  autovalores=spec(T_j);
  rho=max(abs(autovalores))//ver help eigs
  w=2/(1+sqrt(1-rho**2));
endfunction

// Parametro w optimo para matrices tridiagonales
function w = omega_tridiag(A)
    n = size(A, 1);
    T = eye(A) - diag(1./diag(A))* A;
    p = max(abs(spec(T)));
    w = 2 / (1 + sqrt(1 - p^2));
endfunction


function rad_espec= r_SOR(w, A)
  [n,m]=size(A);
  D=diag(diag(A));
  L=zeros(n,n);
  for i=2:n
    L(i,1:i-1)= A(i,1:i-1);
  end
  U=A-L-D;
  
  Tw=inv(D+w*L)*(-(1-w)*D + w*U)
  espectro=spec(Tw)
  rad_espec=max(abs(espectro))
endfunction

function y=evaluar_ran(A,rango)
  n=size(rango,1);
  y=zeros(n);
  for i=1:n
    y(i)=r_SOR(rango(i),A)
  end
endfunction


disp("a)");
disp("omega opt")
w=omega_tridiag(A);
disp(w)
rad_espec=r_SOR(w,A);
disp(rad_espec,"radio espectral de Tw");

disp("b)");

  rango=0:0.001:2
  
  plot2d(rango,evaluar_ran(A,rango'))
  
disp("c)")

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
  disp(iteraciones, "Iteraciones: ");
    disp(operaciones, "Operaciones");
endfunction


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
    disp(iteraciones, "Iteraciones: ");
    disp(operaciones, "Operaciones");
endfunction

x0=[0 0 0 0]';
eps= 10^-6;
x=seidel(A,b,x0,eps);
x2=jacobi(A,b,x0,eps);
disp(x)
disp(x2)

disp("d)")

function x = SOR(A,b,x0,iter_max,tol,w)
    n = size(A,1)
    x = x0
    x0(1) = (1-w)*x0(1)+w*(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
    for i=2:(n-1)
        x0(i) = (1-w)*x0(i)+w*(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i)
    end
    x0(n) = (1-w)*x0(n)+w*(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
    iter= 1
    err = norm(x0-x)
    
    while (err>tol)&&(iter<iter_max)
        x = x0
        x0(1) = (1-w)*x0(1)+w*(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
        for i=2:(n-1)
            x0(i) = (1-w)*x0(i)+w*(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i)
        end
        x0(n) = (1-w)*x0(n)+w*(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
        iter = iter + 1
        err = norm(x0-x)
    end
    
    disp(iter, "iteraciones")
    
endfunction

x_sor=SOR(A,b,x0,500,eps,w)

disp(x_sor,"Metodo de sobrerelajacion")
