# Pokémon FireRed and LeafGreen with SFC32 random number generator

This is a disassembly of Pokémon FireRed and LeafGreen with the original random number generator replaced with the SFC32 random number generator and with additional random number generation functions, which the code has been modified to use. The code compiles under both the agbcc and devkitPRO compilers, but devkitPRO is recommended because it produces smaller and better code. (On my machine, this repo compiles to a binary that is about 300K smaller before padding.)

## New functions and macros
* `void BootSeedRng(void)`: Handles RNG state initialization. You must call `StartSeedTimer()` first for it to work properly.
* `void BurnRandomNumber(void)`: Advances the RNG state if some other piece of code is not currently using it. Used in VBlank callbacks to prevent potential data corruption.
* `u16 CountLeadingZeroes(u32 x)`: Returns the number of leading zeroes in `x` using a de Bruijin algorithm derived from Wikipedia. If `x` is 0, returns 0. Used by `RandomRangeGood`.
* `u16 RandomBits(n)`: A macro that returns a `u16` containing `n` (0-16) unbiased random bits. Used wherever a fixed number of bits was called for.
* `u32 RandomBits32(n)`: A macro that returns a `u32` containing `n` (0-32) unbiased random bits. Not used in this repository.
* `bool8 RandomBool()`: A macro that returns a random unbiased `bool8`. Used for random conditions.
* `u16 RandomRangeFast(u16 n)`: A macro that returns a number from 0 to `n` using a fast but biased method. Used in code that does not affect game mechanics (i.e. code whose results are only visual).
* `u16 RandomRangeGood(u16 n)`: A macro that returns a number from 0 to `n` using slower but unbiased methods. Used in code that affects game mechanics.
* `u16 RandomPercentageGood()`: A function that returns an unbiased random number from 0 to 99. This is used where `RandomRangeGood(100)` would have been used, as it seems like that is done pretty often.
* `void StartSeedTimer(void)`: Starts a hardware timer that is used by `BootSeedRng()`.

Functions and macros starting with an _ are intended for internal use only, the above functions should be used. Here is what they do anyway:
* `_RandomRangeGood_Multiply`: Implements `RandomRangeGood` for cases where the argument is a constant.
* `_RandomRangeGood_Bitmask`: Implements `RandomRangeGood` for cases where the argument is not a constant.
* `__is_constexpr`: Used by `RandomRangeGood` to determine whether its argument is a constant or not.

## `RandomRangeFast` versus `RandomRangeGood`
`RandomRangeFast()` works a lot like the original `Random() % n` technique formerly used throughout the game; given a perfect RNG source, it will not actually choose every number in the range with the same probability, but is faster because it will only ever do one RNG call. `RandomRangeGood()` can make as many RNG calls as it needs to ensure that the generated number is not biased, but usually takes less than 3.

## Removed functions
* `u16 WildEncounterRandom()`: The separate wild encounter RNG no longer exists.
* `void SeedRng(u16 seed)`: It should not be necessary to reseed the RNG typically, and `BootSeedRng()` handles gathering data for you.
* `void SeedWildEncounterRng(u16 seed)`: The separate wild encounter RNG no longer exists.
* `void StartTimer1(void)`: Call `StartSeedTimer()` instead, as that's all the original game did with timer 1.

## Other changes
* `Random32()` is now a function rather than a macro, as SFC32 outputs 32 bits at a time.
