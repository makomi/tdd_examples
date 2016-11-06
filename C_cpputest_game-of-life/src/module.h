#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define WORLD_SIZE_X 4
#define WORLD_SIZE_Y 4

typedef struct Worlds {
  bool space[WORLD_SIZE_X][WORLD_SIZE_Y];
} World;

void init_world(World* world);
void next_world(World* world);
bool cellSurvives(World* world, uint8_t x, uint8_t y);
uint8_t xWrap(int8_t x);
uint8_t yWrap(int8_t y);
bool cellIsAlive(World* world, int8_t x, int8_t y);
uint8_t neighbourCount(World* world, uint8_t x, uint8_t y);

