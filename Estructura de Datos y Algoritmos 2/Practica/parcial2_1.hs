
import ListSeq
import Seq

{-
El TAD Dict es una colección de pares (clave,valor), donde cada clave está asociada a un único valor.
Definimos el TAD Dict con las siguientes operaciones

tad Dict (K:Ordered Set, V:Set) where
    import Bool,Maybe
    empty: Dict K V
    insert: K -> V -> Dict K V -> Dict K V --agrega un par(clave,valor) al diccionario (Si la clave ya existe se sobreescribe el valor antiguo)
    erase: K -> Dict K V -> Dict K V --elimina del diccionario la información de una clave
    isKey: K -> Dict K V -> Bool
    lookup: K -> Dict K V -> Maybe V
    
a) Dar una especificación algebraica para el TAD Dict
k,k':: K ; v,v' :: V ; d,d' :: Dict K V


erase(k empty) = empty
erase(k (insert k' v d)) = if k==k' then d else insert(k' v (erase k d))
insert(k v' (insert k v d)) = insert(k v' d)

isKey(k empty) = False
isKey(k (insert k' v d))= if k==k' then True else isKey( k d)
isKey(k (erase k' v d)) = if k==k' then False else isKey(k d)
lookup(k empty) = Nothing
lookup(k (erase k' d)) = if k==k' then Nothing else lookup(k d)
lookup(k (insert k' v d))= if k==k' then Just v else lookup(k d)

-}


--2)

--se guarda la longitud de la secuenciaen los nodos
--el recorrido inorder del árbol da el orden de los elementos de la secuencia

data Tree a = E | N Int (Tree a) a (Tree a) deriving Show 

(|||):: a -> b -> (a,b)
a ||| b = (a,b) 

filterPrefix :: (a->Bool) -> Tree a -> Tree a 
filterPrefix p E = E 
filterPrefix p t = filterAux p t E 


filterAux :: (a->Bool) -> Tree a -> Tree a -> Tree a
filterAux p E _ = E
filterAux p (N s l x r) prefijo = 
                                let 
                                    nuevoPrefijoI= filterAux p l prefijo
                                    sPrefijoI= size nuevoPrefijoI
                                    nuevoPrefijoD = filterAux p r E 
                                    sPrefijoD = size nuevoPrefijoD
                                in if sPrefijoI == size l && p x then N (sPrefijoI + 1) nuevoPrefijoI x nuevoPrefijoD 
                                else nuevoPrefijoI
                                where
                                    size E = 0
                                    size (N s _ _ _) = s
                            
--3)
{-Usando las funciones Tad secuencia, incluyendo necesariamente a la función scan, definir una función 
longestStreak :: Float -> Seq Float -> Int
que dadis 
*un valor numérico val, que representa una temperatura
*una secuencia de valores neméricos s, que representa la temperatura máxima diaria a lo
largo del tiempo
calcule la racha más larga de días en s donde la temperatura superó los val grados
Definir longestStreak con profundidad en O(lgn), donde n es el largo de la secuencia-}

--(mejorSubsecuencia,mejorPrefijo,mejorSufijo,sumaTotal)
longestStreak :: Float -> [Float] -> Int 
longestStreak val seq =
                        let 
                            seqBase = mapL (base val) seq
                            (pref,tot) = scanL combinar (0,0,0,0) seqBase
                            (msc,_,_,_) = tot
                        in msc

base :: Float -> Float -> (Int, Int, Int, Int)
base val i = if val<i then (1,1,1,1) else (0,0,0,1)

combinar:: (Int,Int,Int,Int)->(Int,Int,Int,Int)->(Int,Int,Int,Int)
combinar (mi,pi,si,ti) (md,pd,sd,td) =
                                    (max (max mi md) (si + pd),
                                    max pi (ti+pd),
                                    max sd (si + td),
                                    ti+td)



-- ==========================================================================

maxPrefixIndex:: [Int] -> [Int]
maxPrefixIndex [] = [] 
maxPrefixIndex [x] = [0]
maxPrefixIndex xs = let
                        (pref,tot) = scanL (funAux xs) 0 (tabulateL id (length xs))
                    in  appendL (dropL pref 1) (singletonL tot )  

funAux::Ord a => [a] -> Int -> Int -> Int 
funAux xs i j = if nthL xs i > nthL xs j then i else j

