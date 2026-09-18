;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |TP7  primo|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp")) #f)))
#|TRABAJO PRACTICO 7 |#

;*****************************************************
;Ejercicio 1

(define CARAS 36) ;representa las caras de un dado

;simulador-dado : Natural -> List (Number)
;recibe un número natural n y devuelve una lista con n
;números aleatorios entre 1 y CARAS.


(define (simular-dado n) (cond [(zero? n) '()]
                                 [else (cons (add1 (random CARAS)) (simular-dado (sub1 n)) )]))

;lista: Number -> Lits(Number)

(define (lista n) (cond [(zero? n) '()]
                        [else (cons n (lista (sub1 n)))]))

;intervalo: Number -> List (Number)

(define (intervalo n) (cond [(zero? n) '()]
                         [else (foldl cons  '() (lista n))]))


(define MAX 100000)
(define EXPERIMENTO (simular-dado MAX))
(define VALORES (intervalo CARAS))

;frecuencia: Number List(Number) -> Number
;Dado un número n y una lista l, la función determina la cantidad de iteraciones de n en l

(define (frecuencia n l)
                         (local ((define (n? m) (= m n)))
                           ; -IN
                           (length (filter n? l))))


;frecuencia-rel: Number List -> Number
;Dado un número n y una lista l, calcula la frecuencia relativa con la que aparece n en l

(define (frecuencia-rel n l) (/ (frecuencia n l) (length l)))


;frec-rel-ex: Number -> Number

(define (frec-rel-ex n) (frecuencia-rel n EXPERIMENTO))


(define FRECUENCIAS-RELATIVAS (map frec-rel-ex VALORES))


;**************************************************************************

;; Estas primera parte nos define una funciÃ3n que genera nÃomeros aleatorios
;; en un intervalo real determinado.
;; Recordemos que la funciÃ3n random nos devuelve un natural, pero para
;; nuestro problema necesitamos nÃomeros aleatorios fraccionarios.
(define RAND-MAX 4294967087) ; nÃomero mÃ¡ximo para valores aleatorios

; aleatorio : Number Number -> Number
; dados dos nÃomeros a y b, devuleve un nÃomero aleatorio en el intervalo [a,b].
(define (aleatorio a b) (+ a (* (- b a) (/  (+ 1 (random RAND-MAX)) (* 1.0 RAND-MAX)))))

;; fin de la parte para generar nÃomeros aleatorios. No es necesario entender cÃ3mo funciona,
;; sÃ3lo basta con entender el propÃ3sito de aleatorio (Â¿se acuerdan de la receta?)

;; Definimos algunas constantes:
(define RADIO 3.0) ; radio del cÃ­rculo
(define CENTRO (make-posn -1 -0.5)) ; coordenadas del centro del cÃ­rculo

(define MAX2 300000) ; cantidad de puntos a generar para nuestra estimaciÃ3n

; generar-puntos : Natural -> List(posn)
; Dado un natural n, devuelve una lista con n puntos aleatorios,
; con ambas componentes en el intervalo [-RADIO, RADIO]. Es decir, dentro del cuadrado.
(define (generar-puntos n)
  (cond [(zero? n) empty]
        [else (cons (make-posn (aleatorio 0 2) (aleatorio 0 2) )
                    (generar-puntos (- n 1)))]
        ))

; distancia : posn posn -> Number
; dados dos puntos, devuelve su distancia
(check-expect (distancia (make-posn 15 0) (make-posn 3 0)) 12)
(check-expect (distancia (make-posn 2 1) (make-posn 6 4)) 5)
(check-expect (distancia (make-posn 0 16) (make-posn 0 0)) 16)
(define (distancia p q)
  (sqrt (+ (sqr (abs (- (posn-x p) (posn-x q)))) (sqr (abs (- (posn-y p) (posn-y q)))))))

; adentro? : posn -> Boolean
; dada una posiciÃ3n, determina si cae en el cÃ­rculo centrado en CENTRO y cuyo radio es RADIO
(check-expect (adentro? (make-posn 0 0)) #t)
(check-expect (adentro? (make-posn RADIO (* 2 RADIO))) #f)
(check-expect (adentro? (make-posn RADIO RADIO)) #f)
(define (adentro? p) (and (<= 0 (posn-x p) ) (<= 0 (posn-y p))(<= (distancia p CENTRO) RADIO))) 


; generamos una lista con muchos puntos aleatorios
(define LISTA (generar-puntos MAX2))

; nos quedamos con aquellos que estÃ¡n dentro del cÃ­rculo 
(define ADENTRO (filter adentro? LISTA))

; aproximamos el Ã¡rea del cÃ­rculo a partir de la proporciÃ3n de puntos que
; caen dentro del cÃ­rculo:
(define AREA (* 4.0 (/ (length ADENTRO) (length LISTA))))


;; Como en nuestro caso ya sabemos cuÃ¡l es el Ã¡rea de la superficie (pi),
;; podemos usar nuestro resultado como una estimaciÃ3n de este nÃomero.
;; Veamos quÃ© tan buena estimaciÃ3n es, calculando el error relativo porcentual
;; respecto del valor que nos proporciona racket:
; calculamos el porcentaje de error:
;(define ERROR (* 100 (/ (abs (- 2 AREA)) 2)))


(string-append "Nuesta aproximaciÃ3n de A es: " (number->string  (exact->inexact AREA)))

;(string-append "Con un porcentaje de error de: " (number->string ERROR) "% (si lo comparamos con el valor que nos proporciona DrRacket)")

;****************************************************************

;Ejercicio 3

; intervalo : N N -> List(N)
; dados dos números naturales, devuelve una lista con todos los nÃomeros entre a y b
(check-expect (intervaloab 2 4) (list 2 3 4)) 
(check-expect (intervaloab 4 4) (list 4))
(check-expect (intervaloab 5 4) empty)


(define (intervaloab a b) (cond [(= a b) (cons b '())]
                              [(< b a) '()]
                              [else (cons a (intervaloab (add1 a) b))])
  )

;eliminar-mul: N List(Natural) -> List(Natural)
;Dado un número natural y una lista de números, descarta todos los multiplos de n de la lista
(check-expect (eliminar-mul 3 (list 4 6 11 15)) (list 4 11))
(check-expect (eliminar-mul 1 (intervaloab 1 1000)) empty)

(define (eliminar-mul n l) (local
                             ;multiplo?: N->Boolean
                             ;dado un m, devuelve #t si es multiplo de  n
                             ((define (multiplo?  m) (not(integer? (/ m n)))))
                             ;- IN-
                             (cond [(= n 1) '()]
                                   [else (filter multiplo? l)]
                                 )))

; eratostenes : List(N) -> List(N)
; dada una lista que inicialmente es de la forma [2, .., n] para algÃon n, realiza el procedimiento de eratÃ3stenes
(check-expect (eratostenes (intervaloab 2 10)) (list 2 3 5 7))
(check-expect (eratostenes empty) empty)
(check-expect (eratostenes (intervaloab 2 17)) (list 2 3 5 7 11 13 17))
(check-expect (eratostenes (intervaloab 2 100)) (list 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97))

(define (eratostenes l) (cond [(empty? l) '()]
                              
                              [else  (cons (first l) (eliminar-mul (first l) (eratostenes (rest l) )))]))

;criba-eratostenes: N ->List(N)
;dado un n>=2, duvuelve una lista con todos los números primos de 2 a n

(check-expect (criba-eratostenes 10) (list 2 3 5 7))
(check-expect (criba-eratostenes 100) (list 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97))

(define (criba-eratostenes n) (eratostenes (intervaloab 2 n)))


;uno-por-uno: List(N)-> string
;dada una lista de números, devuelve un string en donde un número ocupa una linea.
(define (uno-por-uno l) (cond [(empty? l) ""]
                              [else (string-append (number->string (first l)) "\n"
                                     (uno-por-uno (rest l))) ]))
;------FILES--------
(write-file "primos2.txt"(uno-por-uno (criba-eratostenes 1000) )) 

(read-csv-file "primos2.txt" )



;*******************************************************

;EJERCICIO 4

;-------CONSTANTES--------------------------
(define MAX3 10000)
(define LISTA-DE-PRIMOS (read-lines "primos2.txt") )

;-------------------------------------------

; ListSN es:
;- '()
; (cons "n" StringNumeric
;donde "n" es un string de un número n (ej: "2")

;deSaN: ListSN-> List (N)
;dada una ListSN, devuelve una lista de números

(check-expect (deSaN (list "2" "5" "6")) (list 2 5 6))

(define (deSaN l) (cond [(empty? l) '()]
                        [else (cons (string->number (first l)) (deSaN (rest l)))]))





;es-primo?: Natural -> Boolean
;dado un número m<= MAX^2, devuelve #t si es primo

(check-expect (es-primo? 86077909)#t)
(check-expect (es-primo? 96928157)#t)
(check-expect (es-primo? 49987169)#t)
(check-expect (es-primo? 45566464)#f)


(define (es-primo? m) (local
                             ((define (divisible? n) (cond [(= m n) #f]
                                                      [else (integer? (/ m n))])))
                        ;-IN-
                        (cond [(< (sqr MAX3) m) "no computable" ]
                              [else (empty? (filter divisible? (deSaN LISTA-DE-PRIMOS ))
                        )])))

;todos-primos?: Lista(N) -> Boolean
; dada una lista de números
;menores o iguales a max3^2 , determine si todos ellos son primos.

(check-expect (todos-primos? (list 86077909 96928157 49987169)) #t)
(check-expect (todos-primos? (list 49987169 96928157 8595246)) #f)


(define (todos-primos? l) (= (length l)(length (filter es-primo? l))))