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

(eval tape 0)

