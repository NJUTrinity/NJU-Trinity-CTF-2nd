## Writeup For Trinity CTF 2nd

### Web

### Pwn

#### Babypwn
通过`ida`分析可以发现程序存在栈溢出和格式化字符串漏洞，最简单的方法是直接用格式化字符串`leak`出`secret`然后就`get shell`.又或者用格式化字符串把`canary`和程序的基地址`leak`出来后做`ROP`

### Misc

#### Babymisc
这属于这场比赛的签到题，根据提示我们知道这个是用`Asciidots`写的脚本，我们去找到这个语言，看看语法，就可以发现其实脚本里面的每一个字母的作用都是打印出一个字符的`ascii`值，连起来就是`flag`.直接运行的话打出来的字符是乱序的，这个和解释器解析脚本的方法有关。

### Reverse

#### Babyre
给了一个文本文件，里面是汇编代码，直接编译成二进制文件然后用`ida`分析即可

#### Babyre2
和作业题是一样的思路。`main`函数被简单的加密了。详情看题目的源代码即可。

### Crypto