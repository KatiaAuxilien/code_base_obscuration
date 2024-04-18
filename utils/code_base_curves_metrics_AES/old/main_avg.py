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
    psnr_avg_modes = []
    entropy_avg_modes = []
    ssim_avg_modes = []
    npcr_avg_modes = []
    uaci_avg_modes = []

    for mode in modes_op_aes:
        file_tab_alt = []
        dossier_images = mode
        for fichier in os.listdir(dossier_images):
            if fichier.endswith(".pgm") :
                file_tab_alt.append(dossier_images+"\\"+fichier)
                
        cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]

        cle = mode

        psnr = get_PSNR_for_images_and_origins(cv_img_original,cv_img_alt)
        sum = 0
        for i in range(len(psnr)):
            sum += psnr[i]
        psnr_avg = sum / len(psnr)
        results = {cle : psnr_avg}
        psnr_avg_modes.append(results)

        entropy = get_entropy_for_images_gray(cv_img_alt)
        sum = 0
        for i in range(len(entropy)):
            sum += entropy[i]
        entropy_avg = sum / len(entropy)
        results = {cle :entropy_avg}
        entropy_avg_modes.append(results)
        #Ajouter l'entropy d'origine ??? pour une comparaison éventuelle ?

        ssim = get_SSIM_for_images_and_origins_gray(cv_img_original,cv_img_alt)
        sum = 0
        for i in range(len(ssim)):
            sum += ssim[i]
        ssim_avg = sum / len(ssim)
        results = {cle : ssim_avg}
        ssim_avg_modes.append(results)

        npcr = get_NPCR_for_images_and_origins(cv_img_original,cv_img_alt)
        sum = 0
        for i in range(len(npcr)):
            sum += npcr[i]
        npcr_avg = sum / len(npcr)
        results = {cle : npcr_avg}
        npcr_avg_modes.append(results)
        
        uaci = get_UACI_for_images_and_origins(cv_img_original,cv_img_alt)
        sum = 0
        for i in range(len(uaci)):
            sum += uaci[i]
        uaci_avg = sum / len(uaci)
        results = {cle : uaci_avg}
        uaci_avg_modes.append(results)

    print("PSNR")
    for i in psnr_avg_modes:
        print(i)

    print("Entropy")
    for i in entropy_avg_modes:
        print(i)
    
    print("SSIM")
    for i in ssim_avg_modes:
        print(i)
    
    print("NPCR")
    for i in npcr_avg_modes:
        print(i)

    print("UACI")
    for i in uaci_avg_modes:
        print(i)


if __name__ == "__main__":
    main()
