data Color = R|B deriving (Eq,Show)
data AATree a = E |N Color a (AATree a) (AATree a) deriving (Eq,Show)

--a)dado un valor de tipoAATreeadetermine si es un  ́arbol binario deb ́usqueda
isBST :: (Ord a) => AATree a -> Bool
isBST E = True
isBST t = isBSTAux t Nothing Nothing 

isBSTAux :: (Ord a) => AATree a -> Maybe a -> Maybe a -> Bool
isBSTAux E _ _ = True
isBSTAux (N _ x l r) minimo maximo=
     cumpleMinimo && cumpleMaximo &&
     isBSTAux l minimo (Just x) && isBSTAux r (Just x) maximo 
     where 
        cumpleMinimo = 
            case minimo of 
                Nothing -> True
                (Just m) -> m <= x
        cumpleMaximo = 
            case maximo of
                Nothing -> True
                (Just m)-> m>x

--b)dado un valor de tipoAATree a determine si es un AA tree.
isAATree :: (Ord a) => AATree a  -> Bool
isAATree E = True 
isAATree t = isBST t &&  color t == B  && rojoDerecha t
    where   
        raizNegra (N c x l r) = 



color :: AATree a -> Color 
color E = B
color (N c _ _ _) = c

