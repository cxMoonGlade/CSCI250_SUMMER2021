//
//  main.c
//  May12
//
//  Created by Pengyuan Xu on 2021-05-12.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
  // insert code here...
  char string[] = "hello world";
  for(int i =0; i<sizeof(string); i++){
    printf("%c", string[i]);
  }
  char a = 'A';
  char b = 'a';
  printf("\n");
  printf("var a (A) after adds a space = %c\n", a | ' ');
  printf("var b =%c\n", b);
  int c = 5&2;
  int d = 5|2;
  printf("5 | 2 = %d\n", d);
  printf("5 & 2 = %d\n", c);
  
  return 0;
}
