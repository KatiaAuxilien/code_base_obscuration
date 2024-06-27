import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    if len(sys.argv) < 2:
        print("Usage: python "+sys.argv[0]+" <image_file_origin> <image_file_alt>")
        sys.exit(1)

    img_file_origin = sys.argv[1]
    if not os.path.isfile(img_file_origin):
        print(f"Error: File '{img_file_origin}' not found.")
        sys.exit(1)

    cv_img_original = cv2.imread(img_file_origin, cv2.IMREAD_GRAYSCALE)
    if cv_img_original is None:
        print(f"Error: Failed to read image file '{img_file_origin}'.")
        sys.exit(1)

    # https://towardsdev.com/how-to-plot-a-histogram-of-a-grayscale-image-in-2-ways-in-python-using-opencv-e17f1e3e537d
    # plt.subplot(1,2,1)
    # plt.imshow(cv_img_original,cmap='gray')
    # plt.title('image')
    # plt.xticks([])
    # plt.yticks([])

    # plt.subplot(1,2,2)
    plt.hist(cv_img_original.ravel(),256,[0,255])
    plt.title('histogram')
    plt.xlabel('Grayscale')
    plt.ylabel('Number of pixel')
    plt.show()



if __name__ == "__main__":
    main()
