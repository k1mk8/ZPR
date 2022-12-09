#include "../include/Player.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(PlayerTest, variables)
{
    Player player = Player(5,5,10);
    float speed = 5.f;
    int mass = 10;
    ASSERT_EQ(player.getSpeed(), speed);
    ASSERT_EQ(player.getMass(), mass);
}

TEST(PlayerTest, makeShape)
{
    Player player = Player(5,5,10);
    auto shape = player.getShape();
    ASSERT_EQ(shape.getFillColor(), Color::Green);
    ASSERT_EQ(shape.getRadius(), 10);
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
    float speed = 5.f;
    ASSERT_EQ(player.getSpeed(), speed);
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
    ASSERT_EQ(player.getShape().getRadius(), 15);
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