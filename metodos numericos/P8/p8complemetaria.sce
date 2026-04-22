//practica 8 complementria 

function ejer1()
  //ln(2)
  f="1/x"
  a=1
  b=2
  n=2
  Tn=trapecio_comp(f,a,b,n)
  disp(Tn)
  
  //f(x)=1/x
  //f'(x)=-x^-2
  //f''(x)=2*x^-3
  
  deff("y=g(x)","y=2.*x.^-3")
  rango=[1:0.1:2]
  plot2d(rango,g(rango'))
  //luego max|g(x)|=2=eps
  eps=2
  //para n=390 se cumple la condicion 
  n=390
  err=err_trap(a,b,n,eps)
  disp(err<10**-6)
  
endfunction


function ejer3()
  disp("algunos valores son:")
  n=100
  for i=2:6
    [Si,err]=trapecio_funcion_inte(i,n)
    disp("Si(b)=")
    disp(Si)
    disp("err=")
    disp(err)
    
  end
endfunction

function ejer2()
  
  //a)
  //n>15
  //b)
  
  //f(x)=%e^x*sin(x)
  disp("La aproximacion nos da: ")
  s=simpson_compuesta("%e^x*sin(x)",1,3,16)
  disp(s)
endfunction

