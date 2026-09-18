;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname TP5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| PRACTICA 5|#

;1)

(cons "Juan"(cons "pedro" (cons "Paula"(cons "Clara"(cons "martin" '())))))

(list 1 2 3 5 6 4)

;4)

(define (contiene-marcos? l) (cond [(empty? l) #f]
                                   [(cons? l) (if (string=? (first l) "Marcos")
                                                  #t
                                                  (contiene-marcos? (rest l)))]
                                   ))

;5)

(define L1 (list "Marcos" "Clara" "Tomi" "Marian" "Gabriel" "Ozuna"))

;contiene?: List String -> Boolean
;dada una lista y un string, determina si contiene o no ese string.

;(check-expect (contiene? L1 "Ozuna") #t)

;(check-expect (contiene? L1 "Clara") #t)

;(check-expect (contiene? L1 "Rosalia") #f)

(define (contiene? l x) (cond [(empty? l) #f]
                              [(cons? l) (if (string=?(first l) x)
                                             #t
                                             (contiene? (rest l) x))]
                              ))

;7)

(define L2 (list 15 10 2 4 6))
(define L3 (list 1 1 2 -3))


;suma: List -> Number
;recibe una lista de montos y suma todos sus elemntos

;(check-expect (suma L2) 37)

(define (suma l) (cond [(empty? l) 0]
                       [(cons? l) (+ (first l) (suma (rest l)))]
                       ))
                                     

;8)

;pos?: Lista -> Boolean
;recibe una lista de números enteros y si la lista contiene algun número negativo devuelve false

(define (pos? l) (cond [(empty? l) #t]
                       [(cons? l) (if (<= 0 (first l))
                                      (pos? (rest l))
                                      #f
                                      )]
                       ))
                            
;check-suma: Lista -> Number/String
;recibe una lista y si pertenece al tipo monto calcula su suma, sino devuelve "error".
(define (check-suma l) (if (pos? l)
                           (suma l)
                           "error"
                           ))
;9)
;listaB es:
;-empty
;-cons Boolean ListaB
;Interpretación: un elemento de ListaB es una lista cuyo elementos pertenecen al tipo booleano
(define LB (list (< 0 29) (>= 23 54) #t))
(define LB2 (list #f #f #t))
;todos-verdaderos: Lista -> Boolean
;recibe una lista de booleanos y si todos son verdaderos revuelven #true
(define (todos-verdaderos l) (cond [(empty? l) #t]
                                   [(cons? l) (and (first l) (todos-verdaderos (rest l))) ]
                                   ))

(check-expect (todos-verdaderos LB) #f)

;uno-verdadero: Lista->Boolean
;recibe una lista de booleanos y si una es verdad devuelve #true
(define (uno-verdadero l) (cond [(empty? l) #t]
                                   [(cons? l) (or (first l) (uno-verdadero (rest l))) ]
                                   ))
(check-expect (uno-verdadero LB2) #t)

;10)

;cant-elementos: List -> Number
;recibe una lista y devuelve la cantidad de elementos que posee
(check-expect (cant-elementos L2) 5) 

(define (cant-elementos l) (cond [(empty? l) 0]
                                 [(cons? l) (+ 1 (cant-elementos (rest l)))]
                                 ))
;11)

;promedio: List -> Number
;recibe una lista de números y determina el promedio.

(check-expect (promedio L2) 7.4) 

(define (promedio l) (cond [(empty? l) 0]
                           [(cons? l) (/ (suma l) (cant-elementos l))])
  )

;12)

;pares: List->List
;dada una lista l de números, devuelve una lista con todos los pares de la lista l dada

(check-expect (pares (list 10 20 5 3 16)) (list 10 20 16 ))

(define (pares l) (cond [(empty? l) l]
                        [(cons? l ) (if (even? (first l))
                                        (cons (first l) (pares (rest l)))
                                        (pares (rest l))
                                        
                                        )]
                        ))

;13)
;cortas: List->List
;dada una lista de palabras, devuelve una lista formada por aquellas que tengan cinco o menos letras

(check-expect (cortas (list "pito" "cuadril" "bombón" "aceituna" "mol" "michi")) (list "pito" "mol" "michi"))

(define (cortas l) (cond [(empty? l) l]
                         [(cons? l) (if (<= (string-length (first l)) 5)
                                        (cons (first l) (cortas (rest l)))
                                        (cortas (rest l))
                                        )]))

;14)
;mayores:List Number -> List
;dada una lista de números y un numero n, devuelve una lista con los números mayores a n
(check-expect (mayores (list 1 2 3 4 5 6 7 8 9) 7) (list 8 9)) 

(define (mayores l n) (cond [(empty? l) l]
                            [(cons? l) (if (< n (first l))
                                           (cons (first l) (mayores (rest l) n))
                                           (mayores (rest l)n )
                                           )]
                            ))

;15)

(define-struct Posn [x y])
;Posn es (Number Number)
;Interpretación: el primer elemento es la posición en el eje x y el segunda la posicón en el eje y

(define MAX 5)

;cerca: List Posn -> list

(check-expect (cerca (list (make-Posn 3 5) (make-Posn 1 2) (make-Posn 0 1) (make-Posn 5 6)) (make-Posn 0 0)) (list (make-Posn 1 2) (make-Posn 0 1)))
              
(define (cerca l s) (cond [(empty? l) l]
                        [(cons? l)(if (<= (sqrt(+ (sqr(- (Posn-x (first l))(Posn-x s)))(sqr(- (Posn-y (first l))(Posn-y s))))) MAX)
                            (cons (first l) (cerca (rest l) s)) 
                            (cerca (rest l) s))]
                        ))

;17)
;ListNum es:
;-empty
;- (cons Number ListNum)
;interpretación: Una elemento de ListNum sera una lista de números.

;eliminar: ListNum Number -> List
;Dada una lista de numeros l y un número n, elimina todas las iteraciones del número n

(check-expect (eliminar (list 0 2 4 6 8 7 4 5 4) 4) (list 0 2 6 8 7 5))


(define (eliminar l n) (cond [(empty? l) l]
                             [(cons? l) (if (= (first l) n) 
                                             (eliminar (rest l) n)
                                            (cons (first l)(eliminar (rest l) n)))
                                            ]))

;18)
;raices: List -> List
;recibe una lista de números y devuelve una lista con sus raices cuadradas

(check-within (raices (list 1 2 3)) (list (sqrt 1) (sqrt 2) (sqrt 3)) 0.001)

(define (raices l) (cond [(empty? l) l]
                         [(cons? l) (cons (sqrt (first l)) (raices (rest l)))]
                         ))
                                        

;21)

;signo: List -> List
;dada una lista de números distintos de 0, devuelve una lista con sus signos.

(check-expect (signo (list 1 -5 6 -8)) (list 1 -1 1 -1))

(define (signo l) (cond [(empty? l) l]
                        [(cons? l) (if (< 0 (first l))
                                       (cons 1 (signo (rest l)))
                                       (cons -1 (signo (rest l)))
                                       )])
)

;22)
;cuadrados: List -> List
;Dada una lista de números, devuelve una lista con sus cuadrados

(check-expect (cuadrados (list 1 2 3)) (list 1 4 9))

(define (cuadrados l) (cond [(empty? l) '()]
                            [else (cons (sqr (first l)) (cuadrados (rest l)))]
                            ))

;23)
;longitudes: String -> Number
;dada una lista de strings, devuelve una lista con sus longitudes

(check-expect (longitudes (list "hola" "manola")) (list 4 6))

(define (longitudes l) (cond [(empty? l) '()]
                             [else (cons (string-length (first l)) (longitudes (rest l)))]
                             ))

;24)
;convertirFC: List -> List
;Dada una lista de números (grados Fahrenheit), devuelve ota lista de números (grados Celcius)

(check-within (convertirFC (list 203 509 8006)) (list 95 265  4430 ) 0.00000001)

(define (convertirFC l) (cond [(empty? l) '()]
                              [else (cons (* (- (first l) 32) 5/9) (convertirFC (rest l)))]
                              ))

;25)
;prod: List -> Number
; Dada una lista de números, multiplica sus elementos entre si, para la lista vacia devuelve 1.

(check-expect (prod (list 15 2 3)) 90)
(check-expect (prod '()) 1)


(define (prod l) (cond [(empty? l) 1]
                       [else (* (first l) (prod (rest l)))]
                       ))

;26)

;ListStr es:
;-empty
;- cons string ListStr
;Interpretación: Es una lista de strings

;pegar: ListStr -> String
; dada una lista de strings, devuelve el string que se obtiene de concatenar todos los elementos de la lista.

(check-expect (pegar (list "hola " "mañosa" )) "hola mañosa." )

(define (pegar l) (cond [(empty? l) "."]
                        [else (string-append (first l) (pegar (rest l)))]
                        ))
                        
;27)
;ListNum es:
;- empty
;- (cons Number ListNum)
;interpretación: un elemento de ListNum es una lista cuyos elementos son números

;maximo: ListNum -> Number
;Dada una lista de números naturales, devuelve el maximo de la lista.

(define (maximo l) (cond [(empty? l) 0]
                         [else (max (first l) (maximo (rest l)))]
                         ))
;28)



;sumdist: List -> Number
;dada una lista de puntos del plano, devuelva la suma de sus distancias al origen.

(check-within (sumdis (list  (make-Posn 1 1) (make-Posn 1 1))) (* 2 (sqrt 2)) 0.00001)

(define (sumdis l) (cond [(empty? l) 0]
                         [else (sqrt (+ (sqr (suma-x l)) (sqr (suma-y l))))]
                         ))

(define (suma-x l) (cond [(empty? l) 0]
                          [else (+ (Posn-x (first l)) (suma-x (rest l)))]
                          ))
(define (suma-y l) (cond [(empty? l) 0]
                          [else (+ (Posn-y (first l)) (suma-y (rest l)))]
                          ))  