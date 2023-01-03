// DO NOT INCLUDE THIS FILE DIRECTLY!!

#if !defined(RANDOM_IMPL_CONST) || !defined(RANDOM_IMPL_NONCONST)
#error _random_impl.h was included incorrectly.
#endif

#if MODERN==1
#define UNLIKELY(x) (__builtin_expect((x),0))
#else
#define UNLIKELY(x) (x)
#endif

RANDOM_IMPL_NONCONST void _LockRng()
{
    #if DEFERRED_SEEDING==1
        if (UNLIKELY(_gRngStatus == UNINITIALIZED))
            BootSeedRng();
    #endif // DEFERRED_SEEDING
    _gRngStatus = BUSY;
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
#undef UNLIKELY