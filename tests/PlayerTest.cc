#include "../include/Player.h"
#include <gtest/gtest.h>
#include <typeinfo>

using namespace sf;

TEST(PlayerTest, variables) {
  Player player = Player(5, 5, 10, 10);
  int mass = 10;
  float speed = 10 - (log(10) / log(4));
  ;
  ASSERT_EQ(player.getSpeed(), speed);
  ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, makeShape) {
  Player player = Player(5, 5, 10);
  auto shape = player.getShape();
  ASSERT_EQ(shape.getFillColor(), Color::Green);
  ASSERT_EQ(round(round(shape.getRadius())), round(log(10) / log(1.05) - 30));
}

TEST(PlayerTest, calculateSpeed) {
  Player player = Player(5, 5, 10, 10);
  player.grow(10);
  float speed = 10 - (log(10) / log(4));
  ASSERT_EQ(player.getSpeed(), speed);
}

TEST(PlayerTest, createPlayer) {
  Player player = Player(5, 5, 10, 10);
  ASSERT_EQ(player.getMass(), 10);
  ASSERT_EQ(player.getPlayerPostion(), Vector2f(5, 5));
  ASSERT_FLOAT_EQ(player.getSpeed(), 10 - log(10) / log(4));
  ASSERT_EQ(player.getType(), 3);
}

TEST(PlayerTest, getShape) {
  Player player = Player(5, 5, 10);
  CircleShape shape;
  ASSERT_EQ(typeid(player.getShape()).name(), typeid(shape).name());
}

TEST(PlayerTest, getMass) {
  Player player = Player(5, 5, 10);
  int mass = 10;
  ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, getStartingSpeed) {
  Player player = Player(5, 5, 10, 10);
  ASSERT_EQ(player.getStartingSpeed(), 10);
}

TEST(PlayerTest, getRadius) {
  Player player = Player(5, 5, 10, 10);
  ASSERT_FLOAT_EQ(player.getRadius(), log(10) / log(1.05) - 30);
}

TEST(PlayerTest, getSetType) {
  Player player = Player(5, 5, 10, 10);
  player.setType(5);
  ASSERT_EQ(player.getType(), 5);
}

TEST(PlayerTest, getSpeed) {
  Player player = Player(5, 5, 10);
  float speed = 10 - (log(10) / log(4));
  ASSERT_EQ(player.getSpeed(), speed);
}

TEST(PlayerTest, getPlayerPosition) {
  Player player = Player(5, 5, 10);
  Vector2f pos = player.getPlayerPostion();
  ASSERT_EQ(pos.x, 5);
  ASSERT_EQ(pos.y, 5);
}

TEST(PlayerTest, getSetSplitTime) {
  Player player = Player(5, 5, 10);
  clock_t split = clock();
  player.setSplitTime(split);
  ASSERT_EQ(player.getSplitTime(), split);
}

TEST(PlayerTest, setMass) {
  Player player = Player(5, 5, 10);
  int mass = 5;
  player.setMass(mass);
  ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, connect) {
  Player player = Player(5, 5, 10, 10);
  Player player2 = Player(5, 5, 10, 10);
  std::vector<Player> players;
  players.push_back(player);
  players.push_back(player2);
  players[0].setSplitTime(clock() - 100000000);
  player.connect(players);
  ASSERT_EQ(players[0].getMass(), 20);
  ASSERT_EQ(players.size(), 1);
}

TEST(PlayerTest, grow) {
  Player player = Player(5, 5, 10);
  int mass = 5;
  player.grow(mass);
  ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, splitMassEven) {
  Player player = Player(5, 5, 30);
  player.splitMass();
  ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, splitMassOdd) {
  Player player = Player(5, 5, 31);
  player.splitMass();
  ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, splitBySpike) {
  Player player = Player(5, 5, 40);
  std::vector<Player> players;
  players.push_back(player);
  player.splitBySpike(players);
  ASSERT_EQ((int)players.size(), 4);
  ASSERT_EQ(player.getMass(), 10);
  ASSERT_EQ(players[1].getMass(), 10);
  ASSERT_EQ(player.getPlayerPostion().x, 5);
}

TEST(PlayerTest, checkMapColission) {
  Player player = Player(-4900, 0, 31);
  player.checkMapCollision();
  ASSERT_EQ(player.getPlayerPostion().x, -4770);
}

TEST(PlayerTest, loseMass) {
  Player player = Player(5, 5, 30);
  player.loseMass();
  ASSERT_EQ(player.getMass(), 20);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}