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

    modes_op_aes = ["ECB","CBC","CTR","CFB","OFB"]

    npcr_modes = []

    with open("NPCR_results.bin","rb") as f:
        npcr_modes = pickle.load(f)

    for i in range(0,len(npcr_modes)):
            
        x = np.arange(0, len(npcr_modes[i])) 
        y = npcr_modes[i]

        plt.plot(x, y,label=modes_op_aes[i])

    plt.xlabel('Images')
    plt.ylabel('NPCR')
    plt.title('Courbes du NPCR d\'images chiffrées par chiffrement AES en différents modes d\'opération')
    plt.grid()
    plt.legend()
    plt.show()




if __name__ == "__main__":
    main()
