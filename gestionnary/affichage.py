import pygame as pg
import chess as c

pg.init()


size = (1300, 700)
mid = (size[0]//2, size[1]//2)
squareSize = (min(size[0], size[1])-200)//8
squareColor = {
    0:(26,26,26),
    1:(229,229,229)
}
pieces_images = {
    "P": pg.image.load("P.png"),
    "p": pg.image.load("p.png"),
    "N": pg.image.load("N.png"),
    "n": pg.image.load("n.png"),
    "B": pg.image.load("B.png"),
    "b": pg.image.load("b.png"),
    "R": pg.image.load("R.png"),
    "r": pg.image.load("r.png"),
    "Q": pg.image.load("Q.png"),
    "q": pg.image.load("q.png"),
    "K": pg.image.load("K.png"),
    "k": pg.image.load("k.png"),
}


def main():
    display = pg.display.set_mode(size)
    clock = pg.time.Clock()
    
    board = c.Board()
    
    running = True
    while running:
        clock.tick(100)
        
        running = eventGestionnary(pg.event.get())
        
        affichage(display, board)
        pg.display.flip()
    pg.quit()

def eventGestionnary(events:list[pg.event.Event]):
    for e in events:
        if e.type == pg.QUIT:
            return False
    return True

import pygame as pg

# Dictionnaire associant chaque caractère FEN à son image


def affichage(screen: pg.Surface, board: c.Board):
    fen = board.fen().split(" ")[0]
    pg.draw.rect(screen, (13, 13, 13), pg.Rect(0, 0, size[0], size[1]))

    for i in range(-4, 4):
        for j in range(3, -5, -1):
            pg.draw.rect(screen, squareColor[(i + j) % 2], pg.Rect(mid[0] + i * squareSize, mid[1] + j * squareSize, squareSize, squareSize))

    ranks = fen.split("/")
    for rank_index, rank in enumerate(ranks):
        file_index = 0
        for char in rank:
            if char.isdigit():
                file_index += int(char)
            else:
                if char in pieces_images:
                    piece_img = pg.transform.scale(pieces_images[char], (squareSize, squareSize))
                    x = mid[0] + (file_index - 4) * squareSize
                    y = mid[1] + (3 - rank_index) * squareSize
                    screen.blit(piece_img, (x, y))
                file_index += 1

    
    

if __name__ == "__main__":
    main()


