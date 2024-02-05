#include "includes/common.h"

void display_grid(state_t *state) {
	SDL_Rect quad;

	for (int i = 0 ; i < GRID_W ; i++) {
		for (int j = 0 ; j < GRID_H ; j++) {
			if (state->grid[i][j] > 0) {
				quad.x = i * SCALE;
				quad.y = j * SCALE;
				quad.w = SCALE;
				quad.h = SCALE;

				if (state->grid[i][j] == 1) {
					SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, 255); // snake
				} else if (state->grid[i][j] == 2) {
					SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255); // apple
				}

				SDL_RenderFillRect(state->renderer, &quad);
				SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255); // apple
				SDL_RenderDrawRect(state->renderer, &quad);
			}
		}
	}
}
