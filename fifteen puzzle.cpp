#include <iostream>
#include <string>
#include <random>

using namespace std;
const int N = 4;
int grid[N][N];

//This function prints the grid of 2048 Game as the game progresses
void print_grid() {
    for (int i = 0; i < ((N + 4) * N + N + 1); cout << "-", i++);
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "|";
        for (int j = 0; j < N; j++) {
            string e = "";
            if (grid[i][j] == 0) {
                for (int t = 0; t < N + 4; e += " ", t++);
            }
            else {
                int str_len = to_string(grid[i][j]).size();
                int r1 = ((N + 4) - str_len + 1) / 2;
                int r2 = ((N + 4) - str_len) - r1;
                for (int t = 0; t < r1; e += " ", t++);
                e += to_string(grid[i][j]);
                for (int t = 0; t < r2; e += " ", t++);
            }
            cout << e << "|";
        }
        cout << "\n";
        for (int t = 0; t < ((N + 4) * N + N + 1); cout << "-", t++);
        cout << "\n";
    }
}
bool check_win() {
    int counter = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            while (counter <= 15) {
                if (grid[i][j] == counter) {
                    counter++;
                }
                else {
                    return false;
                }
            }
        }
    }
    return true;
}
void check_emptyCell(int& x, int& y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                x = i; y = j;
                break;
            }

        }
    }

}


//function generate cells
void generate_cell() {
    int i = 0, j = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };
    int size = sizeof(data) / sizeof(data[0]);

    std::random_shuffle(data, data + size);

    for (int loop = 0; loop < size; loop++)
    {


        grid[i][j] = data[loop];
        j++;
        if (j > 3) {
            i++;
            j = 0;
        }



    }
}
bool check_available_direction_right(int x, int y) {
    if (y == 0) {
        return false;
    }
    else {
        return true;
    }
}
bool check_available_direction_left(int x, int y) {
    if (y == 3)
    {
        return false;
    }
    else {
        return true;
    }
}
bool check_available_direction_down(int x, int y) {
    if (x == 0) {
        return false;
    }
    else {
        return true;
    }
}
bool check_available_direction_up(int x, int y) {
    if (x == 3) {
        return false;
    }
    else {
        return true;
    }
}

bool check_available_move(int i, int x, int y) {
    bool res = true;

    if (i == 3)  res = check_available_direction_right(x, y);

    else if (i == 5)  res = check_available_direction_up(x, y);

    else if (i == 1)   res = check_available_direction_left(x, y);

    else if (i == 2) res = check_available_direction_down(x, y);
    return res;
}

void move(int i, int x, int y) {
    if (i == 3) {
        grid[x][y] = grid[x][y - 1];
        grid[x][y - 1] = 0;
    }
    else if (i == 1) {
        grid[x][y] = grid[x][y + 1];
        grid[x][y + 1] = 0;
    }
    else if (i == 5) {
        grid[x][y] = grid[x + 1][y];
        grid[x + 1][y] = 0;
    }
    else if (i == 2) {
        grid[x][y] = grid[x - 1][y];
        grid[x - 1][y] = 0;
    }
}
bool check_valid_direction(int i) {
    if (i == 1 || i == 2 || i == 3 || i == 5) {
        return true;
    }
    else
    {
        return false;
    }
}


//This function clears the game structures
void grid_clear() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;

        }
    }

}
int read_input(int x, int y) {
    int i;
    cout << "Enter the direction: ";
    cin >> i;
    while (!check_valid_direction(i) || !check_available_move(i, x, y)) {
        cout << "Enter a valid direction: ";
        cin >> i;
    }
    return i;
}

void play_game() {
    int x, y, i;
    cout << ("15puzzle Game!") << endl;
    cout << ("Welcome...") << endl;
    cout << ("============================") << endl;
    while (true) {
        print_grid();
        check_emptyCell(x, y);
        i = read_input(x, y);
        check_available_move(i, x, y);
        move(i, x, y);
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, You won!\n";
            //Ask for continuing the game
            char c;
            cout << "Continue [Y/N] ";
            cin >> c;
            if (c != 'y' && c != 'Y')
                break;
        }
    }
}



int main() {
    while (true) {
        grid_clear();
        generate_cell();
        play_game();
        char c;
        cout << "Play Again [Y/N] ";
        cin >> c;
        if (c != 'y' && c != 'Y')
            break;
    }
}