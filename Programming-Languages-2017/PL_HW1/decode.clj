; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Yakup Genc                       *
; *********************************************

;; utility functions 
(load-file "include.clj") ;; "c2i and "i2c"


(use 'clojure.java.io)


(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]
	; Implement this function...
	'((a b c) (d e f))
)

;; -----------------------------------------------------
;; HELPERS
;; *** PLACE YOUR HELPER FUNCTIONS BELOW ***

(defn spell-checker-0 
	[word]
	;you should implement this function
)

(defn spell-checker-1
	[word]
 	;you should implement this function
)


;; -----------------------------------------------------
;; DECODE FUNCTIONS

(defn Gen-Decoder-A 
	[paragraph]
	;you should implement this function
)

(defn Gen-Decoder-B-0 
	[paragraph]
  	;you should implement this function
)

(defn Gen-Decoder-B-1 
	[paragraph]
  	;you should implement this function
)

(defn Code-Breaker 
	[document decoder]
  	;you should implement this function
)

;; -----------------------------------------------------
;; Test code...

(defn test_on_test_data
	[]
	(let [doc (read-as-list "document1")]
		(println doc)
	)
)


;; test code...
(test_on_test_data)