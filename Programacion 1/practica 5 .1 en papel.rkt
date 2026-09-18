;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |practica 5 .1 en papel|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
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

(define (agregarUsr login pass permiso l) (cond [(empty? l)  (cons (make-Usr  login pass permiso) '())]
                                                   
                                                [else (if (string=? login (Usr-login (first l)))
                                                          l
                                                           (cons (first l)(agregarUsr login pass permiso (rest l)))
                                                   
                                                 )]
                                                   ))


;3)

;esAdmin?: Usr ->Boolean
;Esta función recibe el registro de una persona usuaria del sistema y determina
; si tiene premisos de administración.

(check-expect (esAdmin? ANA) #t)
(check-expect (esAdmin? LUIS) #f)

(define (esAdmin? usr)  (= (Usr-permiso usr) 0))

;4)

;cantAdmin: List(Usr) ->Number
;Esta función recibe una lista de registro de personas usuarias del sistema y
; devuelve la cantidad de personas que tienen permisos de administración.

(check-expect (cantAdmin L2) 2)
(check-expect (cantAdmin (list LUIS)) 0)
(check-expect (cantAdmin empty) 0)

(define (cantAdmin l) (cond [(empty? l) 0]
                            [else (if (= (Usr-permiso (first l)) 0)
                                  (+ 1 (cantAdmin (rest l)))
                                  (+ 0 (cantAdmin (rest l)))
                                  )]
                            ))

;5)

;eliminaUsr: String List(Usr) ->List(Usr)
;Esta función recibe un identificador de persona en el sistema y la lista de
; registros de personas con acceso al sistema. Si existe un registro con tal
; identificador lo elimina de la lista y devuelve la lista resultante; en caso
; contrario devuelve la lista sin modificaciones.


(check-expect (eliminaUsr "marta" L2) L1)
(check-expect (eliminaUsr "daniel" L2) L2)
(check-expect (eliminaUsr "marta" empty) empty)

(define (eliminaUsr s l) (cond [(empty? l) '()]
                               [else (if (string=? s (Usr-login (first l)))
                                         (rest l)
                                         (cons (first l)(eliminaUsr s (rest l)))
                                         )]))

;6)

;bloquearClaves: List(Usr) ->List(Usr)
;Esta función recibe una la lista de registros de personas con acceso al sistema,
; cambia la clave de cada registro a "nula" y devuelve la lista modificada.

(check-expect (bloquearClaves L1) (list (make-Usr "ana" "nula" ADMIN)
(make-Usr "luis" "nula" USRPERMISO)))
(check-expect (bloquearClaves empty) empty)

(define (bloquearClaves l) (cond [(empty? l) '()]
                                 [else (cons (make-Usr (Usr-login (first l)) "nula" (Usr-permiso (first l)))
                                             (bloquearClaves (rest l)))])
  )

;7)

;intercala: Lista(Any) Lista(Any) ->Lista(Any)
;Esta función intercala los elementos de dos listas dadas.

(check-expect (intercala (list 1 2 3) (list "A" "B")) (list 1 "A" 2 "B" 3))
(check-expect (intercala (list "A" "B") (list 1 2 3) ) (list "A" 1 "B" 2 3))

(define (intercala l1 l2) (cond [(empty? l1) l2]
                                [(empty? l2) l1]                         
                                [else (cons (first l1)(cons (first l2) (intercala (rest l1) (rest l2))))])
  )

;8)

;ultimo : List (Any) ->Any
;Devuelve el último elemento de una lista NO vacía.

(check-expect (ultimo (list 1 2 3)) 3)
(check-expect (ultimo (list 1 2)) 2)
(check-expect (ultimo (list 1)) 1)

(define (ultimo l) (cond [(empty? (rest l)) (first l)]
                         [else (ultimo (rest l))]
                         ))

;9)

;listaCapicua:List(Number) ->Boolean
;Determina si la secuencia de una lista de números de un dígito forman un número
;capicúa.

(check-expect (listaCapicua (list 1)) #t)
(check-expect (listaCapicua (list 1 1)) #t)
(check-expect (listaCapicua (list 1 2 3 2 1)) #t)
(check-expect (listaCapicua (list 1 2)) #f)
(check-expect (listaCapicua (list 1 2 3)) #f)
(check-expect (listaCapicua (list 1 2 3 4 1)) #f)
(check-expect (listaCapicua (list 1 2 3 4 5 6 7 8)) #f)

(define (listaCapicua l ) (compararl l (reverse l)))



(define (compararl l1 l2) (cond [(and (empty? l1) (empty? l2)) #t]
                                [(= (first l1) (first l2)) (compararl (rest l1) (rest l2)) ]
                                [else #f])
  )
