;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |ejercicios de finales|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp")) #f)))
;Ejercicios final


;6)
;Diseñe una función replicar que tome una lista y un número entero n y replique
;cada elemento de la lista n veces.

;replicar: List Number -> List
; toma una lista y un número entero n y replique
;cada elemento de la lista n veces.
(check-expect (replicar (list 4 6 3 9) 3) (list 4 4 4 6 6 6 3 3 3 9 9 9)
)

(define (replicar l n) (cond [(empty? l) '()]
                             [(zero? n) '()]
                             [else (append (make-list  n (first l)) (replicar (rest l) n))]
                             ))


(define-struct pedidos [nombre plato postre])
;pedidos es: [String Number Number]
;donde:
;Nombre: Es un string que represente el nombre.
;plato: Es  un número de 1 a 3 que represente la opción de menú elegida
;postre: Es un número entre 1 y 2 que represente la opción de postre elegida.



(define-struct pedido-f [m1 m2 m3 p1 p2])
;pedido-f es: [Number Number Number NUmber Number]
;Donde:
;m1: Cantidad de menues 1
;m2: cantidad de Menues 2
;m3: "     "            3
;p1: Cantidad de postres 1
;p2:Cantidad de postres 2



;---Ejemplos de pedidos-----------------
(define P1 (make-pedidos "juena" 2 2))

(define P2 (make-pedidos "Juan" 1 2))

(define P3 (make-pedidos "Julieta" 3 1))

(define P4 (make-pedidos "martin" 1 1))

(define Ps (list P1 P2 P3 P4))

;---------------------------------------

;listP es:
;- '()
; (cons pedidos (listP))
;donde pedidos es una estructura pedidos.


;contar-m1: ListP -> Number

(define(contar-m1 l) (cond [(empty? l) 0]
                               [(= 1 (pedidos-plato (first l))) (+ 1 (contar-m1 (rest l)))]
                               [else (contar-m1 (rest l))]))
;contar-m2:ListP -> Number
(define(contar-m2 l) (cond [(empty? l) 0]
                               [(= 2 (pedidos-plato (first l))) (+ 1 (contar-m2 (rest l)))]
                               [else (contar-m2 (rest l))]))

;contar-m3:ListP -> Number
(define(contar-m3 l) (cond [(empty? l) 0]
                               [(= 3 (pedidos-plato (first l))) (+ 1 (contar-m3 (rest l)))]
                               [else (contar-m3 (rest l))]))

;contar-p1:ListP -> Number
(define(contar-p1 l) (cond [(empty? l) 0]
                               [(= 1 (pedidos-postre (first l))) (+ 1 (contar-p1 (rest l)))]
                               [else (contar-p1 (rest l))]))
;contar-p1:ListP -> Number
(define(contar-p2 l) (cond [(empty? l) 0]
                               [(= 2 (pedidos-postre (first l))) (+ 1 (contar-p2 (rest l)))]
                               [else (contar-p2 (rest l))]))



;armar-pedido-final: ListP -> pedido-f
;arma un pedido final con una listP

(check-expect (armar-pedido-final Ps) (make-pedido-f 2 1 1 2 2 ))

(define (armar-pedido-final l) (cond [(empty? l) '()]
                                     [else (make-pedido-f
                                            (contar-m1 l) (contar-m2 l)
                                            (contar-m3 l) (contar-p1 l) (contar-p2 l))]))

;--------------------------------



;7)
;sublistas-vacias?: List(List(Any)) -> Boolean

(check-expect (sublistas-vacias? (list '() '() '())) #true)
(check-expect (sublistas-vacias? (list '() (list 5 7))) #false)

(define (sublistas-vacias? l) (cond [(empty? l) #t]
                                    [else (and (empty? (first l)) (sublistas-vacias? (rest l)))]))


;8)




(define-struct trabajador (apellido EC CH SB))
;trabajador es : [String Number Number Number ]
;1er campo: Apellido
;2do campo: Estado Civil. 0 si no esta casado, 1 si esta casado 
;3er campo: Cantidad de hijos
;4to campo: Sueldo Bruto

;casado? trabajador -> Boolean 
(define (casado? t) (= (trabajador-EC t) 1))

(define IM 5/100)
(define MI 15000)


;immpuestos: trabajador -> Number/string


(check-expect (impuestos (make-trabajador "jorge" 1 4 290.800)) 0)
(check-expect (impuestos (make-trabajador "pepe" 0 1 18500)) 925)

(define (impuestos t) (cond [(not(trabajador? t)) "tipo de dato invalido"]
                            
                            [(and (casado? t) (= 2 (trabajador-CH t))
                                  (> (trabajador-SB t) (+ MI 5000))) (* IM (trabajador-SB t)) ]
                          
                            [(and (casado? t) (= 1 (trabajador-CH t))
                                  (> (trabajador-SB t) (+ MI 4000))) (* IM (trabajador-SB t))]
                        
                            [(and (= 2 (trabajador-CH t))
                                  (> (trabajador-SB t) (+ MI 2000))) (* IM (trabajador-SB t))]
                            [(and (casado? t) (> (trabajador-SB t) (+ MI 3000))) (* IM (trabajador-SB t)) ]
                            
                          
                            [(and (= 1 (trabajador-CH t)) (> (trabajador-SB t) (+ MI 1000))) (* IM (trabajador-SB t))]
                            [ else 0]
                            ))



;9)


;suncadena?: List(string) string -> List(string)

(check-expect (subcadena? (list "cadena" "Helena" "casa") "ena") (list "cadena" "Helena"))
(check-expect (subcadena? (list "Hola" "mundo") "eso") '())
(check-expect (subcadena? '() "altos") '())
                            
(define (subcadena? l s ) (cond [(empty? l) '()]
                                [(string-contains? s (first l)) (cons (first l) (subcadena? (rest l) s))]
                                [else (subcadena? (rest l) s)]
                                ))


;10)
;string-a-n: List(String) -> List(Number)

(define (string-a-n l) (cond [(empty? l) '()]
                             [else (cons (string-length (first l)) (string-a-n (rest l)))]))

;minimo: List (string) -> Number

(define(long-min l) (cond [(empty? l) 1]
                        [else (min (first (string-a-n l)) (long-min (rest l)))]))

;corta: List(Strings) -> List (strings)

(define (cortas l) (cond [(empty? l) '()]
                         [(= (string-length (first l)) (long-min l))
                          (cons (first l) (cortas (rest l)))]
                         [else (cortas (rest l))]))

;shortest: List(Strings)-> String


(check-expect (shortest (list "hola" "manola" "a" "juan"  "b")) "b")

(define (shortest l) (cond [(empty? l) '()]
                       [else (first (reverse (cortas l)))]))


;long-max: List(String) -> Number
(define(long-max l) (cond [(empty? l) 1]
                        [else (max (first (string-a-n l)) (long-max (rest l)))]))


;larga: List(Strings) -> List (strings)

(define (larga l) (cond [(empty? l) '()]
                         [(= (string-length (first l)) (long-max l))
                          (cons (first l) (larga (rest l)))]
                         [else (larga (rest l))]))

;longest: List(Strings)-> String


(check-expect (longest (list "hola" "manola"  "a" "juan"  "b" "manolo")) "manolo")

(define (longest l) (cond [(empty? l) '()]
                       [else (first (reverse (larga l)))]))


;shortest-longest: List(string) -> posn

(check-expect (shortest-longest (list "a" "acb" "b" "xf" "asdf")) (make-posn "b" "asdf"))
(check-expect (shortest-longest (list "a")) (make-posn "a" "a"))


(define (shortest-longest l) (make-posn (shortest l) (longest l)))





;22)


;f: Number -> Number
;f(n) = f(n-1) + 2 * f(n-3), para todo n mayor o igual a 3.

(define (f n) (cond [(zero? n) 0]
                    [(= n 1) 2]
                    [(= n 2) 5]
                    [else (+ (f (- n 1)) (* 2 (f (- n 3)) ))]
                    ))

;lista-f : N -> List (Number)

(define (lista-f n) (cond [(= -1 n) '() ]
                          [else (cons (f n) (lista-f (sub1 n)))]
                          ))



;Fs: N -> List (Number)

(check-expect (Fs 5)
              (list 0 2 5 5 9 19))
(check-expect (Fs 0)
              (list 0))

(define (Fs n) (reverse (lista-f n)))


;23)
(define TAM 300)
(define (dibujar-elipses n ) (cond [(zero? n) (square TAM "outline" "white")]
                                   [else (place-image (rotate (* 2 n)(ellipse (* 10 n) (* 5 n) "outline" "red"))
                                                      (/ TAM 2) (/ TAM 2)
                                                      (dibujar-elipses (sub1 n))
                                                      )]))


;25)


(define (g n) (/ 1 (sqr n)))

(define (g2 n) (cond [(zero? n) 0]
                     [else (+ (g n) (g2 (sub1 n)))]))


(define (aprox-pi n) (sqrt (* 6 (g2 n))))

