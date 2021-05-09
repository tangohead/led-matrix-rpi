import random
import numpy as np
import utils

class GameOfLife:
    def from_params(self, x: int = 32, y: int = 32):
        self.x = x
        self.y = y

        self.grid = [0]*(self.x*self.y)
        self.__seed_grid()

    def from_grid(self, grid: list):
        self.x = grid.shape[1]
        self.y = grid.shape[0]
        self.grid = grid

    def __init__(
        self,
        seed: int = 42,
        starting_elements: int = 40,
        blank_threshold: int = 10,
        wrap_grid: bool = False,
    ):
        self.seed = seed
        self.iter_blank = 0
        self.blank_threshold = blank_threshold
        self.starting_elements = starting_elements
        self.wrap_grid = wrap_grid

        random.seed(self.seed)

    def __get_coord(self, x_pos: int, y_pos: int):
        if self.wrap_grid:
            pass
        else:
            if x_pos < 0 or x_pos >= self.x:
                return 0
            if y_pos < 0 or y_pos >= self.y:
                return 0

            return self.grid[y_pos*self.y+x_pos]

    def __set_coord(self, x_pos: int, y_pos: int, value: int):
        self.grid[y_pos*self.y+x_pos] = value

    def __seed_grid(self):
        print("Seeding...")
        max_pos = self.x * self.y
        for i in range(self.starting_elements):
            coord = utils.convert_int_to_coord(
                self.x, self.y, random.randint(0, max_pos - 1)
            )
            self.__set_coord(coord[1], coord[0], 1)


    def display_ascii_grid(self):
        for i in range(self.y):
            for j in range(self.x):
                if self.grid[i*self.x+j] == 0:
                    print(".", end="")
                else:
                    print("x", end="")
            print()

    def iterate(self):
        # Check if it is blank first
        if sum(self.grid) == 0:
            self.iter_blank += 1

            if self.iter_blank > self.blank_threshold:
                self.__seed_grid()
                self.iter_blank = 0
        else:
            next_grid = [0]*(self.x*self.y)

            for i in range(self.y):
                for j in range(self.x):
                    #print(f"{j},{i}")
                    neighbourhood = self.__get_neighbourhood(j, i)
                    neighbourhood_alive = sum(neighbourhood)
                    alive = False

                    if self.__get_coord(j, i) == 1:
                        # discount the current live cell from the count
                        # neighbourhood_alive =  neighbourhood_alive - 1
                        alive = True

                    # alive and < 2 neighbours - dies
                    if alive and neighbourhood_alive < 2:
                        next_grid[i*self.y+j] = 0
                    # alive and two or three neighbours alive lives
                    elif alive and (neighbourhood_alive == 2 or neighbourhood_alive == 3):
                        next_grid[i*self.y+j] = 1
                    # alive and more than three neighbours dies
                    elif alive and neighbourhood_alive > 3:
                        next_grid[i*self.y+j] = 0
                    # dead and exactly three lives
                    elif not alive and neighbourhood_alive == 3:
                        next_grid[i*self.y+j] = 1

            self.grid = next_grid


    def __get_neighbourhood(self, x, y):

        return [
            self.__get_coord(x-1, y-1),
            self.__get_coord(x, y-1),
            self.__get_coord(x+1, y-1),
            self.__get_coord(x-1, y),
            self.__get_coord(x+1, y),
            self.__get_coord(x-1, y+1),
            self.__get_coord(x, y+1),
            self.__get_coord(x+1, y+1),
        ]

       # return self.grid[y_min : y_max + 1, x_min : x_max + 1]
