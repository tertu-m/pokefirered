#include "global.h"
#include "random.h"
#include "main.h"

// The number 1103515245 comes from the example implementation
// of rand and srand in the ISO C standard.

struct RngState gRngState;
static EWRAM_DATA struct RngState encryptionRngState;
static bool8 encryptionRngSeeded = FALSE;

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

static void SeedRngState(struct RngState *state, u32 seed_c, u32 seed_b, u32 seed_a)
{
    u32 i;

    gRngState.c = seed_c;
    gRngState.b = seed_b;
    gRngState.a = seed_a;
    gRngState.counter = 1;

    for (i = 0; i < 20; i++)
        _Random32_Unlocked();
}

static void DoStandardSeed(struct RngState *state, u32 streamCode)
{
    u32 timers, vblank;
    _StopSeedTimer();
    timers = ((u32)REG_TM2CNT_L << 16) | REG_TM1CNT_L;
    vblank = gMain.vblankCounter2;
    SeedRngState(state, timers, vblank, streamCode);

    #if DEFERRED_SEEDING == 1
        StartSeedTimer();
    #endif // DEFERRED_SEEDING
}

void BootSeedRng(void)
{
    u32 timers, vblank;

    _gRngStatus = UNINITIALIZED;
    DoStandardSeed(&gRngState, 0xBEEF5EEDU);
    _gRngStatus = IDLE;
}

#if DEFERRED_SEEDING == 1
u32 EncryptionRandom(void) {
    if (!encryptionRngSeeded)
    {
        encryptionRngSeeded = TRUE;
        DoStandardSeed(&encryptionRngState, 0xA5EC4E7U);
    }

    return _AdvanceRngState(&encryptionRngState);
}
#endif