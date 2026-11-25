#ifndef GAME_H
#define GAME_H

const uint8_t MAX_ENEMY_COUNT = 3;

typedef struct {
    uint8_t x, y;
} Position;

typedef struct {
    Position pos;
    uint8_t alive;
} Enemy;

typedef struct {
    Position player_pos;
    Enemy enemies[MAX_ENEMY_COUNT];
} Game_State;

#endif GAME_H

