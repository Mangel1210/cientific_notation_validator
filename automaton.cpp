#include <iostream>

int wich_case(char c){

  if (c >= 48 && c <= 57) {
    //std::cout << c << ": Es numero" << '\n';
    return 1;
  }else if(c == 46){
    //std::cout << c << ": Es punto" << '\n';
    return 2;
  }else if (c == 69 || c == 101){
    //std::cout << c << ": Es una E o e" << '\n';
    return 3;
  }else if (c == 43 || c == 45){
    //std::cout << c << ": Es un signo" << '\n';
    return 4;
  }

  return 0;  
}

int main(int argc, char *argv[]){
  int s,c,mantisa,i;
  char *str;

  str = argv[1];

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
        }else if (c == 3) {
          s = 5;
        }else 
        {
          s = -1;
        }     
        break;
      case 3:
        if (c == 1) {
          s = 4;
        }else {
          s = -1;
        }
      case 4:
        if (c == 1 &&  mantisa < 2) {
          s = 4;
          mantisa++;
        }else if (c == 3) {
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

  if (s == 2){
    printf("Es entero\n"); 
  }else if (s == 4){
    printf("Es un flotante\n");
  }else if (s == 7){
    printf("Es una notación científica\n");
  }else {
    printf("No válido\n");
  }

  return 0;
}
