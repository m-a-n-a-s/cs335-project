#include "assembly.h"

#define REG_SPACE 36

int is_float;
int paramOff;
int param_idx;
int data_idx; //to keep track of data section items
string reg1, reg2, reg3;

map<string, vector<string>> asm_code; // asm asm_code
vector<string> _data;
queue<pair<string, Entry *>> used_reg;
queue<pair<string, Entry *>> free_reg;
map<string, string> reg_info;

queue<pair<string, Entry *>> used_reg_float; //for float operations
queue<pair<string, Entry *>> free_reg_float;
map<string, string> reg_info_float;

string curr_function;
ofstream asm_file;

void insert_asm(string a)
{
    asm_code[curr_function].push_back(a);
}
void store_reg_info()
{
    pair<string, Entry *> t;
    while (used_reg.size())
    {
        t = used_reg.front();
        used_reg.pop();
        // Update the exisiting identifier value
        Entry *currTmp = t.second;
        string r = t.first;
        int offset = currTmp->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        insert_asm("li $s6, " + to_string(offset));
        insert_asm("sub $s7, $fp, $s6"); 

        insert_asm("sw " + r + ", 0($s7)");
        t.second = NULL;
        free_reg.push(t);

        reg_info[r] = "";
    }
    //for float registers
    while (used_reg_float.size())
    {
        t = used_reg_float.front();
        used_reg_float.pop();
        // Update the exisiting identifier value
        Entry *currTmp = t.second;
        string r = t.first;
        int offset = currTmp->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        insert_asm("li $s6, " + to_string(offset));
        insert_asm("sub $s7, $fp, $s6"); 

        insert_asm("swc1 " + r + ", 0($s7)");
        t.second = NULL;
        free_reg_float.push(t);

        reg_info_float[r] = "";
    }
}

string getReg(pair<string, Entry *> temp_var)
{
    //checking if the temp_var is already in a register
    //string r = checkTemporaryInReg(temp_var.first);
    string r = "";
    for (auto it = reg_info.begin(); it != reg_info.end(); ++it)
    {
        if (it->second == temp_var.first)
        {
            r = it->first;
            return r;
        }
    }
    //Check if we have a free_reg
    if (free_reg.size())
    {

        pair<string, Entry *> t = free_reg.front();
        free_reg.pop();

        int offset1 = temp_var.second->offset;

        if (curr_function != "main")
            offset1 = offset1 + REG_SPACE;
        r = t.first;

        // now we store value to the location in the stack
        insert_asm("li $s6, " + to_string(offset1)); // put the offset in s6
        insert_asm("sub $s7, $fp, $s6");             
        insert_asm("lw " + r + ", 0($s7)");
        t.second = temp_var.second;
        used_reg.push(t);
        string tmp = "_" + r;
        reg_info[r] = temp_var.first;
        return r;
        ////cout<<"<<"<<r<<">>\n";
    }
    else
    {
        pair<string, Entry *> t = used_reg.front();
        used_reg.pop();
        // Update the exisiting identifier value
        Entry *currTmp = t.second;
        r = t.first;
        int offset = currTmp->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        insert_asm("li $s6, " + to_string(offset));
        insert_asm("sub $s7, $fp, $s6"); 

        insert_asm("sw " + r + ", 0($s7)");

        // Load this register with temp_var
        offset = temp_var.second->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        // now we store value to the location in the stack
        insert_asm("li $s6, " + to_string(offset)); // put the offset in s6
        insert_asm("sub $s7, $fp, $s6");            

        insert_asm("lw " + r + ", 0($s7)");
        t.second = temp_var.second;
        used_reg.push(t);
        string tmp = "_" + r;
        reg_info[r] = temp_var.first;
        return r;
    }
}

string getReg_float(pair<string, Entry *> temp_var)
{
    //checking if the temp_var is already in a register
    //string r = checkTemporaryInReg(temp_var.first);
    string r = "";
    for (auto it = reg_info_float.begin(); it != reg_info_float.end(); ++it)
    {
        if (it->second == temp_var.first)
        {
            r = it->first;
            return r;
        }
    }
    //Check if we have a free_reg
    if (free_reg_float.size())
    {

        pair<string, Entry *> t = free_reg_float.front();
        free_reg_float.pop();

        int offset1 = temp_var.second->offset;

        if (curr_function != "main")
            offset1 = offset1 + REG_SPACE;
        r = t.first;

        // now we store value to the location in the stack
        insert_asm("li $s6, " + to_string(offset1)); // put the offset in s6
        insert_asm("sub $s7, $fp, $s6");             
        insert_asm("lwc1 " + r + ", 0($s7)");
        t.second = temp_var.second;
        used_reg_float.push(t);
        reg_info_float[r] = temp_var.first;
        return r;
        ////cout<<"<<"<<r<<">>\n";
    }
    else
    {
        pair<string, Entry *> t = used_reg_float.front();
        used_reg_float.pop();
        // Update the exisiting identifier value
        Entry *currTmp = t.second;
        r = t.first;
        int offset = currTmp->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        insert_asm("li $s6, " + to_string(offset));
        insert_asm("sub $s7, $fp, $s6"); 

        insert_asm("swc1 " + r + ", 0($s7)");

        // Load this register with temp_var
        offset = temp_var.second->offset;
        if (curr_function != "main")
            offset = offset + REG_SPACE;

        // now we store value to the location in the stack
        insert_asm("li $s6, " + to_string(offset)); // put the offset in s6
        insert_asm("sub $s7, $fp, $s6");            

        insert_asm("lwc1 " + r + ", 0($s7)");
        t.second = temp_var.second;
        used_reg_float.push(t);
        //string tmp = "_" + r;
        reg_info_float[r] = temp_var.first;
        return r;
    }
}

void get_arr_element(pair<string, Entry *> temp_var, string reg_name, int arr_type)
{
    if (curr_function == "main")
    {
        if (arr_type == 1)
        {
            insert_asm("li $s6, " + to_string(temp_var.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t7, $fp, $t7");
                insert_asm("lw $t7, 0($t7)");                             //val of i
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t7");
            insert_asm("sub $s7, $fp, $s6"); 
        }

        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t7");
            insert_asm("sub $s7, $fp, $s6"); 
        }
    }
    else
    {
        if (arr_type == 1)
        {
            insert_asm("li $s6, " + to_string(temp_var.second->size));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //offset of i in a[i][j]
                insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $t7, $fp, $t7");
                insert_asm("lw $t7, 0($t7)");                             //val of i
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t7");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t7");
        }
    }
    insert_asm("lw " + reg_name + ", 0($s7)");
}

void get_arr_element_float(pair<string, Entry *> temp_var, string reg_name, int arr_type)
{
    if (curr_function == "main")
    {
        if (arr_type == 1)
        {
            insert_asm("li $s6, " + to_string(temp_var.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t7, $fp, $t7");
                insert_asm("lw $t7, 0($t7)");                             //val of i
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t7");
            insert_asm("sub $s7, $fp, $s6"); 
        }

        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t7");
            insert_asm("sub $s7, $fp, $s6"); 
        }
    }
    else
    {
        if (arr_type == 1)
        {
            insert_asm("li $s6, " + to_string(temp_var.second->size));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //offset of i in a[i][j]
                insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $t7, $fp, $t7");
                insert_asm("lw $t7, 0($t7)");                             //val of i
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t7");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            if (temp_var.second->dim > 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(temp_var.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t7, $s6");
                insert_asm("mflo $t7");
                insert_asm("add $t8, $t8, $t7"); //i*n2+j
            }
            if (temp_var.second->is_struct == 1)
            {
                insert_asm("li $t7, " + to_string(temp_var.second->struct_size));
            }
            else
                insert_asm("li $t7, 4");
            insert_asm("mult $t8, $t7");
            insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t7");
        }
    }
    insert_asm("lwc1 " + reg_name + ", 0($s7)");
}

void get_struct_element(pair<string, Entry *> temp_var, string reg_name, int struct_type)
{
    if (curr_function == "main")
    {
        if (struct_type == 1)
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            if (temp_var.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off)); // i offset in a[i].val
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                     //val of i
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (temp_var.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("lw $s6, 0($s6)");
            insert_asm("add $s7, $s6, $t8");
            
        }
    }
    else
    {
        if (struct_type == 1)
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            if (temp_var.second->is_array == 1)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off)); // i offset in a[i].val
                insert_asm("addi $s7, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                     //val of i
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (temp_var.second->is_array == 2)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("lw $s6, 0($s6)");
            insert_asm("add $s7, $s6, $t8");
            
        }
    }
    insert_asm("lw " + reg_name + ", 0($s7)");
}

void get_struct_element_float(pair<string, Entry *> temp_var, string reg_name, int struct_type)
{
    if (curr_function == "main")
    {
        if (struct_type == 1)
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            if (temp_var.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off)); // i offset in a[i].val
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                     //val of i
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (temp_var.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("lw $s6, 0($s6)");
            insert_asm("add $s7, $s6, $t8");
            
        }
    }
    else
    {
        if (struct_type == 1)
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            if (temp_var.second->is_array == 1)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off)); // i offset in a[i].val
                insert_asm("addi $s7, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                     //val of i
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (temp_var.second->is_array == 2)
            {
                insert_asm("li $s7, " + to_string(temp_var.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(temp_var.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
        }
        else
        {
            insert_asm("li $t8, " + to_string(temp_var.second->size));
            //insert_asm("li $t7, 4");
            //insert_asm("mult $t8, $t7");
            //insert_asm("mflo $t7");
            insert_asm("li $s6, " + to_string(temp_var.second->offset)); // put the offset in s6
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("lw $s6, 0($s6)");
            insert_asm("add $s7, $s6, $t8");
            
        }
    }
    insert_asm("lwc1 " + reg_name + ", 0($s7)");
}

void print_asm(string asm_name)
{
    asm_name.pop_back();
    asm_name.pop_back();
    asm_name = asm_name + ".asm";
    asm_file.open(asm_name);
    for (int m = 0; m < _data.size(); m++)
    {
        asm_file << _data[m] << endl;
    }
    asm_file << endl;
    asm_file << ".text" << endl;
    //print main function
    asm_file << "main"
             << ":" << endl;
    for (int i = 0; i < asm_code["main"].size(); ++i)
        asm_file << '\t' << asm_code["main"][i] << endl;
    asm_file << endl;

    map<string, std::vector<string>>::iterator it;
    it = asm_code.find("main");
    asm_code.erase(it);
    for (auto it = asm_code.begin(); it != asm_code.end(); ++it)
    {
        //printCodeFunc(it->first);
        string a = it->first;
        asm_file << a << ":" << endl;
        for (int i = 0; i < asm_code[a].size(); ++i)
            asm_file << '\t' << asm_code[a][i] << endl;
        asm_file << endl;
    }
    //asm_file.close();
}

void add_comment(int i)
{
    insert_asm("# " + to_string(i + 1) + " : " + emit_list[i].ans.first + " = " + emit_list[i].operand_1.first + " " + emit_list[i].op.first + " " + emit_list[i].operand_2.first);
}

void func_start_code()
{
    //cout<<"hello::"<<curr_function<<"tt"<<endl;
    if (curr_function == "main")
    {
        //cout<<"in main asm\n";
        // set the frame pointer of the callee
        insert_asm("sub $sp, $sp, 40");
        insert_asm("la $fp, ($sp)");
        int size_func = lookup("main")->size;
        // allocate space for the registers by updating the stack pointer
        insert_asm("sub $sp, $sp, " + to_string(size_func));
    }
    else
    {
        //cout<<"inside other\n";
        int size_func = lookup(curr_function)->size + 4;
        // allocate space for the registers by updating the stack pointer
        //insert_asm("sub $sp, $sp, 72");
        insert_asm("sub $sp, $sp, 32");
        insert_asm("sw $a0, 8($sp)");
        insert_asm("sw $s0, 12($sp)");
        insert_asm("sw $s1, 16($sp)");
        insert_asm("sw $s2, 20($sp)");
        insert_asm("sw $s3, 24($sp)");
        insert_asm("sw $s4, 28($sp)");

        // store return address of the caller
        insert_asm("sw $ra, 0($sp)");

        // store the frame pointe of the caller
        insert_asm("sw $fp, 4($sp)");

        // set the frame pointer of the callee
        // insert_asm("la $fp, 72($sp)");
        insert_asm("la $fp, 32($sp)");

        // create space for local data
        insert_asm("sub $sp, $sp, " + to_string(size_func));

        //copy parameters
        string parameterList = args_map[curr_function];
        int paramNum = 0;
        int paramSize = REG_SPACE;
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
                    if (temp1[0] == 'S')
                    {
                        int k = temp1.find('*');
                        string x = temp1.substr(0, k);
                        paramSize += get_size(x);
                    }
                    //insert_asm("li $s6, " + to_string(paramSize));
                    insert_asm("sub $s7, $fp, " + to_string(paramSize));
                    // cout << temp1 << endl;
                    if (temp1 == "float")
                    {
                        if (paramNum == 0)
                        {
                            insert_asm("swc1 $f12, 0($s7)");
                        }
                        else if (paramNum == 1)
                        {
                            insert_asm("swc1 $f14, 0($s7)");
                        }
                    }
                    else
                        insert_asm("sw $a" + to_string(paramNum) + ", 0($s7)");
                }
                // char a[50];
                // strcpy(a, temp1.c_str());
                paramSize += get_size(temp1);
                paramNum++;
            }
            if (paramNum < 4)
            {
                if (temp[0] == 'S')
                {
                    int k = temp.find('*');
                    string x = temp.substr(0, k);
                    paramSize += get_size(x);
                }
                //insert_asm("li $s6, " + to_string(paramSize));
                insert_asm("sub $s7, $fp, " + to_string(paramSize));
                // cout << temp << endl;
                if (temp == "float")
                {
                    if (paramNum == 0)
                    {
                        insert_asm("swc1 $f12, 0($s7)");
                    }
                    else if (paramNum == 1)
                    {
                        insert_asm("swc1 $f14, 0($s7)");
                    }
                }
                else
                    insert_asm("sw $a" + to_string(paramNum) + ", 0($s7)");
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
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6");
                insert_asm("lw $t8, 0($s7)");
                if (emit_list[i].operand_1.second->dim > 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //offset of i in a[i][j]
                    if (curr_function != "main")
                        insert_asm("addi $t9, " + to_string(REG_SPACE));
                    insert_asm("sub $t9, $fp, $t9");
                    insert_asm("lw $t9, 0($t9)");                                           //val of i
                    insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                    insert_asm("mult $t9, $s6");
                    insert_asm("mflo $t9");
                    insert_asm("add $t8, $t8, $t9"); //i*n2+j
                }
                if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
                }
                else
                    insert_asm("li $t9, 4");

                insert_asm("mult $t8, $t9");
                insert_asm("mflo $t9");                                                    //a[i]   i*4
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                insert_asm("add $s6, $s6, $t9");
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6"); 
                                                 // address
                insert_asm("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_array == 2)
            {
                //constant index
                //insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("sub $s7, $fp, "+to_string(emit_list[i].operand_1.second));
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                if (emit_list[i].operand_1.second->dim > 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //i in a[i][j]
                    insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                    insert_asm("mult $t9, $s6");
                    insert_asm("mflo $t9");
                    insert_asm("add $t8, $t8, $t9"); //i*n2+j
                }
                if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
                }
                else
                    insert_asm("li $t9, 4");
                insert_asm("mult $t8, $t9");
                insert_asm("mflo $t9");                                                    //a[i]   i*4
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                insert_asm("add $s6, $s6, $t9");
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6"); 
                                                 // address
                insert_asm("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 1)
            {
                //insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("li $t7, 4");
                //insert_asm("mult $t8, $t7");
                //insert_asm("mflo $t7");
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                if (emit_list[i].operand_1.second->is_struct_array == 1)
                {
                    insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off)); // i offset in a[i].val
                    if (curr_function != "main")
                        insert_asm("addi $s7, " + to_string(REG_SPACE));
                    insert_asm("sub $s7, $fp, $s7");
                    insert_asm("lw $s7, 0($s7)");                                                   //val of i
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size)); // i*struct_size
                    insert_asm("mult $s7, $t9");
                    insert_asm("mflo $s7");
                    insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
                }
                else if (emit_list[i].operand_1.second->is_struct_array == 2)
                {
                    insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off));         // 2 in a[2].val
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size)); // 2*struct_size
                    insert_asm("mult $s7, $t9");
                    insert_asm("mflo $s7");
                    insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
                }
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s6, $fp, $s6"); 
                insert_asm("add $s7, $s6, $t8");
                insert_asm("lw $t6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 2)
            {
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("li $t7, 4");
                //insert_asm("mult $t8, $t7");
                //insert_asm("mflo $t7");
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s6, $fp, $s6");
                insert_asm("lw $s6, 0($s6)");
                insert_asm("add $s7, $s6, $t8");
                insert_asm("lw $t6, 0($s7)");
            }
        }
        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
            reg1 = "$t6";
        else
            ////cout<<"in\n";
            reg1 = getReg(emit_list[i].operand_1);
        ////cout<<"::"<<reg1<<"\n";
        if (param_idx < 4)
        {
            //paramOff+=get_size(emit_list[i].operand_1.second->type);
            insert_asm("move $a" + to_string(param_idx) + ", " + reg1);
        }
        else
        {
            int paramNum = 0;
            int paramSize = REG_SPACE;
            //////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //char *a = "int"; // to check
            //char a[50];
            //strcpy(a,emit_list[i].operand_1.second->type.c_str());
            //paramSize += param_idx * get_size(convert_to_string("int"));
            string x = emit_list[i].operand_1.second->type;
            if (x[0] == 'S')
            {
                int k = x.find('*');
                string tmp = x.substr(0, k);
                paramOff += get_size(tmp);
            }
            paramSize += paramOff;
            insert_asm("li $s6, " + to_string(paramSize));
            insert_asm("sub $s7, $sp, $s6");
            insert_asm("sw " + reg1 + ", 0($s7)");
        }
        if (emit_list[i].operand_1.second->type == "char")
            paramOff += 4;
        else
        {
            paramOff += get_size(emit_list[i].operand_1.second->type);
        }
        param_idx++;
    }
    else
    { // if the param is constant
        if (param_idx < 4)
        {
            insert_asm("addi $a" + to_string(param_idx) + ",$0, " +
                       emit_list[i].operand_1.first);
        }
        else
        {
            int paramNum = 0;
            int paramSize = REG_SPACE;
            //char *a = "int";
            //paramSize += param_idx * get_size(convert_to_string("int"));
            paramSize += paramOff;
            //cout << paramSize << " " << paramOff + REG_SPACE << endl;
            insert_asm("addi $t9, $0, " + emit_list[i].operand_1.first);
            insert_asm("li $s6, " + to_string(paramSize));
            insert_asm("sub $s7, $sp, $s6");
            insert_asm("sw $t9, 0($s7)");
        }
        //if(emit_list[i].operand_1.second->type=="char") paramOff+=4;
        paramOff += get_size("int");
        param_idx++;
    }
}

void param_code_float(int i)
{
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second != NULL)
        {
            if (emit_list[i].operand_1.second->is_array == 1)
            { //array
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6");
                insert_asm("lw $t8, 0($s7)");
                if (emit_list[i].operand_1.second->dim > 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //offset of i in a[i][j]
                    if (curr_function != "main")
                        insert_asm("addi $t9, " + to_string(REG_SPACE));
                    insert_asm("sub $t9, $fp, $t9");
                    insert_asm("lw $t9, 0($t9)");                                           //val of i
                    insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                    insert_asm("mult $t9, $s6");
                    insert_asm("mflo $t9");
                    insert_asm("add $t8, $t8, $t9"); //i*n2+j
                }
                if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
                }
                else
                    insert_asm("li $t9, 4");

                insert_asm("mult $t8, $t9");
                insert_asm("mflo $t9");                                                    //a[i]   i*4
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                insert_asm("add $s6, $s6, $t9");
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6"); 
                                                 // address
                insert_asm("lwc1 $f6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_array == 2)
            {
                //constant index
                //insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("sub $s7, $fp, "+to_string(emit_list[i].operand_1.second));
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                if (emit_list[i].operand_1.second->dim > 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //i in a[i][j]
                    insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                    insert_asm("mult $t9, $s6");
                    insert_asm("mflo $t9");
                    insert_asm("add $t8, $t8, $t9"); //i*n2+j
                }
                if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
                }
                else
                    insert_asm("li $t9, 4");
                insert_asm("mult $t8, $t9");
                insert_asm("mflo $t9");                                                    //a[i]   i*4
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                insert_asm("add $s6, $s6, $t9");
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s6"); 
                                                 // address
                insert_asm("lwc1 $f6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 1)
            {
                //insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("li $t7, 4");
                //insert_asm("mult $t8, $t7");
                //insert_asm("mflo $t7");
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                if (emit_list[i].operand_1.second->is_struct_array == 1)
                {
                    insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off)); // i offset in a[i].val
                    if (curr_function != "main")
                        insert_asm("addi $s7, " + to_string(REG_SPACE));
                    insert_asm("sub $s7, $fp, $s7");
                    insert_asm("lw $s7, 0($s7)");                                                   //val of i
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size)); // i*struct_size
                    insert_asm("mult $s7, $t9");
                    insert_asm("mflo $s7");
                    insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
                }
                else if (emit_list[i].operand_1.second->is_struct_array == 2)
                {
                    insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off));         // 2 in a[2].val
                    insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size)); // 2*struct_size
                    insert_asm("mult $s7, $t9");
                    insert_asm("mflo $s7");
                    insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
                }
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s6, $fp, $s6"); 
                insert_asm("add $s7, $s6, $t8");
                insert_asm("lwc1 $f6, 0($s7)");
            }
            else if (emit_list[i].operand_1.second->is_struct == 2)
            {
                insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
                //insert_asm("li $t7, 4");
                //insert_asm("mult $t8, $t7");
                //insert_asm("mflo $t7");
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
                if (curr_function != "main")
                    insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $s6, $fp, $s6");
                insert_asm("lw $s6, 0($s6)");
                insert_asm("add $s7, $s6, $t8");
                insert_asm("lwc1 $f6, 0($s7)");
            }
        }
        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
            reg1 = "$f6";
        else
            ////cout<<"in\n";
            reg1 = getReg_float(emit_list[i].operand_1);
        ////cout<<"::"<<reg1<<"\n";
        if (param_idx == 0)
        {
            //paramOff+=get_size(emit_list[i].operand_1.second->type);
            insert_asm("mov.s $f12, " + reg1);
        }
        else if (param_idx == 1)
        {
            insert_asm("mov.s $f14, " + reg1);
        }
        else
        {
            int paramNum = 0;
            int paramSize = REG_SPACE;
            //////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //char *a = "int"; // to check
            //char a[50];
            //strcpy(a,emit_list[i].operand_1.second->type.c_str());
            //paramSize += param_idx * get_size(convert_to_string("int"));
            string x = emit_list[i].operand_1.second->type;
            if (x[0] == 'S')
            {
                int k = x.find('*');
                string tmp = x.substr(0, k);
                paramOff += get_size(tmp);
            }
            paramSize += paramOff;
            insert_asm("li $s6, " + to_string(paramSize));
            insert_asm("sub $s7, $sp, $s6");
            insert_asm("swc1 " + reg1 + ", 0($s7)");
        }
        if (emit_list[i].operand_1.second->type == "char")
            paramOff += 4;
        else
        {
            paramOff += get_size(emit_list[i].operand_1.second->type);
        }
        param_idx++;
    }
    else
    { // if the param is constant
        if (param_idx == 0)
        {
            insert_asm("li.s $f12," + emit_list[i].operand_1.first);
        }
        else if (param_idx == 1)
        {
            insert_asm("li.s $f14," + emit_list[i].operand_1.first);
        }
        else
        {
            int paramNum = 0;
            int paramSize = REG_SPACE;
            //char *a = "int";
            //paramSize += param_idx * get_size(convert_to_string("int"));
            paramSize += paramOff;
            //cout << paramSize << " " << paramOff + REG_SPACE << endl;
            insert_asm("li.s $f9, " + emit_list[i].operand_1.first);
            insert_asm("li $s6, " + to_string(paramSize));
            insert_asm("sub $s7, $sp, $s6");
            insert_asm("swc1 $f9, 0($s7)");
        }
        //if(emit_list[i].operand_1.second->type=="char") paramOff+=4;
        paramOff += get_size("float");
        param_idx++;
    }
}

void assign_op_code(int i)
{
    //cout<<"dim:"<<emit_list[i].ans.first<<" "<<emit_list[i].ans.second->dim<<endl;
    if (emit_list[i].ans.second->is_array == 1 || emit_list[i].ans.second->is_array == 2 || emit_list[i].ans.second->is_struct == 1 || emit_list[i].ans.second->is_struct == 2)
        reg3 = "$t7";
    else
    {
        reg3 = getReg(emit_list[i].ans);
        ////cout<<reg3<<"\n";
    }
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            get_arr_element(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            get_arr_element(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            get_struct_element(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            get_struct_element(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else
            reg2 = getReg(emit_list[i].operand_1);
        insert_asm("move " + reg3 + ", " + reg2);
    }
    else
    {

        insert_asm("addi " + reg3 + ", $0, " + emit_list[i].operand_1.first);
    }

    if (emit_list[i].ans.second->is_array == 1)
    {
        if (curr_function == "main")
        {
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                     //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm(
                "sub $s7, $fp, $s6"); 
        }
        else
        {
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->size));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //offset of i in a[i][j]
                insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                     //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t6, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t6, 4");
            insert_asm("mult $t8, $t6");
            insert_asm("mflo $t6");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t6");
        }

        insert_asm("sw $t7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_array == 2)
    {
        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm(
                "sub $s7, $fp, $s6"); 
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t6, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t6, 4");
            insert_asm("mult $t8, $t6");
            insert_asm("mflo $t6");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t6");
        }

        insert_asm("sw $t7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_struct == 1)
    {
        //struct.identifier

        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            if (emit_list[i].ans.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off)); // i offset in a[i].val
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                             //val of i
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (emit_list[i].ans.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("add $s7, $s6, $t8");
            insert_asm("sw $t7, 0($s7)");
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            if (emit_list[i].ans.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off)); // i offset in a[i].val
                insert_asm("addi $s7, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                             //val of i
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (emit_list[i].ans.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
            insert_asm("sw $t7, 0($s7)");
        }

        //add for non main func also
    }
    else if (emit_list[i].ans.second->is_struct == 2)
    {
        //struct->identifier size contains id off in struct. offset contains ptr offset in func
        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("sub $s6, $fp, $s6");
            //insert_asm("lw $s7, 0($s6)");
            insert_asm("lw $s6, 0($s6)");
            //insert_asm("lw $s6, 10");
            insert_asm("add $s6, $s6, $t8");
            //insert_asm(
            //    "sub $s7, $fp, $s6"); 
            insert_asm("sw $t7, 0($s6)");
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6");
            //insert_asm("lw $s7, 0($s6)");
            insert_asm("lw $s6, 0($s6)");
            //insert_asm("lw $s6, 10");
            insert_asm("add $s6, $s6, $t8");
            //insert_asm(
            //    "sub $s7, $fp, $s6"); 
            insert_asm("sw $t7, 0($s6)");
        }

        //add for non main func also
    }
}

void assign_float(int i)
{
    if (emit_list[i].ans.second->is_array == 1 || emit_list[i].ans.second->is_array == 2 || emit_list[i].ans.second->is_struct == 1 || emit_list[i].ans.second->is_struct == 2)
        reg3 = "$f7";
    else
    {
        reg3 = getReg_float(emit_list[i].ans);
    }
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            get_arr_element_float(emit_list[i].operand_1, "$f6", 1);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            get_arr_element_float(emit_list[i].operand_1, "$f6", 2);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            get_struct_element_float(emit_list[i].operand_1, "$f6", 1);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            get_struct_element_float(emit_list[i].operand_1, "$f6", 2);
            reg2 = "$f6";
        }
        else
            reg2 = getReg_float(emit_list[i].operand_1);

        insert_asm("mov.s " + reg3 + ", " + reg2);
    }
    else
    {
        insert_asm("li.s " + reg3 + ", " + emit_list[i].operand_1.first);
    }

    if (emit_list[i].ans.second->is_array == 1)
    {
        if (curr_function == "main")
        {
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                     //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm(
                "sub $s7, $fp, $s6"); 
        }
        else
        {
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->size));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //offset of i in a[i][j]
                insert_asm("addi $s6, " + to_string(REG_SPACE));
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                     //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t6, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t6, 4");
            insert_asm("mult $t8, $t6");
            insert_asm("mflo $t6");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t6");
        }

        insert_asm("swc1 $f7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_array == 2)
    {
        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm(
                "sub $s7, $fp, $s6"); 
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            if (emit_list[i].ans.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].ans.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].ans.second->is_struct != 0)
            {
                insert_asm("li $t6, " + to_string(emit_list[i].ans.second->struct_size));
            }
            else
                insert_asm("li $t6, 4");
            insert_asm("mult $t8, $t6");
            insert_asm("mflo $t6");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset));
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            insert_asm("sub $s7, $t8, $t6");
        }

        insert_asm("swc1 $f7, 0($s7)");
    }
    else if (emit_list[i].ans.second->is_struct == 1)
    {
        //struct.identifier

        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            if (emit_list[i].ans.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off)); // i offset in a[i].val
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                             //val of i
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (emit_list[i].ans.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("sub $s6, $fp, $s6");
            insert_asm("add $s7, $s6, $t8");
            insert_asm("swc1 $f7, 0($s7)");
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            if (emit_list[i].ans.second->is_struct_array == 1)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off)); // i offset in a[i].val
                insert_asm("addi $s7, " + to_string(REG_SPACE));
                insert_asm("sub $s7, $fp, $s7");
                insert_asm("lw $s7, 0($s7)");                                             //val of i
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // i*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+i*struct_size
            }
            else if (emit_list[i].ans.second->is_struct_array == 2)
            {
                insert_asm("li $s7, " + to_string(emit_list[i].ans.second->off));         // 2 in a[2].val
                insert_asm("li $t9, " + to_string(emit_list[i].ans.second->struct_size)); // 2*struct_size
                insert_asm("mult $s7, $t9");
                insert_asm("mflo $s7");
                insert_asm("add $s6, $s6, $s7"); // a+2*struct_size
            }
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6"); 
            insert_asm("add $s7, $s6, $t8");
            insert_asm("swc1 $f7, 0($s7)");
        }

        //add for non main func also
    }
    else if (emit_list[i].ans.second->is_struct == 2)
    {
        //struct->identifier size contains id off in struct. offset contains ptr offset in func
        if (curr_function == "main")
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("sub $s6, $fp, $s6");
            //insert_asm("lw $s7, 0($s6)");
            insert_asm("lw $s6, 0($s6)");
            //insert_asm("lw $s6, 10");
            insert_asm("add $s6, $s6, $t8");
            //insert_asm(
            //    "sub $s7, $fp, $s6"); 
            insert_asm("swc1 $f7, 0($s6)");
        }
        else
        {
            insert_asm("li $t8, " + to_string(emit_list[i].ans.second->size));
            //insert_asm("li $t9, 4");
            //insert_asm("mult $t8, $t9");
            //insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].ans.second->offset)); // put the offset in s6
            insert_asm("addi $s6, " + to_string(REG_SPACE));
            insert_asm("sub $s6, $fp, $s6");
            //insert_asm("lw $s7, 0($s6)");
            insert_asm("lw $s6, 0($s6)");
            //insert_asm("lw $s6, 10");
            insert_asm("add $s6, $s6, $t8");
            //insert_asm(
            //    "sub $s7, $fp, $s6"); 
            insert_asm("swc1 $f7, 0($s6)");
        }

        //add for non main func also
    }

    return;
}

void int_to_real(int i)
{
    reg3 = getReg_float(emit_list[i].ans);

    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            get_arr_element(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            get_arr_element(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            get_struct_element(emit_list[i].operand_1, "$t6", 1);
            reg2 = "$t6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            get_struct_element(emit_list[i].operand_1, "$t6", 2);
            reg2 = "$t6";
        }
        else
            reg2 = getReg(emit_list[i].operand_1);
        //insert_asm("move " + reg3 + ", " + reg2);
    }
    else
    {
        reg2 = "$t6";
        insert_asm("addi $t6, $0, " + emit_list[i].operand_1.first);
    }
    insert_asm("mtc1 " + reg2 + ", " + reg3);
    insert_asm("cvt.s.w " + reg3 + ", " + reg3);

    return;
}

void real_to_int(int i)
{
    reg3 = getReg(emit_list[i].ans);
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            get_arr_element_float(emit_list[i].operand_1, "$f6", 1);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            get_arr_element_float(emit_list[i].operand_1, "$f6", 2);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            get_struct_element_float(emit_list[i].operand_1, "$f6", 1);
            reg2 = "$f6";
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            get_struct_element_float(emit_list[i].operand_1, "$f6", 2);
            reg2 = "$f6";
        }
        else
            reg2 = getReg_float(emit_list[i].operand_1);

        //insert_asm("mov.s " + reg3 + ", " + reg2);
    }
    else
    {
        reg2="$f6";
        insert_asm("li.s " + reg2 + ", " + emit_list[i].operand_1.first);
    }
    
    insert_asm("cvt.w.s "+reg2+", "+reg2);
    insert_asm("mfc1 "+reg3+", "+reg2);
    return;
}

void unary_and_code(int i)
{
    reg1 = getReg(emit_list[i].ans);
    int off = emit_list[i].operand_1.second->offset;
    //off = -off;
    string u = to_string(off);
    // insert_asm("add " + reg1 + ", $fp, " + u);

    if (emit_list[i].operand_1.second->is_array == 1)
    {

        insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
        insert_asm("sub $s7, $fp, $s6");
        insert_asm("lw $t8, 0($s7)");
        if (emit_list[i].operand_1.second->dim > 1)
        {
            insert_asm("li $t7, " + to_string(emit_list[i].operand_1.second->off)); //offset of i in a[i][j]
            insert_asm("sub $t7, $fp, $t7");
            insert_asm("lw $t7, 0($t7)");                                           //val of i
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
            insert_asm("mult $t7, $s6");
            insert_asm("mflo $t7");
            insert_asm("add $t8, $t8, $t7"); //i*n2+j
        }
        if (emit_list[i].operand_1.second->is_struct != 0)
        {
            insert_asm("li $t7, " + to_string(emit_list[i].operand_1.second->struct_size));
        }
        else
            insert_asm("li $t7, 4");
        insert_asm("mult $t8, $t7");
        insert_asm("mflo $t7");
        insert_asm("addi $t7, " + to_string(off));
        insert_asm("neg $t7, $t7");
        // u = string("$t7");
        insert_asm("add " + reg1 + ", $fp, $t7");
    }
    else if (emit_list[i].operand_1.second->is_array == 2)
    {

        insert_asm("li $t8, " + to_string(emit_list[i].operand_1.second->size));
        if (emit_list[i].operand_1.second->dim > 1)
        {
            insert_asm("li $t7, " + to_string(emit_list[i].operand_1.second->off)); //i in a[i][j]
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
            insert_asm("mult $t7, $s6");
            insert_asm("mflo $t7");
            insert_asm("add $t8, $t8, $t7"); //i*n2+j
        }
        if (emit_list[i].operand_1.second->is_struct != 0)
        {
            insert_asm("li $t7, " + to_string(emit_list[i].operand_1.second->struct_size));
        }
        else
            insert_asm("li $t7, 4");
        insert_asm("mult $t8, $t7");
        insert_asm("mflo $t7");
        insert_asm("addi $t7, " + to_string(off));
        insert_asm("neg $t7, $t7");
        //u = string("$t7");
        insert_asm("add " + reg1 + ", $fp, $t7");
    }
    else if (emit_list[i].operand_1.second->is_struct == 1)
    {

        insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
        insert_asm("li $t7, " + to_string(off));
        if (emit_list[i].operand_1.second->is_struct_array == 1)
        {
            insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off)); // i offset in a[i].val
            insert_asm("sub $s7, $fp, $s7");
            insert_asm("lw $s7, 0($s7)");                                                   //val of i
            insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size)); // i*struct_size
            insert_asm("mult $s7, $t9");
            insert_asm("mflo $s7");
            insert_asm("add $t7 $t7, $s7"); // a+i*struct_size
        }
        else if (emit_list[i].operand_1.second->is_struct_array == 2)
        {
            insert_asm("li $s7, " + to_string(emit_list[i].operand_1.second->off));         // 2 in a[2].val
            insert_asm("li $t9, " + to_string(emit_list[i].operand_2.second->struct_size)); // 2*struct_size
            insert_asm("mult $s7, $t9");
            insert_asm("mflo $s7");
            insert_asm("add $t7, $t7, $s7"); // a+2*struct_size
        }
        insert_asm("sub $t7, $fp, $t7");
        insert_asm("add " + reg1 + ", $s6, $t7");
    }
    else if (emit_list[i].operand_1.second->is_struct == 2)
    {

        insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
        //insert_asm("li $t7, 4");
        //insert_asm("mult $t8, $t7");
        //insert_asm("mflo $t7");
        insert_asm("li $t7, " + to_string(off)); // put the offset in s6
        insert_asm("sub $t7, $fp, $t7");
        insert_asm("lw $t7, 0($t7)");
        insert_asm("add " + reg1 + ", $s6, $t7");
    }
    else
    {
        insert_asm("sub " + reg1 + ", $fp, " + to_string(off));
    }

    store_reg_info();
}

void unary_star_code(int i)
{
    reg1 = getReg(emit_list[i].ans);
    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
        reg2 = "$t6";
    else
        reg2 = getReg(emit_list[i].operand_1);
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].operand_1.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                           //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].operand_1.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            insert_asm("lw $t8, " + to_string(emit_list[i].operand_1.second->size));
            if (emit_list[i].operand_1.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].operand_1.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->size));

            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6

            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("add $s7, $t9, $s7");
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->size));

            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6

            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $s7, 0($s7)");
            insert_asm("add $s7, $t9, $s7");
            insert_asm("lw $t6, 0($s7)");
        }
    }
    insert_asm("lw " + reg1 + ", 0(" + reg2 + ")");
    store_reg_info();
}

void unary_star_code_float(int i)
{
    reg1 = getReg_float(emit_list[i].ans);
    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
        reg2 = "$t6";
    else
        reg2 = getReg(emit_list[i].operand_1);
    if (emit_list[i].operand_1.second != NULL)
    {
        if (emit_list[i].operand_1.second->is_array == 1)
        {
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->size));
            insert_asm("sub $s7, $fp, $s6");
            insert_asm("lw $t8, 0($s7)");
            if (emit_list[i].operand_1.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //offset of i in a[i][j]
                insert_asm("sub $t9, $fp, $t9");
                insert_asm("lw $t9, 0($t9)");                                           //val of i
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].operand_1.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_array == 2)
        {
            insert_asm("lw $t8, " + to_string(emit_list[i].operand_1.second->size));
            if (emit_list[i].operand_1.second->dim > 1)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->off)); //i in a[i][j]
                insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->col)); // n2 a[n1][n2]
                insert_asm("mult $t9, $s6");
                insert_asm("mflo $t9");
                insert_asm("add $t8, $t8, $t9"); //i*n2+j
            }
            if (emit_list[i].operand_1.second->is_struct != 0)
            {
                insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->struct_size));
            }
            else
                insert_asm("li $t9, 4");
            insert_asm("mult $t8, $t9");
            insert_asm("mflo $t9");
            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6
            insert_asm("add $s6, $s6, $t9");
            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_struct == 1)
        {
            insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->size));

            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6

            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("add $s7, $t9, $s7");
            insert_asm("lw $t6, 0($s7)");
        }
        else if (emit_list[i].operand_1.second->is_struct == 2)
        {
            insert_asm("li $t9, " + to_string(emit_list[i].operand_1.second->size));

            insert_asm("li $s6, " + to_string(emit_list[i].operand_1.second->offset)); // put the offset in s6

            insert_asm("sub $s7, $fp, $s6"); 
                                             // address
            insert_asm("lw $s7, 0($s7)");
            insert_asm("add $s7, $t9, $s7");
            insert_asm("lw $t6, 0($s7)");
        }
    }
    insert_asm("lwc1 " + reg1 + ", 0(" + reg2 + ")");
    store_reg_info();
}

void generate_asm()
{
    data_idx = 0;
    _data.push_back(".data");
    _data.push_back("reservedspace: .space 1024");
    _data.push_back("_newline: .asciiz \"\\n\"");
    curr_function = "main";
    asm_code[curr_function].push_back("");
    for (int i = 0; i < emit_list.size(); i++)
    {
        if (label_map.find(i) != label_map.end())
        {
            store_reg_info();
            insert_asm(label_map[i] + ":");
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
            param_idx = 0;
            paramOff = 0;
            curr_function = emit_list[i].op.first;
            //cout<<"is::::"<<curr_function<<endl;
            curr_function.erase(curr_function.begin(), curr_function.begin() + 5);
            curr_function.erase(curr_function.end() - 8, curr_function.end());
            add_comment(i);
            //cout<<"starting\n";
            func_start_code();
            //cout<<"finid\n";
        }
        else if (emit_list[i].line_no == -4)
        {
            // param constant strings
            add_comment(i);
            _data.push_back("DataString" + to_string(data_idx) + ": .asciiz " +
                            emit_list[i].operand_1.first);
            insert_asm("la $a" + to_string(param_idx) + ", DataString" +
                       to_string(data_idx));
            param_idx++;
            data_idx++;
        }
        else if (emit_list[i].line_no == -1)
        {
            add_comment(i);
            if (emit_list[i].op.first == "param")
            {
                //parameters before calling
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        param_code_float(i);
                    }
                    else
                    {
                        param_code(i);
                    }
                }
                else
                {
                    int k = emit_list[i].operand_1.first.find_first_of('.');
                    if (k < 0)
                    {
                        param_code(i);
                    }
                    else
                        param_code_float(i);
                }
            }
            else if (emit_list[i].op.first == "=" || emit_list[i].op.first == "realtoint" || emit_list[i].op.first == "inttoreal")
            {
                //cout<<"in\n";
                //eqaulity operator
                //cout<<emit_list[i].ans.second->type<<endl;
                if (emit_list[i].op.first == "realtoint")
                {
                    real_to_int(i);
                }
                else if (emit_list[i].op.first == "inttoreal")
                {
                    int_to_real(i);
                }
                else if (emit_list[i].ans.second->type == "float")
                {
                    assign_float(i);
                }
                else
                    assign_op_code(i);
            }
            else if (emit_list[i].op.first == "unary&")
            {
                unary_and_code(i);
            }
            else if (emit_list[i].op.first == "unary*")
            {
                if (emit_list[i].ans.second->type == "float")
                {
                    unary_star_code_float(i);
                }
                else
                    unary_star_code(i);
            }
            else if (emit_list[i].op.first == "unary-")
            {
                if (emit_list[i].ans.second->type == "float")
                {
                    reg1 = getReg_float(emit_list[i].ans);
                    if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                            reg2 = "$f6";
                        else
                            reg2 = getReg_float(emit_list[i].operand_1);
                        if (emit_list[i].operand_1.second != NULL)
                        {
                            if (emit_list[i].operand_1.second->is_array == 1)
                            {
                                get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                            }
                            else if (emit_list[i].operand_1.second->is_array == 2)
                            {
                                get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                            }
                            if (emit_list[i].operand_1.second->is_struct == 1)
                            {
                                get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                            }
                            else if (emit_list[i].operand_1.second->is_struct == 2)
                            {
                                get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                            }
                        }
                        insert_asm("neg.s " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("li.s " + reg1 + ", -" + emit_list[i].operand_1.first);
                }
                else
                {
                    reg1 = getReg(emit_list[i].ans);
                    if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                            reg2 = "$t6";
                        else
                            reg2 = getReg(emit_list[i].operand_1);
                        if (emit_list[i].operand_1.second != NULL)
                        {
                            if (emit_list[i].operand_1.second->is_array == 1)
                            {
                                get_arr_element(emit_list[i].operand_1, reg2, 1);
                            }
                            else if (emit_list[i].operand_1.second->is_array == 2)
                            {
                                get_arr_element(emit_list[i].operand_1, reg2, 2);
                            }
                            if (emit_list[i].operand_1.second->is_struct == 1)
                            {
                                get_struct_element(emit_list[i].operand_1, reg2, 1);
                            }
                            else if (emit_list[i].operand_1.second->is_struct == 2)
                            {
                                get_struct_element(emit_list[i].operand_1, reg2, 2);
                            }
                        }
                        insert_asm("neg " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("addi " + reg1 + ", $0, -" + emit_list[i].operand_1.first);
                }
            }
            else if (emit_list[i].op.first == "unary+")
            {
                if (emit_list[i].ans.second->type == "float")
                {
                    reg1 = getReg_float(emit_list[i].ans);

                    if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                            reg2 = "$f6";
                        else
                            reg2 = getReg_float(emit_list[i].operand_1);

                        if (emit_list[i].operand_1.second->is_array == 1)
                        {
                            get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_array == 2)
                        {
                            get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                        }
                        if (emit_list[i].operand_1.second->is_struct == 1)
                        {
                            get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_struct == 2)
                        {
                            get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                        }
                        insert_asm("lwc1 " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("li.s " + reg1 + ", " + emit_list[i].operand_1.first);
                }
                else
                {
                    reg1 = getReg(emit_list[i].ans);

                    if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                            reg2 = "$t6";
                        else
                            reg2 = getReg(emit_list[i].operand_1);

                        if (emit_list[i].operand_1.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_1, reg2, 2);
                        }
                        if (emit_list[i].operand_1.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_1, reg2, 1);
                        }
                        else if (emit_list[i].operand_1.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_1, reg2, 2);
                        }
                        insert_asm("lw " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("addi " + reg1 + ", $0, " + emit_list[i].operand_1.first);
                }
            }
            else if (emit_list[i].op.first == "~")
            {
                reg1 = getReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second != NULL)
                {
                    reg2 = getReg(emit_list[i].operand_1);
                    insert_asm("not " + reg1 + ", " + reg2);
                }
                else
                    insert_asm("not " + reg1 + ", " + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "!")
            {
                reg1 = getReg(emit_list[i].ans);
                if (emit_list[i].operand_1.second != NULL)
                {
                    reg2 = getReg(emit_list[i].operand_1);
                    insert_asm("not " + reg1 + ", " + reg2);
                }
                else
                    insert_asm("not " + reg1 + ", " + emit_list[i].operand_1.first);
            }
            else if (emit_list[i].op.first == "+real")
            {
                reg1 = getReg_float(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$f6";
                    else
                        reg2 = getReg_float(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$f6";
                    insert_asm("li.s " + reg2 + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$f7";
                    else
                        reg3 = getReg_float(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //insert_asm("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$f7";
                    op_2 = 1;
                    insert_asm("li.s " + reg3 + ", " + emit_list[i].operand_2.first);
                }
                insert_asm("add.s " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "+int")
            {

                reg1 = getReg(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //insert_asm("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$t7";
                    op_2 = 1;
                    insert_asm("addi " + reg3 + ", $0" + ", " + emit_list[i].operand_2.first);
                }
                insert_asm("add " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "-real")
            {
                reg1 = getReg_float(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$f6";
                    else
                        reg2 = getReg_float(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$f6";
                    insert_asm("li.s " + reg2 + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$f7";
                    else
                        reg3 = getReg_float(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //insert_asm("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$f7";
                    op_2 = 1;
                    insert_asm("li.s " + reg3 + ", " + emit_list[i].operand_2.first);
                }
                insert_asm("sub.s " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "-int")
            {
                reg1 = getReg(emit_list[i].ans);
                int op_1 = 0, op_2 = 0; // to check whether they are constants
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                    //insert_asm("add " + reg1 + ", " + reg2 + ", " + reg3);
                }
                else
                {
                    reg3 = "$t7";
                    op_2 = 1;
                    insert_asm("addi " + reg3 + ", $0" + ", " + emit_list[i].operand_2.first);
                }
                insert_asm("sub " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "*real")
            {
                reg1 = getReg_float(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$f6";
                    else
                        reg2 = getReg_float(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$f6";
                    insert_asm("li.s " + reg2 + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$f7";
                    else
                        reg3 = getReg_float(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$f7";
                    insert_asm("li.s " + reg3 + ", " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("mul.s " + reg1 + ", " + reg2 + ", " + reg3);
                //insert_asm("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "*int")
            {
                reg1 = getReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    insert_asm("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("mult " + reg2 + ", " + reg3);
                insert_asm("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "/real")
            {
                reg1 = getReg_float(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$f6";
                    else
                        reg2 = getReg_float(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$f6";
                    insert_asm("li.s " + reg2 + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2)
                        reg3 = "$f7";
                    else
                        reg3 = getReg_float(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element_float(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$f7";
                    insert_asm("li.s " + reg3 + ", " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("div.s " + reg1 + ", " + reg2 + ", " + reg3);
                //insert_asm("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "/int")
            {
                reg1 = getReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    insert_asm("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("div " + reg2 + ", " + reg3);
                insert_asm("mflo " + reg1);
            }
            else if (emit_list[i].op.first == "%")
            {
                reg1 = getReg(emit_list[i].ans);

                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_struct == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_struct == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    insert_asm("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("div " + reg2 + ", " + reg3);
                insert_asm("mfhi " + reg1);
            }
            else if (emit_list[i].op.first == "&" || emit_list[i].op.first == "|" || emit_list[i].op.first == "^" || emit_list[i].op.first == ">>" || emit_list[i].op.first == "<<")
            {
                reg1 = getReg(emit_list[i].ans);
                string op = emit_list[i].op.first;
                if (emit_list[i].operand_1.second != NULL)
                {
                    if (emit_list[i].operand_1.second->is_array == 1 || emit_list[i].operand_1.second->is_array == 2 || emit_list[i].operand_1.second->is_struct == 1 || emit_list[i].operand_1.second->is_struct == 2)
                        reg2 = "$t6";
                    else
                        reg2 = getReg(emit_list[i].operand_1);
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_array == 2)
                    {
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                    if (emit_list[i].operand_1.second->is_array == 1)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                    else if (emit_list[i].operand_1.second->is_struct == 2)
                    {
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    reg2 = "$t6";
                    insert_asm("addi " + reg2 + ", $0" + ", " + emit_list[i].operand_1.first);
                    // operand_1 is constant
                    //op_1 = 1;
                }
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (emit_list[i].operand_2.second->is_array == 1 || emit_list[i].operand_2.second->is_array == 2 || emit_list[i].operand_2.second->is_struct == 1 || emit_list[i].operand_2.second->is_struct == 2)
                        reg3 = "$t7";
                    else
                        reg3 = getReg(emit_list[i].operand_2);
                    if (emit_list[i].operand_2.second != NULL)
                    {
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_array == 2)
                        {
                            get_arr_element(emit_list[i].operand_2, reg3, 2);
                        }
                        if (emit_list[i].operand_2.second->is_array == 1)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 1);
                        }
                        else if (emit_list[i].operand_2.second->is_struct == 2)
                        {
                            get_struct_element(emit_list[i].operand_2, reg3, 2);
                        }
                    }
                }
                else
                {
                    reg3 = "$t7";
                    insert_asm("addi " + reg3 + ", $0, " + emit_list[i].operand_2.first);
                    //insert_asm("mult " + reg2 + ", $t9");
                    //insert_asm("mflo " + reg1);
                }
                insert_asm("div " + reg2 + ", " + reg3);
                insert_asm("mflo " + reg1);
                if (op == "&")
                    insert_asm("and " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "|")
                    insert_asm("or " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "^")
                    insert_asm("xor " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == "<<")
                    insert_asm("sll " + reg1 + ", " + reg2 + ", " + reg3);
                else if (op == ">>")
                    insert_asm("sra " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (emit_list[i].op.first == "<" || emit_list[i].op.first == ">" || emit_list[i].op.first == "GE_OP" || emit_list[i].op.first == "LE_OP" || emit_list[i].op.first == "EQ_OP" || emit_list[i].op.first == "NE_OP")
            {
                // int is_float;
                string op = emit_list[i].op.first;
                if (emit_list[i].operand_2.second == NULL)
                {
                    int k = emit_list[i].operand_2.first.find_first_of('.');
                    if (k < 0)
                    {
                        insert_asm("addi $t6, $0, " + emit_list[i].operand_2.first);
                        reg1 = "$t6";
                    }
                    else
                    {
                        is_float = 1;
                        insert_asm("li.s $f6, " + emit_list[i].operand_2.first);
                        reg1 = "$f6";
                    }
                }
                else if (emit_list[i].operand_2.second->is_array == 1)
                {
                    if (emit_list[i].operand_2.second->type == "float")
                    {
                        is_float = 1;
                        reg1 = "$f6";
                        get_arr_element_float(emit_list[i].operand_2, reg1, 1);
                    }
                    else
                    {
                        reg1 = "$t6";
                        get_arr_element(emit_list[i].operand_2, reg1, 1);
                    }
                }
                else if (emit_list[i].operand_2.second->is_array == 2)
                {
                    if (emit_list[i].operand_2.second->type == "float")
                    {
                        is_float = 1;
                        reg1 = "$f6";
                        get_arr_element_float(emit_list[i].operand_2, reg1, 2);
                    }
                    else
                    {
                        reg1 = "$t6";
                        get_arr_element(emit_list[i].operand_2, reg1, 2);
                    }
                }
                else if (emit_list[i].operand_2.second->is_struct == 1)
                {
                    if (emit_list[i].operand_2.second->type == "float")
                    {
                        is_float = 1;
                        reg1 = "$f6";
                        get_struct_element_float(emit_list[i].operand_2, reg1, 1);
                    }
                    else
                    {
                        reg1 = "$t6";
                        get_struct_element(emit_list[i].operand_2, reg1, 1);
                    }
                }
                else if (emit_list[i].operand_2.second->is_struct == 2)
                {
                    if (emit_list[i].operand_2.second->type == "float")
                    {
                        is_float = 1;
                        reg1 = "$f6";
                        get_struct_element_float(emit_list[i].operand_2, reg1, 2);
                    }
                    else
                    {
                        reg1 = "$t6";
                        get_struct_element(emit_list[i].operand_2, reg1, 2);
                    }
                }
                else
                {
                    if (emit_list[i].operand_2.second->type == "float")
                    {
                        is_float = 1;
                        reg1 = getReg_float(emit_list[i].operand_2);
                    }
                    else
                    {
                        reg1 = getReg(emit_list[i].operand_2);
                    }
                }
                if (emit_list[i].operand_1.second == NULL)
                {
                    int k = emit_list[i].operand_1.first.find_first_of('.');
                    if (k < 0)
                    {
                        insert_asm("addi $t7, $0, " + emit_list[i].operand_2.first);
                        reg2 = "$t7";
                    }
                    else
                    {
                        is_float = 1;
                        insert_asm("li.s $f7, " + emit_list[i].operand_2.first);
                        reg2 = "$f7";
                    }
                }
                else if (emit_list[i].operand_1.second->is_array == 1)
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        is_float = 1;
                        reg2 = "$f7";
                        get_arr_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else
                    {
                        reg2 = "$t7";
                        get_arr_element(emit_list[i].operand_1, reg2, 1);
                    }
                }
                else if (emit_list[i].operand_1.second->is_array == 2)
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        is_float = 1;
                        reg2 = "$f7";
                        get_arr_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    else
                    {
                        reg2 = "$t7";
                        get_arr_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else if (emit_list[i].operand_1.second->is_struct == 1)
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        is_float = 1;
                        reg2 = "$f7";
                        get_struct_element_float(emit_list[i].operand_1, reg2, 1);
                    }
                    else
                    {
                        reg2 = "$t7";
                        get_struct_element(emit_list[i].operand_1, reg2, 1);
                    }
                }
                else if (emit_list[i].operand_1.second->is_struct == 2)
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        is_float = 1;
                        reg2 = "$f7";
                        get_struct_element_float(emit_list[i].operand_1, reg2, 2);
                    }
                    else
                    {
                        reg2 = "$t7";
                        get_struct_element(emit_list[i].operand_1, reg2, 2);
                    }
                }
                else
                {
                    if (emit_list[i].operand_1.second->type == "float")
                    {
                        is_float = 1;
                        reg2 = getReg_float(emit_list[i].operand_1);
                    }
                    else
                    {
                        reg2 = getReg(emit_list[i].operand_1);
                    }
                }

                if (emit_list[i].ans.second->type == "float")
                {
                    is_float = 1;
                    reg3 = getReg_float(emit_list[i].ans);
                }
                else
                {
                    reg3 = getReg(emit_list[i].ans);
                }

                if (op == "<")
                {
                    if (is_float)
                    {
                        insert_asm("c.lt.s " + reg2 + ", " + reg1);
                    }
                    else
                        insert_asm("slt " + reg3 + ", " + reg2 + ", " + reg1);
                }
                else if (op == ">")
                {
                    if (is_float)
                    {
                        insert_asm("c.lt.s " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("sgt " + reg3 + ", " + reg2 + ", " + reg1);
                }
                else if (op == "GE_OP")
                {
                    if (is_float)
                    {
                        insert_asm("c.le.s " + reg1 + ", " + reg2);
                    }
                    else
                        insert_asm("sge " + reg3 + ", " + reg2 + ", " + reg1);
                }
                else if (op == "LE_OP")
                {
                    if (is_float)
                    {
                        insert_asm("c.le.s " + reg2 + ", " + reg1);
                    }
                    else
                        insert_asm("sle " + reg3 + ", " + reg2 + ", " + reg1);
                }
                else if (op == "EQ_OP")
                {
                    if (is_float)
                    {
                        insert_asm("c.eq.s " + reg2 + ", " + reg1);
                    }
                    else
                        insert_asm("seq " + reg3 + ", " + reg2 + ", " + reg1);
                }
                else if (op == "NE_OP")
                {
                    if (is_float)
                    {
                        insert_asm("c.ne.s " + reg2 + ", " + reg1);
                    }
                    else
                        insert_asm("sne " + reg3 + ", " + reg2 + ", " + reg1);
                }
                // if(is_float){
                //     insert_asm("mov.s")
                // }
            }
            else if (emit_list[i].op.first == "RETURN")
            {
                // retuning
                if (curr_function == "main")
                {
                    insert_asm("li $a0, 0");
                    insert_asm("li $v0, 10");
                    insert_asm("syscall");
                }
                else
                {
                    if (emit_list[i].operand_1.first == "")
                    {
                        // only return;
                    }
                    else if (emit_list[i].operand_1.second != NULL)
                    {
                        if (emit_list[i].operand_1.second->type == "float")
                        {
                            reg1 = getReg_float(emit_list[i].operand_1);
                            insert_asm("mov.s $f0, " + reg1);
                        }
                        else
                        {
                            reg1 = getReg(emit_list[i].operand_1);
                            insert_asm("move $v0, " + reg1);
                        }
                    }
                    else
                    {
                        int k = emit_list[i].operand_1.first.find_first_of('.');
                        if (k < 0)
                        {
                            insert_asm("li $v0, " + emit_list[i].operand_1.first);
                        }
                        else
                            insert_asm("li.s $f0, " + emit_list[i].operand_1.first);
                    }
                    insert_asm("b " + curr_function + "end");
                }
            }
            //library functions implementation
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "print_float")
            {
                //printing one integer
                insert_asm("li $v0, 2");
                insert_asm("syscall");
                param_idx = 0;
                paramOff = 0;
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "print_int")
            {
                //printing one integer
                insert_asm("li $v0, 1");
                insert_asm("syscall");
                param_idx = 0;
                paramOff = 0;
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "print_char")
            {
                // printing one char
                insert_asm("li $v0, 11");
                insert_asm("syscall");
                param_idx = 0;
                paramOff = 0;
                //insert_asm("li $v0, 11");
                //insert_asm("syscall");
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "print_string")
            {
                // printing string
                // string is already in a0;
                insert_asm("li $v0, 4");
                insert_asm("syscall");
                param_idx = 0;
                paramOff = 0;
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "scan_int")
            {
                reg1 = getReg(emit_list[i].ans);
                insert_asm("li $v0, 5");
                insert_asm("syscall");
                insert_asm("move " + reg1 + ", $v0");
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "scan_char")
            {
                reg1 = getReg(emit_list[i].ans);
                insert_asm("li $v0, 12");
                insert_asm("syscall");
                insert_asm("move " + reg1 + ", $v0");
            }
            else if (emit_list[i].op.first == "CALL" && emit_list[i].operand_1.first == "scan_float")
            {
                reg1 = getReg_float(emit_list[i].ans);
                insert_asm("li $v0, 6");
                insert_asm("syscall");
                insert_asm("mov.s " + reg1 + ", $f0");
            }
            else if (emit_list[i].op.first == "CALL")
            {
                insert_asm("jal " + emit_list[i].operand_1.first);
                if (emit_list[i].ans.second != NULL)
                {
                    if (emit_list[i].ans.second->type == "float")
                    {
                        reg1 = getReg_float(emit_list[i].ans);
                        insert_asm("mov.s " + reg1 + ", $f0");
                        param_idx = 0;
                        paramOff = 0;
                    }
                    else
                    {
                        reg1 = getReg(emit_list[i].ans);
                        insert_asm("move " + reg1 + ", $v0");
                        param_idx = 0;
                        paramOff = 0;
                    }
                }
            }
        }
        else if (emit_list[i].line_no == -3 && curr_function != "main")
        {
            if (i > 0 && emit_list[i - 1].line_no == -2)
            {
                //just the function definition (mutual recursion )
                continue;
            }
            add_comment(i);
            //returns  from non main function
            insert_asm(curr_function + "end:");

            // Removing the local data of the functions
            int sizeEnd = lookup(curr_function)->size + 4;
            insert_asm("addi $sp, $sp, " + to_string(sizeEnd));

            
            insert_asm("lw $ra, 0($sp)");
            insert_asm("lw $fp, 4($sp)");
            insert_asm("lw $a0, 8($sp)");

            insert_asm("lw $s0, 12($sp)");
            insert_asm("lw $s1, 16($sp)");
            insert_asm("lw $s2, 20($sp)");
            insert_asm("lw $s3, 24($sp)");
            insert_asm("lw $s4, 28($sp)");
            insert_asm("addi $sp, $sp, 32");
            // jump to the calling procedure
            insert_asm("jr $ra");
        }
        else
        {
            add_comment(i);
            // jump statements
            if (emit_list[i].op.first == "GOTO" && emit_list[i].operand_1.first == "")
            {
                store_reg_info();
                insert_asm("j " + label_map[emit_list[i].line_no]);
            }
            else if (emit_list[i].op.first == "GOTO" &&
                     emit_list[i].operand_1.first == "IF")
            {
                store_reg_info();
                if (emit_list[i].operand_2.second != NULL)
                {
                    if (is_float == 1)
                    {
                        insert_asm("bc1t " + label_map[emit_list[i].line_no]);
                    }
                    else
                    {
                        reg1 = getReg(emit_list[i].operand_2);
                        insert_asm("bne $0, " + reg1 + ", " +
                                   label_map[emit_list[i].line_no]);
                    }
                }
                else
                {
                    insert_asm("addi $t9, $0, " + emit_list[i].operand_2.first);
                    insert_asm("bne $0, $t9, " + label_map[emit_list[i].line_no]);
                }
                is_float = 0;
            }
        }
        store_reg_info(); //saving registers
    }
}

void initialize_reg()
{
    free_reg.push({"$t0", NULL});
    free_reg.push({"$t1", NULL});
    free_reg.push({"$t2", NULL});
    free_reg.push({"$t3", NULL});
    free_reg.push({"$t4", NULL});
    free_reg.push({"$t5", NULL});
    free_reg.push({"$s0", NULL});
    free_reg.push({"$s1", NULL});
    free_reg.push({"$s2", NULL});
    free_reg.push({"$s3", NULL});
    free_reg.push({"$s4", NULL});

    reg_info.insert({"$t0", ""});
    reg_info.insert({"$t1", ""});
    reg_info.insert({"$t2", ""});
    reg_info.insert({"$t3", ""});
    reg_info.insert({"$t4", ""});
    reg_info.insert({"$t5", ""});
    reg_info.insert({"$s0", ""});
    reg_info.insert({"$s1", ""});
    reg_info.insert({"$s2", ""});
    reg_info.insert({"$s3", ""});
    reg_info.insert({"$s4", ""});

    //float registers
    free_reg_float.push({"$f20", NULL});
    free_reg_float.push({"$f22", NULL});
    free_reg_float.push({"$f24", NULL});
    free_reg_float.push({"$f26", NULL});
    free_reg_float.push({"$f28", NULL});
    free_reg_float.push({"$f30", NULL});
    // free_reg_float.push({"$f6", NULL});
    // free_reg.push({"$f7", NULL});
    // free_reg.push({"$f8", NULL});
    // free_reg.push({"$s3", NULL});
    // free_reg.push({"$s4", NULL});

    reg_info_float.insert({"$f20", ""});
    reg_info_float.insert({"$f22", ""});
    reg_info_float.insert({"$f24", ""});
    reg_info_float.insert({"$f26", ""});
    reg_info_float.insert({"$f28", ""});
    reg_info_float.insert({"$f30", ""});
    // reg_info_float.insert({"$f6", ""});
    // reg_info.insert({"$s1", ""});
    // reg_info.insert({"$s2", ""});
    // reg_info.insert({"$s3", ""});
    // reg_info.insert({"$s4", ""});
}
