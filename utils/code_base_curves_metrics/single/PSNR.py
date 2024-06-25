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

    img_file_alt = sys.argv[2]
    if not os.path.isfile(img_file_alt):
        print(f"Error: File '{img_file_alt}' not found.")
        sys.exit(1)
    cv_img_alt = cv2.imread(img_file_alt, cv2.IMREAD_GRAYSCALE)
    if cv_img_alt is None:
        print(f"Error: Failed to read image file '{img_file_alt}'.")
        sys.exit(1)


    results =  cv2.PSNR(cv_img_original, cv_img_alt)
    print(str(results))





if __name__ == "__main__":
    main()
