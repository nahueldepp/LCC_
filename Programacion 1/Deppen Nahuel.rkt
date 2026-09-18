;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |TRABAJO PRACTICO FINAL|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp")) #f)))
#| Trabajo Práctico Final - Tema 1

Integrantes:
- [Deppen, Nahuel]

|#

;.........................................................................................
;,,,,,,Ejercicio 1



;implica: Boolean Boolean -> Boolean
;dados dos valores booleanos, devuelve #t si p implica q.

(check-expect (implica #t #f) #f)
(check-expect (implica #f #f) #t)
(check-expect (implica #t #t) #t)
(check-expect (implica #f #t) #t)

(define (implica p q)  (or (and p q) (not (or p q)) (and (not p) q)))

;equivalente: Boolean Boolean -> Boolean
;dado dos valores booleanos, devuelve #t si son equivalentes

(check-expect (equivalente #t #t ) #t)
(check-expect (equivalente #t #f) #f)
(check-expect (equivalente #f #t) #f)
(check-expect (equivalente #f #f) #t)

(define (equivalente p q) (and (implica p q) (implica q p)))


;..........................................................................................

;,,,,,,,Ejercicio 2.


;ListV es:
;-'()
; (cons List(Boolean) ListV)
;Donde ListV es una lista de listas de booleanos



;agregar-t: List(boolean) -> List(Boolean)
;dada una lista agrega #t al principio

(check-expect (agregar-t (list #f)) (list #t #f))
(check-expect (agregar-t (list #t )) (list #t #t))

(define (agregar-t l) (cond [(empty? l) '()]
                          [else (cons #t l)]))

;agregar-ts:ListV -> Listv
;dada una Listv, agrega #t al principio de cada lista

(check-expect (agregar-ts (list (list #t) (list #f))) (list (list #t #t) (list #t #f)))
(check-expect (agregar-ts (list (list #f #t) (list #t #f))) (list (list #t #f #t) (list #t #t #f)))

(define (agregar-ts l) (map agregar-t l))


;agregar-f:List (Boolean) -> List (Boolean)
;dada una lista agrega #f al principio

(check-expect (agregar-f (list #t)) (list #f #t))
(check-expect (agregar-f (list #f)) (list #f #f))

(define (agregar-f l) (cond [(empty? l) '()]
                            [else (cons #f l)]))
;agregar-fs: Listv -> Listv
;Dada una Listv, agrega #f al principio de cada lista

(check-expect (agregar-fs (list (list #t) (list #f))) (list (list #f #t) (list #f #f)))
(check-expect (agregar-fs (list (list #f #t) (list #t #f))) (list (list #f #f #t) (list #f #t #f)))

(define (agregar-fs l) (map agregar-f l))
                               
;pegar: Listv -> Listv
;dada una lisv,pega una lista "agregar-fs" con una "agregar-ts"

(check-expect (pegar (list (list #t) (list #f))) (list (list #f #t) (list #f #f) (list #t #t) (list #t #f)))

(define (pegar l) (cond [(empty? l) '()]
                        [else (append (agregar-fs l) (agregar-ts l))]))

;valuaciones: N -> ListV
;dado un número natural n,
;genera todas las posibles valuaciones que existen con n variables proposicionales.


(check-expect (valuaciones 3) (list 
 (list #false #false #false)
 (list #false #false #true)
 (list #false #true #false)
 (list #false #true #true)
 (list #true #false #false)
 (list #true #false #true)
 (list #true #true #false)
 (list #true #true #true))
)

(define (valuaciones n) (cond [(= n 1) (list (list #f) (list #t))]
                              [else (pegar (valuaciones (sub1 n)))]))
                  
;............................................................................................

;,,,,,,Ejercicio 3



; A : List(Boolean) -> Boolean
;Proposición A

(define
  (A l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
  (equivalente (and (implica p1 p3)
                    (implica p2 p3))
               (implica (or p1 p2)
                        p3))))

 

;B: List(Boolean) -> Boolean
;Proposición B, ((p1 ^ p2)->p3) <-> ((p1->p3)^(p2->p3))

(check-expect (B (list #t #t #t)) #t)
(check-expect (B (list #t #f #f))#f)

(define
  (B l)
  (let ([p1 (first l)]
       [p2 (second l)]
       [p3 (third l)])
  (equivalente(implica (and p1 p2) p3)
              (and (implica p1 p3) (implica p2 p3)))))

;C: List(boolean)-> Boolean
;Proposición C , (-p1 v -p2)-> (p1^p2)

(check-expect (C (list #f #t)) #f)
(check-expect (C (list #t #t)) #f)

(define
  (C l)
  (let ([p1 (first l)]
        [p2 (second l)])
    (equivalente (or (not p1) (not p2)) (and p1 p2))))



;............................................................................................

;Ejercicio 4


;evaluar: P  N -> List(Boolean)
;dada una fórmula proposicional P: List (Boolean) -> Boolean y la cantidad de variables n que utiliza P, devuelve una
;lista con booleanos, que son el resultado de evaluar P en cada una de las posibles valuaciones.

(check-expect (evaluar C 2) (list #f #f #f #f))
(check-expect (evaluar A 3) (list #t #t #t #t #t #t #t #t))
(define (evaluar p n) (map p (valuaciones n)))



;,,,,,Ejercicio 5

;true?: Boolean-> Boolean
;dado un Booleano, devuelve #t si es verdadero 
(define (true? b) (not(false? b)))

;tautologia?: P N -> Boolean 
;dada una fórmula proposicional P: List (Boolean) -> Boolean y la cantidad de variables n que utiliza P;
;devuelve #t si la proposición P es una Tautología.

(check-expect (tautología? A 3) #t)
(check-expect (tautología? B 3) #f)
(check-expect (tautología? C 2) #f)

(define (tautología? p n) (empty? (filter  false? (evaluar p n)) ))

;contradiccion?: P N -> Boolean
;;dada una fórmula proposicional P: List (Boolean) -> Boolean y la cantidad de variables n que utiliza P;
;devuelve #t si la proposición P es una contradicción.

(check-expect (contradicción? A 3) #f)
(check-expect (contradicción? B 3) #f)
(check-expect (contradicción? C 2) #t)

(define (contradicción? p n) (empty? (filter true? (evaluar p n))))

;satisfactible?: P N -> Boolean
;dada una fórmula proposicional P: List (Boolean) -> Boolean y la cantidad de variables n que utiliza P;
;devuelve #t si la proposición P es satisfactible.

(check-expect (satisfactible? A 3) #t)
(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? C 2) #f)

(define (satisfactible? p n) (cons? (filter true? (evaluar p n))))



;............................................................................................

;,,,,,,,Ejercicio 6


; D : List(Boolean) -> Boolean
; D representa la fórmula proposicional p
(define
  (D l)
  (first l))

; E : List(Boolean) -> Boolean
; E representa la fórmula proposicional p \/ ~p 
(define
  (E l)
  (let ([p (first l)])
  (or p (not p))))

; F : List(Boolean) -> Boolean
; F representa la fórmula proposicional p /\ ~p 
(define
  (F l)
  (let ([p (first l)])
  (and p (not p))))

; MP : List(Boolean) -> Boolean
; MP representa la fórmula proposicional ((p -> q) /\ p) -> q
; conocida como modus ponens.
(define
  (MP l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) p) q)))

; MT : List(Boolean) -> Boolean
; MT representa la fórmula proposicional ((p -> q) /\ ~q) -> ~p
; conocida como modus tollens.
(define
  (MT l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) (not q)) (not p))))

; DM1 : List(Boolean) -> Boolean
; DM1 representa la fórmula proposicional ~(p \/ q) <-> (~p /\ ~q)
; que constituye una de las leyes de morgan.
(define
  (DM1 l)
  (let ([p (first l)]
        [q (second l)])
  (equivalente (not (or p q))
               (and (not p) (not q)))))

; G : List(Boolean) -> Boolean
; G representa la fórmula proposicional p1 /\ ~ p2 /\ (p1 -> ~p4) /\ (p2 \/ p3) /\ (p3 -> p4)
(define
  (G l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and p1
       (not p2)
       (implica p1 (not p4))
       (or p2 p3)
       (implica p3 p4))))

; H : List(Boolean) -> Boolean
; H representa la fórmula proposicional ((p1 \/ p2) -> p3) /\ (~p3 \/ ~p4)
(define
  (H l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and (implica (or p1 p2) p3)
       (or (not p3) (not p4)))))

; I : List(Boolean) -> Boolean
; I representa la fórmula proposicional
; ((p1 \/ ~p2) -> (p5 \/ (p1 /\ p3 /\ ~p4))) <-> (~(~p1 \/ ~p3 \/ p4 \/ p5) -> (~p1 \/ ~p2))
(define
  (I l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)]
        [p5 (fifth l)])
  (equivalente
    (implica (or p1 (not p2))
             (or p5 (and p1 p3 (not p4))))
    (implica (not (or (not p1) (not p3) p4 p5))
             (or (not p1) (not p2))))))

;;;; Tests para ejercicio 4

; ocurrencias : List(X) X -> Natural
; Dados una lista l de elementos de tipo X y un elemento v de tipo
; X, devuelve la cantidad de veces que v aparece en l.
(define
  (ocurrencias l v) (local ((define (ig? x) (equal? x v)))
                      ;-IN-
  (length (filter ig? l))))

(check-expect (ocurrencias (evaluar A 3) #t) 8)
(check-expect (ocurrencias (evaluar A 3) #f) 0)
(check-expect (ocurrencias (evaluar B 3) #t) 6)
(check-expect (ocurrencias (evaluar B 3) #f) 2)
(check-expect (ocurrencias (evaluar C 2) #t) 0)
(check-expect (ocurrencias (evaluar C 2) #f) 4)
(check-expect (ocurrencias (evaluar D 1) #t) 1)
(check-expect (ocurrencias (evaluar D 1) #f) 1)
(check-expect (ocurrencias (evaluar E 1) #t) 2)
(check-expect (ocurrencias (evaluar E 1) #f) 0)
(check-expect (ocurrencias (evaluar F 1) #t) 0)
(check-expect (ocurrencias (evaluar F 1) #f) 2)
(check-expect (ocurrencias (evaluar MP 2) #t) 4)
(check-expect (ocurrencias (evaluar MP 2) #f) 0)
(check-expect (ocurrencias (evaluar MT 2) #t) 4)
(check-expect (ocurrencias (evaluar MT 2) #f) 0)
(check-expect (ocurrencias (evaluar DM1 2) #t) 4)
(check-expect (ocurrencias (evaluar DM1 2) #f) 0)
(check-expect (ocurrencias (evaluar G 4) #t) 0)
(check-expect (ocurrencias (evaluar G 4) #f) 16)
(check-expect (ocurrencias (evaluar H 4) #t) 6)
(check-expect (ocurrencias (evaluar H 4) #f) 10)
(check-expect (ocurrencias (evaluar I 5) #t) 21)
(check-expect (ocurrencias (evaluar I 5) #f) 11)

;;;; Tests para ejercicio 5

(check-expect (tautología? A 3) #t)
(check-expect (tautología? B 3) #f)
(check-expect (tautología? C 2) #f)
(check-expect (tautología? D 1) #f)
(check-expect (tautología? E 1) #t)
(check-expect (tautología? F 1) #f)
(check-expect (tautología? MP 2) #t)
(check-expect (tautología? MT 2) #t)
(check-expect (tautología? DM1 2) #t)
(check-expect (tautología? G 4) #f)
(check-expect (tautología? H 4) #f)
(check-expect (tautología? I 5) #f)

(check-expect (contradicción? A 3) #f)
(check-expect (contradicción? B 3) #f)
(check-expect (contradicción? C 2) #t)
(check-expect (contradicción? D 1) #f)
(check-expect (contradicción? E 1) #f)
(check-expect (contradicción? F 1) #t)
(check-expect (contradicción? MP 2) #f)
(check-expect (contradicción? MT 2) #f)
(check-expect (contradicción? DM1 2) #f)
(check-expect (contradicción? G 4) #t)
(check-expect (contradicción? H 4) #f)
(check-expect (contradicción? I 5) #f)

(check-expect (satisfactible? A 3) #t)
(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? C 2) #f)
(check-expect (satisfactible? D 2) #t)
(check-expect (satisfactible? E 1) #t)
(check-expect (satisfactible? F 1) #f)
(check-expect (satisfactible? MP 2) #t)
(check-expect (satisfactible? MT 2) #t)
(check-expect (satisfactible? DM1 2) #t)
(check-expect (satisfactible? G 4) #f)
(check-expect (satisfactible? H 4) #t)
(check-expect (satisfactible? I 5) #t)