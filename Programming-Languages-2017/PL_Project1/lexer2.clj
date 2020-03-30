
; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Project1 => Cofffe Lexer                 *
; *  Author: Burak Akten                      *
; *********************************************

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


(defn lexer_for_line 
	"This function find the tokens for a line."
	[line]

	(def tokens (list))

	(def size (count line))

	(def i 0) ;counter
	(while  (< i size)
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
							;(println token)

							(def token (apply str (reverse token)))
							(def tokens (list* token tokens))
						)
						(do 
							(def i (+ i 1))
						)
					)
				)
			)
		)
	)
	(reverse tokens)
)


(defn lexer_for_file
	"This function take a file name and perform lexical analysis of the program
	contained within this fule. The output of the function should be the tokens in a list."
	[filenmane]

	(def file_as_list (read-as-list filenmane))
	(def size (count file_as_list))

	(def tokens_list (list)) ;this list holds tokens in one index for each line

	(dotimes [i size]

		(def line (nth file_as_list i))
		(def tokens_list (list* (lexer_for_line line) tokens_list))
	)
	(flatten (reverse tokens_list)) ;make list of lists one list
)

;(println (lexer_for_file "CoffeeSample.coffee"))




(defn lexer
 	"This is the function to make analysis."
 	[]


 	(def begin  " -------   --------    ------   ------    --------     -------- \n")
 	(def begin2 "|         |        |  |        |         |            |         \n")
 	(def begin3	"|         |        |  |        |         |            |         \n")
 	(def begin4 "|         |        |  |-----   |-----    |------      |------   \n")
 	(def begin5	"|         |        |  |        |         |            |		 \n")
 	(def begin6 "|         |        |  |        |         |            |         \n")
 	(def begin7 " -------   --------   |        |          --------     -------- \n")

 	(print begin)(flush)
 	(print begin2)(flush)
 	(print begin3)(flush)
 	(print begin4)(flush)
 	(print begin5)(flush)
 	(print begin6)(flush)
 	(print begin7)(flush)
 	(println "\nType 'coffee' to continue with interpreter. Thype 'coffee <filename>' to control file.\n")
 	(print "coffee->")(flush)

	(def input (read-line))

	(def inputs (clojure.string/split (clojure.string/trim input)  #" "))
	(def size (count inputs))

	(if (and (= size 1) (= input "coffee"))
	 	(do
		 	(while true
		 		(do
		 			(print "coffee->")(flush)
		 			(def code (read-line))
		 			(println (lexer_for_line code))
		 		)
		 	)
		 )
	 )
	 (if (and (= size 2) (= (nth inputs 0) "coffee"))
	 	(do
		 	(println (lexer_for_file (nth inputs 1)))
		 )
	 )

)

(lexer)