import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import sys
sys.path.append('../')

from lib.metriques import *

def main() :

    dossier_images = "origin\\"
    file_tab_original = []
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_original.append(dossier_images+fichier)
            
    cv_img_original = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_original]

    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]

    uaci_modes = []

    for i in range(len(modes_op_aes)):
        file_tab_alt = []
        dossier_images = modes_op_aes[i]
        for fichier in os.listdir(dossier_images):
            if fichier.endswith(".pgm") :
                file_tab_alt.append(dossier_images+"\\"+fichier)
                
        cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

        cle = modes_op_aes[i]

        uaci = get_UACI_for_images_and_origins(cv_img_original,cv_img_alt,cle)
        uaci_modes.append(uaci)


    # print("uaci")
    for i in range(0,len(uaci_modes)):
        # print(modes_op_aes[i])
        # for y in range(0,len(uaci_modes[i])):
        #     print(uaci_modes[i][y])
            
        x = np.arange(0, len(uaci_modes[i]))  # Indices des images
        y = uaci_modes[i]  # uaci pour le premier mode opératoire

        plt.plot(x, y,label=modes_op_aes[i])


    # plt.yticks(np.arange(5.0, 8.5 + 0.1, 0.1))
    # plt.xticks(np.arange(1, len(uaci_modes[0]), 1))
    plt.xlabel('Images')
    plt.ylabel('UACI')
    plt.title('Courbe du UACI d\'images chiffrées par chiffrement AES en différents modes d\'opération')

    plt.grid()
    plt.legend()
    plt.show()




if __name__ == "__main__":
    main()
