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
    modes_op_aes = ["CFB","CFB_dec_bad_key"]
    couleurs = ['purple', 'pink']

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
    
    with open("Entropy_2_results.bin","rb") as f:
        entropy_modes = pickle.load(f)
    
    
    # for i in range(len(entropy_modes)):
    #     for y in range(len(entropy_modes[i])) :
    #         print(modes_op_aes[i] + ':' + str(entropy_modes[i][y]))

    ########## MOYENNE ##########

    entropy_avg_modes= []
    entropy_ecart_type_modes = []
    entropy_ecart_type_modes2=[]
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
        entropy_ecart_type_modes2.append(o/2)


    ########## BARRES ##########
    x = modes_op_aes
    y = entropy_avg_modes
    plt.bar(x, y, color=couleurs)
    plt.errorbar(range(len(y)),y,entropy_ecart_type_modes2, fmt='none',capsize=10,ecolor='black',elinewidth=2,capthick=2)

    plt.xlabel('Mode opératoire')
    plt.ylabel('Entropie (bit/pixel)')
    plt.title('Graphe de l\'entropie moyenne de 1000 images chiffrées par chiffrement AES en CFB et CFB déchiffrées (mauvaise clé)')

    font = {'family': 'serif',
            'color':  'black',
            'weight': 'bold',
            'size': 8
            }

    box = {'facecolor': 'none',
        'edgecolor': 'black',
        'boxstyle': 'round'
        }

    
    avg_min, avg_max = min(entropy_avg_modes), max(entropy_avg_modes)
    ecart_min, ecart_max = min(entropy_ecart_type_modes), max(entropy_ecart_type_modes)

    facteur = 0.50

    mini = avg_min - facteur * ecart_max
    maxi = avg_max + facteur * ecart_max

    plt.ylim(mini, maxi)
    espacement = (maxi - mini) / 30
    plt.yticks(np.arange(mini, maxi + espacement, espacement))

    for i in range(0, len(modes_op_aes)):
        plt.text( modes_op_aes[i], entropy_avg_modes[i] + espacement/2 , 's = '+ str(entropy_ecart_type_modes[i])+'', fontdict=font, bbox=box)

    plt.show()

    ########## COURBES ##########
    for i in range(0,len(entropy_modes)):
        x = np.arange(0, len(entropy_modes[i]))
        y = entropy_modes[i]

        plt.plot(x, y,label=modes_op_aes[i],color=couleurs[i])

    plt.xlabel('Images')
    plt.ylabel('Entropie (bit/pixel)')
    plt.title('Courbes d\'entropie d\'images chiffrées par chiffrement AES en CFB et CFB déchiffrées (mauvaise clé)')
    plt.grid()
    plt.legend()
    plt.show()

    ########## COURBES INDIVIDUEL ##########
    # for i in range(0,len(entropy_modes)):
    #     x = np.arange(0, len(entropy_modes[i]))
    #     y = entropy_modes[i]

    #     plt.plot(x, y,label=modes_op_aes[i], color=couleurs[i])
        
    #     plt.xlabel('Images')
    #     plt.ylabel('Entropie (bit/pixel)')
    #     plt.title('Courbe d\'entropie d\'images chiffrées par chiffrement AES en '+modes_op_aes[i])
    #     plt.grid()
    #     plt.legend()
    #     plt.show()


if __name__ == "__main__":
    main()
