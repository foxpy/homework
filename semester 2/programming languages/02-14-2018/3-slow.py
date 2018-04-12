# Code presented in 3.py is designed to be short, brief and as fast as
# possible. While being best for real usage, it does not suit hometask
# requirements. So I have written a slow, but verbose version.

from PIL import Image, ImageDraw
import numpy as np
import time



# Python is slow for raw calculations and we are going to prove that
start_time = time.time()


def get_cpu_freq():
    # Put your OS dependent code here. I use Linux, so
    return int(open('/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq',
        'r').read())*10**3


def log_time_elapsed(timestep, image_type, image_size):
    return "[{}]: {} image processed in {} seconds with {} CPU cycles per pixel".format(
            round(time.time() - start_time, 2),
            image_type,
            round(time.time() - timestep, 2),
            int(get_cpu_freq()*(time.time() - timestep)/image_size))



def main():
    image = Image.open("input.jpg")
    draw = ImageDraw.Draw(image)

    w, h = image.size
    print("Image size is {}x{}.".format(*image.size))
    if w*h > 1920*1080:
        print("Image too big. You can drink some coffee.")
    frame = image.load()

    delta_time = time.time()
    for x in range(w):
        for y in range(h):
            draw.point((x, y), ((sum(frame[x, y]) // 3,)*3))
    image.save("gray.jpg", "JPEG")
    print(log_time_elapsed(delta_time, "gray", w*h))


    image = Image.open("input.jpg")
    draw = ImageDraw.Draw(image)
    frame = image.load()

    delta_time = time.time()
    for x in range(w):
        for y in range(h):
            Y = int(0.299*frame[x, y][0] + 0.587*frame[x, y][1] + 0.114*frame[x, y][2])
            U = int(0.492*(frame[x, y][2] - Y))
            V = int(0.877*(frame[x, y][0] - Y))
            draw.point((x, y), (Y, U, V))
    image.save("yuv.jpg", "JPEG")
    print(log_time_elapsed(delta_time, "yuv", w*h))


    image = Image.open("input.jpg")
    draw = ImageDraw.Draw(image)
    frame = image.load()

    delta_time = time.time()
    for x in range(w):
        for y in range(h):
            R, G, B = frame[x, y]
            if (R == 0) and (G == 0) and (B == 0):
                draw.point((x, y), (0, 0, 0))
                continue
            C = 1 - R/255
            M = 1 - G/255
            Y = 1 - B/255

            min_CMY = min(C, M, Y)
            C = int((C - min_CMY) / (1 - min_CMY) * 255)
            M = int((M - min_CMY) / (1 - min_CMY) * 255)
            Y = int((Y - min_CMY) / (1 - min_CMY) * 255)
            draw.point((x, y), (C, M, Y))
    image.save("cmy.jpg", "JPEG")
    print(log_time_elapsed(delta_time, "cmy", w*h))



    kernel = [[0, 1, 0],
              [1, 2, 1],
              [0, 1, 0]]
    k_length = len(kernel)
    expansion = k_length // 2

    image = Image.open("input.jpg")
    expanded = Image.new("RGB", (w + expansion*2, h + expansion*2), (127,)*3)
    draw = ImageDraw.Draw(image)
    frame = expanded.load()
    expanded.paste(image, (expansion,)*2 + (w + expansion, h + expansion))

    delta_time = time.time()
    for x in range(w):
        for y in range(h):
            pixel = [0,]*3
            for color in range(3):
                for i in range(k_length):
                    for j in range(k_length):
                        pixel[color] += frame[x+i, y+j][color]*kernel[i][j]
            pixel[:] = [int(k*1/k_length**2) for k in pixel]
            draw.point((x, y), tuple(pixel))
    image.save("hpf.jpg", "JPEG")
    print(log_time_elapsed(delta_time, "hpf", w*h))



if __name__ == '__main__':
    main()
