function [x,a] = gausselimPP(A,b)
// Esta función obtiene la solución del sistema de ecuaciones lineales A*x=b, 
// dada la matriz de coeficientes A y el vector b.
// La función implementa el método de Eliminación Gaussiana con pivoteo parcial.

[nA,mA] = size(A) 
[nb,mb] = size(b)

if nA<>mA then
    error('gausselim - La matriz A debe ser cuadrada');
    abort;
elseif mA<>nb then
    error('gausselim - dimensiones incompatibles entre A y b');
    abort;
end;

a = [A b]; // Matriz aumentada
n = nA;    // Tamaño de la matriz

// Eliminación progresiva con pivoteo parcial
for k=1:n-1
    kpivot = k;
    amax = abs(a(k,k));  //pivoteo
    for i=k+1:n
        if abs(a(i,k))>amax then
            kpivot = i; amax = a(i,k);
        end;
    end;
    temp = a(kpivot,:);
     a(kpivot,:) = a(k,:); 
     a(k,:) = temp;
    
    for i=k+1:n
        for j=k+1:n+1
            a(i,j) = a(i,j) - a(k,j)*a(i,k)/a(k,k);
        end;
        for j=1:k        // no hace falta para calcular la solución x
            a(i,j) = 0;  // no hace falta para calcular la solución x
        end              // no hace falta para calcular la solución x
    end;
end;

// Sustitución regresiva
x(n) = a(n,n+1)/a(n,n);
for i = n-1:-1:1
    sumk = 0
    for k=i+1:n
        sumk = sumk + a(i,k)*x(k);
    end;
    x(i) = (a(i,n+1)-sumk)/a(i,i);
end;
endfunction

// Ejemplo de aplicación
A2 = [0 2 3; 2 0 3; 8 16 -1]
b2 = [7 13 -3]'

[x2,a2] = gausselimPP(A2,b2)
disp(x2)
disp(a2)

function[x,a]=gausselimPPTri(A,b)
    [nA,mA]=size(A)
    [nb,mb]=size(b)
    if nA<>mA then error('gausselim-La matriz A debe ser cuadrada');
                   abort;
    else 
        if mA<>nb then error('gausselim - dimensiones incompatibles entre A y b');
                       abort;
        end;
    end;
    a=[A b];//Matriz aumentada
    n=nA;//Tamaño de la matriz
    contador=0;
    //Eliminación progresiva con pivoteo parcial
    for k=1:n-1 do
        kpivot=k;
        amax=abs(a(k,k)); //pivoteo
        if abs(a(k+1,k))>amax then  temp=a(k+1,:);
                                    a(k+1,:)=a(k,:);
                                    a(k,:)=temp;//Intercambiamos las filas k y k+1
        end;
        for j=k+1:n+1 do
            a(k+1,j)=a(k+1,j)-a(k,j)*a(k+1,k)/a(k,k);
            contador=contador+3;
        end;
    end;
    //Sustitución regresiva
    x(n)=a(n,n+1)/a(n,n);
    x(n-1)=(a(n-1,n+1)-a(n-1,n)*x(n))/a(n-1,n-1);
    contador=contador+4;
    for i=n-2:-1:1 do
        x(i)=(a(i,n+1)-a(i,i+1)*x(i+1)-a(i,i+2)*x(i+2))/a(i,i);
        contador=contador+5;
    end
    disp(contador);
endfunction


function [x,a]=gausselimTri(A,b)
    [nA,mA]=size(A);
    [nb,mb]=size(b);
    if nA<>mA then error('gausselim-LamatrizAdebesercuadrada');
                   abort;
    else 
        if mA<>nb then error('gausselim - dimensiones incompatibles entre A y b');
                       abort;
        end;
    end;
    
    a=[A b];//Matriz aumentada
    n=nA;//Tamaño de la matriz
    contador=0;
    //Eliminación progresiva sin pivoteo
    for k=1:n-1 do
        mkk=a(k+1,k)/a(k,k);
        a(k+1,k+1)=a(k+1,k+1)-mkk*a(k,k+1);
        a(k+1,n+1)=a(k+1,n+1)-mkk*a(k,n+1);
        contador=contador+5;
    end;
    //Sustitución regresiva
    x(n)=a(n,n+1)/a(n,n);
    contador=contador+1;
    for k=n-1:-1:1 do
        x(k)=(a(k,n+1)-a(k,k+1)*x(k+1))/a(k,k);
        contador=contador+3;
    end;
    disp(contador);
    disp(a)
   
endfunction
A1 = [1 1 0 0;1 1 1 0;0 1 1 1; 0 0 1 1]
b1 = [2;3;3;2]

A2 = [2 2 0 0; 5 2 2 0; 0 5 2 2; 0 0 5 2]
b2 = [6;15;24;23]

A3 = [2 1 0 0;1 2 1 0;0 1 2 1;0 0 1 2]
b = [1;1;1;1]
