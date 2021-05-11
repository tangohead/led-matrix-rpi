#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameOfLife{
    private: 
        int* grid;
        bool wrap;
        int seed;
        int starting_elements;
        int blank_threshold;

        void seed_grid();
        int get_neighbourhood_value(int, int);

    public:
        int x_dim;
        int y_dim;

        GameOfLife(int, int);
        GameOfLife(int, int, unsigned);
        int get_value_at_coord(int, int);
        void set_value_at_coord(int, int, int);
        void iterate();
        void print_grid();    
};

GameOfLife::GameOfLife(int x_dim, int y_dim) {
    this->x_dim = x_dim;
    this->y_dim = y_dim;
    starting_elements = 40;

    grid = new int[x_dim * y_dim]();

    std::srand(std::time(nullptr));

    seed_grid();
}

GameOfLife::GameOfLife(int x_dim, int y_dim, unsigned seed) {
    this->x_dim = x_dim;
    this->y_dim = y_dim;
    starting_elements = 40;

    grid = new int[x_dim * y_dim]();

    std::srand(seed);

    seed_grid();
}

void GameOfLife::seed_grid(){
    int max_pos = x_dim * y_dim;

    for (int i = 0; i < starting_elements; i++) {
        grid[std::rand() % max_pos] = 1;
    }
}

void GameOfLife::print_grid(){
    for(int y = 0; y < y_dim; y++) {
        for (int x = 0; x < x_dim; x++) {
            if (grid[y*y_dim+x] == 1)
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
    if ( x < 0 || x >= x_dim )
        return 0;
    if ( y < 0 || y >= y_dim )
        return 0;

    return grid[y * y_dim + x];
}

void GameOfLife::set_value_at_coord(int x, int y, int value)
{
    grid[y * y_dim + x] = value;
}

int GameOfLife::get_neighbourhood_value(int x, int y)
{
    int sum = 0;
    for(int i = (x-1); i <= (x+1); i++)
    {
        for (int j = (y-1); j <= (y+1); j++)
        {
            sum += get_value_at_coord(i,j);
        }
    }
    return sum;
}

void GameOfLife::iterate(){
    int* next_grid = new int[x_dim*y_dim]();

    for(int i = 0; i < x_dim; i++){
        for(int j = 0; j < y_dim; j++){
            int neighbour_sum = get_neighbourhood_value(i,j);
            bool alive = false;

            if(get_value_at_coord(i,j) == 1)
                alive = true;

            if(alive && neighbour_sum < 2)
            {
                next_grid[j*y_dim+i] = 0;
            }
            else if(alive && (neighbour_sum == 2 || neighbour_sum == 3))
            {
                next_grid[j*y_dim+i] = 1;
            }
            else if(alive && neighbour_sum > 3)
            {
                next_grid[j*y_dim+i] = 0;
            }
            else if(!alive && neighbour_sum == 3)
            {
                next_grid[j*y_dim+i] = 1;
            }
        }
    }
    grid = next_grid;
}


