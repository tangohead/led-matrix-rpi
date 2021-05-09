import numpy as np

def convert_int_to_coord(x_dim: int, y_dim:int, num: int):
    pos_x = num % y_dim
    pos_y = num // y_dim
    return (pos_x, pos_y)
