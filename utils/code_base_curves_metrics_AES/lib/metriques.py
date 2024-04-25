import os
import numpy as np
import cv2
from skimage.metrics import structural_similarity as ssim
import tqdm
# Calculs des métriques (et fonctions nécessaires à ceux-ci)

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


def calculate_UACI(image1, image2):
    if image1.shape != image2.shape:
        raise ValueError("Erreur ! Tailles des images différentes !")
    sum = 0
    for i in range(image1.shape[0]):
        for j in range(image1.shape[1]):
            sum += (abs(int(image1[i][j]) - int(image2[i][j]))) 
    uaci = sum * 100 / (image1.shape[0] * image1.shape[1] * 255)
    return uaci


def extract_edges_rgb(image):
    image_Y = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    med_val = np.median(image_Y)
    lower = int(max(0 , 0.2*med_val))
    upper = int(min(255, 0.5*med_val))
    edges = cv2.Canny(image_Y, lower, upper)
    return edges

def get_binary_map(edges):
    map = np.zeros(edges.shape[:2])
    for i in range(edges.shape[0]):
        for j in range(edges.shape[1]):
            if edges[i][j] == 255:
                map[i][j] = 1
    return map

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

def extract_edges_gray(image_Y):
    med_val = np.median(image_Y)
    lower = int(max(0 , 0.2*med_val))
    upper = int(min(255, 0.5*med_val))
    edges = cv2.Canny(image_Y, lower, upper)
    return edges


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


def calculate_entropy_rgb(image):
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    hist, _ = np.histogram(gray_image.flatten(), bins=256, range=(0,256))
    norm_hist = hist / float(gray_image.shape[0]*gray_image.shape[1])
    entropy = -np.sum(norm_hist * np.log2(norm_hist + 1e-10))
    return entropy

def calculate_entropy_gray(gray_image):
    hist, _ = np.histogram(gray_image.flatten(), bins=256, range=(0,256))
    norm_hist = hist / float(gray_image.shape[0]*gray_image.shape[1])
    entropy = -np.sum(norm_hist * np.log2(norm_hist + 1e-10))
    return entropy


# Calcul de l'ensemble des métriques pour un ensemble d'images donné

def get_PSNR_for_images(init_image, alt_images):
    PSNRs = []
    for alt_img in alt_images:
        img_PSNR = cv2.PSNR(init_image, alt_img)
        PSNRs.append(img_PSNR)
    return PSNRs

def get_PSNR_for_images_and_origins(init_images, alt_images, mode):
    PSNRs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc = "Calculs PSNR "+mode):
        img_PSNR = cv2.PSNR(init_images[i], alt_images[i])
        PSNRs.append(img_PSNR)
    return PSNRs


def get_SSIM_for_images_rgb(init_image, alt_images):
    SSIMs = []
    gray_base_image = cv2.cvtColor(init_image, cv2.COLOR_BGR2GRAY)
    for alt_img in alt_images:
        gray_alt_image = cv2.cvtColor(alt_img, cv2.COLOR_BGR2GRAY)
        img_SSIM, _ = ssim(gray_base_image, gray_alt_image, full=True)
        SSIMs.append(img_SSIM)
    return SSIMs

def get_SSIM_for_images_gray(gray_base_image, alt_images):
    SSIMs = []
    for gray_alt_image in alt_images:
        img_SSIM, _ = ssim(gray_base_image, gray_alt_image, full=True)
        SSIMs.append(img_SSIM)
    return SSIMs


def get_SSIM_for_images_and_origins_gray(gray_base_images, alt_images,mode):
    SSIMs = []
    for i in tqdm.tqdm(range(0,len(gray_base_images)), desc = "Calculs SSIM "+mode):
        img_SSIM, _ = ssim(gray_base_images[i], alt_images[i], full=True)
        SSIMs.append(img_SSIM)
    return SSIMs

def get_NPCR_for_images(init_image, alt_images):
    NPCRs = []
    for alt_img in alt_images:
        img_NPCR = calculate_NPCR(init_image, alt_img)
        NPCRs.append(img_NPCR)
    return NPCRs

def get_NPCR_for_images_and_origins(init_images, alt_images, mode):
    NPCRs = []
    for i in tqdm.tqdm(range(0,len(init_images)),desc = "Calculs NPCR "+mode):
        img_NPCR = calculate_NPCR(init_images[i], alt_images[i])
        NPCRs.append(img_NPCR)
    return NPCRs


def get_UACI_for_images(init_image, alt_images):
    UACIs = []
    for alt_img in alt_images:
        img_UACI = calculate_UACI(init_image, alt_img)
        UACIs.append(img_UACI)
    return UACIs

def get_UACI_for_images_and_origins(init_images, alt_images,mode):
    UACIs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc="Calculs UACI "+mode):
        img_UACI = calculate_UACI(init_images[i], alt_images[i])
        UACIs.append(img_UACI)
    return UACIs

def get_EDR_for_images_rgb(init_image, alt_images):
    EDRs = []
    for alt_img in alt_images:
        img_EDR = calculate_EDR_rgb(init_image, alt_img)
        EDRs.append(img_EDR)
    return EDRs

def get_EDR_for_images_gray(init_image, alt_images):
    EDRs = []
    for alt_img in alt_images:
        img_EDR = calculate_EDR_gray(init_image, alt_img)
        EDRs.append(img_EDR)
    return EDRs


def get_EDR_for_images_and_origins_gray(init_images, alt_images,mode):
    EDRs = []
    for i in tqdm.tqdm(range(0,len(init_images)), desc = "Calculs EDR "+mode):
        img_EDR = calculate_EDR_gray(init_images[i], alt_images[i])
        EDRs.append(img_EDR)
    return EDRs


def get_entropy_for_images_rgb(alt_images):
    entropies = []
    for alt_img in alt_images:
        img_entropy = calculate_entropy_rgb(alt_img)
        entropies.append(img_entropy)
    return entropies

def get_entropy_for_images_gray(alt_images,mode):
    entropies = []
    for alt_img in tqdm.tqdm(alt_images, desc = "Calculs entropy "+mode):
        img_entropy = calculate_entropy_gray(alt_img)
        entropies.append(img_entropy)
    return entropies