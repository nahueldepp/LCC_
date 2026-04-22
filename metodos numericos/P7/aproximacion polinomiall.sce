//aproximacion polinomial


//Polinomio Chebyshev

function Tn=poli_cheby(n)
  s=poly(0,"x","r")
  T_0=1;
  T_1=s;
  for i=1:n
    Tn=T_1
    T_1=2*s*Tn-T_0
    T_0=Tn
  end
endfunction


//polinomio con menor maximo

function Tn=poli_ceby_minmax(n)
    s=poly(0,"x","r")
  T_0=1;
  T_1=s;
  for i=1:n
    Tn=T_1
    T_1=2*s*Tn-T_0
    T_0=Tn
  end
  Tn=Tn*(1/2^(n-1))
  
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



//Aproximacion de minimos cuadrados

// Matriz del método de mínimo cuadrados polinomial
function A = A_mc(x,grado)
    // p = grado+1
    m = length(x)
    A = ones(m,1)
    for j=1:(grado)
        A = [A,(x').^(j)]
    end
    
endfunction


// Aproximación polinomial de mínimos cuadrados para matrices con rango completo
function [p,err] = MinCuad_pol(A,b)
    [a,A_amp] = elim_gaussPP((A')*A,(A')*(b'));
    p = poly(a,"x","c")
    err = norm(A*a-(b'))

endfunction



// Acotacion del error del polinomio de interpolacion
// p es el punto donde se interpola, x son los nodos y
// eps = max |f^(n)(x)| con n = cant. de nodos
function s = interpolation_error(p, x, eps)
    n = length(x);
    s = (prod(p * ones(n,1) - x') * eps) / factorial(n);
endfunction

// Coeficienets de aproximacion de minimos cuadrados de orden n aplicando QR
function a = min_squares(x, y, grado,QR,use_inv)
    n = length(x);
    A=A_mc(x,grado)
    if QR then
        a = solve_QR(A, y,use_inv);
    else
        a = solve(A' * A, A' * y, use_inv);
    end
endfunction

// Polinomio obtenido de la aproximacion de minimos cuadrados de orden n
function p = min_squares_poly(x, y, grado,QR,use_inv)
    a = min_squares(x, y, grado,QR,use_inv);
    p = poly(a, "x", "c");
endfunction

// f es string y p es polinomio
function plot_error(f, p, a, b)
    deff("y = F(x)", "y = " + f);
    x = linspace(a, b, 500);
    plot2d(x, F(x) - horner(p, x));
endfunction

//-----------------------------------------------
function x = solve_QR(A, b,use_inv)
    [Q, R] = qr_factor(A);
    
    if use_inv then
      x=inv(R)*Q'*b
    else
      x = solve_upper(R, Q' * b);
    end
endfunction 
function x = solve(A, b,use_inv)
n = size(A, 1);
if use_inv then
    [x,a] = elim_gaussPP(A,b);
    x=inv(A)*b
else  
    [x,a] = elim_gaussPP(A,b);
end

endfunction

//---------------------------------------------------

// Matriz del método de mínimo cuadrados polinomial para dos variables
function A = A_mc_multi(x,v,grado)
    // p = grado+1
    m = length(x)
    A = ones(m,1)
    for j=1:(grado)
        A = [A,(x').^(j),(v').^(j)]
    end
    
endfunction



//donde a es el vector de los coeficientes de f
function z=fxv(x,v,a)
  z=a(1)+a(2)*x+a(3)*v
endfunction

function ejer6()
  x=[0 0 1 2 2 2]
  v=[0 1 0 0 1 2]
  y=[1.42 1.85 0.78 0.18 0.60 1.05]
  
  A= A_mc_multi(x,v,1)
  [a,A_amp] = elim_gaussPP((A')*A,(A')*(y'));
  a1=a(1)
  a2=a(2)
  a3=a(3)
  disp(a)
  scatter3(x,v,y)
  set(gca(),"auto_clear","off")
  deff("z=f(x,y)","z=a1+a2.*x+a3.*y")
  w=[-1:0.1:3]

  fplot3d(w,w,f)
endfunction
