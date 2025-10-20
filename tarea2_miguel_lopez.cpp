#include <iostream>
#include <regex>
#include <string>

int wich_case(char c);
int is_correct(char *str);
void is_correct_regex(std::string str);
int int_len(char *str);
int mantisa_len(char *str);
int char_index(char c, char *str);
void get_pow(char *str, char *pow_arr);
int char_to_int(char *pow_arr, int arr_len);
int n_digits(int num);
void int_to_char(int num, char *pow_arr, int arr_len);
void corr_pow(char *str, int n_spaces, char *pow_arr, int arr_len);
void correct_expr(char *str, char *expr);
void to_no_mantisa_case(char *str, char *expr);
int error_case(char *str);


int main(int argc, char *argv[])
{
  int correct, error;
  char expr[100], exprf[100];
  //expr[99] = '\0';
  //exprf[99] = '\0';

  error = error_case(argv[1]);
 
  
  if (error == 0) {
    correct = is_correct(argv[1]);
    if (!correct) {
      correct_expr(argv[1], expr);
    }
  }else if (error == 1) {
    to_no_mantisa_case(argv[1], expr);
    correct_expr(expr, exprf);
  }else if (error == 2) {
    std::cout << "Expresión inválida" << '\n';
    return -1;
  }
  

  //is_correct_regex(argv[1]);

  return 0;
}

int int_len(char *str){
  int len,first_ceros,i;

  len = 0;
  i = 0;
  first_ceros = 1;
  while (str[i] != '.') {
    if (str[i] == '0' && first_ceros) {
      i++;
      continue;
    }
    first_ceros = 0;
    len++;
    i++;
  }

  if(wich_case(str[0]) == 4){
    len--;
  }

  return len;
}

int mantisa_len(char *str){
  int len,i;

  len = 0;
  i = 0;
  while (str[i] != '.') i++;
  
  while (str[i] != '\0') {
    if (str[i] == 69 || str[i] == 101) break;
    len++;
    i++;
  }

  return len-1;
}

void get_pow(char *str, char *pow_arr){
  int i,j;

  i = 0;
  while (str[i] != '\0') {
    if (str[i] == 'e' || str[i] == 'E') {
      i++;
      break;
    }
    i++;
  }
  
  j = 0;
  while (str[i] != '\0') {
    pow_arr[j++] = str[i++];
  }

  pow_arr[j] = '\0';
}

int char_to_int(char *pow_arr, int arr_len){
  int num,base,temp_num,i;

  base = 1;
  num = 0;
  for (i = arr_len-1; i >= 0; i--) {
    if (wich_case(pow_arr[i]) == 1) {
      temp_num = pow_arr[i] - 48;
      num += (base * temp_num);
      base *= 10;
    }
  }

  if (pow_arr[0] == '-'){
    num *= -1;
  }

  return num;
}

int n_digits(int num){
  int n_digits, i;

  if (num < 0) {
    num *= -1;
  }

  if (num == 0) {
    return 1;
  }

  n_digits = 0;
  while (num > 0) {
    for (i = 0; i < 10; ++i) {
      if ((num-i)%10==0) {
        num -= i;
        num /= 10;
        break;
      }
    }
    n_digits++;
  }

  return n_digits;
}

void int_to_char(int num, char *pow_arr, int arr_len){
  int n_digs, start, i, j;
  
  n_digs = n_digits(num);

  if (num < 0){
    num *= -1;
    pow_arr[0] = '-';
  }else {
    pow_arr[0] = '0';
  }
  
  j = 0;
  do{
    for (i = 0; i < 10; ++i) {
      if ((num-i)%10 == 0) {
        pow_arr[n_digs-j] = i+48;
        num -= i;
        num /= 10;
        j++;
        break;
      }
    }
  }while (num != 0);

  if (n_digs + 1 < arr_len) {
    pow_arr[n_digs+1] = '\0';
  }else {
    printf("Espacio insuficiente\n");
  }
}

void corr_pow(char *str, int n_spaces, char *pow_arr, int arr_len){
  int pot, e_ind, i, j;

  pot = char_to_int(pow_arr, arr_len);
  pot += n_spaces;
  
  int_to_char(pot, pow_arr, arr_len);

  e_ind = char_index('e', str);
  if (!e_ind){
    e_ind = char_index('E', str);
  }
  e_ind++;

  j = 0;
  for (i = 0; i < arr_len; ++i) {
    if (pow_arr[i] == '0' && i == 0){
      continue;
    }
    str[j+e_ind] = pow_arr[i];
    j++;
  }
}

int char_index(char c, char *str){
  int i;

  i = 0;
  while (str[i] != '\0'){
    if (str[i] == c){
      return i;
    }
    i++;
  }
 
  return 0;
}

void correct_expr(char *str, char *expr){
  int  e_ind, dot_ind, intg, mant, pow_len = 6, i, j, k;
  char digs[4];
  char pow_arr[pow_len];

  intg = int_len(str);
  mant = mantisa_len(str);
  i = 0;
  j = 0;
  k = 4;

  if (wich_case(str[i]) != 4) {
    digs[i++] = '0';
    k = 3;
  }

  for (j = 0; j < k; ++j) {
    if (wich_case(str[j]) == 2){
      k++;
      continue;
    }
    digs[i++] = str[j];
  }

  if (digs[0] != '0'){
    expr[0] = digs[0];
    expr[1] = digs[1];
    expr[2] = '.';
    expr[3] = digs[2];
    expr[4] = digs[3];
    j = 5;
  }else {
    expr[0] = digs[1];
    expr[1] = '.';
    expr[2] = digs[2];
    expr[3] = digs[3];
    j = 4;
  }

  e_ind = char_index('e', str);
  if (!e_ind){
    e_ind = char_index('E', str);
  }

  i = e_ind;
  while (str[i] != '\0') {
    expr[j++] = str[i++];
  }

  expr[j] = '\0';
  get_pow(str, pow_arr);
  corr_pow(expr, intg-1, pow_arr, pow_len); 

  std::cout << "Corrección: "<< expr << '\n';
}

void to_no_mantisa_case(char *str, char *expr){
  int dot_ind, e_ind, intg, mantisa, pow_len = 6, i, j, k;
  char pow_arr[pow_len];

  dot_ind = char_index('.', str);
  e_ind = char_index('e', str);
  if (!e_ind) {
    e_ind = char_index('E', str);
  }

  intg = int_len(str);
  mantisa = mantisa_len(str);

  i = 0;
  
  while (str[i] == '0' || str[i] == '.' || (str[i] == '-' && str[i+1] == '0') || (str[i] == '-' && str[i+1] == '.')) {
    i++;
  }

  if (wich_case(str[i]) == 3) {
    expr[0] = '0';
    expr[1] = '.';
    expr[2] = '0';
    expr[3] = 'E';
    expr[4] = '1';
    expr[5] = '\0';
    return;
  }

  j = 0;
  k = 0;

  if (str[0] == '-' && str[1] == '0'){
    expr[j] = '-';
    k = 1;
  }
  
  while (wich_case(str[j+i]) != 3){
    if (str[j+i] == '.') {
      i++;
      continue;
    }
    expr[j+k] = str[j+i];
    j++;
  }

  expr[j+k] = '.';

  while (str[j+i] != '\0') {
    expr[j+k+1] = str[j+i];
    j++;
  }

  expr[j+k+1] = '\0';
  
  get_pow(expr, pow_arr);
  corr_pow(expr, -e_ind+dot_ind+1, pow_arr, pow_len); 
}

int is_correct(char *str){
  int s,c,mantisa,i;

  s = 0;
  i = 0;
  mantisa = 0;

  while (str[i] != '\0') {    
    c = wich_case(str[i]);
    switch (s) {
      case 0:
        if (c == 1){
          s = 2;
        }else if (c == 4) {
          s = 1;
        }
        else {
          s = -1;
        }
        break;
      case 1:
        if (c == 1) {
          s = 2;
        }else {
          s = -1;
        }
        break;
      case 2:
        if (c == 2) {
          s = 3;
        }else{
          s = -1;
        }     
        break;
      case 3:
        if (c == 1) {
          s = 4;
          mantisa++;
        }else {
          s = -1;
        }
        break;
      case 4:
        if (c == 1 && mantisa < 2) {
          s = 4;
          mantisa++;
        }
        else if (c == 3) {
          s = 5;
        }else {
          s = -1;
        }
        break;
      case 5:
        if (c == 1) {
          s = 7;
        }else if (c == 4) {
          s = 6;
        }else {
          s = -1;
        }
        break;
      case 6:
        if (c == 1) {
          s = 7;
        }else {
          s = -1;
        }
        break;
      case 7:
        if (c == 1) {
          s = 7;
        }else {
          s = -1;
        }
        break;
      default:
        break;
    }
    i++;
  }

  if (s == 7){
    std::cout << "Es notación científica" << '\n';
    return 1;
  } 

  std::cout << "No válido" << '\n';
  return 0;
}

int wich_case(char c){

  if (c >= 48 && c <= 57) {
    return 1;
  }else if(c == 46){
    return 2;
  }else if (c == 69 || c == 101){
    return 3;
  }else if (c == 43 || c == 45){
    return 4;
  }

  return 0;  
}

int error_case(char *str){

  int caso, mant, dot, e, exp, i;

  caso = 0;
  mant = 1;
  exp = 1;
  e = 0;
  dot = 0;
  i = 0;
  

  if (str[0] == '0' || (wich_case(str[0]) == 4 && str[1] == '0')){
    caso = 1;
  }

  while (str[i]){  
   
    if (str[i] == '.') {
      dot = 1;
    }
   
    if (str[i] == 'e' || str[i] == 'E'){
      e = 1;
      if (str[i-1] == '.') {
        mant = 0;
      }
      if (str[i+1] == '\0') {
        exp = 0;
      }
    } 
   
    i++;
  }

  if(!dot || !e || !mant || !exp){
    caso = 2;
  }

  return caso;
}

void is_correct_regex(std::string str){
  std::regex r("^[-+]?\\d(\\.\\d{1,2})?[eE][-+]?\\d+$");
  
  if(std::regex_match(str, r)) {
    std::cout << "Notación científica" << '\n';
  }else {
    std::cout << "Notación no válida" << '\n';
  }
}
