import matplotlib.pyplot as plt
import math
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
    # plt.ylabel('Entropie (bit/pixel)')
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
    entropy_ecart_type_modes = []

    sum = []
    sum1 = 0

    t__sum_pow = []
    sum_pow = 0

    for i in range(len(entropy_modes)) :
        sum1 = 0
        sum_pow = 0 
        for y in range(len(entropy_modes[i])):
            sum1 +=entropy_modes[i][y]
            sum_pow += pow(entropy_modes[i][y],2)
        sum.append(sum1)
        t__sum_pow.append(sum_pow)

    for i in range(len(entropy_modes)) :
        entropy_avg = sum[i] / len(entropy_modes[i])
        entropy_avg_modes.append(entropy_avg)

        entropy_avg_pow =  t__sum_pow[i] / len(entropy_modes[i])
        var = entropy_avg_pow - pow(entropy_avg,2)
        o = math.sqrt(var)
        entropy_ecart_type_modes.append(o)



    ########## BARRES ##########
    x = modes_op_aes
    y = entropy_avg_modes
    couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('Entropie (bit/pixel)')
    plt.title('Graphe de l\'entropie moyenne de 1000 images chiffrées par chiffrement AES en différents modes opératoire')

    font = {'family': 'serif',
            'color':  'black',
            'weight': 'bold',
            'size': 8
            }

    box = {'facecolor': 'none',
        'edgecolor': 'black',
        'boxstyle': 'round'
        }

    #add text with custom font
    for i in range(0, len(modes_op_aes)):
        plt.text(modes_op_aes[i], entropy_avg_modes[i] + 0.001 , 's = '+ str(entropy_ecart_type_modes[i])+'', fontdict=font, bbox=box)

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
    plt.ylabel('Entropie (bit/pixel)')
    plt.title('Courbes d\'entropie d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    plt.show()

    ########## COURBES INDIVIDUEL ##########
    for i in range(0,len(entropy_modes)):
        x = np.arange(0, len(entropy_modes[i]))
        y = entropy_modes[i]

        plt.plot(x, y,label=modes_op_aes[i], color=couleurs[i])
        
        plt.xlabel('Images')
        plt.ylabel('Entropie (bit/pixel)')
        plt.title('Courbe d\'entropie d\'images chiffrées par chiffrement AES en '+modes_op_aes[i])
        plt.grid()
        plt.legend()
        plt.show()


if __name__ == "__main__":
    main()
