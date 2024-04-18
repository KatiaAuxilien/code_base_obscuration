import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import sys
import pickle
sys.path.append('../')

from lib.metriques import *

def main() :

    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]
    uaci_modes = []

    with open("UACI_results.bin","rb") as f :
        uaci_modes = pickle.load(f)

    for i in range(0,len(uaci_modes)):            
        x = np.arange(0, len(uaci_modes[i])) 
        y = uaci_modes[i]

        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('UACI')
    plt.title('Courbes du UACI d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
