import qrcode
f=open('1.txt','r')
s=f.read()
img = qrcode.make(s)
img.save('flag.png')
f=open('2.txt','r')
s=f.read()
img=qrcode.make(s)
img.save('initial.png')
