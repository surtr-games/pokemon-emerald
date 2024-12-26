#include "global.h"
#include "random.h"

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
COMMON_DATA u32 gRngValue = 0;
COMMON_DATA u32 gRng2Value = 0;

u16 Random(void)
{
    gRngValue = ISO_RANDOMIZE1(gRngValue);
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}

bool8 IsRandomProbMet(u16 probability)
{
    return IsRandomProbMetWithValue(Random(), probability);
}

bool8 IsRandomProbMetWithValue(u16 randomValue, u16 probability)
{
    u16 threshold;

    if (probability == 0)
        return FALSE;

    if (probability >= 100)
        return TRUE;

    threshold = (u16)((u32)probability * USHRT_MAX / 100u);
    return randomValue <= threshold;
}

s32 RandomInRange(s32 min, s32 max)
{
    return RandomInRangeWithValue(Random(), min, max);
}

s32 RandomInRangeWithValue(u16 randomValue, s32 min, s32 max)
{
    u32 range;
    u32 scaledValue;

    if (min > max)
    {
        s32 temp = min;
        min = max;
        max = temp;
    }
    
    range = (u32)(max - min) + 1;
    scaledValue = (u32)randomValue * range / USHRT_MAX;
    return min + (s32)scaledValue;
}
