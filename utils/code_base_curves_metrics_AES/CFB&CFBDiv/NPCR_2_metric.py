import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    dossier_images = "..\\..\\..\\main\\img\\"
    file_tab_original = []
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_original.append(dossier_images+fichier)
            
    cv_img_original = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_original]

    modes_op_aes = ["CFB","CFB_dec_bad_key"]

    npcr_modes = []

    file_tab_alt = []
    dossier_images = modes_op_aes[0]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[0]

    npcr = get_NPCR_for_images_and_origins(cv_img_original,cv_img_alt,cle)
    npcr_modes.append(npcr)

    file_tab_alt = []
    dossier_images = modes_op_aes[1]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt_2 = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[1]

    npcr = get_NPCR_for_images_and_origins(cv_img_alt,cv_img_alt_2,cle)
    npcr_modes.append(npcr)

    with open("NPCR_2_results.bin","wb") as f :
        pickle.dump(npcr_modes,f)



if __name__ == "__main__":
    main()
