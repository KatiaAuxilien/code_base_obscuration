
import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle

############### According to r value.

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo k by r value.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param p: A prime number used in Paillier encryption.
# @param q: Another prime number used in Paillier encryption.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_k_by_r_value(t_pix_enc, vector_r_values,n,size_vec_r, p, q):
    t_k = [2,4,8,16,32,64,128,256]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid"]

    for k in range(len(t_k)):
        mod = t_k[k]
        t_pix_avg = []
        t_count_mod_k = []
        for i in range(size_vec_r):
            count_mod_k= 0
            for j in range(n):
                val = t_pix_enc[i][j]
                if(val% mod==0):
                    count_mod_k+=1
            t_count_mod_k.append(count_mod_k)
            t_pix_avg.append(count_mod_k/n)


        avg_pix = 0
        ecart_type_pix = 0
        sum = 0
        sum_pow = 0
        pow_avg = 0
        var = 0
        for i in range(size_vec_r) :
            sum += t_pix_avg[i]
            sum_pow += pow(t_pix_avg[i], 2)
        avg_pix = sum/size_vec_r
        pow_avg = sum_pow/len(t_pix_avg)
        var = pow_avg - pow(avg_pix,2)
        ecart_type_pix = math.sqrt(var)

        print("AVG mod "+str(mod)+ " : " + str(avg_pix))
        print("Ecart type mod "+str(mod)+ " : " +str(ecart_type_pix))

        x = vector_r_values
        y = t_pix_avg

        plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])
        plt.axhline(y = avg_pix, color = color_avg_curve[k])
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k])
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k])

        plt.xlabel('Valeur de r')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        plt.title('Courbe de la moyenne des chiffrés, par paillier, modulo '+str(mod)+' = 0 en fonction de r, pour p = '+str(p)+' et q = '+str(q)+'')
        plt.grid()
        plt.legend()
        plt.show()

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo k by r value for inverse encryption.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param p: A prime number used in Paillier encryption.
# @param q: Another prime number used in Paillier encryption.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_k_by_r_value_inv(t_pix_enc, vector_r_values,n,size_vec_r, p,q):
    t_k = [2,4,8,16,32,64,128,256]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid"]

    for k in range(len(t_k)):
        mod = t_k[k]
        t_pix_avg = []
        t_count_mod_k = []
        for i in range(size_vec_r):
            count_mod_k= 0
            for j in range(n):
                val = t_pix_enc[i][j]
                if(val% mod==0):
                    count_mod_k+=1
            t_count_mod_k.append(count_mod_k)
            t_pix_avg.append(count_mod_k/n)


        avg_pix = 0
        ecart_type_pix = 0
        sum = 0
        sum_pow = 0
        pow_avg = 0
        var = 0
        for i in range(size_vec_r) :
            sum += t_pix_avg[i]
            sum_pow += pow(t_pix_avg[i], 2)
        avg_pix = sum/size_vec_r
        pow_avg = sum_pow/len(t_pix_avg)
        var = pow_avg - pow(avg_pix,2)
        ecart_type_pix = math.sqrt(var)

        print("AVG mod "+str(mod)+ " : " + str(avg_pix))
        print("Ecart type mod "+str(mod)+ " : " +str(ecart_type_pix))

        x = vector_r_values
        y = t_pix_avg

        plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])
        plt.axhline(y = avg_pix, color = color_avg_curve[k])
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k])
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k])

        plt.xlabel('Valeur de r')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        plt.title('Courbe de la moyenne des chiffrés inverse !E(x), par paillier, modulo '+str(mod)+' = 0 en fonction de r, pour p = '+str(p)+' et q = '+str(q)+'')
        plt.grid()
        plt.legend()
        plt.show()

############### According to initial pixel value.

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo k by pixel value.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param p: A prime number used in Paillier encryption.
# @param q: Another prime number used in Paillier encryption.
# @param inverse: A boolean value indicating whether to use inverse encryption or not.
# @param g: A value used in Paillier encryption.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_k_by_pixel_value(t_pix_enc, vector_r_values, n, size_vec_r, p, q, inverse, g):
    t_k = [2,4,8,16,32,64,128,256, 512]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid","purple"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet","indigo"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid","blueviolet"]

    for k in range(len(t_k)):
        mod = t_k[k]
        t_pix_avg = []
        t_count_mod_k = []
        for i in range(n):
            count_mod_k= 0
            for j in range(size_vec_r):
                val = t_pix_enc[j][i]
                if(val % mod==0):
                    count_mod_k+=1
            t_count_mod_k.append(count_mod_k)
            t_pix_avg.append(count_mod_k/size_vec_r)

        avg_pix = 0
        ecart_type_pix = 0
        sum = 0
        sum_pow = 0
        pow_avg = 0
        var = 0
        for i in range(n) :
            sum += t_pix_avg[i]
            sum_pow += pow(t_pix_avg[i], 2)
        avg_pix = sum/n
        pow_avg = sum_pow/n
        var = pow_avg - pow(avg_pix,2)
        ecart_type_pix = math.sqrt(var)

        print("AVG mod "+str(mod)+ " : " + str(avg_pix))
        print("Ecart type mod "+str(mod)+ " : " +str(ecart_type_pix))

        x = np.arange(0, n)
        y = t_pix_avg

        plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k], marker='x')
        plt.axhline(y = avg_pix, color = color_avg_curve[k],linestyle = 'dotted')
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k],linestyle = 'dashed')
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k],linestyle = 'dashed')

        plt.xlabel('Valeur du pixel clair')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        if(inverse):
            plt.title('Courbe de la moyenne des chiffrés inverse !E(x), par paillier g = '+str(g)+', modulo '+str(mod)+' = 0 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
        else:
            plt.title('Courbe de la moyenne des chiffrés, par paillier g = '+str(g)+', modulo '+str(mod)+' = 0 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
        plt.grid()
        plt.legend()
        plt.show()

############### According to initial pixel value with differents modulo

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo 2 by pixel value.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param title: The title of the plot.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_2_by_pixel_value(t_pix_enc, vector_r_values,n,size_vec_r, title):
    # t_k = [2,4,8,16,32,64,128,256]
    t_k = [2]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid"]

    for k in range(len(t_k)):
        mod = t_k[k]
        t_pix_avg_0 = []
        t_count_mod_k_0 = []
        t_pix_avg_1 = []
        t_count_mod_k_1 = []
        for i in range(n):
            count_mod_k_0= 0
            count_mod_k_1= 0
            for j in range(size_vec_r):
                val = t_pix_enc[j][i]
                if(val % mod==0):
                    count_mod_k_0+=1
                if(val % mod==1):
                    count_mod_k_1+=1
            t_count_mod_k_0.append(count_mod_k_0)
            t_pix_avg_0.append(count_mod_k_0/size_vec_r)
            t_count_mod_k_1.append(count_mod_k_1)
            t_pix_avg_1.append((count_mod_k_1/size_vec_r))

        x = np.arange(0, n)
        # plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])

        # plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 1",color=color_main_curve[k])

        fig, (ax1, ax2) = plt.subplots(2)
        fig.suptitle(title)
        
        ax1.plot(x, t_pix_avg_0,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])
        ax1.set_ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        ax1.grid()
        # ax1.legend()
        
        ax2.plot(x, t_pix_avg_1,label="average pixel encrypted modulo "+str(mod)+" = 1",color=color_main_curve[k])
        ax2.set_xlabel('Valeur du pixel clair')
        ax2.set_ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 1')
        ax2.grid()
        # ax2.legend()

        plt.show()

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo 4 by pixel value.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param title: The title of the plot.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_4_by_pixel_value(t_pix_enc, vector_r_values,n,size_vec_r, title):
    t_k = [4]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid"]

    for k in range(len(t_k)):
        mod = t_k[k]
        t_pix_avg_0 = []
        t_count_mod_k_0 = []
        t_pix_avg_1 = []
        t_count_mod_k_1 = []
        t_pix_avg_2 = []
        t_count_mod_k_2 = []
        t_pix_avg_3 = []
        t_count_mod_k_3 = []
        for i in range(n):
            count_mod_k_0= 0
            count_mod_k_1= 0
            count_mod_k_2= 0
            count_mod_k_3= 0
            for j in range(size_vec_r):
                val = t_pix_enc[j][i]
                if(val % mod==0):
                    count_mod_k_0+=1
                if(val % mod==1):
                    count_mod_k_1+=1
                if(val % mod==2):
                    count_mod_k_2+=1
                if(val % mod==3):
                    count_mod_k_3+=1
            t_count_mod_k_0.append(count_mod_k_0)
            t_pix_avg_0.append(count_mod_k_0/size_vec_r)
            t_count_mod_k_1.append(count_mod_k_1)
            t_pix_avg_1.append((count_mod_k_1/size_vec_r))
            t_count_mod_k_2.append(count_mod_k_2)
            t_pix_avg_2.append((count_mod_k_2/size_vec_r))
            t_count_mod_k_3.append(count_mod_k_3)
            t_pix_avg_3.append((count_mod_k_3/size_vec_r))

        x = np.arange(0, n)
        y = t_pix_avg_0


        fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
        fig.suptitle(title)

        # plt.xlabel('Valeur du pixel clair')
        # plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+'')


        ax1.plot(x, t_pix_avg_0,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])
        ax1.legend()
        ax1.set_ylabel('Moyenne des chiffrés modulo '+str(mod)+'')
        ax1.grid()

        ax2.plot(x, t_pix_avg_1,label="average pixel encrypted modulo "+str(mod)+" = 1",color=color_main_curve[k+1])
        ax2.legend()
        ax2.grid()

        ax3.plot(x, t_pix_avg_2,label="average pixel encrypted modulo "+str(mod)+" = 2",color=color_main_curve[k+2])
        ax3.legend()
        ax3.grid()
        ax3.set_ylabel('Moyenne des chiffrés modulo '+str(mod)+'')
        ax3.set_xlabel('Valeur du pixel clair')

        ax4.plot(x, t_pix_avg_3,label="average pixel encrypted modulo "+str(mod)+" = 3",color=color_main_curve[k+3])
        ax4.legend()
        ax4.grid()
        ax4.set_xlabel('Valeur du pixel clair')
        ax4.set_ylabel('Moyenne des chiffrés modulo '+str(mod)+'')

        # for ax in fig.get_axes():
        #     ax.label_outer()

        plt.show()


############### According to initial pixel value, with different modulo, with common values where there is no r value for modulo k = 0

##
# @brief This function calculates and plots the average curve of encrypted pixels modulo k by pixel value for common values.
#
# @param t_pix_enc: A 2D list containing encrypted pixel values.
# @param t_pix_inv_enc: A 2D list containing inversely encrypted pixel values.
# @param vector_r_values: A list containing r values.
# @param n: The number of pixels.
# @param size_vec_r: The size of the r value vector.
# @param p: A prime number used in Paillier encryption.
# @param q: Another prime number used in Paillier encryption.
# @param g: A value used in Paillier encryption.
# @author Katia Auxilien
# @date April 2024
#
def avg_curve_mod_k_by_pixel_value_in_common(t_pix_enc, t_pix_inv_enc, vector_r_values, n, size_vec_r, p, q,g):
    t_k = [2,4,8,16,32,64,128,256, 512, 1024]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid","purple", "deeppink"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet","indigo","pink"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid","blueviolet","hotpink"]
    color_main_curve_inv = list(reversed(color_main_curve))
    color_avg_curve_inv = list(reversed(color_avg_curve))
    color_ecart_type_curve_inv = list(reversed(color_ecart_type_curve))

    for k in range(len(t_k)):
        mod = t_k[k]
        #E(x)
        t_pix_avg = []
        t_count_mod_k = []
        for i in range(n):
            count_mod_k= 0
            for j in range(size_vec_r):
                val = t_pix_enc[j][i]
                if(val % mod==0):
                    count_mod_k+=1
            t_count_mod_k.append(count_mod_k)
            t_pix_avg.append(count_mod_k/size_vec_r)

        avg_pix = 0
        ecart_type_pix = 0
        sum = 0
        sum_pow = 0
        pow_avg = 0
        var = 0
        for i in range(n) :
            sum += t_pix_avg[i]
            sum_pow += pow(t_pix_avg[i], 2)
        avg_pix = sum/n
        pow_avg = sum_pow/n
        var = pow_avg - pow(avg_pix,2)
        ecart_type_pix = math.sqrt(var)

        # print("AVG mod "+str(mod)+ " : " + str(avg_pix))
        # print("Ecart type mod "+str(mod)+ " : " +str(ecart_type_pix))

        x = np.arange(0, n)
        y = t_pix_avg

        #!E(x)
        t_pix_avg_inv = []
        t_count_mod_k_inv = []
        for i in range(n):
            count_mod_k= 0
            for j in range(size_vec_r):
                val = t_pix_inv_enc[j][i]
                if(val % mod==0):
                    count_mod_k+=1
            t_count_mod_k_inv.append(count_mod_k)
            t_pix_avg_inv.append(count_mod_k/size_vec_r)

        avg_pix_inv = 0
        ecart_type_pix_inv = 0
        sum = 0
        sum_pow = 0
        pow_avg = 0
        var = 0
        for i in range(n) :
            sum += t_pix_avg[i]
            sum_pow += pow(t_pix_avg[i], 2)
        avg_pix_inv = sum/n
        pow_avg = sum_pow/n
        var = pow_avg - pow(avg_pix,2)
        ecart_type_pix_inv = math.sqrt(var)

        # print("AVG mod "+str(mod)+ " : " + str(avg_pix_inv))
        # print("Ecart type mod "+str(mod)+ " : " +str(ecart_type_pix_inv))

        x_inv = np.arange(0, n)
        y_inv = t_pix_avg_inv

        plt.plot(x, y,label="average E(x) modulo "+str(mod)+" = 0",color=color_main_curve[k], linestyle = 'solid')
        plt.axhline(y = avg_pix, color = color_avg_curve[k], linestyle = 'dotted')
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k],linestyle = 'dashed')
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k],linestyle = 'dashed')


        plt.plot(x_inv, y_inv,label="average !E(x) modulo "+str(mod)+" = 0",color=color_main_curve_inv[k], linestyle = 'solid')
        plt.axhline(y = avg_pix_inv, color = color_avg_curve_inv[k], linestyle = 'dotted')
        plt.axhline(y = avg_pix_inv + ecart_type_pix_inv /2, color = color_ecart_type_curve_inv[k], linestyle = 'dashed')
        plt.axhline(y = avg_pix_inv - ecart_type_pix_inv /2, color = color_ecart_type_curve_inv[k], linestyle = 'dashed')

        print('Niveaux gris pb %'+str(mod)+' = 0 à 0%')
        t_common= []
        common = []
        for i in range(n) :
            if(t_pix_avg[i] == 0 and t_pix_avg_inv[i] == 0):
                print(str(i))
                t_common.append(i)
                common.append(0)
            
        x_common = t_common;
        y_common = common;
        plt.scatter(x_common,y_common, color = 'black', marker = 'x')

        plt.xlabel('Valeur du pixel clair')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        
        plt.title('Courbe de la moyenne des E(x) et !E(x) , par paillier g = '+str(g)+', modulo '+str(mod)+' = 0 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
        plt.grid()
        plt.legend()
        
        plt.show()

##
# @brief This function processes the results and plots various curves.
#
# @param f_pix: The file containing pixel data.
# @param p: A prime number used in Paillier encryption.
# @param q: Another prime number used in Paillier encryption.
# @author Katia Auxilien
# @date April 2024
#            
def traiterResultats(f_pix, p,q) :

############### Initialisation, get data.
    f_pix = open(f_pix, "r")

    f_pix = open("results_pix_p13q19nbr216.txt", "r")
    p = 13
    q = 19

    lines_pix = f_pix.readlines()

    t_pix_avg = []
    count_pix = []

    g = int(lines_pix[0])
    n =  int(lines_pix[1])
    size_vec_r = int(lines_pix[2])


    vector_r_values = []
    t_pix_enc = []

    line_index = 3
    # Encrypted pixels 
    for _ in range(size_vec_r):
        r_value = np.uint64(lines_pix[line_index].strip())
        vector_r_values.append(r_value)

        t_pix_enc_row = []
        for _ in range(n):
            line_index += 1
            pix_value = np.uint16(lines_pix[line_index].strip())
            t_pix_enc_row.append(pix_value)

        t_pix_enc.append(t_pix_enc_row)
        line_index += 1

    # # Print the values
    # for r_value, row in zip(vector_r_values, t_pix_enc):
    #     if r_value == 2 :
    #         print(f"r_value: {r_value}")
    #         print(f"t_pix_enc: {row}")

############### Curves

    # Encrypted pixels 
    avg_curve_mod_2_by_pixel_value(t_pix_enc, vector_r_values,n,size_vec_r, 'Courbe de la moyenne des chiffrés, par paillier g = '+str(g)+', modulo 2 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_4_by_pixel_value(t_pix_enc, vector_r_values,n, size_vec_r, 'Courbe de la moyenne des chiffrés, par paillier g = '+str(g)+', modulo 4 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_k_by_pixel_value(t_pix_enc, vector_r_values, n, size_vec_r, p, q, False,g)

    avg_curve_mod_k_by_r_value(t_pix_enc, vector_r_values,n, size_vec_r, p ,q)

    # Encrypted pixels complement
    t_pix_enc_inv= []
    for i in range(size_vec_r):
        t_pix_enc_inv_row= []
        for j in range(n):
            x = np.invert(np.array(t_pix_enc[i][j], dtype=np.uint16))
            t_pix_enc_inv_row.append(x)
            # print("!" + str(t_pix_enc[i][j]) + " = " + str(np.binary_repr(t_pix_enc[i][j], width=16)) + "=" + str(np.binary_repr(x, width=16)))

        t_pix_enc_inv.append(t_pix_enc_inv_row)

    avg_curve_mod_2_by_pixel_value(t_pix_enc_inv, vector_r_values,n,size_vec_r, 'Courbe de la moyenne des chiffrés inversés (!E(x)), par paillier g = '+str(g)+', modulo 2 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_4_by_pixel_value(t_pix_enc_inv, vector_r_values,n, size_vec_r, 'Courbe de la moyenne des chiffrés inversés (!E(x)), par paillier g = '+str(g)+', modulo 4 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_k_by_pixel_value(t_pix_enc_inv, vector_r_values, n, size_vec_r, p, q, True,g)

    avg_curve_mod_k_by_r_value_inv(t_pix_enc_inv, vector_r_values,n, size_vec_r, p, q)

    # Curves of pixels E(x) and !E(x) to have r values which don't have mod(k) = 0.
    avg_curve_mod_k_by_pixel_value_in_common(t_pix_enc, t_pix_enc_inv, vector_r_values, n, size_vec_r, p, q, g)

##
# @brief The main function that processes all result files in a directory.
# @author Katia Auxilien
# @date April 2024
#
def main() :
    
    dossier_images = "StatG3_83\\"
    file_tab = []
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".txt") :
            file_tab.append(dossier_images+fichier)

    p = 3
    q = 83

    for i in range(len(file_tab)): 
        traiterResultats(file_tab[i], p, q)

    dossier_images = "StatG13_19\\"
    file_tab = []
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".txt") :
            file_tab.append(dossier_images+fichier)

    p = 13
    q = 19

    for i in range(len(file_tab)): 
        traiterResultats(file_tab[i], p ,q)



if __name__ == "__main__":
    main()
