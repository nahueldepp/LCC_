// funciones graficas 


//f1(x) = cos(x) cosh(x) + 1

function y=f1(x)
    y= cosh(x).*cos(x)+1;
    
endfunction


// f2(x) = 2 sin x − x^2

function y=f2(x)
    y=2.*sin(x)-x.^2;
endfunction







//f4(x) = log x − x + 1

function y=f_5(x)
    y=log(x)-x+1;
    
endfunction

function y=prima_abs(x)
    y=abs((sin(x)-x.*cos(x)).*(1./sqrt(x^4-x^2.*(sin(x).^2))));
endfunction

function y=F_3(x)
    y=x-sin(x)+0.5.*sqrt(x);
endfunction

function y=Fp_3(x)
    y=1-cos(x)+1./(4.*sqrt(x));
endfunction

x=linspace(0,2,100);
plot(x,x)
plot(x,0.1+0.6.*cos(2*x))
title("Funcón f1");
xlabel("x");
ylabel("y");
plot(x,x.*0,"r-");
