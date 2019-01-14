from scipy.misc import imsave
import cv2 as cv
import numpy as np
sent="flag{b1n4ry_1n_g1f_15_fun}"
#f=open("1.png",'w')
#img = np.zeros([400, 400, 3], np.uint8)
#imsave(f,img)
bin=""
for c in sent:
	bin=bin+'{:08b}'.format(ord(c))
print(bin)
cnt=0
for b in bin:
	c=int(b)
	f=open("gif/"+str(cnt)+".png",'w')
	img=(np.zeros([400,300,3],np.uint8)+255 if c==1 else np.zeros([400,300,3],np.uint8))
	imsave(f,img)
	cnt=cnt+1
	print(cnt)


