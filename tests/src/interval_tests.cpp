#include <gtest/gtest.h>
#include <interval/interval.h>
#include <user_literals/user_literals.h>
#include <utils/utils.h>

class IntervalTest : public ::testing::Test
{
   protected:
    using IntervalT = interval::Interval<interval::Min<-1>, interval::Max<2>>;
    IntervalT interval;
    static constexpr auto inside = utils::make_array(-1, 0, 1, 2);
    static constexpr auto below = utils::make_array(-2, -3, -10, -100);
    static constexpr auto above = utils::make_array(3, 4, 5, 10, 100);
    static constexpr auto outside = utils::concatenate_arrays(below, above);
};

TEST_F(IntervalTest, MinMax)
{
    ASSERT_EQ(interval.kMin, -1);
    ASSERT_EQ(interval.kMax, 2);
}

TEST_F(IntervalTest, MaxIndex)
{
    static_assert(IntervalT::kMaxIndex == 3, "Invalid kMaxIndex");
}

TEST_F(IntervalTest, Contains)
{
    for (const auto value: outside)
    {
        ASSERT_FALSE(interval.contains(value));
    }

    for (const auto value: inside)
    {
        ASSERT_TRUE(interval.contains(value));
    }
}

TEST_F(IntervalTest, Location)
{
    for (const auto value: below)
    {
        ASSERT_EQ(interval.location(value),
                  interval::eIntervalLocation::kBelow);
    }

    for (const auto value: above)
    {
        ASSERT_EQ(interval.location(value),
                  interval::eIntervalLocation::kAbove);
    }

    for (const auto value: inside)
    {
        ASSERT_EQ(interval.location(value),
                  interval::eIntervalLocation::kInside);
    }
}

TEST(IntervalSigned, MaxIndexTest1)
{
    using IntT = int16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::min();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 0_u16, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalSigned, MaxIndexTest2)
{
    using IntT = int16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::min() + 1_i16;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 1_u16, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest3)
{
    using IntT = int16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::min() + 2_i16;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 2_u16, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest4)
{
    using IntT = int16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = 0_i16;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(
        IntervalT::kMaxIndex == std::numeric_limits<IntT>::max() + 1_u16,
        "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest5)
{
    using IntT = int16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(
        IntervalT::kMaxIndex == std::numeric_limits<IntervalT::IndexT>::max(),
        "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest6)
{
    using IntT = int8_t;
    constexpr IntT kMin = -10_i8;
    constexpr IntT kMax = 10_i8;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 20_u8, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint8_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalSigned, MaxIndexTest7)
{
    using IntT = int8_t;
    constexpr IntT kMin = 100_i8;
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 27_u8, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint8_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest8)
{
    using IntT = int8_t;
    constexpr IntT kMin = -100_i8;
    constexpr IntT kMax = -90_i8;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 10_u8, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint8_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest9)
{
    using IntT = int32_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::min() + 1_i32;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 1_u32, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint32_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalSigned, MaxIndexTest10)
{
    using IntT = int32_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(
        IntervalT::kMaxIndex == std::numeric_limits<IntervalT::IndexT>::max(),
        "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint32_t>,
                  "Invalid index type");
}

TEST(IntervalSigned, MaxIndexTest11)
{
    using IntT = int64_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(
        IntervalT::kMaxIndex == std::numeric_limits<IntervalT::IndexT>::max(),
        "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint64_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalSigned, MaxIndexTest12)
{
    using IntT = int64_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::min() + 1_i64;
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 1_u64, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint64_t>,
                  "Invalid index type");
}

TEST(IntervalUnsigned, MaxIndexTest1)
{
    using IntT = uint8_t;
    constexpr IntT kMin = 100_u8;
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 155_u8, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint8_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalUnsigned, MaxIndexTest2)
{
    using IntT = uint16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::min();
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == std::numeric_limits<IntT>::max(),
                  "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
    static_assert(std::is_same_v<typename IntervalT::value_type, IntT>,
                  "Invalid IntervalT::value_type.");
}

TEST(IntervalUnsigned, MaxIndexTest3)
{
    using IntT = uint16_t;
    constexpr IntT kMin = std::numeric_limits<IntT>::max();
    constexpr IntT kMax = std::numeric_limits<IntT>::max();
    using IntervalT =
        interval::Interval<interval::Min<kMin>, interval::Max<kMax>>;
    static_assert(IntervalT::kMaxIndex == 0_u16, "Invalid kMaxIndex");
    static_assert(std::is_same_v<IntervalT::IndexT, uint16_t>,
                  "Invalid index type");
}
