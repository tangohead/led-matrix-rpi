import random

import numpy as np

import utils


class GameOfLife:
    def from_params(self, x: int = 32, y: int = 32):
        self.x = x
        self.y = y

        self.grid = np.zeros((self.x, self.y))
        self.__seed_grid()

    def from_grid(self, grid: np.ndarray):
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

    def __seed_grid(self):
        print("Seeding...")
        max_pos = self.x * self.y
        for i in range(self.starting_elements):
            coord = utils.convert_int_to_coord(
                self.x, self.y, random.randint(0, max_pos - 1)
            )
            print("Adding coord at {}".format(coord))
            self.grid[coord[1], coord[0]] = 1


    def display_ascii_grid(self):
        for i in self.grid:
            for j in i:
                if j == 0:
                    print(".", end="")
                else:
                    print("x", end="")
            print()

    def iterate(self):

        # Check if it is blank first
        if np.sum(self.grid) == 0:
            self.iter_blank += 1

            if self.iter_blank > self.blank_threshold:
                self.__seed_grid()
                self.iter_blank = 0
        else:
            next_grid = np.zeros(self.grid.shape)

            for i, j in np.ndindex(self.grid.shape):
                neighbourhood = self.__get_neighbourhood(i, j)
                neighbourhood_alive = np.sum(neighbourhood)
                alive = False

                if self.grid[i, j] == 1:
                    # discount the current live cell from the count
                    neighbourhood_alive =  neighbourhood_alive - 1
                    alive = True

                # alive and < 2 neighbours - dies
                if alive and neighbourhood_alive < 2:
                    next_grid[i, j] = 0
                # alive and two or three neighbours alive lives
                elif alive and (neighbourhood_alive == 2 or neighbourhood_alive == 3):
                    next_grid[i, j] = 1
                # alive and more than three neighbours dies
                elif alive and neighbourhood_alive > 3:
                    next_grid[i, j] = 0
                # dead and exactly three lives
                elif not alive and neighbourhood_alive == 3:
                    next_grid[i, j] = 1

            self.grid = next_grid


    def __get_neighbourhood(self, y, x):
        y_min = y - 1
        y_max = y + 1
        x_min = x - 1
        x_max = x + 1

        if self.wrap_grid:
            # cut y first
            y_cut = self.grid.take([i for i in range(y_min, y_max+1)], axis=0, mode='wrap')
            x_cut = y_cut.take([i for i in range(x_min, x_max+1)], axis=1, mode='wrap')
            return x_cut
        else:
            if y_min < 0:
                y_min = 0
            if y_max > self.grid.shape[0]:
                y_max = self.grid.shape[0]
            if x_min < 0:
                x_min = 0
            if x_max > self.grid.shape[1]:
                x_max = self.grid.shape[1]

            return self.grid[y_min : y_max + 1, x_min : x_max + 1]
