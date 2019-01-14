f=open("origin","r")
s=f.read()
a="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}"
b="ghfjdkslapqowieurytmznxbcvGHFJDKSLAPQOWIEURYTMZNXBCV$%"
#print(s)
c=""
for i in range(0,len(s)):
#	print(s[i])
	try:
		pos=a.index(s[i])
#		print(pos)
		c=c+b[pos]
	except Exception:
#		print("not found")
		c=c+s[i]
print()
print(c)
