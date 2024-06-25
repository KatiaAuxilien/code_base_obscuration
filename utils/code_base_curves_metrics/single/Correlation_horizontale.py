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

    # print(str(cv_img[0,0]))
    # print(str(cv_img[1,0])) #print 66 img :(0,1) 66
    # print(str(cv_img[0,1])) # print 64 (1,0)

    # # (col, row) [row, col]
 
    t_grayval = []
    t_grayval_1 = []
    
    for j in range(rows) :
        for i in range(cols-1):
            t_grayval.append(cv_img[j,i])
            t_grayval_1.append(cv_img[j,i+1])


    x = t_grayval
    y = t_grayval_1

    plt.scatter(x,y, color = "#16e5cb", marker = 'x', s=2)
    plt.xlabel('Pixel gray value on location (x,y)')
    plt.ylabel('Pixel gray value on location (x,y+1)')
    
    plt.title('Correlation property test : horizontal adjacent pixel')

    plt.show()



    x_sample_mean = 0
    y_sample_mean = 0

    x_sum = 0
    y_sum = 0
    for i in range(len(t_grayval)): 
        x_sum = x_sum + t_grayval[i]
        y_sum = y_sum + t_grayval_1[i]

    x_sample_mean = (x_sum) / len(t_grayval)
    y_sample_mean = (y_sum) / len(t_grayval_1)


    sample_covariance = 0
    sample_standard_deviation_x = 0
    sample_standard_deviation_y = 0

    for i in range(len(t_grayval)):
        xi_and_xmean = (t_grayval[i] - x_sample_mean)
        yi_and_ymean = (t_grayval_1[i] - y_sample_mean)
        
        sample_covariance = sample_covariance + (xi_and_xmean * yi_and_ymean)

        sample_standard_deviation_x = sample_standard_deviation_x + pow(xi_and_xmean,2)
        sample_standard_deviation_y = sample_standard_deviation_y + pow(yi_and_ymean, 2)

    

    rxy = sample_covariance / math.sqrt(sample_standard_deviation_x * sample_standard_deviation_y)

    print(str(rxy))

if __name__ == "__main__":
    main()