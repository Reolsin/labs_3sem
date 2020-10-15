#include "pch.h"
#include "../Library_static/Stack.h"

namespace Stack_static {

	TEST(StructConstructor, Default) {
		Cell c;
		EXPECT_EQ(10, c.len);
		EXPECT_EQ(0, c.v);
		ASSERT_STREQ("", c.str);
	}

	TEST(StructConstructor, Init) {
		Cell c1(1);
		Cell c2(2, "string");
		EXPECT_EQ(1, c1.v);
		EXPECT_EQ(2, c2.v);
		ASSERT_STREQ("string", c2.str);
	}

	TEST(StructConstructor, InitException) {
		ASSERT_ANY_THROW(Cell c3(1, "string with len > Cell.len"));
	}

	TEST(ClassConstructor, Default) {
		Stack S;
		EXPECT_EQ(10, S.getSZ());
		EXPECT_EQ(0, S.gettop());
		EXPECT_TRUE(true);
	}

	TEST(ClassConstructor, Init) {
		Cell c[3]{ {1, "string1"}, {2, "string2"}, {3, "string3" } };
		Cell el;
		Stack S1(c, 3);
		EXPECT_EQ(10, S1.getSZ());
		EXPECT_EQ(3, S1.gettop());
		S1(el);
		EXPECT_EQ(c[2].v, el.v);
		ASSERT_STREQ(c[2].str, el.str);
		S1(el);
		EXPECT_EQ(c[1].v, el.v);
		ASSERT_STREQ(c[1].str, el.str);
		S1(el);
		EXPECT_EQ(c[0].v, el.v);
		ASSERT_STREQ(c[0].str, el.str);
	}

	TEST(ClassConstructor, InitException) {
		Cell c[3]{ {1, "string1"}, {2, "string2"}, {3, "string3" } };
		ASSERT_ANY_THROW(Stack S2(c, 11));
		ASSERT_ANY_THROW(Stack S3(c, -1));
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

	TEST(ClassOperators, Exceptions) {
		Stack S;
		Cell c(11, "str");
		Cell el;
		ASSERT_ANY_THROW(S(el));
		int SZ = S.getSZ();
		int i = 0;
		while (i++ < SZ)
			S += c;
		ASSERT_ANY_THROW(S += c);
	}

	TEST(ClassGetters, Status) {
		Stack S;
		Cell c;
		EXPECT_EQ(S.not_empty(), 0);
		EXPECT_EQ(S.not_full(), 1);
		S += c;
		EXPECT_EQ(S.not_empty(), 1);
		EXPECT_EQ(S.not_full(), 1);
		int SZ = S.getSZ();
		int i = 1;
		while (i++ < SZ)
			S += c;
		EXPECT_EQ(S.not_empty(), 1);
		EXPECT_EQ(S.not_full(), 0);
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
