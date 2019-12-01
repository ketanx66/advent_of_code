#lang racket

(define input (open-input-file "input.txt"))
(define mass_list (for/list ([line (in-lines input)])
                   (string->number line)))
(close-input-port input)



(define (fuel_for_mass x) (- (quotient x 3) 2))

(foldl (lambda (x xs) (+ (fuel_for_mass x) xs)) 0 mass_list)

