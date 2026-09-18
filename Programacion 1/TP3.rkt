;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname TP3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; interpretar: Estado -> Image
; dado un estado, devuelve la imagen a mostrar por el programa
;
;
;-----------CONSTANTES----------------------------
(define RADIO 20)
(define ANCHO 300)
(define ALTO 300)
(define COR-X (/ ANCHO 2))
(define COR-Y (/ ALTO 2))
(define DELTA 3)
;-------------------------------------------------
 ;interpretar: String->Estado
(define
   (interpretar s)
                 (place-image (circle RADIO "solid" s) COR-X COR-Y (empty-scene ANCHO ALTO)))

(check-expect (interpretar "blue") (place-image (circle RADIO "solid" "blue") COR-X COR-Y (empty-scene ANCHO ALTO)))

;manejarteclado: Estado String->Estado 
(define (manejarteclado  s k) (cond [(key=? k "a") "blue"]
                                   [(key=? k "r") "red"]
                                   [(key=? k "g") "green"]
                                   [(key=? k "b") "black"]
                                   [else s]
                                   ))

(check-expect (manejarteclado "blue" "a") "blue") 

;(big-bang "blue"         
;  [to-draw interpretar]
 ; [on-key manejarteclado])
;/////////////////////////////////////////////////////////////////////////////////////////////////
;1)

; interpretar : Number -> Estado
; transforma el estado del sistema en una imagen a mostrar a través
; de la cláusula to-draw

(define  (radiocir n)
  (place-image (circle n "solid" (tamaño-color n))  COR-X COR-Y (empty-scene ANCHO ALTO)))

;tamaño-color: Number->String
;depending the value of n, it would give a specific color

(define (tamaño-color n)(cond [(and (< 0 n)(<= n 50)) "yellow"]
                                       [(and (< 50 n)(<= n 100 ))"red"]
                                       [ (< 100 n)"green"]
                                       [else "blue"]))



;decrementar: Estado->Estado
;si n>0 resta 1, si n=0 suma 100

(define (decrementar n) (if (< 0 n )
                            (- n 1)
                            (+ n 100)
                            ))
;Incrementar: number-> Estado
;toma n y devuelve n+1

(define (incrementar n ) (if (and (> (/ ANCHO 2) n) (> (/ ALTO 2)  n))
                           (+ n 1)
                           (- n (/ ANCHO 2))))

;terminar?: Estado->boolean
;si n>110 o n<10 la función indica verdadero, lo que termina el programa

(define (terminar? n) (or (< 110 n ) (< n 10)) )

(define (digito d) (cond [(number? d) (* 10 d)]
                         [else 11]))

;(big-bang 11
;  [to-draw radiocir]
 ; [on-tick incrementar ]
;  [stop-when terminar?]
;  )
;///////////////////////////////////////////////////////////////////////////////////////////////////////

#|EJERCICIO 4|#

;inter: number->image
;transforma el estado del sistema en una imagen a mostrar (circulo) 

(define (inter   n) (place-image (circle RADIO "solid" "red" )   COR-X n (empty-scene ANCHO ALTO)))

;mover-y: number string -> number 
(define (mover-y  n  d) (cond [(key=? d "up" ) (- n DELTA)]
                             [(key=? d "down")(+ n DELTA)]
                           
                             [(= (string-length d ) 1) (/ ALTO 2)]
                             [else n]))
 

(define (mouse-handler n x y event) (cond [(string=? event "button-down") y]
                                          [else n]))

(big-bang  (/ ALTO 2)
  [to-draw inter]
  [on-key mover-y]
  [on-mouse mouse-handler]
  )

;///////////////////////////////////////////////////////////////////////////////////////////
;5)

;circulo-cen: String-> image
;recibe un color y devuelve un circulo de ese color

(define (circulo-cen color)
                           (place-image (circle (* 3 RADIO) "solid" color)  COR-X COR-Y (empty-scene ANCHO ALTO)))


(define (color-tik estado) (cond [(string=? estado "yellow") "red" ]
                                 [(string=? estado "red")"green"]
                                 [(string=? estado "green") "blue"]
                                 [(string=? estado "blue")"yellow"]))

#|(big-bang "yellow"
  [to-draw circulo-cen]
  [on-tick color-tik 2])
|#
;////////////////////////////////////////////////////////////////////////////////////////////////////////

;6)


(define ANCHO2 800)
(define ALTO2 60)
(define ALTO-FUENTE 20)
(define COLOR "indigo")


;texto-imagen: String -> Image
;recibe un string (estado) y la imprime en la pantalla como una imagen
;
(define (texto-imagen texto ) (place-image/align (text texto ALTO-FUENTE COLOR )
                                             0 0 "left" "top" (empty-scene ANCHO2 ALTO2 )))

;escribir:String String -> String
;la funcion recibe un esatado (string) y una tecla (string) y:
;si recive una letra la añade al string previo
;si recive un numero, lo vuelve un string y lo añade al texto previo
;si recive la tecla suprimir, devuelve el texto previo menos un caracter

(define (escribir  texto k ) (cond [(string=? k "\b") (substring texto 0 (- (string-length texto) 1))]
                                  [(string? k) (string-append  texto k  ) ]
                                  [(number? k) (string-append  texto (number->string k) )]
                                  
                                  [else texto])
  )


#|(big-bang " "
    [to-draw texto-imagen]
    [on-key escribir]
  )|#



;/////////////////////////////////////////////////////////////////////////////////////////////////

;7)

;-----------CONSTANTES------------------
(define AUTO (rectangle 65 35 "solid" "red") )
(define ANCHO3 500)
(define ALTO3 100)
(define DIS 1)
(define DIS-TICK (* 3 DIS))
(define DIS-D (* 20 DIS))
(define DIS-I (* 20 DIS))
;----------------------------------------


;imagen-a: Number-> Image
;recibe un número x y devuelve la imagen de un rectangulo en un espacio a una altura horizontal de x.

(define (imagen-a x)(place-image/align AUTO (+ 65 x) (/ ALTO3 2) "right" "center" (empty-scene ANCHO3 ALTO3)))

;auto-tick: Number->Number
;recibe un estado (número) y devuelve otro estado(número)
;la funcion recibe la posición x de AUTO le suma 3 pixeles. cuando llega al borde de la pantalla, devuelve x=435
(define (auto-tick x  ) (cond [(and (<= 0 x) (< x (- ANCHO3 65)))  (+ DIS-TICK x)]
                               
                               [ else 435] 
                                ) )

;key-handler: Number String -> Number
;recibe un numeró y una tecla (string) y si:
;es la barra espaciadora, devuelve 0
;es la flecha izquierda, devuelve la posición x-20
;es la flecha derecha, devuelve la posición x+20

(define(key-handler x k) (cond [(key=? k " ") 0]
                               [(key=? k "left" ) (- x DIS-I)]
                               [(key=? k "right") (+ x DIS-D)]
                               [else x]))

(define (click n x y k ) (cond [(string=? k  "button-down") x]
                                        [else n]
                                        ))

(big-bang 0
  [to-draw imagen-a]
  [on-mouse click]
  [on-tick auto-tick]
 [on-key key-handler]

  )

;////////////////////////////////////////////////////////////////////////////////////////////////

;8)

;-------CONSTANTES------------

(define ANCHO4 500)
(define ALTO4 300)
(define TE 10)
(define ESTRELLA (star TE "solid" "white"))
(define FONDO (rectangle ANCHO4 ALTO4 "solid" "dark blue"))
(define REDUCIR 3/100)
;------------------------------  

;fondo: Image-> Estado
;recibe una imagen (FONDO) y devuelve la misma imagen
(define (fondo n) n)

;tamaño-estrella: Estado Number Number -> Estado
;recibe una imegen y las corde x e y del mouse al hacer click, luego en base a la cordenada x,
;devuelve una imagen con la estrella en (x,y) escalada segun x.

(define (tamaño-estrella n x y) (place-image (scale (* 1/3 (log x)) ESTRELLA) x y n))

;dentro-marco: Number Number -> Boolean
;dadas las coordenadas (x,y) del mouse, devuelve #true si es posible dibujar una estrella o #false si no es posible.

(define (dentro-marco x y)(and (< (* 1/3 (log x) TE) x)
                               (<= x (- ANCHO4 (* 1/3 (log x) TE))) 
                               (< (* 1/3 (log x) TE) y)
                               (<= y (- ALTO4 (* 1/3 (log x) TE)))
                               ))

;estrella: Estado Number Number String -> Estado
;recibe al hacer click coloca una estrella en el fondo 
(define (estrella n x y c) (cond [(and (string=? c "button-down") (dentro-marco x y)) (tamaño-estrella n x y)]
                                 
                                 [else n]))
(define (borrador n k) (cond [(key=? k "\b") FONDO]
                             [else n]))

#|(big-bang FONDO
    [to-draw fondo]
    [on-mouse estrella]
    [on-key borrador]
  )|#


;////////////////////////////////////////////////////////////////////////////////////////////////////////




