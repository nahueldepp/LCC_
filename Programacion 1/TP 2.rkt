;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |TP 2|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
#|Practica 2|#

;1)
;representamos distancia mediante números
; (Number,Number)->Number
;recibe un par ordenado (x,y) y devuelve su distancia al origen (0,0) con un número real
;Input: (1,1), Output: sqrt 2
; Input: (sqrt 2, sqrt 2), Output: 2

(define (distancia-origen x y) (sqrt (+ (sqr x) (sqr y))))

(check-expect (distancia-origen 1 0) 1)

;2)
;Representamos distancia mediante numeros reales
;(x1 y1 x2 y2)->dis(Number,Number,Number,Number)-> Number
;recibe un dos pares de numeros y devueve la distancia entre ambos puntos
;Input: (1,1,1,1) , Output: 0
;Input: (1,1,2,2), output: sqrt 2

(define (distancia-puntos x1 y1 x2 y2) (sqrt(+ (sqr(- x1 x2))(sqr(- y1 y2)))))

(check-expect (distancia-puntos 0 0 0 1) 1)

;3)
;representamos los volumenes con números reales
;Number->Number
;Recibe el valor de una arista y devuelve el volumen del cubo
;Input: 1 , Output: 1
;Input: 2, Outpu: 8

(define (vol-cubo x) (expt x 3))

(check-expect (vol-cubo 2) 8) 

;4)
;representamos el volumen de la figura con numeros reales
; l a a-> area ;Number Number NUmber-> Number
;recibe los valores de tres aristas y devuleve el volumen de la figura
;Input: (1,2,3), Output: 22
;Input: (1,1,1); Output: 6

(define (area-prisma x1 x2 x3) (+(* 2 x1 x2 )(* 2 x1 x3)(* 2 x2 x3))) 


;5)
;representamos una palabra con un "-" en una posicion i-esima
;(str; x)->str, String Number-> String
;recine un string y un numero real y coloca un "-" en la i-esima posicion
;Input: ("hola",2), Output: "ho-la"
;Input: ("chau",3), Output: "Cha-u"

(define (string-insert str x) (string-append (substring str 0 x) "-" (substring str x (string-length str))))

;6)
;representamos el ultimo caracter de una cadena como un string de un caracter
;String->String
;recibe un string y devuelve el ultimo caracter del string
;Input: "hola" , Output: "a"

(define (string-last x)(string-ith x (- (string-length x) 1) ))

;7)
;representamos el string como "  "
;String->String
;recibe un string y devuelve el string sin su ultimo caracter
;Input: "hola", Output:"hol"

(define (string-remove-last str) (substring str 0 (- (string-length str ) 1)))



; Representamos temperaturas mediante números
; far->cel : Number -> Number
; recibe una temperatura en Fahrenheit, devuelve su equivalente en Celsius
; entrada: 32, salida: 0
; entrada: 212, salida: 100
; entrada: 122, salida: 50
(define (far->cel f)
        (* 5/9 (- f 32)))


(check-expect (far->cel 32) 0)
(check-expect (far->cel 212) 100)
(check-expect (far->cel 122) 50)
(check-expect (string-remove-last "hol") "ho")
;9)

;representamos precios mediante numeros reales
;monto-persona: Number Number->>Number
;recibe el numero de cuotas que se van a pagar y el numero de amigos, devuelve el monto a pagar
;receives th number of friends and monthly fee and give the amount to pay
;input: (2,2), Output: $975

;descuento 2 amigos
(define d2a 10/100)
;descuento mas de dos amigos
(define d+2a 20/100)
;descuento 2 cuotas
(define d2c 15/100)
;descuento mas de dos cuotas
(define d+2c 25/100)
;precio de la cuota 
(define Cuo 650)

; 1 Persona 1 Cuaota 
(define caso1A Cuo )
; 1 Persona 2 Cuotas
(define (caso1B p c) (* p (- (* c Cuo) (* Cuo c d2c ) )))
; 1 persona 2 o mas cuotas
(define (caso1C p c) (* p (- (*  c Cuo) (* Cuo c d+2c))))
; 2 Personas 1 cuota
(define (caso2A p c ) (* p (- (* c Cuo) (* c Cuo d2a))))
; 2 personas 2 cuotas
(define (caso2B p c ) (* p (- (* c Cuo) (* Cuo c (+ d2a d2c)))))
;2 personas 3 o mas cuotas
(define (caso2C p c ) (* p (- (* c Cuo) (* Cuo c (+ d2a d+2c)))))
;3 o mas  personas 1 cuota
(define (caso3A p c) (* p (- (* c Cuo) (* Cuo c d+2a))))
;3 o mas personas 2 cuotas
(define (caso3B p c) (* p (- (* c Cuo) (* Cuo c (+ d+2a d2c)))))

(define (monto-persona p c) (cond [(and (= 1 p) (= 1 c)) caso1A]
                                  [(and (= 1 p) (= 2 c)) (caso1B p c)]
                                  [(and (= 1 p) (< 2 c)) (caso1C p c)]
                                  [(and (= 2 p) (= 1 c)) (caso2A p c)]
                                  [(and (= 2 p) (= 2 c)) (caso2B p c)]
                                  [(and (= 2 p) (< 2 c)) (caso2C p c)]
                                  [(and (< 2 p) (= 1 c)) (caso3A p c)]
                                  [(and (< 2 p) (= 2 c)) (caso2A p c)]))
                                  
;10)

;representamos valores positivos (si la persona es anemica) como "Anemia Positivo" y negativos como "Anemia Negativo"
; test-anemia: Number Number ->> String
; receives the age and amount of emoglobin, tell if the pasient have anemia or not

(define (test-anemia n str hem) (cond [(string=? str "día" ) (if (and (< hem 13)(<= n 31))
                                                                "Anamia Positivo"
                                                                "Anemia Negativo")]
                                      [(string=? str "mes" ) (if (and (< 1 n) (<= n 6))
                                                                (if (< hem 10)
                                                                    "Anemia Positivo"
                                                                    "Anemia Negativo")
                                                                (if (< hem 11)
                                                                    "Anemia Positivo"
                                                                    "Anemia Negtivo"))]
                                      [(string=? str "año" ) (if (and (< 1 n)(<= n 5))
                                                                (if (< hem 11.5)
                                                                    "Anemia Positivo"
                                                                    "Anemia Negativo")
                                                                (if (and (< 5 n)(<= n 10))
                                                                    (if (< hem 12.6)
                                                                        "Anemia Positivo"
                                                                        "Anemia Negativo")
                                                                    (if (< hem 13)
                                                                        "Anemia Positivo"
                                                                        "Anemia Negativo")))]))
(check-expect (test-anemia 1 "año" 11 ) "Anemia Positivo")

; 11)
;
;------------------------------------------------------------------------------------
; Number Number Number-> Boolean
;recibe 3 numeros reales y chequea si son autopromediables, si lo es, devuelve true

(define (autopromediable? a b c) (or (= a (/ (+ b c) 2))(= b (/ (+ a c)2))(= c (/ (+ b a) 2))))

;------------------------------------------------------------------------------------

(define (mos a b c) (if (autopromediable? a b c)
                        (* a b c)
                        (+ a b c)))
;12)
;Number Number-> String
;La funcion toma los valores de litros y nafta y devuelve el consumo en ciudad y ruta segun el tipo de nafta

;-------------------CONSTANTES----------------------------------
(define ACIUDAD2 8) ;AUTONOMIA en ciudad 8km/l con nafta grado 2
(define ARUTA2 11) ;Autonomia en la ruta 11km/l con nafta grado 2
(define EFI 10/100) ;Eficiencia de la nafta de grado 3
(define ACIUDAD3 (+ ACIUDAD2 (* ACIUDAD2 EFI))) ; Autonomia en la ciudad con nafta grqado 3
(define ARUTA3 (+ ARUTA2 (* ARUTA2 EFI))) ; Autonomia en la ruta con nafta grado 3
;---------------------------------------------------------------

(define (autonomia litros nafta) (if (= nafta 2)
                                     (string-append "Autonomía en ciudad: " (number->string (* ACIUDAD2 litros)) "km. "
                                                    "Autonomía en ruta: " (number->string (* ARUTA2 litros)) "km." )
                                     (string-append "Autonomía en ciudad: " (number->string (* ACIUDAD3 litros)) "km. "
                                                    "Autonomía en ruta: " (number->string (* ARUTA3  litros)) "km." )
                                     ))


