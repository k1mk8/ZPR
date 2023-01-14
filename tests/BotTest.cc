#include "../include/Bot.h"
#include "../include/StaticPoints.h"
#include <gtest/gtest.h>
#include <typeinfo>
using namespace sf;

TEST(BotTest, createBot) {
  Bot bot = Bot(5, 10, 10, 10);
  ASSERT_EQ(bot.getShape().getFillColor(), Color::Black);
  ASSERT_EQ(bot.getType(), 4);
}

TEST(BotTest, getDirection) {
  Bot bot = Bot(5, 10, 10, 10);
  float xdiff = 20 - 5;
  float ydiff = 20 - 10;
  ASSERT_EQ(bot.getDirection(20, 20), atan2(-ydiff, xdiff));
}

TEST(BotTest, searchNearby) {
  StaticPoints point = StaticPoints(FOOD, 20, 20);
  std::vector<StaticPoints> points;
  points.push_back(point);
  Bot bot = Bot(5, 10, 30, 10);
  Bot bot2 = Bot(5, 10, 30, 10);
  float dirc = bot.getDirection(20, 20);
  bot.getShape().move(cos(dirc) * bot.getSpeed(), -sin(dirc) * bot.getSpeed());
  bot2.searchNearby(points, 500);
  ASSERT_EQ(bot2.getPlayerPostion().x, bot.getPlayerPostion().x);
  ASSERT_EQ(bot2.getPlayerPostion().y, bot.getPlayerPostion().y);
}

TEST(BotTest, moveBot) {
  Bot bot = Bot(20, 20, 80, 10);
  std::vector<Bot> bots;
  std::vector<Player> players;
  std::vector<StaticPoints> points;
  bots.push_back(bot);
  Bot bot1 = Bot(5, 10, 30, 10);
  Bot bot2 = Bot(5, 10, 30, 10);
  float dirc = bot1.getDirection(20, 20);
  bot1.getShape().move(-cos(dirc) * bot1.getSpeed(),
                       sin(dirc) * bot1.getSpeed());
  bot2.moveBot(bots, players, points);
  ASSERT_EQ(bot2.getPlayerPostion().x, bot1.getPlayerPostion().x);
  ASSERT_EQ(bot2.getPlayerPostion().y, bot1.getPlayerPostion().y);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}