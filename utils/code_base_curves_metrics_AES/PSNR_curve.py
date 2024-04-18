import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]
    psnr_modes = []

    with open("PSNR_results.bin","rb") as f:
        psnr_modes = pickle.load(f)

    for i in range(0,len(psnr_modes)):
        x = np.arange(0, len(psnr_modes[i])) 
        y = psnr_modes[i] 

        plt.plot(x, y,label=modes_op_aes[i])


    # plt.yticks(np.arange(5.0, 8.5 + 0.1, 0.1))
    # plt.xticks(np.arange(1, len(psnr_modes[0]), 1))
    plt.xlabel('Images')
    plt.ylabel('PSNR (dB)')
    plt.title('Courbes du PSNR d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    plt.grid()
    plt.legend()
    plt.show()




if __name__ == "__main__":
    main()
