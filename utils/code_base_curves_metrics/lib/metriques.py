import os
import numpy as np
import cv2
from skimage.metrics import structural_similarity as ssim
import tqdm
# Calculs des métriques (et fonctions nécessaires à ceux-ci)

##
# @brief This function calculates the Number of Pixels Change Rate (NPCR) between two images.
# @param image1 The first image.
# @param image2 The second image.
# @return The NPCR value.
# @author Norman Hutte
# @date 2024
#
def calculate_NPCR(image1, image2):
    if image1.shape != image2.shape:
        raise ValueError("Erreur ! Tailles des images différentes !")
    sum = 0
    nb_pixels = image1.shape[0] * image1.shape[1]
    for i in range(image1.shape[0]):
        for j in range(image1.shape[1]):
            if np.all(image1[i][j] != image2[i][j]):
                sum += 1
    ratio = sum / nb_pixels
    npcr = ratio * 100
    return npcr

# def calculate_UACI(image1, image2):
#     if image1.shape != image2.shape:
#         raise ValueError("Erreur ! Tailles des images différentes !")
#     sum = 0
#     nb_pixels = image1.shape[0] * image1.shape[1]
#     for i in range(image1.shape[0]):
#         for j in range(image1.shape[1]):
#             sum += (image1[i][j] - image2[i][j]) / 255.0
#     ratio = sum / nb_pixels
#     ratio = np.mean(ratio)
#     uaci = ratio * 100
#     return uaci

##
# @brief This function calculates the Unified Average Changing Intensity (UACI) between two images.
# @param image1 The first image.
# @param image2 The second image.
# @return The UACI value.
# @author Norman Hutte
# @date 2024
#
def calculate_UACI(image1, image2):
    if image1.shape != image2.shape:
        raise ValueError("Erreur ! Tailles des images différentes !")
    sum = 0
    for i in range(image1.shape[0]):
        for j in range(image1.shape[1]):
            sum += (abs(int(image1[i][j]) - int(image2[i][j]))) 
    uaci = sum * 100 / (image1.shape[0] * image1.shape[1] * 255)
    return uaci

##
# @brief This function extracts the edges from an RGB image.
# @param image The input image.
# @return The edge map of the image.
# @author Norman Hutte
# @date 2024
#
def extract_edges_rgb(image):
    image_Y = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    med_val = np.median(image_Y)
    lower = int(max(0 , 0.2*med_val))
    upper = int(min(255, 0.5*med_val))
    edges = cv2.Canny(image_Y, lower, upper)
    return edges

##
# @brief This function converts an edge map to a binary map.
# @param edges The edge map.
# @return The binary map.
# @author Norman Hutte
# @date 2024
#
def get_binary_map(edges):
    map = np.zeros(edges.shape[:2])
    for i in range(edges.shape[0]):
        for j in range(edges.shape[1]):
            if edges[i][j] == 255:
                map[i][j] = 1
    return map

##
# @brief This function calculates the Edge Detection Ratio (EDR) between two RGB images.
# @param image The first image.
# @param alt_image The second image.
# @return The EDR value.
# @author Norman Hutte
# @date 2024
#
def calculate_EDR_rgb(image, alt_image):
    if image.shape != alt_image.shape:
        raise ValueError("Les images n'ont pas la même taille !")
    edges = get_binary_map(extract_edges_rgb(image))
    alt_edges = get_binary_map(extract_edges_rgb(alt_image))
    height, width, _ = image.shape
    sum = 0
    diff = 0
    for i in range(height):
        for j in range(width):
            diff += abs(edges[i][j] - alt_edges[i][j])
            sum += abs(edges[i][j] + alt_edges[i][j])
    return float(diff)/float(height*width)

##
# @brief This function extracts the edges from a grayscale image.
# @param image_Y The input grayscale image.
# @return The edge map of the image.
# @author Norman Hutte
# @date 2024
#
def extract_edges_gray(image_Y):
    med_val = np.median(image_Y)
    lower = int(max(0 , 0.2*med_val))
    upper = int(min(255, 0.5*med_val))
    edges = cv2.Canny(image_Y, lower, upper)
    return edges

##
# @brief This function calculates the Edge Detection Ratio (EDR) between two grayscale images.
# @param image The first grayscale image.
# @param alt_image The second grayscale image.
# @return The EDR value.
# @author Norman Hutte
# @date 2024
#
def calculate_EDR_gray(image, alt_image):
    if image.shape != alt_image.shape:
        raise ValueError("Les images n'ont pas la même taille !")
    edges = get_binary_map(extract_edges_gray(image))
    alt_edges = get_binary_map(extract_edges_gray(alt_image))
    height, width = image.shape
    sum = 0
    diff = 0
    for i in range(height):
        for j in range(width):
            diff += abs(edges[i][j] - alt_edges[i][j])
            sum += abs(edges[i][j] + alt_edges[i][j])
    return float(diff)/float(height*width)

##
# @brief This function calculates the entropy of an RGB image.
# @param image The input RGB image.
# @return The entropy value.
# @author Norman Hutte
# @date 2024
#
def calculate_entropy_rgb(image):
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    hist, _ = np.histogram(gray_image.flatten(), bins=256, range=(0,256))
    norm_hist = hist / float(gray_image.shape[0]*gray_image.shape[1])
    entropy = -np.sum(norm_hist * np.log2(norm_hist + 1e-10))
    return entropy
##
# @brief This function calculates the entropy of a grayscale image.
# @param gray_image The input grayscale image.
# @return The entropy value.
# @author Norman Hutte
# @date 2024
#
def calculate_entropy_gray(gray_image):
    hist, _ = np.histogram(gray_image.flatten(), bins=256, range=(0,256))
    norm_hist = hist / float(gray_image.shape[0]*gray_image.shape[1])
    entropy = -np.sum(norm_hist * np.log2(norm_hist + 1e-10))
    return entropy


##
# @brief This function calculates the Peak Signal-to-Noise Ratio (PSNR) for a set of images.
# @param init_image The initial image.
# @param alt_images The set of altered images.
# @return The PSNR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_PSNR_for_images(init_image, alt_images):
    PSNRs = []
    for alt_img in alt_images:
        img_PSNR = cv2.PSNR(init_image, alt_img)
        PSNRs.append(img_PSNR)
    return PSNRs

##
# @brief This function calculates the Peak Signal-to-Noise Ratio (PSNR) for a set of images and their origins.
# @param init_images The initial set of images.
# @param alt_images The set of altered images.
# @param mode The mode of calculation.
# @return The PSNR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_PSNR_for_images_and_origins(init_images, alt_images, mode):
    PSNRs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc = "Calculs PSNR "+mode):
        img_PSNR = cv2.PSNR(init_images[i], alt_images[i])
        PSNRs.append(img_PSNR)
    return PSNRs

##
# @brief This function calculates the Structural Similarity Index Measure (SSIM) for a set of RGB images.
# @param init_image The initial RGB image.
# @param alt_images The set of altered RGB images.
# @return The SSIM values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_SSIM_for_images_rgb(init_image, alt_images):
    SSIMs = []
    gray_base_image = cv2.cvtColor(init_image, cv2.COLOR_BGR2GRAY)
    for alt_img in alt_images:
        gray_alt_image = cv2.cvtColor(alt_img, cv2.COLOR_BGR2GRAY)
        img_SSIM, _ = ssim(gray_base_image, gray_alt_image, full=True)
        SSIMs.append(img_SSIM)
    return SSIMs

##
# @brief This function calculates the Structural Similarity Index Measure (SSIM) for a set of grayscale images.
# @param gray_base_image The initial grayscale image.
# @param alt_images The set of altered grayscale images.
# @return The SSIM values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_SSIM_for_images_gray(gray_base_image, alt_images):
    SSIMs = []
    for gray_alt_image in alt_images:
        img_SSIM, _ = ssim(gray_base_image, gray_alt_image, full=True)
        SSIMs.append(img_SSIM)
    return SSIMs

##
# @brief This function calculates the Structural Similarity Index Measure (SSIM) for a set of grayscale images and their origins.
# @param gray_base_images The initial set of grayscale images.
# @param alt_images The set of altered grayscale images.
# @param mode The mode of calculation.
# @return The SSIM values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_SSIM_for_images_and_origins_gray(gray_base_images, alt_images,mode):
    SSIMs = []
    for i in tqdm.tqdm(range(0,len(gray_base_images)), desc = "Calculs SSIM "+mode):
        img_SSIM, _ = ssim(gray_base_images[i], alt_images[i], full=True)
        SSIMs.append(img_SSIM)
    return SSIMs

##
# @brief This function calculates the Number of Pixels Change Rate (NPCR) for a set of images.
# @param init_image The initial image.
# @param alt_images The set of altered images.
# @return The NPCR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_NPCR_for_images(init_image, alt_images):
    NPCRs = []
    for alt_img in alt_images:
        img_NPCR = calculate_NPCR(init_image, alt_img)
        NPCRs.append(img_NPCR)
    return NPCRs

##
# @brief This function calculates the Number of Pixels Change Rate (NPCR) for a set of images and their origins.
# @param init_images The initial set of images.
# @param alt_images The set of altered images.
# @param mode The mode of calculation.
# @return The NPCR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_NPCR_for_images_and_origins(init_images, alt_images, mode):
    NPCRs = []
    for i in tqdm.tqdm(range(0,len(init_images)),desc = "Calculs NPCR "+mode):
        img_NPCR = calculate_NPCR(init_images[i], alt_images[i])
        NPCRs.append(img_NPCR)
    return NPCRs

##
# @brief This function calculates the Unified Average Changing Intensity (UACI) for a set of images.
# @param init_image The initial image.
# @param alt_images The set of altered images.
# @return The UACI values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_UACI_for_images(init_image, alt_images):
    UACIs = []
    for alt_img in alt_images:
        img_UACI = calculate_UACI(init_image, alt_img)
        UACIs.append(img_UACI)
    return UACIs

##
# @brief This function calculates the Unified Average Changing Intensity (UACI) for a set of images and their origins.
# @param init_images The initial set of images.
# @param alt_images The set of altered images.
# @param mode The mode of calculation.
# @return The UACI values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_UACI_for_images_and_origins(init_images, alt_images,mode):
    UACIs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc="Calculs UACI "+mode):
        img_UACI = calculate_UACI(init_images[i], alt_images[i])
        UACIs.append(img_UACI)
    return UACIs

##
# @brief This function calculates the Edge Detection Ratio (EDR) for a set of RGB images.
# @param init_image The initial RGB image.
# @param alt_images The set of altered RGB images.
# @return The EDR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_EDR_for_images_rgb(init_image, alt_images):
    EDRs = []
    for alt_img in alt_images:
        img_EDR = calculate_EDR_rgb(init_image, alt_img)
        EDRs.append(img_EDR)
    return EDRs

##
# @brief This function calculates the Edge Detection Ratio (EDR) for a set of grayscale images.
# @param init_image The initial grayscale image.
# @param alt_images The set of altered grayscale images.
# @return The EDR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_EDR_for_images_gray(init_image, alt_images):
    EDRs = []
    for alt_img in alt_images:
        img_EDR = calculate_EDR_gray(init_image, alt_img)
        EDRs.append(img_EDR)
    return EDRs

##
# @brief This function calculates the Edge Detection Ratio (EDR) for a set of grayscale images and their origins.
# @param init_images The initial set of grayscale images.
# @param alt_images The set of altered grayscale images.
# @param mode The mode of calculation.
# @return The EDR values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_EDR_for_images_and_origins_gray(init_images, alt_images,mode):
    EDRs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc = "Calculs EDR "+mode):
        img_EDR = calculate_EDR_gray(init_images[i], alt_images[i])
        EDRs.append(img_EDR)
    return EDRs

##
# @brief This function calculates the entropy for a set of RGB images.
# @param alt_images The set of altered RGB images.
# @return The entropy values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_entropy_for_images_rgb(alt_images):
    entropies = []
    for alt_img in alt_images:
        img_entropy = calculate_entropy_rgb(alt_img)
        entropies.append(img_entropy)
    return entropies

##
# @brief This function calculates the entropy for a set of grayscale images.
# @param alt_images The set of altered grayscale images.
# @param mode The mode of calculation.
# @return The entropy values for each altered image.
# @author Norman Hutte
# @date 2024
#
def get_entropy_for_images_gray(alt_images,mode):
    entropies = []
    for alt_img in tqdm.tqdm(alt_images, desc = "Calculs entropy "+mode):
        img_entropy = calculate_entropy_gray(alt_img)
        entropies.append(img_entropy)
    return entropies