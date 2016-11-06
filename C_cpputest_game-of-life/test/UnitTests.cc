#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C"
{
  #include "../src/module.h"
}

//------------------------------------------------------------------------------

TEST_GROUP(FirstTestGroup)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};


TEST(FirstTestGroup, initialWorldSpaceIsEmpty)
{
  // given
  World world;

  // when
  init_world(&world);

  // then
  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
      CHECK(world.space[x][y] == false);
}


// a living cell with less than 2 neighbours dies
TEST(FirstTestGroup, loneliness)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = true; // test cell
  world.space[0][0] = true; // neighbour

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==false);
}


// a living cell with more than 3 neighbours dies
TEST(FirstTestGroup, overcrowding)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = true; // test cell
  world.space[0][0] = true; // neighbours
  world.space[1][0] = true;
  world.space[2][0] = true;
  world.space[1][0] = true;

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==false);
}


// counting neighbours in an empty world
TEST(FirstTestGroup, neighbourCountEmpty)
{
  // given
  World world;

  // when
  init_world(&world);

  // then
  for (uint8_t x=0; x<WORLD_SIZE_X; x++)
    for (uint8_t y=0; y<WORLD_SIZE_Y; y++)
      CHECK(neighbourCount(&world, x, y)==0);
}


// counting neighbours
TEST(FirstTestGroup, neighbourCount)
{
  // given
  World world;
  init_world(&world);

  // when
  world.space[0][0] = true;
  world.space[1][0] = true;
  world.space[2][0] = true;

  // then
  CHECK(neighbourCount(&world, 1, 1)==3);
  CHECK(neighbourCount(&world, 1, 0)==2);
  if (WORLD_SIZE_X>3 && WORLD_SIZE_Y>=3)
    CHECK(neighbourCount(&world, 2, 0)==1);
}


// an empty cell with 3 neighbours comes alive
TEST(FirstTestGroup, reproduction)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = false; // test cell
  world.space[0][0] = true;  // neighbours
  world.space[1][0] = true;
  world.space[2][0] = true;

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==true);
  CHECK(world.space[5][5]==false);
}


// an empty cell with 3 neighbours comes alive
TEST(FirstTestGroup, noReproduction)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = true; // test cell
  world.space[0][0] = true; // neighbours
  world.space[1][0] = true;
  world.space[2][0] = true;

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==false);
}


// a cell with exactly 2 neighbours remains the same
TEST(FirstTestGroup, stasisAlive)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = true; // test cell
  world.space[0][0] = true; // neighbours
  world.space[1][0] = true;

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==true);
}


// a cell with exactly 2 neighbours remains the same
TEST(FirstTestGroup, stasisDead)
{
  // given
  World world;
  init_world(&world);

  world.space[1][1] = false; // test cell
  world.space[0][0] = true;  // neighbours
  world.space[1][0] = true;

  // when
  next_world(&world);

  // then
  CHECK(world.space[1][1]==false);
}


// world does wrap around
TEST(FirstTestGroup, wrapAround)
{
  // given

  // when

  // then
  CHECK(xWrap(-1) == WORLD_SIZE_X - 1);
  CHECK(yWrap(-3) == WORLD_SIZE_Y - 3);
}

//------------------------------------------------------------------------------

int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}

