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

    psnr_modes = []

    file_tab_alt = []
    dossier_images = "..\\..\\..\\main\\obscuredPGM\\encryption\\AES\\"+modes_op_aes[0]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[0]

    psnr = get_PSNR_for_images_and_origins(cv_img_original,cv_img_alt,cle)
    psnr_modes.append(psnr)

    file_tab_alt = []
    dossier_images = "..\\..\\..\\main\\obscuredPGM\\encryption\\AES\\"+modes_op_aes[1]
    for fichier in os.listdir(dossier_images):
        if fichier.endswith(".pgm") :
            file_tab_alt.append(dossier_images+"\\"+fichier)
            
    cv_img_alt_2 = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

    cle = modes_op_aes[1]

    psnr = get_PSNR_for_images_and_origins(cv_img_alt,cv_img_alt_2,cle)
    psnr_modes.append(psnr)

    with open("PSNR_2_results.bin","wb") as f:
        pickle.dump(psnr_modes,f)


if __name__ == "__main__":
    main()
