//Ejercicio 5 de la practica complementaria 
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
dia=0:30;
casosDiarios=[32 23 47 59 82 113 143 179 233 269 303 335 371 404 434 446 457 470 481 482 476 465 454 436 424 397 385 359 340 322 303]
casosTotales=cumsum(casosDiarios)

//sabemos que ln(casosTotales)=ln(g(t))=ln(theta_1)-theta_2*e^(-theta_3*t)
//despejando obtenemos que:
//con y=casosTotales, yp=ln(CasosTotales/theta_1)
//ln(-yp)=ln(theta_2)-theta_3*t
//ecuacion la cuel podemos resolver por minimos cuadrados
//ypp=ln(-yp_i)=ln(-ln(CasosTotales(i)/theta_1))

theta_1=13129.3;

for i=1:31
  ypp(i)=log(-log(casosTotales(i)/theta_1));
end
 x = min_squares(dia, ypp, 1,%f,%t);
 p=poly(x,"x","c");
disp(x);

theta_2=%e^x(1);
theta_3=-x(2);

disp(theta_2,"theta_2");
disp(theta_3,"theta_3");

deff("y = g(x)", "y = " + "theta_1*%e^(-theta_2*%e^(-theta_3*x))");

plot2d(dia,casosTotales,-1);
plot2d(dia,g(dia'));
legend("Datos reales", "Modelo ajustado");
xtitle("Casos acumulados vs modelo");
xlabel("Día");
ylabel("Casos acumulados");

