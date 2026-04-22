////Ejercicio 5 de la practica complementaria 

//----------------------------------------

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

//omega, polinomio productoria

function Op= Opoly(nodos)
  Op=poly(nodos,"x","r");
endfunction

// Acotacion del error del polinomio de interpolacion
// p es el valor donde se interpola y
// eps = max |f^(n)(x)| con n = cant. de nodos
function s = interpolation_error(p, nodos, eps)
    n = length(nodos);
    s = abs((prod(p * ones(n,1) - nodos') * eps)) / factorial(n);
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
//----------------------------------------

//f(x)=e^x

deff("y=f(x)","y=%e^x");

//a
nodosUni=[-1 -1/3 1/3 1];
y=[f(-1) f(-1/3) f(1/3) f(1)];
op=interpol_error_poly(nodosUni,%e);
p=interpol_New(nodosUni,y);
disp(p,"Polinomio obtenido usando diferencias divididas de Newton y nodos uniformemente espaciados:");
//b c
v_1=horner(p,-0.9);
v_2=horner(p,0.01);
vr_1=%e^-0.9;
vr_2=%e^0.01;

err1=abs(-v_1+vr_1);
err2=abs(v_2-vr_2);

cotaError1=interpolation_error(-0.9,nodosUni,f(1));
cotaError2=interpolation_error(0.01,nodosUni,f(1));

disp(v_1,"valor aproximado de p(-0.9)");
disp(vr_1,"valor determinado por Scilab de p(-0.9)");
disp(err1,"error relativo en la aproximacion:");
disp(cotaError1,"Cota de error en el punto de interpolacion: ");
disp(v_2,"valor aproximado de p(0.01)");
disp(vr_2,"valor determinado por Scilab de p(0.01)");
disp(err1,"error relativo en la aproximacion:");
disp(cotaError2,"Cota de error en el punto de interpolacion: ");

//d

//como f=e^x es n veces derivable y f^(n)=e^x, luego max(|f^(n)(x)|)=f(1)=e, luego
//|f(x)-p(x)|<=max|f(x)-pn(x)|<=s = interpolation_error(p, x, eps)
[val,idval]=abs_val_poly(op,-1,1);
disp(val, "la cota de error del polinomio p es:")


//e

nodosCheby= cheby_nodos( 4);
y2=[f(nodosCheby(1)) f(nodosCheby(2)) f(nodosCheby(3)) f(nodosCheby(4))]

q=interpol_New(nodosCheby',y2);
disp(q,"Polinomio obtenido usando diferencias divididas de Newton y nodos de Chebyshev ");
//f
oq=interpol_error_poly(nodosCheby',%e)
[valq,idvalq]=abs_val_poly(oq,-1,1);
disp(valq, "la cota de error del polinomio q es:");

rango=-1:0.1:1
plot2d(nodosUni,y,-1);
plot2d(nodosCheby,y2,-1);
function plot_pol_interpolantes()
  plot2d(rango,[horner(p,rango'),f(rango'),horner(q,rango')],[5 2 3],leg="p(x)@e^x@q(x)");
xtitle("nodos uniformemente distribuidos vs nodos de Chebyshev");
xlabel("x");
ylabel("y");
endfunction

plot2d(rango,[abs(horner(op,rango')),abs(horner(oq,rango'))],[5 3],leg="errP@errQ");
