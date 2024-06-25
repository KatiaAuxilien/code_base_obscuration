import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle
sys.path.append('../')

from lib.metriques import *

def main() :
    if len(sys.argv) < 2:
        print("Usage: python "+sys.argv[0]+" <image_file>")
        sys.exit(1)

    image_file = sys.argv[1]
    if not os.path.isfile(image_file):
        print(f"Error: File '{image_file}' not found.")
        sys.exit(1)

    cv_img = cv2.imread(image_file, cv2.IMREAD_GRAYSCALE)
    if cv_img is None:
        print(f"Error: Failed to read image file '{image_file}'.")
        sys.exit(1)


    rows,cols = cv_img.shape

    print(str(cv_img[0,0]))
    print(str(cv_img[1,0])) #print 66 img :(0,1) 66
    print(str(cv_img[0,1])) # print 64 (1,0)

    # (col, row) [row, col]
 
    t_grayval = []
    t_grayval_1 = []
    
    for j in range(cols) :
        for i in range(rows-1):
            t_grayval.append(cv_img[i,j])
            t_grayval_1.append(cv_img[i+1,j])


    x = t_grayval
    y = t_grayval_1

    # plt.plot(x, y, 'ro') # Your original list

    plt.scatter(x,y, color = "#16e5cb", marker = 'x', s=1)
    plt.xlabel('Pixel gray value on location (x,y)')
    plt.ylabel('Pixel gray value on location (x,y+1)')
    
    plt.title('Correlation property test : vertical adjacent pixel')

    plt.show()


if __name__ == "__main__":
    main()