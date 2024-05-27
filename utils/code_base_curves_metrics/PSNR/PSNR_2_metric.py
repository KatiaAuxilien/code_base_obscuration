import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    # fichier = "4754.pgm"
    # dossier_images = "origin\\"
    # file_tab_alt = dossier_images+"\\"+fichier
    # cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # fichier = "4754_E_D(3 et 89 sans recrop avec distri 2px).pgm"
    # dossier_images = "img\\"
    # file_tab_alt = dossier_images+"\\"+fichier

    # cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # psnr = cv2.PSNR(cv_img_original,cv_img_alt)


    # # with open("PSNR_results.bin","wb") as f:
    # #     pickle.dump(psnr,f)

    # print(fichier+" : "+ str(psnr))

    # fichier = "4754.pgm"
    # dossier_images = "origin\\"
    # file_tab_alt = dossier_images+"\\"+fichier
    # cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # fichier = "4754_E_D(13 et 19 recrop distribution 2 px (247)).pgm"
    # dossier_images = "img\\"
    # file_tab_alt = dossier_images+"\\"+fichier

    # cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    # print(fichier+" : "+ str(psnr))

    
    # fichier = "4754.pgm"
    # dossier_images = "origin\\"
    # file_tab_alt = dossier_images+"\\"+fichier
    # cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # fichier = "4754_E_D(13 et 19 sans recrop distri 2px (247)).pgm"
    # dossier_images = "img\\"
    # file_tab_alt = dossier_images+"\\"+fichier

    # cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    # print(fichier+" : "+ str(psnr))


    # fichier = "4754.pgm"
    # dossier_images = "origin\\"
    # file_tab_alt = dossier_images+"\\"+fichier
    # cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # fichier = "4754_E_D(13 et 19 sans recrop sans distribution 2 pix (247)).pgm"
    # dossier_images = "img\\"
    # file_tab_alt = dossier_images+"\\"+fichier

    # cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    # print(fichier+" : "+ str(psnr))


    # fichier = "4754.pgm"
    # dossier_images = "origin\\"
    # file_tab_alt = dossier_images+"\\"+fichier
    # cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # fichier = "4754_E_D(3 et 89 recrop distri 2px).pgm"
    # dossier_images = "img\\"
    # file_tab_alt = dossier_images+"\\"+fichier

    # cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    # print(fichier+" : "+ str(psnr))



    fichier = "4754.pgm"
    dossier_images = "origin\\"
    file_tab_alt = dossier_images+"\\"+fichier
    cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)
        
        # Essais
    fichier = "4754_E_13_19_vanilla.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))

    # 4754_E_D_13_19_vanilla
    # 4754_E_D_distr_13_19_
    # 4754_E_D_hexp_13_19_
    # 4754_E_D_distr_hexp_13_19_

    fichier = "4754_E_D_13_19_vanilla.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))

    fichier = "4754_E_D_distr_13_19_.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))

    fichier = "4754_E_D_hexp_13_19_.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))


    fichier = "4754_E_D_distr_hexp_13_19_.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))


    fichier = "6959.pgm"
    dossier_images = "origin\\"
    file_tab_alt = dossier_images+"\\"+fichier
    cv_img_original = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    # 6959_E_D_vanilla_3_83
    # 6959_E_D_distr_3_83
    # 6959_E_D_hexp_3_83
    # 6959_E_D_hexp_distr_3_83    

    fichier = "6959_E_D_vanilla_3_83.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))

    fichier = "6959_E_D_distr_3_83.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))


    fichier = "6959_E_D_hexp_3_83.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))


    fichier = "6959_E_D_hexp_distr_3_83.pgm"
    dossier_images = "img\\"
    file_tab_alt = dossier_images+"\\"+fichier

    cv_img_alt = cv2.imread(file_tab_alt, cv2.IMREAD_GRAYSCALE)

    psnr = cv2.PSNR(cv_img_original,cv_img_alt)
    print(fichier+" : "+ str(psnr))

if __name__ == "__main__":
    main()
