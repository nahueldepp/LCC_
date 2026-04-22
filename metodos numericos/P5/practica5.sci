//Practica 5

//ejercicio 3
//x^{k+1}=(I-N^-1*A)x^{k}+N^-1*b
//Para Gauss-Seidel N=L+D, para una matriz tridiagonal
//Nij=Aij si i=j o i=j+1
//Nij=0 si i~j o i~j+1

function N=matriz_expl_tridig(A)
  n=size(A,1)
  for i=1:n
    for j=1:n
      if(i==j)||(i==j+1)then
        N(i,j)=A(i,j)
      end
    end
  end
endfunction

