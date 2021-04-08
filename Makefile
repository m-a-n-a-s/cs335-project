# all: 
# 	flex src/comp.l
# 	mv lex.yy.c src/lex.yy.c
# 	yacc -dvt src/comp.y
# 	mv y.tab.c src/y.tab.c
# 	mv y.tab.h src/y.tab.h
# 	g++ src/lex.yy.c src/y.tab.c src/main.cpp src/functions.cpp src/semanticCheck.cpp src/symbolTable.cpp -w -ll -o parser
# 	mkdir bin
# 	mv parser bin/parser
# 	rm src/lex.yy.c src/y.tab.c src/y.tab.h y.output

# clean:
# 	rm -r bin
CC=g++ -ggdb3 -std=c++11 -w
BIN=./bin
SOURCE=./src
INPUT=./test
BUILD=./build
OBJ=$(BUILD)/functions.o     \
		$(BUILD)/semanticCheck.o \
		$(BUILD)/symbolTable.o  

all: $(BIN)/compiler

# $(BIN)/compile: $(SOURCE)/compile $(BIN)/compiler
# 	@mkdir -p $(BIN)
# 	cp $< $@

$(BIN)/compiler: $(BUILD)/y.tab.c $(BUILD)/lex.yy.c $(OBJ)
	@mkdir -p $(BIN)
	$(CC) $^ -o $@ -I$(BUILD) -I$(SOURCE)

$(BUILD)/y.tab.c: $(SOURCE)/comp.y
	@mkdir -p $(BUILD)
	yacc -dvt $^ -o $@

$(BUILD)/lex.yy.c: $(SOURCE)/comp.l
	@mkdir -p $(BUILD)
	flex -t $^ > $@

$(BUILD)/%.o: $(SOURCE)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) -c $^ -o $@ -I$(BUILD) -I$(SOURCE)

%.png: %.gv
	dot -Tpng $? -o $@

clean : 
	rm -rf $(BIN)  $(BUILD)
	rm -f *.csv *.asm *.txt *.gv
