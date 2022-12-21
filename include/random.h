#ifndef GUARD_RANDOM_H
#define GUARD_RANDOM_H

#include "global.h"

extern const u16 clz_Lookup[];

//Returns a 32-bit pseudorandom number
u32 Random32(void);

// Returns x random bits, where x is a number between 1 and 16.
// You can pass arguments up to 32, but don't do that.
#define RandomBits(x) ((u16)(Random32() >> (32-(x))))
// The same but arguments between 1 and 32 are valid.
#define RandomBits32(x) (Random32() >> (32-(x)))

// Burns a random number if the RNG isn't currently in use.
void BurnRandomNumber(void);

// Generates a random number in a range from 0 to x-1.
// This approach is very fast but will be biased if x is not a power of 2 and
// should be used with caution.
#define RandomRangeFast(x) ((u16)(((u32)Random()*(u32)(x)) >> 16))

#define RandomBool() ((bool8)(Random32() >> 31))

// The number 1103515245 comes from the example implementation of rand and srand
// in the ISO C standard.
#define RAND_MULT 1103515245
#define ISO_RANDOMIZE1(val)(RAND_MULT * (val) + 24691)
#define ISO_RANDOMIZE2(val)(RAND_MULT * (val) + 12345)

//Sets the initial seed value of the pseudorandom number generator
void BootSeedRng(void);

void StartSeedTimer(void);

#if MODERN
#define RANDOM_IMPL_NONCONST extern inline __attribute__((gnu_inline))
#define RANDOM_IMPL_CONST extern inline __attribute__((const,gnu_inline))
#define RANDOM_NONCONST extern inline __attribute__((gnu_inline))
#else
#define RANDOM_IMPL_NONCONST extern inline
#define RANDOM_IMPL_CONST extern inline __attribute__((const))
#define RANDOM_NONCONST extern inline
#endif

//Returns a 16-bit pseudorandom number
RANDOM_NONCONST u16 Random(void) {
    return RandomBits(16);
}


RANDOM_NONCONST u16 _RandomRangeGood_Multiply(const u16 range)
{
    u16 scaled_lower_half, smallest_lower_half, random;
    u32 scaled_random;

    if (range == 0) return 0;

    // This lets us compute (UINT16_MAX+1) % range with 16-bit modulo.
    // The compiler should optimize this out, but in case it doesn't...
    smallest_lower_half = (u16)(~range+1) % range;
    do {
        random = Random();
        scaled_random = (u32)random * (u32)range;
        scaled_lower_half = (u16)scaled_random;
    } while (scaled_lower_half < smallest_lower_half);

    return (u16)(scaled_random >> 16);
}

RANDOM_NONCONST u16 RandomPercentageGood() {
    return _RandomRangeGood_Multiply(100);
}

#include "_random_impl.h"

// Taken from Linux. Devised by Martin Uecker.
#define __is_constexpr(x) \
    (sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

#define RandomRangeGood(x) (__is_constexpr((x)) ? _RandomRangeGood_Multiply((x)) : _RandomRangeGood_Mask((x)))

#undef RANDOM_NONCONST

#endif // GUARD_RANDOM_H
