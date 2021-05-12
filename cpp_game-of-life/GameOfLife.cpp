#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameOfLife
{
private:
    int *grid;
    bool wrap;
    int seed;
    int starting_elements;
    int blank_threshold;
    int last_sum;
    int static_count;

    void seed_grid();
    int get_neighbourhood_value(int, int);

public:
    int x_dim;
    int y_dim;

    GameOfLife(int, int);
    GameOfLife(int, int, unsigned);
    GameOfLife(int, int, unsigned, int, bool);

    int get_value_at_coord(int, int);
    void set_value_at_coord(int, int, int);
    void iterate();
    void print_grid();
};

GameOfLife::GameOfLife(int x_dim, int y_dim)
{
    this->x_dim = x_dim;
    this->y_dim = y_dim;
    starting_elements = int(this->x_dim * this->y_dim * 0.2);
    this->wrap = false;
    this->static_count = 0;
    this->last_sum = 0;

    grid = new int[x_dim * y_dim]();

    std::srand(std::time(nullptr));

    seed_grid();
}

GameOfLife::GameOfLife(int x_dim, int y_dim, unsigned seed)
{
    this->x_dim = x_dim;
    this->y_dim = y_dim;
    starting_elements = int(this->x_dim * this->y_dim * 0.2);
    wrap = false;
    this->static_count = 0;
    this->last_sum = 0;

    grid = new int[x_dim * y_dim]();

    std::srand(seed);

    seed_grid();
}

GameOfLife::GameOfLife(int x_dim, int y_dim, unsigned seed, int starting_elements, bool wrapping)
{
    this->x_dim = x_dim;
    this->y_dim = y_dim;
    this->starting_elements = starting_elements;
    wrap = wrapping;
    this->static_count = 0;
    this->last_sum = 0; 

    grid = new int[x_dim * y_dim]();

    std::srand(seed);

    seed_grid();
}

void GameOfLife::seed_grid()
{
    int max_pos = x_dim * y_dim;

    for (int i = 0; i < starting_elements; i++)
    {
        grid[std::rand() % max_pos] = 1;
    }
}

void GameOfLife::print_grid()
{
    for (int y = 0; y < y_dim; y++)
    {
        for (int x = 0; x < x_dim; x++)
        {
            if (grid[y * y_dim + x] == 1)
            {
                cout << " X ";
            }
            else
            {
                cout << " . ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int GameOfLife::get_value_at_coord(int x, int y)
{
    //TODO: implement wrapping
    if (wrap == true)
    {
        int tmp_x = x;
        int tmp_y = y;
        if (x < 0) {
            tmp_x = x_dim + x;
        }
        else if (x >= x_dim) {
            tmp_x = 0 + (x-x_dim);
        }

        if (y < 0) {
            tmp_y = y_dim + y;
        }
        else if (y >= y_dim) {
            tmp_y = 0 + (y-y_dim);
        }

        return grid[tmp_y * y_dim + tmp_x];
    }
    else {
        if (x < 0 || x >= x_dim)
            return 0;
        if (y < 0 || y >= y_dim)
            return 0;

        return grid[y * y_dim + x];
    }
}

void GameOfLife::set_value_at_coord(int x, int y, int value)
{
    grid[y * y_dim + x] = value;
}

int GameOfLife::get_neighbourhood_value(int x, int y)
{
    int sum = 0;
    for (int i = (x - 1); i <= (x + 1); i++)
    {
        for (int j = (y - 1); j <= (y + 1); j++)
        {
            sum += get_value_at_coord(i, j);
        }
    }
    return sum;
}

void GameOfLife::iterate()
{
    //TODO implement reseeding

    int *next_grid = new int[x_dim * y_dim]();
    int curr_sum = 0;

    for (int i = 0; i < x_dim; i++)
    {
        for (int j = 0; j < y_dim; j++)
        {
            int neighbour_sum = get_neighbourhood_value(i, j);
            bool alive = false;

            if (get_value_at_coord(i, j) == 1)
            {
                alive = true;
                curr_sum++;
            }

            if (alive && neighbour_sum < 2)
            {
                next_grid[j * y_dim + i] = 0;
            }
            else if (alive && (neighbour_sum == 2 || neighbour_sum == 3))
            {
                next_grid[j * y_dim + i] = 1;
            }
            else if (alive && neighbour_sum > 3)
            {
                next_grid[j * y_dim + i] = 0;
            }
            else if (!alive && neighbour_sum == 3)
            {
                next_grid[j * y_dim + i] = 1;
            }
        }
    }
    grid = next_grid;
    if(curr_sum == last_sum && curr_sum < (x_dim*y_dim*0.2)) {
        static_count++;
    }
    last_sum = curr_sum;

    if(curr_sum < (x_dim*y_dim*0.2) && static_count > 10) {
        seed_grid();
        static_count = 0;
    }

}
