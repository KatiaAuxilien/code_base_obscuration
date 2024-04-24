import numpy as np
import matplotlib.pyplot as plt
import math
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


    ############ MOYENNES ############

    t_ecart_type = []
    t_avg = []
    for i in range(0, len(ssim_modes)):
        sum = 0
        sum_pow = 0
        for y in range (0, len(ssim_modes[i])):
            sum += ssim_modes[i][y]
            sum_pow += pow(ssim_modes[i][y], 2)
        avg = sum/len(ssim_modes[i])
        pow_avg = sum_pow/len(ssim_modes[i])
        t_avg.append(avg)
        var = pow_avg - pow(avg,2)
        t_ecart_type.append(math.sqrt(var))

    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('SSIM')
    plt.title('Courbes de la SSIM moyenne d\'images chiffrées par chiffrement AES en différents modes d\'opération')

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
        plt.text(modes_op_aes[i], t_avg[i] + 0.000005 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)
    min = 0.0088
    max = 0.008935
    plt.ylim(min,max)
    plt.yticks(np.arange(min,max, 0.00001))
    plt.show()


if __name__ == "__main__":
    main()
