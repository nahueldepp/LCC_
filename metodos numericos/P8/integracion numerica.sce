// Integración númerica 


//metodo compuesto del trapecio
//donde x es un vector con n subintervalos
function Tn=trapecio_comp(f,a,b,n)
  deff("y=f(x)","y="+f)
  h=(b-a)/n
  if n==1 then
    Tn=(h/2)*(f(x0)+f(x1))
  else
    tn=0
    for j=1:n-1
      x(j)=a+h*j
      tn= tn+ f(x(j))
    end
   tn= tn+ (1/2)*(f(a)+f(b))
    Tn=tn*h
  end
endfunction


//error de la integracion trapezoidal
//donde eps es la cota maxima de f''(c_x)
function err=err_trap(a,b,n,eps)
 h=(b-a)/n
  err=-((h^3)*n*eps)/12
endfunction

//regla simpson
//f se pasa como string
function r=simpson_simple(f,a,b)
  deff("y=f(x)","y="+f)
  h=(b-a)/2
  r=(h/3)*(f(a)+4*f(a+h)+f(b))
endfunction

//regla de simpson compuesta 
//f se pasa como string
//n es un número par 

function s=simpson_compuesta(f,a,b,n)
  deff("y=f(x)","y="+f)
  h=(b-a)/n
  v=f(a)+f(b)
  for j=1:n-1
    x_j=a+h*j
    if 0<>modulo(j,2)//si es impar
      v=v+4*f(x_j)
    else
      v=v+2*f(x_j)
    end
    
  end
  s=(h/3)*v
endfunction

//error del metodo simpson compuesto
//donde eps es la cota maxima de f^(4)(c_x), x0<=c_X<=xn
function err=error_simpson(a,b,n,eps)
  h=(b-a)/n
  err=-h^4*(b-a)*eps/180
endfunction


//integracion En dominio bidimecional 

//G(x)= S(c(x0),d(x0))f(x0,y)dy
//integracion de una funcion de una variable y una variable fija, con metodo del trapecio 
//recibe una función de dos variabes, una variale fija y tres funciones c y d y f
//que delimitan el rango de integracion 
//con c(x0)<=y<=d(x0)

function G=trapecio_var_fija_x(f,c,d,x,n)
  a=c(x)
  b=d(x)
  h=(b-a)/n
  tn=0
    for j=1:n-1
      y_j=a+h*j
      tn= tn+ f(x,y_j)
    end
   tn= tn+ (1/2)*(f(x,a)+f(x,b))
   G=tn*h
endfunction


//I=S(a,b)G(x) 
//donde f,c,d son funciones pasados como strings
function I=trapecio_int_doble(f,a,b,c,d,n)
  deff("y=c(x)","y="+c)
  deff("y=d(x)","y="+d)
  deff("g=f(x,y)","g="+f)
  h=(b-a)/n
   tn=0
    for j=1:n-1
      x_j=a+h*j
      tn= tn+ trapecio_var_fija_x(f,c,d,x_j,n)
    end
   tn= tn+ (1/2)*(trapecio_var_fija_x(f,c,d,a,n)+trapecio_var_fija_x(f,c,d,b,n))
    I=tn*h
endfunction


//simpson compuesta para integración doble con variable fija
//G(x)= S(c(x0),d(x0))f(x0,y)dy
//donde f,c,d son funciones
function s=simpson_var_fija(f,x,c,d,n)
  a=c(x)
  b=d(x)
  h=(b-a)/n
  v=f(x,a)+f(x,b)
  for j=1:n-1
    y_j=a+h*j
    if 0<>modulo(j,2)//si es impar
      v=v+4*f(x,y_j)
    else
      v=v+2*f(x,y_j)
    end
    
  end
  s=(h/3)*v
endfunction

//Metodo compuesto simpson para integracion doble
//donde f,c,d son string 
function I=simpson_compuesta_doble(f,a,b,c,d,n)
  deff("y=c(x)","y="+c)
  deff("y=d(x)","y="+d)
  deff("g=f(x,y)","g="+f)
  h=(b-a)/n
  v=simpson_var_fija(f,a,c,d,n)+simpson_var_fija(f,b,c,d,n)
  for j=1:n-1
    x_j=a+h*j
    if 0<>modulo(j,2)//si es impar
      v=v+4*simpson_var_fija(f,x_j,c,d,n)
    else
      v=v+2*simpson_var_fija(f,x_j,c,d,n)
    end
    
  end
  I=(h/3)*v
endfunction

//Si(b)=S(1,b)f(x)dx
function [Si,err]=trapecio_funcion_inte(b,n)
  if n<1 then
    error("n debe ser mayor a 1")
    abort;
  end
  a=1
  f="(%e^x)*sin(x)"
  Si=trapecio_comp(f,a,b,n)
  eps=1
  err=err_trap(a,b,n,eps)
  
endfunction




