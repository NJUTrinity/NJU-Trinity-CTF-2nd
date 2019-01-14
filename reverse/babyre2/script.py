#!/usr/bin/env python
# coding=utf-8
from pwn import *
f=open("./babyre",'r')
of=open("./babyre",'w')

content=f.read()
outb=content[0:0x75a]
for i in content[0x75a:0x801]:
    outb+=p8(u8(i)^0x33)

outb+=content[0x801:]
of.write(outb)
of.close()
