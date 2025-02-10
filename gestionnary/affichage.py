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
boardPos = (mid[0]-4*squareSize, mid[1]-4*squareSize)

pieces_images = {
    "P": pg.image.load("./assets/pw.png"),
    "p": pg.image.load("./assets/pb.png"),
    "N": pg.image.load("./assets/nw.png"),
    "n": pg.image.load("./assets/nb.png"),
    "B": pg.image.load("./assets/bw.png"),
    "b": pg.image.load("./assets/bb.png"),
    "R": pg.image.load("./assets/rw.png"),
    "r": pg.image.load("./assets/rb.png"),
    "Q": pg.image.load("./assets/qw.png"),
    "q": pg.image.load("./assets/qb.png"),
    "K": pg.image.load("./assets/kw.png"),
    "k": pg.image.load("./assets/kb.png"),
}


def main():
    display = pg.display.set_mode(size)
    clock = pg.time.Clock()
    
    board = c.Board()
    
    running = True
    while running:
        clock.tick(100)
        
        for e in pg.event.get():
            if e.type == pg.QUIT:
                running = False
            if e.type == pg.MOUSEBUTTONDOWN:
                if e.button == 1:
                    mouse_x, mouse_y = e.pos
                    file = (mouse_x - boardPos[0]) // squareSize
                    rank = 7 - (mouse_y - boardPos[1]) // squareSize
                    if 0<=file<=7 and 0<=rank<=7:
                        pass
        
        affichage(display, board)
        pg.display.flip()
    pg.quit()



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


