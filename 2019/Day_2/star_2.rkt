#lang racket

(define tape (list-set(list-set (call-with-input-file "input.txt"
                                  (lambda (in)
                                    (map string->number
                                         (string-split (read-line in) ","))))
                                1 12) 2 2))


(define (eval tape pos)
  (let* ((pick (lambda (x) (list-ref tape x)))
         (take-value (lambda (x) (pick (pick x)))))
     
    (match (list-ref tape pos) 
      [1 (eval (list-set tape
                         (pick (+ pos 3))
                         (+ (take-value (+ pos 1))
                            (take-value (+ pos 2))))
               (+ pos 4))]
      [2 (eval (list-set tape
                         (pick (+ pos 3))
                         (* (take-value (+ pos 1))
                            (take-value (+ pos 2))))
               (+ pos 4))]
      [99 (car tape)]
      [n ":C"])))


(define (noun-&-verb target tape)
  (define (out n v) (+ (* 100 n) v))
  (define (set-n-v tape noun verb) (list-set (list-set tape 1 noun) 2 verb))
  (define (aux n&v)
    (match n&v
      [(list 0 0) (if (= (eval (set-n-v tape 0 0) 0) target)
                      (out 0 0)
                      (":("))]
      [(list 0 v) (if (= (eval (set-n-v tape 0 v) 0) target)
                      (out 0 v)
                      (aux (list 99 (- v 1))))]
      [(list n 0) (if (= (eval (set-n-v tape n 0) 0) target)
                      (out n 0)
                      (aux (list (- n 1) 0)))]
      [(list n v) (if (= (eval (set-n-v tape n v) 0) target)
                      (out n v)
                      (aux (list (- n 1) v)))]))
  (aux '(99 99)))

(noun-&-verb 19690720 tape)
