#include "../include/Button.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(ButtonTest, getButton)
{
    Button button = Button(Vector2f(125, 60), Color::Green, Vector2f(800, 750));
    RectangleShape shape = button.getButton();
    ASSERT_EQ(shape.getSize(), Vector2f(125, 60));
}

TEST(ButtonTest, createButton)
{
    Button button = Button(Vector2f(125, 60), Color::Green, Vector2f(800, 750));
    RectangleShape shape = button.getButton();
    ASSERT_EQ(shape.getSize(), Vector2f(125, 60));
    ASSERT_EQ(shape.getFillColor(), Color::Green);
    ASSERT_EQ(shape.getPosition(), Vector2f(800, 750));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}