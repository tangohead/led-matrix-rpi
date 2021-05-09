import time
import numpy as np

from GameOfLife import GameOfLife

if __name__=="__main__":
    #game = GameOfLife(x=10, y=10, starting_elements=50, wrap_grid=True)
    game = GameOfLife(wrap_grid=True)
    # game.from_grid(np.array([
    #             [0,0,1,0,0,0,0],
    #             [1,0,1,0,0,0,0],
    #             [0,1,1,0,0,0,0],
    #             [0,0,0,0,0,0,0],
    #             [0,0,0,0,0,0,0],
    #             [0,0,0,0,0,0,0],
    #             [0,0,0,0,0,0,0],
    # ]))
    game.from_params(10,10)
    game.display_ascii_grid()

    for i in range(100):
        print("------------")
        game.iterate()
        game.display_ascii_grid()
        time.sleep(0.8)

