//Funcion de eliminacion gaussiana
//para b un vector columna y A triangulable con pivotes no nulos
function [x,a]=elim_gauss(A,b)
    [nA,mA]=size(A);
    [nb,mb]=size(b);
      if nA<>mA then error("elim_gauss: La matriz debe ser cuadrada");
      elseif mA<>nb then error("elim_gauss: Las dimenciones de A y b no concuerdan")
      end
        // triangulacion a una matriz U, guadando los mij
        
        a=[A,b]; // matriz aumentada

//eliminacion progresiva
for j=1:(mA-1) do
  for i=(j+1):nA do
    mij=a(i,j)/a(j,j);
    a(i,j)=0;
    a(i,(j+1):(mA+mb))=a(i,(j+1):(mA+mb))-mij*a(j,(j+1):(mA+mb))
    end
end

    
    // sustitucion regresiva
    x(nA,1:mb)=a(nA,(nA+1):(nA+mb))./a(nA,mA)
    
  for i=(nA-1):-1:1

      x(i,1:mb)=(a(i,(nA+1):(nA+mb))-a(i,(i+1):mA)*x((i+1):mA,1:mb))./a(i,i)
  end
    disp(a)
endfunction


//Funcion de eliminacion gaussina 2
//para b un vector columna y A triangulable con pivotes no nulos
function [x,a]=elim_gauss2(A,b)
    [nA,mA]=size(A);
    [nb,mb]=size(b);
      if nA<>mA then error("elim_gauss: La matriz debe ser cuadrada");
      elseif mA<>nb then error("elim_gauss: Las dimenciones de A y b no concuerdan")
      end
        // triangulacion a una matriz U, guadando los mij
        
        a=[A,b]; // matriz aumentada

//eliminacion progresiva
for j=1:(mA-1) do
  for i=(j+1):nA do
    mij=a(i,j)/a(j,j);
    a(i,j)=0;
    a(i,(j+1):(mA+1))=a(i,(j+1):(mA+1))-mij*a(j,(j+1):(mA+1))
    end
end

    
    // sustitucion regresiva
    x(nA,1)=a(nA,nA+1)./a(nA,mA)
    
  for i=(nA-1):-1:1

      x(i)=(a(i,nA+1)-a(i,(i+1):mA)*x((i+1):mA,1))/a(i,i)
  end
    disp(a)
endfunction


//Funcion de eliminacion gaussina 3
//para B una matriz y A triangulable con pivotes no nulos
function [x,a]=elim_gauss3(A,b)
    [nA,mA]=size(A);
    [nb,mb]=size(b);
      if nA<>mA then error("elim_gauss: La matriz debe ser cuadrada");
      elseif mA<>nb then error("elim_gauss: Las dimenciones de A y b no concuerdan")
      end
        // triangulacion a una matriz U, guadando los mij
        
        a=[A,b]; // matriz aumentada

//eliminacion progresiva
for j=1:(mA-1) do
  for i=(j+1):nA do
    mij=a(i,j)/a(j,j);
    a(i,j)=0;
    a(i,(j+1):(mA+mb))=a(i,(j+1):(mA+mb))-mij*a(j,(j+1):(mA+mb))
    end
end

    
    // sustitucion regresiva
    x(nA,1:mb)=a(nA,(nA+1):(nA+mb))./a(nA,mA)
    
  for i=(nA-1):-1:1

      x(i,1:mb)=(a(i,(nA+1):(nA+mb))-a(i,(i+1):mA)*x((i+1):mA,1:mb))./a(i,i)
  end
    disp(a)
endfunction

//eliminacion gussiana con pivoteo
//Dado una matriz A y un vector b, cacula el vector incognita x
// Método de Eliminación Gaussiana con pivoteo parcial
function [x,a]=elim_gaussPP(A,b)
 [nA,mA] = size(A) 
[nb,mb] = size(b)
a = [A b];
n = nA;

for k=1:n-1
    kpivot = k; amax = abs(a(k,k));
    for i=k+1:n
        if abs(a(i,k))>amax then
            kpivot = i; amax = a(i,k);
        end;
    end;
    temp = a(kpivot,:); a(kpivot,:) = a(k,:);
    a(k,:) = temp
    
    for i=k+1:n
        for j=k+1:n+1
            a(i,j) = a(i,j) - a(k,j)*a(i,k)/a(k,k)
        end;
        for j=1:k
            a(i,j) = 0;
        end
    end
end

x(n) = a(n,n+1)/a(n,n)

for i = n-1:-1:1
    sumk = 0
    for k=i+1:n
        sumk = sumk + a(i,k)*x(k)
    end
    x(i) = (a(i,n+1)-sumk)/a(i,i)
end
endfunction

 function [x,a]=elim_gaussTrid(A,b)
   [nA,mA]=size(A)
   //diagonalizacion 
   for i=1:(nA-1) 
     mij=A(i+1,i)/A(i,i);
     A(i+1,i:(i+2))=A(i+1,i:(i+2))-mij*A(i,(i-1):(i+1))
   end
   A(nA,nA-1:nA)=A(nA,nA-1:nA)-(A(nA,nA-1)/A(nA-1,nA-1))*A(nA-1,n-1:n);
   a=A;
 endfunction
 
