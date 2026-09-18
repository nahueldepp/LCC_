module P6 where 


    
(|||) :: a -> b -> (a, b)
a ||| b = (a, b)

-- =============================================================================
-- # Ejercicio 1
-- =============================================================================
data BTree a = Empty | Node Int (BTree a) a (BTree a) deriving Show

nth :: BTree a -> Int -> a
nth Empty _ = error "Índice fuera de rango"
nth (Node t izq x der) n
  | n == size izq = x
  | n < size izq = nth izq n
  | otherwise = nth der (n - size izq - 1)
  where
    size Empty = 0
    size (Node t _ _ _) = t

{-
W(h) = W(h - 1) + O(1) ∈ O(h)
S(h) = S(h - 1) + O(1) ∈ O(h)
-}

cons' :: a -> BTree a -> BTree a
cons' x Empty = Node 1 Empty x Empty
cons' x arbol@(Node t izq y der) = Node (t + 1) Empty x arbol

{-
W(n) ∈ O(1)
S(n) ∈ O(1)
-}

tabulate :: (Int -> a) -> Int -> BTree a
tabulate f 0 = Empty
tabulate f n = build 0 n
                where
                        build _ 0 = Empty
                        build start len = 
                                let 
                                        m = len `div` 2
                                        lenDer = len-m-1
                                in Node len (build start m) (f (start+m)) (build (start+m+1) lenDer)

{-
W(n) = 2*W(floor(n/2)) + O(1) ∈ O(n)
S(n) = S(floor(n/2)) + O(1) ∈ O(lg n)
-}

mapTree :: (a -> b) -> BTree a -> BTree b
mapTree f Empty = Empty
mapTree f (Node t izq x der) =
  let (izq', der') = mapTree f izq ||| mapTree f der
   in Node t izq' (f x) der'

{-
W(n) = 2*W(floor(n/2)) + O(1) ∈ O(n)
S(n) = W(floor(n/2)) + O(1) ∈ O(lg n)
-}

take' :: Int -> BTree a -> BTree a
take' _ Empty = Empty
take' 0 _ = Empty
take' k arbol@(Node t izq x der)
  | k >= t = arbol
  | k <= size izq = take' k izq
  | otherwise = Node k izq x (take' (k - size izq - 1) der)
  where
    size Empty = 0
    size (Node t _ _ _) = t

{-
W(h) = W(h - 1) + O(1) ∈ O(h)
S(h) = S(h - 1) + O(1) ∈ O(h)
-}

drop' :: Int -> BTree a -> BTree a
drop' _ Empty = Empty
drop' 0 arbol = arbol
drop' k arbol@(Node t izq x der)
  | k >= t = Empty
  | k <= size izq = Node (t - k) (drop' k izq) x der
  | otherwise = drop' (k - size izq - 1) der
  where
    size Empty = 0
    size (Node t _ _ _) = t

{-
W(h) = W(h - 1) + O(1) ∈ O(h)
S(h) = S(h - 1) + O(1) ∈ O(h)
-}

mapreduce :: (a -> b) -> (b -> b -> b) -> b -> Tree a -> b
mapreduce m f e E = e
mapreduce m f e (Leaf x) = m x
mapreduce m f e (Join l r) = f (mapreduce m f e l) (mapreduce m f e r)
-- =======================================================
-- 2)
-- =======================================================

data Tree a = E | Leaf a | Join (Tree a) (Tree a) deriving Show

{-
a) Definir una funci´on mcss :: (Num a, Ord a) ⇒ Tree a → a, que calcule la m´axima suma de una subsecuencia
contigua de una secuencia dada, en t´erminos de mapreduce.
Ayuda: Dado un ´arbol t, mcss aplica la funci´on reduce sobre el ´arbol que se obtiene al reemplazar cada
elemento v por la 4-tupla (max (v, 0), max (v, 0), max (v, 0), v).

-}


mapReduce :: (a->b) -> (b->b->b) -> b -> Tree a -> b
mapReduce f g base = mr 
                where   mr E = base
                        mr (Leaf x) = f x
                        mr (Join l r) = let (l', r') = mr l ||| mr r
                                        in  g l' r' 



hojaCuatrupla :: (Num a, Ord a) => a -> (a,a,a,a)
hojaCuatrupla x = (max x 0,max x 0,max x 0,x)


combine :: (Num a, Ord a) => (a,a,a,a) -> (a,a,a,a) -> (a,a,a,a)
combine (ml,pl,sl,tl) (mr,pr,sr,tr) = (mcss, pm, sm, tm)
                                    where 
                                        mcss = max (max (sl + pr) ml) mr
                                        pm = max pl (tl + pr)
                                        sm = max sr (tr + sl)
                                        tm = tl + tr 

mcss:: (Num a, Ord a) => Tree a -> a
mcss t= sumaMaxima 
            where 
                (sumaMaxima, p, s, total) = mapReduce hojaCuatrupla combine (0,0,0,0) t


-- =======================================================
-- 3)
-- =======================================================

{-sufijos:: Tree Int → Tree (Tree Int), tal que dado un ´arbol t construye otro con los sufijos de cada elemento de
t. Por ejemplo,-}

sufijos :: Tree Int -> Tree(Tree Int)
sufijos t = sufijosAux t E 
            where 
                sufijosAux E contexto = E
                sufijosAux (Leaf x) contexto = Leaf contexto
                sufijosAux (Join izq der) contexto = Join (sufijosAux izq (Join der contexto)) (sufijosAux der contexto)

   
conSufijos :: Tree Int -> Tree(Int, Tree Int)
conSufijos t = conSufijosAux t E 
                where 
                    conSufijosAux E _ = E
                    conSufijosAux (Leaf x) sufijo = Leaf (x, sufijo)
                    conSufijosAux  (Join izq der) sufijo = Join (conSufijosAux  izq (Join der sufijo)) (conSufijosAux der sufijo)

reduce :: (a->a->a) -> a -> Tree a -> a
reduce g base E = base
reduce g base (Leaf x) =  x
reduce g base (Join izq der) = let (izq', der') = reduce g base izq ||| reduce g base der
                                in g izq' der'

maxT :: Tree Int -> Int
maxT = reduce max 0 

maxAll :: Tree(Tree Int) -> Int 
maxAll = mapReduce maxT max 0

mapT :: (a->b) -> Tree a -> Tree b 
mapT f E = E 
mapT f (Leaf x) = Leaf (f x)
mapT f (Join izq der) = Join (mapT f izq) (mapT f der)

mejorGanancia :: Tree Int -> Int
mejorGanancia t = maxAll arbolDeGanancias
                where 
                    arbolCompraVentas = conSufijos t
                    arbolDeGanancias= mapT diferencia arbolCompraVentas 
                            
                    

diferencia :: (Int, Tree Int) -> Tree Int
diferencia (x,t) = mapT (\venta -> venta-x) t

-- =======================================================
-- 4)
-- =======================================================

data T a = Em | N (T a) a (T a) deriving Show

altura :: T a -> Int 
altura Em = 0
altura (N l x r) = 1 + max (altura l) (altura r)

--a) 
combinar :: T a -> T a -> T a
combinar Em  t2 = t2
combinar (N l x r) t2 = N t2 x (combinar l r)


--b) 
filterT :: (a -> Bool) -> T a -> T a
filterT p Em = Em 
filterT p (N l x r)  
                    |p x= N (filterT p l) x (filterT p r)
                    | otherwise = combinar (filterT p l) (filterT p r)


quicksortT :: T Int -> T Int 
quicksortT Em = Em 
quicksortT (N l x r) = N (quicksortT(combinar (filterT (x>) l ) (filterT (x>) r))) x (quicksortT(combinar (filterT (x<=) l ) (filterT (x<=) r)))

{-
**Calcular WquicksortT(n) en el peor caso, siendo n la cantidad de nodos del ´arbol que recibe como argumento
la función.

El peor de los casos consistira en un árbol desbalanceado en foma de lista y que el pivote elegido sea el mayor de todos 
los elementos del árbol.
Como el árbol estara desbalanceado, luego, quicksort se llamara de manera recursiva solo hacia una rama, ya que la otra estara vacia.
Tambien, notemos que filter tiene que recorrer todos los nodos del árbol obligatoriamente, luefo Wfilter(n)∈O(n).
Para combinar, sabemos que Wcombinar ∈ O(h), pero como el árbol es una lista, luego h = n y entonces Wcombinar ∈ O(n).
Luego: 
        Wqs(n)  = Wqs(n-1) + Wfilter(n) + Wcombinar(n)
                = Wqs(n-1) + c1*n +c2*n
                = Wqs(n-1) +c3*n ∈ O(n^2)

Suponiendo que quicksortT recibe un árbol balanceado, calcular el trabajo y la profundidad de la función
en el peor caso, el mejor caso y suponiendo que el pivote divide a los datos en proporci´on 1 a 9. ¿Qu´e
cambiaría en el último caso si la proporción es 1 a 99?

Si quicksortT recibe un árbol balanceado: 

*En el peor de los casos, el pivote de la raíz es el mayor de los elementos del árbol.
En este caso, el resto de elementos del árbol se plegarian hacia la izquierda en todos los casos.
Además como WfilterT(n) ∈ O(n), Wcombinar(h=lgn) ∈ O(lgn), luego:

Wqs(n)  = Wqs(n-1) + Wfilter(n) + Wcombinar(n)
                = Wqs(n-1) + c1*n +c2*logn
                <=  Wqs(n-1) + c3*n ∈ O(n^2)
En cuento a su trabajo, como el árbol esta balanceado h = lgn

Sqs(n)  = Sqs(n-1) + Sfilter(d) +Scombinar(d)
        = Sqs(n-1) + Sfilter(lgn) + Scombinar(lgn)
donde sabemos que :
Sfilter(lgn) ∈ O(lgn)
Scombinar(lgn) ∈ O(lgn^2)
Luego: 
        = Sqs(n-1) + c3(lgn^2) ∈ O(nlgn^2)

*En el mejor de los casos el pivote divide el árbol a la mitad

Wqs(n)  = 2Wqs(n/2) + Wfilter(n)+ Wcombinar(n)
        = 2Wqs(n/2) + c3*n ∈ O(nlgn)

En cueto a la profundiad, por lo visto anteriormente: 

Sqs(n)  = Sqs(n/2) + Sfilter(d) +Scombinar(d)
        = Sqs(n/2) + Sfilter(lgn) + Scombinar(lgn)
         = Sqs(n/2) + c3(lgn^2) ∈ O(lgn^3)

*En el caso de un pivot desequilibrado (1 a 9 o 1 a 99)
tenemos que en cuenta al trabajo : 
Wqs(n)  = Wqs(n/10)+Wqs(9*n/10) + Wfilter(n)+ Wcombinar(n)
        = Wqs(n/10)+Wqs(9*n/10) +c3*n

Luego el la profundidad maxima del trabajo es a lo sumo log10/9(n) lo cual asintoticamente ∈ O(lgn)
con lo cual: 
Wqs(n)  = Wqs(n/10)+Wqs(9*n/10) + c3*n ∈ O(nlgn)

En cuento a la profundidad 
Sqs(n)  = Sqs(n*9/10) +  Sfilter(lgn) + Scombinar(lgn)
        =  Sqs(n*9/10) + c3(lgn^2) ∈ O(lgn^3)
-}


-- =======================================================
-- 5)
-- =======================================================

--a)
splitAt' :: BTree a -> Int -> (BTree a, BTree a)
splitAt' Empty _ = (Empty,Empty) 
splitAt' t@(Node s l x r) i
                    | i==s = (t, Empty)
                    | i==0 = (Empty, t)
                    | size l + 1 == i = (Node (s-size r ) l x Empty ,  r)
                    | size l +1 > i  =  let (ll,lr) = splitAt' l i
                                        in  (ll, Node (s-size ll) lr x r)
                    | otherwise     =   let (rl,rr) = splitAt' r (i-size l -1)
                                        in  (Node (s-size rr) l x rl, rr)
                    where 
                        size Empty = 0
                        size (Node tam _ _ _) = tam


--b)

rebalance :: BTree a -> BTree a
rebalance Empty = Empty  
rebalance t@(Node s l x r) =
                        let 
                            m = s `div` 2
                            (lt,rt)=splitAt' t m
                            (Node 1 Empty y Empty,newrt) = splitAt' rt 1
                            (rlt,rrt) = rebalance lt ||| rebalance newrt 
                        in Node (size rlt +size newrt+1) rlt y rrt
                        where
                            size Empty = 0
                            size (Node tam _ _ _) = tam

{-

-}