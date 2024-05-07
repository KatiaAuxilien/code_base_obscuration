
import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle

def main() :
    f = open("results_pix_enc.txt", "r")
    lines = f.readlines()

    nb_r = lines[0]
    g = lines[1]
    lines.pop(0)
    lines.pop(1)

    t_pix_enc_avg = []
    r_val = []
    for l in range(lines.size()):
        if(l % 2 != 0):
            val = np.ulonglong(lines[l].replace("\n", ""))
            r_val.append()
        if(l % 2 == 0):
            val = np.double(lines[l].replace("\n", "")
            t_pix_enc_avg.append(val)



if __name__ == "__main__":
    main()
