;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |TP 1 p2|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
(define (sgn2 x) (cond [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1]))

(sgn2 0)

#| Practica 1 P2 |#
 ;2)
    ; a)
(define (AoAoL x) (cond
                    [(< (image-width x) (image-height x)) "Angosta"]
                    [(> (image-width x) (image-height x)) "Ancha"]
                    [(= (image-width x) (image-height x)) "Cuadrada"]))
    ;b)
(define (triangulo a b c) (if (= 180 (+ a b c))
                                 (cond
                                   [(= 60 a b c) "Equilatero"]
                                   [(or (= a b)(= a c)(= c b)) "Isoceles"]
                                   [(not(or (= a b)(= a c)(= c b))) "escaleno"])
                               "No es un triangulo"))    
                                                          

    ;c)
(define (pitagorica? a b c) (cond
                              [(= (expt c 2) (+(expt b 2) (expt a 2)))
                               (string-append "Los números " (number->string a) "," (number->string b) " y " (number->string c)
                                                " son una terna pitagorica")]
                              [(= (expt a 2) (+(expt b 2) (expt c 2)))
                               (string-append "Los números " (number->string a) "," (number->string b) " y " (number->string c)
                                                " son una terna pitagorica")]
                              [(= (expt b 2) (+(expt a 2) (expt c 2)))
                               (string-append "Los números " (number->string a) "," (number->string b) " y " (number->string c)
                                                " son una terna pitagorica")]
                              [(not (= (expt b 2) (+(expt a 2) (expt c 2))))
                               (string-append "Los números " (number->string a) "," (number->string b) " y " (number->string c)
                                                " no son una terna pitagorica")]
                              ))
;4)
(define (imagesize x) (cond
                    [(< (* 2 (image-width x)) (image-height x)) "Muy Angosta"]
                    [(< (image-width x) (image-height x)) "Angosta"]
                    [(> (image-width x) (* 2 (image-height x))) "Muy Ancha"]
                    [(> (image-width x) (image-height x)) "Ancha"]
                    [(= (image-width x) (image-height x)) "Cuadrada"]))
;5)

(define (clasificar t) (cond [(<= t 0) "Muy frío (MF)"]
                             [(and (> t 0) (<= t 15)) "Frío (F)"]
                             [(and (> t 15) (<= t 25)) "Agradable (A)"]
                             [(> t 25) "Caluroso (C)"]))
;6)
(define (sgn4 x) (cond [(boolean=? x #t) 1]
                       [(boolean=? x #f) 0]))
;7)
; (sgn5 x) : Image->number
(define (sgn5 x) (cond [(string=? (AoAoL x) "Angosta") -1]
                       [(string=? (AoAoL x) "Ancha") 1]
                       [(string=? (AoAoL x) "Cuadrada")0]))
;8)
(define (sgn3 x) (cond [(number? x) (sgn2 x)]
                       [(string? x) (if (number? (string->number x))
                                    (sgn2 (string->number x))
                                    "La cadena no se puede convertir a un número")]))

(define (sgnT x) (cond [(or (string? x) (number? x)) (sgn3 x)]
                       [(boolean? x) (sgn4 x)]
                       [(image? x) (sgn5 x)]
                       
                       [#t "Clase no soportada por la función"]))
                       
