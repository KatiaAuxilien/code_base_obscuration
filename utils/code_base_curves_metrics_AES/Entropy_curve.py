import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]







    # plt.plot(x, y, marker = 'o')

    # plt.xlabel('Mode opératoire')
    # plt.ylabel('Entropie')
    # plt.title('Courbe de l\'entropie moyenne des modes opératoire du chiffrement AES')

    # min = 7.65
    # max = 8.1
    # plt.ylim(min,max)
    # plt.yticks(np.arange(min,max, 0.01))

    # plt.show()

    entropy_modes = []
    
    with open("Entropy_results.bin","rb") as f:
        entropy_modes = pickle.load(f)
    
    ########## MOYENNE ##########

    entropy_avg_modes= []
    sum = []
    sum1 = 0

    for i in range(len(entropy_modes)) :
        sum1 = 0
        for y in range(len(entropy_modes[i])):
            # print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(entropy_modes[i][y]))
            sum1 +=entropy_modes[i][y];
        sum.append(sum1)

    for i in range(len(entropy_modes)) :
        entropy_avg_modes.append(sum[i] / 1000)

    ########## BARRES ##########
    x = modes_op_aes
    y = entropy_avg_modes
    couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('Entropie (bit)')
    plt.title('Graphe de l\'entropie moyenne de 1000 images chiffrées par chiffrement AES en différents modes opératoire')

    min = 7.975
    max = 8.001
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.001))
    plt.show()

    ########## COURBES ##########

    for i in range(0,len(entropy_modes)):
        x = np.arange(0, len(entropy_modes[i]))
        y = entropy_modes[i]

        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('Entropie (bit)')
    plt.title('Courbes d\'entropie d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
