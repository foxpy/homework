# Code presented in 3.py is designed to be short, brief and as fast as
# possible. While being best for real usage, it does not suit hometask
# requirements. So I have written a slow, but verbose version.

from PIL import Image, ImageDraw
import time


# Python is slow for raw calculations and we are going to prove that
print("Applying filters. Please wait...")
start_time = time.time()

image = Image.open("input.jpg")
draw = ImageDraw.Draw(image)

w, h = image.size
print("Image size is {}x{}.".format(*image.size))
if w*h > 640*480:
    print("Image too big. You can drink some coffee.")
frame = image.load()

delta_time = time.time()
for x in range(w):
    for y in range(h):
        draw.point((x, y), ((sum(frame[x, y]) // 3,)*3))
image.save("gray.jpg", "JPEG")
print("[{}]: Gray image processed in {} seconds with {} CPU cycles per pixel."
        .format(round(time.time() - start_time, 2),
            round(time.time() - delta_time, 2),
            int(int(open('/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq',
                'r').read())*10**3*(time.time() - delta_time)/(w*h))))

print("Execution took {} seconds.".format(round(time.time() - start_time, 2)))

