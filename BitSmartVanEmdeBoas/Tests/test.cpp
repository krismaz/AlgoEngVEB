#include "pch.h"

#include "gtest/gtest.h"

#include "stdSetWrapper.h"

#define MAX_SIZE ((1 << 24) - 1)

template <typename T>
class PredecessorTest : public ::testing::Test {
public:
	T * Target;
	PredecessorTest() {
		Target = new T();
		this->Target->Insert(0);
		this->Target->Insert(1);
		this->Target->Insert(2);
		this->Target->Insert(100);
		this->Target->Insert(10000);
		this->Target->Insert(MAX_SIZE / 100);
		this->Target->Insert(MAX_SIZE / 10);
		this->Target->Insert(MAX_SIZE / 2);
		this->Target->Insert(MAX_SIZE - 1);
	}
	~PredecessorTest() {
		delete Target;
	}
};

typedef ::testing::Types<stdSetWrapper> TargetTypes;
TYPED_TEST_CASE(PredecessorTest, TargetTypes);

TYPED_TEST(PredecessorTest, InsertDoesNotCrash) {
	EXPECT_TRUE(true);
}

TYPED_TEST(PredecessorTest, Min) {
	EXPECT_EQ(this->Target->Min(), 0);
}

TYPED_TEST(PredecessorTest, Max) {
	EXPECT_EQ(this->Target->Max(), MAX_SIZE - 1);
}

TYPED_TEST(PredecessorTest, ContainsPositive) {
	EXPECT_TRUE(this->Target->Contains(0));
	EXPECT_TRUE(this->Target->Contains(1));
	EXPECT_TRUE(this->Target->Contains(2));
	EXPECT_TRUE(this->Target->Contains(100));
	EXPECT_TRUE(this->Target->Contains(10000));
	EXPECT_TRUE(this->Target->Contains(MAX_SIZE / 100));
	EXPECT_TRUE(this->Target->Contains(MAX_SIZE / 10));
	EXPECT_TRUE(this->Target->Contains(MAX_SIZE / 2));
	EXPECT_TRUE(this->Target->Contains(MAX_SIZE - 1));
}

TYPED_TEST(PredecessorTest, ContainsNegative) {
	EXPECT_FALSE(this->Target->Contains(4));
	EXPECT_FALSE(this->Target->Contains(7));
	EXPECT_FALSE(this->Target->Contains(8));
	EXPECT_FALSE(this->Target->Contains(108));
	EXPECT_FALSE(this->Target->Contains(20000));
	EXPECT_FALSE(this->Target->Contains(MAX_SIZE / 101));
	EXPECT_FALSE(this->Target->Contains(MAX_SIZE / 9));
	EXPECT_FALSE(this->Target->Contains(MAX_SIZE / 21));
	EXPECT_FALSE(this->Target->Contains(MAX_SIZE - 2));
}

TYPED_TEST(PredecessorTest, Predecessor) {
	EXPECT_EQ(this->Target->Predecessor(1), 0);
	EXPECT_EQ(this->Target->Predecessor(2), 1);
	EXPECT_EQ(this->Target->Predecessor(5), 2);
	EXPECT_EQ(this->Target->Predecessor(7), 2);
	EXPECT_EQ(this->Target->Predecessor(200), 100);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 3), MAX_SIZE / 10);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 2), MAX_SIZE / 10);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 2 + 1), MAX_SIZE / 2);
}

TYPED_TEST(PredecessorTest, Successor) {
	EXPECT_EQ(this->Target->Successor(0), 1);
	EXPECT_EQ(this->Target->Successor(1), 2);
	EXPECT_EQ(this->Target->Successor(2), 100);
	EXPECT_EQ(this->Target->Successor(7), 100);
	EXPECT_EQ(this->Target->Successor(200), 10000);
	EXPECT_EQ(this->Target->Successor(MAX_SIZE / 3), MAX_SIZE / 2);
	EXPECT_EQ(this->Target->Successor(MAX_SIZE / 2), MAX_SIZE - 1);
}

TYPED_TEST(PredecessorTest, Insert) {
	this->Target->Insert(8);
	this->Target->Insert(200);
	this->Target->Insert(MAX_SIZE / 4);

	EXPECT_TRUE(this->Target->Contains(8));
	EXPECT_TRUE(this->Target->Contains(200));
	EXPECT_TRUE(this->Target->Contains(MAX_SIZE / 4));

	EXPECT_EQ(this->Target->Predecessor(10), 8);
	EXPECT_EQ(this->Target->Predecessor(1000), 200);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 2), MAX_SIZE / 4);

	EXPECT_EQ(this->Target->Successor(7), 8);
	EXPECT_EQ(this->Target->Successor(110), 200);
	EXPECT_EQ(this->Target->Successor(MAX_SIZE / 10), MAX_SIZE / 4);
}


TYPED_TEST(PredecessorTest, Delete) {
	this->Target->Delete(1);
	this->Target->Delete(10000);
	this->Target->Delete(MAX_SIZE / 10);

	EXPECT_FALSE(this->Target->Contains(1));
	EXPECT_FALSE(this->Target->Contains(1000));
	EXPECT_FALSE(this->Target->Contains(MAX_SIZE / 10));

	EXPECT_EQ(this->Target->Predecessor(2), 0);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 100), 100);
	EXPECT_EQ(this->Target->Predecessor(MAX_SIZE / 2), MAX_SIZE / 100);

	EXPECT_EQ(this->Target->Successor(0), 2);
	EXPECT_EQ(this->Target->Successor(100), MAX_SIZE / 100);
	EXPECT_EQ(this->Target->Successor(MAX_SIZE / 100), MAX_SIZE / 2);
}