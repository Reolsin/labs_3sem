#include "pch.h"
#include "../Library_dynamic/Stack.h"

namespace Stack_dynamic {

	TEST(StructConstructor, Default) {
		Cell c;
		EXPECT_EQ(0, c.v);
		ASSERT_STREQ("", c.str);
	}

	TEST(StructConstructor, Init) {
		Cell c1(1);
		Cell c2(2, "string");
		EXPECT_EQ(1, c1.v);
		ASSERT_STREQ("", c1.str);
		EXPECT_EQ(2, c2.v);
		ASSERT_STREQ("string", c2.str);
	}

	TEST(StructConstructor, Copy) {
		Cell c1(2, "string");
		Cell c2 = c1;
		EXPECT_EQ(c1.v, c2.v);
		ASSERT_STREQ(c1.str, c2.str);
	}

	TEST(StructConstructor, Move) {
		Cell c1 = Cell(2, "string");
		EXPECT_EQ(2, c1.v);
		ASSERT_STREQ("string", c1.str);
	}

	TEST(StructOperators, Copy) {
		Cell c1(2, "string");
		Cell c2;
		c2 = c1;
		EXPECT_EQ(c1.v, c2.v);
		ASSERT_STREQ(c1.str, c2.str);
	}

	TEST(StructOperators, Move) {
		Cell c1;
		c1 = Cell(2, "string");
		EXPECT_EQ(2, c1.v);
		ASSERT_STREQ("string", c1.str);
	}

	TEST(ClassConstructor, Default) {
		Stack S;
		EXPECT_EQ(10, S.getSZ());
		EXPECT_EQ(0, S.gettop());
	}

	TEST(ClassConstructor, Init) {
		Cell el;

		Cell c1[3]{ {1, "string1"}, {2, "string2"}, {3, "string3" } };
		Stack S1(c1, 3);
		EXPECT_EQ(10, S1.getSZ());
		EXPECT_EQ(3, S1.gettop());
		S1(el);
		EXPECT_EQ(c1[2].v, el.v);
		ASSERT_STREQ(c1[2].str, el.str);
		S1(el);
		EXPECT_EQ(c1[1].v, el.v);
		ASSERT_STREQ(c1[1].str, el.str);
		S1(el);
		EXPECT_EQ(c1[0].v, el.v);
		ASSERT_STREQ(c1[0].str, el.str);

		Cell c2[12];
		Stack S2(c2, 12);
		EXPECT_EQ(20, S2.getSZ());
		EXPECT_EQ(12, S2.gettop());
		while (S2.not_empty()) {
			S2(el);
			EXPECT_EQ(0, el.v);
			ASSERT_STREQ("", el.str);
		}
	}

	TEST(ClassConstructor, InitException) {
		Cell c[3]{ {1, "string1"}, {2, "string2"}, {3, "string3" } };
		ASSERT_ANY_THROW(Stack S3(c, -1));
	}

	TEST(ClassConstructor, Copy) {
		Cell* c = &Cell(2, "string");
		Stack S1(c, 1);
		Stack S2 = S1;
		Cell el1, el2;
		EXPECT_EQ(S1.gettop(), S2.gettop());
		EXPECT_EQ(S1.getSZ(), S2.getSZ());
		S1(el1);
		S2(el2);
		EXPECT_EQ(el1.v, el2.v);
		ASSERT_STREQ(el1.str, el2.str);
	}

	TEST(ClassConstructor, Move) {
		Cell c(2, "string");
		Stack S1 = Stack(&c,1);
		Cell el;
		EXPECT_EQ(S1.gettop(), 1);
		EXPECT_EQ(S1.getSZ(), 10);
		S1(el);
		EXPECT_EQ(el.v, 2);
		ASSERT_STREQ(el.str, "string");
	}

	TEST(ClassOperators, copy) {
		Cell el;
		Cell c[12];
		Stack S1(c, 12);
		Stack S2;
		S2 = S1;
		EXPECT_EQ(20, S2.getSZ());
		EXPECT_EQ(12, S2.gettop());
		while (S2.not_empty()) {
			S2(el);
			EXPECT_EQ(0, el.v);
			ASSERT_STREQ("", el.str);
		}
	}

	TEST(ClassOperators, move) {
		Cell el;
		Cell c[12];
		Stack S;
		S = Stack(c, 12);
		EXPECT_EQ(20, S.getSZ());
		EXPECT_EQ(12, S.gettop());
		while (S.not_empty()) {
			S(el);
			EXPECT_EQ(0, el.v);
			ASSERT_STREQ("", el.str);
		}
	}

	TEST(ClassOperators, pop_push) {
		Stack S;
		Cell c(11, "str");
		Cell el;
		S += c;
		S(el);
		EXPECT_EQ(el.v, c.v);
		ASSERT_STREQ(el.str, c.str);
	}

	TEST(ClassOperators, pop_pushExceptions) {
		Stack S;
		Cell el;
		ASSERT_ANY_THROW(S(el));
	}

	TEST(ClassGetters, Status) {
		Stack S;
		Cell c;
		EXPECT_EQ(S.not_empty(), 0);
		EXPECT_EQ(S.is_full(), 0);
		S += c;
		EXPECT_EQ(S.not_empty(), 1);
		EXPECT_EQ(S.is_full(), 0);
		int SZ = S.getSZ();
		int i = 1;
		while (i++ < SZ)
			S += c;
		EXPECT_EQ(S.not_empty(), 1);
		EXPECT_EQ(S.is_full(), 1);
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
