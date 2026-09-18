;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |estructuras, teoria|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))

;promedio: number number -> Number
;dados p1 y p2 (notas del primer y segundo parcial respectivamente) devuelve el promedio.

(define (promedio p1 p2) (/ (+ p1 p2) 2))

;make-Nota: String Number Number Number -> Nota
;Donde:
;nombre: nombre de la persona
; p1: La nota del primer parcial
; p2: La nota del segundo parcial
; promedio: nota promedio de los dos parciales

(define-struct Nota [nombre p1 p2 promedio])
;Nota es (String Number Number Number)
;interpretación: un elemento en nota, representa el nombre del alumno, las notas de
;su primer y segundo parcial, junto a su promedio.

(define D-43478/7 (make-Nota "Nahuel Deppen" 10 10 10))

(define D-43479/7 (make-Nota "Martinez Martinez" 5 3 4))

(define (mayor-promedio a b) (if (< (Nota-promedio a) (Nota-promedio b))
                                  (string-append (Nota-nombre b) " tiene mejor promedio")
                                  (string-append (Nota-nombre a) " tiene mejor promedio")
                                  ))

(define (promedio-mayor-8? a) (<= 8 (Nota-promedio a)))