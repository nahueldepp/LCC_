function l=alghorner(a,x0)
          n=length(a)
          b=a(n)
          c=b
          for i=(n):-1:1
               c=b+c*x0
               b=a(i)+b*x0
               
          end
          l(1)=b
          l(2)=c
endfunction
