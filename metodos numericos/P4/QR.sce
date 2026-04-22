//fACTORIZACION QR

function [Q, R] = qr_factor(A)
    [n, m] = size(A);
    if n < m then
        error('qr_factor - La matriz A no cumple con las dimensiones');
        abort;
    end
    R(1,1) = norm(A(:,1), 2);
    Q(:,1) = A(:,1) / R(1,1);
    for k = 2:m
        Q(:,k) = A(:,k);
        for i = 1:k-1
            R(i, k) = A(:,k)' * Q(:,i)
            Q(:,k) = Q(:,k) - R(i, k) * Q(:,i);
        end
        R(k,k) = norm(Q(:,k), 2);
        Q(:,k) = Q(:,k) / R(k,k);
    end
endfunction

function [Q,R]= mi_QR(A)
  [m, n] = size(A);
    if m < n then
        error('qr_factor - La matriz A no cumple con las dimensiones');
        abort;
    end
    
   
   for j = 1:n
        v = A(:, j);
        for i = 1:j-1
            R(i, j) = Q(:, i)' * A(:, j);
            v = v - R(i, j) * Q(:, i);
        end
        R(j, j) = norm(v, 2);
        Q(:, j) = v / R(j, j);
    end
endfunction

function x = solve_upper(A, b)
    n = size(A, 1);
    x(n) = b(n) / A(n, n)
    for k = n-1:-1:1
        x(k) = (b(k) - A(k, k+1:n) * x(k+1:n)) / A(k, k);
    end
endfunction




function x = solve(A, b,use_inv)
    n = size(A, 1);
    if use_inv then
        [x,a] = elim_gaussPP(A,b);
        x=inv(A)*b
    else  
        [x,a] = elim_gaussPP(A,b);
    end
    
endfunction

function x = solve_QR(A, b,use_inv)
    [Q, R] = qr(A,"e");
    
    if use_inv then
      x=inv(R)*Q'*b
    else
      x = solve_upper(R, Q' * b);
    end

   //; x = solve_upper(R, Q' * b);
endfunction

