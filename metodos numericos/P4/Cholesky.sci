//Factorización de cholesky

function [U]=cholesky(A,eps)
  n=size(A,1);
  U=zeros(n,n);
  for k=1:n
    if k<>1 then
      t=A(k,k)-U(1:(k-1),k)'*U(1:(k-1),k);
    else
      t=A(k,k);
    end
      
    if t<=eps then
      printf("Matriz no definida positiva.\n");
      return
    end
    U(k,k)=sqrt(t);
    for j=(k+1):n
      if k<>1 then
        U(k,j)=(A(k,j)-U(1:(k-1),k)'*U(1:(k-1),j))/U (k,k);
      else
        U(k,j)=A(k,j)/U(k,k)
      end
      
    end
  end

endfunction

function [x1,x2]=resolChole(A,b)
  U=cholesky(A,0.0001);
  
  c=inferior(U',b);
  x1=superior(U,c);
  
  p=inv(U')*b;
  x2=inv(U)*p;

disp(x2)
endfunction


function Ai=AX(A)
  n=size(A,1)
  U=cholesky(A,0.0001);
 Uin=inv(U)
  Ai=Uin*Uin'
endfunction

