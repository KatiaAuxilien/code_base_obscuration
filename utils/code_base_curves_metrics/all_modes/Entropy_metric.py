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

    dossier_images = "origin\\"
    file_tab_original = []
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_original.append(dossier_images+fichier)
            
    cv_img_original = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_original]

    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]

    # ######### MOYENNE ##########
    # entropy_avg_modes = []
    # entropy_ecart_type_modes = []

    # for mode in modes_op_aes:
    #     file_tab_alt = []
    #     dossier_images = mode
    #     for fichier in os.listdir(dossier_images):
    #         if fichier.endswith(".pgm") :
    #             file_tab_alt.append(dossier_images+"\\"+fichier)
                
    #     cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    #     cle = mode

    #     entropy = get_entropy_for_images_gray(cv_img_alt)
    #     sum = 0
    #     sum_pow = 0
    #     for i in range(len(entropy)):
    #         sum += entropy[i]
    #         sum_pow = pow(entropy[i],2)
    #     entropy_avg = sum / len(entropy)
    #     entropy_avg_pow = sum_pow / len(entropy)

    #     entropy_avg_modes.append(entropy_avg)

    #     var = entropy_avg_pow - pow(entropy_avg,2)
    #     o = math.sqrt(var)
    #     entropy_ecart_type_modes.append()



    entropy_modes = []
    for i in range(len(modes_op_aes)):
        file_tab_alt = []
        dossier_images = modes_op_aes[i]
        for fichier in os.listdir(dossier_images):
            if fichier.endswith(".pgm") :
                file_tab_alt.append(dossier_images+"\\"+fichier)
                
        cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

        cle = modes_op_aes[i]

        entropy = get_entropy_for_images_gray(cv_img_alt,cle)
        entropy_modes.append(entropy)

    with open("Entropy_results.bin","wb") as f:
        pickle.dump(entropy_modes,f)
 


if __name__ == "__main__":
    main()
