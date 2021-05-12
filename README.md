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
$./bin/compiler <file> 
```
Where \<file\> is the path of the code you want to run the executable on.<br /> 
Sample test files have been included in **testcases** folder.

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
or<br/>
```
$spim -file "code.asm"
```
## LIBRARY FUNCTIONS<br /> 
* use **print_int(x)** to print integer x<br /> 
* use **x=scan_int()** to scan integer into x<br />
<br/>
* use **print_string(s)** to print string s  
<br/>
* use **print_char(x)** to print char c<br />  
* use **x=scan_char()** to scan char into c<br /> 
<br/>
* use **print_float(x)** to print float x<br />  
* use **x=scan_float()** to scan float into x<br /> 
