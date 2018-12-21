#lang scheme

;;; Task 1
(cons 'car 'cdr)
(list 'this '(is silly))
(cons 'is '(this silly?))
(quote (+ 2 3))
(cons '+ '(2 3))
(car '(+ 2 3))
(cdr '(+ 2 3))
cons
(quote cons)
(quote (quote cons))
(car (quote (quote cons)))
(+ 2 3)
(+ '2 '3)
(+   (car   '(2   3))   (car   (cdr
'(2 3))))
((car (list + - * /)) 2 3)

;;; Task 2
(define a (+ -8.7 (* 1.2 (- 2 1.3))))
(define b (/ (+ (/ 2 3) (/ 4 9)) (- (/ 5 11) (/ 4 3))))
(define c (+ 1 (/ 1 (+ 2 (/ 1 (+ 1 (/ 1 2)))))))
(define d (* 1 (* -2 (* 3 (* -4 (* 5 (* -6 7)))))))
(displayln a)
(displayln b)
(displayln c)
(displayln d)

;;; Task 3
(+ 1 2)
(+ 1.0 2)
(+ 1 2.0)
(+ 1.0 2.0)
(- 2 1)
(- 2.0 1)
(- 2 1.0)
(- 2.0 1.0)
(* 2 3)
(* 2.0 3)
(* 2 3.0)
(* 2.0 3.0)
(/ 6 2)
(/ 6.0 2)
(/ 6 2.0)
(/ 6.0 2.0)
(/ 10 3)
(/ 10.0 3)
(/ 10 3.0)
(/ 10.0 3.0)

;;; Task 4
(cons 1 (cons '(2 . ((3) . ())) (cons '(()) (cons 4 5))))

;;; Task 5
((car (cdr (list + - * /))) 17 5)

;;; Task 6
(let ([3a (* 3 a)])
  (+ (- 3a b) (+ 3a b)))
(let ([abc (list a b c)])
  (cons (car abc) (cdr abc)))

;;; Task 7
(let ([x 9])
  (* x
    (let ([x (/ x 3)])
      (+ x x))))

;;; Task 8
(let ([f (lambda(x) x)]) (f 'a))
(let ([f (lambda x x)]) (f 'a))
(let ([f (lambda (x . y) x)]) (f 'a))
(let ([f (lambda (x . y) y)])   (f 'a))

;;; Task 9
(define (shorter list1 list2)
  (cond [(> (length list1) (length list2)) (list2)]
	[else list1]))
(shorter '(a b) '(a b c))
(shorter '(a b) '(a b c d))

;;; List 10
(define (len list)
  (let loop ((i 0) (input-list list))
    (if (null? input-list) i
	(loop (+ i 1) (cdr input-list)))))
(len '(1 2 3 4 5))
