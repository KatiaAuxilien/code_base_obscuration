from PIL import Image

def compare_images(image1_path, image2_path):
    image1 = Image.open(image1_path)
    image2 = Image.open(image2_path)

    width, height = image1.size

    if image2.size != (width, height):
        print("The images have different dimensions.")
        return

    different_pixels = False
    for y in range(height):
        for x in range(width):
            pixel1 = image1.getpixel((x, y))
            pixel2 = image2.getpixel((x, y))

            if pixel1 != pixel2:
                different_pixels = True
                break

        if different_pixels:
            break

    if different_pixels:
        print("The images are not identical.")
    else:
        print("The images are identical.")

compare_images('img_CFB_0.pgm', 'img_CFB_div_0.pgm')