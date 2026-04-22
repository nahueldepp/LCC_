//NORMAS

//norma euclídea
//se define para un vector x en R^n

function y=nor_euclidea(x)
  n=size(x,1)
  y=0;
  for i=1:n
    y=y+x(i)**2;
  end
  y=sqrt(y);
  
endfunction

//max(1<i<n)|xi|
function y=nor_infinito(x)
  n=size(x,1);
  y=abs(x(1));
  for i=1:n
    if abs(x(i))>=abs(y) then
      y=x(i);
    end
  end
endfunction


function y=norma_p(x,p)
  n=size(x,1);
  y=0;
  for i=1:n;
    y=y+abs(x(i))**p
  end
  y=(y)^(1/p);
endfunction

