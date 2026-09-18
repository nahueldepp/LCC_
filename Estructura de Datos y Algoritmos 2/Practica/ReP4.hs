-- =======================================================
-- 1)
-- =======================================================

data Tree a = Leaf | Node (Tree a) a (Tree a) deriving Show

{-completo :: a → Int → Tree a, tal que dado un valor x de tipo a y un entero d, crea un ´arbol binario completo
de altura d con el valor x en cada nodo.-}


completo :: a -> Int -> Tree a 
completo x d 
                | d == 0 = Leaf
                | otherwise = Node (completo x (d-1)) x (completo x (d-1)) 


{-balanceado::a → Int → Tree a, tal que dado un valor x de tipo a y un entero n, crea un ´arbol binario balanceado
de tama˜no n, con el valor x en cada nodo-}

balanceado :: a -> Int -> Tree a 
balanceado x 0 = Leaf
balanceado x n = completo x (floor (logBase 2 (fromIntegral (n+1))))