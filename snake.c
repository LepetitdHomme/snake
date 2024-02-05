#include "includes/common.h"

void grow(state_t *state, coord_t coord) {
	snake_t *old_head = state->snake;

	state->snake = (snake_t *)malloc(sizeof(snake_t));
	state->snake->x = coord.x;
	state->snake->y = coord.y;
	state->snake->next = old_head;
	state->grid[state->snake->x][state->snake->y] = 1;
}

void lose_tail(state_t *state) {
	snake_t *tmp = state->snake;
	snake_t *new_tail = tmp;

	if (tmp->next == NULL) {
		return;
	}

	while (tmp->next) {
		tmp = tmp->next;
		if (tmp->next == NULL) {
			new_tail->next = NULL;
			state->grid[tmp->x][tmp->y] = 0;
			free(tmp);
			return;
		}
		new_tail = tmp;
	}
}

void update_apple(state_t *state) {
	coord_t coord;

	do {
		coord.x = get_random_int(GRID_W);
		coord.y = get_random_int(GRID_H);
	} while (state->grid[coord.x][coord.y] != 0);

	state->grid[coord.x][coord.y] = 2;
	state->apple.x = coord.x;
	state->apple.y = coord.y;
}

int touching_itself(state_t *state, coord_t coord) {
	snake_t *tmp = state->snake;

	do {
		if (tmp->x == coord.x && tmp->y == coord.y) {
			return TRUE; // touching itself !
		}
		tmp = tmp->next;
	} while (tmp && tmp->next);

	return FALSE;
}

void move_snake(state_t *state) {
	snake_t *node = state->snake;
	coord_t coord;

	coord.x = state->snake->x;
	coord.y = state->snake->y;

	switch (state->direction) {
		case UP:
			coord.y -= 1;
			break;
		case DOWN:
			coord.y += 1;
			break;
		case LEFT:
			coord.x -= 1;
			break;
		default:
			coord.x += 1;
	}

	// HITS APPLE
	if (state->apple.x == coord.x && state->apple.y == coord.y) {
		printf("YUMMY !\n");
		update_apple(state);
		grow(state, coord);
		//regen apple
		return;
	}

	// HITS WALL
	if (coord.x >= GRID_W || coord.x < 0 || coord.y >= GRID_H || coord.y < 0) {
		printf("LOST - walls are not comestible!\n");
		state->running = FALSE;
		state->lost = TRUE;
		return;
	}

	if (touching_itself(state, coord)) {
		printf("LOST - stop touching yourself !\n");
		state->running = FALSE;
		state->lost = TRUE;
		return;
	}

	grow(state, coord);
	lose_tail(state);
}
