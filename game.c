#include "game.h"

Game_State init_game() {
    return Game_State {
        player_pos = 0;
        enemy_positions = {};

        input_state = {};
    };
}
