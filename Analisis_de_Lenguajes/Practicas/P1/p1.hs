import Parsing 
import Data.Char
import Control.Monad
import Control.Applicative hiding (many)
import Distribution.PackageDescription.Configuration (transformAllBuildDepends)
import Distribution.Simple.Utils (xargs, die')
import Data.Type.Coercion (sym)


--2)
expr:: Parser Int
expr = do   t <- term
            do  symbol "+"
                e <- expr
                return (t+e)
                <|> do  symbol "-"
                        e <- expr
                        return (t - e)
                    <|> return t

term:: Parser Int
term = do   f <- factor 
            do  symbol "*"
                t <- term 
                return (f*t)
                <|> do  symbol "/"
                        t <- term 
                        return (f `div` t)
                    <|> return f 

factor:: Parser Int 
factor = do symbol "("
            e <- expr 
            symbol  ")"
            return e
        <|> natural

eval :: String -> Int
eval xs = fst (head (parse expr xs))

--3) 
--Escribir un transformador que al recibir un parser, devuelva un nuevo parser que se comporta como el original
--pero que tambi´en acepta opcionalmente que las cadenas est´en entre par´entesis.

transformador:: Parser a -> Parser a 
transformador par = do  symbol "("
                        x <- par 
                        symbol ")"
                        return x

--4) Modificar el parser del ejercicio 2 para que en lugar de evaluar una expresi´on genere un ´arbol de sintaxis
--abstracta dado por el tipo

data Expr = Num Int | BinOp Op Expr Expr deriving Show
data Op = Add | Mul | Min | Div deriving Show

expr2:: Parser Expr
expr2 = do  t <- term2
            do  symbol "+"
                e <- expr2
                return (BinOp Add t e)
                <|> do  symbol "-"
                        e <- expr2 
                        return (BinOp Min t e)
                        <|> return t
        
term2:: Parser Expr
term2 = do  f <- factorOp 
            do  symbol "*"
                e <- expr2 
                return (BinOp Mul f e)
                <|> do  symbol "/"
                        e <- expr2
                        return (BinOp Div f e)
                <|> return f



factorOp:: Parser Expr 
factorOp = do   symbol "("
                e <- expr2 
                symbol  ")"
                return e
            <|> do  n <- natural
                    return (Num n)
 

--5) 
--Podemos modelizar una subfamilia de los tipos de datos de Haskell mediante el siguiente tipo de datos:
data Basetype = DInt | DChar | DFloat | Fun Basetype Basetype deriving Show
type Hasktype = [Basetype] 


basetype:: Parser Basetype
basetype =  do  string "Int"
                return  DInt
                <|> do  string "Char"
                        return DChar
                        <|> do  string "Float"
                                return DFloat
                                <|> failure 

hasktype :: Parser Hasktype
hasktype =  do sepBy basetype (symbol "->")


--6)

data AlphaNum = N Int | C Char deriving Show
type Ans = [AlphaNum]

alphaNumtype :: Parser AlphaNum
alphaNumtype    =   do  symbol "'"
                        c <- item 
                        symbol "'"
                        return (C c)
                        <|> do  n <- integer
                                return (N n)

hetero :: Parser Ans 
hetero  =   do  symbol "["
                sepBy   alphaNumtype    (symbol ",")

--7) 7. Podemos modelizar otra subfamilia de los tipos de datos de Haskell, m´as expresiva que la del ejercicio 5,
--mediante el siguiente tipo de datos: data Hasktype = DInt | DChar | DFloat | Fun Hasktype Hasktype(lo puse como basetype)

{-
hexpr ::= Fun term expr | term ---> term(Fun  hexpr | e)
hterm ::= DInt | DFloat | DChar | '('hexpr')'
-}
hexpr :: Parser Basetype
hexpr = do  t <- hterm 
            do  symbol "->"
                e <- hexpr
                return  (Fun t e)
                <|> return t 

hterm :: Parser Basetype
hterm   =   do  symbol "("
                e <- hexpr
                symbol ")"
                return e
                <|> basetype  
            

-- 8)
{-Transformar la gram´atica para eliminar la recursi´on izquierda e implementar el parser expr :: Parser Expr para
la gram´atica transformada.
expr → expr (’+’ term | ’-’ term) | term
term → term (’*’ factor | ’/’ factor ) | factor
factor → digit | ’(’ expr ’)’
digit → ’0’ | ’1’ | ... | ’9’

A -> Aa | b

para evitar recursion a izquierda
A-> bA' 
A' -> aA' | e

expr -> term  expr'
expr' -> (’+’ term | ’-’ term) expr' | term 
term -> factor term'
term' -> (’*’ factor | ’/’ factor ) term' | factor
factor → digit | ’(’ expr ’)’
digit → ’0’ | ’1’ | ... | ’9’
-}

exprSri:: Parser Expr 
exprSri =   do  t <-term 
                e <- expr'
                <|> t <- term

expr':: Parser Expr 
expr' = do  