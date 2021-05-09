#include "assembly.h"

int counter;
int dataCounter; //to keep track of data section items
string reg1, reg2, reg3;

map<string, vector<string>> code; // asm code
vector<string> dataSection;
queue<pair<string, Entry *>> regInUse;
queue<pair<string, Entry *>> freeReg;
map<string, string> reg;

string currFunction;
ofstream codeFile;

void addLine(string a)
{
    code[currFunction].push_back(a);
}

void addData(string a)
{
    dataSection.push_back(a);
}

// flush all registers on jump
void saveOnJump()
{
    pair<string, Entry *> t;
    while (regInUse.size())
    {
        t = regInUse.front();
        regInUse.pop();
        // Update the exisiting identifier value from resetRegister
        Entry *currTmp = t.second;
        string r = t.first;
        int offset = currTmp->offset;
        if (currFunction != "main")
            offset = offset + 76;

        addLine("li $s6, " + to_string(offset));
        addLine("sub $s7, $fp, $s6"); //combine the two components of the address

        addLine("sw " + r + ", 0($s7)");
        t.second = NULL;
        freeReg.push(t);
        string tmp = "_" + r;
        reg[tmp] = "";
    }
}

string checkTemporaryInReg(string t)
{
    for (auto it = reg.begin(); it != reg.end(); ++it)
    {
        if (it->second == t)
            return it->first;
    }
    return "";
}

string getNextReg(pair<string, Entry *> temporary)
{
    //checking if the temporary is already in a register
    string r = checkTemporaryInReg(temporary.first);
    if (r != "")
    {
        r.erase(r.begin(), r.begin() + 1);
        return r;
    }
    ////cout<<"mm\n";
    //Check if we have a freeReg
    if (freeReg.size())
    {

        pair<string, Entry *> t = freeReg.front();
        freeReg.pop();

        int offset1 = temporary.second->offset;

        if (currFunction != "main")
            offset1 = offset1 + 76;
        r = t.first;

        // now we store value to the location in the stack
        addLine("li $s6, " + to_string(offset1)); // put the offset in s6
                                                  //  addLine("add $s6, $s6, $s6");        // double the offset
                                                  //  addLine("add $s6, $s6, $s6");        // double the offset again(4x)
        addLine("sub $s7, $fp, $s6");             //combine the two components of the address
        addLine("lw " + r + ", 0($s7)");
        t.second = temporary.second;
        regInUse.push(t);
        string tmp = "_" + r;
        reg[tmp] = temporary.first;
        return r;
        ////cout<<"<<"<<r<<">>\n";
    }
    else
    {
        pair<string, Entry *> t = regInUse.front();
        regInUse.pop();
        // Update the exisiting identifier value from resetRegister
        Entry *currTmp = t.second;
        r = t.first;
        int offset = currTmp->offset;
        if (currFunction != "main")
            offset = offset + 76;

        addLine("li $s6, " + to_string(offset));
        addLine("sub $s7, $fp, $s6"); //combine the two components of the address

        addLine("sw " + r + ", 0($s7)");

        // Load this register with temporary
        offset = temporary.second->offset;
        if (currFunction != "main")
            offset = offset + 76;

        // now we store value to the location in the stack
        addLine("li $s6, " + to_string(offset)); // put the offset in s6
                                                 //  addLine("add $s6, $s6, $s6");        // double the offset
                                                 //  addLine("add $s6, $s6, $s6");        // double the offset again(4x)
        addLine("sub $s7, $fp, $s6");            //combine the two components of the address

        addLine("lw " + r + ", 0($s7)");
        t.second = temporary.second;
        regInUse.push(t);
        string tmp = "_" + r;
        reg[tmp] = temporary.first;
        return r;
    }
}

void loadArrayElement(pair<string, Entry *> temporary, string registerTmp, int arr_type)
{
    if (currFunction == "main")
    {
        if (arr_type == 1)
        {
            addLine("li $s6, " + to_string(temporary.second->size));
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("li $t7, 4");
            addLine("mult $t8, $t7");
            addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("add $s6, $s6, $t7");
            addLine("sub $s7, $fp, $s6"); // combine the two components of the
        }

        else
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            addLine("li $t7, 4");
            addLine("mult $t8, $t7");
            addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("add $s6, $s6, $t7");
            addLine("sub $s7, $fp, $s6"); // combine the two components of the
        }
    }
    else
    {
        if (arr_type == 1)
        {
            addLine("li $s6, " + to_string(temporary.second->size));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("li $t7, 4");
            addLine("mult $t8, $t7");
            addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("sub $s7, $t8, $t7");
        }
        else
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            addLine("li $t7, 4");
            addLine("mult $t8, $t7");
            addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("sub $s7, $t8, $t7");
        }
    }
    addLine("lw " + registerTmp + ", 0($s7)");
}

void loadStructElement(pair<string, Entry *> temporary, string registerTmp, int struct_type)
{
    if (currFunction == "main")
    {
        if (struct_type == 1)
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            //addLine("li $t7, 4");
            //addLine("mult $t8, $t7");
            //addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("sub $s6, $fp, $s6");                              // combine the two components of the
            addLine("add $s7, $s6, $t8");
        }
        else
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            //addLine("li $t7, 4");
            //addLine("mult $t8, $t7");
            //addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("sub $s6, $fp, $s6");
            addLine("lw $s6, 0($s6)");
            addLine("add $s7, $s6, $t8");
            // combine the two components of the
        }
    }
    else
    {
        if (struct_type == 1)
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            //addLine("li $t7, 4");
            //addLine("mult $t8, $t7");
            //addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("addi $s6, 76");
            addLine("sub $s6, $fp, $s6"); // combine the two components of the
            addLine("add $s7, $s6, $t8");
        }
        else
        {
            addLine("li $t8, " + to_string(temporary.second->size));
            //addLine("li $t7, 4");
            //addLine("mult $t8, $t7");
            //addLine("mflo $t7");
            addLine("li $s6, " + to_string(temporary.second->offset)); // put the offset in s6
            addLine("addi $s6, 76");
            addLine("sub $s6, $fp, $s6");
            addLine("lw $s6, 0($s6)");
            addLine("add $s7, $s6, $t8");
            // combine the two components of the
        }
        //baadme dalna hai
    }
    addLine("lw " + registerTmp + ", 0($s7)");
}

void print_asm(string asm_name)
{
    asm_name.pop_back();
    asm_name.pop_back();
    asm_name = asm_name + ".asm";
    codeFile.open(asm_name);
    for (int m = 0; m < dataSection.size(); m++)
    {
        codeFile << dataSection[m] << endl;
    }
    codeFile << endl;
    codeFile << ".text" << endl;
    printCodeFunc("main");
    map<string, std::vector<string>>::iterator it;
    it = code.find("main");
    code.erase(it);
    for (auto it = code.begin(); it != code.end(); ++it)
    {
        //printCodeFunc(it->first);
        string a = it->first;
        codeFile << a << ":" << endl;
        for (int i = 0; i < code[a].size(); ++i)
            codeFile << '\t' << code[a][i] << endl;
        codeFile << endl;
    }
    //codeFile.close();
}

void printCodeFunc(string a)
{
    codeFile << a << ":" << endl;
    for (int i = 0; i < code[a].size(); ++i)
        codeFile << '\t' << code[a][i] << endl;
    codeFile << endl;
}

void add_comment(int i)
{
    addLine("# " + to_string(i + 1) + " : " + emit_list[i].ans.first + " = " + emit_list[i].operand_1.first + " " + emit_list[i].op.first + " " + emit_list[i].operand_2.first);
}

void func_start_code()
{
    //cout<<"hello::"<<currFunction<<"tt"<<endl;
    if (currFunction == "main")
    {
        //cout<<"in main asm\n";
        // set the frame pointer of the callee
        addLine("sub $sp, $sp, 200");
        addLine("la $fp, ($sp)");
        int size_func = lookup("main")->size;
        // allocate space for the registers by updating the stack pointer
        addLine("sub $sp, $sp, " + to_string(size_func));
    }
    else
    {
        //cout<<"inside other\n";
        int size_func = lookup(currFunction)->size + 4;
        // allocate space for the registers by updating the stack pointer
        addLine("sub $sp, $sp, 72");

        // storing the remaining registers
        addLine("sw $t0, 12($sp)");
        addLine("sw $t1, 16($sp)");
        addLine("sw $t2, 20($sp)");
        addLine("sw $t3, 24($sp)");
        addLine("sw $t4, 28($sp)");
        addLine("sw $t5, 32($sp)");
        addLine("sw $t6, 36($sp)");
        addLine("sw $t7, 40($sp)");
        addLine("sw $t8, 44($sp)");
        addLine("sw $t9, 48($sp)");
        addLine("sw $s0, 52($sp)");
        addLine("sw $s1, 56($sp)");
        addLine("sw $s2, 60($sp)");
        addLine("sw $s3, 64($sp)");
        addLine("sw $s4, 68($sp)");

        // store return address of the caller
        addLine("sw $ra, 0($sp)");

        // store the frame pointe of the caller
        addLine("sw $fp, 4($sp)");

        // set the frame pointer of the callee
        addLine("la $fp, 72($sp)");

        // create space for local data
        addLine("sub $sp, $sp, " + to_string(size_func));

        //copy parameters
        string parameterList = args_map[currFunction];
        int paramNum = 0;
        int paramSize = 76;
        string temp = parameterList;
        if (parameterList != "")
        {
            string delim = ",";
            string temp1;
            int f1 = temp.find_first_of(delim);
            while (f1 != -1)
            {
                temp1 = temp.substr(0, f1);
                temp = temp.substr(f1 + 1);
                f1 = temp.find_first_of(delim);
                if (paramNum < 4)
                {
                    //addLine("li $s6, " + to_string(paramSize));
                    addLine("sub $s7, $fp, " + to_string(paramSize));
                    addLine("sw $a" + to_string(paramNum) + ", 0($s7)");
                }
                // char a[50];
                // strcpy(a, temp1.c_str());
                paramSize += get_size(temp1);
                paramNum++;
            }
            if (paramNum < 4)
            {
                //addLine("li $s6, " + to_string(paramSize));
                addLine("sub $s7, $fp, " + to_string(paramSize));
                addLine("sw $a" + to_string(paramNum) + ", 0($s7)");
            }
        }
    }
}

void param_code(int i)
{
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second != NULL)
        {
            if (emit_list[i].operand_1.second->is_array == 1)
            { //array
                //addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                addLine("sub $s7, $fp, " + to_string(emit_list[i].operand_1.second->size));
                addLine("lw $t8, 0($s7)");
                addLine("li $t9, 4");
                addLine("mult $t8, $t9");
                addLine("mflo $t9"); //a[i]   i*4
                addLine(
                    "li $s6, " +
                    to_string(
                        emit_list[i].operand_1.second->offset)); // put the offset in s6
                addLine("add $s6, $s6, $t9");
                addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                              // address
                addLine("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_array == 2)
            {
                //constant index
                //addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                //addLine("sub $s7, $fp, "+to_string(emit_list[i].operand_1.second));
                addLine("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                addLine("li $t9, 4");
                addLine("mult $t8, $t9");
                addLine("mflo $t9"); //a[i]   i*4
                addLine(
                    "li $s6, " +
                    to_string(
                        emit_list[i].operand_1.second->offset)); // put the offset in s6
                addLine("add $s6, $s6, $t9");
                addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                              // address
                addLine("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 1)
            {
                //addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                addLine("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //addLine("li $t7, 4");
                //addLine("mult $t8, $t7");
                //addLine("mflo $t7");
                addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                addLine("sub $s6, $fp, $s6");                                           // combine the two components of the
                addLine("add $s7, $s6, $t8");
                addLine("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 2)
            {
                addLine("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //addLine("li $t7, 4");
                //addLine("mult $t8, $t7");
                //addLine("mflo $t7");
                addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                addLine("sub $s6, $fp, $s6");
                addLine("lw $s6, 0($s6)");
                addLine("add $s7, $s6, $t8");
                addLine("lw $t6, 0($s7)");
            }
        }
        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
            reg1 = "$t6";
        else
            ////cout<<"in\n";
            reg1 = getNextReg(emit_list[i].operand_1);
        ////cout<<"::"<<reg1<<"\n";
        if (counter < 4)
        {
            addLine("move $a" + to_string(counter) + ", " + reg1);
        }
        else
        {
            int paramNum = 0;
            int paramSize = 76;
            //////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //char *a = "int"; // to check
            //char a[50];
            //strcpy(a,emit_list[i].operand_1.second->type.c_str());
            paramSize += counter * get_size(convert_to_string("int"));

            addLine("li $s6, " + to_string(paramSize));
            addLine("sub $s7, $sp, $s6");
            addLine("sw " + reg1 + ", 0($s7)");
        }
        counter++;
    }
    else
    { // if the param is constant
        if (counter < 4)
        {
            addLine("addi $a" + to_string(counter) + ",$0, " +
                    emit_list[i].operand_1.first);
        }
        else
        {
            int paramNum = 0;
            int paramSize = 76;
            //char *a = "int";
            paramSize += counter * get_size(convert_to_string("int"));
            addLine("addi $t9, $0, " + emit_list[i].operand_1.first);
            addLine("li $s6, " + to_string(paramSize));
            addLine("sub $s7, $sp, $s6");
            addLine("sw $t9, 0($s7)");
        }
        counter++;
    }
}

void assign_op_code(int i)
{
    if (emit_list[i].ans.second->is_array == 1 || emit_list[i].ans.second->is_array == 2 || emit_list[i].ans.second->is_struct == 1 || emit_list[i].ans.second->is_struct == 2)
        reg3 = "$t7";
    else
    {
        reg3 = getNextReg(emit_list[i].ans);
        ////cout<<reg3<<"\n";
    }
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            loadArrayElement(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            loadArrayElement(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            loadStructElement(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            loadStructElement(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else
            reg2 = getNextReg(emit_list[i].operand_1);
        addLine("move " + reg3 + ", " + reg2);
    }
    else
    {
        addLine("addi" + reg3 + ", $0, " + emit_list[i].operand_1.first);
    }

    if (emit_list[i].ans.second->is_array == 1)
    {
        if (currFunction == "main")
        {
            addLine("li $s6, " + to_string(emit_list[i].ans.second->size));
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("li $t9, 4");
            addLine("mult $t8, $t9");
            addLine("mflo $t9");
            addLine(
                "li $s6, " +
                to_string(
                    emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("add $s6, $s6, $t9");
            addLine(
                "sub $s7, $fp, $s6"); // combine the two components of the address
        }
        else
        {
            addLine("li $s6, " + to_string(emit_list[i].ans.second->size));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("li $t6, 4");
            addLine("mult $t8, $t6");
            addLine("mflo $t6");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("sub $s7, $t8, $t6");
        }

        addLine("sw $t7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_array == 2)
    {
        if (currFunction == "main")
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            addLine("li $t9, 4");
            addLine("mult $t8, $t9");
            addLine("mflo $t9");
            addLine(
                "li $s6, " +
                to_string(
                    emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("add $s6, $s6, $t9");
            addLine(
                "sub $s7, $fp, $s6"); // combine the two components of the address
        }
        else
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            addLine("li $t6, 4");
            addLine("mult $t8, $t6");
            addLine("mflo $t6");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset));
            addLine("addi $s6, 76");
            addLine("sub $s7, $fp, $s6");
            addLine("lw $t8, 0($s7)");
            addLine("sub $s7, $t8, $t6");
        }

        addLine("sw $t7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_struct == 1)
    {
        //struct.identifier

        if (currFunction == "main")
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            //addLine("li $t9, 4");
            //addLine("mult $t8, $t9");
            //addLine("mflo $t9");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("sub $s6, $fp, $s6");
            addLine("add $s7, $s6, $t8");
            addLine("sw $t7, 0($s7)");
        }
        else
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            //addLine("li $t9, 4");
            //addLine("mult $t8, $t9");
            //addLine("mflo $t9");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("addi $s6, 76");
            addLine("sub $s6, $fp, $s6"); // combine the two components of the address
            addLine("add $s7, $s6, $t8");
            addLine("sw $t7, 0($s7)");
        }

        //add for non main func also
    }
    else if (emit_list[i].ans.second->is_struct == 2)
    {
        //struct->identifier size contains id off in struct. offset contains ptr offset in func
        if (currFunction == "main")
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            //addLine("li $t9, 4");
            //addLine("mult $t8, $t9");
            //addLine("mflo $t9");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("sub $s6, $fp, $s6");
            //addLine("lw $s7, 0($s6)");
            addLine("lw $s6, 0($s6)");
            //addLine("lw $s6, 10");
            addLine("add $s6, $s6, $t8");
            //addLine(
            //    "sub $s7, $fp, $s6"); // combine the two components of the address
            addLine("sw $t7, 0($s6)");
        }
        else
        {
            addLine("li $t8, " + to_string(emit_list[i].ans.second->size));
            //addLine("li $t9, 4");
            //addLine("mult $t8, $t9");
            //addLine("mflo $t9");
            addLine("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            addLine("addi $s6, 76");
            addLine("sub $s6, $fp, $s6");
            //addLine("lw $s7, 0($s6)");
            addLine("lw $s6, 0($s6)");
            //addLine("lw $s6, 10");
            addLine("add $s6, $s6, $t8");
            //addLine(
            //    "sub $s7, $fp, $s6"); // combine the two components of the address
            addLine("sw $t7, 0($s6)");
        }

        //add for non main func also
    }
}

void generate_asm()
{
    dataCounter = 0;
    dataSection.push_back(".data");
    dataSection.push_back("reservedspace: .space 1024");
    dataSection.push_back("_newline: .asciiz \"\\n\"");
    currFunction = "main";
    code[currFunction].push_back("");
    //cout<<"hello\n";
    int unconditionalgoto = 0;
    for (int i = 0; i < emit_list.size(); i++)
    {
        //cout<<"f1\n";
        //addLine("# " + to_string(i + 1) + " : " + emit_list[i].ans.first + " = " + emit_list[i].operand_1.first + " " + emit_list[i].op.first + " " + emit_list[i].operand_2.first);
        //cout<<"f2\n";
        if (emit_list[i].op.first == "GOTO")
            unconditionalgoto = 0;
        if (label_map.find(i) != label_map.end())
        {
            saveOnJump();
            addLine(label_map[i] + ":");
            if (unconditionalgoto == 1)
                unconditionalgoto = 0;
        }
        if (unconditionalgoto)
        {
            continue;
        }
        //cout<<"f3::"<<emit_list[i].line_no<<endl;
        if (emit_list[i].line_no == -2)
        {
            if (i < emit_list.size() && emit_list[i + 1].line_no == -3)
            {
                //only func declration (mutual recusrsion)
                continue;
            }
            //function starting
            counter = 0;
            currFunction = emit_list[i].op.first;
            //cout<<"is::::"<<currFunction<<endl;
            currFunction.erase(currFunction.begin(), currFunction.begin() + 5);
            currFunction.erase(currFunction.end() - 8, currFunction.end());
            add_comment(i);
            //cout<<"starting\n";
            func_start_code();
            //cout<<"finid\n";
        }
        else if (emit_list[i].line_no == -4)
        {
            // param constant strings
            add_comment(i);
            addData("DataString" + to_string(dataCounter) + ": .asciiz " +
                    emit_list[i].operand_1.first);
            addLine("la $a" + to_string(counter) + ", DataString" +
                    to_string(dataCounter));
            counter++;
            dataCounter++;
            /////To add for more than 4 parameters
            /////////////////////////////////////
            /////////////////////////////////////
            /////////////////////////////////////
        }
        else if (emit_list[i].line_no == -1)
        {
            add_comment(i);
            if (emit_list[i].op.first == "param")
            {
                //parameters before calling
                param_code(i);
            }
            else if (emit_list[i].op.first == "=" || emit_list[i].op.first == "realtoint" || emit_list[i].op.first == "inttoreal")
            {
                //cout<<"in\n";
                //eqaulity operator
                assign_op_code(i);
            }
            else if (emit_list[i].op.first == "unary&")
            {
                reg1 = getNextReg(emit_list[i].ans);
                int off = emit_list[i].operand_1.second->offset;
                //off = -off;
                string u = to_string(off);
                // addLine("add " + reg1 + ", $fp, " + u);

                if (emit_list[i].operand_1.second->is_array == 1)
                {

                    addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                    addLine("sub $s7, $fp, $s6");
                    addLine("lw $t8, 0($s7)");
                    addLine("li $t7, 4");
                    addLine("mult $t8, $t7");
                    addLine("mflo $t7");
                    addLine("addi $t7, " + to_string(off));
                    addLine("neg $t7, $t7");
                    // u = string("$t7");
                    addLine("add " + reg1 + ", $fp, $t7");
                }
                else if (emit_list[i].operand_1.second->is_array == 2)
                {

                    addLine("lw $s8, " + to_string(emit_list[i].operand_1.second->size));
                    addLine("li $t7, 4");
                    addLine("mult $t8, $t7");
                    addLine("mflo $t7");
                    addLine("addi $t7, " + to_string(off));
                    addLine("neg $t7, $t7");
                    //u = string("$t7");
                    addLine("add " + reg1 + ", $fp, $t7");
                }
                else if (emit_list[i].operand_1.second->is_struct == 1)
                {

                    addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                    addLine("li $t7, " + to_string(off));
                    addLine("sub $t7, $fp, $t7");
                    addLine("add " + reg1 + ", $s6, $t7");
                }
                else if (emit_list[i].operand_1.second->is_struct == 2)
                {

                    addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                    //addLine("li $t7, 4");
                    //addLine("mult $t8, $t7");
                    //addLine("mflo $t7");
                    addLine("li $t7, " + to_string(off)); // put the offset in s6
                    addLine("sub $t7, $fp, $t7");
                    addLine("lw $t7, 0($t7)");
                    addLine("add " + reg1 + ", $s6, $t7");
                }
                else
                {
                    addLine("sub " + reg1 + ", $fp, " + to_string(off));
                }

                saveOnJump();
            }
            else if (emit_list[i].op.first == "unary*")
            {
                reg1 = getNextReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                    reg2 = "$t6";
                else
                    reg2 = getNextReg(emit_list[i].operand_1);
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        addLine("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                        addLine("sub $s7, $fp, $s6");
                        addLine("lw $t8, 0($s7)");
                        addLine("li $t9, 4");
                        addLine("mult $t8, $t9");
                        addLine("mflo $t9");
                        addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                        addLine("add $s6, $s6, $t9");
                        addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                                      // address
                        addLine("lw $t6, 0($s7)");
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        addLine("lw $s8, " + to_string(emit_list[i].operand_1.second->size));
                        addLine("li $t9, 4");
                        addLine("mult $t8, $t9");
                        addLine("mflo $t9");
                        addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                        addLine("add $s6, $s6, $t9");
                        addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                                      // address
                        addLine("lw $t6, 0($s7)");
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        addLine("li $t9, " + to_string(emit_list[i].operand_1.second->size));
                        
                        addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                        
                        addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                                      // address
                        addLine("add $s7, $t9, $s7");                              
                        addLine("lw $t6, 0($s7)");
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        addLine("li $t9, " + to_string(emit_list[i].operand_1.second->size));
                        
                        addLine("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                        
                        addLine("sub $s7, $fp, $s6"); // combine the two components of the
                                                      // address
                        addLine("lw $s7, 0($s7)");
                        addLine("add $s7, $t9, $s7");
                        addLine("lw $t6, 0($s7)");
                    }
                }
                addLine("lw " + reg1 + ", 0(" + reg2 + ")");
                saveOnJump();
            }
            else if (emit_list[i].op.first == "unary-")
            {
                reg1 = getNextReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_1, reg2, 2);
                        }
                        if (emit_list[i].operand_1.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_1, reg2, 2);
                        }
                    }
                    addLine("neg " + reg1 + ", " + reg2);
                }
                else
                    addLine("addi " + reg1 + ", $0, -" + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "unary+")
            {
                reg1 = getNextReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);

                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                    addLine("lw " + reg1 + ", " + reg2);
                }
                else
                    addLine("addi " + reg1 + ", $0, " + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "~")
            {
                reg1 = getNextReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second != NULL)
                {
                    reg2 = getNextReg(emit_list[i].operand_1);
                    addLine("not " + reg1 + ", " + reg2);
                }
                else
                    addLine("not " + reg1 + ", " + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "!")
            {
                reg1 = getNextReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second != NULL)
                {
                    reg2 = getNextReg(emit_list[i].operand_1);
                    addLine("not " + reg1 + ", " + reg2);
                }
                else
                    addLine("not " + reg1 + ", " + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "+int")
            {
                
                reg1 = getNextReg(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //addLine("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$t7";
                    op_2 = 1;
                    addLine("addi " + reg3 + ", $0" + ", " + emit_list[i].operand_2.first);
                }
                addLine("add " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "-int")
            {
                reg1 = getNextReg(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //addLine("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$t7";
                    op_2 = 1;
                    addLine("addi " + reg3 + ", $0" + ", " + emit_list[i].operand_2.first);
                }
                addLine("sub " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "*int")
            {
                reg1 = getNextReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    
                }
                else
                {
                    reg3 = "$t7";
                    addLine("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //addLine("mult " + reg2 + ", $t9");
                    //addLine("mflo " + reg1);
                }
                addLine("mult " + reg2 + ", " + reg3);
                addLine("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "/int")
            {
                reg1 = getNextReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    addLine("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //addLine("mult " + reg2 + ", $t9");
                    //addLine("mflo " + reg1);
                }
                addLine("div " + reg2 + ", " + reg3);
                addLine("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "%")
            {
                reg1 = getNextReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    addLine("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //addLine("mult " + reg2 + ", $t9");
                    //addLine("mflo " + reg1);
                }
                addLine("div " + reg2 + ", " + reg3);
                addLine("mfhi " + reg1);
            }
            else if (emit_list[i].op.first == "&" || emit_list[i].op.first == "|" || emit_list[i].op.first == "^" || emit_list[i].op.first == ">>" || emit_list[i].op.first == "<<")
            {
                reg1 = getNextReg(emit_list[i].ans);
                string op = emit_list[i].op.first;
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2||emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getNextReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        loadArrayElement(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        loadStructElement(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    addLine("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2||emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getNextReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            loadArrayElement(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            loadStructElement(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    addLine("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //addLine("mult " + reg2 + ", $t9");
                    //addLine("mflo " + reg1);
                }
                addLine("div " + reg2 + ", " + reg3);
                addLine("mflo " + reg1);
                if (op == "&")
                    addLine("and " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "|")
                    addLine("or " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "^")
                    addLine("xor " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "<<")
                    addLine("sll " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == ">>")
                    addLine("sra " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "<" || emit_list[i].op.first == ">" || emit_list[i].op.first == "GE_OP" || emit_list[i].op.first == "LE_OP" || emit_list[i].op.first == "EQ_OP" || emit_list[i].op.first == "NE_OP")
            {
                string op = emit_list[i].op.first;
                if (emit_list[i].operand_2.second == NULL)
                {
                    addLine("addi $t6, $0, " + emit_list[i].operand_2.first);
                    reg1 = "$t6";
                }
                else if (emit_list[i].operand_2.second->is_array == 1)
                {
                    reg1 = "$t6";
                    loadArrayElement(emit_list[i].operand_2, reg1, 1);
                }
                else if (emit_list[i].operand_2.second->is_array == 2)
                {
                    reg1 = "$t6";
                    loadArrayElement(emit_list[i].operand_2, reg1, 2);
                }
                else if (emit_list[i].operand_2.second->is_struct == 1)
                {
                    reg1 = "$t6";
                    loadStructElement(emit_list[i].operand_2, reg1, 1);
                }
                else if (emit_list[i].operand_2.second->is_struct == 2)
                {
                    reg1 = "$t6";
                    loadStructElement(emit_list[i].operand_2, reg1, 2);
                }
                else
                    reg1 = getNextReg(emit_list[i].operand_2);

                if (emit_list[i].operand_1.second == NULL)
                {
                    addLine("addi $t7, $0, " + emit_list[i].operand_2.first);
                    reg2 = "$t7";
                }
                else if (emit_list[i].operand_1.second->is_array == 1)
                {
                    reg2 = "$t7";
                    loadArrayElement(emit_list[i].operand_1, reg2, 1);
                }
                else if (emit_list[i].operand_1.second->is_array == 2)
                {
                    reg2 = "$t7";
                    loadArrayElement(emit_list[i].operand_1, reg2, 2);
                }
                else if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    reg2 = "$t7";
                    loadStructElement(emit_list[i].operand_1, reg2, 1);
                }
                else if (emit_list[i].operand_1.second->is_struct == 2)
                {
                    reg2 = "$t7";
                    loadStructElement(emit_list[i].operand_1, reg2, 2);
                }
                else
                    reg2 = getNextReg(emit_list[i].operand_1);
                reg3 = getNextReg(emit_list[i].ans);
                if (op == "<")
                    addLine("slt " + reg3 + ", " + reg2 + ", " + reg1);
                else if (op == ">")
                    addLine("sgt " + reg3 + ", " + reg2 + ", " + reg1);
                else if (op == "GE_OP")
                    addLine("sge " + reg3 + ", " + reg2 + ", " + reg1);
                else if (op == "LE_OP")
                    addLine("sle " + reg3 + ", " + reg2 + ", " + reg1);
                else if (op == "EQ_OP")
                    addLine("seq " + reg3 + ", " + reg2 + ", " + reg1);
                else if (op == "NE_OP")
                    addLine("sne " + reg3 + ", " + reg2 + ", " + reg1);
            }
            else if (emit_list[i].op.first == "RETURN")
            {
                // retuning
                if (currFunction == "main")
                {
                    addLine("li $a0, 0");
                    addLine("li $v0, 10");
                    addLine("syscall");
                }
                else
                {
                    if (emit_list[i].operand_1.first == "")
                    {
                        // only return;
                    }
                    else if (emit_list[i].operand_1.second != NULL)
                    {
                        reg1 = getNextReg(emit_list[i].operand_1);
                        addLine("move $v0, " + reg1);
                    }
                    else
                    {
                        addLine("li $v0, " + emit_list[i].operand_1.first);
                    }
                    addLine("b " + currFunction + "end");
                }
            }
            //library functions implementation

            else if (emit_list[i].op.first == "CALL" &&
                     emit_list[i].operand_1.first == "printf")
            {
                // printing one integer with newline
                addLine("li $v0, 1");
                addLine("syscall");
                addLine("li $v0, 4");
                addLine("la $a0, _newline");
                addLine("syscall");
                counter = 0;
            }

            else if (emit_list[i].op.first == "CALL" &&
                     emit_list[i].operand_1.first == "print_int")
            {
                // printing one integer without newline
                addLine("li $v0, 1");
                addLine("syscall");
                counter = 0;
            }

            else if (emit_list[i].op.first == "CALL" &&
                     emit_list[i].operand_1.first == "print_string")
            {
                // printing string
                // string is already in a0;
                addLine("li $v0, 4");
                addLine("syscall");
                counter = 0;
            }
            else if (emit_list[i].op.first == "CALL" &&
                     emit_list[i].operand_1.first == "scanf")
            {
                reg1 = getNextReg(emit_list[i].ans);
                addLine("li $v0, 5");
                addLine("syscall");
                addLine("move " + reg1 + ", $v0");
            }
            else if (emit_list[i].op.first == "CALL")
            {
                addLine("jal " + emit_list[i].operand_1.first);
                if (emit_list[i].ans.second != NULL)
                {
                    reg1 = getNextReg(emit_list[i].ans);
                    addLine("move " + reg1 + ", $v0");
                    counter = 0;
                }
            }
        }
        else if (emit_list[i].line_no == -3 && currFunction != "main")
        {
            if (i > 0 && emit_list[i - 1].line_no == -2)
            {
                //just the function definition (mutual recursion )
                continue;
            }
            add_comment(i);
            //returns  from non main function
            addLine(currFunction + "end:");

            // Removing the local data of the functions
            int sizeEnd = lookup(currFunction)->size + 4;
            addLine("addi $sp, $sp, " + to_string(sizeEnd));

            // Get environment pointers
            addLine("lw $ra, 0($sp)");
            addLine("lw $fp, 4($sp)");
            addLine("lw $a0, 8($sp)");

            // Restoring all the Registers
            addLine("lw $t0, 12($sp)");
            addLine("lw $t1, 16($sp)");
            addLine("lw $t2, 20($sp)");
            addLine("lw $t3, 24($sp)");
            addLine("lw $t4, 28($sp)");
            addLine("lw $t5, 32($sp)");
            addLine("lw $t6, 36($sp)");
            addLine("lw $t7, 40($sp)");
            addLine("lw $t8, 44($sp)");
            addLine("lw $t9, 48($sp)");
            addLine("lw $s0, 52($sp)");
            addLine("lw $s1, 56($sp)");
            addLine("lw $s2, 60($sp)");
            addLine("lw $s3, 64($sp)");
            addLine("lw $s4, 68($sp)");
            addLine("addi $sp, $sp, 72");

            // jump to the calling procedure
            addLine("jr $ra");
        }
        else
        {
            add_comment(i);
            // jump statements
            if (emit_list[i].op.first == "GOTO" && emit_list[i].operand_1.first == "")
            {
                saveOnJump();
                addLine("j " + label_map[emit_list[i].line_no]);
            }
            else if (emit_list[i].op.first == "GOTO" &&
                     emit_list[i].operand_1.first == "IF")
            {
                saveOnJump();
                if (emit_list[i].operand_2.second != NULL)
                {
                    reg1 = getNextReg(emit_list[i].operand_2);
                    addLine("bne $0, " + reg1 + ", " +
                            label_map[emit_list[i].line_no]);
                }
                else
                {
                    addLine("addi $t9, $0, " + emit_list[i].operand_2.first);
                    addLine("bne $0, $t9, " + label_map[emit_list[i].line_no]);
                }
            }
        }
        saveOnJump(); //saving registers
        if (emit_list[i].op.first == "GOTO" && emit_list[i].operand_1.first == "")
            unconditionalgoto = 1;
    }
}

void resetRegister()
{
    pair<string, Entry *> t0 = pair<string, Entry *>("$t0", NULL);
    pair<string, Entry *> t1 = pair<string, Entry *>("$t1", NULL);
    pair<string, Entry *> t2 = pair<string, Entry *>("$t2", NULL);
    pair<string, Entry *> t3 = pair<string, Entry *>("$t3", NULL);
    pair<string, Entry *> t4 = pair<string, Entry *>("$t4", NULL);
    pair<string, Entry *> t5 = pair<string, Entry *>("$t5", NULL);
    //  pair<string, Entry*> t6 = pair<string, Entry*>("$t6", NULL);
    // pair<string, Entry*> t7 = pair<string, Entry*>("$t7", NULL);
    //  pair<string, Entry*> t8 = pair<string, Entry*>("$t8", NULL);
    //  pair<string, Entry*> t9 = pair<string, Entry*>("$t9", NULL);
    pair<string, Entry *> s0 = pair<string, Entry *>("$s0", NULL);
    pair<string, Entry *> s1 = pair<string, Entry *>("$s1", NULL);
    pair<string, Entry *> s2 = pair<string, Entry *>("$s2", NULL);
    pair<string, Entry *> s3 = pair<string, Entry *>("$s3", NULL);
    pair<string, Entry *> s4 = pair<string, Entry *>("$s4", NULL);
    freeReg.push(t1);
    freeReg.push(t2);
    freeReg.push(t3);
    freeReg.push(t4);
    freeReg.push(t0);
    freeReg.push(t5);
    //  freeReg.push(t6);
    //  freeReg.push(t7);
    //  freeReg.push(t8);
    //  freeReg.push(t9); for using in calculations
    freeReg.push(s0);
    freeReg.push(s1);
    freeReg.push(s2);
    freeReg.push(s3);
    freeReg.push(s4);
    //----------MAP to store the identifier--------------------------//
    pair<string, string> _t0 = pair<string, string>("$t0", "");
    pair<string, string> _t1 = pair<string, string>("$t1", "");
    pair<string, string> _t2 = pair<string, string>("$t2", "");
    pair<string, string> _t3 = pair<string, string>("$t3", "");
    pair<string, string> _t4 = pair<string, string>("$t4", "");
    pair<string, string> _t5 = pair<string, string>("$t5", "");
    //  pair<string, string> _t6 = pair<string, string>("$t6", "");
    //  pair<string, string> _t7 = pair<string, string>("$t7", "");
    //  pair<string, string> _t8 = pair<string, string>("$t8", "");
    //  pair<string, string> _t9 = pair<string, string>("$t9", "");
    pair<string, string> _s0 = pair<string, string>("$s0", "");
    pair<string, string> _s1 = pair<string, string>("$s1", "");
    pair<string, string> _s2 = pair<string, string>("$s2", "");
    pair<string, string> _s3 = pair<string, string>("$s3", "");
    pair<string, string> _s4 = pair<string, string>("$s4", "");
    reg.insert(_t1);
    reg.insert(_t2);
    reg.insert(_t3);
    reg.insert(_t4);
    reg.insert(_t0);
    reg.insert(_t5);
    //  reg.insert(_t6);
    //  reg.insert(_t7);
    //  reg.insert(_t8);
    //  reg.insert(_t9);
    reg.insert(_s0);
    reg.insert(_s1);
    reg.insert(_s2);
    reg.insert(_s3);
    reg.insert(_s4);
}
