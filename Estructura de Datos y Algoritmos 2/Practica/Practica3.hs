import Data.Sequence (Seq(Empty))
import Distribution.Simple.Utils (xargs)
import Data.Char
-- ##################################################
-- 1)Definir un tipo Color en este modelo y una funci´on mezclar que permita obtener el promedio componente a
--componente entre dos colores
-- ##################################################

data Color = RGB Int Int Int  deriving Show

mezclar :: Color -> Color -> Color
mezclar (RGB r1 g1 b1) (RGB r2 g2 b2) =  RGB ((r1+r2)`div`2)  ((g1+g2)`div`2) ((b1+b2)`div`2)



-- ##################################################
--  Supongamos que una L´ınea es una secuencia de caracteres c1, c2, . . . , cn
--junto con una posici´on p, siendo <= p <= n,
-- ##################################################

data Linea = Linea [Char] Int deriving Show
--Devuelve una linea vacia
vacia :: Linea
vacia = Linea [] 0

--la operación moverDer el cursor una posici´on a la derecha (siempre que ello sea posible)
moverDer :: Linea -> Linea
moverDer (Linea lista p)    |null lista  = Linea lista 0
                            |p < length lista = Linea lista (p+1)
                            |otherwise = Linea lista p


-- la operaci´on moverIzq mueve el cursor una posici´on a la izquierda (siempre que ello sea posible)
moverIzq :: Linea -> Linea
moverIzq (Linea lista p)    |null lista  = Linea lista 0
                            |p > 0 = Linea lista (p-1)
                            |otherwise = Linea lista p


-- mueve el cursor al inicio d e la linea
moverIni :: Linea -> Linea 
moverIni (Linea xs p) = Linea xs 0; 

-- mueve el cursor al final de la linea 
moverFin :: Linea -> Linea 
moverFin (Linea lc p) = Linea lc (length lc)

-- Agrega un caracter en el lugar deonde se encontraba el cursor, dejando al caracter insertadi a su izquierda
insertar :: Char -> Linea -> Linea 
insertar c (Linea xs p) = Linea (take p xs ++ (c: drop p xs)) (p+1)


-- Elimina el caracter que se encuetra a la izquierda del cursor
borrar :: Linea -> Linea 
borrar (Linea xs p) 
                    |p>0 = Linea (take (p-1) xs ++ drop p xs) (p-1)
                    |otherwise = Linea xs p


-- #############################################################
-- 3) 
-- #############################################################

data CList a  = EmptyCL | CUnit a | Consnoc a (CList a) a deriving Show

--a)

headCL :: CList a -> a
headCL (CUnit x) = x 
headCL  (Consnoc x l y) = x 

tailCL :: CList a -> CList a
tailCL (CUnit x) = EmptyCL
tailCL  (Consnoc x xs y ) = addEnd xs y

addEnd :: CList a -> a -> CList a
addEnd EmptyCL y = CUnit y
addEnd (CUnit x) y = Consnoc x EmptyCL y 
addEnd (Consnoc x xs w) y = Consnoc x (addEnd xs w)  y

isEmptyCL :: CList a -> Bool
isEmptyCL EmptyCL = True 
isEmptyCL _ = False


isCUnit :: CList a -> Bool
isCUnit (CUnit x) = True
isCUnit _  = False 


--b) definir reverseCL que toma una CList y devuelve su inversa

reverseCL :: CList a -> CList a
reverseCL EmptyCL = EmptyCL
reverseCL (CUnit x) = CUnit x
reverseCL (Consnoc x xs y) = Consnoc y (reverseCL xs) x

-- c) Definir una funci´on inits que toma una CList y devuelve una CList con todos los posibles inicios de la CList.

inits :: CList a -> CList (CList a)
inits EmptyCL = CUnit EmptyCL
inits (CUnit x) = Consnoc EmptyCL EmptyCL (CUnit x)
inits xs = addEnd (inits (deleteEnd xs)) xs

deleteEnd :: CList a -> CList a
deleteEnd EmptyCL = EmptyCL
deleteEnd (CUnit x) = EmptyCL
deleteEnd (Consnoc x l _) = addInit x l

addInit :: a -> CList a -> CList a
addInit x EmptyCL = CUnit x
addInit x (CUnit y) = Consnoc x EmptyCL y
addInit x (Consnoc z l w) = Consnoc x (addInit z l) w

-- d) Definir una función lasts que toma una CList y
-- devuelve una CList con todas las posibles terminaciones de laCList.

lastCL :: CList a -> CList (CList a) 
lastCL EmptyCL = CUnit EmptyCL
lastCL (CUnit x) = Consnoc EmptyCL EmptyCL (CUnit x)
lastCL xs = addEnd (lastCL (tailCL xs)) xs

-- e) Definir una función concatCL que toma una CList de CList y devuelve la CList con todas ellas concatenadas

concatCL :: CList (CList a) -> CList a
concatCL EmptyCL = EmptyCL
concatCL (CUnit EmptyCL) = EmptyCL
concatCL (Consnoc EmptyCL EmptyCL (CUnit x)) = CUnit x
concatCL (Consnoc (CUnit x) EmptyCL EmptyCL) = CUnit x
concatCL (Consnoc xs xss ys) = appendCL xs (appendCL (concatCL xss) ys )   
 
appendCL :: CList a -> CList a -> CList a
appendCL EmptyCL xs = xs 
appendCL xs EmptyCL = xs 
appendCL (CUnit x) xs = addEnd xs x 
appendCL xs (CUnit x)  = addEnd xs x
appendCL xs (Consnoc z i w) = appendCL (addEnd xs z) (tailCL (Consnoc z i w)) 

-- ###############################################
-- 4) 
-- ###############################################

data Exp = Lit Int | Add Exp Exp | Sub Exp Exp | Prod Exp Exp | Div Exp Exp deriving Show

eval :: Exp -> Int 
eval (Lit x) = x
eval (Add exp1 exp2) = eval exp1 + eval exp2
eval (Sub exp1 exp2) = eval exp1 - eval exp2
eval (Prod exp1 exp2) = eval exp1 * eval exp2
eval (Div exp1 exp2) = eval exp1 `div` eval exp2

-- #####################################
-- 5)
-- #####################################

{- a) 
Defina una funci´on parseRPN :: String → Exp que, dado un string que representa una expresi´on escrita en
RPN, construya un elemento del tipo Exp presentado en el ejercicio 4 correspondiente a la expresi´on dada. Por
ejemplo:
parseRPN “8 5 3 − 3 ∗ +” = Add (Lit 8) (Prod (Sub (Lit 5) (Lit 3)) (Lit 3))
Ayuda: para implementar parseRPN puede seguir un algoritmo similar al presentado anteriormente. En lugar
de evaluar las expresiones, debe construir un valor de tipo Exp.
-}
type Stack  = [Exp] 

push :: Exp -> Stack  -> Stack 
push x xs = (x:xs) 

pop :: Stack  -> Maybe (Exp, Stack )
pop [] = Nothing
pop (x:xs) = Just (x,xs)

parseRPN :: String ->  Exp 
parseRPN cs = exp 
                where 
                   (Just (exp,s)) = parseAux cs []

parseAux :: [Char] -> Stack  -> Maybe (Exp, Stack ) 
parseAux xs  p
                | null xs  = pop p
                | isDigit x = parseAux xs'  (push (Lit (digitToInt x)) p)
                | x == '+' = parseAux xs' (push (Add exp1 exp2) p'')
                | x == '-' = parseAux xs' (push (Sub exp1 exp2) p'')
                | x == '/' = parseAux xs' (push (Div exp1 exp2) p'')
                | x == '*' = parseAux xs' (push (Prod exp1 exp2) p'')
                where 
                    x = head xs
                    xs' = tail xs
                    Just (exp1, p') = pop p
                    Just (exp2, p'') = pop p'

evalRPN :: String -> Int
evalRPN cs = eval (parseRPN cs)

-- ===================================================
--6)
-- ===================================================

seval :: Exp -> Maybe Int 
seval (Lit x) = Just x
seval (Add exp1 exp2) =  
    case seval exp1 of 
        Nothing -> Nothing
        Just y -> 
            case seval exp2 of 
                Nothing -> Nothing
                Just w -> Just (y + w)

seval (Sub exp1 exp2) = 
    case seval exp1 of 
        Nothing -> Nothing
        Just y -> 
            case seval exp2 of 
                Nothing -> Nothing
                Just w -> Just ( y - w)
seval (Prod exp1 exp2) = 
    case seval exp1 of
        Nothing -> Nothing 
        Just y -> 
            case seval exp2 of
                Nothing -> Nothing 
                Just w -> Just (y * w)
seval (Div exp1 exp2) = 
    case seval exp1 of
        Nothing -> Nothing 
        Just y -> 
            case seval exp2 of
                Nothing -> Nothing
                Just 0 -> Nothing
                Just w -> Just (y `div` w)
