;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |TP7 PARTE 2|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp")) #f)))

; TRABAJO PRACTICO 7 PARTE


; representaremos alfabetos como Strings.
; Por ejemplo, si nuestros sÃ­mbolos son las cinco primeras letras, los dÃ­gitos y el espacio,
; lo representaremos como "ABCDE0123456789 "

; representaremos sÃ­mbolos como strings de longitud 1. En el alfabeto anterior,
; el sÃ­mbolo E lo representamos con el string "E"

; el cÃ3digo del cÃ©sar lo representaremos mediante parejas de sÃ­mbolos.
; Por ejemplo, si queremos decir que el sÃ­mbolo "A" se codifica con el
; sÃ­mbolo "C", tendremos (make-posn "A" "C") para representar esta situaciÃ3n.

;;;;;;;; Primero comenzamos definiendo algunas funciones
; sobre strings y listas que nos son de utilidad.

; partir : String -> List(String)
; dado un string, devuele una lista de strings con cada sÃ­mbolo separado
(check-expect (partir "ABC") (list "A" "B" "C"))
(check-expect (partir "12345") (list "1" "2" "3" "4" "5")) 

(define (partir s) (cond [(= (string-length s) 0 ) '()]
                         [else (cons (string-ith s 0) (partir (substring s 1  (string-length s))))]))

; tomar : List N -> List
; dada una lista y un nÃomero natural n, devuelve una lista
; con los primeros n elementos de l. Si l no tiene tantos elementos,
; devuelve l.
(check-expect (tomar (list 1 2 3 4 5) 4) (list 1 2 3 4))
(check-expect (tomar (list 1 2 3 4 5) 10) (list 1 2 3 4 5))
(check-expect (tomar (list 1 2 3 4 5) 0) empty)


(define (tomar l n) (cond [(= n 0) '()]
                          [(= n (length l)) l]
                          [(empty? l) l]
                          [else (cons (first l) (tomar (rest l) (sub1 n)))]))

; tirar : List N -> List
; dada una lista y un nÃomero natural n, devuelve una lista
;  sin los primeros n elementos de l. Si l no tiene tantos elementos,
; devuelve empty.
(check-expect (tirar (list 1 2 3 4 5) 2) (list 3 4 5))
(check-expect (tirar (list 1 2 3 4 5) 10) empty)
(check-expect (tirar (list 1 2 3 4 5) 0) (list 1 2 3 4 5))

(define (tirar l n) (cond [(empty? l) '()]
                          [(zero? n) l ]
                          [(= n (length l)) '()]
                          [else (tirar (rest l) (sub1 n))]))

; OBSERVACION: para cualquier n <= length l, (append (tomar n l) (tirar n l)) = l

; emparejar : List List -> List
; dadas dos listas [a0,..., an] y [b0, ...., bn] de la misma longitud, devuelve una lista
; de posn con parejas tomadas de ambas listas: [(make-posn a0 b0), ...., (make-posn an bn)]
(check-expect (emparejar (list 1 2) (list "a" "b")) (list (make-posn 1 "a") (make-posn 2 "b")))
(check-expect (emparejar (list #t #f) (list 1 0)) (list (make-posn #t 1) (make-posn #f 0)))

(define (emparejar l1 l2) (cond [(empty? l1) '()]
                                [(empty? l2) '()]
                                [(= (length l1) (length l2)) (cons (make-posn (first l1) (first l2))
                                                                   (emparejar (rest l1) (rest l2))) ] 
                           ))


;;;;;;;;;;;;; Ahora comienzan las funciones especÃ­ficas para el mÃ©todo del CÃ©sar
; cifrado : N String -> List(posn)
; dada una clave de desplazamiento y un alfabeto s, devuelve una lista
; con parejas de strings, donde el primer elemento es el caracter a cifrar, y el segundo
; su cÃ3digo del CÃ©sar de acuerdo a la clave. Se asume que 0 < n < (string-length s)
(check-expect (cifrado 2 "ABC") (list (make-posn "A" "C") (make-posn "B" "A") (make-posn "C" "B"))) 
(check-expect (cifrado 1 "ABC") (list (make-posn "A" "B") (make-posn "B" "C") (make-posn "C" "A")))
; COMPLETAR (las funciones tirar, tomar, partir y emparejar le serÃ¡n de utilidad.

(define (cifrado n l) (cond [(empty? l) '()]
                            [else (emparejar  (partir l) (append(tirar (partir l) n) (tomar (partir l) n)))]))

; encriptar-simbolo : String List(posn) -> String
; dado un string s de longitud 1 que es un sÃ­mbolo del
; alfabeto y una lista de parejas que representa un cÃ3digo del cÃ©sar,
; devuelve el cÃ3digo que le corresponde a s
(check-expect (encriptar-simbolo "A" (cifrado 2 "ABC")) "C")
(check-expect (encriptar-simbolo "A" (cifrado 1 "ABC")) "B")
; COMPLETAR ...  

(define (encriptar-simbolo s l) (cond [(string=? s (posn-x (first l))) (posn-y (first l))]
                                      [else (encriptar-simbolo s (rest l))]))

; encriptar-mensaje : String String Natural -> String
; dado un string, un alfabeto y una clave, devuelve el string encriptado
(check-expect (encriptar-mensaje "ABC" "ABCDEF" 3) "DEF")
(check-expect (encriptar-mensaje "ABC" "ABCDEF" 4) "EFA")
; COMPLETAR ...
(define (encriptar-mensaje s alfa clave) (cond [(zero? (string-length s ) ) ""]
                                               [else (string-append
                                                      (encriptar-simbolo (first (partir s))(cifrado clave alfa))
                                                      (encriptar-mensaje (substring s 1 (string-length s)) alfa clave))
                                                ]))


; desencriptar-simbolo : String List(posn) -> String
; dado un string s de longitud 1 que es un sÃ­mbolo del
; alfabeto y una lista de parejas que representa un cÃ3digo del cÃ©sar,
; devuelve el caracter desencriptado que le corresponde a s
(check-expect (desencriptar-simbolo "A" (cifrado 2 "ABC")) "B")
(check-expect (desencriptar-simbolo "A" (cifrado 1 "ABC")) "C")
; COMPLETAR ...

(define (desencriptar-simbolo s l) (cond [(string=? s (posn-y (first l))) (posn-x (first l))]
                                         [else (desencriptar-simbolo s (rest l))]))

; desencriptar-mensaje : String String N -> String
; dado un string, un alfabeto y una clave, devuelve el string encriptado
(check-expect (desencriptar-mensaje "DEF" "ABCDEF" 3) "ABC")
(check-expect (desencriptar-mensaje "EFA" "ABCDEF" 4) "ABC")
; COMPLETAR ...

(define (desencriptar-mensaje s alfa clave) (cond [(zero? (string-length s)) ""]
                                                  [else (string-append
                                                         (desencriptar-simbolo  (first (partir s)) (cifrado clave alfa))
                                                         (desencriptar-mensaje (substring s 1 (string-length s)) alfa clave))])
  )


(define ALFABETO "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ 0123456789")
(define CLAVE 3)
(define CODIGO-DEL-CESAR (cifrado CLAVE ALFABETO))


(encriptar-mensaje "HOLA" ALFABETO CLAVE)
(encriptar-mensaje "ATACAR A LAS 18" ALFABETO CLAVE)
(encriptar-mensaje "LA OPERACION ES REVERSIBLE" ALFABETO CLAVE)
(desencriptar-mensaje (encriptar-mensaje "LA OPERACION ES REVERSIBLE" ALFABETO CLAVE) ALFABETO CLAVE)



;Ejercicio 6


;intervalo: List(Natural) -> List (Number)
;Dado un numero n, devuelve una lista con el intervalo de 1 a n

 
 
(define (intervalo n) (reverse (lista-n n )))

;lista-n: N -> List (n)
;dado un n genera una lista de n a 1,tal que: n, (n-1), (n-2) , ......, 1
(define (lista-n n) (cond [(zero? n) '()]
                            [else (cons n (lista-n (sub1 n)))]))


(define JUEGOS 100000)


;eliminar: N List(n) -> List (n)
;dado un número de cartas n, devuelve una lista de números de [1,n], simulando el juego Nada

(define (eliminar n l) (cond [(empty? l) '()]
                            [(= (first l) n) (rest l)]
                            [else (cons (first l) (eliminar n (rest l))) ]))


;pegar: N List(N) -> List(n)
;dado un número n y una lista de 1 a n, toma el elemento en la posición n
;y lo coloca al principio de la lista 


(define (pegar n l) (cond [(empty? l) '()]
                          [(zero? n) l]
                          
                          [else (cons n (eliminar n  l))]))

;lista-random: N N -> List(N)
;dados dos números n y m, la función aplica m veces "pegar" en una lista de n elementos.
;Cada vez que se aplica "pegar" se elige un elemento de manera aleatoria en el rango de [1,n]


(define (lista-random n m) (cond
                         [(zero? m) (pegar (random (add1 n)) (intervalo n))]
                         [else (pegar (random (add1 n )) (lista-random n (sub1 m)))  ]))

;Nada: N -> List(N)
;Dado un número n, devuelve una lista con valores de 1 a n en orden aleatorio.


(define (Nada n) (lista-random n n))


;camparando: List(N) List(N) -> N
;dadas dos listas ,compara los elementos de las listas 1 a 1, si algúno de estes resulta ser igual
;a su pareja devuelve 0,
;sino 1


(define (comparando l l2) (cond [(and (empty? l) (empty? l2)) #t]
                                [(not(= (first l) (first l2))) (comparando (rest l) (rest l2) )]
                                [else #f] ))

;perdedora?: List(N)-> boolean
;dada una lista Nada, decide si es una mano ganadora o perdedora, si es perdedora devuelve un 0,
;si es ganadora devuelve un 1

(check-expect (ganadora? (list 1 5 6 3 4 2)) #f)

(check-expect (ganadora? (list 2 3 1 5 6 4)) #t)

(define (ganadora? l) (comparando l (intervalo (length l))) )



;muchas-nada: N N -> ListNada
;dados n y m, juega m veces nada con n cartas.

(define (muchas-nada m n) (cond [(zero? m) '()]
                              [else (cons (Nada n ) (muchas-nada (sub1 m) n))]))

;n-ganadoras: N N -> ListNada
;dados n y m, devuelve la canidad de manos ganadoras de jugar al Nada m veces con un maso de n cartas
(define (n-ganadoras m n) (length(filter ganadora? (muchas-nada m n ))))


;por-ganadoras: N N -> N


(define (por-ganadoras m n) (/ (n-ganadoras m n) m))

