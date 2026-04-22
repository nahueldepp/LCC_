//ejercicio6 practica complementaria

//---------------------------------------------------------------


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

// Matriz del método de mínimo cuadrados polinomial para dos variables
function A = A_mc_multi(x,v,grado)
    // p = grado+1
    m = length(x)
    A = ones(m,1)
    for j=1:(grado)
        A = [A,(x').^(j),(v').^(j)]
    end
    
endfunction


// f es string y p es polinomio
function plot_error(f, p, a, b)
    deff("y = F(x)", "y = " + f);
    x = linspace(a, b, 500);
    plot2d(x, F(x) - horner(p, x));
endfunction

//-----------------------------------------------
function x = solve_QR(A, b,use_inv)
    [Q, R] = qr(A,"e");
    
    if use_inv then
      x=inv(R)*Q'*b
    else
      x = solve_upper(R, Q' * b);
    end
endfunction 
function x = solve(A, b,use_inv)
n = size(A, 1);
if use_inv then

    x=inv(A)*b
else  
    [x,a] = elim_gaussPP(A,b);
end

endfunction
//---------------------------------------------------------------

x=[0 0 1 2 2 2];
v=[0 1 0 0 1 2];
yp=[1.42 1.85 0.78 0.18 0.60 1.05];

A=A_mc_multi(x,v,1);
[Q,R]=qr(A,"e");
coef=inv(R)*Q'*yp'
a=coef(1);
b=coef(2);
c=coef(3);
s=linspace(20,1);
deff("y=f(x,v)","y= a + b*x +c*v");
scatter3([-5 5],[-5 5],[-5 5]);

scatter3(x,v,yp,mcolors="scilabgreen2","fill",marker="circle plus");
set(gca(),"auto_clear","off");

xy=[-1:0.1:3]
fplot3d(xy,xy,f);
