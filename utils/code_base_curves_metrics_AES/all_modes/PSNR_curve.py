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
    psnr_modes = []

    with open("PSNR_results.bin","rb") as f:
        psnr_modes = pickle.load(f)

    # for i in range(len(psnr_modes)) :
    #     for y in range(len(psnr_modes[i])):
    #         if(y == 2) :
    #             print(str(modes_op_aes[i]) + " n°"+ str(y)+" : " + str(psnr_modes[i][y]))

    # i=4
    # x = np.arange(0, len(psnr_modes[i])) 
    # y = psnr_modes[i] 

    # plt.plot(x, y,label=modes_op_aes[i])

    # i=3
    # x = np.arange(0, len(psnr_modes[i])) 
    # y = psnr_modes[i] 

    # plt.plot(x, y,label=modes_op_aes[i])

    # i=2
    # x = np.arange(0, len(psnr_modes[i])) 
    # y = psnr_modes[i] 

    # plt.plot(x, y,label=modes_op_aes[i])

    
    # i=0
    # x = np.arange(0, len(psnr_modes[i])) 
    # y = psnr_modes[i] 

    # plt.plot(x, y,label=modes_op_aes[i])
    
    # i=1
    # x = np.arange(0, len(psnr_modes[i])) 
    # y = psnr_modes[i] 

    # plt.plot(x, y,label=modes_op_aes[i])


    # plt.xlabel('Images')
    # plt.ylabel('PSNR (dB)')
    # plt.title('Courbes du PSNR d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    # plt.grid()
    # plt.legend()
    # plt.show()


    
    ############ MOYENNES ############

    t_ecart_type = []
    t_ecart_type2 = []
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
        t_ecart_type2.append(math.sqrt(var)/2)

    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['blue', 'green', 'red', 'purple', 'orange']
    plt.bar(x, y, color=couleurs)
    plt.errorbar(range(len(y)),y,t_ecart_type2, fmt='none',capsize=10,ecolor='black',elinewidth=2,capthick=2)

    plt.xlabel('Mode opératoire')
    plt.ylabel('PSNR (dB)')
    plt.title('Courbes du PSNR moyen d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    font = {'family': 'serif',
            'color':  'black',
            'weight': 'bold',
            'size': 8
            }

    box = {'facecolor': 'none',
        'edgecolor': 'black',
        'boxstyle': 'round'
        }

    avg_min, avg_max = min(t_avg), max(t_avg)
    ecart_min, ecart_max = min(t_ecart_type), max(t_ecart_type)

    facteur = 0.55

    mini = avg_min - facteur * ecart_max
    maxi = avg_max + facteur * ecart_max

    plt.ylim(mini, maxi)
    espacement = (maxi - mini) / 30
    plt.yticks(np.arange(mini, maxi + espacement, espacement))

    for i in range(0, len(modes_op_aes)):
        plt.text( modes_op_aes[i], t_avg[i] + espacement/2 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)

    plt.show()


if __name__ == "__main__":
    main()
