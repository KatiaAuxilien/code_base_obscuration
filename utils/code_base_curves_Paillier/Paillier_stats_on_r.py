
import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle

def main() :
    f_pix = open("results_pix.txt", "r")
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


    # Print the values
    for r_value, row in zip(vector_r_values, t_pix_enc):
        if r_value == 2 :
            print(f"r_value: {r_value}")
            print(f"t_pix_enc: {row}")

    t_k = [2,4,8,16,32,64,128,256]
    color_main_curve = ["deepskyblue","royalblue"]
    color_avg_curve = ["turquoise","midnightblue"]
    color_ecart_type_curve = ["dodgerblue","darkblue"]

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

        plt.plot(x, y,label="average pixel encrypted modulo "+str(mod)+"",color=color_main_curve[k])
        plt.axhline(y = avg_pix, color = color_avg_curve[k])
        plt.axhline(y = avg_pix + ecart_type_pix /2, color = color_ecart_type_curve[k])
        plt.axhline(y = avg_pix - ecart_type_pix /2, color = color_ecart_type_curve[k])

        plt.xlabel('Valeur de r')
        plt.ylabel('Moyenne des chiffrés modulo '+str(mod)+'')
        plt.title('Courbe de la moyenne des chiffrés, par paillier, modulo '+str(mod)+' en fonction de r, pour p = 13 et q = 19.')
        plt.grid()
        plt.legend()
        plt.show()

    # ########## BARRES ##########    

    # plt.bar(x, y, color="deepskyblue")
    # plt.xlabel('...')
    # plt.ylabel('..')
    # plt.title('...')

    # plt.show()


if __name__ == "__main__":
    main()
