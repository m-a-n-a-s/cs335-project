# Group 6 CS335-project
If bin folder already exists run 
```
$make clean
```
To build the executable -
```
$make
```
This will make an executable named parser in bin folder.<br /> 
To run and make the dot script -
```
$./bin/parser <file> -o ast.dot
```
Where \<file\> is the path of the code you want to run the executable on.<br /> 
5 sample test files have been included in test folder.

To visualize the tree -
```
$dot -Tps ast.dot -o ast.ps
```
Open ast.ps to see the Abstract Syntax Tree.
