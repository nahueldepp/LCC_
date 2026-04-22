//Practica 4


//Resolucion sis triangular superior

function X=superior(U,b)
    [fA,cA]=size(U)
    X(fA)=b(fA)/U(fA,cA)
    for i=cA-1:-1:1
        sums=0;
        for j=i+1:fA
            sums= sums + U(i,j)*X(j)
        end
        X(i)=(b(i)-sums)./U(i,i)
    end
endfunction

//Resolucion sis triangular inf 
function X=inferior(L,b)
 [nL,mL]=size(L);
 X(1)=b(1)/L(1,1);
 
 for i=2:nL
   sums=0;
     for j=1:i-1
         sums=sums+L(i,j)*X(j);
     end
     X(i)=(b(i)-sums)/L(i,i)
 end
endfunction


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
        n=nA  
    for k=1:n-1 // n-1 es la cantidad fi->fi-afj, como no opero sobre la priera fila, tengo q hacerlo sobre las n-1 restantes
            for i=k+1:n
                for j=k+1:n+1
                   
                    a(i,j)=a(i,j)-(a(i,k)./a(k,k))*a(k,j);
                end
                for j=1:k
                  a(i,j)=0;
                end
            end
    end
    
    // sustitucion regresiva
    x(n)=a(n,n+1)./a(n,n)
    
    for k=n-1:-1:1
      sums=0;
      for j=k+1:n
        sums=sums+a(k,j).*x(j)
      end
      x(k)=(a(k,n+1)-sums)./a(k,k)
       
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

function D=deter(A)
  [nA,mA]=size(A);
  for j=1:mA
    for i=(j+1):nA
      mij=A(i,j)./A(j,j);
      A(i,j)=0
      A(i,j+1:mA)=A(i,j+1:mA)-mij.*A(j,j+1:mA) // funcione distinto si para usar columnas se usa i o j+1
      end
  end
  D=1
  for i=1:mA
    D=A(i,i)*D ;
  end
endfunction

//eliminacion gussiana con pivoteo
//Dado una matriz A y un vector b, cacula el vector incognita x
function [x,a]=elim_guassPP(A,b)
  
  [nA,mA]=size(A)
  [nb,mb]=size(b)
  if nA<>mA then
     error("elim_gaussPP:La matriz debe ser cuadrada");
     abort;
  elseif mA<>nb then
     error("elim_gaussPP:LAs dimensiones de las matrices no coinciden")
     abort;
  end 
  
  a=[A,b]
  //eliminacion progresiva
  for j=1:mA
    //pivoteo
   amax=abs(a(j,j));
   for i=2:nA
     if abs(a(i,j))>amax then 
       temp=a(i,:);
       a(i,:)=a(j,:)
       a(j,:)=temp
     end
     end
     //triangulacion
     for i=(j+1):mA 
       mij=a(i,j)/a(j,j)
       a(i,j)=0
       a(i,j+1:mA+mb)=a(i,j+1:mA+mb)-mij*a(j,j+1:mA+mb)
   end
end
  
  //sustitucion regresiva 
x(nA,1)=a(nA,nA+1)./a(nA,mA)
      
  for i=(nA-1):-1:1

      x(i)=(a(i,nA+1)-a(i,(i+1):mA)*x((i+1):mA,1))/a(i,i)
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
 
 
 //ejercio 7
 
 function [a,L,P]=LU(A)
  
  [nA,mA]=size(A)
  P=eye(mA,mA);
  L=eye(mA,mA);
  if nA<>mA then
     error("elim_gaussPP:La matriz debe ser cuadrada");
     abort;
  end 
  
  //eliminacion progresiva
  for k=1:mA-1
    //pivoteo
   amax=abs(A(k,k));
   for i=(k+1):nA
     if abs(A(i,k))>amax then 
       temp=A(i,:);
       A(i,:)=A(k,:)
       A(k,:)=temp
       
       temp2=L(i,1:(k-1));
       L(i,1:(k-1))=L(k,1:(k-1));
       L(k,1:(k-1))=temp2;
       
       temp3=P(i,:);
       P(i,:)=P(k,:);
       P(k,:)=temp3;
     end
    end
    for i=(k+1):mA 
       L(i,k)=A(i,k)/A(k,k)
       A(i,k)=0
       A(i,k+1:mA)=A(i,k+1:mA)-L(i,k)*A(k,k+1:mA)
   end
 end
 a=A
 disp(L)
 disp(P)
endfunction


//sistema Ax=~b

function x=resolLU(A,b)
  
  [na,ma]=size(A);
  [nb,mb]=size(b);
  if nb<>ma then error("resolLU: Tamaños incompatibles")
  end
  
  [U,L,P]=LU(A);
  c=P*b
  y=inferior(L,c)
  x=superior(U,y)
endfunction
