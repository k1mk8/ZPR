#include "../include/Player.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(PlayerTest, variables)
{
    Player player = Player(5,5,10);
    int mass = 10;
    float speed = 10 - (log(10) / log(4));;
    ASSERT_EQ(player.getSpeed(), speed);
    ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, makeShape)
{
    Player player = Player(5,5,10);
    auto shape = player.getShape();
    ASSERT_EQ(shape.getFillColor(), Color::Green);
    ASSERT_EQ(round(round(shape.getRadius())), round(log(10)/log(1.05)));
}

TEST(PlayerTest, calculateSpeed)
{   
    Player player = Player(5,5,10);
    player.grow(10);
    player.move();
    float speed = 10 - (log(20) / log(4));
    ASSERT_EQ(player.getSpeed(), speed);
}

TEST(PlayerTest, createPlayer)
{   
    Player player = Player(5,5,10);
    ASSERT_EQ(player.getMass(), 10);
    ASSERT_EQ(player.getPlayerPostion(), Vector2f(5,5));
}

TEST(PlayerTest, getShape)
{
    Player player = Player(5,5,10);
    CircleShape shape;
    ASSERT_EQ(typeid(player.getShape()).name(), typeid(shape).name());
}

TEST(PlayerTest, getMass)
{
    Player player = Player(5,5,10);
    int mass = 10;
    ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, getSpeed)
{
    Player player = Player(5,5,10);
    float speed = 10 - (log(10) / log(4));
    ASSERT_EQ(player.getSpeed(), speed);
}

TEST(PlayerTest, getPlayerPosition)
{
    Player player = Player(5,5,10);
    Vector2f pos = player.getPlayerPostion();
    ASSERT_EQ(pos.x, 5);
    ASSERT_EQ(pos.y, 5);
}

TEST(PlayerTest, SplitTime)
{
    Player player = Player(5,5,10);
    clock_t split = clock();
    player.setSplitTime(split);
    ASSERT_EQ(player.getSplitTime(), split);
}

TEST(PlayerTest, setMass)
{
    Player player = Player(5,5,10);
    int mass = 5;
    player.setMass(mass);
    ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, grow)
{
    Player player = Player(5,5,10);
    int mass = 5;
    player.grow(mass);
    ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, splitMassEven)
{
    Player player = Player(5,5,30);
    player.splitMass();
    ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, splitMassOdd)
{
    Player player = Player(5,5,31);
    player.splitMass();
    ASSERT_EQ(player.getMass(), 15);
}

TEST(PlayerTest, loseMass)
{
    Player player = Player(5,5,30);
    player.loseMass();
    ASSERT_EQ(player.getMass(), 20);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}