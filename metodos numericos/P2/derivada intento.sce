


// derivada con numderivate
function d=Df(f,x,h,n)
     deff("d=D0f(x)","d="+f);
     
     
      for i=1:n-1
         deff("d=D"+string(i)+"f(x)","d=numderivative(D"+string(i-1)+"f,x,h)");
         
         
      end
         deff("d=Dnf(x)","d=numderivative("+"D"+string(n-1)+"f,x,h)");
      d=Dnf(x);
      
      
      
endfunction
//polinomios de taylor
//calcula el polinomio de taylor  de grado n de la funcion f en un punto x0
//f: funcion 
//n: orden del polinomio
//x:valor a evaluar
//a: centro  
function t=taylor(f,n,x,a)
    deff("t=F(x)","t="+f)
    h=0.00001;

    p0=F(a);
    if n==0 then t=p0;
    else 
        for i=1:n
            p0= p0+(Df(f,a,h,i)*(x-a)^i/factorial(i));
        
     end
  end
    t=p0;
endfunction

function t=taylor2(f,n,x,h)
    deff("t=F(x)","t="+f);

    t=F(0);
        for i=(1:n)
            t= t+(Df(f,0,h,i)/factorial(i))*(x**i);
        
     end
 

endfunction
// funcion f es la ley de la función dada por un string, usa como 
// variable x
// v es el valor donde se evaluará la derivada
// n es el orden de derivación
// h es el paso de derivación

function valor = derivada(f,v,n,h)
    deff("y=DF0(x)","y="+f);
    if n==0 then valor = DF0(v);
    else
        for i=1:(n-1)
        deff("y=DF"+string(i)+"(x)","y=(DF"+string(i-1)+"(x+"+string(h)+")-DF"+string(i-1)+"(x))/"+string(h));
        end
        deff("y=DFn(x)","y=(DF"+string(n-1)+"(x+"+string(h)+")-DF"+string(n-1)+"(x))/"+string(h));
        valor = DFn(v);
    end
endfunction



