/**
 * @file life.c
 * @author Ryan Najac
 * @brief Conway's Game of Life
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

/* @def SIZE
 * @brief The size of the game grid.
 */
#define SIZE 15

/* @def DELAY
 * @brief The delay between each iteration of the game in microseconds.
 */
#define DELAY 300000

/* @var int ticks
 * @brief Global variable to count the number of iterations (ticks) in the game.
 */
int ticks = 0;

/*
 * @struct unit
 * @brief Represents a single cell in the game grid.
 *
 * Each cell can be either alive or dead and can be marked for death in the next iteration.
 */
struct unit {
	bool alive;		///< Indicates if the cell is currently alive.
	bool marked_for_death;	///< Flags the cell for life or death in the next iteration.
} cell[SIZE][SIZE];		///< 2D array representing the game grid.

/*
 * @brief Initializes all cells in the grid to dead.
 */
void init_cells();

/*
 * @brief Randomizes the state of each cell in the grid.
 */
void randomize();

/*
 * @brief Counts the number of alive neighbors for a given cell.
 * @param i Row index of the cell.
 * @param j Column index of the cell.
 * @return int Number of alive neighbors.
 */
int count_neighbors(int i, int j);

/*
 * @brief Flags each cell for life or death in the next cycle based on the number of neighbors.
 */
void flag_life();

/*
 * @brief Prints the current state of the world to the console.
 */
void print_world();

/*
 * @brief Updates the world to the next cycle, changing the state of each cell based on life flags.
 */
void cycle_world();

/* seed states */
void seedLWSS();
void seedSpaceshipGlider();
void seedBlinkerOscillator();

int main(int argc, char** argv)
{
	init_cells();
	if (argc == 2) {
		switch (atoi(argv[1])) {
			case 1: seedSpaceshipGlider(); break;
			case 2: seedBlinkerOscillator(); break;
			case 3: seedLWSS(); break;
			case 4: seedSpaceshipGlider(); seedBlinkerOscillator(); break;
			case 5: seedLWSS(); seedBlinkerOscillator(); break;
			case 6: seedSpaceshipGlider(); seedLWSS(); break;
			default: randomize();
		}
	} else {
		randomize();
	}
	while(1) {
		print_world();
		flag_life();
		cycle_world();
		usleep(DELAY);
		fflush(NULL);
	}
	return 0;
}

void init_cells()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			cell[i][j] = (struct unit){ false, false };
}

void randomize()
{
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			cell[i][j].alive = rand() % 2;
}

int count_neighbors(int i, int j) {
	int neighbors = 0;
	for (int row = i - 1; row <= i + 1; row++)
		for (int col = j - 1; col <= j + 1; col++)
			if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && !(row == i && col == j) && cell[row][col].alive)
				neighbors++;
	return neighbors;
}

void flag_life() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int neighbors = count_neighbors(i, j);
			cell[i][j].marked_for_death = !(neighbors == 3 || (cell[i][j].alive && neighbors == 2));
		}
	}
}

void print_world() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			printf("%c ", cell[i][j].alive ? '0' : '.');
		printf("\n");
	}
	printf("\nTicks = %d\n\n", ticks);
}

void cycle_world() {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			cell[i][j].alive = !cell[i][j].marked_for_death;
	ticks++;
}

void seedBlinkerOscillator() {
	cell[5][5].alive++;
	cell[6][5].alive++;
	cell[7][5].alive++;
	cell[8][5].alive++;
	cell[9][5].alive++;
	cell[5][7].alive++;
	cell[9][7].alive++;
	cell[5][9].alive++;
	cell[6][9].alive++;
	cell[7][9].alive++;
	cell[8][9].alive++;
	cell[9][9].alive++;
}

void seedSpaceshipGlider() {
	cell[0][2].alive++;
	cell[1][0].alive++;
	cell[1][2].alive++;
	cell[2][1].alive++;
	cell[2][2].alive++;
}

void seedLWSS() {
	cell[1][11].alive++;
	cell[2][10].alive++;
	cell[3][10].alive++;
	cell[4][10].alive++;
	cell[4][11].alive++;
	cell[4][12].alive++;
	cell[4][13].alive++;
	cell[1][14].alive++;
	cell[3][14].alive++;
}

