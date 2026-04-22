//Doolittle

//j<i
//lij=aij-sum(lik*ukj){1:j-1}/ujj
//i<j
//uij=aij-sum(lik*ukj){1:i-1}

// l11    0    0     u11  u12  u13
// l21  l22    0     0    u22  u23
// l31  l32  l33      0    0    u33


function [L,U] = doolittle(A)
    [n, m] = size(A);
    if n<>m then
        error('doolittle - La matriz A debe ser cuadrada');
        abort;
    end;
    
    L = eye(n, n);
    U = zeros(n, n);
    
    U(1,:) = A(1,:);
    L(:,1) = A(:,1) / U(1,1);
    for k = 2:n
        U(k,k:n) = A(k,k:n) - L(k,1:k-1) * U(1:k-1,k:n);
        for j = k+1:n
            L(j, k) = (A(j, k) - L(j,1:k-1) * U(1:k-1,k)) / U(k,k);
        end
    end
endfunction

