from math import log10, sqrt 
import cv2 
import numpy as np 

def PSNR(original, compressed): 
	mse = np.mean((original - compressed) ** 2) 
	if(mse == 0): # MSE is zero means no noise is present in the signal . 
				# Therefore PSNR have no importance. 
		return 100
	max_pixel = 255.0
	psnr = 20 * log10(max_pixel / sqrt(mse)) 
	return psnr 

def main(): 
    tab = ["AES_ECB.pgm","AES_CBC.pgm","AES_CTR.pgm","AES_CFB.pgm","AES_OFB.pgm"]
    original = cv2.imread("original.pgm", cv2.IMREAD_GRAYSCALE) 

    for l in tab:
        compressed = cv2.imread(l, cv2.IMREAD_GRAYSCALE)
        value = PSNR(original, compressed) 
        print(f"{l} : {value} dB") 
	
if __name__ == "__main__": 
	main() 
