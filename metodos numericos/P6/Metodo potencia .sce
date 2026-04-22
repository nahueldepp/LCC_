
//Metodo de la potencia 
function [valor,zn]=mpotencia(A,z0,eps,max_iter)
  valor=0;
  iter=1;
  w=A*z0;
  zn=w/norm(w,%inf);
  [m,j]=max(abs(w));//devuelve el valor maximo y su indice
  valor=w(j)/z0(j);
  zn=w/valor;
  
  while (iter<=max_iter)& (norm(z0-zn,%inf)>eps)//cualquier norma es valida
    z0=zn;
    w=A*z0;
    zn=w/norm(w,%inf);
    [m,j]=max(abs(w)); 
    valor=w(j)/z0(j);
    zn=w/valor;
    iter=iter+1;
  end
  disp("iteraciones",iter);
endfunction

L=[12 1 3 4;1 -3 1 5;3 1 6 -2;4 5 -2 -1] 

//Ejercicio 3

function [P]=matriz_eps(eps)
  P=[1 -1 0;
    -2 4 -2;
     0 -1 1+eps]
  p=poly(P,"x");
  lamda=spec(P);
  disp("EL polinomio es p")
  disp(p);
  disp("Las raices son");
  disp(roots(p))
  disp("sus autovalores son:")
  disp(spec(P))
endfunction

//ejercicio 5

function y=err_autovectores(M)
  
  v1=mpotencia(M,[1 0 0 0]',0.00001,100);
  disp("Valor aproximado")
  disp(v1)
  
  disp("Mayor auto valor")
  v2=norm(M,1);
  disp(v2)
  
  disp("Error ")
  y=abs(v1-v2)
  
endfunction

//ejercicio parcial

function ejer_parcial()
A=[9 1 -2 1;
  0 8 1 1;
  -1 0 7 0;
  1 0 0 1]
  z0=[50 21 35 99]'
  z1=[0 1 1 0]'
  [valor0,zn0]=mpotencia(A,z0,10**-5,100);
  [valor1,zn1]=mpotencia(A,z1,10**-5,100);
  
  disp("Primera estimacion")
  disp(valor0,zn0);
  disp("Segunda estimacion")
  disp(valor1,zn1);

  
  disp("Diferencia auotovalor")
  disp(abs(valor1-valor0))
  disp("diferencia autovector")
  disp(norm(zn1-zn0,2))
endfunction
