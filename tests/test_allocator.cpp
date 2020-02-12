#include "custom_forward_list.h"

#include <gtest/gtest.h>


TEST(EMPTY_CUSTOM_FORWARD_LIST, EMPTY)
{
    // Arrange, Act
    custom_forward_list<int> cfl;

    // Assert
    ASSERT_TRUE(cfl.empty());
}


TEST(EMPTY_CUSTOM_FORWARD_LIST, SIZE)
{
    // Arrange, Act
    custom_forward_list<int> cfl;

    // Assert
    ASSERT_EQ(cfl.size(), 0);
}

TEST(EMPTY_CUSTOM_FORWARD_LIST, ITERATORS)
{
    // Arrange, Act
    custom_forward_list<int> cfl;

    // Assert
    ASSERT_TRUE(cfl.begin() == cfl.end());
}

TEST(EMPTY_CUSTOM_FORWARD_LIST, FRONT)
{
    // Arrang, Act
    custom_forward_list<int> cfl;
    bool handle_exception = false;

    //Assert
    try{
        cfl.front();
    }
    catch(const std::range_error& ex) {
        handle_exception = true;
    }

    ASSERT_TRUE(handle_exception);
}

TEST(FILLED_CUSTOM_FORWARD_LIST, PUSH_FRONT_AND_EMPTY)
{
    // Arrange
    custom_forward_list<std::size_t> cfl;

    // Act
    std::size_t number = 5;
    for(std::size_t i = 0; i < number; ++i)
        cfl.push_front(i);

    // Assert
    ASSERT_FALSE(cfl.empty());
}

TEST(FILLED_CUSTOM_FORWARD_LIST, PUSH_FRONT_AND_SIZE)
{
    // Arrange
    custom_forward_list<std::size_t> cfl;

    // Act
    std::size_t number = 5;
    for(std::size_t i = 0; i < number; ++i)
        cfl.push_front(i);

    // Assert
    ASSERT_EQ(cfl.size(), number);
}

TEST(FILLED_CUSTOM_FORWARD_LIST, PUSH_FRONT_AND_FRONT)
{
    // Arrange
    custom_forward_list<std::size_t> cfl;

    // Act
    std::size_t value = 5;
    cfl.push_front(value);

    // Assert
    ASSERT_EQ(cfl.front(), value);
}

TEST(FILLED_CUSTOM_FORWARD_LIST, PUSH_FRONT_AND_POP_FRONT)
{
    // Arrange
    custom_forward_list<std::size_t> cfl;
    std::size_t number = 5;
    for(std::size_t i = 0; i < number; ++i)
        cfl.push_front(i);

    // Assert
    for(int i = 4; i >= 0; --i)
    {
        cfl.pop_front();
        ASSERT_EQ(cfl.size(), i);
    }
}

TEST(FILLED_CUSTOM_FORWARD_LIST, PUSH_FRONT_AND_ITERATORS)
{
    // Arrange
    custom_forward_list<std::size_t> cfl;
    for(std::size_t i = 5; i > 0; --i)
        cfl.push_front(i);

    // Act Assert
    std::size_t value = 1;
    for(auto it = cfl.begin(); it != cfl.end(); ++it, ++value)
        ASSERT_EQ(*it, value);
}




