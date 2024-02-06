#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#define DEBUG printf("%s - %d\n", __FILE__, __LINE__)

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define SCALE 16
#define CYCLE_INTERVAL 60 // milliseconds between cycles
#define GRID_W WINDOW_WIDTH/SCALE
#define GRID_H WINDOW_HEIGHT/SCALE

#define TRUE 1
#define FALSE 0

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef struct {
	int                  x;
	int                  y;
} coord_t;

typedef struct snake_node {
	int                  x;
	int                  y;
	struct snake_node    *next;
} snake_t;

typedef struct {
	int                  quit;
	int                  running;
	int                  score;
	int                  lost;
	int                  cycle_count;
	snake_t              *snake;
	coord_t              apple;
	enum Direction       direction;
	int                  (*grid)[GRID_H];
	Uint32               current_time;
	SDL_Renderer         *renderer;
	SDL_Event            event;
} state_t;


void                  move_snake(state_t *state);
void                  display_grid(state_t *state);
int                   get_random_int(int upper_bound);
void                  update_apple(state_t *state);
void                  free_snake(state_t *state);

#endif