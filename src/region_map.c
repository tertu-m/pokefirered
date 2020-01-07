#include "global.h"
#include "palette.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "task.h"
#include "m4a.h"
#include "malloc.h"
#include "overworld.h"
#include "event_data.h"
#include "region_map.h"
#include "window.h"
#include "sound.h"
#include "new_menu_helpers.h"
#include "menu.h"
#include "string_util.h"
#include "strings.h"
#include "map_preview_screen.h"
#include "constants/flags.h"
#include "constants/songs.h"
#include "constants/region_map.h"
#include "constants/maps.h"

#define FREE_IF_NOT_NULL(ptr) ({ \
    if (ptr) {                   \
        FREE_AND_SET_NULL(ptr);  \
    }                            \
})

struct UnkStruct_20399D4
{
    u8 field_0000[19];
    u8 field_0013[19];
    u16 field_0026[5][600];
    // Inefficiency: these should be u8 or have half the elements each
    u16 field_1796[3][BG_SCREEN_SIZE];
    u8 field_4796;
    u8 field_4797[4];
    u8 field_479B;
    u8 field_479C;
    u8 filler_479D[3];
    u8 field_47A0;
    u8 filler_47A1[3];
    u8 field_47A4;
    u8 filler_47A5[3];
    u8 field_47A8;
    u16 field_47AA;
    u16 field_47AC;
    u16 field_47AE;
    u16 field_47B0;
    u8 filler_47B2[6];
    TaskFunc field_47B8;
    MainCallback field_47BC;
}; // size = 0x47C0

struct UnkStruct_20399D8_14B0
{
    u8 field_000[0x400];
    struct Sprite * field_400;
    u16 field_404;
    u16 field_406;
    s16 field_408;
};

struct UnkStruct_20399D8
{
    u8 field_0000[0x1000];
    u16 field_1000[0x258];
    struct UnkStruct_20399D8_14B0 field_14B0[2];
    u8 field_1CC8;
    u8 field_1CC9;
    u8 field_1CCA;
    u8 field_1CCB;
    u8 field_1CCC;
    u8 field_1CCD;
    u16 field_1CCE;
    TaskFunc field_1CD0;
    u16 field_1CD4[4];
    u16 field_1CDC;
}; // size = 0x1CE0

struct UnkStruct_80C4CF0
{
    u16 v0;
    u16 v2;
    u16 v4;
    u16 v6;
};

struct UnkStruct_83F1B3C
{
    u16 field_0;
    const u8 *field_4;
    const u8 *field_8;
};

struct UnkStruct_20399DC
{
    u16 field_0000[0x1C20];
    u16 field_3840[0x280];
    const struct MapPreviewScreen * field_3D40;
    TaskFunc field_3D44;
    u8 field_3D48;
    u8 field_3D49;
    u8 field_3D4A;
    u8 field_3D4B;
    u8 field_3D4C;
    u16 field_3D4E[0x30];
    u8 filler_3DAE[0x60];
    u16 field_3E0E;
    u16 field_3E10;
    u16 field_3E12;
    u16 field_3E14;
    u16 field_3E16;
    u16 field_3E18;
    u16 field_3E1A;
    u16 field_3E1C;
    u16 field_3E1E;
    u16 field_3E20;
    u16 field_3E22;
    u16 field_3E24;
}; // size = 0x3E28

struct UnkStruct_20399E0_000
{
    u16 field_000[0x200];
    struct Sprite * field_400;
    s16 field_404;
    s16 field_406;
    u16 field_408;
    u16 field_40A;
};

struct UnkStruct_20399E0
{
    struct UnkStruct_20399E0_000 * field_000[6];
    u16 field_018[0x400];
    u16 field_818[0x258];
    TaskFunc field_CC8;
    u8 field_CCC;
    u8 field_CCD;
    u8 field_CCE;
    u8 field_CCF;
    u8 field_CD0;
}; // size = 0xCD4

struct UnkStruct_20399E4
{
    s16 field_000;
    s16 field_002;
    u16 field_004;
    u16 field_006;
    s16 field_008;
    s16 field_00A;
    u16 field_00C;
    u8 field_00E;
    u8 (*field_010)(void);
    u16 field_014;
    u16 field_016;
    u16 field_018;
    struct Sprite * field_01C;
    u16 field_020;
    u16 field_022;
    u16 field_024[0x080];
}; // size = 0x124

struct UnkStruct_20399E8
{
    s16 field_00;
    s16 field_02;
    struct Sprite * field_04;
    u16 field_08;
    u16 field_0A;
    u16 field_0C[0x40];
}; // size = 0x8C

struct UnkStruct_20399EC_2D4
{
    u8 field_0;
    struct Sprite * field_4;
    u8 filler_8[8];
};

struct UnkStruct_20399EC
{
    u8 field_000[0x40];
    u8 field_040[0x100];
    u8 field_140[4];
    struct UnkStruct_20399EC_2D4 field_144[25];
    struct UnkStruct_20399EC_2D4 field_2D4[24];
    u8 field_454[0xC];
    u8 field_460;
    u8 filler_461[2];
    u8 field_463;
    u8 filler_464[4];
    TaskFunc field_468;
}; // size = 0x46C

EWRAM_DATA struct UnkStruct_20399D4 * gUnknown_20399D4 = NULL;
EWRAM_DATA struct UnkStruct_20399D8 * gUnknown_20399D8 = NULL;
EWRAM_DATA struct UnkStruct_20399DC * gUnknown_20399DC = NULL;
EWRAM_DATA struct UnkStruct_20399E0 * gUnknown_20399E0 = NULL;
EWRAM_DATA struct UnkStruct_20399E4 * gUnknown_20399E4 = NULL;
EWRAM_DATA struct UnkStruct_20399E8 * gUnknown_20399E8 = NULL;
EWRAM_DATA struct UnkStruct_20399EC * gUnknown_20399EC = NULL;
EWRAM_DATA void * gUnknown_20399F0[3] = {};
EWRAM_DATA void * gUnknown_20399FC = NULL;

static void sub_80BFFD0(void);
void sub_80C0100(void);
bool8 sub_80C0238(void);
void sub_80C03E8(void);
void sub_80C04E4(u8 taskId);
void sub_80C07F8(u8 taskId);
void sub_80C0820(u8 taskId);
void sub_80C08B4(void);
void sub_80C08E0(void);
void sub_80C08F4(void);
void sub_80C0904(void);
void sub_80C0A2C(void);
void sub_80C0A6C(void);
void sub_80C0A88(u8 a0);
void sub_80C0AB8(void);
void sub_80C0B18(void);
void sub_80C0B9C(void);
void sub_80C0BB0(void);
void sub_80C0CC8(u8 bg, u16 *map);
bool8 sub_80C0E04(u8 a0);
u8 sub_80C0E20(void);
void sub_80C0E70(u8 a0, u8 taskId, TaskFunc taskFunc);
void sub_80C1098(u8 taskId);
void sub_80C1280(u8 taskId);
bool8 sub_80C12EC(void);
void sub_80C1324(u8 bg, u16 *map);
void sub_80C1390(void);
bool8 sub_80C144C(void);
bool8 sub_80C1478(void);
bool8 sub_80C16D0(void);
void sub_80C1754(u8 a0, u16 a1, u16 a2);
void sub_80C176C(u8 a0, u16 a1, u16 a2);
void sub_80C1880(void);
void sub_80C195C(u8 a0, u8 taskId, TaskFunc taskFunc);
void sub_80C1A94(u8 taskId);
void sub_80C1BE0(u8 taskId);
void sub_80C1E14(u8 taskId);
void sub_80C1E94(void);
void sub_80C1E78(u8 bgId, const u16 * tilemap);
bool8 sub_80C1F80(bool8 a0);
void sub_80C2208(u8 taskId, TaskFunc taskFunc);
void sub_80C24BC(void);
void sub_80C267C(u8 taskId);
void sub_80C25BC(void);
void sub_80C2604(void);
bool8 sub_80C29A4(void);
void sub_80C2B48(void);
void sub_80C2C1C(u8 taskId);
void sub_80C2C7C(u8 taskId);
bool8 sub_80C2E1C(void);
void sub_80C3008(u16 a0, u16 a1);
void sub_80C309C(void);
void sub_80C3154(bool8 a0);
void sub_80C3178(void);
void sub_80C3188(void);
u8 sub_80C31C0(void);
u8 sub_80C3348(void);
u8 sub_80C3400(void);
void sub_80C3418(void);
u16 sub_80C3508(void);
u16 sub_80C3514(void);
u16 sub_80C3520(void);
u16 sub_80C3580(void);
u8 sub_80C35DC(u8 a0);
u8 sub_80C3878(u8 a0);
u8 sub_80C3AC8(u8 a0);
void sub_80C3D40(void);
u8 sub_80C4164(u8 a0, u8 a1, s16 a2, s16 a3);
void sub_80C41D8(u16 a0, u16 a1);
void sub_80C4244(void);
void sub_80C4324(bool8 a0);
void sub_80C4348(void);
u16 sub_80C4380();
u16 sub_80C438C();
void sub_80C4398(u8 a0, u8 taskId, TaskFunc taskFunc);
void sub_80C440C(u8 taskId);
void sub_80C44E4(u8 taskId);
void sub_80C4750(void);
void sub_80C47F0(void);
void sub_80C48BC(u8 a0, u8 a1, u8 a2);
void sub_80C4960(u8 a0, u8 a1, u8 a2);
void sub_80C4A04(void);
void sub_80C4B30(u8 a0);
void sub_80C4AAC(u8 a0);
void sub_80C4BE4(void);
void sub_80C4C2C(u8 a0, u16 a1, u16 a2);
void sub_80C4C48(u16 a0);
void sub_80C4C5C(u16 a0);
void sub_80C4C74(u16 a0, u16 a1);
void sub_80C4C88(u16 a0);
void sub_80C4C9C(u8 a0, u8 a1);
void sub_80C4CF0(u8 a0, const struct UnkStruct_80C4CF0 *a1);
void sub_80C4D30(void);
void sub_80C4E18(const u8 *str);
void sub_80C4E74(const u8 *str);
void sub_80C4ED0(bool8 a0);
void sub_80C4F08(u8 taskId);

#include "data/text/map_section_names.h"
extern const u16 gUnknown_83EF23C[];
extern const u16 gUnknown_83EF25C[];
extern const u16 gUnknown_83EF27C[];
extern const u16 gUnknown_83EF29C[];
extern const u16 gUnknown_83EF2BC[];
extern const u16 gUnknown_83EF2DC[];
extern const u16 gUnknown_83EF384[];
extern const u16 gUnknown_83EF3A4[];
extern const u32 gUnknown_83EF3C4[];
extern const u32 gUnknown_83EF450[];
extern const u32 gUnknown_83EF4E0[];
extern const u32 gUnknown_83EF524[];
extern const u32 gUnknown_83EF59C[];
extern const u32 gUnknown_83EF61C[];
extern const u32 gUnknown_83F0330[];
extern const u32 gUnknown_83F0E0C[];
extern const u32 gUnknown_83F0580[];
extern const u32 gUnknown_83F089C[];
extern const u32 gUnknown_83F0AFC[];
extern const u32 gUnknown_83F0C0C[];
extern const u32 gUnknown_83F0CF0[];
extern const u32 gUnknown_83F0F1C[];
extern const u32 gUnknown_83F1084[];
extern const u32 gUnknown_83F1190[];
extern const u32 gUnknown_83F12CC[];
extern const u32 gUnknown_83F13EC[];
extern const u32 gUnknown_83F1550[];
extern const u32 gUnknown_83F1640[];
extern const u32 gUnknown_83F1738[];
extern const u32 gUnknown_83F1804[];
extern const u32 gUnknown_83F18D8[];
extern const u32 gUnknown_83F1908[];
extern const u32 gUnknown_83F1978[];
extern const u32 gUnknown_83F19A0[];
extern const struct BgTemplate gUnknown_83F1A50[4];
extern const struct WindowTemplate gUnknown_83F1A60[];
extern const u8 gUnknown_83F1A90[];
extern const u8 gUnknown_83F1A94[];
extern const u8 *const gUnknown_83F1A9C[];
extern const u8 sSeviiMapsecs[3][30];
extern const u8 gUnknown_83F1B00[3][4];
extern const struct UnkStruct_80C4CF0 gUnknown_83F1B0C[3];
extern const struct OamData gUnknown_83F1B24;
extern const union AnimCmd *const gUnknown_83F1B38[];
extern const struct UnkStruct_83F1B3C gUnknown_83F1B3C[];
extern const struct OamData gUnknown_83F1C20;
extern const union AnimCmd *const gUnknown_83F1C30[];
extern const struct UnkStruct_80C4CF0 gUnknown_83F1C34;
extern const struct OamData gUnknown_83F1C3C;
extern const union AnimCmd *const gUnknown_83F1C50[];
extern const struct OamData gUnknown_83F1C54;
extern const union AnimCmd *const gUnknown_83F1C64[];
extern const struct OamData gUnknown_83F1C68;
extern const struct OamData gUnknown_83F1C70;
extern const union AnimCmd *const gUnknown_83F1C94[];
extern const union AnimCmd *const gUnknown_83F1C98[];
extern const u8 *const gUnknown_83F1CAC[];
extern const u16 gUnknown_83F1E60[][2];
extern const u16 gUnknown_83F2178[][2];
extern const u8 gUnknown_83F2490[][15][22];
extern const u8 gUnknown_83F2724[][15][22];
extern const u8 gUnknown_83F29B8[][15][22];
extern const u8 gUnknown_83F2C4C[][15][22];

static void RegionMap_DarkenPalette(u16 *pal, u16 size, u16 tint)
{
    int i;
    int r, g, b;

    for (i = 0; i < size; i++)
    {
        r = (*pal) & 0x1F;
        g = ((*pal) >> 5) & 0x1F;
        b = ((*pal) >> 10) & 0x1F;

        r = (((r << 8) / 100) * tint) >> 8;
        g = (((g << 8) / 100) * tint) >> 8;
        b = (((b << 8) / 100) * tint) >> 8;

        *pal = RGB2(r, g, b);
        pal++;
    }
}

void sub_80BFEA0(void)
{
    u16 pal[16];
    CpuCopy16(&gUnknown_83EF2DC[0x20], pal, sizeof(pal));
    RegionMap_DarkenPalette(pal, NELEMS(pal), 95);
    LoadPalette(pal, 0x20, 0x20);
    LoadPalette(&gUnknown_83EF2DC[0x2F], 0x2F, sizeof(u16));
}

void sub_80BFEDC(u8 kind)
{
    gUnknown_20399D4 = AllocZeroed(sizeof(struct UnkStruct_20399D4));
    if (gUnknown_20399D4 == NULL)
    {
        SetMainCallback2(CB2_ReturnToField);
    }
    else
    {
        gUnknown_2031DE0 = TRUE;
        gUnknown_20399D4->field_4796 = kind;
        gUnknown_20399D4->field_47A0 = 0;
        gUnknown_20399D4->field_47A4 = 0;
        gUnknown_20399D4->field_47A8 = 0;
        sub_80BFFD0();
        SetMainCallback2(sub_80C0100);
    }
}

void sub_80BFF50(u8 kind, MainCallback cb)
{
    gUnknown_20399D4 = AllocZeroed(sizeof(struct UnkStruct_20399D4));
    if (gUnknown_20399D4 == NULL)
    {
        SetMainCallback2(CB2_ReturnToField);
    }
    else
    {
        gUnknown_2031DE0 = TRUE;
        gUnknown_20399D4->field_4796 = kind;
        gUnknown_20399D4->field_47A0 = 0;
        gUnknown_20399D4->field_47A4 = 0;
        gUnknown_20399D4->field_47A8 = 0;
        gUnknown_20399D4->field_47BC = cb;
        sub_80BFFD0();
        SetMainCallback2(sub_80C0100);
    }
}

static void sub_80BFFD0(void)
{
    u8 i;
    u8 j;
    u8 r7;

    switch (gUnknown_20399D4->field_4796)
    {
    default:
    case 0:
    case 1:
        gUnknown_20399D4->field_47B8 = sub_80C04E4;
        break;
    case 2:
        gUnknown_20399D4->field_47B8 = sub_80C4F08;
        break;
    }
    for (i = 0; i < 4; i++)
    {
        gUnknown_20399D4->field_4797[i] = gUnknown_83F1B00[gUnknown_20399D4->field_4796][i];
    }
    if (!FlagGet(FLAG_SYS_SEVII_MAP_123))
        gUnknown_20399D4->field_4797[0] = FALSE;
    r7 = 0;
    j = 0;
    if (gMapHeader.regionMapSectionId >= MAPSECS_SEVII_123)
    {
        while (r7 == 0)
        {
            for (i = 0; sSeviiMapsecs[j][i] != MAPSEC_NONE; i++)
            {
                if (gMapHeader.regionMapSectionId == sSeviiMapsecs[j][i])
                {
                    r7 = j + 1;
                    break;
                }
            }
            j++;
        }
    }
    gUnknown_20399D4->field_479B = r7;
    gUnknown_20399D4->field_479C = r7;
}

void sub_80C0100(void)
{
    switch (gUnknown_20399D4->field_47A4)
    {
    case 0:
        sub_80C08E0();
        break;
    case 1:
        sub_80C0904();
        break;
    case 2:
        sub_80C0A6C();
        break;
    case 3:
        if (!sub_80C0238())
            return;
        break;
    case 4:
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(1);
        break;
    case 5:
        sub_80C0CC8(0, gUnknown_20399D4->field_0026[gUnknown_20399D4->field_479B]);
        CopyBgTilemapBufferToVram(0);
        if (gUnknown_20399D4->field_4796 != 0)
        {
            sub_80C0CC8(1, gUnknown_20399D4->field_0026[4]);
            CopyBgTilemapBufferToVram(1);
        }
        break;
    case 6:
        sub_80C0B18();
        PutWindowTilemap(0);
        break;
    case 7:
        sub_80C0BB0();
        PutWindowTilemap(1);
        break;
    case 8:
        if (sub_80C0E04(2) == TRUE)
            sub_80C0A88(1);
        break;
    default:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        sub_80C03E8();
        sub_80C08F4();
        break;
    }
    gUnknown_20399D4->field_47A4++;
}

bool8 sub_80C0238(void)
{
    switch (gUnknown_20399D4->field_47A8)
    {
    case 0:
        LoadPalette(gUnknown_83EF23C, 0xC0, 0x20);
        break;
    case 1:
        LoadPalette(gUnknown_83EF2DC, 0x00, 0xA0);
        sub_80BFEA0();
        if (gUnknown_20399D4->field_4796 != 0)
        {
            LoadPalette(&gUnknown_83EF23C[15], 0x00, 0x02);
            LoadPalette(&gUnknown_83EF23C[15], 0x10, 0x02);
            LoadPalette(&gUnknown_83EF23C[15], 0x20, 0x02);
            LoadPalette(&gUnknown_83EF23C[15], 0x30, 0x02);
            LoadPalette(&gUnknown_83EF23C[15], 0x40, 0x02);
        }
        break;
    case 2:
        ResetTempTileDataBuffers();
        break;
    case 3:
        DecompressAndCopyTileDataToVram(0, gUnknown_83EF61C, 0, 0, 0);
        if (gUnknown_20399D4->field_4796 != 0)
        {
            DecompressAndCopyTileDataToVram(1, gUnknown_83F1978, 0, 0, 0);
        }
        break;
    case 4:
        if (FreeTempTileDataBuffersIfPossible() == TRUE)
            return FALSE;
        break;
    case 5:
        LZ77UnCompWram(gUnknown_83F089C, gUnknown_20399D4->field_0026[0]);
        break;
    case 6:
        LZ77UnCompWram(gUnknown_83F0AFC, gUnknown_20399D4->field_0026[1]);
        break;
    case 7:
        LZ77UnCompWram(gUnknown_83F0C0C, gUnknown_20399D4->field_0026[2]);
        break;
    case 8:
        LZ77UnCompWram(gUnknown_83F0CF0, gUnknown_20399D4->field_0026[3]);
        break;
    default:
        LZ77UnCompWram(gUnknown_83F19A0, gUnknown_20399D4->field_0026[4]);
        return TRUE;
    }
    gUnknown_20399D4->field_47A8++;
    return FALSE;
}

void sub_80C03E8(void)
{
    CreateTask(gUnknown_20399D4->field_47B8, 0);
    SetMainCallback2(sub_80C08B4);
}

bool32 sub_80C0410(void)
{
    if (sub_80C4164(sub_80C0E20(), 0, sub_80C3514(), sub_80C3508()) == 99)
        return FALSE;
    else
        return TRUE;
}

void sub_80C0450(void)
{
    if (sub_80C0410())
    {
        if ((sub_80C3AC8(0) != 1 && sub_80C3AC8(0) != 0) || (sub_80C3AC8(1) != 1 && sub_80C3AC8(1) != 0))
            PlaySE(SE_Z_SCROLL);
        if (sub_80C3508() == 21 && sub_80C3514() == 11 && sub_80C0E04(0) == TRUE)
            PlaySE(SE_W255);
        else if (sub_80C3508() == 21 && sub_80C3514() == 13)
            PlaySE(SE_W255);
    }
}

void sub_80C04E4(u8 taskId)
{
    switch (gUnknown_20399D4->field_47A0)
    {
    case 0:
        sub_80C4398(sub_80C0E20(), taskId, gUnknown_20399D4->field_47B8);
        sub_80C3008(0, 0);
        sub_80C41D8(1, 1);
        gUnknown_20399D4->field_47A0++;
        break;
    case 1:
        if (gUnknown_20399D4->field_4797[2] == 1)
        {
            sub_80C2208(taskId, gUnknown_20399D4->field_47B8);
        }
        else
        {
            ShowBg(0);
            ShowBg(3);
            ShowBg(1);
            sub_80C4E18(gUnknown_8418EB5);
            sub_80C4E74(gUnknown_8418E8B);
            sub_80C4ED0(FALSE);
            sub_80C4324(FALSE);
            sub_80C3154(FALSE);
            sub_80C48BC(sub_80C0E20(), 25, 0);
            sub_80C4960(sub_80C0E20(), 25, 0);
        }
        gUnknown_20399D4->field_47A0++;
        break;
    case 2:
        if (!gPaletteFade.active && !IsDma3ManagerBusyWithBgCopy())
        {
            sub_80C0B18();
            PutWindowTilemap(0);
            sub_80C0BB0();
            PutWindowTilemap(1);
            gUnknown_20399D4->field_47A0++;
        }
        break;
    case 3:
        switch (sub_80C3400())
        {
        case 1:
            sub_80C3178();
            break;
        case 2:
            break;
        case 3:
            sub_80C0B18();
            sub_80C0BB0();
            sub_80C0B9C();
            sub_80C0450();
            if (sub_80C3580() != MAPSEC_NONE)
            {
                if (sub_80C0E04(1) == TRUE)
                {
                    if (sub_80C3AC8(1) == 2)
                    {
                        sub_80C4E74(gUnknown_8418E8D);
                    }
                    else
                    {
                        sub_80C4E74(gUnknown_8418E8B);
                    }
                }
            }
            else
            {
                if (sub_80C3508() == 21 && sub_80C3514() == 11 && sub_80C0E04(0) == TRUE)
                {
                    sub_80C4E74(gUnknown_8418EA7);
                }
                else if (sub_80C3508() == 21 && sub_80C3514() == 13)
                {
                    sub_80C4E74(gUnknown_8418E95);
                }
                else
                {
                    sub_80C4E74(gUnknown_8418E8B);
                }
            }
            break;
        case 4:
            if (sub_80C3AC8(1) == 2 && gUnknown_20399D4->field_4797[1] == 1)
            {
                sub_80C195C(0, taskId, sub_80C07F8);
            }
            break;
        case 5:
            sub_80C0E70(gUnknown_20399D4->field_479B, taskId, sub_80C07F8);
            break;
        case 6:
            gUnknown_20399D4->field_47A0++;
            break;
        }
        break;
    case 4:
        if (sub_80C0E04(2) == 1)
        {
            sub_80C2C1C(taskId);
            // FIXME: goto required to match
            // gUnknown_20399D4->field_47A0++;
            goto _080C0798;
        }
        else
        {
            gUnknown_20399D4->field_47A0++;
        }
        break;
    case 5:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    _080C0798:
        gUnknown_20399D4->field_47A0++;
        break;
    default:
        if (!gPaletteFade.active)
        {
            sub_80C0820(taskId);
        }
        break;
    }
}

void sub_80C07D0(TaskFunc taskFunc)
{
    gUnknown_20399D4->field_47B8 = taskFunc;
}

TaskFunc sub_80C07E4(void)
{
    return gUnknown_20399D4->field_47B8;
}

void sub_80C07F8(u8 taskId)
{
    gTasks[taskId].func = gUnknown_20399D4->field_47B8;
}

void sub_80C0820(u8 taskId)
{
    if (sub_80C0E04(2) == TRUE)
        sub_80C25BC();
    sub_80C4A04();
    sub_80C3188();
    sub_80C4348();
    sub_80C4D30();
    DestroyTask(taskId);
    FreeAllWindowBuffers();
    if (gUnknown_20399D4->field_47BC == NULL)
        SetMainCallback2(gMain.savedCallback);
    else
        SetMainCallback2(gUnknown_20399D4->field_47BC);
    FREE_IF_NOT_NULL(gUnknown_20399D4);
}

void sub_80C0898(void)
{
    FREE_IF_NOT_NULL(gUnknown_20399D4);
}

void sub_80C08B4(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void sub_80C08CC(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void sub_80C08E0(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

void sub_80C08F4(void)
{
    SetVBlankCallback(sub_80C08CC);
}

void sub_80C0904(void)
{
    DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaFill32Defvars(3, 0, (void *)OAM, OAM_SIZE);
    DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    ResetBgsAndClearDma3BusyFlags(FALSE);
    InitBgsFromTemplates(0, gUnknown_83F1A50, NELEMS(gUnknown_83F1A50));
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    InitWindows(gUnknown_83F1A60);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
    sub_80C0A2C();
    sub_80C0AB8();
}

void sub_80C0A2C(void)
{
    SetBgTilemapBuffer(0, gUnknown_20399D4->field_1796[0]);
    SetBgTilemapBuffer(1, gUnknown_20399D4->field_1796[1]);
    SetBgTilemapBuffer(2, gUnknown_20399D4->field_1796[2]);
}

void sub_80C0A6C(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

void sub_80C0A88(u8 mode)
{
    switch (mode)
    {
    case 0:
        ShowBg(0);
        ShowBg(3);
        break;
    case 1:
        HideBg(0);
        HideBg(3);
        break;
    }
}

void sub_80C0AB8(void)
{
    sub_80C4BE4();
    sub_80C4C2C(0, 0x11, 0xc0);
    sub_80C4C48(6);
    sub_80C4C74(0x39, 0x39);
    sub_80C4C88(0x1b);
    sub_80C4CF0(0, &gUnknown_83F1B0C[0]);
    sub_80C4CF0(1, &gUnknown_83F1B0C[1]);
    sub_80C4C9C(0, 0);
    if (sub_80C3580() != MAPSEC_NONE)
        sub_80C4C9C(1, 0);
}

void sub_80C0B18(void)
{
    ClearWindowTilemap(0);
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    if (sub_80C3520() == MAPSEC_NONE)
    {
        sub_80C4CF0(0, &gUnknown_83F1B0C[2]);
    }
    else
    {
        GetMapName(gUnknown_20399D4->field_0000, sub_80C3520(), 0);
        AddTextPrinterParameterized3(0, 2, 2, 2, gUnknown_83F1A90, 0, gUnknown_20399D4->field_0000);
        PutWindowTilemap(0);
        CopyWindowToVram(0, 2);
        sub_80C4CF0(0, &gUnknown_83F1B0C[0]);
    }
}

void sub_80C0B9C(void)
{
    sub_80C4CF0(1, &gUnknown_83F1B0C[1]);
}

void sub_80C0BB0(void)
{
    u16 mapsecId;
    u16 descOffset;
    gUnknown_20399D4->field_47AC = 0;
    gUnknown_20399D4->field_47AE = 24;
    gUnknown_20399D4->field_47B0 = 32;
    sub_80C4C9C(1, 1);
    ClearWindowTilemap(1);
    mapsecId = sub_80C3580();
    if (mapsecId != MAPSEC_NONE)
    {
         descOffset = mapsecId - MAPSECS_KANTO;
         sub_80C4C9C(1, 0);
         gUnknown_20399D4->field_47AC = 1;
         gUnknown_20399D4->field_47AA = StringLength(gUnknown_83F1CAC[descOffset]);
         gUnknown_20399D4->field_47AE = gUnknown_20399D4->field_47AA * 10 + 50;
         gUnknown_20399D4->field_47B0 = 48;
         FillWindowPixelBuffer(1, PIXEL_FILL(0));
         StringCopy(gUnknown_20399D4->field_0013, gUnknown_83F1CAC[descOffset]);
         AddTextPrinterParameterized3(1, 2, 12, 2, gUnknown_83F1A9C[sub_80C3AC8(1) - 2], 0, gUnknown_20399D4->field_0013);
         PutWindowTilemap(1);
         CopyWindowToVram(1, 3);
    }
}

void sub_80C0CA0(void)
{
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    CopyWindowToVram(0, 3);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    CopyWindowToVram(1, 3);
}

void sub_80C0CC8(u8 bg, u16 *map)
{
    s16 i;
    s16 j;
    u8 r4;
    u16 *buffer = gUnknown_20399D4->field_1796[bg];
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (j < 30)
                buffer[32 * i + j] = map[30 * i + j];
            else
                buffer[32 * i + j] = map[0];
        }
    }
    if (gUnknown_20399D4->field_4797[0] == 1)
    {
        WriteSequenceToBgTilemapBuffer(0, 0x0F0, 0x18, 0x0E, 3, 1, 0x3, 0x001);
        WriteSequenceToBgTilemapBuffer(0, 0x100, 0x18, 0x0F, 3, 1, 0x3, 0x001);
        WriteSequenceToBgTilemapBuffer(0, 0x110, 0x18, 0x10, 3, 1, 0x3, 0x001);
    }
    if (gUnknown_20399D8 != NULL)
        r4 = gUnknown_20399D8->field_1CCA;
    else
        r4 = gUnknown_20399D4->field_479B;
    if (r4 == 2 && !FlagGet(FLAG_WORLD_MAP_NAVEL_ROCK_EXTERIOR))
        FillBgTilemapBufferRect_Palette0(0, 0x003, 13, 11, 3, 2);
    if (r4 == 3 && !FlagGet(FLAG_WORLD_MAP_BIRTH_ISLAND_EXTERIOR))
        FillBgTilemapBufferRect_Palette0(0, 0x003, 21, 16, 3, 3);
}

u8 sub_80C0E04(u8 a0)
{
    return gUnknown_20399D4->field_4797[a0];
}

u8 sub_80C0E20(void)
{
    return gUnknown_20399D4->field_479B;
}

u8 sub_80C0E34(void)
{
    return gUnknown_20399D4->field_479C;
}

void sub_80C0E48(u8 a0)
{
    gUnknown_20399D4->field_479B = a0;
}

void sub_80C0E5C(u8 a0)
{
    gUnknown_20399D4->field_479C = a0;
}

void sub_80C0E70(u8 a0, u8 taskId, TaskFunc taskFunc)
{
    gUnknown_20399D8 = AllocZeroed(sizeof(struct UnkStruct_20399D8));
    if (FlagGet(FLAG_SYS_SEVII_MAP_4567))
        gUnknown_20399D8->field_1CCC = 3;
    else if (FlagGet(FLAG_SYS_SEVII_MAP_123))
        gUnknown_20399D8->field_1CCC = 1;
    else
        gUnknown_20399D8->field_1CCC = 0;
    gUnknown_20399D8->field_14B0[0].field_408 = 0x58;
    gUnknown_20399D8->field_14B0[1].field_408 = 0x98;
    switch (gUnknown_20399D8->field_1CCC)
    {
    case 1:
        LZ77UnCompWram(gUnknown_83F1084, gUnknown_20399D8->field_1000);
        gUnknown_20399D8->field_1CCE = 6;
        break;
    case 2: // never reached
        LZ77UnCompWram(gUnknown_83F1190, gUnknown_20399D8->field_1000);
        gUnknown_20399D8->field_1CCE = 4;
        break;
    case 3:
    default:
        gUnknown_20399D8->field_1CCE = 3;
        LZ77UnCompWram(gUnknown_83F0F1C, gUnknown_20399D8->field_1000);
        break;
    }
    LZ77UnCompWram(gUnknown_83F0580, gUnknown_20399D8->field_0000);
    gUnknown_20399D8->field_1CC8 = 0;
    gUnknown_20399D8->field_1CCA = a0;
    gUnknown_20399D8->field_1CD0 = taskFunc;
    gUnknown_20399D8->field_1CCB = sub_80C0E34();
    sub_80C4AAC(0);
    sub_80C4E74(gUnknown_8418EB0);
    gTasks[taskId].func = sub_80C1098;
}

void sub_80C0FE0(void)
{
    sub_80C4BE4();
    sub_80C4C2C(27, 4, 64);
    sub_80C4C5C(16 - gUnknown_20399D8->field_1CCD);
}

bool8 sub_80C1014(void)
{
    if (gUnknown_20399D8->field_1CCD < 16)
    {
        sub_80C4C5C(16 - gUnknown_20399D8->field_1CCD);
        gUnknown_20399D8->field_1CCD += 2;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool8 sub_80C1058(void)
{
    if (gUnknown_20399D8->field_1CCD >= 2)
    {
        gUnknown_20399D8->field_1CCD -= 2;
        sub_80C4C5C(16 - gUnknown_20399D8->field_1CCD);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void sub_80C1098(u8 taskId)
{
    switch (gUnknown_20399D8->field_1CC8)
    {
    case 0:
        sub_80C08E0();
        sub_80C4E18(gUnknown_8418EBC);
        gUnknown_20399D8->field_1CC8++;
        break;
    case 1:
        LoadBgTiles(2, gUnknown_20399D8->field_0000, 0x1000, 0x000);
        gUnknown_20399D8->field_1CC8++;
        break;
    case 2:
        sub_80C1324(2, gUnknown_20399D8->field_1000);
        CopyBgTilemapBufferToVram(2);
        gUnknown_20399D8->field_1CC8++;
        break;
    case 3:
        sub_80C0CA0();
        gUnknown_20399D8->field_1CC8++;
        break;
    case 4:
        sub_80C0FE0();
        ShowBg(2);
        gUnknown_20399D8->field_1CC8++;
        break;
    case 5:
        sub_80C08F4();
        gUnknown_20399D8->field_1CC8++;
        break;
    case 6:
        if (sub_80C1014() == TRUE)
        {
            sub_80C1390();
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 7:
        if (sub_80C144C() == TRUE)
        {
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 8:
        if (sub_80C16D0() == TRUE)
        {
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 9:
        if (sub_80C1478() == TRUE)
        {
            sub_80C0E48(gUnknown_20399D8->field_1CCA);
            if (sub_80C0E34() == gUnknown_20399D8->field_1CCA)
            {
                sub_80C4324(FALSE);
                sub_80C48BC(gUnknown_20399D8->field_1CCA, 25, 0);
                sub_80C4960(gUnknown_20399D8->field_1CCA, 25, 0);
            }
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 10:
        if (sub_80C12EC() == TRUE)
        {
            sub_80C1880();
            sub_80C0FE0();
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 11:
        if (sub_80C1058() == TRUE)
        {
            gUnknown_20399D8->field_1CC8++;
        }
        break;
    case 12:
        sub_80C3154(FALSE);
        gUnknown_20399D8->field_1CC8++;
        break;
    default:
        sub_80C1280(taskId);
        break;
    }
}

void sub_80C1280(u8 taskId)
{
    gTasks[taskId].func = gUnknown_20399D8->field_1CD0;
    HideBg(2);
    sub_80C4E18(gUnknown_8418EB5);
    sub_80C4E74(gUnknown_8418EA7);
    sub_80C0AB8();
    sub_80C0B9C();
    sub_80C4CF0(0, &gUnknown_83F1B0C[2]);
    FREE_IF_NOT_NULL(gUnknown_20399D8);
}

bool8 sub_80C12EC(void)
{
    if (gUnknown_20399D8->field_1CDC != 0)
    {
        gUnknown_20399D8->field_1CDC--;
        SetGpuReg(REG_OFFSET_BLDY, gUnknown_20399D8->field_1CDC);
        return FALSE;
    }
    else
    {
        SetGpuReg(REG_OFFSET_BLDY, 0);
        return TRUE;
    }
}

void sub_80C1324(u8 bg, u16 *map)
{
    s16 i;
    s16 j;
    u16 *buffer = gUnknown_20399D4->field_1796[bg];
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (j < 30)
                buffer[32 * i + j] = map[30 * i + j];
            else
                buffer[32 * i + j] = map[0];
        }
    }
}

void sub_80C1390(void)
{
    struct UnkStruct_80C4CF0 data;
    data.v0 = gUnknown_20399D8->field_1CD4[0] = 0x48;
    data.v2 = gUnknown_20399D8->field_1CD4[1] = 8 * (gUnknown_20399D8->field_1CCE + 4 * gUnknown_20399D8->field_1CCA);
    data.v4 = gUnknown_20399D8->field_1CD4[2] = 0xA8;
    data.v6 = gUnknown_20399D8->field_1CD4[3] = gUnknown_20399D8->field_1CD4[1] + 32;
    sub_80C4BE4();
    sub_80C4C2C(0, 0x15, 0xc0);
    sub_80C4C74(0x1f, 0x15);
    sub_80C4C88(0x3f);
    sub_80C4C9C(1, 0);
    sub_80C4CF0(1, &data);
}

bool8 sub_80C144C(void)
{
    if (gUnknown_20399D8->field_1CDC < 6)
    {
        gUnknown_20399D8->field_1CDC++;
        sub_80C4C48(gUnknown_20399D8->field_1CDC);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool8 sub_80C1478(void)
{
    bool8 r6 = FALSE;
    struct UnkStruct_80C4CF0 data;
    data.v0 = gUnknown_20399D8->field_1CD4[0] = 0x48;
    data.v2 = gUnknown_20399D8->field_1CD4[1] = 8 * (gUnknown_20399D8->field_1CCE + 4 * gUnknown_20399D8->field_1CCA);
    data.v4 = gUnknown_20399D8->field_1CD4[2] = 0xA8;
    data.v6 = gUnknown_20399D8->field_1CD4[3] = gUnknown_20399D8->field_1CD4[1] + 32;
    if (JOY_NEW(DPAD_UP) && gUnknown_20399D8->field_1CCA != 0)
    {
        PlaySE(SE_BAG1);
        gUnknown_20399D8->field_1CCA--;
        r6 = TRUE;
    }
    if (JOY_NEW(DPAD_DOWN) && gUnknown_20399D8->field_1CCA < gUnknown_20399D8->field_1CCC)
    {
        PlaySE(SE_BAG1);
        gUnknown_20399D8->field_1CCA++;
        r6 = TRUE;
    }
    if (JOY_NEW(A_BUTTON) && gUnknown_20399D8->field_1CDC == 6)
    {
        PlaySE(SE_W129);
        gUnknown_20399D8->field_1CCB = gUnknown_20399D8->field_1CCA;
        return TRUE;
    }
    if (JOY_NEW(B_BUTTON))
    {
        gUnknown_20399D8->field_1CCA = gUnknown_20399D8->field_1CCB;
        sub_80C0CC8(0, gUnknown_20399D4->field_0026[gUnknown_20399D8->field_1CCA]);
        CopyBgTilemapBufferToVram(0);
        sub_80C48BC(255, 25, 1);
        sub_80C4960(255, 25, 1);
        return TRUE;
    }
    if (r6)
    {
        sub_80C0CC8(0, gUnknown_20399D4->field_0026[gUnknown_20399D8->field_1CCA]);
        sub_80C4E74(gUnknown_8418EB0);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(3);
        sub_80C48BC(255, 25, 1);
        sub_80C4960(255, 25, 1);
        sub_80C48BC(gUnknown_20399D8->field_1CCA, 25, 0);
        sub_80C4960(gUnknown_20399D8->field_1CCA, 25, 0);
    }
    if (gUnknown_20399D8->field_1CCA != sub_80C0E34())
        sub_80C4324(TRUE);
    else
        sub_80C4324(FALSE);
    sub_80C4CF0(1, &data);
    return FALSE;
}

void sub_80C16B8(struct Sprite * sprite)
{
    sprite->pos1.y = gUnknown_20399D8->field_1CD4[1] + 16;
}

bool8 sub_80C16D0(void)
{
    switch (gUnknown_20399D8->field_1CC9)
    {
    case 0:
        LZ77UnCompWram(gUnknown_83EF3C4, gUnknown_20399D8->field_14B0[0].field_000);
        break;
    case 1:
        LZ77UnCompWram(gUnknown_83EF450, gUnknown_20399D8->field_14B0[1].field_000);
        break;
    case 2:
        sub_80C1754(0, 2, 2);
        sub_80C1754(1, 3, 3);
        break;
    default:
        return TRUE;
    }
    gUnknown_20399D8->field_1CC9++;
    return FALSE;
}

void sub_80C1754(u8 a0, u16 a1, u16 a2)
{
    sub_80C176C(a0, a1, a2);
}

void sub_80C176C(u8 a0, u16 a1, u16 a2)
{
    u8 spriteId;

    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399D8->field_14B0[a0].field_000,
        .size = 0x400,
        .tag = a1
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF384,
        .tag = a2
    };
    struct SpriteTemplate template = {
        .tileTag = a1,
        .paletteTag = a2,
        .oam = &gUnknown_83F1B24,
        .anims = gUnknown_83F1B38,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80C16B8
    };

    gUnknown_20399D8->field_14B0[a0].field_404 = a1;
    gUnknown_20399D8->field_14B0[a0].field_406 = a2;

    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);

    spriteId = CreateSprite(&template, gUnknown_20399D8->field_14B0[a0].field_408, 8 * (gUnknown_20399D8->field_1CCE + 4 * gUnknown_20399D8->field_1CCA), 0);
    gUnknown_20399D8->field_14B0[a0].field_400 = &gSprites[spriteId];
    gSprites[spriteId].invisible = FALSE;
}

void sub_80C1880(void)
{
    u8 i;
    for (i = 0; i < 2; i++)
    {
        if (gUnknown_20399D8->field_14B0[i].field_400 != NULL)
        {
            DestroySprite(gUnknown_20399D8->field_14B0[i].field_400);
            FreeSpriteTilesByTag(gUnknown_20399D8->field_14B0[i].field_404);
            FreeSpritePaletteByTag(gUnknown_20399D8->field_14B0[i].field_406);
        }
    }
}

const u8 *sub_80C18E0(u16 a0)
{
    u8 i;
    for (i = 0; i < 19; i++)
    {
        if (gUnknown_83F1B3C[i].field_0 == a0)
            return gUnknown_83F1B3C[i].field_8;
    }
    return gUnknown_8418EC3;
}

const u8 *sub_80C1920(u16 a0)
{
    u8 i;
    for (i = 0; i < 19; i++)
    {
        if (gUnknown_83F1B3C[i].field_0 == a0)
            return gUnknown_83F1B3C[i].field_4;
    }
    return gUnknown_8418EC3;
}

void sub_80C195C(u8 a0, u8 taskId, TaskFunc taskFunc)
{
    u8 r0;
    gUnknown_20399DC = AllocZeroed(sizeof(struct UnkStruct_20399DC));
    r0 = sub_80C3580();
    if (r0 == MAPSEC_TANOBY_CHAMBERS)
        r0 = MAPSEC_MONEAN_CHAMBER;
    gUnknown_20399DC->field_3D40 = sub_80F8544(r0);
    if (gUnknown_20399DC->field_3D40 == NULL)
        gUnknown_20399DC->field_3D40 = sub_80F8544(MAPSEC_ROCK_TUNNEL);
    gUnknown_20399DC->field_3D48 = 0;
    gUnknown_20399DC->field_3D4A = 0;
    gUnknown_20399DC->field_3D44 = taskFunc;
    gUnknown_20399DC->field_3E14 = 0;
    sub_80C4AAC(0);
    sub_80C4BE4();
    sub_80C0CA0();
    gTasks[taskId].func = sub_80C1A94;
}

bool8 sub_80C19FC(void)
{
    switch (gUnknown_20399DC->field_3D4A)
    {
    case 0:
        LZ77UnCompWram(gUnknown_20399DC->field_3D40->tilesptr, gUnknown_20399DC->field_0000);
        break;
    case 1:
        LZ77UnCompWram(gUnknown_20399DC->field_3D40->tilemapptr, gUnknown_20399DC->field_3840);
        break;
    case 2:
        LoadBgTiles(2, gUnknown_20399DC->field_0000, 0x3840, 0x000);
        break;
    case 3:
        LoadPalette(gUnknown_20399DC->field_3D40->palptr, 0xD0, 0x60);
        break;
    default:
        return TRUE;
    }
    gUnknown_20399DC->field_3D4A++;
    return FALSE;
}

void sub_80C1A94(u8 taskId)
{
    switch (gUnknown_20399DC->field_3D48)
    {
    case 0:
        sub_80C08E0();
        gUnknown_20399DC->field_3D48++;
        break;
    case 1:
        if (sub_80C19FC() == TRUE)
            gUnknown_20399DC->field_3D48++;
        break;
    case 2:
        sub_80C1E94();
        sub_80C4E74(gUnknown_8418E9E);
        gUnknown_20399DC->field_3D48++;
        break;
    case 3:
        sub_80C1E78(2, gUnknown_20399DC->field_3840);
        CopyBgTilemapBufferToVram(2);
        gUnknown_20399DC->field_3D48++;
        break;
    case 4:
        ShowBg(2);
        gUnknown_20399DC->field_3D48++;
        break;
    case 5:
        sub_80C08F4();
        gUnknown_20399DC->field_3D48++;
        break;
    case 6:
        if (sub_80C1F80(FALSE) == TRUE)
            gUnknown_20399DC->field_3D48++;
        break;
    case 7:
        gTasks[taskId].func = sub_80C1BE0;
        break;
    case 8:
        if (sub_80C1F80(TRUE) == TRUE)
        {
            gUnknown_20399DC->field_3D48++;
        }
        break;
    case 9:
        sub_80C1E14(taskId);
        gUnknown_20399DC->field_3D48++;
        break;
    }
}

void sub_80C1BE0(u8 taskId)
{
    switch (gUnknown_20399DC->field_3D49)
    {
    case 0:
        gUnknown_20399DC->field_3E0E = 0x0133;
        gUnknown_20399DC->field_3E10 = 0x0100;
        gUnknown_20399DC->field_3E12 = 0x00F0;
        gUnknown_20399DC->field_3D49++;
        break;
    case 1:
        if (gUnknown_20399DC->field_3D4C++ > 40)
        {
            gUnknown_20399DC->field_3D4C = 0;
            gUnknown_20399DC->field_3D49++;
        }
        break;
    case 2:
        FillWindowPixelBuffer(2, PIXEL_FILL(0));
        CopyWindowToVram(2, 3);
        PutWindowTilemap(2);
        gUnknown_20399DC->field_3D49++;
        break;
    case 3:
        if (gUnknown_20399DC->field_3D4C > 25)
        {
            AddTextPrinterParameterized3(2, 2, 4, 0, gUnknown_83F1A94, -1, sub_80C1920(sub_80C3580()));
            AddTextPrinterParameterized3(2, 2, 2, 14, gUnknown_83F1A90, -1, sub_80C18E0(sub_80C3580()));
            CopyWindowToVram(2, 3);
            gUnknown_20399DC->field_3D49++;
        }
        else if (gUnknown_20399DC->field_3D4C > 20)
        {
            gUnknown_20399DC->field_3E0E -= 6;
            gUnknown_20399DC->field_3E10 -= 5;
            gUnknown_20399DC->field_3E12 -= 5;
            CpuCopy16(gUnknown_20399DC->field_3D40->palptr, gUnknown_20399DC->field_3D4E, 0x60);
            TintPalette_CustomTone(gUnknown_20399DC->field_3D4E, 0x30, gUnknown_20399DC->field_3E0E, gUnknown_20399DC->field_3E10, gUnknown_20399DC->field_3E12);
            LoadPalette(gUnknown_20399DC->field_3D4E, 0xD0, 0x60);
        }
        gUnknown_20399DC->field_3D4C++;
        break;
    case 4:
        if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
        {
            FillWindowPixelBuffer(2, PIXEL_FILL(0));
            CopyWindowToVram(2, 3);
            gUnknown_20399DC->field_3D48++;
            gUnknown_20399DC->field_3D49++;
        }
        break;
    default:
        gTasks[taskId].func = sub_80C1A94;
        break;
    }
}

void sub_80C1E14(u8 taskId)
{
    gTasks[taskId].func = gUnknown_20399DC->field_3D44;
    HideBg(2);
    sub_80C4B30(0);
    sub_80C0B18();
    sub_80C0BB0();
    sub_80C0AB8();
    sub_80C0B9C();
    sub_80C4E74(gUnknown_8418E8D);
    FREE_IF_NOT_NULL(gUnknown_20399DC);
}

void sub_80C1E78(u8 bgId, const u16 * tilemap)
{
    CopyToBgTilemapBufferRect(2, tilemap, 0, 0, 32, 20);
}

void sub_80C1E94(void)
{
    u16 r4;
    u16 r0;
    sub_80C4BE4();
    sub_80C4C2C(0, 17, 192);
    sub_80C4C48(gUnknown_20399DC->field_3E14);
    sub_80C4C74(0, 13);
    sub_80C4C88(59);
    sub_80C4C9C(1, 0);
    r4 = sub_80C3508();
    r0 = sub_80C3514();
    gUnknown_20399DC->field_3E16 = 8 * r4 + 32;
    gUnknown_20399DC->field_3E18 = 8 * r0 + 24;
    gUnknown_20399DC->field_3E1A = gUnknown_20399DC->field_3E16 + 8;
    gUnknown_20399DC->field_3E1C = gUnknown_20399DC->field_3E18 + 8;
    gUnknown_20399DC->field_3E1E = (0x10 - gUnknown_20399DC->field_3E16) / 8;
    gUnknown_20399DC->field_3E20 = (0x20 - gUnknown_20399DC->field_3E18) / 8;
    gUnknown_20399DC->field_3E22 = (0xE0 - gUnknown_20399DC->field_3E1A) / 8;
    gUnknown_20399DC->field_3E24 = (0x88 - gUnknown_20399DC->field_3E1C) / 8;
}

bool8 sub_80C1F80(bool8 a0)
{
    struct UnkStruct_80C4CF0 data;

    if (!a0)
    {
        if (gUnknown_20399DC->field_3D4B < 8)
        {
            gUnknown_20399DC->field_3E16 += gUnknown_20399DC->field_3E1E;
            gUnknown_20399DC->field_3E18 += gUnknown_20399DC->field_3E20;
            gUnknown_20399DC->field_3E1A += gUnknown_20399DC->field_3E22;
            gUnknown_20399DC->field_3E1C += gUnknown_20399DC->field_3E24;
            gUnknown_20399DC->field_3D4B++;
            if (gUnknown_20399DC->field_3E14 < 6)
                gUnknown_20399DC->field_3E14++;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        if (gUnknown_20399DC->field_3D4B == 0)
        {
            return TRUE;
        }
        else
        {
            gUnknown_20399DC->field_3E16 -= gUnknown_20399DC->field_3E1E;
            gUnknown_20399DC->field_3E18 -= gUnknown_20399DC->field_3E20;
            gUnknown_20399DC->field_3E1A -= gUnknown_20399DC->field_3E22;
            gUnknown_20399DC->field_3E1C -= gUnknown_20399DC->field_3E24;
            gUnknown_20399DC->field_3D4B--;
            if (gUnknown_20399DC->field_3E14 > 0)
                gUnknown_20399DC->field_3E14--;
        }
    }
    data.v0 = gUnknown_20399DC->field_3E16;
    data.v2 = gUnknown_20399DC->field_3E18;
    data.v4 = gUnknown_20399DC->field_3E1A;
    data.v6 = gUnknown_20399DC->field_3E1C;
    sub_80C4CF0(1, &data);
    sub_80C4C48(gUnknown_20399DC->field_3E14);
    return FALSE;
}

void nullsub_63(struct Sprite * sprite)
{

}

void sub_80C210C(u8 a0, u8 a1, u8 a2)
{
    u8 spriteId;
    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399E0->field_000[a0],
        .size = 0x400,
        .tag = a1
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF3A4,
        .tag = a2
    };
    struct SpriteTemplate template = {
        .tileTag = a1,
        .paletteTag = a2,
        .oam = &gUnknown_83F1C20,
        .anims = gUnknown_83F1C30,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = nullsub_63
    };

    gUnknown_20399E0->field_000[a0]->field_408 = a1;
    gUnknown_20399E0->field_000[a0]->field_40A = a2;
    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    spriteId = CreateSprite(&template, gUnknown_20399E0->field_000[a0]->field_404, gUnknown_20399E0->field_000[a0]->field_406, 0);
    gUnknown_20399E0->field_000[a0]->field_400 = &gSprites[spriteId];
    gSprites[spriteId].invisible = TRUE;
}

void sub_80C2208(u8 taskId, TaskFunc taskFunc)
{
    u8 i;

    gUnknown_20399E0 = AllocZeroed(sizeof(struct UnkStruct_20399E0));
    for (i = 0; i < 6; i++)
    {
        gUnknown_20399E0->field_000[i] = AllocZeroed(sizeof(struct UnkStruct_20399E0_000));
        gUnknown_20399E0->field_000[i]->field_404 = 32 * (i / 3) + 0x68;
        gUnknown_20399E0->field_000[i]->field_406 = 64 * (i % 3) + 0x28;
    }
    sub_80C4AAC(0);
    sub_80C4BE4();
    sub_80C24BC();
    sub_80C0A88(1);
    gUnknown_20399E0->field_CC8 = taskFunc;
    gTasks[taskId].func = sub_80C267C;
}

void sub_80C22C4(u8 a0, bool8 a1)
{
    u8 i;
    if (a0 == 6)
    {
        for (i = 0; i < 6; i++)
        {
            gUnknown_20399E0->field_000[i]->field_400->invisible = a1;
        }
    }
    else
    {
        gUnknown_20399E0->field_000[a0]->field_400->invisible = a1;
    }
}

bool8 sub_80C2344(void)
{
    switch (gUnknown_20399E0->field_CCD)
    {
    case 0:
        LZ77UnCompWram(gUnknown_83F12CC, gUnknown_20399E0->field_000[0]->field_000);
        sub_80C210C(0, 4, 4);
        break;
    case 1:
        LZ77UnCompWram(gUnknown_83F1550, gUnknown_20399E0->field_000[1]->field_000);
        sub_80C210C(1, 5, 5);
        break;
    case 2:
        LZ77UnCompWram(gUnknown_83F1738, gUnknown_20399E0->field_000[2]->field_000);
        sub_80C210C(2, 6, 6);
        break;
    case 3:
        LZ77UnCompWram(gUnknown_83F13EC, gUnknown_20399E0->field_000[3]->field_000);
        sub_80C210C(3, 7, 7);
        break;
    case 4:
        LZ77UnCompWram(gUnknown_83F1640, gUnknown_20399E0->field_000[4]->field_000);
        sub_80C210C(4, 8, 8);
        break;
    case 5:
        LZ77UnCompWram(gUnknown_83F1804, gUnknown_20399E0->field_000[5]->field_000);
        sub_80C210C(5, 9, 9);
        break;
    case 6:
        LZ77UnCompWram(gUnknown_83F0330, gUnknown_20399E0->field_018);
        break;
    case 7:
        LZ77UnCompWram(gUnknown_83F0E0C, gUnknown_20399E0->field_818);
        break;
    case 8:
        LoadBgTiles(1, gUnknown_20399E0->field_018, BG_SCREEN_SIZE, 0x000);
        break;
    default:
        return TRUE;
    }
    gUnknown_20399E0->field_CCD++;
    return FALSE;
}

void sub_80C24BC(void)
{
    struct UnkStruct_80C4CF0 data;
    data.v0 = gUnknown_20399E0->field_000[0]->field_404 + 8;
    data.v2 = 0x10;
    data.v4 = gUnknown_20399E0->field_000[3]->field_404 - 8;
    data.v6 = 0xA0;
    sub_80C4C2C(0, 2, 0);
    sub_80C4C74(18, 0);
    sub_80C4C88(16);
    sub_80C4CF0(0, &data);
    sub_80C4C9C(0, 0);
}

void sub_80C253C(void)
{
    struct UnkStruct_80C4CF0 data = gUnknown_83F1C34;
    sub_80C4BE4();
    sub_80C4C2C(2, 41, 128);
    sub_80C4C48(gUnknown_20399E0->field_CD0);
    sub_80C4C74(55, 0);
    sub_80C4C88(18);
    sub_80C4CF0(0, &data);
    sub_80C4C9C(0, 0);
}

void sub_80C2594(u8 taskId)
{
    gTasks[taskId].func = gUnknown_20399E0->field_CC8;
}

void sub_80C25BC(void)
{
    u8 i;
    sub_80C2604();
    for (i = 0; i < 6; i++)
    {
        FREE_IF_NOT_NULL(gUnknown_20399E0->field_000[i]);
    }
    FREE_IF_NOT_NULL(gUnknown_20399E0);
}

void sub_80C2604(void)
{
    u8 i;
    for (i = 0; i < 6; i++)
    {
        gUnknown_20399E0->field_000[i]->field_404 = gUnknown_20399E0->field_000[i]->field_400->pos1.x;
        gUnknown_20399E0->field_000[i]->field_406 = gUnknown_20399E0->field_000[i]->field_400->pos1.y;
        if (gUnknown_20399E0->field_000[i]->field_400 != NULL)
        {
            DestroySprite(gUnknown_20399E0->field_000[i]->field_400);
            FreeSpriteTilesByTag(gUnknown_20399E0->field_000[i]->field_408);
            FreeSpritePaletteByTag(gUnknown_20399E0->field_000[i]->field_40A);
        }
    }
}

void sub_80C267C(u8 taskId)
{
    switch (gUnknown_20399E0->field_CCC)
    {
    case 0:
        sub_80C08E0();
        gUnknown_20399E0->field_CCC++;
        break;
    case 1:
        if (sub_80C2344() == TRUE)
            gUnknown_20399E0->field_CCC++;
        break;
    case 2:
        CopyToBgTilemapBufferRect(1, gUnknown_20399E0->field_818, 0, 0, 30, 20);
        gUnknown_20399E0->field_CCC++;
        break;
    case 3:
        CopyBgTilemapBufferToVram(1);
        BlendPalettes(0xFFFFFFFF, 0x10, RGB_BLACK);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        sub_80C08F4();
        gUnknown_20399E0->field_CCC++;
        break;
    case 4:
        ShowBg(0);
        ShowBg(3);
        ShowBg(1);
        sub_80C22C4(6, FALSE);
        sub_80C2B48();
        gUnknown_20399E0->field_CCC++;
        break;
    case 5:
        if (!gPaletteFade.active)
        {
            gUnknown_20399E0->field_CCC++;
            PlaySE(SE_CARD3);
        }
        break;
    case 6:
        if (sub_80C29A4() == TRUE)
            gUnknown_20399E0->field_CCC++;
        break;
    case 7:
        sub_80C4324(FALSE);
        sub_80C3154(FALSE);
        gUnknown_20399E0->field_CCC++;
        break;
    case 8:
        gUnknown_20399E0->field_CD0 = 15;
        sub_80C253C();
        sub_80C0A88(0);
        sub_80C48BC(sub_80C0E20(), 25, 0);
        sub_80C4960(sub_80C0E20(), 25, 0);
        gUnknown_20399E0->field_CCC++;
        break;
    case 9:
        sub_80C4E18(gUnknown_8418EB5);
        if (sub_80C3AC8(1) != 2)
            sub_80C4E74(gUnknown_8418E8B);
        else
            sub_80C4E74(gUnknown_8418E8D);
        sub_80C4ED0(FALSE);
        gUnknown_20399E0->field_CCC++;
        break;
    case 10:
        LoadPalette(&gUnknown_83EF23C[15], 0x00, 2);
        LoadPalette(&gUnknown_83EF23C[15], 0x10, 2);
        LoadPalette(&gUnknown_83EF23C[15], 0x20, 2);
        LoadPalette(&gUnknown_83EF23C[15], 0x30, 2);
        LoadPalette(&gUnknown_83EF23C[15], 0x40, 2);
        gUnknown_20399E0->field_CCC++;
        break;
    case 11:
        FillBgTilemapBufferRect(1, 0x002, 0, 1, 1, 1, 0x2);
        FillBgTilemapBufferRect(1, 0x003, 1, 1, 1, 1, 0x2);
        FillBgTilemapBufferRect(1, 0x03E, 28, 1, 1, 1, 0x2);
        FillBgTilemapBufferRect(1, 0x03F, 29, 1, 1, 1, 0x2);
        FillBgTilemapBufferRect(1, 0x03D, 2, 1, 26, 1, 0x2);
        CopyBgTilemapBufferToVram(1);
        m4aSongNumStop(SE_CARD3);
        PlaySE(SE_HI_TURUN);
        gUnknown_20399E0->field_CCC++;
        break;
    case 12:
        if (gUnknown_20399E0->field_CD0 == 2)
        {
            sub_80C22C4(6, TRUE);
            gUnknown_20399E0->field_CCC++;
            sub_80C4C48(0);
        }
        else
        {
            gUnknown_20399E0->field_CD0--;
            sub_80C4C48(gUnknown_20399E0->field_CD0);
        }
        break;
    case 13:
        sub_80C4B30(0);
        sub_80C0BB0();
        gUnknown_20399E0->field_CCC++;
        break;
    default:
        sub_80C2604();
        sub_80C2594(taskId);
        break;
    }
}

bool8 sub_80C29A4(void)
{
    sub_80C2B48();
    if (gUnknown_20399E0->field_000[0]->field_400->pos1.x == 0)
    {
        return TRUE;
    }
    else if (gUnknown_20399E0->field_CCE > 17)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x -= 1;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x -= 1;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x -= 1;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x += 1;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x += 1;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x += 1;
    }
    else if (gUnknown_20399E0->field_CCE > 14)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x -= 2;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x -= 2;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x -= 2;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x += 2;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x += 2;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x += 2;
    }
    else if (gUnknown_20399E0->field_CCE > 10)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x -= 3;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x -= 3;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x -= 3;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x += 3;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x += 3;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x += 3;
    }
    else if (gUnknown_20399E0->field_CCE > 6)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x -= 5;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x -= 5;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x -= 5;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x += 5;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x += 5;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x += 5;
    }
    else
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x -= 8;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x -= 8;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x -= 8;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x += 8;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x += 8;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x += 8;
    }
    gUnknown_20399E0->field_CCE++;
    return FALSE;
}

void sub_80C2B48(void)
{
    struct UnkStruct_80C4CF0 data;
    data.v0 = gUnknown_20399E0->field_000[0]->field_400->pos1.x;
    data.v2 = 0x10;
    data.v4 = gUnknown_20399E0->field_000[3]->field_400->pos1.x;
    data.v6 = 0xA0;
    sub_80C4CF0(0, &data);
}

void sub_80C2B9C(void)
{
    struct UnkStruct_80C4CF0 data;
    data.v0 = gUnknown_20399E0->field_000[0]->field_404 + 16;
    data.v2 = 0x10;
    data.v4 = gUnknown_20399E0->field_000[3]->field_404 - 16;
    data.v6 = 0xA0;
    sub_80C4C2C(0, 2, 0);
    sub_80C4C74(18, 0);
    sub_80C4C88(16);
    sub_80C4CF0(0, &data);
    sub_80C4C9C(0, 0);
}

void sub_80C2C1C(u8 taskId)
{
    gTasks[taskId].func = sub_80C2C7C;
}

void sub_80C2C38(void)
{
    sub_80C210C(0, 4, 4);
    sub_80C210C(1, 5, 5);
    sub_80C210C(2, 6, 6);
    sub_80C210C(3, 7, 7);
    sub_80C210C(4, 8, 8);
    sub_80C210C(5, 9, 9);
}

void sub_80C2C7C(u8 taskId)
{
    switch (gUnknown_20399E0->field_CCF)
    {
    case 0:
        sub_80C4ED0(TRUE);
        CopyWindowToVram(3, 3);
        CopyWindowToVram(4, 3);
        gUnknown_20399E0->field_CCF++;
        break;
    case 1:
        sub_80C2C38();
        gUnknown_20399E0->field_CCF++;
        break;
    case 2:
        LoadPalette(gUnknown_83EF2DC, 0x00, 0xA0);
        gUnknown_20399E0->field_CCF++;
        break;
    case 3:
        sub_80C22C4(6, FALSE);
        sub_80C4324(TRUE);
        sub_80C3154(TRUE);
        sub_80C4960(255, 25, 1);
        sub_80C48BC(255, 25, 1);
        gUnknown_20399E0->field_CCE = 0;
        gUnknown_20399E0->field_CD0 = 0;
        gUnknown_20399E0->field_CCF++;
        break;
    case 4:
        sub_80C253C();
        gUnknown_20399E0->field_CCF++;
        break;
    case 5:
        if (gUnknown_20399E0->field_CD0 == 15)
        {
            sub_80C4C48(gUnknown_20399E0->field_CD0);
            gUnknown_20399E0->field_CCF++;
        }
        else
        {
            gUnknown_20399E0->field_CD0++;
            sub_80C4C48(gUnknown_20399E0->field_CD0);
        }
        break;
    case 6:
        sub_80C2B9C();
        sub_80C2B48();
        PlaySE(SE_CARD2);
        gUnknown_20399E0->field_CCF++;
        break;
    case 7:
        if (sub_80C2E1C() == TRUE)
            gUnknown_20399E0->field_CCF++;
        break;
    default:
        gTasks[taskId].func = gUnknown_20399E0->field_CC8;
        break;
    }
}


bool8 sub_80C2E1C(void)
{
    sub_80C2B48();
    if (gUnknown_20399E0->field_000[0]->field_400->pos1.x == 104)
    {
        return TRUE;
    }
    else if (gUnknown_20399E0->field_CCE > 17)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x += 1;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x += 1;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x += 1;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x -= 1;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x -= 1;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x -= 1;
    }
    else if (gUnknown_20399E0->field_CCE > 14)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x += 2;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x += 2;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x += 2;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x -= 2;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x -= 2;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x -= 2;
    }
    else if (gUnknown_20399E0->field_CCE > 10)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x += 3;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x += 3;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x += 3;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x -= 3;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x -= 3;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x -= 3;
    }
    else if (gUnknown_20399E0->field_CCE > 6)
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x += 5;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x += 5;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x += 5;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x -= 5;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x -= 5;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x -= 5;
    }
    else
    {
        gUnknown_20399E0->field_000[0]->field_400->pos1.x += 8;
        gUnknown_20399E0->field_000[1]->field_400->pos1.x += 8;
        gUnknown_20399E0->field_000[2]->field_400->pos1.x += 8;
        gUnknown_20399E0->field_000[3]->field_400->pos1.x -= 8;
        gUnknown_20399E0->field_000[4]->field_400->pos1.x -= 8;
        gUnknown_20399E0->field_000[5]->field_400->pos1.x -= 8;
    }
    gUnknown_20399E0->field_CCE++;
    return FALSE;
}

void sub_80C2FC0(struct Sprite * sprite)
{
    if (gUnknown_20399E4->field_00C != 0)
    {
        sprite->pos1.x += gUnknown_20399E4->field_008;
        sprite->pos1.y += gUnknown_20399E4->field_00A;
        gUnknown_20399E4->field_00C--;
    }
    else
    {
        gUnknown_20399E4->field_01C->pos1.x = 8 * gUnknown_20399E4->field_000 + 36;
        gUnknown_20399E4->field_01C->pos1.y = 8 * gUnknown_20399E4->field_002 + 36;
    }
}

void sub_80C3008(u16 a0, u16 a1)
{
    gUnknown_20399E4 = AllocZeroed(sizeof(struct UnkStruct_20399E4));
    LZ77UnCompWram(gUnknown_83EF4E0, gUnknown_20399E4->field_024);
    gUnknown_20399E4->field_020 = a0;
    gUnknown_20399E4->field_022 = a1;
    sub_80C3D40();
    gUnknown_20399E4->field_004 = 8 * gUnknown_20399E4->field_000 + 36;
    gUnknown_20399E4->field_006 = 8 * gUnknown_20399E4->field_002 + 36;
    gUnknown_20399E4->field_010 = sub_80C31C0;
    gUnknown_20399E4->field_016 = sub_80C35DC(gUnknown_20399E4->field_014);
    gUnknown_20399E4->field_018 = sub_80C3878(sub_80C4164(sub_80C0E20(), 1, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000));
    sub_80C309C();
}

void sub_80C309C(void)
{
    u8 spriteId;
    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399E4->field_024,
        .size = 0x100,
        .tag = gUnknown_20399E4->field_020
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF25C,
        .tag = gUnknown_20399E4->field_022
    };
    struct SpriteTemplate template = {
        .tileTag = gUnknown_20399E4->field_020,
        .paletteTag = gUnknown_20399E4->field_022,
        .oam = &gUnknown_83F1C3C,
        .anims = gUnknown_83F1C50,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80C2FC0
    };

    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    spriteId = CreateSprite(&template, gUnknown_20399E4->field_004, gUnknown_20399E4->field_006, 0);
    gUnknown_20399E4->field_01C = &gSprites[spriteId];
    sub_80C3154(TRUE);
}

void sub_80C3154(bool8 a0)
{
    gUnknown_20399E4->field_01C->invisible = a0;
}

void sub_80C3178(void)
{
    gUnknown_20399E4->field_00E = 0;
}

void sub_80C3188(void)
{
    if (gUnknown_20399E4->field_01C != NULL)
    {
        DestroySprite(gUnknown_20399E4->field_01C);
        FreeSpriteTilesByTag(gUnknown_20399E4->field_020);
        FreeSpritePaletteByTag(gUnknown_20399E4->field_022);
    }
    FREE_IF_NOT_NULL(gUnknown_20399E4);
}

u8 sub_80C31C0(void)
{
    u8 ret = 0;
    gUnknown_20399E4->field_008 = 0;
    gUnknown_20399E4->field_00A = 0;

    if (JOY_HELD(DPAD_UP))
    {
        if (gUnknown_20399E4->field_002 > 0)
        {
            gUnknown_20399E4->field_00A = -2;
            ret = 1;
        }
    }
    if (JOY_HELD(DPAD_DOWN))
    {
        if (gUnknown_20399E4->field_002 < 14)
        {
            gUnknown_20399E4->field_00A = 2;
            ret = 1;
        }
    }
    if (JOY_HELD(DPAD_RIGHT))
    {
        if (gUnknown_20399E4->field_000 < 21)
        {
            gUnknown_20399E4->field_008 = 2;
            ret = 1;
        }
    }
    if (JOY_HELD(DPAD_LEFT))
    {
        if (gUnknown_20399E4->field_000 > 0)
        {
            gUnknown_20399E4->field_008 = -2;
            ret = 1;
        }
    }
    if (JOY_NEW(A_BUTTON))
    {
        ret = 4;
        if (gUnknown_20399E4->field_000 == 21 && gUnknown_20399E4->field_002 == 13)
        {
            PlaySE(SE_W063B);
            ret = 6;
        }
        if (gUnknown_20399E4->field_000 == 21 && gUnknown_20399E4->field_002 == 11)
        {
            if (sub_80C0E04(0) == TRUE)
            {
                PlaySE(SE_W063B);
                ret = 5;
            }
        }
    }
    else if (!JOY_NEW(B_BUTTON))
    {
        if (JOY_REPT(START_BUTTON))
        {
            sub_80C3418();
            gUnknown_20399E4->field_014 = sub_80C4164(sub_80C0E20(), 0, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
            gUnknown_20399E4->field_016 = sub_80C35DC(gUnknown_20399E4->field_014);
            gUnknown_20399E4->field_018 = sub_80C3878(sub_80C4164(sub_80C0E20(), 1, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000));
            return 3;
        }
        else if (JOY_NEW(SELECT_BUTTON) && gUnknown_20399D4->field_47BC == CB2_ReturnToField)
        {
            ret = 6;
        }
    }
    else
    {
        ret = 6;
    }
    if (ret == 1)
    {
        gUnknown_20399E4->field_00C = 4;
        gUnknown_20399E4->field_010 = sub_80C3348;
    }
    return ret;
}

u8 sub_80C3348(void)
{
    if (gUnknown_20399E4->field_00C != 0)
        return 2;
    if (gUnknown_20399E4->field_008 > 0)
        gUnknown_20399E4->field_000++;
    if (gUnknown_20399E4->field_008 < 0)
        gUnknown_20399E4->field_000--;
    if (gUnknown_20399E4->field_00A > 0)
        gUnknown_20399E4->field_002++;
    if (gUnknown_20399E4->field_00A < 0)
        gUnknown_20399E4->field_002--;
    gUnknown_20399E4->field_014 = sub_80C4164(sub_80C0E20(), 0, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
    gUnknown_20399E4->field_016 = sub_80C35DC(gUnknown_20399E4->field_014);
    gUnknown_20399E4->field_018 = sub_80C3878(sub_80C4164(sub_80C0E20(), 1, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000));
    gUnknown_20399E4->field_010 = sub_80C31C0;
    return 3;
}

u8 sub_80C3400(void)
{
    return gUnknown_20399E4->field_010();
}

void sub_80C3418(void)
{
    if (sub_80C0E04(0) == 1)
    {
        gUnknown_20399E4->field_00E++;
        gUnknown_20399E4->field_00E %= 3;
        if (gUnknown_20399E4->field_00E == 0 && sub_80C0E20() != sub_80C0E34())
        {
            gUnknown_20399E4->field_00E++;
        }
        switch (gUnknown_20399E4->field_00E)
        {
        case 0:
        default:
            gUnknown_20399E4->field_000 = sub_80C4380();
            gUnknown_20399E4->field_002 = sub_80C438C();
            break;
        case 1:
            gUnknown_20399E4->field_000 = 21;
            gUnknown_20399E4->field_002 = 11;
            break;
        case 2:
            gUnknown_20399E4->field_002 = 13;
            gUnknown_20399E4->field_000 = 21;
            break;
        }
    }
    else
    {
        gUnknown_20399E4->field_00E++;
        gUnknown_20399E4->field_00E %= 2;
        switch (gUnknown_20399E4->field_00E)
        {
        case 0:
        default:
            gUnknown_20399E4->field_000 = sub_80C4380();
            gUnknown_20399E4->field_002 = sub_80C438C();
            break;
        case 1:
            gUnknown_20399E4->field_002 = 13;
            gUnknown_20399E4->field_000 = 21;
            break;
        }
    }
    gUnknown_20399E4->field_01C->pos1.x = 8 * gUnknown_20399E4->field_000 + 36;
    gUnknown_20399E4->field_01C->pos1.y = 8 * gUnknown_20399E4->field_002 + 36;
    gUnknown_20399E4->field_014 = sub_80C4164(sub_80C0E20(), 0, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
}

u16 sub_80C3508(void)
{
    return gUnknown_20399E4->field_000;
}

u16 sub_80C3514(void)
{
    return gUnknown_20399E4->field_002;
}

u16 sub_80C3520(void)
{
    u8 ret;
    if (gUnknown_20399E4->field_002 < 0
     || gUnknown_20399E4->field_002 > 14
     || gUnknown_20399E4->field_000 < 0
     || gUnknown_20399E4->field_000 > 21)
        return MAPSEC_NONE;

    ret = sub_80C4164(sub_80C0E20(), 0, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
    if ((ret == MAPSEC_NAVEL_ROCK || ret == MAPSEC_BIRTH_ISLAND) && !FlagGet(FLAG_WORLD_MAP_NAVEL_ROCK_EXTERIOR))
        ret = MAPSEC_NONE;
    return ret;
}

u16 sub_80C3580(void)
{
    u8 ret;
    if (gUnknown_20399E4->field_002 < 0
     || gUnknown_20399E4->field_002 > 14
     || gUnknown_20399E4->field_000 < 0
     || gUnknown_20399E4->field_000 > 21)
        return MAPSEC_NONE;

    ret = sub_80C4164(sub_80C0E20(), 1, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
    if (ret == MAPSEC_CERULEAN_CAVE && !FlagGet(FLAG_SYS_CAN_LINK_WITH_RS))
        ret = MAPSEC_NONE;
    return ret;
}

u8 sub_80C35DC(u8 mapsec)
{
    switch (mapsec)
    {
    case MAPSEC_PALLET_TOWN:
        return FlagGet(FLAG_WORLD_MAP_PALLET_TOWN) ? 2 : 3;
    case MAPSEC_VIRIDIAN_CITY:
        return FlagGet(FLAG_WORLD_MAP_VIRIDIAN_CITY) ? 2 : 3;
    case MAPSEC_PEWTER_CITY:
        return FlagGet(FLAG_WORLD_MAP_PEWTER_CITY) ? 2 : 3;
    case MAPSEC_CERULEAN_CITY:
        return FlagGet(FLAG_WORLD_MAP_CERULEAN_CITY) ? 2 : 3;
    case MAPSEC_LAVENDER_TOWN:
        return FlagGet(FLAG_WORLD_MAP_LAVENDER_TOWN) ? 2 : 3;
    case MAPSEC_VERMILION_CITY:
        return FlagGet(FLAG_WORLD_MAP_VERMILION_CITY) ? 2 : 3;
    case MAPSEC_CELADON_CITY:
        return FlagGet(FLAG_WORLD_MAP_CELADON_CITY) ? 2 : 3;
    case MAPSEC_FUCHSIA_CITY:
        return FlagGet(FLAG_WORLD_MAP_FUCHSIA_CITY) ? 2 : 3;
    case MAPSEC_CINNABAR_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_CINNABAR_ISLAND) ? 2 : 3;
    case MAPSEC_INDIGO_PLATEAU:
        return FlagGet(FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR) ? 2 : 3;
    case MAPSEC_SAFFRON_CITY:
        return FlagGet(FLAG_WORLD_MAP_SAFFRON_CITY) ? 2 : 3;
    case MAPSEC_ONE_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_ONE_ISLAND) ? 2 : 3;
    case MAPSEC_TWO_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_TWO_ISLAND) ? 2 : 3;
    case MAPSEC_THREE_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_THREE_ISLAND) ? 2 : 3;
    case MAPSEC_FOUR_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_FOUR_ISLAND) ? 2 : 3;
    case MAPSEC_FIVE_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_FIVE_ISLAND) ? 2 : 3;
    case MAPSEC_SEVEN_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND) ? 2 : 3;
    case MAPSEC_SIX_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_SIX_ISLAND) ? 2 : 3;
    case MAPSEC_ROUTE_4_FLYDUP:
        if (!sub_80C0E04(3))
            return 0;
        return FlagGet(FLAG_WORLD_MAP_ROUTE4_POKEMON_CENTER_1F) ? 2 : 3;
    case MAPSEC_ROUTE_10_FLYDUP:
        return FlagGet(FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F) ? 2 : 3;
    case MAPSEC_NONE:
        return 0;
    default:
        return 1;
    }
}

u8 sub_80C3878(u8 mapsec)
{
    switch (mapsec)
    {
    case MAPSEC_NONE:
        return 0;
    case MAPSEC_VIRIDIAN_FOREST:
        return FlagGet(FLAG_WORLD_MAP_VIRIDIAN_FOREST) ? 2 : 3;
    case MAPSEC_MT_MOON:
        return FlagGet(FLAG_WORLD_MAP_MT_MOON_1F) ? 2 : 3;
    case MAPSEC_S_S_ANNE:
        return FlagGet(FLAG_WORLD_MAP_SSANNE_EXTERIOR) ? 2 : 3;
    case MAPSEC_UNDERGROUND_PATH:
        return FlagGet(FLAG_WORLD_MAP_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL) ? 2 : 3;
    case MAPSEC_UNDERGROUND_PATH_2:
        return FlagGet(FLAG_WORLD_MAP_UNDERGROUND_PATH_EAST_WEST_TUNNEL) ? 2 : 3;
    case MAPSEC_DIGLETTS_CAVE:
        return FlagGet(FLAG_WORLD_MAP_DIGLETTS_CAVE_B1F) ? 2 : 3;
    case MAPSEC_KANTO_VICTORY_ROAD:
        return FlagGet(FLAG_WORLD_MAP_VICTORY_ROAD_1F) ? 2 : 3;
    case MAPSEC_ROCKET_HIDEOUT:
        return FlagGet(FLAG_WORLD_MAP_ROCKET_HIDEOUT_B1F) ? 2 : 3;
    case MAPSEC_SILPH_CO:
        return FlagGet(FLAG_WORLD_MAP_SILPH_CO_1F) ? 2 : 3;
    case MAPSEC_POKEMON_MANSION:
        return FlagGet(FLAG_WORLD_MAP_POKEMON_MANSION_1F) ? 2 : 3;
    case MAPSEC_KANTO_SAFARI_ZONE:
        return FlagGet(FLAG_WORLD_MAP_SAFARI_ZONE_CENTER) ? 2 : 3;
    case MAPSEC_POKEMON_LEAGUE:
        return FlagGet(FLAG_WORLD_MAP_POKEMON_LEAGUE_LORELEIS_ROOM) ? 2 : 3;
    case MAPSEC_ROCK_TUNNEL:
        return FlagGet(FLAG_WORLD_MAP_ROCK_TUNNEL_1F) ? 2 : 3;
    case MAPSEC_SEAFOAM_ISLANDS:
        return FlagGet(FLAG_WORLD_MAP_SEAFOAM_ISLANDS_1F) ? 2 : 3;
    case MAPSEC_POKEMON_TOWER:
        return FlagGet(FLAG_WORLD_MAP_POKEMON_TOWER_1F) ? 2 : 3;
    case MAPSEC_CERULEAN_CAVE:
        return FlagGet(FLAG_WORLD_MAP_CERULEAN_CAVE_1F) ? 2 : 3;
    case MAPSEC_POWER_PLANT:
        return FlagGet(FLAG_WORLD_MAP_POWER_PLANT) ? 2 : 3;
    case MAPSEC_NAVEL_ROCK:
        return FlagGet(FLAG_WORLD_MAP_NAVEL_ROCK_EXTERIOR) ? 2 : 3;
    case MAPSEC_MT_EMBER:
        return FlagGet(FLAG_WORLD_MAP_MT_EMBER_EXTERIOR) ? 2 : 3;
    case MAPSEC_BERRY_FOREST:
        return FlagGet(FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST) ? 2 : 3;
    case MAPSEC_ICEFALL_CAVE:
        return FlagGet(FLAG_WORLD_MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE) ? 2 : 3;
    case MAPSEC_ROCKET_WAREHOUSE:
        return FlagGet(FLAG_WORLD_MAP_FIVE_ISLAND_ROCKET_WAREHOUSE) ? 2 : 3;
    case MAPSEC_TRAINER_TOWER_2:
        return FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND_TRAINER_TOWER_LOBBY) ? 2 : 3;
    case MAPSEC_DOTTED_HOLE:
        return FlagGet(FLAG_WORLD_MAP_SIX_ISLAND_DOTTED_HOLE_1F) ? 2 : 3;
    case MAPSEC_LOST_CAVE:
        return FlagGet(FLAG_WORLD_MAP_FIVE_ISLAND_LOST_CAVE_ENTRANCE) ? 2 : 3;
    case MAPSEC_PATTERN_BUSH:
        return FlagGet(FLAG_WORLD_MAP_SIX_ISLAND_PATTERN_BUSH) ? 2 : 3;
    case MAPSEC_ALTERING_CAVE:
        return FlagGet(FLAG_WORLD_MAP_SIX_ISLAND_ALTERING_CAVE) ? 2 : 3;
    case MAPSEC_TANOBY_CHAMBERS:
        return FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER) ? 2 : 3;
    case MAPSEC_THREE_ISLE_PATH:
        return FlagGet(FLAG_WORLD_MAP_THREE_ISLAND_DUNSPARCE_TUNNEL) ? 2 : 3;
    case MAPSEC_TANOBY_KEY:
        return FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND_SEVAULT_CANYON_TANOBY_KEY) ? 2 : 3;
    case MAPSEC_BIRTH_ISLAND:
        return FlagGet(FLAG_WORLD_MAP_BIRTH_ISLAND_EXTERIOR) ? 2 : 3;
    default:
        return 1;
    }
}

u8 sub_80C3AC8(u8 a0)
{
    switch (a0)
    {
    default:
        return gUnknown_20399E4->field_016;
    case 0:
        return gUnknown_20399E4->field_016;
    case 1:
        return gUnknown_20399E4->field_018;
    }
}

u16 sub_80C3B00(void)
{
    return Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum)->regionMapSectionId;
}

void sub_80C3B28(void)
{
    u16 width;
    u32 divisor;
    u16 height;
    u16 x;
    u16 y;
    u32 r6;
    const struct MapHeader * mapHeader;
    struct WarpData * warp;

    switch (get_map_light_level_by_bank_and_number(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
    {
    default:
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        gUnknown_20399E4->field_014 = gMapHeader.regionMapSectionId;
        width = gMapHeader.mapLayout->width;
        height = gMapHeader.mapLayout->height;
        x = gSaveBlock1Ptr->pos.x;
        y = gSaveBlock1Ptr->pos.y;
        break;
    case 4:
    case 7:
        mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->escapeWarp.mapGroup, gSaveBlock1Ptr->escapeWarp.mapNum);
        gUnknown_20399E4->field_014 = mapHeader->regionMapSectionId;
        width = mapHeader->mapLayout->width;
        height = mapHeader->mapLayout->height;
        x = gSaveBlock1Ptr->escapeWarp.x;
        y = gSaveBlock1Ptr->escapeWarp.y;
        break;
    case 9:
        mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->warp2.mapGroup, gSaveBlock1Ptr->warp2.mapNum);
        gUnknown_20399E4->field_014 = mapHeader->regionMapSectionId;
        width = mapHeader->mapLayout->width;
        height = mapHeader->mapLayout->height;
        x = gSaveBlock1Ptr->warp2.x;
        y = gSaveBlock1Ptr->warp2.y;
        break;
    case 8:
        if ((gUnknown_20399E4->field_014 = gMapHeader.regionMapSectionId) != MAPSEC_SPECIAL_AREA)
        {
            warp = &gSaveBlock1Ptr->escapeWarp;
            mapHeader = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);
        }
        else
        {
            warp = &gSaveBlock1Ptr->warp2;
            mapHeader = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);
            gUnknown_20399E4->field_014 = mapHeader->regionMapSectionId;
        }
        width = mapHeader->mapLayout->width;
        height = mapHeader->mapLayout->height;
        x = warp->x;
        y = warp->y;
        break;
    }

    gUnknown_20399E4->field_014 -= MAPSECS_KANTO;
    divisor = width / gUnknown_83F2178[gUnknown_20399E4->field_014][0];
    if (divisor == 0)
        divisor = 1;
    x /= divisor;
    if (x >= gUnknown_83F2178[gUnknown_20399E4->field_014][0])
        x = gUnknown_83F2178[gUnknown_20399E4->field_014][0] - 1;
    divisor = height / gUnknown_83F2178[gUnknown_20399E4->field_014][1];
    if (divisor == 0)
        divisor = 1;
    y /= divisor;
    if (y >= gUnknown_83F2178[gUnknown_20399E4->field_014][1])
        y = gUnknown_83F2178[gUnknown_20399E4->field_014][1] - 1;
    gUnknown_20399E4->field_000 = x + gUnknown_83F1E60[gUnknown_20399E4->field_014][0];
    gUnknown_20399E4->field_002 = y + gUnknown_83F1E60[gUnknown_20399E4->field_014][1];
}

void sub_80C3D40(void)
{
    switch (sub_80C3B00())
    {
    case MAPSEC_KANTO_SAFARI_ZONE:
        gUnknown_20399E4->field_000 = 12;
        gUnknown_20399E4->field_002 = 12;
        break;
    case MAPSEC_SILPH_CO:
        gUnknown_20399E4->field_000 = 14;
        gUnknown_20399E4->field_002 = 6;
        break;
    case MAPSEC_POKEMON_MANSION:
        gUnknown_20399E4->field_000 = 4;
        gUnknown_20399E4->field_002 = 14;
        break;
    case MAPSEC_POKEMON_TOWER:
        gUnknown_20399E4->field_000 = 18;
        gUnknown_20399E4->field_002 = 6;
        break;
    case MAPSEC_POWER_PLANT:
        gUnknown_20399E4->field_000 = 18;
        gUnknown_20399E4->field_002 = 4;
        break;
    case MAPSEC_S_S_ANNE:
        gUnknown_20399E4->field_000 = 14;
        gUnknown_20399E4->field_002 = 9;
        break;
    case MAPSEC_POKEMON_LEAGUE:
        gUnknown_20399E4->field_000 = 2;
        gUnknown_20399E4->field_002 = 3;
        break;
    case MAPSEC_ROCKET_HIDEOUT:
        gUnknown_20399E4->field_000 = 11;
        gUnknown_20399E4->field_002 = 6;
        break;
    case MAPSEC_UNDERGROUND_PATH:
        gUnknown_20399E4->field_000 = 14;
        gUnknown_20399E4->field_002 = 7;
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(UNDERGROUND_PATH_NORTH_ENTRANCE))
        {
            gUnknown_20399E4->field_000 = 14; // optimized out but required to match
            gUnknown_20399E4->field_002 = 5;
        }
        break;
    case MAPSEC_UNDERGROUND_PATH_2:
        gUnknown_20399E4->field_000 = 12;
        gUnknown_20399E4->field_002 = 6;
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(UNDERGROUND_PATH_EAST_ENTRANCE))
        {
            gUnknown_20399E4->field_000 = 15;
            gUnknown_20399E4->field_002 = 6; // optimized out but required to match
        }
        break;
    case MAPSEC_BIRTH_ISLAND:
        gUnknown_20399E4->field_000 = 18;
        gUnknown_20399E4->field_002 = 13;
        break;
    case MAPSEC_NAVEL_ROCK:
        gUnknown_20399E4->field_000 = 10;
        gUnknown_20399E4->field_002 = 8;
        break;
    case MAPSEC_TRAINER_TOWER_2:
        gUnknown_20399E4->field_000 = 5;
        gUnknown_20399E4->field_002 = 6;
        break;
    case MAPSEC_MT_EMBER:
        gUnknown_20399E4->field_000 = 2;
        gUnknown_20399E4->field_002 = 3;
        break;
    case MAPSEC_BERRY_FOREST:
        gUnknown_20399E4->field_000 = 14;
        gUnknown_20399E4->field_002 = 12;
        break;
    case MAPSEC_PATTERN_BUSH:
        gUnknown_20399E4->field_000 = 17;
        gUnknown_20399E4->field_002 = 3;
        break;
    case MAPSEC_ROCKET_WAREHOUSE:
        gUnknown_20399E4->field_000 = 17;
        gUnknown_20399E4->field_002 = 11;
        break;
    case MAPSEC_DILFORD_CHAMBER:
    case MAPSEC_LIPTOO_CHAMBER:
    case MAPSEC_MONEAN_CHAMBER:
    case MAPSEC_RIXY_CHAMBER:
    case MAPSEC_SCUFIB_CHAMBER:
    case MAPSEC_TANOBY_CHAMBERS:
    case MAPSEC_VIAPOIS_CHAMBER:
    case MAPSEC_WEEPTH_CHAMBER:
        gUnknown_20399E4->field_000 = 9;
        gUnknown_20399E4->field_002 = 12;
        break;
    case MAPSEC_DOTTED_HOLE:
        gUnknown_20399E4->field_000 = 16;
        gUnknown_20399E4->field_002 = 8;
        break;
    case MAPSEC_VIRIDIAN_FOREST:
        gUnknown_20399E4->field_000 = 4;
        gUnknown_20399E4->field_002 = 6;
        break;
    case MAPSEC_ROUTE_2:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(PALLET_TOWN))
        {
            gUnknown_20399E4->field_000 = 4;
            gUnknown_20399E4->field_002 = 7;
        }
        else if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(CERULEAN_CITY))
        {
            gUnknown_20399E4->field_000 = 4;
            gUnknown_20399E4->field_002 = 5;
        }
        else
        {
            sub_80C3B28();
        }
        break;
    case MAPSEC_ROUTE_21:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE21_NORTH))
        {
            gUnknown_20399E4->field_000 = 4;
            gUnknown_20399E4->field_002 = 12;
        }
        else if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE21_SOUTH))
        {
            gUnknown_20399E4->field_000 = 4;
            gUnknown_20399E4->field_002 = 13;
        }
        break;
    case MAPSEC_ROUTE_5:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(VIRIDIAN_CITY))
        {
            gUnknown_20399E4->field_000 = 14;
            gUnknown_20399E4->field_002 = 5;
        }
        else
        {
            sub_80C3B28();
        }
        break;
    case MAPSEC_ROUTE_6:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(PALLET_TOWN))
        {
            gUnknown_20399E4->field_000 = 14;
            gUnknown_20399E4->field_002 = 7;
        }
        else
        {
            sub_80C3B28();
        }
        break;
    case MAPSEC_ROUTE_7:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(PALLET_TOWN))
        {
            gUnknown_20399E4->field_000 = 13;
            gUnknown_20399E4->field_002 = 6;
        }
        else
        {
            sub_80C3B28();
        }
        break;
    case MAPSEC_ROUTE_8:
        if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(PALLET_TOWN))
        {
            gUnknown_20399E4->field_000 = 15;
            gUnknown_20399E4->field_002 = 6;
        }
        else
        {
            sub_80C3B28();
        }
        break;
    default:
        sub_80C3B28();
        break;
    }
    gUnknown_20399E4->field_014 = sub_80C4164(sub_80C0E20(), 0, gUnknown_20399E4->field_002, gUnknown_20399E4->field_000);
}

u8 sub_80C4164(u8 a0, u8 a1, s16 a2, s16 a3)
{
    switch (a0)
    {
    case 0:
        return gUnknown_83F2490[a1][a2][a3];
    case 1:
        return gUnknown_83F2724[a1][a2][a3];
    case 2:
        return gUnknown_83F29B8[a1][a2][a3];
    case 3:
        return gUnknown_83F2C4C[a1][a2][a3];
    default:
        return MAPSEC_NONE;
    }
}

void sub_80C41D8(u16 a0, u16 a1)
{
    gUnknown_20399E8 = AllocZeroed(sizeof(struct UnkStruct_20399E8));
    if (gSaveBlock2Ptr->playerGender == FEMALE)
        LZ77UnCompWram(gUnknown_83EF59C, gUnknown_20399E8->field_0C);
    else
        LZ77UnCompWram(gUnknown_83EF524, gUnknown_20399E8->field_0C);
    gUnknown_20399E8->field_08 = a0;
    gUnknown_20399E8->field_0A = a1;
    gUnknown_20399E8->field_00 = sub_80C3508();
    gUnknown_20399E8->field_02 = sub_80C3514();
    sub_80C4244();
}

void sub_80C4244(void)
{
    u8 spriteId;
    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399E8->field_0C,
        .size = 0x80,
        .tag = gUnknown_20399E8->field_08
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF27C,
        .tag = gUnknown_20399E8->field_0A
    };
    struct SpriteTemplate template = {
        .tileTag = gUnknown_20399E8->field_08,
        .paletteTag = gUnknown_20399E8->field_0A,
        .oam = &gUnknown_83F1C54,
        .anims = gUnknown_83F1C64,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    };

    if (gSaveBlock2Ptr->playerGender == FEMALE)
        spritePalette.data = gUnknown_83EF29C;

    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    spriteId = CreateSprite(&template, 8 * gUnknown_20399E8->field_00 + 36, 8 * gUnknown_20399E8->field_02 + 36, 2);
    gUnknown_20399E8->field_04 = &gSprites[spriteId];
    sub_80C4324(TRUE);
}

void sub_80C4324(bool8 a0)
{
    gUnknown_20399E8->field_04->invisible = a0;
}

void sub_80C4348(void)
{
    if (gUnknown_20399E8->field_04 != NULL)
    {
        DestroySprite(gUnknown_20399E8->field_04);
        FreeSpriteTilesByTag(gUnknown_20399E8->field_08);
        FreeSpritePaletteByTag(gUnknown_20399E8->field_0A);
    }
    FREE_IF_NOT_NULL(gUnknown_20399E8);
}

u16 sub_80C4380(void)
{
    return gUnknown_20399E8->field_00;
}

u16 sub_80C438C(void)
{
    return gUnknown_20399E8->field_02;
}

void sub_80C4398(u8 a0, u8 taskId, TaskFunc taskFunc)
{
    gUnknown_20399EC = AllocZeroed(sizeof(struct UnkStruct_20399EC));
    gUnknown_20399EC->field_468 = taskFunc;
    gUnknown_20399EC->field_460 = a0;
    LZ77UnCompWram(gUnknown_83F18D8, gUnknown_20399EC->field_000);
    LZ77UnCompWram(gUnknown_83F1908, gUnknown_20399EC->field_040);
    gTasks[taskId].func = sub_80C440C;
}

void sub_80C440C(u8 taskId)
{
    switch (gUnknown_20399EC->field_463)
    {
    case 0:
        sub_80C08E0();
        gUnknown_20399EC->field_463++;
        break;
    case 1:
        sub_80C47F0();
        gUnknown_20399EC->field_463++;
        break;
    case 2:
        sub_80C4750();
        gUnknown_20399EC->field_463++;
        break;
    case 3:
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gUnknown_20399EC->field_463++;
        break;
    case 4:
        sub_80C08F4();
        gUnknown_20399EC->field_463++;
        break;
    default:
        SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) | DISPCNT_OBJ_ON);
        sub_80C44E4(taskId);
        break;
    }
}

void sub_80C44E4(u8 taskId)
{
    gTasks[taskId].func = gUnknown_20399EC->field_468;
}

void sub_80C450C(u8 a0, u8 a1, u16 a2, u16 a3, u8 a4, u8 a5)
{
    u8 spriteId;
    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399EC->field_040,
        .size = 0x100,
        .tag = a4
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF2BC,
        .tag = a5
    };
    struct SpriteTemplate template = {
        .tileTag = a4,
        .paletteTag = a5,
        .oam = &gUnknown_83F1C68,
        .anims = gUnknown_83F1C94,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    };

    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    spriteId = CreateSprite(&template, 8 * a2 + 36, 8 * a3 + 36, 1);
    gUnknown_20399EC->field_2D4[a1].field_4 = &gSprites[spriteId];
    gSprites[spriteId].invisible = TRUE;
    gUnknown_20399EC->field_2D4[a1].field_0 = a0;
}

void sub_80C4614(u8 a0, u8 a1, u16 a2, u16 a3, u8 a4, u8 a5)
{
    u8 spriteId;
    u8 r4;
    s16 r7 = 0;
    struct SpriteSheet spriteSheet = {
        .data = gUnknown_20399EC->field_000,
        .size = 0x40,
        .tag = a4
    };
    struct SpritePalette spritePalette = {
        .data = gUnknown_83EF2BC,
        .tag = a5
    };
    struct SpriteTemplate template = {
        .tileTag = a4,
        .paletteTag = a5,
        .oam = &gUnknown_83F1C70,
        .anims = gUnknown_83F1C98,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    };

    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    r4 = sub_80C4164(a0, 0, a3, a2);
    if ((sub_80C35DC(r4) == 2 || sub_80C35DC(r4) == 3) && r4 != MAPSEC_ROUTE_10_FLYDUP)
        r7 = 2;
    spriteId = CreateSprite(&template, 8 * a2 + 36 + r7, 8 * a3 + 36 + r7, 3);
    gUnknown_20399EC->field_144[a1].field_4 = &gSprites[spriteId];
    gSprites[spriteId].invisible = TRUE;
    gUnknown_20399EC->field_144[a1].field_0 = a0;
}

void sub_80C4750(void)
{
    u16 i, j, k;
    u8 r7 = 0;
    if (sub_80C0E04(3))
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 15; j++)
            {
                for (k = 0; k < 22; k++)
                {
                    if (sub_80C35DC(sub_80C4164(i, 0, j, k)) == 2)
                    {
                        sub_80C450C(i, r7, k, j, r7 + 10, 10);
                        r7++;
                    }
                }
            }
        }
    }
}

void sub_80C47F0(void)
{
    u16 i, j, k;
    u8 r6 = 0;
    u8 mapsec;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 15; j++)
        {
            for (k = 0; k < 22; k++)
            {
                mapsec = sub_80C4164(i, 1, j, k);
                if (mapsec == MAPSEC_NONE)
                    continue;
                if (mapsec == MAPSEC_CERULEAN_CAVE && !FlagGet(FLAG_SYS_CAN_LINK_WITH_RS))
                    continue;
                sub_80C4614(i, r6, k, j, r6 + 35, 10);
                if (sub_80C3878(mapsec) != 2)
                {
                    StartSpriteAnim(gUnknown_20399EC->field_144[r6].field_4, 1);
                }
                r6++;
            }
        }
    }
}
