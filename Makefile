all: 
	flex src/comp.l
	gcc lex.yy.c -lfl -o lexer
	mv lexer bin/lexer
	rm lex.yy.c

clean:
	rm bin/lexer
