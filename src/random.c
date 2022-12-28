#include "global.h"
#include "random.h"
#include "main.h"

// The number 1103515245 comes from the example implementation
// of rand and srand in the ISO C standard.

struct RngState gRngState;

volatile enum RngStatus _gRngStatus;

#define RANDOM_IMPL_NONCONST
#define RANDOM_IMPL_CONST __attribute__((const))
#include "_random_impl.h"

void BurnRandomNumber(void) {
    if (_gRngStatus == IDLE)
        Random32();
}

const u16 clz_Lookup[] = {31, 22, 30, 21, 18, 10, 29, 2, 20, 17, 15, 13, 9,
    6, 28, 1, 23, 19, 11, 3, 16, 14, 7, 24, 12, 4, 8, 25, 5, 26, 27, 0};

static void SeedRngInternal(u32 seed_c, u32 seed_b, u32 seed_a)
{
    u32 i;
    _gRngStatus = UNINITIALIZED;

    gRngState.c = seed_c;
    gRngState.b = seed_b;
    gRngState.a = seed_a;
    gRngState.counter = 1;

    for (i = 0; i < 20; i++)
        _Random32_Unlocked();

    _gRngStatus = IDLE;
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
