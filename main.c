#include "includes/common.h"

int get_random_int(int upperBound) {
  return rand() % upperBound;
}

void handle_event(state_t *state) {
  SDL_Event event = state->event;

  if (event.type == SDL_QUIT) {
    state->quit = TRUE;
  }

  /* KEYS */
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_w:
        if (state->direction != DOWN)
          state->direction = UP;
        break;
      case SDLK_s:
        if (state->direction != UP)
          state->direction = DOWN;
        break;
      case SDLK_a:
        if (state->direction != RIGHT)
          state->direction = LEFT;
        break;
      case SDLK_d:
        if (state->direction != LEFT)
          state->direction = RIGHT;
        break;
    }
  }
}

int next_cycle_ready(state_t *state, uint32_t last_cycle) {
  if (state->running == TRUE) {
    if ((state->current_time - last_cycle) >= CYCLE_INTERVAL) {
      return TRUE;
    }
  }
  return FALSE;
}

void reinitialize_game(state_t *state) {
  for (int x = 0; x < GRID_W ; x++) {
    for ( int y = 0 ; y < GRID_H ; y++) {
      state->grid[x][y] = 0;
    }
  }
  free_snake(state);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL initialization failed: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return 1;
  }

  int grid[GRID_W][GRID_H] = {{0}};
  state_t state;

  if ((state.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return 1;
  }


  state.quit = FALSE;
  state.running = TRUE;
  state.score = 0;
  state.lost = FALSE;
  state.cycle_count = 0;
  state.snake = (snake_t *)malloc(sizeof(snake_t));
  state.snake->x = GRID_W / 2;
  state.snake->y = GRID_H / 2;
  state.snake->next = NULL;
  state.apple.x = GRID_W / 2 + GRID_W / 4;
  state.apple.y = GRID_H / 2 + GRID_H / 4;
  state.direction = RIGHT;
  state.grid = grid;
  grid[state.snake->x][state.snake->y] = 1;
  grid[state.apple.x][state.apple.y] = 2;
  uint32_t last_cycle = SDL_GetTicks();


  while (state.quit == FALSE) {
    state.current_time = SDL_GetTicks();

    while (SDL_PollEvent(&state.event)) {
      handle_event(&state);
    }

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    if (next_cycle_ready(&state, last_cycle)) {
      move_snake(&state);
      last_cycle = state.current_time;
      state.cycle_count++;
    }

    if (state.lost == TRUE) {
      reinitialize_game(&state);
    }

    /* Draw your graphics here (currently an empty black window) */
    display_grid(&state);
    if (state.lost) {

    }
    SDL_RenderPresent(state.renderer);

    SDL_Delay(16); //Uncomment to limit frame rate (approximately 60 FPS) 
  }

  /* Clean up */
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
