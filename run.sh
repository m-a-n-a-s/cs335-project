#!/bin/bash
RED='\033[0;33m'
GREEN='\033[0;32m'
NOCOLOR='\033[0m'

tests=`ls ./testcases/*.c`
for entry in $tests
do 
./bin/compiler $entry
echo -e "${RED}$entry${NOCOLOR}"
spim -file "code.asm"
echo -e "${GREEN}$entry done${NOCOLOR}"
done

# for i in {1..6}
# do 
# ./bin/compiler ./test/test$i.c -o ast.dot
# echo "$i done"
# done

# # ./bin/compiler test1.c -o ast.dot
# # echo "test1 done"
# ./bin/compiler sample.c -o ast.dot
# echo "sample done"
