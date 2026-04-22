
function x = SOR(A, b, x0, w, tol, iter_max)
  n = size(A, 1)
  x=x0
  x0(1)=(1-w)*x0(1)+w*(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
  for i=2:n-1
    x0(i)=(1-w)*x0(i)+w*(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i)
  end
  x0(n)=(1-w)*x0(n)+w*(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
  iter=1;
  while(iter<iter_max)&&(norm(x-x0)>tol)
    x=x0
    x0(1)=(1-w)*x0(1)+w*(b(1)-A(1,2:n)*x0(2:n))/A(1,1)
    for i=2:n-1
      x0(i)=(1-w)*x0(i)+w*(b(i)-A(i,1:i-1)*x0(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i)
    end
    x0(n)=(1-w)*x0(n)+w*(b(n)-A(n,1:n-1)*x0(1:n-1))/A(n,n)
    iter=1+iter;
  end
  disp("Iterciones",iter)
endfunction

function w=omega_opt(A)
  //A es una matriz definida positiva y tridiagonal 
  [n,m]=size(A);
  T_j=eye(n,n)-diag(1./diag(A))*A;
  autovalores=spec(T_j);
  rho=max(abs(autovalores))//ver help eigs
  w=2/(1+sqrt(1-rho**2));
endfunction


//Ejercicio 5
function x=ej5()
    A = [4  3  0;
         3  4 -1;
         0 -1 4];
    b = [24; 30; -24];
    x0 = [3.5; 3.8; -4.8]; // Solucion del sistema: x = [3; 4; -5]
    eps = 10 ** -7;
    w = 1.2404082; // Calculado en cuaderno de practica
    
    x=SOR(A, b, x0, w, eps, 1000);
endfunction
