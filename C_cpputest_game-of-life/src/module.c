#include "module.h"


// initialize empty world space
void init_world(World* world)
{
  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
      world->space[x][y] = false;
}


// advance world space to the next generation
void next_world(World* world)
{
  World oldWorld = *world;

  init_world(world);

  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
    {
      world->space[x][y] = cellSurvives(&oldWorld, x, y);
    }
}


// test if cell is part of the next generation
bool cellSurvives(World* world, uint8_t x, uint8_t y)
{
  bool alive = false;

  // reproduction
  if (   world->space[x][y] == false
      && neighbourCount(world, x, y) == 3 )
    alive = true;
  // stasis
  else if (   world->space[x][y] == true
           && neighbourCount(world, x, y) == 2 )
    alive = true;

  return alive;
}


// wrap around x coordinates, if necessary
uint8_t xWrap(int8_t x)
{
  return (x >= 0) ? x : WORLD_SIZE_X + x;
}


// wrap around y coordinates, if necessary
uint8_t yWrap(int8_t y)
{
  return (y >= 0) ? y : WORLD_SIZE_Y + y;
}


// check if cell is alive ... wrap around if necessary
bool cellIsAlive(World* world, int8_t x, int8_t y)
{
  // FIXME no wrap around
  if (x>0 && y>0)
    return world->space[x][y];
  else
    return false;
  //return world->space[xWrap(x)][yWrap(y)];
}


// number of neighbours
uint8_t neighbourCount(World* world, uint8_t x, uint8_t y)
{
  // FIXME  correctly count the number of neighbours
  uint8_t count = 0;

  // count all living neighbouring cells
  if (cellIsAlive(world, x-1, y-1))
    count++;
  printf("%d ", count);
  if (cellIsAlive(world, x  , y-1))
    count++;
  printf("%d ", count);
  if (cellIsAlive(world, x+1, y-1))
    count++;
  printf("%d  ", count);

  if (cellIsAlive(world, x-1, y  ))
    count++;
  printf("%d ", count);
  if (cellIsAlive(world, x+1, y  ))
    count++;
  printf("%d  ", count);

  if (cellIsAlive(world, x-1, y+1))
    count++;
  printf("%d ", count);
  if (cellIsAlive(world, x  , y+1))
    count++;
  printf("%d ", count);
  if (cellIsAlive(world, x+1, y+1))
    count++;
  printf("%d\n", count);

  return count;
}

