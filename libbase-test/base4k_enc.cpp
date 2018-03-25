#include "pch.h"
#include "../libbase/base4096.h"

const char input[] = { 0x2d, 0x8f, 0x47, 0x5e, 0x90, 0x35, 0xfc, 0xec, 0x00 };
const int input_sz = sizeof(input);
uint16_t output[300] = { 0 };
const uint16_t answer[] = { 0x2d8, 0xf47, 0x5e9, 0x035, 0xfce, 0xc00, 0 };
const int answer_sz = 6;

TEST(base4kenc, CutD0)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x2f, 0xec };
	int len = base4096_encode(inputA, sizeof(inputA), output, 0);
	const uint16_t ansA[] = { 0x2fe, 0xc00, 0xF001 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ansA, output, 0));
}
TEST(base4kenc, CutD1)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x2f, 0xec };
	int len = base4096_encode(inputA, sizeof(inputA), output, 1);
	const uint16_t ansA[] = { 0x2fe, 0xc00, 0xF001 };
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(ansA, output, 2));
}
TEST(base4kenc, CutD2)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x2f, 0xec };
	int len = base4096_encode(inputA, sizeof(inputA), output, 2);
	const uint16_t ansA[] = { 0x2fe, 0xc00, 0xF001 };
	EXPECT_EQ(2, len);
	EXPECT_EQ(0, memcmp(ansA, output, 4));
}
TEST(base4kenc, CutD3)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x2f, 0xec };
	int len = base4096_encode(inputA, sizeof(inputA), output, 3);
	const uint16_t ansA[] = { 0x2fe, 0xc00, 0xF001 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ansA, output, 6));
}
TEST(base4kenc, CutD)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x2f, 0xec };
	int len = base4096_encode(inputA, sizeof(inputA), output, sizeof(output));
	const uint16_t ansA[] = { 0x2fe, 0xc00, 0xF001 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kenc, CutC)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x00, 0x00, 0x00 };
	int len = base4096_encode(inputA, sizeof(inputA), output, sizeof(output));
	const uint16_t ansA[] = { 0x000, 0x000 };
	EXPECT_EQ(2, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kenc, CutB)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x00, 0x00 };
	int len = base4096_encode(inputA, sizeof(inputA), output, sizeof(output));
	const uint16_t ansA[] = { 0x000, 0x000, 0xF001 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kenc, CutA)
{
	memset(output, 0, sizeof(output));
	const char inputA[] = { 0x00 };
	int len = base4096_encode(inputA, sizeof(inputA), output, sizeof(output));
	const uint16_t ansA[] = { 0x000 };
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kenc, Cut0)
{
	memset(output, 0, sizeof(output));
	int len = base4096_encode(input, input_sz, output, 0);
	const uint16_t ans0[] = { 0 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ans0, output, sizeof(ans0)));
}
TEST(base4kenc, Cut1)
{
	memset(output, 0, sizeof(output));
	int len = base4096_encode(input, input_sz, output, 1);
	const uint16_t ans0[] = { 0x2d8 };
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(ans0, output, sizeof(ans0)));
}
TEST(base4kenc, Cut2)
{
	memset(output, 0, sizeof(output));
	int len = base4096_encode(input, input_sz, output, 2);
	const uint16_t ans0[] = { 0x2d8, 0xf47 };
	EXPECT_EQ(2, len);
	EXPECT_EQ(0, memcmp(ans0, output, sizeof(ans0)));
}
TEST(base4kenc, Cut3)
{
	memset(output, 0, sizeof(output));
	int len = base4096_encode(input, input_sz, output, 3);
	const uint16_t ans0[] = { 0x2d8, 0xf47, 0x5e9 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ans0, output, sizeof(ans0)));
}
TEST(base4kenc, Null)
{
	EXPECT_EQ(0, base4096_encode(0, 0, 0, 0));
}
TEST(base4kenc, Null0)
{
	EXPECT_EQ(0, base4096_encode(0, input_sz, output, sizeof(output)));
}
TEST(base4kenc, Null1)
{
	EXPECT_EQ(0, base4096_encode(input, 0, output, sizeof(output)));
}
TEST(base4kenc, Null2)
{
	EXPECT_EQ(0, base4096_encode(input, input_sz, 0, answer_sz));
}
TEST(base4kenc, Null3)
{
	EXPECT_EQ(0, base4096_encode(input, input_sz, output, 0));
}
TEST(base4kenc, Negative)
{
	EXPECT_EQ(0, base4096_encode(input, -1, output, -1));
}
TEST(base4kenc, Negative1)
{
	EXPECT_EQ(0, base4096_encode(input, -1, output, sizeof(output)));
	EXPECT_EQ(0, base4096_encode(input, -2, output, sizeof(output)));
	EXPECT_EQ(0, base4096_encode(input, -175, output, sizeof(output)));
}
TEST(base4kenc, Negative2)
{
	EXPECT_EQ(0, base4096_encode(input, input_sz, output, -1));
	EXPECT_EQ(0, base4096_encode(input, input_sz, output, -2));
	EXPECT_EQ(0, base4096_encode(input, input_sz, output, -175));
}
TEST(base4kenc, Full)
{
	memset(output, 0, sizeof(output));
	int len = base4096_encode(input, input_sz, output, sizeof(output));
	EXPECT_EQ(answer_sz, len);
	EXPECT_EQ(0, memcmp(answer, output, len * 2));
}
