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
        print("Usage: python "+sys.argv[0]+" <image_file>")
        sys.exit(1)

    img_file = sys.argv[1]
    if not os.path.isfile(img_file):
        print(f"Error: File '{img_file}' not found.")
        sys.exit(1)

    cv_img_alt = cv2.imread(img_file, cv2.IMREAD_GRAYSCALE)
    if cv_img_alt is None:
        print(f"Error: Failed to read image file '{img_file}'.")
        sys.exit(1)

    entropy = calculate_entropy_gray(cv_img_alt)
    print(str(entropy))

if __name__ == "__main__":
    main()
