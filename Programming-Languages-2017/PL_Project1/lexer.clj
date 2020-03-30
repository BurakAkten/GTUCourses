; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Project1 => Cofffe Lexer                 *
; *  Author: Burak Akten                      *
; *********************************************


;You can change the input file at the end of the file


(def valid true) ; global variable to contol valid or not


(comment 
	(def KEYWORDS #{"and"    , "not"    , "set"   , "if"   ,
					"append" , "concat" , "equal" , "else" ,
					"deffun" , "for"    , "while" , "then" ,
					"true"   , "false"  , "or"})
)

(def OPERATORS #{ \+ , ;PLUS
				  \- , ;MINUS
				  \/ , ;SLASH
				  \* , ;ASTERISK
				  \( , ;LEFT_PARENTHESIS
				  \)   ;RIGHT_PARENTHESIS
				}) 

(def SPACE 32)
;(println (contains? OPERATORS (nth "+" 0)))

(defn read-as-list
	"Reads a file containing one word per line and returns a list of words 
	(each word is in turn a list of characters)."
	[filename]
  ;Controlling file exists or not
  (if (.exists (clojure.java.io/file filename))
    (do
      (def myList (list))                                   ;defining the list.
      (with-open [rdr (clojure.java.io/reader filename)]    ;opening the file.
        (doseq [line (line-seq rdr)]
          (def myList (list* (clojure.string/trim line) myList))) ;adding new line into the list
      )
      (reverse myList)                       ;returning the list.
    )
    (do
      (println "File not found!")
      (System/exit 1)
      
    )
  )
)

(defn is_digit 
	"This function control the character is digit or not"
	[character]

	(def ascii_val (int character))
	(def isDigit false)
	(if (and (> ascii_val 47) (< ascii_val 58))
		(def isDigit true))
	isDigit
)

(defn is_alpha
	"This function control the character is in alphabet or not"
	[character]

	(def ascii_val (int character))
	(def isAlpha false)

	(if (or (and (> ascii_val 64) (< ascii_val 91)) (and (> ascii_val 96) (< ascii_val 123)))
		(def isAlpha true))
	isAlpha
)

(defn is_valid 
	"This function control the token to is valid or not"
	[token]

	(def digit false)
	(def alpha false)
	(def control true)

	(doseq [i token]

		(if (is_alpha i)
			(def alpha true)
			(def digit true)
		)
	)

	(if (and alpha digit)
		(def control false)
	)
	control
)

(defn find_tokens 
	"This function find the tokens for a line."
	[line]

	(def tokens (list))
	(def size (count line))

	(def i 0) ;counter
	(while  (and (< i size) (= valid true))
		(do
			(def element (nth line i))
			(if (contains? OPERATORS element)
				(do
					;(println "->" i)
					;(println "el->"  element)

					(def tokens (list* element tokens))
					(def i (+ i 1))
				)
				(do
					(if (or (is_alpha element) (is_digit element))
						(do
							(def token (list))
							;DFA part 
							;in this loop finding identifiers, integer and keyword.
							(while (and (not= (int element) 32) (< i size) (= (contains? OPERATORS element) false))
								(do
									;(println "<-" i)
									;(println "el2 -> " element)

									(def token (list* element token))
									(def i (+ i 1))

									(if (not= i size)
										(def element (nth line i)))
								)
							)
							(def token (apply str (reverse token)))

							;(println token)

							(def tokens (list* token tokens))
						)
						(do 
							(if (= (int element) 32 )
								(def i (+ i 1)) ;space
								(def valid false) ; invalid 
							)
						)
					)
				)
			)
		)
	)
	;Control the token is valid or not
	(def tokens (reverse tokens))
	(doseq [token tokens]
		(if (= (char? 	token) false)
			(do
				(if (= (is_valid token) false)
					(def valid false)
				)
			)
		)
	)
	tokens
)


(defn lexer
	"This function take a file name and perform lexical analysis of the program
	contained within this fule. The output of the function should be the tokens in a list."
	[filenmane]

	(def file_as_list (read-as-list filenmane))
	(def size (count file_as_list))

	(def tokens_list (list)) ;this list holds tokens in one index for each line

	(dotimes [x size]

		(def line (nth file_as_list x))
		(def tokens_list (list* (find_tokens line) tokens_list))
		(if (not valid)
			(def x size)
		)
	)
	;controlling for the valid token
	(if (not valid)
		(do 
			(println "Invalid Token/Tokens!")
			(list)
		)
		(flatten (reverse tokens_list)) ;make list of lists one list
	)
	
)

;Print the result on the screet.
(def total_tokens (lexer "CoffeeSample.coffee"))
(doseq [n total_tokens]

	(println "Next token : " n)

)
