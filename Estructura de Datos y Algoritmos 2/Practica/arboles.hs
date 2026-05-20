import Data.Bitraversable (Bitraversable(bitraverse))
import Control.Monad.Cont (label)
import Language.Haskell.TH (Body)
import GHC.Int (neInt32)
import Distribution.Simple.Utils (xargs)
import GHC.RTS.Flags (DebugFlags(hpc))

data Bin a = Leaf | Nodo (Bin a) a (Bin a) deriving Show

--Recorrido in order de un arbol
inOrder :: Bin a -> [a]
inOrder Leaf = []
inOrder (Nodo l a r)= inOrder l ++ [a]++  inOrder r  

ordenada ::(Ord a) => [a] -> Bool
ordenada [] = True
ordenada [_] = True
ordenada (x:y:xs) = x<=y && ordenada (y:xs)

--Minimo valor en un bst
minimo :: Bin a -> a
minimo (Nodo Leaf a r) = a
minimo (Nodo l a r) = minimo l

--Maximo valor en un bst
maximo :: Bin a -> a
maximo (Nodo l a Leaf) = a
maximo (Nodo l a r) = maximo r

--Checkea si un arbol es BST
checkBST ::(Ord a) => Bin a -> Bool
checkBST  t = ordenada (inOrder t) 

--Inserto un elemento 
insertar :: (Ord a) => Bin a -> a -> Bin a
insertar Leaf a = Nodo Leaf a Leaf
insertar (Nodo l b r) a |a<=b = Nodo (insertar l a) b r
                        |otherwise = Nodo l b (insertar r a)

borrar :: (Ord a) => a -> Bin a ->Bin a
borrar _ Leaf = Leaf
borrar z (Nodo l a r)   |z<=a = Nodo (borrar z l) a r
borrar z (Nodo l a r)   |z>a = Nodo l a (borrar z r)
borrar z (Nodo Leaf a Leaf) |z==a = Leaf
borrar z (Nodo Leaf a r) |z==a = r
borrar z (Nodo l a Leaf) |z==a = l
borrar z (Nodo l a r) |z==a = let y = minimo r 
                                in Nodo l y (borrar y r)


--red black trees
data Color =  R|B deriving (Eq, Show)
data RBT a = E | T Color (RBT a) a (RBT a) deriving Show 

isEmptyRBT :: RBT a -> Bool
isEmptyRBT E = True
isEmptyRBT _ = False 

color :: RBT a -> Color
color E = B
color (T c _ _ _) = c

isRed :: RBT a -> Bool 
isRed (T R _ _ _) = True 
isRed _ = False

isBlack :: RBT a -> Bool  
isBlack t =  color t == B


noRedRed :: RBT a -> Bool
noRedRed E = True 
noRedRed (T c l _ r) = not (c == R && (isRed l || isRed r)) && noRedRed l && noRedRed r

blackHeight :: RBT a -> Int 
blackHeight E = 1
blackHeight (T c l _ r) 
                        | hl == -1 = -1
                        | hr == -1 = -1
                        | hl /= hr = -1
                        | c == B = hl + 1
                        | otherwise = hl 
                        where 
                            hr = blackHeight r 
                            hl = blackHeight l

sameBlackHeight :: RBT a -> Bool
sameBlackHeight t = blackHeight t /= -1 



isBST :: (Ord a) => RBT a -> Bool
isBST E = True
isBST t = isBSTAux t Nothing Nothing

isBSTAux ::(Ord a)=> RBT a -> Maybe a -> Maybe a ->Bool
isBSTAux E _ _ = True
isBSTAux (T _ l x r) minimo maximo = 
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

isRBT :: Ord a => RBT a -> Bool
isRBT t = isBST t && noRedRed t && sameBlackHeight t 



insertRBT :: Ord a => a -> RBT a -> RBT a
insertRBT x t = makeBlack (ins x t)
                where 
                    makeBlack E = E
                    makeBlack (T _ l x r) = T B l x r 


ins :: Ord a => a -> RBT a -> RBT a
ins x E = T R E x E 
ins x (T c l y r) 
                    | x < y = lbalance c (ins x l) y r 
                    | x > y  = rbalance c l y (ins x r)
                    | otherwise = T c l y r 

balance :: Color -> RBT a -> a -> RBT a  -> RBT a 
balance  B (T R (T R a y b) z c) x d = T R (T B a y b) z (T B c x d)
balance  B (T R a y (T R b z c)) x d = T R (T B a y b) z (T B c x d)
balance  B a y (T R b z (T R c x d)) = T R (T B a y b) z (T B c x d)
balance  B a y (T R (T R b z c) x d) = T R (T B a y b) z (T B c x d)
balance  c l x r = T c l x r 

lbalance :: Color -> RBT a -> a -> RBT a -> RBT a
lbalance  B (T R (T R a y b) z c) x d = T R (T B a y b) z (T B c x d)
lbalance  B (T R a y (T R b z c)) x d = T R (T B a y b) z (T B c x d)
lbalance  c l x r = T c l x r 

rbalance :: Color -> RBT a -> a -> RBT a -> RBT a
rbalance  B a y (T R b z (T R c x d)) = T R (T B a y b) z (T B c x d)
rbalance  B a y (T R (T R b z c) x d) = T R (T B a y b) z (T B c x d)
rbalance  c l x r = T c l x r 

-- arbol 2-3-4

data T234 a = Leaf234
    | Node2  a (T234 a) (T234 a)
    | Node3  a a (T234 a) (T234 a) (T234 a)
    | Node4  a a a (T234 a) (T234 a) (T234 a) (T234 a)


(|||) :: a -> a -> (a,a)
x ||| y = (x,y)

convertirRBTa234 :: RBT a -> T234 a 
convertirRBTa234 E = Leaf234
convertirRBTa234 (T B (T R a x b) y (T R c z d)) = 
    let (n1, n2) = convertirRBTa234 a ||| convertirRBTa234 b
        (n3, n4) = convertirRBTa234 c ||| convertirRBTa234 d
    in  Node4 x y z n1 n2 n3 n4 
convertirRBTa234 (T B (T R a x b) y c) =
    let (n1, n2) = convertirRBTa234 a ||| convertirRBTa234 b
        n3       = convertirRBTa234 c 
    in Node3 x y n1 n2 n3 
convertirRBTa234 (T B a x (T R b y c)) =
    let (n1, n2) = convertirRBTa234 a ||| convertirRBTa234 b
        n3       = convertirRBTa234 c 
    in Node3 x y n1 n2 n3 
convertirRBTa234 (T B a x b) =
    let (n1, n2) = convertirRBTa234 a ||| convertirRBTa234 b
    in Node2 x n1 n2 
 
-- lefist heaps 

type Rank = Int 
data Heap a = LeafH | N Rank a (Heap a) (Heap a)

rank :: Heap a -> Rank
rank LeafH = 0
rank (N ran _ _ _) = ran 

merge :: (Ord a) => Heap a -> Heap a -> Heap a 
merge LeafH h = h
merge h LeafH = h
merge h1@(N _ x l1 r1) h2@(N _ y l2 r2) = 
    if x <= y then makeH x l1 (merge r1 h2)
    else    makeH y l2 (merge r2 h1) 

makeH :: (Ord a) => a -> Heap a -> Heap a -> Heap a
makeH  x a b = 
    if rank a >= rank b then N (rank b + 1) x a b
    else N (rank a + 1) x b a


insert :: (Ord a) => a -> Heap a -> Heap a
insert x  = merge (N 1 x LeafH  LeafH)  

findMin :: Heap a -> a
findMin (N _ x a b) = x

deleteMin :: (Ord a) => Heap a -> Heap a
deleteMin LeafH = LeafH
deleteMin (N _ x a b) = merge a b


-- =================
--  pairing heap
-- =================

data PHeaps a = LeafPH | Root a [PHeaps a]

isPHeap :: (Ord a) => PHeaps a -> Bool 
isPHeap LeafPH = True
isPHeap (Root x pheaps) = all (isMin x) pheaps && all isPHeap pheaps 

isMin :: (Ord a) => a -> PHeaps a -> Bool 
isMin _ LeafPH = True 
isMin x (Root y _) = x<=y 

mergePH :: (Ord a) => PHeaps a -> PHeaps a -> PHeaps a
mergePH LeafPH ph = ph 
mergePH ph LeafPH = ph 
mergePH h1@(Root x hijosx) h2@(Root y hijosy) = 
    if x <= y then Root x (h2:hijosx) 
    else Root y (h1:hijosy)

insertPH :: (Ord a) => PHeaps a -> a -> PHeaps a 
insertPH hp x = mergePH (Root x [LeafPH]) hp

concatHeaps :: (Ord a) => [PHeaps a] -> PHeaps a
concatHeaps heaps = foldr mergePH LeafPH heaps 


delMin :: (Ord a) => PHeaps a -> Maybe (a, PHeaps a)
delMin LeafPH = Nothing
delMin (Root x hijos) = Just (x, concatHeaps hijos)