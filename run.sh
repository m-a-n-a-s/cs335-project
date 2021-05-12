#!/bin/bash

tests=`ls ./testcases/*.c`
for entry in $tests
do 
./bin/compiler $entry -o ast.dot
echo "${red}entry"
spim -file "code.asm"
echo "${green}entry done"
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
