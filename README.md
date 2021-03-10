# Group 6 CS335-project
If bin folder already exists run 
```
$make clean
```
To build the executable run.
```
$make
```
This will make a executable named parser in bin folder.<br /> 
To run 
```
$./bin/parser <file> -o ast.dot
```
Where \<file\> is the path of the code you want to run the executable on.<br /> 
Sample files have been included in test folder

To visualize the tree
```
$dot -Tps ast.dot -o ast.ps
```
