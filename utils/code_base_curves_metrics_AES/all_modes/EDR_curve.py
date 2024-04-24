import numpy as np
import matplotlib.pyplot as plt
import math
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

    ############ COURBES ############
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


    ############ MOYENNES ############

    t_ecart_type = []
    t_avg = []
    for i in range(0, len(edr_modes)):
        sum = 0
        sum_pow = 0
        for y in range (0, len(edr_modes[i])):
            sum += edr_modes[i][y]
            sum_pow += pow(edr_modes[i][y], 2)
        avg = sum/len(edr_modes[i])
        pow_avg = sum_pow/len(edr_modes[i])
        t_avg.append(avg)
        var = pow_avg - pow(avg,2)
        t_ecart_type.append(math.sqrt(var))

    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('EDR')
    plt.title('Courbes de l\'EDR moyen d\'images chiffrées par chiffrement AES en différents modes d\'opération')

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
        plt.text(modes_op_aes[i], t_avg[i] + 0.00005 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)

    min = 0.4189
    max = 0.4194
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.0001))
    plt.show()

if __name__ == "__main__":
    main()
