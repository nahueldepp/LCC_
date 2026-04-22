//practica 8

//ejer 1

function ejer1()
  deff("y=f1(x)","y=log(x)")
  deff("y=f2(x)","y=x.^(1/3)")
  deff("y=f3(x)","y=sin(x)^2")
  
  disp("La aproximacion por el metodo del trapacio para log(x) es:")
  tn1=regla_trap_comp("log(x)",1,2,20)
  disp(tn1)
  disp("su cota de error es:")
  //eps=f''(2)=-1/4
  errT1=err_trap(1,2,20,-1/4)
  disp(errT1)
  disp("La aproximacion por el metodo simpson para log(x) es:")
  s1=simpson_compuesta("log(x)",1,2,20)
  disp(s1)
  disp("su cota de error es:")
  //eps=f''''(2)=-0.375
  errs1=error_simpson(0,0.1,20,-0.375)
  disp(errs1)
  //f2
  disp("La aproximacion por el metodo del trapacio para x.^(1/3) es:")
  tn2=regla_trap_comp("x.^(1/3)",0,0.1,20)
  disp(tn2)
  disp("La aproximacion por el metodo simpson para x.^(1/3) es:")
  s2=simpson_compuesta("x.^(1/3)",0,0.1,20)
  disp(s2)
  
  //f3
  disp("La aproximacion por el metodo del trapacio para sin(x)^2 es:")
  tn3=regla_trap_comp("sin(x)^2",0,%pi/3,20)
  disp(tn3)
  disp("La aproximacion por el metodo simpson para sin(x)^2 es:")
  s3=simpson_compuesta("sin(x)^2",0,%pi/3,20)
  disp(s3)
endfunction


function ejer2()
  
  //e)
  disp("e)")
  disp("El resultado con el metodo del trapecio compuesto para x*sin(x) es:")
  re=trapecio_comp("x*sin(x)",0,2*%pi,8)
  disp(re)
  disp("El resultado con comandos de scilab es:")
  deff("z=f(x)","z=x*sin(x)")
  re=intg(0,2*%pi,f)
  disp(re)
  
  
  //f)
  disp("f)")
  disp("El resultado con el metodo del trapecio compuesto para (x^2)*%e^x es:")
  re=trapecio_comp("(x^2)*%e^x",0,1,8)
  disp(re)
  disp("El resultado con comandos de scilab es:")
  deff("z=f(x)","z=(x^2)*%e^x")
  re=intg(0,1,f)
  disp(re)
endfunction

//ejer 4

function ejer4()
  
  //a)
  f="(x+1)^(-1)"
  disp("Con el metodo del trapecio")
  Tn1=trapecio_comp(f,0,1.5,10)
  disp(Tn1)
  disp("---------------------------")
  //b
   disp("Con el metodo simpson")
  Tn2=simpson_compuesta(f,0,1.5,10)
  disp(Tn2)
  disp("---------------------------")
  //c
  I=0.9262907
  disp("el Error con el metodo del trapecio es:")
  disp(abs(I-Tn1))
  disp("el Error con el metodo simpson es:")
  disp(abs(I-Tn2))
  
endfunction
function ejer5()
   //S(0-2)S(0-1)sin(x+y)dydx
   
   f="sin(x+y)"
   c="0"
   d="1"
   n=2
   I=trapecio_int_doble(f,0,2,c,d,n)
   disp(I)
endfunction

function ejer6()
  //calculo del area de un circulo unitario por integral doble
  //0<=x<=2, -sqrt(2x-x^2)<=y<=sqrt(2x-x^2)
  
  a=0
  b=2
  c="-sqrt(2*x-x^2)"
  d="sqrt(2*x-x^2)"
  n=100
  f="1"
  disp("calculo por metodo del trapecio: ")
  I=trapecio_int_doble(f,a,b,c,d,n)
  disp(I)
  
  disp("calculo por metodo simpson: ")
  I=simpson_compuesta_doble(f,a,b,c,d,n)
  
  disp(I)
endfunction
