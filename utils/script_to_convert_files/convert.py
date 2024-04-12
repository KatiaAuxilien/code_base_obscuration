from PIL import Image
import sys

def convert_image(input_image_path, output_image_path):
    try:
        # Ouvre l'image avec PIL
        image = Image.open(input_image_path)

        # Enregistre l'image avec le format spécifié
        image.save(output_image_path)
        print(f"L'image a été convertie avec succès en format : {output_image_path}")
    
    except Exception as e:
        print(f"Erreur lors de la conversion de l'image : {e}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Utilisation: python convert_image.py <chemin_vers_image> <format_entree> <format_sortie>")
        print("Formats disponibles : jpg, jpeg, png, pgm, ppm")
        sys.exit(1)

    input_image_path = sys.argv[1]
    input_format = sys.argv[2].lower()
    output_format = sys.argv[3].lower()

    output_image_path = input_image_path.rsplit('.', 1)[0] + '.' + output_format

    if input_format not in ['jpg', 'jpeg', 'png', 'pgm', 'ppm'] or output_format not in ['jpg', 'jpeg', 'png', 'pgm', 'ppm']:
        print("Formats invalides. Formats disponibles : jpg, jpeg, png, pgm, ppm")
        sys.exit(1)

    convert_image(input_image_path, output_image_path)
