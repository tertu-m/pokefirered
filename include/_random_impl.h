// DO NOT INCLUDE THIS FILE DIRECTLY!!

#if !defined(RANDOM_IMPL_CONST) || !defined(RANDOM_IMPL_NONCONST)
#error _random_impl.h was included incorrectly.
#endif

RANDOM_IMPL_NONCONST u32 _Random32_Unlocked(void) {
    u32 b, c, result;

    b = gRngState.b;
    c = gRngState.c;
    result = gRngState.a + b + gRngState.counter++;

    gRngState.a = b ^ (b >> 9);
    gRngState.b = c * 9;
    gRngState.c = ((c << 21) | (c >> 11)) + result;

    return result;
}


RANDOM_IMPL_NONCONST u32 Random32(void) {
    u32 result;

    _LockRng();
    result = _Random32_Unlocked();
    _UnlockRng();

    return result;
}

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

#undef RANDOM_IMPL_CONST
#undef RANDOM_IMPL_NONCONST
