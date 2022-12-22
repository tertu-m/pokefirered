// DO NOT INCLUDE THIS FILE DIRECTLY!!

#if !defined(RANDOM_IMPL_CONST) || !defined(RANDOM_IMPL_NONCONST)
#error _random_impl.h was included incorrectly.
#endif

RANDOM_IMPL_CONST const u16 CountLeadingZeroes(const u32 value)
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


RANDOM_IMPL_NONCONST u16 _RandomRangeGood_Mask(const u16 range)
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

#undef RANDOM_IMPL_CONST
#undef RANDOM_IMPL_NONCONST
