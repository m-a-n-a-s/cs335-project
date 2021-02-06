all: 
	flex comp.l
	gcc -ll lex.yy.c -o lexer
	mv lexer ../bin/lexer
	rm lex.yy.c

clean:
	rm ../bin/lexer
