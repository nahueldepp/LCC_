//Unidad 7 
//Interpolación 

//Polinomios Lk(x)
//donde x es un vector, 
//k es el indice de la k-esima componente,
// Mx es la cantidad de componentes
function y=LK(x,k,Mx)
  
  r=[x(1:k-1)x(k+1:Mx)]
  p=poly(r,"x","roots")
  pk=horner(p,x(k))
  y=p/pk
endfunction

//donde x,y son vectores con las cordenas (xi,yi) de los puntos de interpolacion 
function z=interpollagrange(x,y)
  Mx=size(x,2)
  p=0
  for k=1:Mx
    p=p+(LK(x,k,Mx)*y(k))
  end
  z=p
endfunction


//Diferencias divididas de Newton 
//donde x,y son vectores con las coordenadas con los puntos de interpolacion
function w=DD(x,y)
  Mx=length(x);
  
  if Mx==1 then
    w=y(1)
  else
    w=(DD(x(2:Mx),y(2:Mx))-DD(x(1:Mx-1),y(1:Mx-1)))/(x(Mx)-x(1))
    //f[x1 x2 x3]=(f[x2 x3]-f[x1 x2])/x3-x1
  end
endfunction


//formula de interpolacion por Newton 

function pn=interpol_New(x,y)
  Mx=size(x,2)
  
  p=0
  r=poly(0,"x")
  for i=Mx:(-1):2
    //multiplicacion encajada
    p=(p+DD(x(1:i),y(1:i)))*(r-x(i-1))
  end
  pn=p+y(1)
endfunction


// Acotacion del error del polinomio de interpolacion
// p es el punto donde se interpola, x son los nodos y
// eps = max |f^(n)(x)| con n = cant. de nodos
function s = interpolation_error(p, x, eps)
    n = length(x);
    s = (prod(p * ones(n,1) - x') * eps) / factorial(n);
endfunction

function p=interpol_error_poly(nodos,eps)
  n = length(nodos);
  p=Opoly(nodos);
  p= p*eps/factorial(n);
endfunction

//determina el maximo valor absoluto de un polinomio en [a,b];
//maxVal es el mayor valor absoluto,
//xVal es la ordenada donde se alcanza;
function [maxVal,xVal]=abs_val_poly(p,a,b)
  x=linspace(a,b,1000);
  y=abs(horner(p,x));
  [maxVal,idx]=max(y);
  xVal=x(idx);
endfunction


//raices con cheby 

function x=cheby_nodos(n)
  if n==0 then
    r=[]
  else
    for i=1:n
      theta=(%pi*(2*i-1))/(2*n)
      x(i)=cos(theta)
    end
    x=flipdim(x,1);
  end
endfunction

function x = chebyshev_roots_general(a, b, n)
    x = cheby_nodos(n);
    x = ((b + a) + x .* (b - a)) ./ 2;
endfunction

function z=inter_cheby(f,n)
  deff("y=f(x)","y="+f)
  x=cheby_nodos(n)
  y=zeros(1,n)
  for i=1:n
    y(i)=f(x(i))
  end 
  z=interpollagrange(x',y)
endfunction

