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


    avg_modes= []
    sum = []
    sum1 = 0

    for i in range(len(uaci_modes)) :
        sum1 = 0
        for y in range(len(uaci_modes[i])):
            # if(y == 2) :
            #     print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(uaci_modes[i][y]))
            sum1 +=uaci_modes[i][y];
        sum.append(sum1)

 
    for i in range(len(uaci_modes)) :
        avg_modes.append(sum[i] / 1000)


    ########## BARRES ##########
    x = modes_op_aes
    y = avg_modes
    couleurs = ['blue','orange', 'green', 'red', 'purple']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('NPCR')
    plt.title('Graphe du UACI moyen de 1000 images chiffrées par chiffrement AES en différents modes opératoire')

    min = 49.975
    max = 50.005
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.001))
    plt.show()
        
    ########## COURBES ##########

    for i in range(len(uaci_modes)) :
        for y in range(len(uaci_modes[i])):
            print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(uaci_modes[i][y]))

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
