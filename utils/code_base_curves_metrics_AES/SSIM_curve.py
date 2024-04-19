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
    ssim_modes = []

    with open("SSIM_results.bin","rb") as f:
        ssim_modes = pickle.load(f)

    # for i in range(len(ssim_modes)) :
    #     for y in range(len(ssim_modes[i])):
    #         if(y == 2) :
    #             print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(ssim_modes[i][y]))

    avg_modes= []
    sum = []
    sum1 = 0

    for i in range(len(ssim_modes)) :
        sum1 = 0
        for y in range(len(ssim_modes[i])):
            sum1 +=ssim_modes[i][y];
        sum.append(sum1)

 
    for i in range(len(ssim_modes)) :
        avg_modes.append(sum[i] / 1000)


    ########## BARRES ##########
    x = modes_op_aes
    y = avg_modes
    couleurs = ['blue','orange', 'green', 'red', 'purple']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('NPCR')
    plt.title('Graphe de la SSIM moyenne de 1000 images chiffrées par chiffrement AES en différents modes opératoire')

    min = 0.0088
    max = 0.008935
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.00001))
    plt.show()

    ########## COURBES ##########

    for i in range(0,len(ssim_modes)):
        x = np.arange(0, len(ssim_modes[i])) 
        y = ssim_modes[i] 

        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('SSIM')
    plt.title('Courbes de la SSIM d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
