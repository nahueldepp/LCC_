;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |TP 1 p1|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
(define CUA 60)
(define DESC 10/100)

(define (Precio x) (if (> 4 x)
                       (* CUA x)
                       (- (* CUA x)(* CUA x DESC ))))

#| Practica 1 parte 1|#

;1)Ancha o angosta 
(define (AOA x) (if (> (image-width x) (image-height x))
                    "Ancha"
                    "Angosta"))

;2)

(define (AoAoC x) (if (> (image-width x) (image-height x))
                    "Ancha"
                    (if (= (image-width x) (image-height x))
                        "Cuadrado"
                        "Angosto")))
;3)4)
(define (QTrian? a b c)(if(= 180 (+ a b c))
                          (if (= 60 a b c)
                            "Equilatero"
                            (if (or (= a b)(= a c)(= c b))
                                    "Isoseles"
                                    "Escaleno"))
                          "No es un triangulo"))
;5)
(define PC 60)
(define PL 8)
(define DL 15/100)
(define DC 10/100)

;L>5 C>4
(define (caso1 c l) (+ (* l (- PL (* PL DL))) (* c (- PC (* PC DC)))))
;L>5 C<4
(define (caso2 c l) (+ (* l (- PL (* PL DL))) (* c PC)))
;L<5 C<4
(define (caso3 c l) (+ (* l PL) (* c PC)))
;L<5 C>4
(define (caso4 c l) (+ (* l PL) (* c (- PC (* PC DC)))))

(define (total c l) (if (and (>= l 5) (>= c 4))
                        (caso1 c l)
                        (if (and (>= l 5) (<= c 4))
                            (caso2 c l)
                            (if (and (<= l 5) (<= c 4))
                                (caso3 c l)
                                (caso4 c l)))))

;7)(
(define (pitagorica a b c)(= (expt c 2) (+(expt b 2) (expt a 2))))
(define (pitagorica? x y z) (or (pitagorica x y z) (pitagorica x z y)
                                 (pitagorica y z x) (pitagorica y x z)
                                 (pitagorica z x y) (pitagorica z y x)))
(define (pitagorica?? x y z) (if (pitagorica? x y z)
                                 (string-append "Los números " (number->string x) "," (number->string y) " y " (number->string z)
                                                " son una terna pitagorica")
                                 "No son una terna pitagorica"))
;9)
(define (collatz n) (if (even? n)
                        (/ n 2)
                        (+ (* n 3) 1)))
#| BANDERAS|#

(define T 2)
 (define ejemplo (place-image (rectangle (* T 90) (* T 30) "solid" "red")
                              45 15
                              (place-image (circle 10 "solid" "blue")
                                           45 45
                                           (empty-scene 90 60))))
 ;a)peru
(define peru (place-image (rectangle 30 60 "solid" "white")
                          45 30
                          (rectangle 90 60 "solid" "red")))
;b) italia
(define itali (place-image (rectangle 30 60 "solid" "dark green")
                           15 30
                           (place-image (rectangle 30 60 "solid" "white")
                                        45 30
                                        (rectangle 90 60 "solid" "red"))))
;c) 

(define (vertical x y z) (place-image (rectangle (* T 30) (* T 60) "solid" x)
                           (* T 15) (* 30 T)
                           (place-image (rectangle (* T 30) (* T 60) "solid" y)
                                        (* T 45) (* T 30)
                                        (rectangle (* T 90) (* T 60) "solid" z))))
;d)
(define alemania (place-image (rectangle 90 20 "solid" "black")
                              45 10
                              (place-image (rectangle 90 20 "solid" "red")
                                           45 30
                                           (rectangle 90 60 "solid" "yellow"))))
;f)
(define (hori x y z) (place-image (rectangle (* T 90) (* T 20) "solid" x)
                              (* T 45) (* T 10)
                              (place-image (rectangle (* T 90) (* T 20) "solid" y)
                                           (* T 45) (* T 30)
                                           (rectangle (* T 90) (* T 60) "solid" z))))
;g)
(define (bandera x y z s) (if (string=? s "vertical")
                              (vertical x y z)
                              (hori x y z)))
;i)

(define TRIANGULO (rotate 30 (triangle 50 "solid" "dark green")))
(define ESTRE (star 10 "solid" "yellow"))

(define A 45)
(define B 30)

(define (banderass x y z s) (place-image ESTRE
                             A B          (bandera x y z s)))
