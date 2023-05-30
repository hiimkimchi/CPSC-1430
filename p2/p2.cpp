// Bryan Kim
// p2.cpp
// This file allows users to input prompts to create ASCII art (rectangular canvas).
// A TextGrid struct that uses dynamic memory helps users change height and width easily.
// Assume the user knows the commands and the necessary parameters for each command.

#include <fstream>
#include <iostream>
#include <string>

int const         INIT_HEIGHT = 8;
int const         INIT_WIDTH  = 16;
int const         FULL_LINE   = 10000;
char const        TICK        = '`';
std::string const QUIT        = "Q";
std::string const SAVE        = "S";
std::string const LOAD        = "L";
std::string const PAINT       = "P";
std::string const TRANS       = "T";
std::string const AROW        = "R";
std::string const RROW        = "r";
std::string const ACOL        = "C";
std::string const RCOL        = "c";

// desc: a two dimensional dynamic array that represents a grid of texts
//       two ints that represent height and width.
// invariants:
//     -tiles is either null, or pointing to a dynamically allocated 2D array
//     -the length of the array pointed by tiles is height
//     -every element in the array pointed by tiles points to an array of length width
//     -every character element in the 2D array pointed by tiles is not a whitespace
//      or control character
struct TextGrid {
    char       **tiles;
    unsigned int height;
    unsigned int width;
};

// desc: Returns a TextGrid that contains the contents of the file file_path as a
//       dynamic 2D array.
// pre : -input should have each parameter seperated by a space
// post: -grid should be saved onto the grid.tiles
//       -grid should be saved as a rectangle (no variation in row sizes)
//       -grid.height and grid.width should be updated as necessary
TextGrid load_grid(std::string file_path);

// desc: Saves the contents of grid to the file named file_path, saving each row in the grid
//       as a line in the file.
// pre : -input should have each parameter seperated by a space
// post: -saved file should contain the contents of the grid
//       -saved file should be .txt
void save_grid(TextGrid &grid, std::string file_path);

// desc: Writes the value of fill to the character at the yth row and the xth column of grid
// pre : -input should have each parameter seperated by a space
//       -x and y are zero indexed
// post: -grid is permanently changed at [x][y] to the fill char
void paint(TextGrid &grid, unsigned int x, unsigned int y, char fill);

// desc: Prints the contents of the 2D dynamic array pointed by grid.tiles
// pre : -input should have each parameter seperated by a space
// post: none
void show(TextGrid &grid);

// desc: Accepts two characters, target and repl, then replaces every
//       instance of the value target in the grid state with the value repl.
// pre : -input should have each parameter seperated by a space
// post: -every element of grid that is target is permanently changed to the replacement
void transform(TextGrid &grid, char target, char repl);

// desc: Accepts a character, fill, then adds a row to the bottom of the
//       grid state, with each new character assigned the value of fill.
// pre : -input should have each parameter seperated by a space
// post: -the grid's height is incremented
//       -new row is permanently filled with fill char
void add_row(TextGrid &grid, char fill);

// desc: Removes the bottom-most row from the grid state.
// pre : -grid.height must be greater than 0
// post: -the grid's height is decremented
//       -the last row is deallocated
void remove_row(TextGrid &grid);

// desc: Accepts a character, fill, then adds a column to the right end
//       of the grid state, with each new character assigned the value of fill.
// pre : -input should have each parameter seperated by a space
// post: -the grid's width is incremented
//       -new col is permanently filled with fill char
void add_col(TextGrid &grid, char fill);

// desc: Removes the right-most column from the grid state.
// pre : -grid.width must be greated than 0
// post: -the grid's width is decremented
//       -the last column is deallocated
void remove_col(TextGrid &grid);

// desc: Checks if the user's cin inputs are valid
// pre : -must be called after the desired cin statements are finished
// post: -true  = cin input is bad
//       -false = cin input is valid
bool is_input_bad();

// desc: Deallocates a grid
// pre : -grid must be previously allocated
// post: -grid parameter is deallocated
void deallocate(TextGrid &grid);

// desc: In a loop, uses the show function to display the grid state to the user, then
//       accepts a command.
// pre : -consts must be declared and helper functions should be functional
//       -whenever TextGrid struct is used, it must be initialized before usage
// post: none
int main() {
    std::string  input_letter;
    std::string  file_path;
    char         character;
    char         target;
    unsigned int x;
    unsigned int y;
    bool         bad_input;
    TextGrid     temp_grid;
    TextGrid     grid;

    // allocate dynamic grid and initialize fields
    grid.height = INIT_HEIGHT;
    grid.width  = INIT_WIDTH;
    grid.tiles  = new char *[grid.height];
    for (unsigned int i = 0; i < grid.height; i++) {
        grid.tiles[i] = new char[grid.width];
    }

    // initialize each element to `
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            grid.tiles[i][j] = TICK;
        }
    }

    // loop that prints and accepts command
    while (input_letter != QUIT) {
        show(grid);
        std::cin >> input_letter;
        // error if first char is longer than one char long
        if (input_letter.size() != 1) {
            std::cout << "Invalid command: please choose from valid options.\n\n";
            // all conditionals check to see if there are user errors with cin
        } else {
            // call save function
            if (input_letter == SAVE) {
                std::cin >> file_path;
                bad_input = is_input_bad();
                if (!bad_input) {
                    save_grid(grid, file_path);
                }
                // call load function
            } else if (input_letter == LOAD) {
                std::cin >> file_path;
                bad_input = is_input_bad();
                if (!bad_input) {
                    // set temp_grid to load function and if the input file does not exist,
                    // do not update grid
                    temp_grid = load_grid(file_path);
                    if (temp_grid.height > 0) {
                        // deallocate and reallocate
                        deallocate(grid);
                        grid = temp_grid;
                    }
                }
                // call paint function
            } else if (input_letter == PAINT) {
                std::cin >> x >> y >> character;
                bad_input = is_input_bad();
                if (!bad_input) {
                    paint(grid, x, y, character);
                }
                // call transform function
            } else if (input_letter == TRANS) {
                std::cin >> target >> character;
                bad_input = is_input_bad();
                if (!bad_input) {
                    transform(grid, target, character);
                }
                // call row adding function
            } else if (input_letter == AROW) {
                std::cin >> character;
                bad_input = is_input_bad();
                if (!bad_input) {
                    add_row(grid, character);
                }
                // call row removing function
            } else if (input_letter == RROW) {
                remove_row(grid);
                // call column adding function
            } else if (input_letter == ACOL) {
                std::cin >> character;
                bad_input = is_input_bad();
                if (!bad_input) {
                    add_col(grid, character);
                }
                // call column removing function
            } else if (input_letter == RCOL) {
                remove_col(grid);
                // if all else fails error message
            } else {
                if (input_letter != QUIT) {
                    std::cout << "Invalid command: please choose from valid options.\n\n";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Thank you for using the ASCII Art Editor.\n\n";

    // deallocate the 2D dynamic array
    deallocate(grid);
    return 0;
}

TextGrid load_grid(std::string file_path) {
    TextGrid      grid;
    std::string   line;
    std::ifstream in_file;
    in_file.open(file_path);

    // check if the file fails
    if (in_file.fail()) {
        std::cout << "File error.\n\n";
        grid.height = -1;
        grid.width  = -1;
        grid.tiles  = nullptr;
        return grid;
    }

    // set width to length of a line in the file
    // set height to number of lines
    // close and reopen file
    grid.height = 0;
    while (getline(in_file, line)) {
        grid.height++;
        grid.width = line.length();
    }
    in_file.close();
    in_file.open(file_path);

    // allocate the 2D array
    grid.tiles = new char *[grid.height];
    for (unsigned int i = 0; i < grid.height; i++) {
        grid.tiles[i] = new char[grid.width];
    }

    // use line as an array of chars
    for (unsigned int i = 0; i < grid.height; i++) {
        getline(in_file, line);
        for (unsigned int j = 0; j < grid.width; j++) {
            grid.tiles[i][j] = line[j];
        }
    }

    in_file.close();

    return grid;
}

void save_grid(TextGrid &grid, std::string file_path) {
    std::ofstream out_file;
    out_file.open(file_path);

    // write all the elements into the file
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            out_file << grid.tiles[i][j];
        }
        // new line after each row
        out_file << '\n';
    }
    out_file.close();
}

void paint(TextGrid &grid, unsigned int x, unsigned int y, char fill) {
    // if in bounds, fill a character
    if (x < grid.width && y < grid.height) {
        grid.tiles[x][y] = fill;
    } else {
        // error message
        std::cout << "Coordinates are out of bounds\n" << std::endl;
    }
}

void show(TextGrid &grid) {
    // traverse width and length of the tiles
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            // print element
            std::cout << grid.tiles[i][j];
        }
        // next line
        std::cout << std::endl;
    }
}

void transform(TextGrid &grid, char target, char repl) {
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            // finds which elements are the target and replaces them
            if (grid.tiles[i][j] == target) {
                grid.tiles[i][j] = repl;
            }
        }
    }
}

void add_row(TextGrid &grid, char fill) {
    // make a new temp 2D ptr array
    char **new_array_ptr = new char *[grid.height + 1];
    for (unsigned int i = 0; i < grid.height + 1; i++) {
        new_array_ptr[i] = new char[grid.width];
    }

    // copy all the elements into a temp 2D ptr array
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            new_array_ptr[i][j] = grid.tiles[i][j];
        }
    }

    // add the new row
    for (unsigned int i = 0; i < grid.width; i++) {
        new_array_ptr[grid.height][i] = fill;
    }

    // deallocate the original 2D ptr array
    deallocate(grid);

    grid.tiles = new_array_ptr;
    grid.height++;
}

void remove_row(TextGrid &grid) {
    if (grid.height > 0) {
        delete[] grid.tiles[grid.height - 1];
        grid.height--;
    } else {
        std::cout << "No rows able to delete\n";
    }
}

void add_col(TextGrid &grid, char fill) {
    // make a new temp 2D ptr array
    char **new_array_ptr = new char *[grid.height];
    for (unsigned int i = 0; i < grid.height; i++) {
        new_array_ptr[i] = new char[grid.width + 1];
    }

    // copy all the elements into a temp 2D ptr array
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width + 1; j++) {
            if (j == grid.width) {
                new_array_ptr[i][j] = fill;
            } else {
                new_array_ptr[i][j] = grid.tiles[i][j];
            }
        }
    }

    // deallocate the original 2D ptr array
    deallocate(grid);
    grid.tiles = new_array_ptr;
    grid.width++;
}

void remove_col(TextGrid &grid) {
    if (grid.width > 0) {
        // make a new temp 2D ptr array
        char **new_array_ptr = new char *[grid.height];
        for (unsigned int i = 0; i < grid.height; i++) {
            new_array_ptr[i] = new char[grid.width - 1];
        }

        // copy all the elements into a temp 2D ptr array
        for (unsigned int i = 0; i < grid.height; i++) {
            for (unsigned int j = 0; j < grid.width - 1; j++) {
                new_array_ptr[i][j] = grid.tiles[i][j];
            }
        }

        // deallocate the original 2D ptr array
        deallocate(grid);
        grid.tiles = new_array_ptr;
        grid.width--;
    } else {
        std::cout << "No columns able to delete\n";
    }
}

bool is_input_bad() {
    bool input_fail = std::cin.fail();
    if (input_fail) {
        std::cin.clear();
        std::cin.ignore(FULL_LINE, '\n');
    }
    return input_fail;
}

void deallocate(TextGrid &grid) {
    for (unsigned int i = 0; i < grid.height; i++) {
        delete[] grid.tiles[i];
    }
    delete[] grid.tiles;
}