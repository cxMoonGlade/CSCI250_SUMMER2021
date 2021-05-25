#### Moore's Law 

The number of transistors doubles every 18 months.





#### The evolution of  computer component

Electromechanical --> Relay --> Vacuum Tube --> Transistor --> Integrated Circuit

​						 机电 --> 中继器 --> 真空管 -----------> 三极管 -------> 集成电路



真空管依然被应用在军用等需要超强稳定性的地方



### Machine-Level Code

- Instruction set architecture (ISA) 指令集

  1. 指令集定义了机器级程序的格式和行为，包括处理器状态、指令的格式、以及每条指令对状态的影响。

  2. 处理器看似是按顺序执行每一条指令，但事实上处理器会并发地处理多条指令；同时保证指令顺序。

  指令集本质是一堆机器指令，其中分为两大类：

  1. 精细化指令，每个（套）指令做一件专门的任务，这样的指令效率高但会使得整个指令集包含的指令数量较多。 这种类型以英特尔的X86为代表。
  2. 笼统性指令，每个（套）指令可以完成一件小事情，多个指令自由结合可以完成一个任务，这样的指令集效率低但是整个指令集包含的指令较少。这种类型以AMD的ARM为代表。

  

- The Program Counter(%rip)指令计数器/程序计数器

  给出将要执行的下一条指令在内存中的地址。

  

- The Integer Register File整数寄存器文件

  包含了16个命名的位置，分别存储64位的值。这些寄存器可以存储地址（对应C语言中的Pointer）或者整数数据。 

  1. 用来记录某些重要的程序状态
  2. 保存临时数据，如：**过程的参数和局部变量**，以及**函数的返回值**。

  

- The Condition Code Registers 条件寄存器

  保存着最近执行的算数或逻辑指令的状态信息。

  他们用来实现控制或者数据流中的条件变换，如： if / else



PS： 

1. 在C语言中虽然我们可以通过指针等方式声明和分配各种数据类型的对象，但是机器代码只是简单地把内存视为一个很大的、按字节寻址的数组。所以汇编代码不区分有符号和无符号整数，也不区分指针类型，甚至不区分指针和整数。

2. 程序内存包括：程序的可执行**机器代码**、操作系统需要的一些信息、用来管理过程调用和返回的运行时栈、以及用户分配的内存块。 

   程序内存使用虚拟内存来寻址，而只有有限的一部分虚拟地址是合法的。以X86_64来说，地址的高16位必须设置为0，所以实际能制定的内存数量为2^48或256TB范围内的一个字节。

   操作系统负责管理虚拟地址空间，将虚拟地址范围成实际处理器内存中的物理地址。

3. 一条机器指令只执行一个非常基本的操作。例如，将存放在寄存器中的两个数字相加，在存储器（RAM）和寄存器（Register）之间传送数据，或是条件分支转移到新的指令地址。编译器必须产生这些指令的序列，从而实现（求值、循环、返回等）程序结构。



#### Flat Memory Model平坦内存模型

程序实际上在存储数据和指令的单个存储空间中，将32位的地址编码为逻辑上的参考虚拟位置。



#### Segmented Model分段模型

存储器被可视化为”**段**“的集合，每个“段”长64kb，以16的倍数为开始和增长。



#### General Register (Data Register)通用寄存器

可用于传送和暂存数据，也可参与算术逻辑运算，并保存运算结果。

此外他们还有一些特殊功能：

<i>注：除了位宽外，AH, AX, EAX, RAX 并无本质区别， BH, BX, EBX, RBX 也无本质区别，以此类推。</i>

64位的寄存器（通用寄存器）： RAX， RBX，RCX, RDX

32位的寄存器 （通用寄存器）：EAX,  EBX, ECX, EDX， 储存在32位中的高16位里，对低16位的数据做存取

16位的寄存器 ： AX, BX, CX, DX, 这四个16位的寄存器分为8个独立的8位寄存器：

​							（AX = AH - AL）\ (BX =  BH - BL) \ (CX = CH - CL) \ (DX = DH - DL)

8位的寄存器： AH - AL, BH - BL,  CH - CL, DH - DL.

AX里的AH - AL是累加寄存器 （Accumulator）； BX是基底寄存器Base Register，可以存储指针；

CX是计数寄存器Count Register，可以控制循环次数； DX是数据寄存器Data Register， 在进行乘除运算时，可以用于存放I/O的端口地址。



示例代码里的

```assembly
add eax, 158
// eax = eax + 158

sub ax, 10
// ax = ax - 10
mov ah, '*'
// ah = '*' 

// 这里的eax，ax，ah都是寄存器，可以把寄存器当作变量来使用，
```





#### EFLAGS

EFLAGS 寄存器主要用于提供程序的状态及进行相应的控制。

在64位模式下，EFLAGS寄存器被拓展为64位的RFLAGS寄存器，高32位被保留，而低32位则与EFLAGS寄存器相同。

1. ##### 状态标志 Status Flags， 指示算数指令（ADD， SUB，MUL，DIV）的结果

   1. CF（bit 0）Carry Flags， 如果算数操作产生的结果在最高有效位MSB发生进位或借位，则为1，否则为0，这标志无符号整数型运算的溢出状态；

   2. PF （bit 2）Parity Flags， 如果最低有效位（LSB）包含偶数个1位，则该位为1，否则为0；

   3. AF （bit 4） Adjust Flags，如果算数操作在结果的第三位发生进位或借位则为1，这个标志用于BCD运算；

   4. ZF （bit 6） Zero Flags， 如果结果是0，则为1；

   5. SF （bit 7）Sign Flags， 该标志被设置为有符号的整形的最高有效位，（0为正，1为负）

   6. OF （bit 11）Overflow Flags，如果整形结果是大于最大可表示的数字时，或小于最小可表示的数字时，且无法匹配目的操作数时，则为1，反之为0，表示带符号整型运算的溢出状态

      

2. ##### 方向标志 Direction Flags， （bit 10）控制串指令（MOVS，CMPS，SCAS，LODS，STOS）。

   设置DF标志使得串指令自动递减（从高地址向低地址方向处理字符串），清楚该表示则自动递增。 

   STD和CLD指令分别用于设置和清除DF标志。

   

3. ##### 系统标志以及IOPL域 System Flags and IOPL Field （暂时不管）

   1. TF （bit 9）Trap Flag， 
   2. IF (bit 9) Interrupt Enable Flag
   3. IOPL(bits 12 and 13) [I/O privilege level field] 
   4. NT(bit 14) [Nested task flag]
   5. RF(bit 16) [Resume flag]
   6. VM(bit 17) [Virtual-8086 mode flag] 
   7. AC(bit 18) [Alignment check flag]
   8. VIF(bit 19) [Virtual interrupt flag]
   9. VIP(bit 20) [Virtual interrupt pending flag]
   10. ID(bit 21) [Identification flag]





#### Modes of Memory Addressing on x86

| 0000H                           | program Sement Prefix (PSP) | CS, DS, SS, ES | 有操作系统设定的段寄存器                                     |
| ------------------------------- | --------------------------- | -------------- | ------------------------------------------------------------ |
| 0100H                           | Your Program Code           | IP             | IP 指向cpu即将执行的下一个机器指令的地址                     |
|                                 | Your Program Data           | BX             | 像BX这样的GP寄存器指向存储数据的地址                         |
|                                 | Unused Memory Space         |                |                                                              |
| 0FFFFH(16 bit Offset Addresses) | The Stack                   | SP             | Stack Pointer指向下一个push动作发生的地方。Stack，栈，是一个先入后出的buffer缓冲器。 |



#### Basic Assembly Language

```assembly
.586	
// this means these instructions can only use on 80586 micro processor

.Model Flat 
// this means the memory model. Read more in 
// http://c.biancheng.net/view/3864.html

.STACK 4096 
// reserve 4096 bytes stack, like make 10101010 to be 01010101, but there is only 1 byte

.DATA 
// 简化段定义，用于定义数据, 

number DWORD -105
// 不知道这个number 什么意思
// DWORD指令的意思是'size' of the memory location used for move operation

sum DWORD ?
// 不知道什么意思……求好心人修改一下

.CODE

main PROC
			mov eax, number;
			// EAX = first_number
			add eax, 158;
			// eax = eax + 158
			// eax 是一个32位长的通用寄存器，且如上述提到，是一个累加器
			// 158会被转换为一个双字长度的补码
			// 同时也会 update sum的值？
			// Carry flag = 1； Overflow flag = 0； Sign flag = 0； Zero flag = 0 (sum not equal zero). 不清楚这里为什么Carry Flag = 1， 最高位是怎么溢出的呢？
			mov sum, eax
			// sum = eax
			mov eax, 0
			// eax = 0
			ret
			// exit
Main ENDP
// method ends here
END
// program ends here
```



#### Recall this Overall Flowchart



【c语言文本】hello.c --> [Preprocessor预处理器[cpp]] --> 【修改过的文本】hello.i --> [Compiler编译器[cci]] --> 【汇编文本】hello.s --> [Assembler汇编器[as]] --> 【二进制可重定向的程序】hello.o（printf.o[]） --> [Linker链接器[ld]] --> 【二进制可执行对象程序】hello



1. preprocessor: according to the the instructions which starts as # like #include <stdio.o> inside the .c file

   to read the .h files and insert them into the program, then we can get another C program, usually ends as .i

   

2. compiler: converts the .i file to be text file .s in assembly language.

   Assemply language offers an universal output language for different HLLs.

   

3. Assembler: converts the .s file to be machine instructions (binary file .o), and packages them to be a special format named relocatable object program. This binary file only include things has been described in the .c file, not including the static methods or variables.

   

4. Linker: Linker used to link the things used in the program but described by the standard C library.

   Then, we have the last file which can be loaded into memory and excuted by the system. [Executable object program (binary)]





#### linux instructions:

1. linux> gcc -Og -S fileName.c

   This cause GCC to run the compiler and generating an assembly file fileName.s, but go no further.

   

2. linux> gcc -Og -c fileName.c

   This generate an object-code file fileName.o.





#### Push and Pop Stack Data 压栈， 出栈

Stack is a first in, last out data structure.

Add data via push, 

Remove data via pop



# 剩下的就是去背这些汇编指令，加油干吧兄弟们！







PS: 汇编指令大全

https://wenku.baidu.com/view/314aa7cf58fb770bf78a55ea.html

