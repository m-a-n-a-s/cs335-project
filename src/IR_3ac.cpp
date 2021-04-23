#include <fstream>
#include "IR_3ac.h"
#include "semanticCheck.h"
using namespace std;
using std::setw;

map<int , string> Labels;
ofstream IRcodeFile;
long long Index = -1;
map<string, int> gotoIndex;
unordered_map<string, list<int>> gotoIndexPatchList;

vector <quad> emittedCode;

//get temporary variable
string getTmpVar(){
  static long temp_var_num = 0;
  temp_var_num++;
  return (string("temp_") + to_string(temp_var_num));
}

//get temporary symbol
pair<string, Entry*> getTmpSym(string type){
    string temp = getTmpVar();
//  char *cstr = new char[type.length() + 1];
//  strcpy(cstr, type.c_str());
//  char* test = &type[0];
    insert_symbol(*curr, temp, type, get_size(&type[0]),0, 1);
    return pair <string, Entry* >(temp, lookup(temp));
}

//emit
int emit (qid op, qid id1, qid id2, qid  res, int stmtNum){
  quad t;
  t.id1 = id1;
  t.id2 = id2;
  t.res = res;
  t.op = op;
  t.stmtNum = stmtNum;
  emittedCode.push_back(t);
  Index++;
  return emittedCode.size()-1;
}

//nextinstr
int getNextIndex(){
  return emittedCode.size();
}

//backpatch
void backPatch(list<int> li, int p){
    std::list<int>::iterator it = li.begin();
    for(int i=0; i<li.size(); ++i){
    // unsigned N = i;
    // if (li.size() > N)
    // {
    //   std::list<int>::iterator it = li.begin();
    //   std::advance(it, N);
    //   emittedCode[*it].stmtNum = p;
    // }
        emittedCode[*it].stmtNum = p;
        advance(it, 1);
    }
return;
}

//goto symbol
void setResult(int a, qid p){
  emittedCode[a].res = p;
  return;
}

//goto
void setId1(int a, qid p){
	emittedCode[a].id1 = p;
	return;
}

//goto for whole list
void setListId1(list<int> li, qid p){
    std::list<int>::iterator it = li.begin();
    for(int i=0; i<li.size(); ++i){
//     unsigned N = i;
//     if (li.size() > N)
//     {
//       std::list<int>::iterator it = li.begin();
//       std::advance(it, N);
//       setId1(*it, p);
//   }
        setId1(*it, p);
        advance(it, 1);
    }
	return;
}


int assignmentExpression(char *o, string type, string type1, string type3, qid place1, qid place3){
	qid t = place3;
    qid t2;
    string o_new(o);
	string op;
	string op1;
    int a=0;
    int b=0;
    if(o_new == "=") a=1;
	else if(o_new == "*="){
		op = "*";
        op1 = "*";
		t = getTmpSym(type);
	}else if(o_new == "/="){
		op = "/";
        op1 = "/";
		t = getTmpSym(type);
	}else if(o_new == "+="){
		op = "+";
        op1 = "+";
		t = getTmpSym(type);
	}else if(o_new == "-="){
		op = "-";
        op1 = "-";
		t = getTmpSym(type);
	}
    int k;
	// if(is_Intgr(type1) && is_Intgr(type3)){
	// 	op += "int";
	//     if(o_new != "=") k= emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
	// }else if(is_float(type1) && is_Intgr(type3)){
	// 	t2 = getTmpSym(type);
	// 	k = emit(pair<string, Entry*>("inttoreal",NULL), place3,pair<string, Entry*>("",NULL),t2,-1);
	// 	op += "real";
	// 	if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
    //     b=1;
	// }else if(is_float(type3) && is_Intgr(type1)){
	// 	t2 = getTmpSym(type);
	// 	k = emit(pair<string, Entry*>("realtoint",NULL),place3,pair<string, Entry*>("",NULL),t2,-1);
	// 	op += "int";
	// 	if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
    //     b=1;
	// }else if(is_float(type3) && is_float(type1)){
	// 	op += "real";
	// 	if(o_new != "=") k=emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
	// }

    if(is_Intgr(type1)){
        if(is_Intgr(type3)){
            op += "int";
	        if(o_new != "=") k= emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
        }else if(is_float(type3)){
            t2 = getTmpSym(type);
		    k = emit(pair<string, Entry*>("realtoint",NULL),place3,pair<string, Entry*>("",NULL),t2,-1);
		    op += "int";
		    if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
            b=1;
        }
    }else if(is_float(type1)){
        if(is_Intgr(type3)){
            t2 = getTmpSym(type);
            k = emit(pair<string, Entry*>("realtoint",NULL),place3,pair<string, Entry*>("",NULL),t2,-1);
            op += "int";
            if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
            b=1;
        }else if(is_float(type3)){
            op += "real";
		    if(o_new != "=") k=emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
        }
    }

    if(!(a &&b )) k= emit(pair<string, Entry*>("=", lookup("=")),  t, pair<string, Entry*>("", NULL), place1, -1);
	else emit(pair<string, Entry*>("=", lookup("=")),  t2, pair<string, Entry*>("", NULL), place1, -1);

    return k;

}
void assignment2(char *o, string type, string type1, string type3, qid place1, qid place3){
	qid t = getTmpSym(type);
    string o_new(o);
	string op;
	string op1;
    if(o_new == "%=") op = "%";
    else if(o_new == "^=") op = "^";
    else if(o_new == "|=") op = "|";
    else if(o_new == "&=") op = "&";
    op1 = op;
    if(o_new == "<<="){ op="LEFT_OP"; op1="<<"; }
    if(o_new == ">>="){ op="RIGHT_OP"; op1=">>"; }
    emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
    emit(pair<string, Entry*>("=", lookup("=")),  t, pair<string, Entry*>("", NULL), place1, -1);
}

// List of goto___'s
//if(!gotoIndexStorage($1, $3)){yyerror("ERROR:\'%s\' is already defined", $1);}
bool gotoIndexStorage (string id, int loc){
  if(gotoIndex.find(id) == gotoIndex.end()){
    //not found
    gotoIndex.insert(pair<string, int>(id, loc));
    return true;
  }
  return false;
}

//List of backpatch to resolve goto___'s
void gotoIndexPatchListStorage (string id, int loc){
    gotoIndexPatchList[id].push_back(loc);
}

//finding corresponding goto for backpatches
char* backPatchGoto(){
  for (auto it =gotoIndexPatchList.begin(); it!=gotoIndexPatchList.end(); ++it){
    if(gotoIndex.find(it->first)==gotoIndex.end()){
        char *a;
        strcpy(a, it->first.c_str());
        return a;
    }
    else {
        backPatch(gotoIndexPatchList[it->first] , gotoIndex[it->first]);
    }
 }
    return NULL;
}


void display(quad q, int i){
    
    int k = q.stmtNum;
	// if(q.stmtNum==-1 || q.stmtNum == -4){
	// 	IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << q.op.first << " " <<
	// 		setw(15) << q.id1.first << " " <<
	// 		setw(15) << q.id2.first << " " <<
	// 		setw(15) << q.res.first << '\n';
	// }else if(q.stmtNum==-2 || q.stmtNum == -3){
	// 	IRcodeFile  << endl << "[" << i << "]" << ": "<<
	// 	 q.op.first << endl << endl;
	// }else{
    //     k = q.stmtNum;
    //     while(emittedCode[k].op.first == "GOTO" && emittedCode[k].id1.first == ""){
    //         k = emittedCode[k].stmtNum;
    //     }
    //     if(Labels.find(k)== Labels.end()) Labels.insert(pair<int, string>(k, "Label"+to_string(k)));
	// 	IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << q.op.first << " " <<
	// 		setw(15) << q.id1.first << " " <<
	// 		setw(15) << q.id2.first << " " <<
	// 		setw(15) << k << "---" << '\n';
    //     emittedCode[i].stmtNum = k;
	// }
    switch (-k){
       case 1: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << q.op.first << " " <<
	 		    setw(15) << q.id1.first << " " <<
			    setw(15) << q.id2.first << " " <<
			    setw(15) << q.res.first << '\n';}
               break;
       case 2: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
	 	        q.op.first << endl << endl;}
                break;
       case 3: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
	 	        q.op.first << endl << endl;}
               break;
       case 4: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << q.op.first << " " <<
                setw(15) << q.id1.first << " " <<
                setw(15) << q.id2.first << " " <<
                setw(15) << q.res.first << '\n';}
       default: {while(emittedCode[k].op.first == "GOTO" && emittedCode[k].id1.first == ""){
                    k = emittedCode[k].stmtNum;
                }
                if(Labels.find(k)== Labels.end()) Labels.insert(pair<int, string>(k, "Label"+to_string(k)));
                IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << q.op.first << " " <<
                    setw(15) << q.id1.first << " " <<
                    setw(15) << q.id2.first << " " <<
                    setw(15) << k << "---" << '\n';
                emittedCode[i].stmtNum = k;}
                break; 
   }
}

void display3ac(){
  IRcodeFile.open("IRcode.txt");
	for(int i = 0; i < emittedCode.size(); ++i)  {
		display(emittedCode[i], i);
	}
	return;
  IRcodeFile.close();
}