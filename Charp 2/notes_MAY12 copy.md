[toc]

#### String, char array

in C, we use char[] for String, and we can use char[] just like string in other HHL

```c
#include <stdio.h>

int main(int argc, const char * argv[]) {
  // insert code here...
  char string[] = "hello world";
  for(int i =0; i<sizeof(string); i++){
    printf("%c", string[i]);
  }
  return 0;
}

//output:
//hello world
```



#### | and &

in C, and other HHL, I and & is operating bnary numbers. like:

```c
int a = 5;
int b = 2;
printf("%d\n", a | b);
// output is 7, a -> 0101, b -> 0010, a | b -> 0111 -> 7
printf("%d\n", a & b);
// output is 0, a -> 0101, b -> 0010, a & b -> 0000 -> 0
```



#### Not only the numbers, but also char,

```c
char x = 'A'; // 1000001
printf("%c", x | ' ');//& with a space 0100000
// output is a, 1100001
```



#### left shift 

```c
x << N;
// x is the variable, N is the number of shift
// this changes x to be x * (2^N)
// set N = 1
// before, x = 0110;
// after, x = 1100;
```



#### right shift

```c
x >> N;
// x is the variable, N is the number of shift
// this changes x to be x / (2^N)
// set N = 1;
// before, x = 0110 / 1110;
// after, 
// positive number add zero in front, like x = 0011;
// negative numver add one in front, like x = 1111;
// skip the MSB if number is signed.
```



 We can use >>> to force the number right shift fot 3 zeros.

```c
-5 >>> 3;
-5: 1111 1111 1111 1111 1111 1111 1111 1011
res	0001 1111 1111 1111 1111 1111 1111 1111
res = 536870911
```



#### movie suggestion:

1. Final Destination 
2. Matrix



#### some math operations

##### Add, minors, 1's comp, 2's comp

​	

#### signed number trans to unsigned number

For positive number: they equal

For negative number: unsigned number equals the 2's complement of signed number

e.g.

```c
short s = -12345;
unsigned short us = (unsigned short) s;
printf("s = %d, us = %u", s, us);

// the output will be :
// v = -12345, us = 53191
```



但是如果转换出的补码数字太大，那么就会的到TMax，既该数据类型下的最大值。



##### Multiplication

for 15 (X) * 13 (y) -> 1111 * 1101

<1>  y's LSB = 1 (2^0), x left shift 0 bit -> 1111

<2> y's second LSB = 0, x do no shift -> treat as 0

<3> y's third LSB = 1 (2^2), x left shift 2 bits -> 111100

<4> y's forth LSB = 1 (2^3), x left shift 3 bits -> 1111000

<5> add them all: 1111 + 0 + 111100 + 1111000 -> 11000011 (195)



##### division 

for 13 / 3

1 - 3 -> -2, not working, there is a number (3) behind, add together;

13 - 3 -> 10 , count 1

10 - 3 -> 7, count 1

7 - 3 -> 4, count 1

4 - 3 -> 1, count 1

1 - 3 -> -2, not working, no number behind, save 1 as remainder

count 4 times, so the quotient (Q) is 4, remainder (R) is 1;



for 51 / 3 -> 110011 / 11

<1> from MSB = 1, less than 11, Q1 = 0, R1 = 1;

<2> from second MSB = 1, R1*2 + 1 = 11, Q2 = 1, R2 = 0;

<3> from third MSB = 0, R2 *2 + 0 = 0, Q3 = 0, R3 = 0;

<4> from forth MSB = 0, R3 *2 + 0 = 0, Q4 = 0, R4 = 0;

<5> from fifth MSB = 1, R4 *2 + 1 = 1, Q5 = 0, R5 = 1;

<6> from sixth (last) MSB = 1, R5 *2 + 1 = 11, Q6 = 1, R5 = 0;

from Q1 to Q6, the quotient is 010001 (17), the remainder is R5 = 0;



for 11/ 2 -> 1011 / 10

<1> from MSB = 1, less than 10, Q1 = 0, R1 = 1;

<2> from second MSB = 0, R1 *2 + 0 = 10, Q2 = 1, R2 = 0;

<3> from third MSB = 1, R2 *2 + 1 = 1, Q3 = 0, R3 = 1;

<4> from forth MSB = 1, R3 *2 + 1 = 11, Q4 = 1, R4 = 1;

from Q1 to Q4, the quotiend is 0101 (5), the remainder is R4 = 1;

