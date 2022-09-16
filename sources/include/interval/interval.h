#ifndef interval_h
#define interval_h

#include <limits>
#include <type_traits>

namespace interval
{
template <auto Value>
struct Min
{
};

template <auto Value>
struct Max
{
};

enum class eIntervalLocation : uint8_t
{
    kInside = 0b001,  //  value location is inside of the interval
    kAbove = 0b010,   //  value location is above the interval
    kBelow = 0b100    //  value location is below the interval
};

template <typename MinT, typename MaxT>
struct Interval;

template <typename T, T MinV, T MaxV>
struct Interval<Min<MinV>, Max<MaxV>>
{
    static_assert(MinV <= MaxV, "interval cannot be empty");
    static constexpr T kMin = MinV;
    static constexpr T kMax = MaxV;
    using IndexT = std::make_unsigned_t<T>;
    using value_type = T;

    static constexpr eIntervalLocation location(T aValue) noexcept
    {
        if (aValue >= kMin)
        {
            if (aValue <= kMax)
            {
                return eIntervalLocation::kInside;
            }
            else
            {
                return eIntervalLocation::kAbove;
            }
        }
        else
        {
            return eIntervalLocation::kBelow;
        }
    }

    constexpr bool contains(T aValue) const noexcept
    {
        return location(aValue) == eIntervalLocation::kInside;
    }

    static constexpr IndexT maxIndex() noexcept
    {
        if constexpr (std::is_unsigned_v<T>)
        {
            return MaxV - MinV;
        }

        if constexpr (std::is_signed_v<T>)
        {
            constexpr IndexT uValue =
                static_cast<IndexT>(1) + std::numeric_limits<T>::max();
            constexpr IndexT uMin =
                static_cast<IndexT>(uValue + static_cast<IndexT>(MinV));
            constexpr IndexT uMax =
                static_cast<IndexT>(uValue + static_cast<IndexT>(MaxV));
            return uMax - uMin;
        }
    }

    static constexpr IndexT kMaxIndex = maxIndex();
};
}  // namespace interval

#endif /* interval_h */
