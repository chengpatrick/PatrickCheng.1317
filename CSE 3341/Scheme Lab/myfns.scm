
; check if x is member of list L
(define (xmemb x L) 
   (cond
	((null? L) #f)		;L is empty so X is not in L
   	((eq? x (car L)) #t) 	;X is equal to the first element of L
   	(#t (xmemb x (cdr L)))	; else check the rest of L
   )
)

;find common elements in L1 L2
(define (common L1 L2)
   (cond
	((null? L1) '())	;L1 empty, return empty list
	((null? L2) '())	;L2 empty, return empty list
	((xmemb (car L1) L2) (cons (car L1) (common (cdr L1) L2)))
	(#t (common (cdr L1) L2))
   )
)

;eliminate numbers of L2 from L1
(define (eliminate L1 L2)
   (cond
	((null? L1) '())	;L1 empty, return empty list
	((null? L2) L1)		;L2 empty, return L1
	((xmemb (car L1) L2) (eliminate (cdr L1) L2))	;front of L1 is in L2,remove front
	(#t (cons (car L1) (eliminate (cdr L1) L2)))	;else add front
   )
)

;find length of list
(define (len L)
   (cond 
	((null? L) 0)		;L is empty, return 0 length
        (#t (+ 1 (len (cdr L))))	;L is not empty, recurssion to count
   )
)

;bubble helper function, make L in order
(define (order L)
    (cond
	((null? (cdr L)) L)    ;L empty return L
        ((< (car L) (cadr L))	(cons (car L) (order (cdr L))))   ;front is small, order is alright
        (#t (cons (cadr L) (order (cons (car L) (cddr L)))))	;front is not small, swap
    )
)

;bubble helper function, go thru L
(define (bubble x L)    
    (cond 
	((eq? x 1) (order L))   	;length is 1
        (#t (bubble (- x 1) (order L)))	;L length is greater than 1, order it out
    )
)

;sort using bubble sort
(define (sort L) 
    (bubble(len L) L)
)

;start with L1 and remove from it all those elements that are also in L2
;sort the remaining elements into non-decreasing order to get the result list
(define (eliminateNsort L1 L2)
	(sort (eliminate L1 (common L1 L2)))
)