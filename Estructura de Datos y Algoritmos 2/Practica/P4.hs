import Distribution.License (License(BSD2))
import Control.Monad.Cont (label)

-- ==================================================
--    1)
-- ==================================================    
data Tree a = Leaf | Nodo (Tree a) a (Tree a) deriving Show

mirror :: Tree a -> Tree a
mirror Leaf = Leaf
mirror (Nodo l x r) = Nodo (mirror r) x (mirror l) 

inorder :: Tree a -> [a]
inorder Leaf = []
inorder (Nodo l x r) = inorder l ++ [x] ++ inorder r

mapTree :: Num a => (a->a) -> Tree a -> Tree a
mapTree _ Leaf = Leaf
mapTree f (Nodo l x r) = Nodo (mapTree f l) (f x) (mapTree f r) 

countLeaves :: Tree a -> Int 
countLeaves Leaf = 1
countLeaves (Nodo l _ r) = countLeaves l + countLeaves r
{-a) completo :: a → Int → Tree a, tal que dado un valor x de tipo a y un entero d, crea un ´arbol binario completo
de altura d con el valor x en cada nodo-}

completo :: a -> Int -> Tree a 
completo x d    
                | d == 0 = Leaf
                | otherwise = Nodo t x t
                    where 
                        t = completo x (d-1)

{-b) balanceado::a → Int → Tree a, tal que dado un valor x de tipo a y un entero n, crea un ´arbol binario balanceado
de tama˜no n, con el valor x en cada nodo.
-}
balanceado :: a -> Int -> Tree a
balanceado x n = completo x (floor (logBase 2 (fromIntegral (n+1)) ))

-- ==================================================
--    2) Definir las siguientes funciones sobre ´arboles binarios de b´usqueda (bst):

-- ==================================================  
data BST a = LeafB | NB (BST a) a (BST a) deriving Show

maximumBST :: Ord a => BST a -> a
maximumBST (NB l x LeafB) = x
maximumBST (NB l y r) = maximumBST r

minimumBST :: Ord a => BST a -> a
minimumBST (NB LeafB x r) =  x
minimumBST (NB l x _) = minimumBST l
                        
checkBST :: Ord a => BST a -> Bool 
checkBST t = checkAux t Nothing Nothing

checkAux :: Ord a => BST a -> Maybe a -> Maybe a -> Bool
checkAux LeafB _ _= True 
checkAux (NB l x r) minimo maximo= 
        cumpleMinimo && cumpleMaximo && checkAux l minimo (Just x) && checkAux r (Just x) maximo
        where
            cumpleMinimo = 
                case minimo of 
                    Nothing -> True
                    (Just m) -> m <= x
            cumpleMaximo = 
                case maximo of 
                    Nothing -> True
                    (Just m) -> m > x

{-splitBST :: Ord a ⇒ BST a → a → (BST a, BST a), que dado un ´arbol bst t y un elemento x , devuelva una
tupla con un bst con los elementos de t menores o iguales a x y un bst con los elementos de t mayores a x .-}
splitBST :: Ord a => BST a -> a -> (BST a, BST a)
splitBST LeafB _ = (LeafB, LeafB)
splitBST (NB l y r) x  
                        | y <= x = 
                            let (a,b) = splitBST r x --Nos fijamos la rama derecha ya que puede haber un valor >x
                            in (NB l y a, b)
                        | y > x = 
                            let (a,b) = splitBST l x
                            in (a,NB b y r )
   

{-join :: Ord a ⇒ BST a → BST a → BST a, que una los elementos de dos árboles bst en uno-}
join :: Ord a => BST a -> BST a -> BST a
join LeafB LeafB = LeafB
join LeafB t = t
join t LeafB = t
join (NB l y r) t = join l (join r(insertar y t))
                    

insertar ::Ord a =>  a -> BST a ->BST a
insertar x LeafB = NB LeafB x LeafB
insertar x (NB l y r) 
                        | x <= y = NB (insertar x l) y r
                        |otherwise = NB l y (insertar x r)

eliminar :: Ord a => a -> BST a -> BST a
eliminar x LeafB = LeafB
eliminar x (NB LeafB y LeafB)  | x==y = LeafB
eliminar x (NB l y LeafB)      | x==y = l 
eliminar x (NB LeafB y r)      | x==y = r
eliminar x (NB l y r)          | x==y = let w = minimumBST r 
                                        in NB l w (eliminar w r)
eliminar x (NB l  y r) 
                        | x < y = NB (eliminar x l) y r
                        | x > y = NB l y (eliminar x r)


                                 
-- ===============================================
-- 3) 
-- ===============================================

member :: Ord a => BST a -> a -> Bool
member t a = memberAux t a Nothing

memberAux :: Ord a => BST a -> a -> Maybe a -> Bool
memberAux LeafB x Nothing = False
memberAux LeafB x (Just y) = x == y
memberAux (NB l y r) x v 
                                    | x <= y  = memberAux l x (Just y)
                                    | x>y = memberAux r x v 
                                                                     
-- ===============================================
-- 3) 
-- ===============================================