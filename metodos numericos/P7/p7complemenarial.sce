// practica 7 complementaria 


function [p,err] = MinCuad_pol_1(A,b)
    [a,A_amp] = elim_gaussPP((A')*A,(A')*(b'));
    a(1)=0
    a(2)=0
    p = poly(a,"x","c")
    err = norm(A*a-(b'))
endfunction

function ejer1()
  //g(0)=0,g'(0)=0
  
  
  x=[-2.0 -1.6 -1.2 -0.8 -0.4 0 0.4 0.8 1.2 1.6 2.0]
  b=[1.50 0.99 0.61 0.27 0.02 -0.0096 0.02 0.38 0.63 0.98 1.50]
  grado=4
  A = A_mc(x,grado)
 [p,err] = MinCuad_pol_1(A,b)
  pprim=derivat(p)
  disp("El polinomio p y p^(1) son: ")
  disp(p)
  disp(pprim)
  disp("donde p(0)es")
  disp(horner(p,0))
  disp("donde pprim(0)es")
  disp(horner(pprim,0))
  disp(err)
  
  rango=linspace(-2,2,1000)
  plot2d(x',b',-1)
  plot2d(rango,[horner(p,rango'),horner(pprim,rango')],leg="p(x)@p^(1)(x)")
endfunction



function ejer2()
  //f(x)=%e^x
  deff("y=f(x)","y=%e^x")
  x=[-1 -1/3 1/3 1]
  y=[f(-1) f(-1/3) f(1/3) f(1)]
  
  p=interpollagrange(x,y)
  disp("EL polinomio obtenido es:")
  disp(p)
  
  //b)
  disp("")
  disp("b)")
  
  disp("Calculamos p(-0.9)")
  p1=horner(p,-0.9)
  disp(p1)
  disp("Comparamos con el valor dado por scilab:")
  f1=f(-0.9)
  disp(f1)
  disp("error")
  disp(abs(p1-f1))
  
  disp("Calculamos p(0.01)")
  p2=horner(p,0.01)
  disp(horner(p,0.01))
  disp("Comparamos con el valor dado por scilab:")
  f2=f(0.01)
  disp(f2)
  disp("error")
  disp(abs(p2-f2))
  
  //c
  //notemos que f^(n)(x)=f(x)
  disp("")
  disp("c)")
  disp("notemos que f^(n)(x)=f(x)=e^x")
  disp("luego la cota para p(-0.9) es:")
  eps=f1
  s = interpolation_error(p, x, eps)
  disp(abs(horner(s,-0.9)))
  disp("luego la cota para p(0.01) es:")
  disp(abs(horner(s,0.01)))
  
  //d
  //como eps = max |f^(n)(x)|, eps=f(1)
  disp("")
  disp("d)")
  disp("el erorr de p(x) en [-1,1] es de:")
  eps_M=horner(interpolation_error(p, x, f(1)),1)
  disp(eps_M)
  
  
  rango=linspace(-2,2,1000)
  
  plot2d(rango,[horner(p,rango'),f(rango')])
  
  
endfunction

function ejer2_parte2()
  //f(x)=%e^x
  deff("y=f(x)","y=%e^x")
  x=[-1 -1/3 1/3 1]
  n=4
  q=inter_cheby("%e^x",n)
  disp("e)")
  disp("")
  disp("El polinomio de interpolacion usando lagrange y nodos de chebyshev es:")
  disp(q)
  //f
  disp("f)")
  disp("")
  //como f(x) es creciente tomamos eps=f(1)
  s = interpolation_error(q, x,f(1))
  disp("La cota de error es de: ")
  disp(horner(s,1))
  
  
  rango=linspace(-2,2,1000)
  plot2d(rango,[horner(q,rango'),f(rango')-horner(q,rango')],[4,2],leg="q(x)@error_q")
endfunction

function ejer4()
  y_M=[32.9 30.8 26.4 24.2 19.2 16.5 19.3 21 23 26.2]
  y_m=[19.5 15.5 13.1 9.8 5.7 2.2 5.3 4.7 6 10.5]
  
  for i=1:10
    y(i)=(y_m(i)+y_M(i))/2
  end
  x=[1 2 3 4 5 6 7 8 9 10]
  
  
  disp("p_3(x)")
  
  p3 = min_squares_poly(x, y,3,%f,%T)
  disp(p3)
  
  disp("p_5(x)")
  
  p5 = min_squares_poly(x, y,5,%f,%T)
  disp(p5)
  
  disp("p_7(x)")
  p7= min_squares_poly(x, y,7,%f,%t)
  disp(p7)
  
  p9= min_squares_poly(x, y,9,%f,%t)
  disp(p9)
  
  rango=0:0.1:10
  plot2d(x',y_M,-1)
  plot2d(x',y_m,-1)
  plot2d(x',y,-1)
  //plot2d(rango,[horner(p3,rango'),horner(p5,rango'),horner(p7,rango')],[1 2 4],leg="p3(x)@p5(x)@p7(x)")
  
  
  disp("p_3(x)")
  
  pQR3 = min_squares_poly(x, y,3,%t,%t)
  disp(p3)
  
  disp("p_5(x)")
  
  pQR5 = min_squares_poly(x, y,5,%t,%t)
  disp(p5)
  
  disp("p_7(x)")
  pQR7= min_squares_poly(x, y,7,%t,%t)
  disp(p7)
  
  disp("p_9(x)")
  pQR9= min_squares_poly(x, y,9,%t,%t)
  disp(p9)
  
  rango=0:0.1:10
  plot2d(x',y_M,-1)
  plot2d(x',y_m,-1)
  plot2d(rango,[horner(p9,rango'),horner(pQR9,rango')],[ 3 5],leg="p9@pqr")
endfunction

function ejer5()
  x=[0:30]
  y=[35 23 47 59 82 113 143 179 233 269 303 335 371 404 434 446 457 470 481 482 476 465 454 436 424 397 385 359 340 322 303]
  
  theta_1=13129.3
  grado=1
  //g(t_i)~y_i
  //ln(g(t))=ln(theta_1)+h(t)
  //ln(y_i)=ln(theta_1)+h(t_i)
  //h(t)=-theta_2*e^(-theta_3*t)
  //h(t_i)=y'_i=-ln(y_i)+ln(theta_1)
  //a_2=theta2, a_1=-theta_3
  //ln(h(t))=ln(a_2)+a_1*t
  //y''_i=ln(y'_i)=ln(-ln(y_i)+ln(theta_1))
  
  for i=1:31
    ypp(i)=log(-log(y(i))+log(theta_1))
  end
   
  
  plh = min_squares_poly(x, ypp,grado,%f,%f)
  disp(plh)
  theta_3=0.0160426
  theta_2=4.9539151
  rango=[0:0.1:30]
  plot2d(x',y',-1)
  //plot2d(rango,[horner(plh,rango')])
  deff("y=g(x)","y=theta_1*%e.^(-theta_2*%e.^(-theta_3.*x))")
  plot2d(rango,g(rango'))
  
endfunction
