#include "module.h"


// populate the world
void populate_world(World* world)
{
  // FIXME  [x][y] -> use correct coordinate system
  /*world->space[3][2] = true;
  world->space[3][3] = true;
  world->space[3][4] = true;*/

  world->space[1][1] = true;
  world->space[2][1] = true;
  world->space[3][1] = true;
}


// draw the world's space
void draw_world(World* world)
{
  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
  {
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
    {
      printf("%s", (world->space[x][y]==true) ? "X" : ".");
    }
    printf("\n");
  }
}


// draw the world's neighbour count
void draw_neighbour_count(World* world)
{
  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
  {
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
    {
      printf("%d", neighbourCount(world, x, y));
    }
    printf("\n");
  }
}


int main()
{
  World world;
  init_world(&world);
  //populate_world(&world);

  for (uint8_t gen=0; gen<2; gen++)
  {
    printf("gen %d\n", gen);
    draw_world(&world);
    //draw_neighbour_count(&world);
    next_world(&world);
    printf("\n");
  }

  return 0;
}

