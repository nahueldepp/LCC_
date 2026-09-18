import ListSeq
import Seq
data Trie = E  | N String [Trie] deriving Show

--a)
isPrefix:: String -> String -> Bool
isPrefix [] _ = True
isPrefix _ [] = False 
isPrefix (x:xs) (y:ys) = x == y && isPrefix xs ys

--b)
inv2 :: Trie -> Bool
inv2 E = True 
inv2 (N s ts) = inv2Aux s ts && all inv2 ts

inv2Aux :: String -> [Trie] -> Bool
inv2Aux _ [] = True 
inv2Aux s (t@(N s1 tss):ts) = isPrefix s s1 && inv2Aux s ts


--c)
inv3 :: Trie -> Bool 
inv3 E = True 
inv3 (N s []) = True
inv3 (N s hijos) = all inv3 hijos && inv3Aux hijos

inv3Aux :: [Trie] -> Bool 
inv3Aux [] = True
inv3Aux (h@(N s _):hermanos) = all (\(N x _ ) -> not (isPrefix s x) && not (isPrefix x s))  hermanos && inv3Aux hermanos 


--e)
prefixes:: String -> Trie -> [String]
prefixes _ E = []
prefixes s (N x hijos) 
                        |isPrefix s x = x: prefixesAux s hijos
                        |otherwise = prefixesAux s hijos

prefixesAux :: String -> [Trie] -> [String]
prefixesAux _ [] = []
prefixesAux s (t@(N x hijos):ts) 
                            |isPrefix s x = x:prefixesAux s hijos ++ prefixesAux s ts
                            |otherwise = prefixesAux s hijos ++ prefixesAux s ts

--2)
base :: Float -> (Float, Float) -> (Int, Int, Int, Int)
base v (tempMax,tempMin) 
                            | tempMax <= v = (1,1,1,1)
                            |otherwise = (0,0,0,1)

--(mejorSecuencia, mejorPrefijo, mejorSufijo, longitudDelaSecuencia)
combine:: (Int, Int, Int, Int) -> (Int, Int, Int, Int) -> (Int, Int, Int, Int)
combine  (mi,pi,si,loni) (md,pd,sd,lond) = (max (si+pd) (max mi md),
                                        if pi == loni then loni+pd else pi,--si pi<=ti luego el mejor prefijo izquierdo esta contenido del lado izquierdo
                                        if sd == lond then lond+si else sd,
                                    loni+lond)

coldWavesDays:: [(Float,Float)] -> Float -> Int 
coldWavesDays [] _ = 0
coldWavesDays seq v =   let 
                            val = (0,0,0,0)
                            diasFrios = map (base v) seq
                            (m,p,s,lon) = reduceL combine val diasFrios
                        in m