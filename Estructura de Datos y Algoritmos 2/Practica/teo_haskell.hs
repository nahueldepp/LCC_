{- HLINT ignore "Use foldr" -}
{- HLINT ignore "Redundant lambda" -}
takeWhile' :: (a -> Bool)->[a]->[a]
takeWhile' p []  = []
takeWhile' p (x:xs)  |p x =x:takeWhile' p xs
                     |otherwise = []

--Elimina el prefijo mas grande que cumple un predicado
dropWhile' :: (a->Bool)->[a]->[a]
dropWhile' p [] = []
dropWhile' p (x:xs)     | p x = dropWhile' p xs
                        | otherwise = x:dropWhile' p xs
--Divide la lista ente el prefijo más grande que cumple con un predicado y el resto de la lista
span'::(a->Bool)->[a]->([a], [a])
span' p [] = ([],[])
span' p (x:xs) =  (takeWhile' p (x:xs), dropWhile' p (x:xs))

--Funciones lamda 
add':: Int -> Int -> Int
add' = \x ->(\y -> x+y)

impares_1:: Int -> [Int]
impares_1 n = map f [0..n-1]
                where f x = x*2+1
impares_2:: Int -> [Int]
impares_2 n = map (\x -> x*2+1) [0..n-1]

largoL :: [a]-> Int
largoL [] = 0
largoL (x:xs) = 1 + largoL xs

pairs :: [a]->[(a,a)]
pairs xs = zip xs (tail xs)


sortedL ::Ord a => [a]->Bool
sortedL xs = and[x<=y|(x,y)<-pairs xs]

fact :: Int -> Int
fact 0 = 1
fact n = n*fact(n-1)


largoL' ::[a] -> Int
largoL' = foldr (\x -> (+)1) 0 

multiplicar :: Int -> Int -> Int
multiplicar x y = x*y

duplicar :: Int -> Int
duplicar  = multiplicar 2 



greater :: Int ->Int ->Bool
greater x y = x>y

concat' :: [[a]]->[a]
concat' xss = [ x| xs <- xss, x <-xs ]

f :: (Int, Int) -> Int
f (x , y) = let z = x + y in g (z , y) 
    where g (a, b) = a - b

second' :: a -> (a->a)
second' x = \y -> y

second2' :: a -> (a->a)
second2' x = \x -> x

zip' :: [a] -> [a] -> [(a,a)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x,y):zip' xs ys

zip3' :: [a] -> [a] -> [a] -> [(a,a,a)]
zip3' [] _ _ = []
zip3' _ [] _= []
zip3' _ _ []= []
zip3' (x:xs) (y:ys) (z:zs) = (x,y,z):zip3' xs ys zs

zip3'' :: [a] -> [a] -> [a] -> [(a,a,a)]
zip3'' xs ys  zs = [ (x,y,z) | ((x,y),z) <- zip (zip xs ys) zs]  

modulus ::(Floating a)=> [a]->a
modulus = sqrt . sum . map(^2)    

{-
Dado el siguiente tipo para representar n´umeros binarios:
type NumBin = [Bool ]
donde el valor False representa el n´umero 0 y True el 1. Definir las siguientes operaciones tomando como convenci´on
una representaci´on Little-Endian (i.e. el primer elemento de las lista de d´ıgitos es el d´ıgito menos significativo del
n´umero representado).
a) suma binaria
b) producto binario
c) cociente y resto de la divisi´on por dos
-}

type NumBin = [Bool]

xor :: Bool -> Bool -> Bool
xor x y | x&&y = False
        | otherwise = x || y
        



sumBi :: NumBin -> NumBin -> NumBin
sumBi [] ys = ys
sumBi xs [] = xs 
sumBi xs ys = sumaConCarry xs ys False

{-sumarBit usa la siguiente logica:
si cantidad = 0, (0+0+0) luego vamos a tener que devolver la suma con su bit de acarreo
en este caso (0,0), lo conseguimos ya que 0mod2=0, como 0!=1 devolvemos False(0)
y como 0<2 luego devolvemos False(0)
asimismo, siempre que la cantidad>=2, su modulo sera 0 u 1, en el caso de que 
cantidad == 2 luego al menos uno de los terminos es 0, igualmente se devuelve (0,1)
si cantidad == 3 luego todos sus terminos son 1 y obtenemos (1,1)-}
sumarBit:: Bool -> Bool ->Bool -> (Bool,Bool)
sumarBit x y carry =
    let  cantidad = fromEnum x + fromEnum y + fromEnum carry    --convertimos los booleanos a enteros
    in   (cantidad `mod` 2 == 1, cantidad>=2)

sumaConCarry :: NumBin-> NumBin -> Bool -> NumBin
sumaConCarry [] [] False = []
sumaConCarry [] []  True = [True]

sumaConCarry (x:xs) [] carry = 
    let (bit, carryNuevo) = sumarBit x False carry
    in bit : sumaConCarry xs [] carryNuevo 
sumaConCarry [] (y:ys) carry =
    let (bit, carryNuevo) = sumarBit False y carry
    in bit : sumaConCarry [] ys carryNuevo
sumaConCarry (x:xs) (y:ys) carry = 
    let (bit, nuevoCarry) = sumarBit x y carry
    in bit : sumaConCarry xs ys nuevoCarry
     

-- ============================================
-- ej13
-- ============================================          
divisors::Int -> [Int]
divisors n  |n>0 = [ x | x<-[1..n], n `mod` x == 0]
            |n<=0 = []

matches:: Int -> [Int] -> [Int]
matches x [] = []
matches x (y:ys)    |y == x = y:matches x ys
                    |y/=x = matches x ys

matches' :: Int -> [Int] -> [Int]
matches' n xs = [ x | x <- xs, x==n]

cuadruplas :: Int -> [(Int, Int, Int, Int)]
cuadruplas n = [ (a,b,c,d) | a <- [1..n], b <- [1..n], c <- [1..n], d <- [1..n], a^2+b^2==c^2+d^2 ]

unique :: [Int] -> [Int]
--tomo los elementos que no estan en la lista xs hasta la posición i
unique xs = [ x | (i,x) <- zip [0..]xs, x `notElem` take i xs  ]

enLista :: Int->[Int]->Bool
enLista n (x:xs) 
                    |null xs = False
                    | x==n =True
                    | x/=n = enLista n xs  