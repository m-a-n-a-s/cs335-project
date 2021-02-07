all: 
	flex src/comp.l
	mv lex.yy.c src/lex.yy.c
	gcc src/lex.yy.c -lfl -o lexer
	mv lexer bin/lexer
	rm src/lex.yy.c

clean:
	rm bin/lexer
