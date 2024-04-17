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


    ########## BARRES ##########
    # x = modes_op_aes
    # y = entropy_avg_modes
    # couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    # plt.bar(x, y, color=couleurs)

    # plt.xlabel('Mode opératoire')
    # plt.ylabel('Entropie')
    # plt.title('Graphe de l\'entropie moyenne d\'images chiffrées par chiffrement AES en différents modes opératoire')

    # min = 7.55
    # max = 8.1
    # plt.ylim(min,max)
    # plt.yticks(np.arange(min,max, 0.01))
    # plt.show()
        
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


    # print("entropy")
    for i in range(0,len(entropy_modes)):
        # print(modes_op_aes[i])
        # for y in range(0,len(entropy_modes[i])):
        #     print(entropy_modes[i][y])
            
        x = np.arange(0, len(entropy_modes[i]))  # Indices des images
        y = entropy_modes[i]  # entropy pour le premier mode opératoire

        plt.plot(x, y,label=modes_op_aes[i],marker = 'o')

    plt.xlabel('Images')
    plt.ylabel('Entropy')
    plt.title('Courbes d\'entropie d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    # plt.xticks(np.arange(1, len(entropy_modes[0]), 1))
    plt.show()


if __name__ == "__main__":
    main()
