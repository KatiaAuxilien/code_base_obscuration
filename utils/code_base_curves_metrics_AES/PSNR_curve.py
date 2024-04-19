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

    for i in range(len(psnr_modes)) :
        for y in range(len(psnr_modes[i])):
            if(y == 2) :
                print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(psnr_modes[i][y]))

    i=4
    x = np.arange(0, len(psnr_modes[i])) 
    y = psnr_modes[i] 

    plt.plot(x, y,label=modes_op_aes[i])

    i=3
    x = np.arange(0, len(psnr_modes[i])) 
    y = psnr_modes[i] 

    plt.plot(x, y,label=modes_op_aes[i])

    i=2
    x = np.arange(0, len(psnr_modes[i])) 
    y = psnr_modes[i] 

    plt.plot(x, y,label=modes_op_aes[i])

    
    i=0
    x = np.arange(0, len(psnr_modes[i])) 
    y = psnr_modes[i] 

    plt.plot(x, y,label=modes_op_aes[i])
    
    i=1
    x = np.arange(0, len(psnr_modes[i])) 
    y = psnr_modes[i] 

    plt.plot(x, y,label=modes_op_aes[i])


    plt.xlabel('Images')
    plt.ylabel('PSNR (dB)')
    plt.title('Courbes du PSNR d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
