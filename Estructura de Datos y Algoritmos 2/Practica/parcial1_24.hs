{-

Ning ́un nodo rojo tiene hijos rojos (padre negro).
•Todos los caminos de la ra ́ız a una hoja tienen el mismo n ́umero de nodos negros (altura negra).
•Ning ́un nodo rojo es el hijo izquierdo de otro nodo (rojo a derecha)

-}
data Color= R | B deriving(Eq,Show)
data AATree a= N Color a (AATree a) (AATree a)|E deriving(Eq,Show)

isBST :: Ord a => AATree a -> Bool
isBST t = isBSTAux Nothing Nothing t

isBSTAux :: Ord a => Maybe a -> Maybe a -> AATree a -> Bool
isBSTAux _ _ E = True
isBSTAux lo hi (N _ x l r) =
     cumpleMin lo x
  && cumpleMax hi x
  && isBSTAux lo (Just x) l
  && isBSTAux (Just x) hi r

cumpleMin :: Ord a => Maybe a -> a -> Bool
cumpleMin Nothing _  = True
cumpleMin (Just m) x = m < x

cumpleMax :: Ord a => Maybe a -> a -> Bool
cumpleMax Nothing _  = True
cumpleMax (Just m) x = x < m


--isAATree::Orda⇒AATreea→Bool, que dado un valor de tipoAATreeadetermine si es un AA tree
isAATree::Ord a=> AATree a -> Bool
isAATree  E = True
isAATree t =  alturaNegra t /= -1 && isBST t && rojoAderecha t

rojoAderecha:: Ord a => AATree a -> Bool 
rojoAderecha E = True
rojoAderecha (N R _ l r) = color l /= R && color r /= R && rojoAderecha l && rojoAderecha r
rojoAderecha (N B _ l r) = color l /= R && rojoAderecha l && rojoAderecha r

color:: Ord a => AATree a -> Color
color E = B
color (N c _ _ _) = c 

alturaNegra:: Ord a => AATree a -> Int
alturaNegra E = 1 
alturaNegra (N c _ l r) 
                        |hl == -1 || hr == -1 || hr /= hl = -1
                        |c == B= 1 + hl
                        |c == R = hl
                    where 
                    hr = alturaNegra r
                    hl = alturaNegra l


--member::Orda⇒a→AATreea→Bool, que dado un AA tree y un elemento determine si el elemento est ́aen el  ́arbol.

--insert::Orda⇒a→AATreea→AATreea, que inserte un elemento en un AA tree.  El nuevo  ́arbol debeverificar todas las invariantes para ser AA tree.

insertAA:: Ord a => a -> AATree a -> AATree a
insertAA x E = N R x E E 
insertAA x t@(N c y l r) 
                            |x<y = pintarNegro(rebalance (N c y (insertAA x l) r))
                            |x>y = pintarNegro(rebalance(N c y l (insertAA x r)))
                            |otherwise = t 

pintarNegro:: AATree a -> AATree a 
pintarNegro E = E 
pintarNegro (N c x l r) = N B x l r

rebalance:: AATree a -> AATree a 
rebalance (N B y (N R x a b) c) = N R x (N B y a b) c
rebalance (N B x a (N R y b (N R z c d))) = N R y (N B x a b) (N B z c d)

