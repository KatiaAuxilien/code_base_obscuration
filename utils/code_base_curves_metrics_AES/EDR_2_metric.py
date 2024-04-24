import numpy as np
import matplotlib.pyplot as plt
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

    modes_op_aes = ["CFB","CFB_div"]

    edr_modes = []

    file_tab_alt = []
    dossier_images = modes_op_aes[0]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[0]

    edr = get_EDR_for_images_and_origins_gray(cv_img_original,cv_img_alt,cle)
    edr_modes.append(edr)


    file_tab_alt = []
    dossier_images = modes_op_aes[1]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt_2 = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[1]

    edr = get_EDR_for_images_and_origins_gray(cv_img_alt,cv_img_alt_2,cle)
    edr_modes.append(edr)

    with open("EDR_2_results.bin","wb") as f:
        pickle.dump(edr_modes,f)
    



if __name__ == "__main__":
    main()
