# Code presented in 3.py is designed to be short, brief and as fast as
# possible. While being best for real usage, it does not suit hometask
# requirements. So I have written a slow, but verbose version.

from PIL import Image, ImageDraw


image = Image.open("input.jpg")
draw = ImageDraw.Draw(image)

w, h = image.size
frame = image.load()

for x in range(w):
    for y in range(h):
        draw.point((x, y), ((sum(frame[x, y]) // 3,)*3))

image.save("gray.jpg", "JPEG")

