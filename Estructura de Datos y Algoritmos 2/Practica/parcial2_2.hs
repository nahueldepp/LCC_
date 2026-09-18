import ListSeq
import Seq

(|||):: a -> b -> (a,b)
a ||| b = (a,b) 


--1)
{-Se almacenan los tamaños de los árboles en los nodos y el recorrido inorder del árbol de el
orden de los elementos de la secuencia.
Definir paralelizando cuando sea posible, las siguientes operaciones sobre secuencias-}
data Tree a = E | L a | N Int (Tree a) (Tree a) deriving Show
-- a) concat:: Tree(Tree a) -> Tree a, que concatena una secuencia de secuencias
concat':: Tree(Tree a) -> Tree a
concat' E = E 
concat' (L t) = t 
concat' (N s l r) = 
                    let 
                        (seqI,seqD) = concat' l ||| concat' r
                    in N ((size seqI) + (size seqD)) seqI seqD


size :: Tree a -> Int 
size E = 0
size (L _) = 1
size (N s _ _) = s

--b)subsequence :: Tree a -> Int -> Int -> Tree a, que dada una secuencia s y dos enteros i y j,
-- devuelve la subsecuencia de s que esta entre los indices i y j
-- subsecuence <1,2,3,4,5,6> 2 4 = <3,4,5>

subsequence :: Tree a -> Int -> Int ->Tree a 
subsequence E _ _ = E
subsequence (L x) i j= if i+j == 0 then L x else error "Subsecuencia invalida" 
subsequence t@(N s l r) i j   
                            |i == 0 && j == s = t
                            |j<size l = subsequence l i j 
                            |size l <= i = subsequence r (i - size l) (j - size l) 
                            |i< size l && size l <= j = N (j-i+1) (subsequence l i (size l -1)) (subsequence r 0 (j-size l))
 
                            
{-
Usando las operaciones del TAD Secuencia definir las siguientes funciones
-}

--a) uniquify :: Seq Int -> Seq Int, que elimina los elementos duplicados de una secuencia de enteros
--esta funcion puede definirse con profundiad O((lgn)^2)

uniquify :: [Int] -> [Int]
uniquify [] = []
uniquify s = 
            let 
                s' =uniquify (filterL ((nthL s 0)/=) (dropL s 1))
            in  appendL (takeL s 1) s'