#include "global.h"
#include "random.h"
#include "main.h"

// The number 1103515245 comes from the example implementation
// of rand and srand in the ISO C standard.

static struct RngState {
    u32 a;
    u32 b;
    u32 c;
    u32 counter;
} state;

static volatile enum RngStatus {
    UNINITIALIZED,
    IDLE,
    BUSY
} status;

static u32 AdvanceRngInternal(void) {
    u32 b, c, result;

    b = state.b;
    c = state.c;
    result = state.a + b + state.counter++;

    state.a = b ^ (b >> 9);
    state.b = (c << 3) + 1;
    state.c = ((c << 21) | (c >> 11)) + result;

    return result;
}

void BurnRandomNumber(void) {
    if (status == IDLE)
        Random32();
}

u32 Random32(void) {
    u32 result;

    status = BUSY;
    result = AdvanceRngInternal();
    status = IDLE;

    return result;
}

u16 Random(void)
{
    return Random32() >> 16;
}

const u16 clz_Lookup[] = {31, 22, 30, 21, 18, 10, 29, 2, 20, 17, 15, 13, 9,
    6, 28, 1, 23, 19, 11, 3, 16, 14, 7, 24, 12, 4, 8, 25, 5, 26, 27, 0};

static void SeedRngInternal(u32 seed_c, u32 seed_b, u32 seed_a)
{
    u32 i;

    state.c = seed_c;
    state.b = seed_b;
    state.a = seed_a;
    state.counter = 1;

    for (i = 0; i < 20; i++)
        AdvanceRngInternal();

    status = IDLE;
}

void BootSeedRng(void)
{
    u32 timers, vblank;

    REG_TM1CNT_H = 0;
    REG_TM2CNT_H = 0;
    timers = ((u32)REG_TM2CNT_L << 16) | REG_TM1CNT_L;
    vblank = gMain.vblankCounter2;
    SeedRngInternal(timers, vblank, 0xBEEF5EEDU);
}

// Starts
void StartSeedTimer(void)
{
    REG_TM1CNT_H = 0x80;
    REG_TM2CNT_H = 0x82;
}

__attribute__((const)) const u16 CountLeadingZeroes(const u32 value)
{
    u32 modified_value;

    if (value == 0)
        return 0;

    modified_value = value | (value >> 1);
    modified_value |= modified_value >> 2;
    modified_value |= modified_value >> 4;
    modified_value |= modified_value >> 8;
    modified_value |= modified_value >> 16;

    return clz_Lookup[(modified_value * 0x07C4ACDDU) >> 27];
}


u16 RandomRangeGood(const u16 range)
{
    u32 mask, candidate;
    u16 adjusted_range;

    if (range == 0)
        return 0;

    adjusted_range = range - 1;
    mask = ~0U;
    mask >>= CountLeadingZeroes((u32)range);
    do {
        candidate = Random32() & mask;
    } while (candidate > adjusted_range);

    return candidate;
}

u16 RandomPercentageGood()
{
    return RandomRangeGood(100);
}