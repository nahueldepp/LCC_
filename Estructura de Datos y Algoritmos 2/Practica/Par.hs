{-
 Este módulo requiere la librería parallel.

 Si no la tiene instalada, se puede instalarse utilizando Cabal, ejecutando el siguiente código
 en un intérprete de comandos:

 $ cabal update
 $ cabal install parallel

-}

module Par where


(|||) :: a -> b -> (a, b)
a ||| b = (a, b)
