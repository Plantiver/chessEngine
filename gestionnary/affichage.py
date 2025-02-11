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
    
    pos0 = None
    pos1 = None
    move = None
    
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
                        if pos0 is None:
                            pos0 = c.parse_square(chr(97+file)+str(rank+1))
                            if not board.piece_at(pos0):
                                pos0 = None
                        else:
                            pos1 = c.parse_square(chr(97+file)+str(rank+1))
                            if c.Move(pos0, pos1) in board.legal_moves:
                                move = c.Move(pos0, pos1)
                                board.push(move)
                                pos0 = None
                                pos1 = None
                            else:
                                if board.piece_at(pos1):
                                    pos0 = pos1
                                pos1 = None
        
        affichage(display, board, move, pos0)
        pg.display.flip()
    pg.quit()



def affichage(screen: pg.Surface, board: c.Board, move:c.Move, selectionned:c.Square):
    fen = board.fen().split(" ")[0]
    pg.draw.rect(screen, (13, 13, 13), pg.Rect(0, 0, size[0], size[1]))

    if not (selectionned is None):
        possiblePlay = [x.to_square for x in board.legal_moves if x.from_square==selectionned]

    counter = 0
    for j in range(3, -5, -1):
        for i in range(-4, 4):
            pg.draw.rect(screen, squareColor[(i + j) % 2], pg.Rect(mid[0] + i * squareSize, mid[1] + j * squareSize, squareSize, squareSize))
            if not (move is None):
                if counter == move.from_square or counter==move.to_square:
                    pg.draw.rect(screen, (128,128,128), pg.Rect(mid[0] + i * squareSize, mid[1] + j * squareSize, squareSize, squareSize))
            if not (selectionned is None):
                if counter == selectionned:
                    pg.draw.rect(screen, (64,128,64), pg.Rect(mid[0] + i * squareSize, mid[1] + j * squareSize, squareSize, squareSize))
                if counter in possiblePlay:
                    pg.draw.rect(screen, (128,64,64), pg.Rect(mid[0] + i * squareSize, mid[1] + j * squareSize, squareSize, squareSize))
            counter+=1
    
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
                    y = mid[1] - (4 - rank_index) * squareSize
                    screen.blit(piece_img, (x, y))
                file_index += 1


if __name__ == "__main__":
    main()


