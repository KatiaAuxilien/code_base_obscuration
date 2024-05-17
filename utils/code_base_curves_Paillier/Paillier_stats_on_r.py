
import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle

############### En fonction de r
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

#En fonction de la valeur du pixel clair.
def avg_curve_mod_k_by_pixel_value(t_pix_enc, vector_r_values, n, size_vec_r, p, q, inverse):
    t_k = [2,4,8,16,32,64,128,256]
    color_main_curve = ["orangered","darkorange","gold","limegreen","springgreen","deepskyblue","royalblue","darkorchid"]
    color_avg_curve = ["darkred","orange","lightyellow","lightgreen","seagreen","turquoise","lightsteelblue","violet"]
    color_ecart_type_curve = ["red","wheat","yellow","palegreen","darkgreen","dodgerblue","darkblue","mediumorchid"]

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

        plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+" = 0",color=color_main_curve[k])
        plt.axhline(y = avg_pix, color = color_avg_curve[k])
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k])
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k])

        plt.xlabel('Valeur du pixel clair')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+' = 0')
        if(inverse):
            plt.title('Courbe de la moyenne des chiffrés inverse !E(x), par paillier, modulo '+str(mod)+' = 0 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
        else:
            plt.title('Courbe de la moyenne des chiffrés, par paillier, modulo '+str(mod)+' = 0 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
        plt.grid()
        plt.legend()
        plt.show()

#En fonction de la valeur du pixel clair différents modulod
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



def main() :

############### Initialisation, récupération des données.
    f_pix = open("results_pix_p3q83nbR164.txt", "r")
    p = 3
    q = 83
    # f_pix = open("results_pix_p13q19nbr216.txt", "r")
    # p = 13
    # q = 19


    lines_pix = f_pix.readlines()

    t_pix_avg = []
    count_pix = []

    n = int(lines_pix[0]) 
    size_vec_r = int(lines_pix[1])


    vector_r_values = []
    t_pix_enc = []

    line_index = 2 
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

############### Courbes

    # Pixels chiffrés
    # avg_curve_mod_2_by_pixel_value(t_pix_enc, vector_r_values,n,size_vec_r, 'Courbe de la moyenne des chiffrés, par paillier, modulo 2 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    # avg_curve_mod_4_by_pixel_value(t_pix_enc, vector_r_values,n, size_vec_r, 'Courbe de la moyenne des chiffrés, par paillier, modulo 4 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    # avg_curve_mod_k_by_r_value(t_pix_enc, vector_r_values,n, size_vec_r, p ,q)
    # avg_curve_mod_k_by_pixel_value(t_pix_enc, vector_r_values, n, size_vec_r, p, q, False)


    # Pixels chiffrés inversés.
    t_pix_enc_inv= []
    for i in range(size_vec_r):
        t_pix_enc_inv_row= []
        for j in range(n):
            x = np.invert(np.array(t_pix_enc[i][j], dtype=np.uint16))
            t_pix_enc_inv_row.append(x)
            print("!" + str(t_pix_enc[i][j]) + " = " + str(np.binary_repr(t_pix_enc[i][j], width=16)) + "=" + str(np.binary_repr(x, width=16)))

        t_pix_enc_inv.append(t_pix_enc_inv_row)

    avg_curve_mod_2_by_pixel_value(t_pix_enc_inv, vector_r_values,n,size_vec_r, 'Courbe de la moyenne des chiffrés inversés (!E(x)), par paillier, modulo 2 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_4_by_pixel_value(t_pix_enc_inv, vector_r_values,n, size_vec_r, 'Courbe de la moyenne des chiffrés inversés (!E(x)), par paillier, modulo 4 en fonction de la valeur du pixel, pour p = '+str(p)+' et q = '+str(q)+'.')
    avg_curve_mod_k_by_pixel_value(t_pix_enc_inv, vector_r_values, n, size_vec_r, p, q, True)
    # avg_curve_mod_k_by_r_value_inv(t_pix_enc_inv, vector_r_values,n, size_vec_r, p, q)

if __name__ == "__main__":
    main()
