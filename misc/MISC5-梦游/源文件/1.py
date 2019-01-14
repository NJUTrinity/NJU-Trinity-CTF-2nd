import base64
a="flag{fuck_yeah_qrcode}"
cnt=0
while cnt<15:

    a=base64.b64encode(a)
#    print a
    cnt=cnt+1
print(a)
