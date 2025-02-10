"""Découpage des pieces par chat-gpt (un peu retraivaillé pour fonctionner)"""
from PIL import Image

# Charger l'image
image_path = "./assets/Pieces.png"  # Remplace par le chemin de ton image
img = Image.open(image_path)

# Dimensions de l'image
img_width, img_height = img.size

# Nombre de pièces par ligne
num_pieces = 6  # kqbnrp

# Calcul de la taille d'une pièce
piece_width = img_width // num_pieces
piece_height = img_height // 2  # 2 lignes : blancs en haut, noirs en bas
print(piece_width)
print(piece_height)

# Noms des pièces en notation échiquéenne
notation = ["k", "q", "b", "n", "r", "p"]

# Extraire et sauvegarder chaque pièce
for i in range(num_pieces):
    # Coordonnées pour la pièce blanche (ligne du haut)
    left = i * piece_width
    right = (i + 1) * piece_width
    top_white = 0
    bottom_white = piece_height

    # Coordonnées pour la pièce noire (ligne du bas)
    top_black = piece_height
    bottom_black = img_height

    white_piece = img.crop((left, top_white, right, bottom_white))
    black_piece = img.crop((left, top_black, right, bottom_black))
    
    white_piece.save(f"./assets/{notation[i]}w.png")  # Majuscule pour blanc
    black_piece.save(f"./assets/{notation[i]}b.png")  # Minuscule pour noir

print("Découpage terminé !")

