
--Implementación de colas usando listas

newtype Cola a = MkCola [a] 

vacia :: Cola a 
vacia = MkCola []

push :: a -> Cola a -> Cola a -- O(1)
push x (MkCola xs) = MkCola (x:xs) 

pop :: Cola a -> Cola a -- O(n)
pop (MkCola []) = MkCola []
pop (MkCola xs) = MkCola (init xs) 

primero :: Cola a -> a -- O(n)
primero (MkCola []) = error "Cola vacía"
primero (MkCola xs) = last xs

esVacia :: Cola a -> Bool -- O(1)
esVacia (MkCola []) = True
esVacia (MkCola _) = False
