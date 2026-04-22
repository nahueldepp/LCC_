//Ejercicio 4 practica complementaria 7


// Matriz del método de mínimo cuadrados polinomial
function A = A_mc(x,grado)
    // p = grado+1
    m = length(x)
    A = ones(m,1)
    for j=1:(grado)
        A = [A,(x').^(j)]
    end
    
endfunction




// Coeficienets de aproximacion de minimos cuadrados de orden n aplicando QR
function a = min_squares(x, y, grado,QR,use_inv)
    n = length(x);
    A=A_mc(x,grado)
    if QR==%t then
        a = solve_QR(A,y,use_inv)
    else
        a = solve(A' * A, A' * y, use_inv);
    end
endfunction

// Polinomio obtenido de la aproximacion de minimos cuadrados de orden n
function p = min_squares_poly(x, y, grado,QR,use_inv)
    a = min_squares(x, y, grado,QR,use_inv);
    p = poly(a, "x", "c");
endfunction

//-----------------------------------------------
function x = solve_QR(A, b,use_inv)
    [Q,R] = qr(A,"e");
    
    if use_inv==%T  then
      x=inv(R)*Q'*b
      
    else
      x = solve_upper(R, Q' * b);
    end
endfunction

function x = solve(A, b,use_inv)
n = size(A, 1);
if use_inv==%T  then
    x=inv(A)*b
else  
    [x,a] = elim_gaussPP(A,b);
end

endfunction

function [Q, R] = qr_factor(A)
    [n, m] = size(A);
    if n < m then
        error('qr_factor - La matriz A no cumple con las dimensiones');
        abort;
    end
    R(1,1) = norm(A(:,1), 2);
    Q(:,1) = A(:,1)/R(1,1);
    for k = 2:m
        Q(:,k) = A(:,k);
        for i = 1:k-1
            R(i, k) = (A(:,k)' * Q(:,i));
            Q(:,k) = Q(:,k) - R(i, k) * Q(:,i);
        end
        R(k,k) = norm(Q(:,k),2);
        Q(:,k) = Q(:,k) / R(k,k);
    end
endfunction


//---------------------------------------------------




//-----------------------------------------------
TempMax=[32.9 30.8 26.4 24.2 19.2 16.5 19.3 21 23 26.2]';
TempMin=[19.5 15.5 13.1 9.8 5.7 2.2 5.3 4.7 6 10.5]';
xrango=1:10;

for i=1:10
  TempMed(i)=(TempMax(i)+TempMin(i))/2;
end


//a)



disp("a)");
//usando inv(A'A)
p9=min_squares_poly(xrango,TempMed,9,%f,%t)
disp(p9, "P9(x)=");

p7=min_squares_poly(xrango,TempMed,7,%F,%T)
disp(p7, "P7(x)=");

p5=min_squares_poly(xrango,TempMed,5,%F,%T)
disp(p5, "P5(x)=");

p3=min_squares_poly(xrango,TempMed,3,%F,%T)
disp(p3, "P3(x)=");

rango=0:0.1:10
//plot2d(xrango,TempMax,-1,leg="TempMax")

function plota()
  plot2d(rango,[horner(p3,rango'), horner(p5,rango'), horner(p7,rango'), horner(p9,rango')],[1 2 3 4], leg="p3(x)@p5(x)@p7(x)@p9(x)");
endfunction



//b)

disp("b)");
//usando inv(A'A)
p9qr=min_squares_poly(xrango,TempMed,9,%t,%T)
disp(p9qr, "P9qr(x)=");
p7qr=min_squares_poly(xrango,TempMed,7,%t,%T)
disp(p7qr, "P7qr(x)=");


rango=0:0.1:10
plot2d(xrango,TempMax,-1,leg="TempMax")
plot2d(xrango,TempMin,-1,leg="TempMin")
plot2d(xrango,TempMed,-1,leg="TempMed")
function ejerbplot()

  plot2d(rango,[horner(p9qr,rango'),horner(p9,rango')],[3 6], leg="p9QR(x)@p9(x)");

  //plot2d(rango,[horner(p9qr,rango')],[5], leg="p3QR(x)");
endfunction
//plot2d(rango,[horner(p9,rango')],[5]);
//plot2d(rango,[horner(p9qr2,rango')],[2]);
//plot2d(rango,[ horner(p9,rango')-horner(p9qr,rango')],[2], leg="p3(x)");
