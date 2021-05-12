int main() {
  int true_var = 1;
  int false_var = 0;
  int test_var = 3;
  if (true_var || (test_var=4)) {
    if(test_var == 3)
	print_string("OR short circuit working!!\n");
    else	
	print_string("OR short circuit not working!!\n");
  }
  if (false_var && (test_var=4)) {
	print_string("AND short_circuit not working");
 }
  else {
    if(test_var == 3)
	print_string("AND short circuit working!!\n");
    else	
	print_string("AND short circuit not working!!\n");
  }

  if (false_var || (test_var=4)) {
    if(test_var == 4)
	print_string("OR without short circuit working!!\n");
    else	
	print_string("OR without short circuit not working!!\n");
  }

else{
	print_string("OR without short circuit not working!!\n");
}

   if (true_var && (test_var=4)) {
	if(test_var == 4)
	print_string("AND without short circuit working!!\n");
    else	
	print_string("AND without short circuit not working!!\n");
 }
	

  return 0;
}
