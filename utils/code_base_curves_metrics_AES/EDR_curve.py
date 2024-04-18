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
    edr_modes = []

    with open("EDR_results.bin","rb") as f:
        edr_modes = pickle.load(f)
    
    for i in range(len(edr_modes)) :
        for y in range(len(edr_modes[i])):
            print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(edr_modes[i][y]))


    for i in range(0,len(edr_modes)):
        x = np.arange(0, len(edr_modes[i]))
        y = edr_modes[i]  
        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('EDR')
    plt.title('Courbes du EDR d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
