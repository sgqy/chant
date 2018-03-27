#include "pch.h"
#include "../libbase/base4096.h"

const uint16_t input[] = { 0x2d8, 0xf47, 0x5e9, 0x035, 0xfce, 0xc7c };
const int input_sz = sizeof(input) / 2;
char output[300] = { 0 };
const char answer[] = { 0x2d, 0x8f, 0x47, 0x5e, 0x90, 0x35, 0xfc, 0xec, 0x7c, 0x00 };
const int answer_sz = 9;


TEST(base4kdec, Invalid1)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xf001, 0x022, 0x8cd };
	int len = base4096_decode(inputA, 3, output, sizeof(output));
	const char ansA[] = { 0 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ansA, output, 0));
}
TEST(base4kdec, Invalid2)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xf002, 0x022, 0x8cd };
	int len = base4096_decode(inputA, 3, output, sizeof(output));
	const char ansA[] = { 0 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ansA, output, 0));
}
TEST(base4kdec, Invalid3)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0x07ef, 0xf002, 0x022, 0x8cd };
	int len = base4096_decode(inputA, 4, output, sizeof(output));
	const char ansA[] = { 0 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ansA, output, 0));
}
TEST(base4kdec, CutC)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0x07f2, 0x022, 0x8cd, 0x594, 0xf001 };
	int len = base4096_decode(inputA, 5, output, sizeof(output));
	const char ansA[] = { 0x7f, 0x20, 0x22, 0x8c, 0xd5 };
	EXPECT_EQ(5, len);
	EXPECT_EQ(0, memcmp(ansA, output, 5));
}
TEST(base4kdec, CutB0)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022 };
	int len = base4096_decode(inputA, 2, output, 0);
	const char ansA[] = { 0xe4, 0x70, 0x22 };
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(ansA, output, 0));
}
TEST(base4kdec, CutB1)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022 };
	int len = base4096_decode(inputA, 2, output, 1);
	const char ansA[] = { 0xe4, 0x70, 0x22 };
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(ansA, output, 1));
}
TEST(base4kdec, CutB2)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022 };
	int len = base4096_decode(inputA, 2, output, 2);
	const char ansA[] = { 0xe4, 0x70, 0x22 };
	EXPECT_EQ(2, len);
	EXPECT_EQ(0, memcmp(ansA, output, 2));
}
TEST(base4kdec, CutB3)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022 };
	int len = base4096_decode(inputA, 2, output, 3);
	const char ansA[] = { 0xe4, 0x70, 0x22 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ansA, output, 3));
}
TEST(base4kdec, CutB)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022 };
	int len = base4096_decode(inputA, 2, output, sizeof(output));
	const char ansA[] = { 0xe4, 0x70, 0x22 };
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kdec, CutA)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47 };
	int len = base4096_decode(inputA, 1, output, sizeof(output));
	const char ansA[] = { 0xe4 };
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kdec, CutAL)
{
	memset(output, 0, sizeof(output));
	const uint16_t inputA[] = { 0xe47, 0x022, 0x8cd };
	int len = base4096_decode(inputA, 3, output, sizeof(output));
	const char ansA[] = { 0xe4, 0x70, 0x22, 0x8c };
	EXPECT_EQ(4, len);
	EXPECT_EQ(0, memcmp(ansA, output, sizeof(ansA)));
}
TEST(base4kdec, Cut0)
{
	memset(output, 0, sizeof(output));
	int len = base4096_decode(input, input_sz, output, 0);
	EXPECT_EQ(0, len);
	EXPECT_EQ(0, memcmp(answer, output, 0));
}
TEST(base4kdec, Cut1)
{
	memset(output, 0, sizeof(output));
	int len = base4096_decode(input, input_sz, output, 1);
	EXPECT_EQ(1, len);
	EXPECT_EQ(0, memcmp(answer, output, 1));
}
TEST(base4kdec, Cut2)
{
	memset(output, 0, sizeof(output));
	int len = base4096_decode(input, input_sz, output, 2);
	EXPECT_EQ(2, len);
	EXPECT_EQ(0, memcmp(answer, output, 2));
}
TEST(base4kdec, Cut3)
{
	memset(output, 0, sizeof(output));
	int len = base4096_decode(input, input_sz, output, 3);
	EXPECT_EQ(3, len);
	EXPECT_EQ(0, memcmp(answer, output, 3));
}
TEST(base4kdec, Null)
{
	EXPECT_EQ(0, base4096_decode(0, 0, 0, 0));
}
TEST(base4kdec, Null0)
{
	EXPECT_EQ(0, base4096_decode(0, input_sz, output, sizeof(output)));
}
TEST(base4kdec, Null1)
{
	EXPECT_EQ(0, base4096_decode(input, 0, output, sizeof(output)));
}
TEST(base4kdec, Null2)
{
	EXPECT_EQ(0, base4096_decode(input, input_sz, 0, answer_sz));
}
TEST(base4kdec, Null3)
{
	EXPECT_EQ(0, base4096_decode(input, input_sz, output, 0));
}
TEST(base4kdec, Negative)
{
	EXPECT_EQ(0, base4096_decode(input, -1, output, -1));
}
TEST(base4kdec, Negative1)
{
	EXPECT_EQ(0, base4096_decode(input, -1, output, sizeof(output)));
	EXPECT_EQ(0, base4096_decode(input, -2, output, sizeof(output)));
	EXPECT_EQ(0, base4096_decode(input, -175, output, sizeof(output)));
}
TEST(base4kdec, Negative2)
{
	EXPECT_EQ(0, base4096_decode(input, input_sz, output, -1));
	EXPECT_EQ(0, base4096_decode(input, input_sz, output, -2));
	EXPECT_EQ(0, base4096_decode(input, input_sz, output, -175));
}
TEST(base4kdec, Full)
{
	memset(output, 0, sizeof(output));
	int len = base4096_decode(input, input_sz, output, sizeof(output));
	EXPECT_EQ(answer_sz, len);
	EXPECT_EQ(0, memcmp(answer, output, len));
}
