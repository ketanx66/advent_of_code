#lang racket

(define input (open-input-file "input.txt"))
(define mass_list (for/list ([line (in-lines input)])
                   (string->number line)))

(close-input-port input)


(define (fuel_for_mass x) (- (quotient x 3) 2))
(define (advanced_fuel x)
  (let ((out  (fuel_for_mass x)))
    (if (<= out 0) 0 (+ out (advanced_fuel out)))))

(foldl (lambda (x xs) (+ (advanced_fuel x) xs)) 0 mass_list)