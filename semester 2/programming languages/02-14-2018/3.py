#!/usr/bin/python

import sys 
import os
import cv2 as cv
import numpy as np

def main():
    filters = ["copy", "edges", "blur", "psycho", "noise",
               "blue", "green", "red", "gray", "hsv"]

    if len(sys.argv) != 4\
        or sys.argv[2] not in filters:
        # Stop execution if arguments passed wrong
        print("\tArguments: <INPUT> <FILTER> <OUTPUT>\n"\
                + "\tAvailable filters: " + " ".join(filters))
        exit(1)

    in_file, filter_type, out_file = sys.argv[1], sys.argv[2], sys.argv[3]
    frame = cv.imread(in_file)

    # We just ignore copy filter because it should do nothing
    if filter_type == "edges":
        frame = cv.Canny(frame, 200, 300)
    elif filter_type == "blur":
        frame = cv.GaussianBlur(frame, (11, 11), 0)
    elif filter_type == "psycho":
        frame -= cv.GaussianBlur(frame, (11, 11), 0)
    elif filter_type == "noise":
        h, w, d = frame.shape
        frame += np.array(bytearray(os.urandom(h*w*d))).reshape(h, w, d)//2
    elif filter_type == "blue":
        frame[:, :, 0] = 0xFF
    elif filter_type == "green":
        frame[:, :, 1] = 0xFF
    elif filter_type == "red":
        frame[:, :, 2] = 0xFF
    elif filter_type == "gray":
        frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    elif filter_type == "hsv":
        frame = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    if cv.imwrite(out_file, frame):
        exit(0)
    else:
        exit(-1)


if __name__ == '__main__':
    main()

