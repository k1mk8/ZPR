#include "../include/Game.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(GameTest, createGame) {
  Game game(10);
  ASSERT_EQ(game.getEndGame(), false);
}

TEST(GameTest, running) {
  Game game(10);
  ASSERT_EQ(game.running(), true);
}

TEST(GameTest, getTotalPoints) {
  Game game(10);
  ASSERT_EQ(game.getTotalPoints(), 10);
}

TEST(GameTest, calculateTotalPoints) {
  Game game(10);
  game.calculateTotalPoints();
  ASSERT_EQ(game.getTotalPoints(), 10);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}