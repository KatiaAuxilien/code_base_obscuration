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
    npcr_modes = []

    with open("NPCR_results.bin","rb") as f:
        npcr_modes = pickle.load(f)

    # for i in range(len(npcr_modes)) :
    #     for y in range(len(npcr_modes[i])):
    #         print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(npcr_modes[i][y]))
    
    ########## MOYENNE ##########

    avg_modes= []
    sum = []
    sum1 = 0

    for i in range(len(npcr_modes)) :
        sum1 = 0
        for y in range(len(npcr_modes[i])):
            if(y == 2) :
                print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(npcr_modes[i][y]))

            sum1 +=npcr_modes[i][y];
        sum.append(sum1)

 
    for i in range(len(npcr_modes)) :
        avg_modes.append(sum[i] / 1000)


    ########## BARRES ##########
    x = modes_op_aes
    y = avg_modes
    couleurs = ['blue','orange', 'green', 'red', 'purple']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('NPCR')
    plt.title('Graphe du NPCR moyen de 1000 images chiffrées par chiffrement AES en différents modes opératoire')

    min = 99.608
    max = 99.611
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.0001))
    plt.show()
        
    ########## COURBES ##########

    for i in range(0,len(npcr_modes)):
            
        x = np.arange(0, len(npcr_modes[i])) 
        y = npcr_modes[i]

        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('NPCR')
    plt.title('Courbes du NPCR d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
