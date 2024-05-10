
import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle

def main() :
    f_x = open("results_x.txt", "r")
    lines_x = f_x.readlines()

    # nb_r_x = lines_x[0]
    # g_x = lines_x[1]
    # lines_x.pop(1)

    t_x_avg = []
    r_val_x = []
    for l in range(len(lines_x)):
        if(l % 2 == 0):
            val = np.ulonglong(lines_x[l].replace("\n", ""))
            r_val_x.append(val)
        if(l % 2 != 0):
            val = np.double(lines_x[l].replace("\n", ""))
            t_x_avg.append(val)



    f_y = open("results_y.txt", "r")
    lines_y = f_y.readlines()

    # nb_r_y = lines_y[0]
    # g_y = lines_y[1]
    # lines_y.pop(0)
    # lines_y.pop(1)

    t_y_avg = []
    r_val_y = []
    for l in range(len(lines_y)):
        if(l % 2 == 0):
            val = np.ulonglong(lines_y[l].replace("\n", ""))
            r_val_y.append(val)
        if(l % 2 != 0):
            val = np.double(lines_y[l].replace("\n", ""))
            t_y_avg.append(val)


    f_pix = open("results_pix.txt", "r")
    lines_pix = f_pix.readlines()

    t_pix_avg = []
    r_val_pix = []
    for l in range(len(lines_pix)):
        if(l % 2 == 0):
            val = np.ulonglong(lines_pix[l].replace("\n", ""))
            r_val_pix.append(val)
        if(l % 2 != 0):
            val = np.double(lines_pix[l].replace("\n", ""))
            t_pix_avg.append(val)


    avg_x = 0
    ecart_type_x = 0
    sum = 0
    sum_pow = 0
    pow_avg = 0
    var = 0
    for i in range(len(t_x_avg)) : 
        sum += t_x_avg[i]
        sum_pow += pow(t_x_avg[i], 2)
    avg_x = sum/len(t_x_avg)
    pow_avg = sum_pow/len(t_x_avg)
    var = pow_avg - pow(avg_x,2)
    ecart_type_x = math.sqrt(var)


    avg_y = 0
    ecart_type_y = 0
    sum = 0
    sum_pow = 0
    pow_avg = 0
    var = 0
    for i in range(len(t_y_avg)) :
        sum += t_y_avg[i]
        sum_pow += pow(t_y_avg[i], 2)
    avg_y = sum/len(t_y_avg)
    pow_avg = sum_pow/len(t_y_avg)
    var = pow_avg - pow(avg_y,2)
    ecart_type_y = math.sqrt(var)


    avg_pix = 0
    ecart_type_pix = 0
    sum = 0
    sum_pow = 0
    pow_avg = 0
    var = 0
    for i in range(len(t_pix_avg)) :
        sum += t_pix_avg[i]
        sum_pow += pow(t_pix_avg[i], 2)
    avg_pix = sum/len(t_pix_avg)
    pow_avg = sum_pow/len(t_pix_avg)
    var = pow_avg - pow(avg_pix,2)
    ecart_type_pix = math.sqrt(var)

    print(str(avg_x))
    print(str(avg_y))
    print(str(avg_pix))
    print(str(ecart_type_x))
    print(str(ecart_type_y))
    print(str(ecart_type_pix))

    x1 = r_val_x
    x2 = r_val_y
    y1 = t_x_avg
    y2 = t_y_avg
    x3 = r_val_pix
    y3 = t_pix_avg
    plt.plot(x1, y1,label="x = pixel_encrypted / n",color="red")
    plt.axhline(y = avg_x, color = 'crimson')
    plt.axhline(y = avg_x + ecart_type_x /2, color = 'crimson')
    plt.axhline(y = avg_x - ecart_type_x /2, color = 'crimson')


    plt.plot(x2, y2,label="y = pixel_encrypted % n",color="blue")
    plt.axhline(y = avg_y, color = 'mediumblue')
    plt.axhline(y = avg_y + ecart_type_y /2, color = 'mediumblue')
    plt.axhline(y = avg_y - ecart_type_y /2, color = 'mediumblue')


    plt.plot(x3, y3,label="pixel encrypted",color="yellow")
    plt.axhline(y = avg_pix, color = 'gold')
    plt.axhline(y = avg_pix + ecart_type_pix /2, color = 'gold')
    plt.axhline(y = avg_pix - ecart_type_pix /2, color = 'gold')

    # plt.xticks(np.arange(min(r_val_x), max(r_val_x)+1, step=10))
    # plt.xticks(r_val_x)
    plt.xlabel('Valeur de r')
    plt.ylabel('Moyenne des chiffrés pairs')
    plt.title('...')
    plt.grid()
    plt.legend()
    plt.show()



    ########## BARRES ##########
    x1 = r_val_x
    y1 = t_x_avg
    
    plt.bar(x1, y1, color="red")
    # plt.errorbar(range(len(y)),y,t_ecart_type2, fmt='none',capsize=10,ecolor='black',elinewidth=2,capthick=2)

    plt.xlabel('...')
    plt.ylabel('..')
    plt.title('...')

    # font = {'family': 'serif',
    #         'color':  'black',
    #         'weight': 'bold',
    #         'size': 8
    #         }

    # box = {'facecolor': 'none',
    #     'edgecolor': 'black',
    #     'boxstyle': 'round'
    #     }

    # avg_min, avg_max = min(t_avg), max(t_avg)
    # ecart_min, ecart_max = min(t_ecart_type), max(t_ecart_type)

    # facteur = 1
    # mini = avg_min - facteur * ecart_max
    # maxi = avg_max + facteur * ecart_max

    # plt.ylim(mini, maxi)
    # espacement = (maxi - mini) / 30
    # plt.yticks(np.arange(mini, maxi + espacement, espacement))

    # for i in range(0, len(modes_op_aes)):
    #     plt.text( modes_op_aes[i], t_avg[i] + espacement/2 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)

    plt.show()

    x2 = r_val_y
    y2 = t_y_avg
    
    plt.bar(x2, y2, color="blue")
    plt.xlabel('...')
    plt.ylabel('..')
    plt.title('...')

    plt.show()

    
    x3 = r_val_pix
    y3 = t_pix_avg
    
    plt.bar(x3, y3, color="yellow")
    plt.xlabel('...')
    plt.ylabel('..')
    plt.title('...')

    plt.show()


if __name__ == "__main__":
    main()
