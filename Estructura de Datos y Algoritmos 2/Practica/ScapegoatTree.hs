import Distribution.Simple.Utils (xargs)
{--}

data Scapegoat a = E | N a Int (Scapegoat a) (Scapegoat a) deriving (Eq, Show)


--a) Calcular el tamaño de un arbol (número de nodos)
size ::(Ord a) => Scapegoat a -> Int 
size E = 0
size (N _ i _ _) = i

--b)Dado un valor de tipo Scapegoat a determine si es un árbol binario de busqueda
isBST :: (Ord a) => Scapegoat a -> Bool
isBST E = True
isBST t = isBSTAux t Nothing Nothing

isBSTAux ::(Ord a)=> Scapegoat a -> Maybe a -> Maybe a ->Bool
isBSTAux E _ _ = True
isBSTAux (N x _ l r) minimo maximo = 
    cumpleMinimo && cumpleMaximo &&
    isBSTAux l minimo (Just x) && isBSTAux r (Just x) maximo 
    where
        cumpleMinimo = 
            case minimo of
                Nothing -> True
                Just m -> m < x
        cumpleMaximo = 
            case maximo of
                Nothing -> True
                Just m -> m >= x

--c) Dado un valor de tipo scapegoat a determine si es un scapegoat tree
isScapegoatTree :: (Ord a) => Scapegoat a -> Bool
isScapegoatTree E = True
isScapegoatTree (N x n l r) = isScapegoatTreeAux l n && isScapegoatTreeAux r n

isScapegoatTreeAux ::(Ord a) => Scapegoat a -> Int -> Bool 
isScapegoatTreeAux E _ = True
isScapegoatTreeAux (N x m l r) n = relacionIzq && relacionDer && isScapegoatTreeAux l m && isScapegoatTreeAux r m
            where 
                    relacionIzq = 3*size l <= 2*m
                    relacionDer = 3 * size r <= 2*m 

--d) member: dado un Scapegoat tree y un elemento determine si el elemento esta en el arbol
member :: (Ord a) => a -> Scapegoat a -> Bool
member _ E = False
member x (N a _ l r)    | x<a = member x l
                        | x>a = member x r
                        | x==a = True 

--e) 
--aplana el árbol en una lista inOrder
inOrder :: Scapegoat a -> [a]
inOrder E = []
inOrder (N x _ l r) = inOrder l ++ [x] ++ inOrder r

midList :: [a]-> Int
midList xs = length xs `div` 2

--Dada una lista ordenada, toma el elemento del medio y lo usa como raíz y usa como hijos izquierdo y derecho
--a los resultados de aplicar recursivamente este procedimiento sobre las sublistas que quedan a izquierda y derecha de mid
listToTree :: (Ord a) => [a] -> Scapegoat a
listToTree [] = E
listToTree xs = N x m (listToTree l) (listToTree r) 
    where 
        m = midList xs
        x = xs !! m
        l = take m xs
        (y:r) = drop m xs


rebuild :: (Ord a) => Scapegoat a -> Scapegoat a
rebuild E = E
rebuild t = listToTree (inOrder t)

--f)Que inserte un elemento en un Scapegoat tree, preservando el invariante de balanceo 

insert :: Ord a => a-> Scapegoat a -> Scapegoat a
insert x E = N x 1 E E 
insert x (N y m l r) 
                    | x<=y = 
                        let nuevoL = N y (m+1) (insert x l) r
                        in if 3 * (size l + 1) <= 2 * (m+1)
                            then nuevoL
                            else rebuild nuevoL 
                    | otherwise = 
                        let nuevoD = N y (m+1) l (insert x r)
                        in if 3 * (size r + 1) <= 2 * (m+1)
                            then nuevoD
                            else rebuild nuevoD
                    