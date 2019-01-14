#-*- coding: UTF-8 -*-  
 
import imageio
import sys
def create_gif(image_list, gif_name):
 
    frames = []
    for image_name in image_list:
        frames.append(imageio.imread(image_name))
    # Save them as frames into a gif 
    imageio.mimsave(gif_name, frames, 'GIF', duration = 0.1)
 
    return
 
def main():
    cnt=0
    image_list=[]
    while cnt<208:
        image_list.append(str(cnt)+".png")
        cnt=cnt+1
    gif_name = 'created_gif.gif'
    create_gif(image_list, gif_name)
 
if __name__ == "__main__":
    reload(sys)
    sys.setdefaultencoding("utf-8")
    main()

