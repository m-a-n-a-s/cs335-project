all: 
	flex src/comp.l
	mv lex.yy.c src/lex.yy.c
	yacc -dvt src/comp.y
	mv y.tab.c src/y.tab.c
	mv y.tab.h src/y.tab.h
	gcc src/y.tab.c src/lex.yy.c src/functions.c src/main.c -lfl -o parser
	mkdir bin
	mv parser bin/parser
	rm src/lex.yy.c src/y.tab.c src/y.tab.h y.output

clean:
	rm -r bin
