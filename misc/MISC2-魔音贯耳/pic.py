import os 
import StringIO 
import PIL.Image as Image, PIL.ImageFont as ImageFont, PIL.ImageDraw as ImageDraw
import pygame
pygame.init()
text = u"TrinityCTF{0h!FLAG_1N_4UD10!}"
im = Image.new("RGB", (1800, 200), (255, 255, 255))
dr = ImageDraw.Draw(im) 
font = ImageFont.truetype(os.path.join("/usr/share/fonts/truetype/dejavu/", "DejaVuSerif-Bold.ttf"), 88) 
font = pygame.font.Font(os.path.join("/usr/share/fonts/truetype/dejavu/", "DejaVuSerif-Bold.ttf"), 88)
#dr.text((10, 5), text, font=font, fill="#000000") 
rtext = font.render(text, True, (0, 0, 0), (255, 255, 255))
pygame.image.save(rtext, "t.gif") 
sio = StringIO.StringIO() 
pygame.image.save(rtext, sio) 
sio.seek(0)
line = Image.open(sio) 
im.paste(line, (10, 5))
im.show() 
im.save("t.png") 
