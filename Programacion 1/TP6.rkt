;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname TP6) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| Practica 6 |#


; copiar: Natural String -> Lista(String)
; El propósito de la función copiar es crear una lista de
; n copias de una cadena s

;given a Natural and a String, the function create a list of n copies of a string

(define (copiar n s) (cond [(zero? n) '()]
                           [(positive? n) (cons s (copiar (sub1 n) s))]
                           ))

(check-expect (copiar 2 "hola") (list "hola" "hola"))
(check-expect (copiar 0 "hola") '())
(check-expect (copiar 4 "abc") (list "abc" "abc" "abc" "abc"))



;****************************************
;Ejercicio 1

;sumanat: Natural Natural -> Natural
;Given two natural numbers, add both of them without using "+".

(check-expect (sumnat 1 2) 3)
(check-expect (sumnat 0 1) 1)
(check-expect (sumnat 1 0) 1)
(check-expect (sumnat 5 2) 7)

(define (sumnat n1 n2) (cond [(zero? n1) n2]
                             [(positive? n1) (sumnat (sub1 n1)(add1 n2))  ]
                             ))

;***************************************

;Ejercicio 2

;multiplicar: Number Number -> Number
;Given two natural nubers, the function multiplies both without using * or +

(check-expect (multiplicar 1 0 ) 0)
(check-expect (multiplicar 1 15) 15)
(check-expect (multiplicar 2 4) 8)
(check-expect (multiplicar 3 2) 6)
(check-expect (multiplicar 2 3) 6)
(define (multiplicar n m) (cond [(zero? n) 0]                              
                                [(positive? n) (sumnat (multiplicar (sub1 n) m) m)]
                                
                            ))


;***************************************

; Ejercicio 3

;powernat: Natural Natural -> Natural
;Given two natural numbers n, m, the function return the power of n to the m.

(check-expect (powernat 1 2) 1)
(check-expect (powernat 2 1) 2)
(check-expect (powernat 3 2) 9)

(define (powernat  m n) (cond [(zero? n) 1]
                             [(positive? n) (multiplicar (powernat m (sub1 n)  ) m)]))

;***************************************

;Ejercicio 4

;sigma: Natural (Natural -> Number) -> Number
; dados un número natural n y una función f, devuelve la
;sumatoria de f para los valores de 0 hasta n.


(check-expect (sigma 4 sqr)
              30)
(check-expect (sigma 10 identity)
              55)

(define (sigma n f) (cond [(zero? n) (f 0)]
                          [(positive? n) (+ (f n) (sigma (sub1 n) f))]))

;***********************************

;Ejercicio 5


;a)

;r(n): Natural -> Number
;dado un numero natural calcula 1/2^n

(check-expect (r 2) 1/4)
(check-expect (r 3) 1/8)

(define (r n) (/ 1 (expt 2 n)))

;R(n): Number (Natural -> Number) -> Number

(check-expect (R 2) 7/4)


(define (R n) (sigma n r))

;b)

;s: Natural -> Number
;dado un naural i, calcula i/1+i

(check-expect (s 0) 0)
(check-expect (s 1) 1/2)
(check-expect (s 2) 2/3)

(define (s i) (/ i (+ 1 i)))

;S(n): Natural (Natural -> Number) -> Number

(check-expect (S 2) 7/6)

(define (S n) (sigma n s))

;c)

;t(n): Natural -> Number
;Dado un natural n calcula: 1/1+n

(define (t n) (/ 1 (+ 1 n)))


;T(n):Natural (Natural->Number) -> Number

(check-expect (T 2) 11/6)

(define (T n) (sigma n t))

;******************************************

;Ejercicio 6


;intervalo: List(Natural) -> List (Number)
;Dado un numero n, devuelve una lista con el intervalo de 1 a n

; n-(n-1)
(define (lista-n n) (cond [(zero? n) '()]
                            [else (cons n (lista-n (sub1 n)))]))
 


(define (intervalo n) (reverse (lista-n n )))


;******************************************


;Ejercicio 7

;factnat: Natural -> Natural
; Dado un número n calcula su factorial

(check-expect (factnat 5) 120)
(check-expect (factnat 2) 2)


(define (factnat n) (cond [(zero? n ) 1]
                          [else (* n (factnat (sub1 n)))]))

;******************************************

;Ejercicio 8

;fibo: Natural -> Natural
;toma un número natural y devuelve el valor correspondiente a la secuencia de Fibonacci para ese valor

(define (fibo n) (cond [(zero? n) 1]
                       [(= n 1) 1]
                       [else (+ (fibo (sub1 n)) (fibo (- n 2) ))]))

;******************************************

;Ejercicio 9

(check-expect (list-fibo 4)
              (list 5 3 2 1 1))
(check-expect (list-fibo 0)
              (list 1))

(define (list-fibo n) (cond [(zero? n) (cons 1'())]
                             [else (cons (fibo n) (list-fibo (sub1 n)))]
                             )) 

;******************************************

;Ejercicio 10





;G: Natural -> Natural
;

(define (G n) (cond [(zero? n) 1]
                    [(= n 1) 2]
                    [(= n 2)3 ]
                    [else (* (G (- n 1)) (G (- n 2)) (G (- n 3)))]
                    ))

;list-g: Natural -> List(Natural)
;dado un número n devuelve la lista con los valores que resulta de evaluar a g
;en n, n-1, n-2,...,0. Es decir (list-g n) = (list (g n) (g (- 1 n)) ... (g 1) (g 0)).

(check-expect (list-g 4)
              (list 36 6 3 2 1))
(check-expect (list-g 0)
              (list 1))

(define (list-g n ) (cond [(zero? n) (cons(G 0) '())]
                          [(positive? n) (cons (G n) (list-g (sub1 n)))]
                          ))

;*******************************************

;Ejercicio 11

;componer: Number (Number->Number) -> Number
;dados: una función f: Number -> Number,
;un natural n, y
;un número x,
;devuelva el resultado de aplicar n veces la función f a x.

(check-expect (componer sqr 2 5)
              625)
(check-expect (componer add1 5 13)
              18)


(define (componer  f n x) (cond [(= 1 n) (f x)]
                               [else (f(componer f (sub1 n) x))]))

;*******************************************

; Ejercicio 12

;multiplos: Natural Natural -> List (Natural)
;Dado dos naturales n y m, y devuelva una lista con los primeros n
;múltiplos positivos de m, en orden inverso: m * n, m * (n-1), ... , m * 2, m.

(check-expect (multiplos 4 7)
              (list 28 21 14 7))
(check-expect (multiplos 0 11)
              '())

(define (multiplos  n m)  (cond [(zero? n) '()]
                               [else (cons (* m (first (lista-n n))) (multiplos  (sub1 n) m))]
                           ))

;*********************************************

;Ejercicio 13


(define (una-funcion n m) (or m n))

;ge: Number (Number -> Boolean) -> Boolean
;dado un número natural n y una función f: Natural -> Boolean,
;devuelve #true si y sólo si alguno de los valores (f 0) ,(f 1) ,... (f n) es #true.

(check-expect (ge 3 negative?)
               #false)
 
(check-expect (ge 7 even?)
               #true)

(define (ge n f) (foldr una-funcion #f (map f (lista-n n))))

;**********************************************

;Ejercicio 14


;circulos: Number Number -> Image
;tome un número natural m y devuelva una imagen cuadrada de lado 2*m2
;con m círculos azules centrados y radios: m2, (m-1)2, ... , 22, 1 respectivamente.

(define (circulos m n) (cond [(zero? n) (square (* 2 (sqr m)) "outline" "red")]
                             [else (place-image
                                  (circle (sqr n) "outline" "yellow")
                                  (sqr m)  (sqr m)
                                  (circulos m (sub1 n)))]))

;**********************************************

;Ejercicio 15

;cuadrados: Number Number -> Image


(define (cuadrados m n ang) (cond [(zero? n) (square  200 "outline" "red")]
                                  [else (place-image
                                         (rotate ang(square (sqr n) "outline" "blue"))
                                           (sqr m)   (sqr m) 
                                          (cuadrados m (sub1 n) (- ang 20)))]
                                  ))

;********************************************

;Ejercicio 16

;cuotas: Number Number Number -> List (Number)
;dado un importe total de un préstamo, un valor n correspondiente al número de cuotas,
;una tasa i de interés, devuelva una lista con las cuotas a pagar ordenadas de forma creciente.

(check-expect (cuotas 10000 0 18)
              '())
(check-expect (cuotas 10000 1 12)
              (list 10100))
(check-expect (cuotas 30000 3 12)
              (list 10100 10200 10300))
(check-expect (cuotas 100000 4 18)
              (list 25375 25750 26125 26500))

(define (cuotas total n i) (cond [(zero? n) '()]
                             [else (reverse (cuotas-al (/ total n) n i))]
                             ))



(define (calc-cuo cuota n  i ) (+ cuota  (*  cuota  n (/ i (* 12 100)) )))


(define (cuotas-al cuota n i) (cond [(zero? n) '()]
                             [else (cons (calc-cuo cuota n i ) (cuotas-al cuota (sub1 n) i))]
  ))
                                 
                             