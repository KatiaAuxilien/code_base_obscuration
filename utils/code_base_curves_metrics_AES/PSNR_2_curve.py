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
    modes_op_aes = ["CFB","CFB_div"]
    psnr_modes = []

    with open("PSNR_2_results.bin","rb") as f:
        psnr_modes = pickle.load(f)

    for i in range(len(psnr_modes)) :
        for y in range(len(psnr_modes[i])):
            x = np.arange(0, len(psnr_modes[i])) 
            y = psnr_modes[i] 
            plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('PSNR (dB)')
    plt.title('Courbes du PSNR d\'images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')
    plt.grid()
    plt.legend()
    plt.show()
    
    ############ MOYENNES ############

    t_ecart_type = []
    t_avg = []
    for i in range(0, len(psnr_modes)):
        sum = 0
        sum_pow = 0
        for y in range (0, len(psnr_modes[i])):
            sum += psnr_modes[i][y]
            sum_pow += pow(psnr_modes[i][y], 2)
        avg = sum/len(psnr_modes[i])
        pow_avg = sum_pow/len(psnr_modes[i])
        t_avg.append(avg)
        var = pow_avg - pow(avg,2)
        t_ecart_type.append(math.sqrt(var))

    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['purple', 'pink']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('PSNR (dB)')
    plt.title('Courbes du PSNR moyen d\'images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')

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
        plt.text(modes_op_aes[i], t_avg[i] , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)

    min = 8.34
    max = 8.355
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.001))
    plt.show()


if __name__ == "__main__":
    main()
