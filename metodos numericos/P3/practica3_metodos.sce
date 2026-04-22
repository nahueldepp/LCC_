function ro=robusta(p)
          c=coeff(p,0);
          b=coeff(p,1);
          a=coeff(p,2);
          if sqrt(b^2-4*a*c)>0 then
                    if b>0 then 
                              x1=(2*c)/(-b-sqrt(b^2-4*a*c));
                              x2=(-b-sqrt(b^2-(4*a*c)))/(2*a);
                    elseif b<0 then
                              x1=(-b+sqrt(b^2-(4*a*c)))/(2*a);
                              x2=(2*c)/(-b+sqrt(b^2-4*a*c));
                    end
          else
                    [x1 x2]=[2 2];
          end
          ro(1)=x1;
          ro(2)=x2;
endfunction

//Graficas funciones 

function y=bisec(f, a, b, epsilon)
    deff("y=fp(x)","y="+f);
    if fp(a)*fp(b)>0 then
        y=-1;
    else
        c=(a+b)/2;
        while (b-c)>epsilon && fp(c)~=0
            
            if fp(b)*fp(c)<0 then 
                a=c;
            else 
                b=c;
            end
            c=(a+b)/2;
        end
        y(1)=a;
        y(2)=b
        y(3)=c;
            
    end
endfunction

//Metodo de Newton 
function y=newton(f,x,dif,iter_max)
    deff("y=F(x)","y="+f);
    deff("yp=Fp(x)","yp=numderivative(F,x)");
    if Fp(x)==0 then
        y=-1;
    else 
        i=0;
        x1=x-(F(x)/Fp(x));
        
       while abs(x1-x)>dif && i<iter_max //abs(x1-F(x1))>dif
        x=x1;
        x1=x-(F(x)/Fp(x)) 
        
        i=i+1;
        end
    end
    disp("iter",i);
    y=x;

endfunction
//ejercicio 8
//f3: R2->R2
//x=[x1,x2]
function y=f3(x)
   y(1)=x(1)^2+x(1)*(x(2)^3)-9;
   y(2)=3*x(1)^2*x(2)-4-x(2)^3
   
endfunction

//Ejercicio 7
//f_7 R2->R2
//x es un vector fila 1*2
function y=f_7(x)
    y(1)=1+x(1)^2-x(2)^2+exp(x(1))*cos(x(2));
    y(2)=2*x(1)*x(2)+%e^x(1)*sin(x(2));
endfunction

//Ejercicio 9 a)
function y=ejer_9(x)
    y(1)=x(1)*exp(x(2))+x(3)-10;
    y(2)=x(1)*exp(2*x(2))+2*x(3)-12;
    y(3)=x(1)*exp(3*x(2))+3*x(3)-15;
endfunction

//metodo de newton multi variable
// x es un vector columna
//f sera una funcion de R2->R2
function y=newton_multi(f,x,epsilon,iter_max,h)
    
    J=numderivative(f,x,h);
    x0=x-(inv(J)*f(x));
    i=1;
    while(norm(x-x0)>epsilon) && i<iter_max
        x=x0;
        J=numderivative(f,x,h);
        x0=x-(inv(J)*f(x));
        
        i=i+1;
     end
     y=x;
endfunction



//se asume funcion monotona 
//epsilon =xn+1 -xn/ xn+1
//Raices positivas?
function y=secante(f,x0,x1,epsilon)
    deff("y=F(x)","y="+f);
    if F(x0)*F(x1)>0 then
        y=-1;
    else 
        x2=x1;
        while F(x2)~=0&&(abs(x2-x0)/x2)>epsilon 
            F1=F(x1);
            F0=F(x0);
            x2=x1-F1*((x1-x0)/(F1-F0));
            x0=x1;
            x1=x2;
        end
    end
    y=x1;
endfunction


//Metodo de Falsa posición 
function y=regula_falsi(f,a,b,epsilon,iter_max)
    deff("y=F(x)","y="+f);
    fa=F(a);
    fb=F(b);
    if fa*fb>0 then error("intervalo invalido");
    else 
        c=b-fb*((b-a)/(fb-fa));
        i=0;
        while (b-c)>epsilon && i<iter_max
            fc=F(c)
            if fc*fb<0 then 
                a=c;
            else 
                b=c;
            end
            c=b-F(b)*((b-a)/(F(b)-F(a)));
            i=i+1;
    end
end
disp("iteraciones: ",i);
    y=c;
endfunction

function y=longitud_de_onda(tol)
    t=5;
    g=9.8;
    d=1;
    h=4;
    l0=2*%pi;
    l1=(t^2*g*tanh(h*(2*%pi)/l0))*(1/(2*%pi));
    i=0;
    lambda=0.7 // valor del sup de g
    n=log((tol*(1-lambda))/abs(l0-l1)).*(1./log(lambda))// iteraciones despejando resultado de teorema de convergencia con existencia de sup g'(x)<1
    while i<n
        l0=l1;
        l1=(t^2*g*tanh(h*(2*%pi)/l0))*(1/(2*%pi));
        i=i+1;
    end
    y=l1;
    disp("iteraciones ",i);
endfunction


//ejercicio 2 practica complementaria 
//x=tan(x)

function y=tan_pf(tol)
    x0=0.2;
    x1=acos(sin(x0)./x0);
    i=0;
    lambda=0.555
    n=log((tol*(1-lambda))/abs(x0-x1)).*(1./log(lambda))
    while i<n
        x0=x1;
        x1=acos(sin(x0)./x0);
        i=i+1;
    end
    y=x1;
     disp("iteraciones ",i);
endfunction


// practica complementaria 3)

//lambda es sup abs(g'(x)) en [a,b]
function y=punto_fijo(f,tol,x0,lambda)
    deff("a=F(x)","a="+f);
    x1=F(x0);
    i=0;
    n=ceil(log((tol*(1-lambda)/abs(x0-x1))).*(1./log(lambda)))
    while i<n
        x0=x1;
        x1=F(x0);
        i=i+1;
    end
    y=x1;
     disp("iteraciones ",i);
endfunction


//calculo de inverse mediante newton

function y=inv_newton(c,x0,epsi,iter_max)
    x1=x0+2*(1-c*x0);
    i=0;
    while abs(x1-x0)>epsi && i<iter_max
        x0=x1;
        x1=2*x0-c*(x0^2);
        i=i+1;
    end
    y=x1;
    disp("iter",i);
endfunction
