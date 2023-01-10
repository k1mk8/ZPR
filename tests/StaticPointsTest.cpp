#include "../include/StaticPoints.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(StaticPointsTest, createStaticPointFood)
{
    vector <Player> players;
    players.push_back(Player(5,5,10));
    StaticPoints point = StaticPoints(FOOD, players);
    ASSERT_EQ(point.getMass(), 1);
    ASSERT_EQ(point.getShape().getFillColor(), Color::Blue);
    ASSERT_EQ(point.getShape().getRadius(), 5);
}

TEST(StaticPointsTest, createStaticPointSpike)
{
    vector <Player> players;
    players.push_back(Player(5,5,10));
    StaticPoints point = StaticPoints(SPIKES, players);
    ASSERT_EQ(point.getMass(), 30);
    ASSERT_EQ(point.getShape().getFillColor(), Color::Red);
    ASSERT_EQ(point.getShape().getRadius(), 30);
}

TEST(StaticPointsTest, getType)
{
    vector <Player> players;
    players.push_back(Player(5,5,10));
    StaticPoints point = StaticPoints(FOOD, players);
    ASSERT_EQ(point.getType(), FOOD);
}

TEST(StaticPointsTest, getMass)
{
    vector <Player> players;
    players.push_back(Player(5,5,10));
    StaticPoints point = StaticPoints(FOOD, players);
    ASSERT_EQ(point.getMass(), 1);
}

TEST(StaticPointsTest, eatMass)
{
    vector <Player> players;
    players.push_back(Player(5,5,10));
    StaticPoints point = StaticPoints(FOOD, players);
    point.eatMass(10);
    ASSERT_EQ(point.getMass(), 11);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}