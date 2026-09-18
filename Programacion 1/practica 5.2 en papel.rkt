;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |practica 5.2 en papel|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| SISTEMA DE CONTRASEÑAS|#

;----------------------------------------------------------------------------------------
(define-struct Usr [login pass permiso])
;Usr es (String, String, Number)
;Un elemento Usr representa el registro de una persona con acceso al sistema
; operativo donde
;login: es el nombre identificador de la persona,
;pass: es la contraseña de acceso,
;permiso: es el identificador de los permisos en el sistema que tiene la persona
; Si tiene permiso de administración, el valor es 0; en otro caso es 1.

; 0 es el identificador de permisos de administración del sistema
(define ADMIN 0)
;1 es el identificador de permisos de uso básico del sistema
(define USRPERMISO 1)

;Constantes que pueden ser usadas para casos de prueba.
(define ANA (make-Usr "ana" "12345678" ADMIN))
(define LUIS (make-Usr "luis" "12345678" USRPERMISO))
(define MARTA (make-Usr "marta" "R34dlsoA" ADMIN))
(define L1 (list ANA LUIS))
(define L2 (list ANA LUIS MARTA))

;1)

;cambioClave: Usr String ->Usr
;Esta función recibe el registro de una persona usuaria del sistema y una contraseña.
;Si la contraseña recibida es diferente a la que tiene el registro y tiene 8
; o más caracteres, la función cambia la contraseña en el registro y lo devuelve;
; en caso contrario, devuelve el registro sin modificaciones.

(check-expect (cambioClave ANA "aaa") ANA)
(check-expect (cambioClave ANA "12345678") ANA)
(check-expect (cambioClave ANA "abcdefghi") (make-Usr "ana""abcdefghi" ADMIN))

(define (cambioClave usr s) (if (and (>=(string-length s) 8) (not (string=? s (Usr-pass usr))))
                                (make-Usr (Usr-login usr) s (Usr-permiso usr))
                                usr)
  )

;2)

;agregaUsr: String String Number List(Usr) ->List(Usr)
;Esta función agrega un nuevo registro de una persona con acceso al sistema.
;Para esto recibe un nombre identificador de la persona, una contraseña de acceso,
; un identificador de permisos y la lista de registros de personas con acceso
; al sistema. Si no existe un registro con el identificador recibido, agrega uno
; nuevo a la lista, con la correspondiente información, y la devuelve;
; en caso contrario, no lo agrega y devuelve la lista original.

(check-expect (agregarUsr "marta" "R34dlsoA" ADMIN L1) L2)
(check-expect (agregarUsr "luis" "R34dlsoA" ADMIN L1) L1)
(check-expect (agregarUsr "marta" "R34dlsoA" ADMIN empty) (list MARTA))

(define (agregarUsr login pass permiso l) (local
                                            ((define (esta? a) (string=? login a ))
                                             )
                        ;-IN-

  (cond [(empty? l)  (cons (make-Usr  login pass permiso) '())]
                                                   
        [else  (if (cons? (filter esta? (map Usr-login l)))
                   l
                   (foldr cons (list (make-Usr login pass permiso)) l))]
        )))
                                                   
                                                 
                                                   


;3)

;esAdmin?: Usr ->Boolean
;Esta función recibe el registro de una persona usuaria del sistema y determina
; si tiene premisos de administración.

(check-expect (esAdmin? ANA) #t)
(check-expect (esAdmin? LUIS) #f)

(define (esAdmin? usr)  (= (Usr-permiso usr) ADMIN))

;-----------------------------------------------------------------------------------



;,,,,,,,,,,,,,.
;1)
;,,,,,,,,,,,,,,

add1
;cantAdmin: List(Usr) ->Number
;Esta función recibe una lista de registro de personas usuarias del sistema y
; devuelve la cantidad de personas que tienen permisos de administración.

(check-expect (cantAdmin L2) 2)
(check-expect (cantAdmin (list LUIS)) 0)
(check-expect (cantAdmin empty) 0)

; Version mas simple
(define (uno x) 1)
;(define (longitud l) (suma (map uno l)))
; Version con unico recorrido
; foldr: (X, Y -> Y), Y, List(X) -> Y
(define (inc1 x n) (+ n 1))
(define (longitud-fold l) (foldr inc1 0 l))

(define (cantAdmin l) (foldr inc1 0 (filter esAdmin? l)))

; b)
(define (contar-admins usr n) (if (esAdmin? usr) (+ n 1) n))
(define (cantAdmin-fold l) (foldr contar-admins 0 l))

;,,,,,,,,,,,,,,,,,,,
;2)
;;;;;;;;;;;;;;;;;,,,


;bloquearClaves: List(Usr) ->List(Usr)
;Esta función recibe una la lista de registros de personas con acceso al sistema,
; cambia la clave de cada registro a "nula" y devuelve la lista modificada.

(check-expect (bloquearClaves L1) (list (make-Usr "ana" "nula" ADMIN)
(make-Usr "luis" "nula" USRPERMISO)))
(check-expect (bloquearClaves empty) empty)

(define (bloquearClaves l) (cond [(empty? l) '()]
                                 [else (map cambiar l)])
  )

(define (cambiar usr) (make-Usr (Usr-login usr) "nula" (Usr-permiso usr)))


;,,,,,,,,,,
;3)
;,,,,,,,,,,


;idLargos: List(Usr) ->List(String)
;Esta función recibe una lista de Usr y devuelve la lista de los identificadores
;con más de 3 caracteres.
(check-expect (idLargos (list ANA LUIS MARTA)) (list "luis" "marta"))
(check-expect (idLargos (list ANA)) empty)

(define (mayor3? a) (> (string-length a) 3))

(define (idLargos l) (filter mayor3? (map Usr-login l)))

;,,,,,,,,,,
;4)
;,,,,,,,,,,

;sumNumericos: List(String) ->Number
;Recibe una lista de Strings y devuelve la suma todos aquellos que son enteros no
;negativos.
(check-expect (sumNumericos (list "12-9" "12" "sol" "1nos" "33.5" "10")) 22)
(check-expect (sumNumericos (list "-12" "sol" "33.5")) 0)
(check-expect (sumNumericos empty) 0)

(define (sumNumericos l) (foldr + 0 (map string->number (filter string-numeric? l))))

;,,,,,,
;5)
;,,,,,,

;infAn: List(Number) Number ->List(Number)
;infAn recibe una lista de números y un número n; y devuelve la lista de números
;inferiores a n.
(check-expect (infAn (list 1 2 3 4) 3) (list 1 2))
(check-expect (infAn (list 1 2 3 4) 1) empty)

(define (infAn l n)
  (local (
          ;mayorAn?: Number Number -> Boolean
          ;dado dos números reales n y m, devuelve #t si m< n
          (define (mayorAn? m) (< m n))
          )
        ;-IN-
          (filter mayorAn? l)
          
          ))

;,,,,,
;6)
;,,,,,

;minimo: List(Number) ->Number
;Esta función recibe una lista NO vacía de números cualesquiera y devuelve el menor.
(check-within (minimo (list -1.6 5 3 -80 6 57.9 0)) -80 0.000000000000001)

(define (minimo l) (foldr min +inf.0 l))

;,,,,,
;7)
;,,,,,

;primeroPares: List(Number) ->List(Number)
;Esta función recibe una lista NO vacía de enteros y los ordena ubicando primero
;los pares y luego los impares.
(check-expect (primeroPares (list 9 -5 6 3 -2 8 0 12 100 7))
(list 6 -2 8 0 12 100 9 -5 3 7))

(define (primeroPares l) (foldr cons (filter odd? l) (filter even? l)))

                              