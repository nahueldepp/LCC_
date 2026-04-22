
// borra el contenido de la memoria
// Primera funci´on
function y = P1(x)
y = x.^7 - 7*x.^6 + 21*x.^5 - 35*x.^4 + 35*x.^3 - 21*x.^2 + 7*x - 1;
endfunction
// Segunda funci´on
function y = P2(x)
y = (x - 1).^7;
endfunction
// Evaluaci´on de ambas funciones cerca de uno
x = linspace(1-1e-2,1+1e-2,2001);
y1 = P1(x);
y2 = P2(x);
// Gr´afica de las funciones
plot(x,y1,'b');
plot(x,y2,'r','thickness',2)
legend(["$P1(x)$";"$P2(x)$"]);


function r=misraices(p)
c=coeff(p,0);
b=coeff(p,1);
a=coeff(p,2);
r(1)=(-b + sqrt(b^2-4*a*c))/(2*a);
r(2)=(-b - sqrt(b^2-4*a*c))/(2*a);
endfunction



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
