#pragma once

#include <algorithm>
#include <forward_list>
#include <vector>

#include "../DataStructures/include/DeQue.hpp"

// ================================================
// ==============   DEQUE TESTS   =================
// ================================================

TEST(DequeTest, DequeConstructor)
{
	// Default Constructor
	DeQue<int> defaultConstructor = DeQue<int>();
	EXPECT_EQ(defaultConstructor.size(), 0);

	for (int i = 0; i < 10; ++i)
	{
		defaultConstructor.push_back(154);
	}

	// Copy Constructor
	DeQue<int>copyConstructor = DeQue<int>(defaultConstructor);
	EXPECT_EQ(defaultConstructor.size(), 10);
	auto it = copyConstructor.begin();

	// Iterator based constructor -> copies in range [first, last)
	DeQue<int>iteratorConstructor = DeQue<int>(copyConstructor.begin(), copyConstructor.end());
	auto otherIt = iteratorConstructor.begin();
	EXPECT_TRUE(it == otherIt);

	// Initializer list based constructor
	DeQue<int> initListDeque = { 0, 1, 2, 3 };
	EXPECT_EQ(initListDeque.size(), 4);
	EXPECT_TRUE(std::find(initListDeque.begin(), initListDeque.end(), 3) != initListDeque.end());
}

// Used to test push_front, push_back, pop_front and pop_back
TEST(DequeTest, PushAndPop)
{
	DeQue<int> testDeque = DeQue<int>();
	EXPECT_TRUE(testDeque.begin() == testDeque.end());

	testDeque.push_back(0);
	EXPECT_EQ(testDeque.size(), 1);
	EXPECT_EQ(*testDeque.begin(), 0);

	testDeque.push_front(-1);
	EXPECT_EQ(testDeque.size(), 2);
	EXPECT_EQ(*testDeque.begin(), -1);

	for (int i = 0; i < 10; ++i)
	{
		testDeque.push_back(i);
	}
	EXPECT_EQ(testDeque.size(), 12);
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 3) == testDeque.end());

	auto it = testDeque.begin();
	it = std::next(it);

	// Trigger a resize
	for (int i = 0; i < 100; ++i)
	{
		testDeque.push_front(i);
	}
	EXPECT_EQ(testDeque.size(), 112);
	// The find is used to confirm the resize keeps the data readable
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 99) == testDeque.end());
	// If iterator is invalidated during resize, this will blow up ( but there is no real way of checking iterator validity )
	EXPECT_EQ(*it, 0);

	// Now we pop data out of the Deque
	// First, we check the current last element
	it = testDeque.begin();
	std::advance(it, testDeque.size() - 1);
	EXPECT_EQ(*it, 9);

	// Pop back
	testDeque.pop_back();
	// Check the new final element
	it = testDeque.begin();
	std::advance(it, testDeque.size() - 1);
	EXPECT_EQ(*it, 8);

	// Pop Front
	it = testDeque.begin();
	EXPECT_EQ(*it, 99);

	testDeque.pop_front();
	it = testDeque.begin();
	EXPECT_EQ(*it, 98);
}

// Test at(), front(), back() and operator []
TEST(DequeTest, Accessors)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	EXPECT_EQ(testDeque.front(), 0);
	EXPECT_EQ(testDeque.back(), 9);
	EXPECT_EQ(testDeque.at(2), 2);
	EXPECT_EQ(testDeque[5], 5);
}

TEST(DequeTest, Resizing)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	EXPECT_EQ(testDeque.size(), 10);

	testDeque.resize(15);
	EXPECT_EQ(testDeque.size(), 15);

	testDeque.resize(5);
	EXPECT_EQ(testDeque.size(), 5);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 10) == testDeque.end());

	testDeque.resize(15, 12);
	EXPECT_EQ(testDeque.size(), 15);
	EXPECT_EQ(std::count(testDeque.begin(), testDeque.end(), 12), 10);
}

TEST(DequeTest, Insertion)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	auto it = testDeque.cbegin();
	std::advance(it, 3);
	auto returnedIt = testDeque.insert(it, 10);

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 10) == testDeque.end());
	EXPECT_EQ(*returnedIt, 10);

	// insert count values
	it = testDeque.cbegin();
	std::advance(it, 3);
	returnedIt = testDeque.insert(it, 10, 150);

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 150) == testDeque.end());
	EXPECT_EQ(*returnedIt, 150);
	returnedIt = std::find(testDeque.begin(), testDeque.end(), 10);
	EXPECT_EQ(*(--returnedIt), 150);

	// insert iter first, iter last ( bidirectional )
	std::vector<int> insertableVec = { -1, -2, -3, -4, -5 };
	it = testDeque.cbegin();
	std::advance(it, 10);
	returnedIt = testDeque.insert(it, insertableVec.begin(), insertableVec.end());

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), -3) == testDeque.end());

	// insert iter first, iter last ( non-bidirectional )
	std::forward_list<int> insertableFList = { -10, -20, -30, -40, -50 };
	it = testDeque.cbegin();
	std::advance(it, 12);
	returnedIt = testDeque.insert(it, insertableFList.begin(), insertableFList.end());

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), -30) == testDeque.end());
}