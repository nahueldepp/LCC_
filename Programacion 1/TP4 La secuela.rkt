;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |TP4 La secuela|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| TP 4: la secuela|#

;9)

(define-struct Auto [ mod año don renop])
;Auto es (String, Number, String, Number)
;Interpretación: El primer elemento es el modelo del auto,el segundo es el año de fabricación del modelo, el tercero
;refiera a si usa nafta o gasoil y el quiento refiere al rendimiento que el modelo posee al ser 0km

(define PEAJE 50)

(define PRECIO-N 19);precio por litro de nafta

(define PRECIO-D 17);precio por litro de gasoil



;rendimiento: Auto -> Number
;recibe el año del auto y el rendimiento optimo y calcula la reducción del rendimiento

(check-expect (rendimiento (make-Auto "FIAT" 2003 "nafta" 10)) 8.5)

(check-expect (rendimiento (make-Auto "FIAT" 2019 "nafta" 10)) 9.8)

(define (rendimiento s ) (cond [(> 1 (- 2023 (Auto-año s))) (Auto-renop s) ]
                               [(and (< 1 (- 2023 (Auto-año s))) (<= (- 2023 (Auto-año s)) 5)) (* (Auto-renop s) 0.98)]
                               [(and (< 6 (- 2023 (Auto-año s))) (<= (- 2023 (Auto-año s)) 10)) (* (Auto-renop s) 0.94)]
                               [(and (< 10 (- 2023 (Auto-año s))) (<= (- 2023 (Auto-año s)) 15)) (* (Auto-renop s) 0.90)]
                               [(< 15 (- 2023 (Auto-año s))) (* (Auto-renop s) 0.85)]
                               
                               ))
;peaje: Number -> Number
;recibe la cantidad de kilometros a recorrer y si km=>100 , entonces se toma el mayor entero
;menor o igual al cociente entre km y 100 y se lo multiplica por el peaje.

(check-expect (peaje 500) 250)

(check-expect (peaje 20) 0)


(define (peaje km) (if (<= 100 km )
                       (* (floor (/ km 100)) PEAJE)
                       0
                       ))

;nafodie: Auto -> Number
;recibe si el auto usa diesel o nafta y devuelve el precio correspondiente a cada uno.

(check-expect (nafodie (make-Auto "FIAT" 2003 "nafta" 10)) 19)
(check-expect (nafodie (make-Auto "FIAT" 2003 "diesel" 10)) 17)

(define (nafodie s) (if (string=? (Auto-don s) "nafta")
                        PRECIO-N
                        PRECIO-D)
  )
;costo-viaje: Struct Number -> Number
;recibe una estructura Auto y una cantidad de kilometros a recorrer y calcula el costo de combustible
(define (costo-viaje s km) (+ (* (/ km (rendimiento s)) (nafodie s)) (peaje km)))

;**************************************

;10)

(define-struct Estudiante [nombre promedio asis])
;Estudiante es (String, Number ; Number)
;interpretación: el primer elemento es el nombre del estudiante, el segundo es el promidio de sus notas
; y el tercero representa su asistencia

;condicion: Struct -> String
;recibe una struct Estudiante y si:
;un dato es el esperado, devuelve "Tipo de dato invalido"
;sino, dependiendo de ciertas condiciones devuelve "Libre", "Regular" o "Promovido"

(check-expect (condicion (make-Estudiante "Nahuel" 8 30)) "Libre")

(check-expect (condicion (make-Estudiante "Nahuel" 8 60)) "Promovido/a")

(check-expect (condicion (make-Estudiante "Nahuel" 10 100)) "Promovido/a")

(check-expect (condicion (make-Estudiante 8 "nahuel" 50)) "Tipo de dato invalido")

(define (condicion s) (if (valido? s)
                       (cond [(< (Estudiante-asis s) 60) "Libre"]
                             [(< (Estudiante-promedio s) 6) "Libre"]
                             [(< (Estudiante-promedio s) 8) "Regular"]
                             [#t "Promovido/a"]
                            )
                       "Tipo de dato invalido"))


;valido?: Estudiante -> Boolean
;recibe una estructura  y si es una de tipo Estudiante devuelve #t
(define (valido? s) (and (Estudiante? s) (string? (Estudiante-nombre s)) (<= (Estudiante-promedio s) 10)(number? (Estudiante-promedio s))
                        (<=(Estudiante-asis s) 100) (number? (Estudiante-asis s))
                        ))


;11)

(define-struct Casa [prop direc sup zona])
;Casa es (String, String, Number, Number)
;Interpretación: El primer elemento representa el propietario, ell segundo la dirección de la casa, el tercero la superficie
; en metros cuadrados y el cuerto la zona en la que esta la casa.

(define ZONA-A 20000)
(define ZONA-B 15000)
(define ZONA-C 10000)
(define ZONA-D 5000)


;venta: Estudiante -> String
;recibe una estructura Casa y devuelve un texto particular dependiendo de si: el monto es mayor o menor a 1000000
; si la zona no esta registrada, si se ingresaron los datos de manera incorrecta.



(define (venta s) (if (Casa? s )
                      (cond[ (and (< (monto s) 1000000) (or(= (Casa-zona s) ZONA-A)(= (Casa-zona s) ZONA-B)(= (Casa-zona s) ZONA-C)(= (Casa-zona s) ZONA-D))) 
                          (string-append "El señor/a " (Casa-prop s) " recibirá " (number->string (*(monto s)0.97)) " pesos por la venta de su
                                             propiedad ubicada en la calle " (Casa-direc s))]
                           
                          [(or(= (Casa-zona s) ZONA-A)(= (Casa-zona s) ZONA-B)(= (Casa-zona s) ZONA-C)(= (Casa-zona s) ZONA-D))
                           (string-append "El señor/a " (Casa-prop s) " recibirá " (number->string (*(monto s)0.95)) " pesos por la venta de su
                                             propiedad ubicada en la calle " (Casa-direc s))]
                          [else  "No se puede calcular el precio de venta por no disponer de los valores del
                                  metro cuadrado para la zona solicitada"]
                          )
                      "Tipo de dato incorrecto")
  )
                      
                             

                            
                   
(define (monto s) (* (Casa-sup s) (Casa-zona s)))


;12)

(define-struct Persona [nom/ape peso unip estatura unie])
;Persona es (String, Number, String, Number String)
;Interpretación:
;Primer elemento: nombre y apellido
;Segundo elemneto: Escalar del peso
;Tercer elemento: Unidad de peso
;cuarto: Escalar de estatura
;quinto: Unidad de estatura


;IMC: Persona-> String
;recibe una estructura Persona y calcula el indice de masa corporal de esa persona

(check-expect (IMC (make-Persona "Nahuel Deppen" 71.8 "kg" 1.70 "m")) "IMC: 24.8")

(check-expect (IMC (make-Persona "Nahuel Deppen" 71800 "g" 1.70 "m")) "IMC: 24.8")

(check-expect (IMC (make-Persona "Nahuel Deppen" 71.8 "kg" 170 "cm"))"IMC: 24.8")

(check-expect (IMC (make-Persona "Nahuel Deppen" 71800 "g" 170 "cm"))"IMC: 24.8")

(define (IMC s) (if (Persona? s)
                    (cond [(and (string=? (Persona-unip s) "kg")(string=? (Persona-unie s) "m"))
                          (string-append "IMC: " (number->string-digits (/ (Persona-peso s) (sqr(Persona-estatura s)))1)) ]
                          [(string=? (Persona-unip s) "kg") 
                           (string-append "IMC: "(number->string-digits (/ (Persona-peso s) (sqr(/ (Persona-estatura s) 100))) 1))]
                          [(and(string=? (Persona-unip s) "g" ) (string=? (Persona-unie s) "m"))
                          (string-append "IMC: " (number->string-digits (/ (/ (Persona-peso s) 1000)  (sqr (Persona-estatura s))) 1))]
                          [else (string-append "IMC: " (number->string-digits (/ (/ (Persona-peso s) 1000) (sqr (/(Persona-estatura s) 100))) 1))]
                          )
                    "Tipo de dato invalido")
  )


