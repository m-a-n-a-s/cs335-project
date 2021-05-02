# Group 6 CS335-project
If bin folder already exists run 
```
$make clean
```
To build the executable -
```
$make
```
This will make an executable named compiler in bin folder.<br /> 
To run and make the dot script , symbol tables, IR code and asm code-
```
$./bin/compiler <file> -o ast.dot
```
Where \<file\> is the path of the code you want to run the executable on.<br /> 
6 sample test files have been included in test folder.

To visualize the tree -
```
$dot -Tps ast.dot -o ast.ps
```
Open ast.ps to see the Abstract Syntax Tree.

To run the assembly code
```
$spim
load "code.asm"
run
```
LIBRARY FUNCTIONS<br /> 
use print_int(x) to print integer x<br /> 
use print_string(s) to print string s<br /> 
use x=scanf() to scan integer into x<br /> 
