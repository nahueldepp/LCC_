
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
    
    disp(iter)
    
endfunction

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
    disp(p)
    w = 2 / (1 + sqrt(1 - p^2));
endfunction

