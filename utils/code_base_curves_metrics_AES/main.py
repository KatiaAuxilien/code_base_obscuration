import numpy as np
import matplotlib.pyplot as plt
import cv2
import sys
sys.path.append('../')  # ajoute le répertoire parent au chemin d'accès

from lib.metriques import *

def main() :
    file_img_original = "original.pgm"
    file_tab_alt = ["original.pgm","AES_ECB.pgm","AES_CBC.pgm","AES_CTR.pgm","AES_CFB.pgm","AES_OFB.pgm"]
    cv_img_original = cv2.imread(file_img_original, cv2.IMREAD_GRAYSCALE)
    cv_img_alt = [cv2.imread(img, cv2.IMREAD_GRAYSCALE) for img in file_tab_alt]


    print("PSNR")
    psnr = get_PSNR_for_images(cv_img_original,cv_img_alt)
    for i in range(len(psnr)):
        print(file_tab_alt[i] + " : " + str(psnr[i]))

    print("Entropy")
    entropy = get_entropy_for_images_gray(cv_img_alt)
    for i in range(len(entropy)):
        print(file_tab_alt[i] + " : " + str(entropy[i]))

    print("SSIM")
    ssim = get_SSIM_for_images_gray(cv_img_original,cv_img_alt)
    for i in range(len(ssim)):
        print(file_tab_alt[i] + " : " + str(ssim[i]))

    print("NPCR")
    npcr = get_NPCR_for_images(cv_img_original,cv_img_alt)
    for i in range(len(npcr)):
        print(file_tab_alt[i] + " : " + str(npcr[i]))


    print("UACI")
    uaci = get_UACI_for_images(cv_img_original,cv_img_alt)
    for i in range(len(uaci)):
        print(file_tab_alt[i] + " : " + str(uaci[i]))





if __name__ == "__main__":
    main()
