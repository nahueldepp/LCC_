//p7

//ejercicio 1
//aproximacion lineal y cubica mediante lagrange y newton 
function ejer1()
  //lienal
  x=[0,0.2]
  y=[1.0,1.2214]
  //cúbica
  x1=[0,0.2,0.4,0.6]
  y1=[1.0,1.2214,1.4918,1.8221]
  
  //aprox newton 
  
  disp("Aproximación lineal por Newton")
  lineal1=interpol_New(x,y)
  disp(lineal1)
  
  disp("Aproximación cubica por Newton")
  cubica1=interpol_New(x1,y1)
  disp(cubica1)
  
  rango=[-2:0.01:2]
  
  plot(rango,horner(lineal1,rango),"r")
  plot(rango,horner(cubica1,rango),"b")
  plot(rango,exp(rango),"g")
  a=gca();
  a.x_location = "origin";
  a.y_location = "origin";
  h1 = legend("Lineal","Cubico","e^x")
  
  //el error en el extremo derecho en el caso lineal es:
  disp("error en el punto 1/3:")
  disp(interpolation_error(1/3, x,1.2214028))
  //aprox lagrange
  
  disp("Aproximación cúbica por Lagrange")
  lineal=interpollagrange(x,y)
  disp(lineal)
  
  disp("Aproximación lineal por Lagrange")
  cubica=interpollagrange(x1,y1)
  disp(interpollagrange(x1,y1))
  
  
  
  plot(rango,horner(lineal,rango),"r")
  plot(rango,horner(cubica,rango),"b")
  plot(rango,exp(rango),"g")
  a=gca();
  a=gca();
  a.x_location = "origin";
  a.y_location = "origin";
  h1 = legend("Lineal","Cubico","e^x")
  
  
  //el error en el extremo derecho en el caso lineal es:
  disp("error en el extremo derecho en el caso lineal es:")
  disp(interpolation_error(1.2214, x, 1.2214))
endfunction

//*****
//ejercicio 4
function ejer4()

x=[2:0.1:2.5];
y=[0.2239 0.1666 0.1104 0.0555 0.0025 -0.0484]

poli_new=interpol_New(x,y)
disp("Valor para J_0(2.15)")
disp(horner(poli_new,2.15))
disp("su error es")
err=interpolation_error(2.15,x,1)
disp(err)

endfunction
//ejercicio 7
function ejer7()

x=[0 0.15 0.31 0.5 0.6 0.75]
y=[1 1.004 1.31 1.117 1.223 1.422]

disp("Polinomio de grado 1")
[poli1,err]=MinCuad_pol(A_mc(x,1),y)
disp(poli1)
disp("Su error es de: ")
disp(err)

disp("Polinomio de grado 2")
[poli1,err]=MinCuad_pol(A_mc(x,2),y)
disp(poli1)
disp("Su error es de: ")
disp(err)

disp("Polinomio de grado 3")
[poli1,err]=MinCuad_pol(A_mc(x,3),y)
disp(poli1)
disp("Su error es de: ")
disp(err)
endfunction

function ejer8()
  x=[4 4.2 4.5 4.7 5.1 5.5 5.9 6.3 6.8 7.1]
  y=[102.56 113.18 130.11 142.05 167.53 195.14 224.87 256.73 299.5 326.72]
  
  plot2d(x,y,-1,strf= "081")
  
disp("Polinomio de grado 1")
[poli1,err1]=MinCuad_pol(A_mc(x,1),y)
disp(poli1)
disp("Su error es de: ")
disp(err1)

disp("Polinomio de grado 2")
[poli2,err2]=MinCuad_pol(A_mc(x,2),y)
disp(poli2)
disp("Su error es de: ")
disp(err2)

disp("Polinomio de grado 3")
[poli3,err3]=MinCuad_pol(A_mc(x,3),y)
disp(poli3)
disp("Su error es de: ")
disp(err3)
  a=gca();
  
  rango=[0:0.01:10]
plot2d(rango',[horner(poli1,rango'),horner(poli2,rango'),horner(poli3,rango')],[2,3,4],leg="poli1(x)@poli2(x)@poli3(x)")
//plot(rango,horner(poli1,rango),"r")
//plot(rango,horner(poli2,rango),"g")
//plot(rango,horner(poli3,rango),"b")

endfunction


function ejer9_a(n)
  deff("y=f(x)","y=(1./(1+x.^2))")
  
  x=linspace(-5,5,n+1)
  y=zeros(1,n+1)
  for i=1:n+1
    y(i)=f(x(i))
  end
  
  p=interpol_New(x,y)
  
  rango=[-5:0.001:5]
  plot2d(x,y,-1)
  plot2d(rango',[horner(p,rango'), f(rango'),abs(f(rango')-horner(p,rango'))],[1 3 4],leg="pn(x)@f(x)@err")
  plot2d(rango,0*rango)
  
endfunction

function ejer9()
  x=[2,4,6,10,14]
  s=size(x,2)
  for i=1:s
    ejer9_a(i)
  end
endfunction


function ejer10()
  p=inter_cheby("%e^x",4)
  rango=[-4:0.001:4]

  plot2d(rango',[%e.^rango',horner(p,rango'),%e.^rango'-horner(p,rango')],[1,4,2],leg="e^x@p3(x)@eror")
endfunction


function p=ejer11()
  f="cos(%pi*(x+1)/4)"
  p=inter_cheby(f,4)
endfunction
