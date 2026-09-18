module P7 where

import ListSeq
import Seq

-- ============================================================
--1)
-- ============================================================

promedios :: [Int] -> [ Float]
promedios s = 
                let 
                    (pref,total) = scanL (+) 0 s
                    sumas = appendL (dropL pref 1) (singletonL total) 
                in tabulateL (\i -> fromIntegral (nthL sumas i)/fromIntegral (i+1)) (lengthL sumas)


mayores :: [Int] -> Int 
mayores s = 
            let 
                (pref,maxTot) = scanL max (nthL s 0) (dropL s 1)
                maximos = appendL pref (singletonL maxTot)
                maximosSig = dropL maximos 1
                seqMayores=tabulateL (\i -> if (nthL maximosSig i)>(nthL maximos i) then 1 else 0) (lengthL maximosSig) 
            in  reduceL (+) 0 seqMayores


-- ============================================================
--3)
-- ============================================================
aguaHist :: [Int] ->Int
aguaHist hist = 
                let 
                    (maximosL,mTot1) = scanL max 0 hist
                    len = lengthL hist
                    histReverse = tabulateL (\i-> nthL hist (len-1-i)) len
                    (maximosRr, mTot2) = scanL max 0 histReverse 
                    alturasAgua= tabulateL (\i -> max 0 (min (nthL maximosL i) (nthL maximosRr (len-1 -i)) - (nthL hist i))) len
                 in reduceL (+) 0 alturasAgua 

-- ============================================================
--4)
-- ============================================================

data Paren = Open | Close deriving Eq  

matchParen :: [Paren] -> Bool 
matchParen s = matchP s == (0,0)

matchP :: [Paren]-> (Int,Int)
matchP s = 
    case showtL s of
        EMPTY -> (0,0)
        ELT x -> if x == Open then (0,1) else (1,0)
        NODE l r -> let 
                        (csi,osi) = matchP l
                        (csd,osd) = matchP r
                        closeSobrantes = csi + max 0 (csd-osi)
                        openSobrantes = osd + max 0 (osi-csd)
                    in (closeSobrantes, openSobrantes) 

matchParen' :: [Paren] -> Bool 
matchParen' s = 
                let 
                    sint = map parenAux s 
                    (pref, tot) = scanL (+) 0 sint
                    prefBool = reduceL (&&) True (map (>=0) pref) 
                in prefBool && tot == 0

parenAux :: Paren -> Int 
parenAux Open = 1
parenAux Close = -1

