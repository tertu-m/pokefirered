# Pokémon FireRed and LeafGreen with SFC32 random number generator

This is a disassembly of Pokémon FireRed and LeafGreen with the original random number generator replaced with the SFC32 random number generator and with additional random number generation functions. Unlike my other `sfc` branch, the code has been modified only where necessary to continue to function. It works with either agbcc or modern gcc.

## New functions and macros
* `void BootSeedRng(void)`: Handles RNG state initialization. You must call `StartSeedTimer()` first for it to work properly.
* `void BurnRandomNumber(void)`: Advances the RNG state if some other piece of code is not currently using it. Used in VBlank callbacks to prevent potential data corruption.
* `u16 CountLeadingZeroes(u32 x)`: Returns the number of leading zeroes in `x` using a de Bruijin algorithm derived from Wikipedia. If `x` is 0, returns 0. Used by `RandomRangeGood`.
* `u16 RandomBits(n)`: A macro that returns a `u16` containing `n` (0-16) unbiased random bits. Recommended for use where patterns like `Random() & x` or `Random % 2/4/8/16/32...` are used.
* `u32 RandomBits32(n)`: A macro that returns a `u32` containing `n` (0-32) unbiased random bits.
* `bool8 RandomBool()`: A macro that returns a random unbiased `bool8`. Recommended for use in random conditions (e.g. `if( RandomBool() )`).
* `u16 RandomRangeFast(u16 n)`: A macro that returns a number from 0 to `n` using a fast but biased method. Recommended for use in code that does not affect game mechanics (e.g. code whose results are only visual or audible).
* `u16 RandomRangeGood(u16 n)`: A function that returns a number from 0 to `n` using a slower but unbiased method. Recommended for use in code that affects game mechanics.
* `u16 RandomPercentageGood()`: A function that returns an unbiased random number from 0 to 99. Recommended for uses where `RandomRangeGood(100)` would have been used.
* `void StartSeedTimer(void)`: Starts a hardware timer that is used by `BootSeedRng()`.

## `RandomRangeFast` versus `RandomRangeGood`
`RandomRangeFast` works a lot like the `Random() % n` technique currently used throughout the game; given a perfect RNG source, it will not actually choose every number in the range with the same probability, but is faster than `RandomRangeGood` because it will only ever do one RNG call. It is almost always faster than `Random() % n` because the Game Boy Advance does division using a very slow software routine.
`RandomRangeGood`, on the other hand, can make as many RNG calls as it needs to ensure that the generated number is not biased, but usually takes less than 4. Even so, this method will usually be faster than `Random() % n` where n is not a constant value because software division is just that slow.

## Suggested changes
* Remove the separate wild encounter RNG. There really doesn't seem to be any point to it.
* Go through the codebase, find uses of `Random() % x`, and replace them with `RandomRangeFast`, `RandomRangeGood`, `RandomBits`, or `RandomBool` as appropriate. The `sfc` branch of this repository has already done this if you need pointers, though I have not thoroughly tested it.

## Removed functions
* `void SeedRng(u16 seed)`: It should not be necessary to reseed the RNG typically, and `BootSeedRng()` handles gathering data for you.
* `void StartTimer1(void)`: Call `StartSeedTimer()` instead, as that's all the original game did with timer 1.

## Other changes
* `Random32()` is now a function rather than a macro, as SFC32 outputs 32 bits at a time.
