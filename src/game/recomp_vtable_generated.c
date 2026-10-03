/* Exact runtime-observed vtable bodies extracted from xboxrecomp output. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include <stdio.h>

extern void xbox_irq_wait_for_vblank(void);
extern void godzilla_d3d_frame_hook(void);
extern void sub_000DD430(void);
extern void sub_000E0430(void);
extern void sub_000E0860(void);
extern void sub_000EA9D0(void);
extern void sub_000EAAA0(void);
extern void sub_000ECCA0(void);

uint32_t g_mainmenu_bundle_trace;

/* Four retail startup vtable bodies that fall in gaps in the seeded function
 * table.  These run once from sub_0002FD80 before the main loop; omitting them
 * left the event bus with no listeners and skipped controller initialization. */
void sub_000306D0(void)
{
    uint32_t ebp = g_ebp;

    esp -= 0x0C;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebx = ecx;
    PUSH32(esp, esi);
    PUSH32(esp, edi);

    MEM8(ebx + 0x298) = 1;
    eax = ebx + 0xD0;
    ecx = 4;
    do {
        MEM32(eax - 4) = 0xFFFFFFFFu;
        MEM8(eax) = 1;
        eax += 0x94;
    } while (--ecx != 0);

    /* Build the retail four-port device-type descriptor on the guest stack. */
    eax = esp + 0x14;
    PUSH32(esp, eax);
    PUSH32(esp, 1);
    MEM32(esp + 0x1C) = 0x001D9974u;
    MEM32(esp + 0x20) = 4;
    PUSH32(esp, 0x0003071Eu);
    sub_001DABDD();

    PUSH32(esp, 0x001D9974u);
    PUSH32(esp, 0x00030728u);
    sub_001DABE2();
    edi = 0;
    MEM32(esp + 0x10) = eax;
    MEM32(ebx + 0x290) = 0;
    esi = ebx + 0x58;
    ebp = 0x7F7FFFFFu;

    do {
        edx = 1u << (edi & 31u);
        if ((MEM32(esp + 0x10) & edx) != 0) {
            PUSH32(esp, 0);
            PUSH32(esp, 0);
            MEM32(esi - 0x18) = 0;
            ecx = esi - 0x18;
            PUSH32(esp, edi);
            PUSH32(esp, 0x001D9974u);
            MEM32(esi - 4) = ebp;
            MEM32(esi) = ebp;
            MEM32(esi + 4) = ebp;
            MEM32(esi + 8) = ebp;
            MEM32(esi + 0x74) = 0xFFFFFFFFu;
            PUSH32(esp, 0x0003077Cu);
            sub_001DA8DC();
            MEM32(esi + 0x6C) = eax;
            edx = esi + 0x52;
            MEM32(ebx + 0x290) = 0;
            eax = MEM32(esi + 0x6C);
            PUSH32(esp, edx);
            PUSH32(esp, eax);
            PUSH32(esp, 0x00030796u);
            sub_001DA93E();
        }
        ++edi;
        esi += 0x94;
    } while (edi < 4);

    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 0x0C;
    esp += 8; /* ret 4 */
}

/**
 * sub_000DBBFA
 * Shared epilogue for the sub_000DBA30 jump-table fragments.
 * Original: 0x000DBBFA - 0x000DBC03 (9 bytes)
 */
void sub_000DBBFA(void)
{
    uint32_t ebp = g_ebp;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    g_ebp = ebp;
    esp += 12; return; /* ret 8 */
}

/**
 * sub_000682B0
 * Original: 0x000682B0 - 0x00068355 (165 bytes, 55 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000682B0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000682B0: ;
    eax = MEM32(esp + 4);
    esp = esp - 0x22C;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    ebx = ecx;
    PUSH32(esp, 0x000682C4u); sub_00067FD0(); /* call 0x00067FD0 */

loc_000682C4: ;
    esi = eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000682D5; /* jne: not equal / not zero */

loc_000682CA: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x22C;
    esp += 8; return; /* ret 4 */

loc_000682D5: ;
    eax = MEM32(esi + 8);
    eax--;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, edi);
    edi = esi + 0xC;
    ecx = esp + 0x134;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000682F7; /* jle: less or equal (signed <=) */

loc_000682E8: ;
    SET_LO8(edx, MEM8(edi));
    edi++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000682F7; /* je: equal / zero */

loc_000682EF: ;
    MEM8(ecx) = LO8(edx);
    ecx++;
    eax--;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_G(_fas & _fbs, 0)) goto loc_000682E8; /* jg: greater (signed >) */

loc_000682F7: ;
    MEM8(ecx) = 0;
    ecx = esp + 0x1C;
    PUSH32(esp, 0x00068303u); sub_00071F60(); /* call 0x00071F60 */

loc_00068303: ;
    PUSH32(esp, 0);
    ecx = esp + 0x138;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x1ED83C);
    ecx = esp + 0x28;
    PUSH32(esp, 0x0006831Bu); sub_00071FC0(); /* call 0x00071FC0 */

loc_0006831B: ;
    edx = esp + 0xC;
    PUSH32(esp, edx);
    ecx = esp + 0x20;
    MEM32(esp + 0x10) = 0x1ED838;
    MEM32(esp + 0x14) = ebx;
    MEM8(esp + 0x1C) = 1;
    MEM32(esp + 0x18) = esi;
    PUSH32(esp, 0x0006833Eu); sub_000722C0(); /* call 0x000722C0 */

loc_0006833E: ;
    ecx = esp + 0x1C;
    PUSH32(esp, 0x00068347u); sub_00071EE0(); /* call 0x00071EE0 */

loc_00068347: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x22C;
    esp += 8; return; /* ret 4 */
}

/**
 * sub_00068660
 * Original: 0x00068660 - 0x000686E3 (131 bytes, 49 insns)
 * Category: game_callback
 * CC: thiscall, 2 params, returns bool
 * Frame: fpo_leaf
 */
void sub_00068660(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00068660: ;
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0xC));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = _fa;
    _fas = (int32_t)(int8_t)_fa; _fbs = _fas;
    if (TEST_Z(_fa, _fb)) goto loc_000686AF;

loc_0006866B: ;
    eax = esp + 4;
    PUSH32(esp, eax);
    ecx = esp + 0x10;
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 4);
    ecx = ecx + 0x198;
    PUSH32(esp, 0x00068683u); sub_000686F0();

loc_00068683: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = _fa;
    _fas = (int32_t)(int8_t)_fa; _fbs = _fas;
    if (TEST_Z(_fa, _fb)) goto loc_000686A2;

loc_00068687: ;
    edx = MEM32(esp + 4);
    MEM32(edx) = 1;
    eax = MEM32(esi + 8);
    ecx = MEM32(esp + 4);
    MEM32(ecx + 4) = eax;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 12; return; /* ret 8 */

loc_000686A2: ;
    eax = MEM32(esp + 4);
    MEM32(eax)++;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 12; return; /* ret 8 */

loc_000686AF: ;
    ecx = MEM32(esi + 4);
    edx = esp + 0xC;
    PUSH32(esp, edx);
    ecx = ecx + 0x198;
    PUSH32(esp, 0x000686C2u); sub_00068360();

loc_000686C2: ;
    _fa = (uint32_t)eax; _fb = eax;
    _fas = (int32_t)eax; _fbs = (int32_t)eax;
    if (TEST_Z(_fa, _fb)) goto loc_000686DE;

loc_000686C6: ;
    edx = MEM32(eax);
    edx--;
    ecx = edx;
    MEM32(eax) = edx;
    ecx = MEM32(esi + 4);
    PUSH32(esp, eax);
    ecx = ecx + 0x198;
    PUSH32(esp, 0x000686DEu); sub_000687A0();

loc_000686DE: ;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 12; return; /* ret 8 */
}

/**
 * sub_00012CA0
 * Original: 0x00012CA0 - 0x00012D2C (140 bytes, 54 insns)
 * Category: game_vtable
 * CC: thiscall, 1 param, returns bool
 * Frame: fpo_leaf
 */
void sub_00012CA0(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00012CA0: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    eax = ebx;
    PUSH32(esp, esi);
    edx = eax + 1;

loc_00012CB0: ;
    SET_LO8(ecx, MEM8(eax));
    eax++;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = _fa;
    _fas = (int32_t)(int8_t)_fa; _fbs = _fas;
    if (TEST_NZ(_fa, _fb)) goto loc_00012CB0;

loc_00012CB7: ;
    eax = eax - edx;
    esi = eax;
    _fa = esi; _fb = 4u;
    _fas = (int32_t)esi; _fbs = 4;
    if (CMP_GE(_fas, _fbs)) goto loc_00012CC7;

loc_00012CC0: ;
    POP32(esp, esi);
    SET_LO8(eax, 0);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

loc_00012CC7: ;
    PUSH32(esp, edi);
    edi = esi + ebx - 4;
    PUSH32(esp, 0x001E18B0u);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00012CD7u); sub_0010FE36();

loc_00012CD7: ;
    esp = esp + 8;
    _fa = eax; _fb = eax;
    _fas = (int32_t)eax; _fbs = _fas;
    if (TEST_NZ(_fa, _fb)) goto loc_00012CE6;

loc_00012CDE: ;
    POP32(esp, edi);
    POP32(esp, esi);
    SET_LO8(eax, 0);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

loc_00012CE6: ;
    PUSH32(esp, 0x001E18A8u);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00012CF1u); sub_0010FE36();

loc_00012CF1: ;
    esp = esp + 8;
    _fa = eax; _fb = eax;
    _fas = (int32_t)eax; _fbs = _fas;
    if (TEST_Z(_fa, _fb)) goto loc_00012CDE;

loc_00012CF8: ;
    _fa = esi; _fb = 0xAu;
    _fas = (int32_t)esi; _fbs = 0xA;
    if (CMP_NE(_fa, _fb)) goto loc_00012D26;

loc_00012CFD: ;
    PUSH32(esp, 5);
    PUSH32(esp, 0x001E18A0u);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x00012D0Au); sub_0011FDF0();

loc_00012D0A: ;
    esp = esp + 0xC;
    _fa = eax; _fb = eax;
    _fas = (int32_t)eax; _fbs = _fas;
    if (TEST_NZ(_fa, _fb)) goto loc_00012D26;

loc_00012D11: ;
    PUSH32(esp, 0x001E1898u);
    ebx = ebx + 6;
    PUSH32(esp, ebx);
    PUSH32(esp, 0x00012D1Fu); sub_0010FE36();

loc_00012D1F: ;
    esp = esp + 8;
    _fa = eax; _fb = eax;
    _fas = (int32_t)eax; _fbs = _fas;
    if (TEST_Z(_fa, _fb)) goto loc_00012CDE;

loc_00012D26: ;
    POP32(esp, edi);
    POP32(esp, esi);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */
}

void sub_00033540(void)
{
    uint32_t call_esp = g_esp;
    eax = MEM32(ecx);
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    edx = ecx + 4;
    PUSH32(esp, edx);
    {
        uint32_t target = MEM32(eax + 0x14);
        PUSH32(esp, 0x0003354Du);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    esp += 4;
}

void sub_000338A0(void)
{
    eax = MEM32(ecx + 0x204) + 1;
    edx = MEM32(esp + 4);
    MEM32(ecx + 0x204) = eax;
    MEM32(ecx + eax * 4 + 0x1E0) = edx;
    esp += 8; /* ret 4 */
}

/* Input-event listener callback.  The retail jump table has six compact
 * handlers selected by a 30-byte event-code map at 0x33630. */
void sub_00033580(void)
{
    uint32_t event = MEM32(esp + 4);
    uint32_t type;
    PUSH32(esp, esi);
    type = MEM32(event);
    if (type == 0) {
        uint32_t port = MEM32(event + 4);
        if ((int32_t)port < 4) {
            uint32_t code = MEM32(event + 8);
            uint32_t dst = ecx + port * 0x5C + 0x0C;
            if (code <= 0x1D) {
                if (code == 0)
                    MEM32(dst) = MEM32(event + 0x0C);
                else if (code == 1)
                    MEM32(dst + 8) = MEM32(event + 0x0C);
                else if (code == 2)
                    MEM32(dst + 4) = MEM32(event + 0x0C);
                else if (code == 3)
                    MEM32(dst + 0x0C) = MEM32(event + 0x0C);
                else if (code <= 0x15)
                    MEM8(dst + code + 0x0C) = MEM8(event + 0x0C);
                else
                    MEM32(dst + code * 4 - 0x34) = MEM32(event + 0x0C);
            }
        }
    } else if (type == 1) {
        MEM32(ecx + 0x17C) = ZX8(MEM8(event + 4));
        MEM32(ecx + 0x180) = ZX8(MEM8(event + 5));
    }
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 8; /* ret 4 */
}

void sub_000377C0(void)
{
    uint32_t i;
    PUSH32(esp, edi);
    edx = ecx;
    SET_LO8(eax, MEM8(edx + 4));
    if (LO8(eax) == 0) {
        MEM32(edx + 8) = 0;
        MEM8(edx + 4) = 1;
    }
    eax = 0;
    edi = edx + 0x1C;
    for (i = 0; i < 8; ++i)
        MEM32(edi + i * 4) = 0;
    edi = edx + 0x3C;
    for (i = 0; i < 0x40; ++i)
        MEM32(edi + i * 4) = 0;
    SET_LO8(eax, 1);
    POP32(esp, edi);
    esp += 4;
}

/* XOnline task vtable slot at 0x0019952C.  The original is a compact
 * nine-way jump-table thunk which the function seeder mistook for data after
 * sub_0019941F.  It is called by XOnlineTaskContinue once per game frame. */
void sub_0019952C(void)
{
    ecx = MEM32(esp + 4);
    eax = 0;
    if (ecx != 0) {
        switch (MEM32(ecx + 0x0C)) {
        case 0: PUSH32(esp, 0x00199546u); sub_001991EA(); break;
        case 1: PUSH32(esp, 0x0019954Du); sub_00199287(); break;
        case 2: PUSH32(esp, 0x00199554u); sub_00197F97(); break;
        case 3: PUSH32(esp, 0x0019955Bu); sub_00198DA2(); break;
        case 4: PUSH32(esp, 0x00199562u); sub_00197F97(); break;
        case 5: PUSH32(esp, 0x00199569u); sub_00198073(); break;
        case 6: PUSH32(esp, 0x00199570u); sub_0019941F(); break;
        case 7: PUSH32(esp, 0x00199577u); sub_0019811D(); break;
        case 8: PUSH32(esp, 0x0019957Eu); sub_001980CD(); break;
        default: break;
        }
    }
    esp += 8;
}

/* XOnline async task vtable slot.  Like 0x0019952C, this valid code lives in
 * a seeding gap and therefore never received a generated dispatch entry. */
void sub_0019A6F6(void)
{
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    PUSH32(esp, 0);
    eax = esi + 0x18;
    PUSH32(esp, eax);
    eax = esi + 0x20;
    PUSH32(esp, eax);
    PUSH32(esp, MEM32(esi + 0x1C));
    PUSH32(esp, 0x0019A70Du);
    sub_0002A7DA();

    if (eax == 0) {
        PUSH32(esp, 0x0019A716u);
        sub_0002A76D();
        if (eax == 0x3E5u || eax == 0x3E4u) {
            MEM32(esi + 0x0C) = 0;
        } else {
            if ((int32_t)eax > 0)
                eax = (eax & 0xFFFFu) | 0x80070000u;
            MEM32(esi + 0x0C) = eax;
        }
    } else {
        MEM32(esi + 0x0C) = 0x001500F0u;
    }
    eax = MEM32(esi + 0x0C);
    POP32(esp, esi);
    esp += 8;
}

void sub_0010B520(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_0010B520: ;
    PUSH32(esp, ecx);
    eax = MEM32(ecx + 0x28);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xD (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B53B; /* je: equal / zero */

loc_0010B529: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x12) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x12 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B53B; /* je: equal / zero */

loc_0010B52E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x13) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x13 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B53B; /* je: equal / zero */

loc_0010B533: ;
    fp_push(MEMF(0x1E16FC)); /* fld float */
    POP32(esp, ecx);
    esp += 4; return; /* ret */

loc_0010B53B: ;
    eax = MEM32(ecx + 0x20);
    fp_push((double)SMEM32(ecx + 0x20)); /* fild */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_0010B54B; /* jge: greater or equal (signed >=) */

loc_0010B545: ;
    fp_top() = fp_top() + MEMF(0x1E17EC); /* fadd dword ptr [0x1e17ec] */

loc_0010B54B: ;
    POP32(esp, ecx);
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_0010B550(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_0010B550: ;
    PUSH32(esp, ecx);
    eax = MEM32(ecx + 0x28);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xD (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B56B; /* je: equal / zero */

loc_0010B559: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x12) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x12 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B56B; /* je: equal / zero */

loc_0010B55E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x13) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x13 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010B56B; /* je: equal / zero */

loc_0010B563: ;
    fp_push(MEMF(0x1E16FC)); /* fld float */
    POP32(esp, ecx);
    esp += 4; return; /* ret */

loc_0010B56B: ;
    eax = MEM32(ecx + 0x24);
    fp_push((double)SMEM32(ecx + 0x24)); /* fild */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_0010B57B; /* jge: greater or equal (signed >=) */

loc_0010B575: ;
    fp_top() = fp_top() + MEMF(0x1E17EC); /* fadd dword ptr [0x1e17ec] */

loc_0010B57B: ;
    POP32(esp, ecx);
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00030F60(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00030F60: ;
    eax = MEM32(esp + 8);
    esp = esp - 0x104;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ebx = ecx;
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x114);
    MEM32(ebx + 0x1C) = eax;
    eax = esp + 0xC;
    ecx = 0xFF;
    esi = 0; /* xor self */

loc_00030F84: ;
    SET_LO8(edx, MEM8(edi));
    edi++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00030F95; /* je: equal / zero */

loc_00030F8B: ;
    eax++;
    MEM8(eax + -1) = LO8(edx);
    ecx--;
    esi++;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_G(_fas & _fbs, 0)) goto loc_00030F84; /* jg: greater (signed >) */

loc_00030F95: ;
    ecx = esp + 0xC;
    PUSH32(esp, 0x2E);
    PUSH32(esp, ecx);
    MEM8(eax) = 0;
    PUSH32(esp, 0x00030FA4u); sub_00110280(); /* call 0x00110280 */

loc_00030FA4: ;
    esp = esp + 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00030FBF; /* jne: not equal / not zero */

loc_00030FAB: ;
    eax = MEM32(0x1E5170);
    SET_LO8(ecx, MEM8(0x1E5174));
    edx = esp + esi + 0xC;
    MEM32(edx) = eax;
    MEM8(edx + 4) = LO8(ecx);

loc_00030FBF: ;
    edx = MEM32(ebx + 0x18);
    PUSH32(esp, edx);
    eax = esp + 0x10;
    PUSH32(esp, eax);
    ecx = 0x3E25C0;
    PUSH32(esp, 0x00030FD2u); sub_00036270(); /* call 0x00036270 */

loc_00030FD2: ;
    POP32(esp, edi);
    MEM32(ebx + 0x10) = eax;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, esi);
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    POP32(esp, ebx);
    esp = esp + 0x104;
    esp += 12; return; /* ret 8 */

}

void sub_000318D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000318D0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000318D8u); sub_00031650(); /* call 0x00031650 */

loc_000318D8: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000318E6; /* je: equal / zero */

loc_000318DF: ;
    ecx = esi;
    PUSH32(esp, 0x000318E6u); sub_00039840(); /* call 0x00039840 */

loc_000318E6: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_000EAC00(void)
{

loc_000EAC00: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, 7);
    MEM32(ecx + 0xAC) = eax;
    PUSH32(esp, ecx);
    ecx = ecx + 0x88;
    PUSH32(esp, 0x000EAC18u); sub_000E9C60(); /* call 0x000E9C60 */

loc_000EAC18: ;
    esp += 8; return; /* ret 4 */

}

void sub_000E9CD0(void)
{

loc_000E9CD0: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, 7);
    MEM32(ecx + 0xB0) = eax;
    PUSH32(esp, ecx);
    ecx = ecx + 0x88;
    PUSH32(esp, 0x000E9CE8u); sub_000E9C60(); /* call 0x000E9C60 */

loc_000E9CE8: ;
    esp += 8; return; /* ret 4 */

}

void sub_000EA920(void)
{

loc_000EA920: ;
    eax = MEM32(esp + 4);
    edx = MEM32(eax);
    MEM32(ecx + 0x78) = edx;
    eax = MEM32(eax + 4);
    MEM32(ecx + 0x7C) = eax;
    esp += 8; return; /* ret 4 */

}

void sub_000DFCD0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DFCD0: ;
    PUSH32(esp, 0x10);
    PUSH32(esp, 0x000DFCD7u); sub_0010F511(); /* call 0x0010F511 */

loc_000DFCD7: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DFCF0; /* je: equal / zero */

loc_000DFCDE: ;
    MEM8(eax) = 1;
    ecx = ecx | 0xFFFFFFFFu;
    MEM32(eax + 4) = ecx;
    MEM32(eax + 8) = ecx;
    MEM32(eax + 0xC) = ecx;
    esp += 8; return; /* ret 4 */

loc_000DFCF0: ;
    eax = 0; /* xor self */
    esp += 8; return; /* ret 4 */

}

void sub_000EAC20(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EAC20: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    esi = ecx;
    PUSH32(esp, edi);
    ecx = esi + 0xB4;
    PUSH32(esp, 0x000EAC34u); sub_000DD590(); /* call 0x000DD590 */

loc_000EAC34: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EAC4C; /* jne: not equal / not zero */

loc_000EAC38: ;
    PUSH32(esp, 7);
    PUSH32(esp, esi);
    ecx = esi + 0x88;
    MEM32(esi + 0xB0) = edi;
    PUSH32(esp, 0x000EAC4Cu); sub_000E9C60(); /* call 0x000E9C60 */

loc_000EAC4C: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_000DFB70(void)
{

loc_000DFB70: ;
    ecx = ecx - MEM32(ecx + -4);
    goto loc_000DFB80;

    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */

loc_000DFB80: ;
    eax = 1;
    esp += 4; return; /* ret */

}

void sub_000DA490(void)
{

loc_000DA490: ;
    ecx = ecx - MEM32(ecx + -4);
    goto loc_000DA4A0;

    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */

loc_000DA4A0: ;
    eax = 4;
    esp += 4; return; /* ret */

}

void sub_000E1330(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E1330: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000E1338u); sub_000E1220(); /* call 0x000E1220 */

loc_000E1338: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E1348; /* je: equal / zero */

loc_000E133F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E1345u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000E1345: ;
    esp = esp + 4;

loc_000E1348: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00040F90
 * Original: 0x00040F90 - 0x000410DE (334 bytes, 128 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: standard_frame
 */
void sub_00040F90(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00040F90: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    eax = MEM32(ebp + 0xC);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(eax + 8);
    eax = 0; /* xor self */
    ebx = ecx;
    MEM32(ebx + 0x4C) = eax;
    PUSH32(esp, edi);
    edi = ZX16(MEM16(esi + 2));
    MEM32(ebp + 0xC) = eax;
    eax = edi * 4;
    eax = eax + 3;
    eax = eax & 0xFFFFFFFCu;
    MEM32(ebp + -8) = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00040FC2u); sub_0010F4D0(); /* call 0x0010F4D0 */

loc_00040FC2: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(ebp + -12) = esp;
    MEM32(ebp + -4) = 0;
    if (CMP_BE(_fa & _fb, 0)) goto loc_00041023; /* jbe: below or equal (unsigned <=) */

loc_00040FD0: ;
    eax = ZX16(MEM16(esi));
    edi = MEM32(ebp + -4);
    edx = MEM32(ebp + 8);
    ecx = MEM32(edx + 0x34);
    eax = eax + edi;
    eax = ZX16(MEM16(esi + eax * 2 + 0xC));
    eax = MEM32(ecx + eax * 4 + 4);
    eax = eax + ecx;
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    ecx = edx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00040FF3u); sub_0003EB70(); /* call 0x0003EB70 */

loc_00040FF3: ;
    SET_LO8(ecx, MEM8(eax + 2));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041014; /* jne: not equal / not zero */

loc_00040FFA: ;
    ecx = MEM32(ebp + 0xC);
    edx = MEM32(ebp + -12);
    MEM32(edx + ecx * 4) = eax;
    eax = MEM32(eax + 8);
    edx = MEM32(eax);
    edi = MEM32(ebx + 0x4C);
    edi = edi + edx;
    ecx++;
    MEM32(ebx + 0x4C) = edi;
    MEM32(ebp + 0xC) = ecx;

loc_00041014: ;
    eax = MEM32(ebp + -4);
    ecx = ZX16(MEM16(esi + 2));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    MEM32(ebp + -4) = eax;
    if (CMP_B(_fa, _fb)) goto loc_00040FD0; /* jb: below (unsigned <) */

loc_00041023: ;
    edi = MEM32(ebx + 0x4C);
    edx = edi;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x38);
    edx = edx + 4;
    PUSH32(esp, edx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041034u); sub_0010F511(); /* call 0x0010F511 */

loc_00041034: ;
    edx = 0; /* xor self */
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0004106B; /* je: equal / zero */

loc_0004103D: ;
    MEM32(eax) = edi;
    eax = eax + 4;
    edi--;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, edx (32-bit) */
    MEM32(ebp + -4) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_0004106D; /* jl: less (signed <) */

loc_0004104A: ;
    ecx = edi + 1;
    eax = eax + 0x10;
    edi = 0x1E5D1C;

loc_00041055: ;
    MEM32(eax + -4) = edx;
    MEM32(eax) = edx;
    MEM32(eax + -8) = edi;
    MEM32(eax + 0x24) = edx;
    eax = eax + 0x38;
    ecx--;
    if ((ecx != 0)) goto loc_00041055; /* jne: not equal / not zero */

loc_00041066: ;
    eax = MEM32(ebp + -4);
    goto loc_0004106D;

loc_0004106B: ;
    eax = 0; /* xor self */

loc_0004106D: ;
    PUSH32(esp, eax);
    ecx = ebx + 0x50;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041076u); sub_00040E60(); /* call 0x00040E60 */

loc_00041076: ;
    eax = MEM32(ebp + 0xC);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebx + 0x4C) = edi;
    if (CMP_BE(_fa & _fb, 0)) goto loc_000410D2; /* jbe: below or equal (unsigned <=) */

loc_00041082: ;
    ecx = MEM32(esi + 4);
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_000410B6; /* jl: less (signed <) */

loc_0004108B: ;
    ecx = ZX16(MEM16(esi));
    edx = ZX16(MEM16(esi + 2));
    ebx = edi;
    ebx = ebx + ecx;
    edx = edx + ebx;
    SET_LO16(edx, MEM16(esi + edx * 2 + 0xC));
    _fa = (uint32_t)(LO16(edx)) & 0xFFFFu; _fb = (uint32_t)(0xFFFF) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(edx), 0xFFFF (16-bit) */
    ebx = MEM32(ebp + -8);
    if (CMP_EQ(_fa, _fb)) goto loc_000410B6; /* je: equal / zero */

loc_000410A7: ;
    eax = MEM32(ebp + 8);
    ecx = MEM32(eax + 0x34);
    edx = ZX16(LO16(edx));
    eax = MEM32(ecx + edx * 4 + 4);
    eax = eax + ecx;

loc_000410B6: ;
    edx = MEM32(ebp + 8);
    PUSH32(esp, eax);
    eax = MEM32(ebp + -12);
    ecx = MEM32(eax + edi * 4);
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    PUSH32(esp, edx);
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x000410CAu); sub_00040340(); /* call 0x00040340 */

loc_000410CA: ;
    eax = MEM32(ebp + 0xC);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00041082; /* jb: below (unsigned <) */

loc_000410D2: ;
    esp = ebp + -24;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000410E0
 * Original: 0x000410E0 - 0x00041269 (393 bytes, 139 insns)
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000410E0(void)
{
    static uint32_t s_scene_resource_bind_trace;
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000410E0: ;
    ++s_scene_resource_bind_trace;
    esp = esp - 8;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = ecx;
    eax = MEM32(ebp);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x10) = ebp;
    if (CMP_EQ(_fa, _fb)) goto loc_00041121; /* je: equal / zero */

loc_000410F6: ;
    edi = 0; /* xor self */
    esi = ebp + 4;
    goto loc_00041100;

    /* nop */

loc_00041100: ;
    eax = MEM32(esi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041121; /* je: equal / zero */

loc_00041106: ;
    ecx = eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041118; /* je: equal / zero */

loc_0004110C: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00041116; /* jne: not equal / not zero */

loc_00041111: ;
    PUSH32(esp, 0x00041116u); sub_0002E400(); /* call 0x0002E400 */

loc_00041116: ;
    MEM32(esi) = ebx;

loc_00041118: ;
    edi++;
    esi = esi + 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 0x20 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00041100; /* jl: less (signed <) */

loc_00041121: ;
    esi = MEM32(esp + 0x1C);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, ebx (32-bit) */
    ecx = MEM32(ebp);
    MEM8(ebp + 0x89) = LO8(ebx);
    if (CMP_NE(_fa, _fb)) goto loc_00041153; /* jne: not equal / not zero */

loc_00041132: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0004123E; /* je: equal / zero */

loc_0004113A: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00041144; /* jne: not equal / not zero */

loc_0004113F: ;
    PUSH32(esp, 0x00041144u); sub_0002E400(); /* call 0x0002E400 */

loc_00041144: ;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebp) = ebx;
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_00041153: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041161; /* je: equal / zero */

loc_00041157: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00041161; /* jne: not equal / not zero */

loc_0004115C: ;
    PUSH32(esp, 0x00041161u); sub_0002E400(); /* call 0x0002E400 */

loc_00041161: ;
    MEM32(ebp) = esi;
    edx = MEM32(esi + 4);
    eax = MEM32(esi + 0x54);
    edx++;
    MEM32(esp + 0x1C) = eax;
    eax = MEM32(esi + 0x48);
    MEM32(esi + 4) = edx;
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM32(esp + 0x14) = eax;
    if (CMP_LE(_fas, _fbs)) goto loc_00041232; /* jle: less or equal (signed <=) */

loc_00041183: ;
    ebp = ebp + 4;
    goto loc_00041190;

    /* nop */
    /* nop */

loc_00041190: ;
    eax = MEM32(0x3E259C);
    if (s_scene_resource_bind_trace <= 24u && eax == 0u) {
        fprintf(stderr,
                "[SCENE-BIND-FAIL] #%u reason=wrapper-pool-empty node=%08X "
                "slot=%u slots=%u allocator=%08X\n",
                s_scene_resource_bind_trace, MEM32(esp + 0x10), esi,
                MEM32(esp + 0x14), MEM32(0x3D0198));
    }
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0004124A; /* je: equal / zero */

loc_0004119D: ;
    ecx = MEM32(eax);
    MEM32(0x3E259C) = ecx;
    MEM32(eax + 0x10) = ebx;
    MEM32(eax + 0x14) = ebx;
    MEM32(eax) = 0x1E1930;
    ecx = 1;
    MEM32(eax + 4) = ecx;
    MEM32(eax + 8) = ecx;
    MEM32(eax + 0x20) = ebx;
    MEM32(eax + 0x1C) = ebx;
    MEM32(eax + 0x28) = ebx;
    MEM32(eax + 0x24) = ebx;
    MEM32(eax + 0x2C) = ebx;
    ecx = MEM32(eax + 8);
    ecx = ecx | 0x10;
    MEM32(eax + 0x14) = 0x3D0198;
    MEM32(eax + 8) = ecx;
    edi = eax;

loc_000411DD: ;
    ecx = MEM32(ebp);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000411EE; /* je: equal / zero */

loc_000411E4: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_000411EE; /* jne: not equal / not zero */

loc_000411E9: ;
    PUSH32(esp, 0x000411EEu); sub_0002E400(); /* call 0x0002E400 */

loc_000411EE: ;
    ecx = edi;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    MEM32(ebp) = edi;
    if (CMP_EQ(_fa, _fb)) goto loc_0004124E; /* je: equal / zero */

loc_000411F7: ;
    edx = MEM32(esp + 0x1C);
    eax = MEM32(edx + esi * 4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00041204u); sub_0010A2C0(); /* call 0x0010A2C0 */

loc_00041204: ;
    _fa = (uint32_t)(MEM8(esp + 0x20)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esp + 0x20), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0004121E; /* je: equal / zero */

loc_0004120A: ;
    edx = MEM32(esp + 0x1C);
    eax = MEM32(edx + esi * 4);
    ecx = MEM32(ebp);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0004121Au); sub_0010A2F0(); /* call 0x0010A2F0 */

loc_0004121A: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) {
        if (s_scene_resource_bind_trace <= 24u)
            fprintf(stderr,
                    "[SCENE-BIND-FAIL] #%u reason=resource-link node=%08X slot=%u wrapper=%08X resource=%08X\n",
                    s_scene_resource_bind_trace, MEM32(esp + 0x10), esi,
                    MEM32(ebp), MEM32(esp + 0x1C + esi * 4));
        goto loc_0004124E;
    } /* je: equal / zero */

loc_0004121E: ;
    eax = MEM32(esp + 0x14);
    esi++;
    ebp = ebp + 4;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00041190; /* jl: less (signed <) */

loc_0004122E: ;
    ebp = MEM32(esp + 0x10);

loc_00041232: ;
    MEM32(ebp + 0x84) = ebx;
    MEM8(ebp + 0x88) = LO8(ebx);

loc_0004123E: ;
    if (s_scene_resource_bind_trace <= 24u)
        fprintf(stderr,
                "[SCENE-BIND-DONE] #%u node=%08X ok=1 slots=%u used=%u pool=%08X\n",
                s_scene_resource_bind_trace, MEM32(esp + 0x10),
                MEM32(esp + 0x14), MEM32(MEM32(esp + 0x10) + 0x84u),
                MEM32(0x3E259C));
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_0004124A: ;
    edi = 0; /* xor self */
    goto loc_000411DD;

loc_0004124E: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x14)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, MEM32(esp + 0x14) (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_0004122E; /* jge: greater or equal (signed >=) */

loc_00041254: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, 0x0004125Du); sub_00040920(); /* call 0x00040920 */

loc_0004125D: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

}

void sub_000412F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000412F0: ;
    esp = esp - 0x30;
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(eax + 8);
    ebx = ZX16(MEM16(edi));
    esi = ecx;
    ecx = ebx * 4 + 4;
    PUSH32(esp, ecx);
    MEM32(esp + 0x14) = edi;
    MEM32(esi + 0x48) = ebx;
    PUSH32(esp, 0x00041317u); sub_0010F511(); /* call 0x0010F511 */

loc_00041317: ;
    ebp = 0; /* xor self */
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0004133D; /* je: equal / zero */

loc_00041320: ;
    MEM32(eax) = ebx;
    edx = eax + 4;
    eax = ebx + -1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00041339; /* jl: less (signed <) */

loc_0004132C: ;
    ecx = eax + 1;
    eax = 0; /* xor self */
    edi = edx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    edi = MEM32(esp + 0x10);

loc_00041339: ;
    eax = edx;
    goto loc_0004133F;

loc_0004133D: ;
    eax = 0; /* xor self */

loc_0004133F: ;
    ecx = esi + 0x54;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00041348u); sub_00040DB0(); /* call 0x00040DB0 */

loc_00041348: ;
    edx = MEM32(esp + 0x44);
    _fa = (uint32_t)(MEM32(esi + 0x48)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x48), ebp (32-bit) */
    ebx = MEM32(edx + 0x34);
    MEM8(esi + 0x44) = 0;
    if (CMP_LE(_fas, _fbs)) goto loc_000413D0; /* jle: less or equal (signed <=) */

loc_00041358: ;
    edi = edi + 0xC;
    MEM32(esp + 0x10) = edi;
    /* nop */

loc_00041360: ;
    eax = MEM32(esp + 0x10);
    ecx = ZX16(MEM16(eax));
    eax = MEM32(ebx + ecx * 4 + 4);
    edi = MEM32(esi + 0x54);
    eax = eax + ebx;
    PUSH32(esp, eax);
    ecx = 0x238E28;
    PUSH32(esp, 0x0004137Bu); sub_00041CD0(); /* call 0x00041CD0 */

loc_0004137B: ;
    ecx = MEM32(edi + ebp * 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esp + 0x14) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00041390; /* je: equal / zero */

loc_00041386: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00041390; /* jne: not equal / not zero */

loc_0004138B: ;
    PUSH32(esp, 0x00041390u); sub_0002E400(); /* call 0x0002E400 */

loc_00041390: ;
    edx = MEM32(esp + 0x14);
    MEM32(edi + ebp * 4) = edx;
    SET_LO8(eax, MEM8(esi + 0x44));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000413B3; /* jne: not equal / not zero */

loc_0004139E: ;
    eax = MEM32(esi + 0x54);
    ecx = MEM32(eax + ebp * 4);
    edx = MEM32(ecx + 8);
    edx = edx >> 7;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000413B3; /* jne: not equal / not zero */

loc_000413AF: ;
    eax = 0; /* xor self */
    goto loc_000413B8;

loc_000413B3: ;
    eax = 1;

loc_000413B8: ;
    ecx = MEM32(esp + 0x10);
    MEM8(esi + 0x44) = LO8(eax);
    eax = MEM32(esi + 0x48);
    ebp++;
    ecx = ecx + 2;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    MEM32(esp + 0x10) = ecx;
    if (CMP_L(_fas, _fbs)) goto loc_00041360; /* jl: less (signed <) */

loc_000413CE: ;
    ebp = 0; /* xor self */

loc_000413D0: ;
    eax = MEM32(esp + 0x48);
    ecx = MEM32(esp + 0x44);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = esi;
    PUSH32(esp, 0x000413E1u); sub_00040F90(); /* call 0x00040F90 */

loc_000413E1: ;
    _fa = (uint32_t)(MEM32(esi + 0x4C)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x4C), ebp (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041418; /* jne: not equal / not zero */

loc_000413E6: ;
    MEM32(esi + 0x34) = ebp;
    MEM32(esi + 0x38) = ebp;
    MEM32(esi + 0x3C) = ebp;
    MEM32(esi + 0x40) = ebp;
    eax = 0x7EFFFFFF;
    MEM32(esi + 0x1C) = eax;
    MEM32(esi + 0x20) = eax;
    MEM32(esi + 0x24) = eax;
    eax = 0xFEFFFFFFu;
    POP32(esp, edi);
    MEM32(esi + 0x28) = eax;
    MEM32(esi + 0x2C) = eax;
    MEM32(esi + 0x30) = eax;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x30;
    esp += 12; return; /* ret 8 */

loc_00041418: ;
    edx = MEM32(esi + 0x50);
    ecx = MEM32(edx + 0x34);
    eax = MEM32(ecx);
    edx = esp + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00041428u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00041428: ;
    eax = MEM32(esi + 0x4C);
    edi = 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_0004146A; /* jle: less or equal (signed <=) */

loc_00041434: ;
    ebx = 0x38;
    /* nop */

loc_00041440: ;
    eax = MEM32(esi + 0x50);
    ecx = MEM32(ebx + eax + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00041451u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00041451: ;
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    ecx = esp + 0x1C;
    PUSH32(esp, 0x0004145Fu); sub_00065F40(); /* call 0x00065F40 */

loc_0004145F: ;
    eax = MEM32(esi + 0x4C);
    edi++;
    ebx = ebx + 0x38;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00041440; /* jl: less (signed <) */

loc_0004146A: ;
    fp_push(MEMF(esp + 0x24)); /* fld float */
    eax = MEM32(esp + 0x18);
    fp_top() = sqrt(fp_top()); /* fsqrt */
    ecx = MEM32(esp + 0x1C);
    edx = esi + 0x34;
    MEM32(edx) = eax;
    eax = MEM32(esp + 0x20);
    MEM32(edx + 4) = ecx;
    MEM32(edx + 8) = eax;
    edi = esi + 0x1C;
    eax = 0x7EFFFFFF;
    ebx = 0; /* xor self */
    MEMF(esi + 0x40) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(edi) = eax;
    MEM32(edi + 4) = eax;
    MEM32(edi + 8) = eax;
    eax = 0xFEFFFFFFu;
    MEM32(edi + 0xC) = eax;
    MEM32(edi + 0x10) = eax;
    MEM32(edi + 0x14) = eax;
    eax = MEM32(esi + 0x4C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000414E7; /* jle: less or equal (signed <=) */

loc_000414B1: ;
    ebp = 0; /* xor self */

loc_000414B3: ;
    ecx = MEM32(esi + 0x50);
    ecx = MEM32(ecx + ebp + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x14); PUSH32(esp, 0x000414C4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000414C4: ;
    ecx = esp + 0x34;
    PUSH32(esp, ecx);
    ecx = edi;
    PUSH32(esp, 0x000414D0u); sub_00040230(); /* call 0x00040230 */

loc_000414D0: ;
    edx = esp + 0x28;
    PUSH32(esp, edx);
    ecx = edi;
    PUSH32(esp, 0x000414DCu); sub_00040230(); /* call 0x00040230 */

loc_000414DC: ;
    eax = MEM32(esi + 0x4C);
    ebx++;
    ebp = ebp + 0x38;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000414B3; /* jl: less (signed <) */

loc_000414E7: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x30;
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041500(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00041500: ;
    edx = MEM32(esp + 4);
    fp_push(MEMF(ecx + 8)); /* fld float */
    fp_top() = fp_top() * MEMF(edx + 4); /* fmul dword ptr [edx + 4] */
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_top() = fp_top() * MEMF(edx); /* fmul dword ptr [edx] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() + MEMF(esp + 8); /* fadd dword ptr [esp + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ecx + 0xC)); fp_pop(); /* fcomp dword ptr [ecx + 0xc] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041578; /* jne: not equal / not zero */

loc_0004151F: ;
    fp_push(MEMF(ecx + 0x14)); /* fld float */
    fp_top() = fp_top() * MEMF(edx + 4); /* fmul dword ptr [edx + 4] */
    fp_push(MEMF(ecx + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(edx); /* fmul dword ptr [edx] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() + MEMF(esp + 8); /* fadd dword ptr [esp + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ecx + 0x18)); fp_pop(); /* fcomp dword ptr [ecx + 0x18] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041578; /* jne: not equal / not zero */

loc_0004153A: ;
    fp_push(MEMF(ecx + 0x20)); /* fld float */
    fp_top() = fp_top() * MEMF(edx + 4); /* fmul dword ptr [edx + 4] */
    fp_push(MEMF(edx)); /* fld float */
    fp_top() = fp_top() * MEMF(ecx + 0x1C); /* fmul dword ptr [ecx + 0x1c] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() + MEMF(esp + 8); /* fadd dword ptr [esp + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ecx + 0x24)); fp_pop(); /* fcomp dword ptr [ecx + 0x24] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041578; /* jne: not equal / not zero */

loc_00041555: ;
    fp_push(MEMF(ecx + 0x2C)); /* fld float */
    fp_top() = fp_top() * MEMF(edx + 4); /* fmul dword ptr [edx + 4] */
    fp_push(MEMF(edx)); /* fld float */
    fp_top() = fp_top() * MEMF(ecx + 0x28); /* fmul dword ptr [ecx + 0x28] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() + MEMF(esp + 8); /* fadd dword ptr [esp + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ecx + 0x30)); fp_pop(); /* fcomp dword ptr [ecx + 0x30] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041578; /* jne: not equal / not zero */

loc_00041570: ;
    eax = 1;
    esp += 12; return; /* ret 8 */

loc_00041578: ;
    eax = 0; /* xor self */
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041580(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00041580: ;
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_top() = fp_top() * MEMF(eax + 4); /* fmul dword ptr [eax + 4] */
    fp_push(MEMF(ecx)); /* fld float */
    fp_top() = fp_top() * MEMF(eax); /* fmul dword ptr [eax] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() * MEMF(eax + 8); /* fmul dword ptr [eax + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ecx + 0xC)); fp_pop(); /* fcomp dword ptr [ecx + 0xc] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0004159F; /* jne: not equal / not zero */

loc_00041599: ;
    eax = 1;
    esp += 4; return; /* ret */

loc_0004159F: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_000415B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000415B0: ;
    esp = esp - 8;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x10);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x18);
    PUSH32(esp, esi);
    esi = 0xFFFFFFF8u;
    esi = esi - ecx;
    PUSH32(esp, edi);
    MEM32(esp + 0x10) = 0;
    edi = ecx + 8;
    MEM32(esp + 0x14) = esi;
    goto loc_000415E0;

loc_000415D7: ;
    esi = MEM32(esp + 0x14);
    goto loc_000415E0;

    /* nop */

loc_000415E0: ;
    ecx = 0; /* xor self */

loc_000415E2: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 4 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041647; /* je: equal / zero */

loc_000415E7: ;
    fp_push(MEMF(ebp + ecx * 8 + 4)); /* fld float */
    fp_top() = fp_top() * MEMF(edi + -4); /* fmul dword ptr [edi - 4] */
    fp_push(MEMF(ebp + ecx * 8)); /* fld float */
    fp_top() = fp_top() * MEMF(edi + -8); /* fmul dword ptr [edi - 8] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi)); fp_pop(); /* fcomp dword ptr [edi] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041603; /* je: equal / zero */

loc_00041600: ;
    ecx++;
    goto loc_000415E2;

loc_00041603: ;
    ecx = 0; /* xor self */
    esi = esi + edi;

loc_00041607: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 4 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041647; /* je: equal / zero */

loc_0004160C: ;
    fp_push(MEMF(edx + ecx * 8 + 4)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + ebx + 4); /* fmul dword ptr [esi + ebx + 4] */
    fp_push(MEMF(edx + ecx * 8)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + ebx); /* fmul dword ptr [esi + ebx] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + ebx + 8)); fp_pop(); /* fcomp dword ptr [esi + ebx + 8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004162A; /* je: equal / zero */

loc_00041627: ;
    ecx++;
    goto loc_00041607;

loc_0004162A: ;
    eax = MEM32(esp + 0x10);
    eax++;
    edi = edi + 0xC;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    MEM32(esp + 0x10) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_000415D7; /* jl: less (signed <) */

loc_0004163B: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_00041647: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041660(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00041660: ;
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_push(MEMF(ecx)); /* fld float */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fabs(fp_top()); /* fabs */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1888)); fp_pop(); /* fcomp dword ptr [0x1e1888] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0004168B; /* jp: parity */

loc_00041686: ;
    SET_LO8(eax, 0); /* xor self */
    fp_pop(); /* fstp st(0) */
    esp += 4; return; /* ret */

loc_0004168B: ;
    fp_top() = MEMF(0x1E16FC) / fp_top(); /* fdivr dword ptr [0x1e16fc] */
    SET_LO8(eax, 1);
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * MEMF(ecx); /* fmul dword ptr [ecx] */
    MEMF(edx) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * MEMF(ecx + 4); /* fmul dword ptr [ecx + 4] */
    MEMF(edx + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ecx + 0xC)); /* fld float */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    MEMF(edx + 8) = (float)fp_top(); fp_pop(); /* fstp */
    fp_pop(); /* fstp st(0) */
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_000416B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000416B0: ;
    esp = esp - 0x20;
    PUSH32(esp, edi);
    edi = ecx;
    ecx = MEM32(esp + 0x30);
    MEM8(edi) = 0;
    fp_push(MEMF(ecx + 8)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1888)); fp_pop(); /* fcomp dword ptr [0x1e1888] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000416D6; /* jp: parity */

loc_000416CD: ;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, edi);
    esp = esp + 0x20;
    esp += 20; return; /* ret 16 */

loc_000416D6: ;
    edx = MEM32(esp + 0x2C);
    fp_push(MEMF(edx + 4)); /* fld float */
    PUSH32(esp, ebx);
    fp_top() = fp_top() * MEMF(ecx + 4); /* fmul dword ptr [ecx + 4] */
    PUSH32(esp, ebp);
    fp_push(MEMF(edx)); /* fld float */
    eax = edx;
    fp_top() = fp_top() * MEMF(ecx); /* fmul dword ptr [ecx] */
    ebx = MEM32(eax);
    PUSH32(esp, esi);
    esi = MEM32(eax + 4);
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    ebp = MEM32(eax + 8);
    fp_push(MEMF(edx + 8)); /* fld float */
    MEM32(esp + 0x10) = ebx;
    fp_top() = fp_top() * MEMF(ecx + 8); /* fmul dword ptr [ecx + 8] */
    ecx = MEM32(esp + 0x34);
    ecx = ecx + 0x20;
    MEM32(esp + 0x14) = esi;
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    MEM32(esp + 0x18) = ebp;
    MEMF(esp + 0x1C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_push(MEMF(ecx)); /* fld float */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(0x1E5D64)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E5D64); /* fmul dword ptr [0x1e5d64] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (TEST_NZ(_fa, _fb)) goto loc_0004178C; /* jne: not equal / not zero */

loc_0004173A: ;
    fp_push(MEMF(edx + 8)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00041756; /* jp: parity */

loc_0004174A: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, edi);
    esp = esp + 0x20;
    esp += 20; return; /* ret 16 */

loc_00041756: ;
    fp_push(MEMF(esp + 0x40)); /* fld float */
    ecx = MEM32(esp + 0x1C);
    fp_top() = fp_top() * MEMF(0x1E1888); /* fmul dword ptr [0x1e1888] */
    MEM32(esp + 0x24) = esi;
    MEM32(esp + 0x2C) = ecx;
    esi = edi + 4;
    fp_top() = fp_top() + MEMF(esp + 0x1C); /* fadd dword ptr [esp + 0x1c] */
    edx = esi;
    ecx = esp + 0x20;
    MEM32(esp + 0x20) = ebx;
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(esp + 0x28) = ebp;
    PUSH32(esp, 0x0004178Au); sub_00041660(); /* call 0x00041660 */

loc_0004178A: ;
    goto loc_000417B3;

loc_0004178C: ;
    esi = edi + 4;
    edx = esi;
    PUSH32(esp, 0x00041796u); sub_00041660(); /* call 0x00041660 */

loc_00041796: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 4); /* fmul dword ptr [esi + 4] */
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(esi); /* fmul dword ptr [esi] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() * MEMF(esi + 8); /* fmul dword ptr [esi + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 0x1C)); fp_pop(); /* fcomp dword ptr [esp + 0x1c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0004174A; /* jne: not equal / not zero */

loc_000417B3: ;
    ecx = MEM32(esp + 0x34);
    ebp = edi + 0x28;
    edx = ebp;
    PUSH32(esp, 0x000417C1u); sub_00041660(); /* call 0x00041660 */

loc_000417C1: ;
    edx = edi + 0x10;
    ecx = ecx + 0x10;
    PUSH32(esp, 0x000417CCu); sub_00041660(); /* call 0x00041660 */

loc_000417CC: ;
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    ecx = MEM32(esp + 0x1C);
    fp_top() = fp_top() + MEMF(esp + 0x40); /* fadd dword ptr [esp + 0x40] */
    edx = MEM32(esp + 0x14);
    eax = MEM32(esp + 0x18);
    MEM32(esp + 0x2C) = ecx;
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esp + 0x34);
    MEM32(esp + 0x20) = ebx;
    ebx = edi + 0x1C;
    MEM32(esp + 0x24) = edx;
    ecx = ecx + 0x30;
    edx = ebx;
    MEM32(esp + 0x28) = eax;
    PUSH32(esp, 0x00041805u); sub_00041660(); /* call 0x00041660 */

loc_00041805: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041837; /* je: equal / zero */

loc_00041809: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() * MEMF(ebx + 4); /* fmul dword ptr [ebx + 4] */
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(ebx); /* fmul dword ptr [ebx] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() * MEMF(ebx + 8); /* fmul dword ptr [ebx + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 0x1C)); fp_pop(); /* fcomp dword ptr [esp + 0x1c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041837; /* jne: not equal / not zero */

loc_00041826: ;
    eax = ebx;
    ecx = esp + 0x20;
    PUSH32(esp, 0x00041831u); sub_00041580(); /* call 0x00041580 */

loc_00041831: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041863; /* je: equal / zero */

loc_00041835: ;
    goto loc_00041858;

loc_00041837: ;
    fp_push(MEMF(esp + 0x24)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 4); /* fmul dword ptr [esi + 4] */
    fp_push(MEMF(esp + 0x20)); /* fld float */
    fp_top() = fp_top() * MEMF(esi); /* fmul dword ptr [esi] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() * MEMF(esi + 8); /* fmul dword ptr [esi + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 0x2C)); fp_pop(); /* fcomp dword ptr [esp + 0x2c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004174A; /* je: equal / zero */

loc_00041858: ;
    ecx = esp + 0x20;
    edx = ebx;
    PUSH32(esp, 0x00041863u); sub_00041660(); /* call 0x00041660 */

loc_00041863: ;
    eax = edi + 0x34;
    PUSH32(esp, eax);
    PUSH32(esp, ebp);
    ecx = esi;
    PUSH32(esp, 0x0004186Fu); sub_00065AF0(); /* call 0x00065AF0 */

loc_0004186F: ;
    eax = edi + 0x3C;
    PUSH32(esp, eax);
    eax = edi + 0x10;
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x0004187Eu); sub_00065AF0(); /* call 0x00065AF0 */

loc_0004187E: ;
    eax = edi + 0x44;
    PUSH32(esp, eax);
    eax = edi + 0x10;
    PUSH32(esp, eax);
    ecx = ebx;
    PUSH32(esp, 0x0004188Du); sub_00065AF0(); /* call 0x00065AF0 */

loc_0004188D: ;
    edx = edi + 0x4C;
    PUSH32(esp, edx);
    PUSH32(esp, ebp);
    ecx = ebx;
    PUSH32(esp, 0x00041899u); sub_00065AF0(); /* call 0x00065AF0 */

loc_00041899: ;
    fp_push(MEMF(edi + 0x48)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 4); /* fmul dword ptr [esi + 4] */
    fp_push(MEMF(edi + 0x44)); /* fld float */
    fp_top() = fp_top() * MEMF(esi); /* fmul dword ptr [esi] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 8)); fp_pop(); /* fcomp dword ptr [esi + 8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000418C6; /* je: equal / zero */

loc_000418B0: ;
    fp_push(MEMF(esi)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(esi) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 4)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(esi + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 8)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(esi + 8) = (float)fp_top(); fp_pop(); /* fstp */

loc_000418C6: ;
    fp_push(MEMF(edi + 0x40)); /* fld float */
    fp_top() = fp_top() * MEMF(ebp + 4); /* fmul dword ptr [ebp + 4] */
    fp_push(MEMF(edi + 0x3C)); /* fld float */
    fp_top() = fp_top() * MEMF(ebp); /* fmul dword ptr [ebp] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ebp + 8)); fp_pop(); /* fcomp dword ptr [ebp + 8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000418F6; /* je: equal / zero */

loc_000418DE: ;
    fp_push(MEMF(ebp)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebp) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ebp + 4)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ebp + 8)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebp + 8) = (float)fp_top(); fp_pop(); /* fstp */

loc_000418F6: ;
    fp_push(MEMF(edi + 0x38)); /* fld float */
    fp_top() = fp_top() * MEMF(edi + 0x14); /* fmul dword ptr [edi + 0x14] */
    fp_push(MEMF(edi + 0x34)); /* fld float */
    fp_top() = fp_top() * MEMF(edi + 0x10); /* fmul dword ptr [edi + 0x10] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi + 0x18)); fp_pop(); /* fcomp dword ptr [edi + 0x18] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041926; /* je: equal / zero */

loc_0004190E: ;
    fp_push(MEMF(edi + 0x10)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(edi + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(edi + 0x14)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(edi + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(edi + 0x18)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(edi + 0x18) = (float)fp_top(); fp_pop(); /* fstp */

loc_00041926: ;
    fp_push(MEMF(edi + 0x38)); /* fld float */
    fp_top() = fp_top() * MEMF(ebx + 4); /* fmul dword ptr [ebx + 4] */
    fp_push(MEMF(edi + 0x34)); /* fld float */
    fp_top() = fp_top() * MEMF(ebx); /* fmul dword ptr [ebx] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ebx + 8)); fp_pop(); /* fcomp dword ptr [ebx + 8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041953; /* je: equal / zero */

loc_0004193D: ;
    fp_push(MEMF(ebx)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebx) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ebx + 4)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebx + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(ebx + 8)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(ebx + 8) = (float)fp_top(); fp_pop(); /* fstp */

loc_00041953: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    MEM8(edi) = 1;
    SET_LO8(eax, 1);
    POP32(esp, edi);
    esp = esp + 0x20;
    esp += 20; return; /* ret 16 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041970(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00041970: ;
    esp = esp - 0x60;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x6C);
    fp_push(MEMF(esi)); /* fld float */
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x74);
    fp_top() = fp_top() + MEMF(edi); /* fadd dword ptr [edi] */
    ebx = ecx;
    edx = esp + 0xC;
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esp + 0x14);
    fp_push(MEMF(edi + 4)); /* fld float */
    MEM32(esp + 0xC) = eax;
    fp_top() = fp_top() + MEMF(esi + 4); /* fadd dword ptr [esi + 4] */
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esp + 0x18);
    fp_push(MEMF(esp + 0x14)); /* fld float */
    MEM32(esp + 0x10) = ecx;
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    PUSH32(esp, ecx);
    ecx = ebx;
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x10); /* fsub dword ptr [esp + 0x10] */
    fp_push(MEMF(esi + 4)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, edx);
    PUSH32(esp, 0x000419EBu); sub_00041500(); /* call 0x00041500 */

loc_000419EB: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000419F8; /* jne: not equal / not zero */

loc_000419EF: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x60;
    esp += 12; return; /* ret 8 */

loc_000419F8: ;
    fp_push(MEMF(esi)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi)); fp_pop(); /* fcomp dword ptr [edi] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00041A07; /* jp: parity */

loc_00041A03: ;
    fp_push(MEMF(esi)); /* fld float */
    goto loc_00041A09;

loc_00041A07: ;
    fp_push(MEMF(edi)); /* fld float */

loc_00041A09: ;
    fp_push(MEMF(esi)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi)); fp_pop(); /* fcomp dword ptr [edi] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041A18; /* jne: not equal / not zero */

loc_00041A14: ;
    fp_push(MEMF(esi)); /* fld float */
    goto loc_00041A1A;

loc_00041A18: ;
    fp_push(MEMF(edi)); /* fld float */

loc_00041A1A: ;
    fp_push(MEMF(esi + 4)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi + 4)); fp_pop(); /* fcomp dword ptr [edi + 4] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00041A2C; /* jp: parity */

loc_00041A27: ;
    fp_push(MEMF(esi + 4)); /* fld float */
    goto loc_00041A2F;

loc_00041A2C: ;
    fp_push(MEMF(edi + 4)); /* fld float */

loc_00041A2F: ;
    fp_push(MEMF(esi + 4)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi + 4)); fp_pop(); /* fcomp dword ptr [edi + 4] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041A41; /* jne: not equal / not zero */

loc_00041A3C: ;
    fp_push(MEMF(esi + 4)); /* fld float */
    goto loc_00041A44;

loc_00041A41: ;
    fp_push(MEMF(edi + 4)); /* fld float */

loc_00041A44: ;
    { double _t = fp_st1(); fp_push(_t); } /* fld st(1) */
    eax = ebx + 0x34;
    MEMF(esp + 0x44) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    ebx = ebx + 4;
    fp_top() = -fp_top(); /* fchs */
    PUSH32(esp, ebx);
    MEMF(esp + 0x58) = (float)fp_top(); fp_pop(); /* fstp */
    edx = esp + 0x24;
    ecx = esp + 0x44;
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    MEM32(esp + 0x44) = 0;
    fp_top() = -fp_top(); /* fchs */
    MEM32(esp + 0x48) = 0x3F800000;
    MEMF(esp + 0x64) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(esp + 0x50) = 0xBF800000u;
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    MEM32(esp + 0x54) = 0;
    MEMF(esp + 0x70) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(esp + 0x5C) = 0;
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    MEM32(esp + 0x60) = 0xBF800000u;
    MEMF(esp + 0x24) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(esp + 0x68) = 0x3F800000;
    { double _t = fp_st1(); fp_push(_t); } /* fld st(1) */
    MEM32(esp + 0x6C) = 0;
    MEMF(esp + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    MEMF(esp + 0x34) = (float)fp_top(); fp_pop(); /* fstp */
    MEMF(esp + 0x38) = (float)fp_top(); /* fst */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    MEMF(esp + 0x3C) = (float)fp_top(); fp_pop(); /* fstp */
    MEMF(esp + 0x40) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00041AE1u); sub_000415B0(); /* call 0x000415B0 */

loc_00041AE1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x60;
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041AF0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00041AF0: ;
    esp = esp - 0x3C;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x4C);
    fp_push(MEMF(esi + 8)); /* fld float */
    PUSH32(esp, edi);
    fp_top() = fp_top() + MEMF(esi + 0x10); /* fadd dword ptr [esi + 0x10] */
    edi = esi + 8;
    ebp = esi + 0x10;
    ebx = esi + 0x18;
    fp_top() = fp_top() + MEMF(esi); /* fadd dword ptr [esi] */
    MEM32(esp + 0x10) = ecx;
    fp_top() = fp_top() + MEMF(ebx); /* fadd dword ptr [ebx] */
    fp_top() = fp_top() * MEMF(0x1E27CC); /* fmul dword ptr [0x1e27cc] */
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x1C)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x14); /* fadd dword ptr [esi + 0x14] */
    fp_top() = fp_top() + MEMF(esi + 0xC); /* fadd dword ptr [esi + 0xc] */
    fp_top() = fp_top() + MEMF(esi + 4); /* fadd dword ptr [esi + 4] */
    fp_top() = fp_top() * MEMF(0x1E27CC); /* fmul dword ptr [0x1e27cc] */
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(esi); /* fsub dword ptr [esi] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + 4); /* fsub dword ptr [esi + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(edi); /* fsub dword ptr [edi] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(edi + 4); /* fsub dword ptr [edi + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (TEST_Z(_fa, _fb)) goto loc_00041B90; /* je: equal / zero */

loc_00041B73: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(edi); /* fsub dword ptr [edi] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(edi + 4); /* fsub dword ptr [edi + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */

loc_00041B90: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(ebp); /* fsub dword ptr [ebp] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(ebp + 4); /* fsub dword ptr [ebp + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (TEST_Z(_fa, _fb)) goto loc_00041BD5; /* je: equal / zero */

loc_00041BB7: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(ebp); /* fsub dword ptr [ebp] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(ebp + 4); /* fsub dword ptr [ebp + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */

loc_00041BD5: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(ebx); /* fsub dword ptr [ebx] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(ebx + 4); /* fsub dword ptr [ebx + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (TEST_Z(_fa, _fb)) goto loc_00041C18; /* je: equal / zero */

loc_00041BFB: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(ebx); /* fsub dword ptr [ebx] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(ebx + 4); /* fsub dword ptr [ebx + 4] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = fp_top(); fp_pop(); /* fstp st(2) */
    fp_pop(); /* fstp st(0) */

loc_00041C18: ;
    fp_top() = sqrt(fp_top()); /* fsqrt */
    PUSH32(esp, ecx);
    eax = esp + 0x18;
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    PUSH32(esp, 0x00041C28u); sub_00041500(); /* call 0x00041500 */

loc_00041C28: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041C36; /* jne: not equal / not zero */

loc_00041C2C: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x3C;
    esp += 8; return; /* ret 4 */

loc_00041C36: ;
    PUSH32(esp, edi);
    PUSH32(esp, esi);
    ecx = esp + 0x24;
    PUSH32(esp, 0x00041C41u); sub_00065D60(); /* call 0x00065D60 */

loc_00041C41: ;
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    ecx = esp + 0x30;
    PUSH32(esp, 0x00041C4Cu); sub_00065D60(); /* call 0x00065D60 */

loc_00041C4C: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ecx = esp + 0x3C;
    PUSH32(esp, 0x00041C57u); sub_00065D60(); /* call 0x00065D60 */

loc_00041C57: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    ecx = esp + 0x48;
    PUSH32(esp, 0x00041C62u); sub_00065D60(); /* call 0x00065D60 */

loc_00041C62: ;
    eax = MEM32(esp + 0x10);
    ecx = eax + 0x34;
    PUSH32(esp, ecx);
    eax = eax + 4;
    PUSH32(esp, eax);
    edx = esi;
    ecx = esp + 0x24;
    PUSH32(esp, 0x00041C79u); sub_000415B0(); /* call 0x000415B0 */

loc_00041C79: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x3C;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00041C90(void)
{

loc_00041C90: ;
    eax = MEM32(esp + 4);
    edx = MEM32(esp + 8);
    MEM32(ecx + 0x188) = eax;
    MEM32(ecx + 0x18C) = edx;
    SET_LO8(eax, 1);
    esp += 12; return; /* ret 8 */

}

void sub_00041CB0(void)
{

loc_00041CB0: ;
    edx = MEM32(esp + 4);
    eax = MEM32(ecx + 0x190);
    MEM32(ecx + 0x190) = edx;
    esp += 8; return; /* ret 4 */

}

void sub_00041CD0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00041CD0: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    esi = ecx;
    SET_LO8(edx, 0); /* xor self */
    ecx = edi;
    PUSH32(esp, 0x00041CE1u); sub_0002E4B0(); /* call 0x0002E4B0 */

loc_00041CE1: ;
    PUSH32(esp, edi);
    ecx = esi + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    PUSH32(esp, 0x00041CEDu); sub_0002E4F0(); /* call 0x0002E4F0 */

loc_00041CED: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, edi);
    POP32(esp, esi);
    if (TEST_Z(_fa, _fb)) goto loc_00041CF9; /* je: equal / zero */

loc_00041CF3: ;
    MEM32(eax + 4) = MEM32(eax + 4) + 1;
    esp += 8; return; /* ret 4 */

loc_00041CF9: ;
    eax = 0; /* xor self */
    esp += 8; return; /* ret 4 */

}

void sub_00041D00(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_00041D00: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    _cf = (int)((uint32_t)(esp) < (uint32_t)(0xF4));
    esp = esp - 0xF4;
    eax = MEM32(ebp + 0xC);
    PUSH32(esp, ebx);
    ebx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    ecx = ZX16(MEM16(ebx));
    esi = MEM32(eax + ecx * 4 + 4);
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(eax)) >> 32) & 1);
    esi = esi + eax;
    SET_LO8(edx, 0); /* xor self */
    ecx = esi;
    MEM32(ebp + -16) = edi;
    MEM32(ebp + -20) = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041D2Cu); sub_0002E4B0(); /* call 0x0002E4B0 */

loc_00041D2C: ;
    PUSH32(esp, esi);
    ecx = edi + 4;
    esi = 0; /* xor self */
    MEM32(ebp + -36) = ecx;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    MEM32(ebp + -32) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041D3Fu); sub_0002E4F0(); /* call 0x0002E4F0 */

loc_00041D3F: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041D55; /* je: equal / zero */

loc_00041D43: ;
    MEM32(eax + 4) = MEM32(eax + 4) + 1;
    esp = ebp + -256;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

loc_00041D55: ;
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM32(ebp + -24) = esi;
    if (TEST_Z(_fa, _fb)) goto loc_00041D62; /* je: equal / zero */

loc_00041D5F: ;
    MEM32(ebp + -24) = ebx;

loc_00041D62: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM32(ebp + -28) = esi;
    if (TEST_Z(_fa, _fb)) goto loc_00041D81; /* je: equal / zero */

loc_00041D69: ;
    eax = 0x124;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041D73u); sub_0010F4D0(); /* call 0x0010F4D0 */

loc_00041D73: ;
    edi = esp;
    ecx = 0x49;
    esi = ebx;
    MEM32(ebp + -28) = edi;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */

loc_00041D81: ;
    eax = MEM32(ebx + 4);
    ebx = eax;
    if (0x14) _cf = (int)(((ebx) >> ((0x14) - 1)) & 1);
    ebx = ebx >> 0x14;
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 1);
    MEM8(ebp + -11) = LO8(ebx);
    esi = MEM32(ebp + 8);
    SET_LO16(esi, MEM16(esi + 2));
    ebx = eax;
    if (0x15) _cf = (int)(((ebx) >> ((0x15) - 1)) & 1);
    ebx = ebx >> 0x15;
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 1);
    MEM8(ebp + -10) = LO8(ebx);
    ebx = eax;
    if (0x19) _cf = (int)(((ebx) >> ((0x19) - 1)) & 1);
    ebx = ebx >> 0x19;
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 1);
    MEM8(ebp + -9) = LO8(ebx);
    ebx = eax;
    if (0x1A) _cf = (int)(((ebx) >> ((0x1A) - 1)) & 1);
    ebx = ebx >> 0x1A;
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 1);
    MEM8(ebp + -12) = LO8(ebx);
    ecx = eax;
    if (1) _cf = (int)(((ecx) >> ((1) - 1)) & 1);
    ecx = ecx >> 1;
    ebx = eax;
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 0xC);
    _cf = 0; /* logical op clears CF */
    SET_LO8(ecx, LO8(ecx) & 1);
    SET_LO8(edx, LO8(eax));
    _cf = 0; /* logical op clears CF */
    SET_LO8(edx, LO8(edx) & 1);
    _cf = (int)((LO8(ebx)) != 0);
    SET_LO8(ebx, (uint32_t)(-(int32_t)LO8(ebx)));
    SET_LO8(ebx, _cf ? 0xFFFFFFFF : 0); /* sbb self (CF extend) */
    SET_LO8(ebx, LO8(ebx) + 1);
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(1) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 1 (16-bit) */
    MEM32(ebp + -4) = 0;
    if (CMP_NE(_fa, _fb)) goto loc_00041E31; /* jne: not equal / not zero */

loc_00041DDB: ;
    eax = 0x238D30;
    esi = 0; /* xor self */
    MEM32(ebp + -8) = eax;

loc_00041DE5: ;
    _fa = (uint32_t)(MEM8(eax + 1)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 1), LO8(ecx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E0F; /* jne: not equal / not zero */

loc_00041DEA: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), LO8(edx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E0F; /* jne: not equal / not zero */

loc_00041DEE: ;
    eax = MEM32(ebp + -8);
    SET_LO8(eax, MEM8(eax + 2));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ebp + -11)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ebp + -11) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E0C; /* jne: not equal / not zero */

loc_00041DF9: ;
    SET_LO8(eax, MEM8(ebp + -10));
    edi = MEM32(ebp + -8);
    _fa = (uint32_t)(MEM8(edi + 3)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 3), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E0C; /* jne: not equal / not zero */

loc_00041E04: ;
    SET_LO8(eax, MEM8(ebp + -9));
    _fa = (uint32_t)(MEM8(edi + 4)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 4), LO8(eax) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041E22; /* je: equal / zero */

loc_00041E0C: ;
    eax = MEM32(ebp + -8);

loc_00041E0F: ;
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(0xC)) >> 32) & 1);
    eax = eax + 0xC;
    esi++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x238D9C) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x238D9C (32-bit) */
    MEM32(ebp + -8) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_00041DE5; /* jl: less (signed <) */

loc_00041E1D: ;
    goto loc_00041F78;

loc_00041E22: ;
    ecx = esi + esi * 2;
    edx = MEM32(ecx * 4 + 0x238D38);
    goto loc_00041F75;

loc_00041E31: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(2) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 2 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E8D; /* jne: not equal / not zero */

loc_00041E37: ;
    eax = 0x238DA0;
    esi = 0; /* xor self */
    MEM32(ebp + -8) = eax;

loc_00041E41: ;
    _fa = (uint32_t)(MEM8(eax + 1)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 1), LO8(ecx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E6B; /* jne: not equal / not zero */

loc_00041E46: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), LO8(edx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E6B; /* jne: not equal / not zero */

loc_00041E4A: ;
    eax = MEM32(ebp + -8);
    SET_LO8(eax, MEM8(eax + 2));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ebp + -11)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ebp + -11) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E68; /* jne: not equal / not zero */

loc_00041E55: ;
    SET_LO8(eax, MEM8(ebp + -10));
    edi = MEM32(ebp + -8);
    _fa = (uint32_t)(MEM8(edi + 3)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 3), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041E68; /* jne: not equal / not zero */

loc_00041E60: ;
    SET_LO8(eax, MEM8(ebp + -9));
    _fa = (uint32_t)(MEM8(edi + 4)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 4), LO8(eax) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00041E7E; /* je: equal / zero */

loc_00041E68: ;
    eax = MEM32(ebp + -8);

loc_00041E6B: ;
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(0xC)) >> 32) & 1);
    eax = eax + 0xC;
    esi++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x238E24) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x238E24 (32-bit) */
    MEM32(ebp + -8) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_00041E41; /* jl: less (signed <) */

loc_00041E79: ;
    goto loc_00041F78;

loc_00041E7E: ;
    ecx = esi + esi * 2;
    edx = MEM32(ecx * 4 + 0x238DA8);
    goto loc_00041F75;

loc_00041E8D: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(3) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 3 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041EAA; /* jne: not equal / not zero */

loc_00041E93: ;
    if (6) _cf = (int)(((eax) >> ((6) - 1)) & 1);
    eax = eax >> 6;
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) & 1);
    _cf = (int)((LO8(eax)) != 0);
    SET_LO8(eax, (uint32_t)(-(int32_t)LO8(eax)));
    eax = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    eax = eax & 7;
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(0x1B)) >> 32) & 1);
    eax = eax + 0x1B;
    MEM32(ebp + -4) = eax;
    goto loc_00041F78;

loc_00041EAA: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(4) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 4 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041EDC; /* jne: not equal / not zero */

loc_00041EB0: ;
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041EC9; /* je: equal / zero */

loc_00041EB7: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(0x1F)) >> 32) & 1);
    eax = eax + 0x1F;
    MEM32(ebp + -4) = eax;
    goto loc_00041F78;

loc_00041EC9: ;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    SET_LO8(ecx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    ecx = ecx + ecx + 1;
    MEM32(ebp + -4) = ecx;
    goto loc_00041F78;

loc_00041EDC: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(5) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 5 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041EF1; /* jne: not equal / not zero */

loc_00041EE2: ;
    _cf = (int)((LO8(ecx)) != 0);
    SET_LO8(ecx, (uint32_t)(-(int32_t)LO8(ecx)));
    ecx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = (int)((((uint64_t)(ecx) + (uint64_t)(0x1A)) >> 32) & 1);
    ecx = ecx + 0x1A;
    MEM32(ebp + -4) = ecx;
    goto loc_00041F78;

loc_00041EF1: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(6) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 6 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041F00; /* jne: not equal / not zero */

loc_00041EF7: ;
    MEM32(ebp + -4) = 0x22;
    goto loc_00041F78;

loc_00041F00: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(7) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 7 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00041F22; /* jne: not equal / not zero */

loc_00041F06: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041F16; /* je: equal / zero */

loc_00041F0A: ;
    _cf = (int)((LO8(edx)) != 0);
    SET_LO8(edx, (uint32_t)(-(int32_t)LO8(edx)));
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xC;
    _cf = (int)((((uint64_t)(edx) + (uint64_t)(0x34)) >> 32) & 1);
    edx = edx + 0x34;
    goto loc_00041F75;

loc_00041F16: ;
    _cf = (int)((LO8(edx)) != 0);
    SET_LO8(edx, (uint32_t)(-(int32_t)LO8(edx)));
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xC;
    _cf = (int)((((uint64_t)(edx) + (uint64_t)(0x33)) >> 32) & 1);
    edx = edx + 0x33;
    goto loc_00041F75;

loc_00041F22: ;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(8) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(esi), 8 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00042075; /* jne: not equal / not zero */

loc_00041F2C: ;
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041F54; /* je: equal / zero */

loc_00041F33: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041F44; /* je: equal / zero */

loc_00041F37: ;
    edx = 0; /* xor self */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    SET_LO8(edx, (TEST_Z(_fa, _fb)) ? 1 : 0); /* sete */
    edx = edx + edx + 0x4A;
    goto loc_00041F75;

loc_00041F44: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    SET_LO8(eax, (TEST_Z(_fa, _fb)) ? 1 : 0); /* sete */
    eax = eax + eax + 0x49;
    MEM32(ebp + -4) = eax;
    goto loc_00041F78;

loc_00041F54: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041F67; /* je: equal / zero */

loc_00041F58: ;
    _cf = (int)((LO8(ecx)) != 0);
    SET_LO8(ecx, (uint32_t)(-(int32_t)LO8(ecx)));
    ecx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 7;
    _cf = (int)((((uint64_t)(ecx) + (uint64_t)(3)) >> 32) & 1);
    ecx = ecx + 3;
    MEM32(ebp + -4) = ecx;
    goto loc_00041F78;

loc_00041F67: ;
    edx = 0; /* xor self */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    SET_LO8(edx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    edx = edx * 4 + 1;

loc_00041F75: ;
    MEM32(ebp + -4) = edx;

loc_00041F78: ;
    esi = MEM32(ebp + -16);
    ecx = MEM32(esi + 0x190);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00041F98; /* je: equal / zero */

loc_00041F85: ;
    edx = MEM32(ebp + -4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    edx = MEM32(ebp + 8);
    PUSH32(esp, edx);
    edx = MEM32(ebp + -20);
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00041F95u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00041F95: ;
    MEM32(ebp + -4) = eax;

loc_00041F98: ;
    SET_LO8(eax, MEM8(ebp + -12));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041FBB; /* jne: not equal / not zero */

loc_00041F9F: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00041FBB; /* jne: not equal / not zero */

loc_00041FA3: ;
    eax = MEM32(ebp + -24);
    ecx = MEM32(ebp + -4);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 0x18C);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00041FB6u); sub_00109BB0(); /* call 0x00109BB0 */

loc_00041FB6: ;
    goto loc_00042046;

loc_00041FBB: ;
    esi = MEM32(ebp + -4);
    esi = (uint32_t)((int32_t)esi * (int32_t)0xD0);
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(0x1E5D70)) >> 32) & 1);
    esi = esi + 0x1E5D70;
    ecx = 0x34;
    edi = ebp + -244;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    SET_LO8(ecx, MEM8(ebp + -241));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (CMP_BE(_fa & _fb, 0)) goto loc_0004202D; /* jbe: below or equal (unsigned <=) */

loc_00041FE1: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    SET_LO8(edx, 0x80);
    if (TEST_Z(_fa, _fb)) goto loc_00042008; /* je: equal / zero */

loc_00041FE7: ;
    SET_LO8(eax, MEM8(ebp + -110));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042008; /* je: equal / zero */

loc_00041FEE: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (CMP_BE(_fa & _fb, 0)) goto loc_00042008; /* jbe: below or equal (unsigned <=) */

loc_00041FF2: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042008; /* je: equal / zero */

loc_00041FF6: ;
    SET_LO8(eax, MEM8(ebp + -244));
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | LO8(edx));
    MEM8(ebp + -110) = 0;
    MEM8(ebp + -244) = LO8(eax);

loc_00042008: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004202D; /* je: equal / zero */

loc_0004200C: ;
    SET_LO8(eax, MEM8(ebp + -111));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004202D; /* je: equal / zero */

loc_00042013: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (CMP_BE(_fa & _fb, 0)) goto loc_0004202D; /* jbe: below or equal (unsigned <=) */

loc_00042017: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004202D; /* je: equal / zero */

loc_0004201B: ;
    SET_LO8(eax, MEM8(ebp + -244));
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | LO8(edx));
    MEM8(ebp + -111) = 0;
    MEM8(ebp + -244) = LO8(eax);

loc_0004202D: ;
    edx = MEM32(ebp + -24);
    ecx = MEM32(ebp + -16);
    ecx = MEM32(ecx + 0x18C);
    PUSH32(esp, edx);
    eax = ebp + -244;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00042046u); sub_00109BF0(); /* call 0x00109BF0 */

loc_00042046: ;
    ebx = eax;
    eax = MEM32(ebp + -28);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042056; /* je: equal / zero */

loc_0004204F: ;
    edx = MEM32(ebp + 0xC);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    goto loc_0004205E;

loc_00042056: ;
    eax = MEM32(ebp + 0xC);
    ecx = MEM32(ebp + 8);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);

loc_0004205E: ;
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00042065u); sub_0010A370(); /* call 0x0010A370 */

loc_00042065: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00042086; /* jne: not equal / not zero */

loc_00042069: ;
    MEM32(ebx + 4) = MEM32(ebx + 4) - 1;
    if ((MEM32(ebx + 4) != 0)) goto loc_00042075; /* jne: not equal / not zero */

loc_0004206E: ;
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00042075u); sub_0002E400(); /* call 0x0002E400 */

loc_00042075: ;
    eax = 0; /* xor self */
    esp = ebp + -256;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

loc_00042086: ;
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000420A7; /* je: equal / zero */

loc_0004208D: ;
    SET_LO16(edx, MEM16(ebp + -32));
    ecx = MEM32(ebp + -16);
    eax = MEM32(ebp + -20);
    MEM32(ebx + 8) = 0xC;
    MEM16(ebx + 0xE) = LO16(edx);
    MEM32(ebx + 0x14) = ecx;
    goto loc_000420EC;

loc_000420A7: ;
    esi = MEM32(ebp + -20);
    eax = esi;
    edx = eax + 1;
    /* nop */

loc_000420B0: ;
    SET_LO8(ecx, MEM8(eax));
    eax++;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000420B0; /* jne: not equal / not zero */

loc_000420B7: ;
    _cf = (int)((uint32_t)(eax) < (uint32_t)(edx));
    eax = eax - edx;
    edi = eax + 1;
    PUSH32(esp, edi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x000420C2u); sub_0010F511(); /* call 0x0010F511 */

loc_000420C2: ;
    ecx = edi;
    edx = ecx;
    if (2) _cf = (int)(((ecx) >> ((2) - 1)) & 1);
    ecx = ecx >> 2;
    edi = eax;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    edx = MEM32(ebp + -16);
    _cf = (int)((((uint64_t)(esp) + (uint64_t)(4)) >> 32) & 1);
    esp = esp + 4;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    SET_LO16(ecx, MEM16(ebp + -32));
    MEM32(ebx + 8) = 0;
    MEM16(ebx + 0xE) = LO16(ecx);
    MEM32(ebx + 0x14) = edx;

loc_000420EC: ;
    MEM32(ebx + 0x10) = eax;
    eax = MEM32(ebp + -16);
    MEM8(ebx + 0xC) = 0;
    ecx = MEM32(eax + 0x190);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042112; /* je: equal / zero */

loc_00042100: ;
    eax = MEM32(ebp + -4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(ebp + 8);
    PUSH32(esp, eax);
    eax = MEM32(ebp + -20);
    PUSH32(esp, eax);
    PUSH32(esp, ebx);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00042112u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042112: ;
    eax = ZX16(MEM16(ebx + 0xE));
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    ecx = 0x61;
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)ecx));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)ecx)); }
    ecx = MEM32(ebp + -36);
    eax = MEM32(ecx + edx * 4);
    MEM32(ecx + edx * 4) = ebx;
    MEM32(ebx + 0x18) = eax;
    eax = ebx;
    esp = ebp + -256;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

}

void sub_00042140(void)
{

loc_00042140: ;
    eax = MEM32(esp + 8);
    edx = MEM32(esp + 4);
    PUSH32(esp, 1);
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00042151u); sub_00041D00(); /* call 0x00041D00 */

loc_00042151: ;
    esp += 12; return; /* ret 8 */

}

void sub_00042170(void)
{

loc_00042170: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    esi = ecx;
    SET_LO8(edx, 0); /* xor self */
    ecx = edi;
    PUSH32(esp, 0x00042181u); sub_0002E4B0(); /* call 0x0002E4B0 */

loc_00042181: ;
    PUSH32(esp, edi);
    ecx = esi + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    PUSH32(esp, 0x0004218Du); sub_0002E4F0(); /* call 0x0002E4F0 */

loc_0004218D: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_000421A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000421A0: ;
    edx = MEM32(esp + 4);
    eax = MEM32(esp + 0xC);
    eax = MEM32(edx + eax * 4 + 2);
    eax = eax + edx;
    MEM32(esp + 0xC) = 0;
    MEM32(esp + 4) = eax;
    g_seh_ebp = ebp; sub_00041D00(); return; /* tail jmp 0x00041D00 */

}

void sub_000421C0(void)
{

loc_000421C0: ;
    PUSH32(esp, 0x1EAB80);
    PUSH32(esp, 0x000421CAu); sub_0002E27A(); /* call 0x0002E27A */

loc_000421CA: ;
    esp += 4; return; /* ret */

}

void sub_000421D0(void)
{

loc_000421D0: ;
    PUSH32(esp, 0x1EAB80);
    PUSH32(esp, 0x000421DAu); sub_0002E295(); /* call 0x0002E295 */

loc_000421DA: ;
    esp += 4; return; /* ret */

}

void sub_000421E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000421E0: ;
    esp = esp - 8;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x14);
    ebx = 0; /* xor self */
    ebp--;
    eax = ebp;
    eax = eax >> 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x14) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_00042228; /* je: equal / zero */

loc_000421FA: ;
    ecx = ZX16(MEM16(ecx));
    MEM32(esp + 0x10) = ecx;

loc_00042201: ;
    edi = MEM32(esp + 0x10);
    esi = eax + ebx;
    ecx = esi + esi * 2;
    edi = edi - MEM32(edx + ecx * 2);
    if ((edi == 0)) goto loc_0004224D; /* je: equal / zero */

loc_00042210: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00042218; /* jle: less or equal (signed <=) */

loc_00042214: ;
    ebx = esi;
    goto loc_0004221A;

loc_00042218: ;
    ebp = esi;

loc_0004221A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042228; /* je: equal / zero */

loc_0004221E: ;
    eax = ebp;
    eax = eax - ebx;
    eax = eax >> 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00042201; /* jne: not equal / not zero */

loc_00042228: ;
    eax = MEM32(esp + 0x14);
    eax = ZX16(MEM16(eax));
    esi = ebx + ebx * 2;
    edi = MEM32(edx + esi * 2);
    ecx = eax;
    ecx = ecx - edi;
    if ((ecx != 0)) goto loc_0004225F; /* jne: not equal / not zero */

loc_0004223B: ;
    ecx = MEM32(esp + 0x20);
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    MEM32(ecx) = ebx;
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_0004224D: ;
    edx = MEM32(esp + 0x20);
    POP32(esp, edi);
    MEM32(edx) = esi;
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_0004225F: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_00042275; /* jge: greater or equal (signed >=) */

loc_00042263: ;
    edx = MEM32(esp + 0x20);
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    MEM32(edx) = ebx;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_00042275: ;
    ecx = ebp + ebp * 2;
    eax = eax - MEM32(edx + ecx * 2);
    if ((eax != 0)) goto loc_00042290; /* jne: not equal / not zero */

loc_0004227E: ;
    edx = MEM32(esp + 0x20);
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(edx) = ebp;
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_00042290: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000422AA; /* jle: less or equal (signed <=) */

loc_00042294: ;
    eax = MEM32(esp + 0x20);
    ecx = MEM32(esp + 0x1C);
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    MEM32(eax) = ecx;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

loc_000422AA: ;
    edx = MEM32(esp + 0x20);
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(edx) = ebp;
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 12; return; /* ret 8 */

}

void sub_000422C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000422C0: ;
    esp = esp - 8;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000422CD; /* jne: not equal / not zero */

loc_000422C7: ;
    SET_LO16(eax, ZX8(LO8(ecx)));
    goto loc_000422D3;

loc_000422CD: ;
    eax = 0; /* xor self */
    SET_HI8(eax, LO8(ecx));
    SET_LO8(eax, LO8(edx));

loc_000422D3: ;
    ecx = esp + 4;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x15DB);
    edx = 0x4BFB80;
    ecx = esp + 8;
    MEM32(esp + 8) = eax;
    PUSH32(esp, 0x000422EFu); sub_000421E0(); /* call 0x000421E0 */

loc_000422EF: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042311; /* je: equal / zero */

loc_000422F3: ;
    eax = MEM32(esp + 4);
    ecx = MEM32(esp + 0xC);
    edx = eax + eax * 2;
    SET_LO16(eax, MEM16(edx * 2 + 0x4BFB84));
    MEM16(ecx) = LO16(eax);
    SET_LO8(eax, 1);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_00042311: ;
    SET_LO8(eax, 0); /* xor self */
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

}

void sub_00042320(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00042320: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042333; /* je: equal / zero */

loc_00042329: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042333; /* jne: not equal / not zero */

loc_0004232E: ;
    PUSH32(esp, 0x00042333u); sub_0002E400(); /* call 0x0002E400 */

loc_00042333: ;
    eax = MEM32(esp + 8);
    MEM32(esi) = eax;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_00042340(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00042340: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x1C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042354; /* je: equal / zero */

loc_0004234A: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042354; /* jne: not equal / not zero */

loc_0004234F: ;
    PUSH32(esp, 0x00042354u); sub_0002E400(); /* call 0x0002E400 */

loc_00042354: ;
    eax = MEM32(esp + 8);
    MEM32(esi + 0x1C) = eax;
    esi = eax;
    MEM32(esi + 4) = MEM32(esi + 4) + 1;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_00042370(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00042370: ;
    ecx = MEM32(ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000423AF; /* je: equal / zero */

loc_00042376: ;
    eax = MEM32(ecx + -4);
    PUSH32(esp, ebx);
    ebx = ecx + -4;
    ecx = ecx + eax * 8;
    eax--;
    if (((int32_t)eax < 0)) goto loc_000423A5; /* js: sign (negative) */

loc_00042383: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx + 4;
    edi = eax + 1;
    goto loc_00042390;

    /* nop */

loc_00042390: ;
    ecx = MEM32(esi + -8);
    esi = esi - 8;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000423A0; /* je: equal / zero */

loc_0004239A: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000423A0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000423A0: ;
    edi--;
    if ((edi != 0)) goto loc_00042390; /* jne: not equal / not zero */

loc_000423A3: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_000423A5: ;
    PUSH32(esp, ebx);
    PUSH32(esp, 0x000423ABu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000423AB: ;
    esp = esp + 4;
    POP32(esp, ebx);

loc_000423AF: ;
    esp += 4; return; /* ret */

}

void sub_000423B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000423B0: ;
    PUSH32(esp, ebp);
    ebp = ecx;
    ecx = MEM32(ebp);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000423FA; /* je: equal / zero */

loc_000423BA: ;
    eax = MEM32(ecx + -4);
    PUSH32(esp, edi);
    edi = ecx + -4;
    ecx = ecx + eax * 8;
    eax--;
    if (((int32_t)eax < 0)) goto loc_000423E5; /* js: sign (negative) */

loc_000423C7: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx + 4;
    ebx = eax + 1;
    /* nop */

loc_000423D0: ;
    ecx = MEM32(esi + -8);
    esi = esi - 8;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000423E0; /* je: equal / zero */

loc_000423DA: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000423E0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000423E0: ;
    ebx--;
    if ((ebx != 0)) goto loc_000423D0; /* jne: not equal / not zero */

loc_000423E3: ;
    POP32(esp, esi);
    POP32(esp, ebx);

loc_000423E5: ;
    PUSH32(esp, edi);
    PUSH32(esp, 0x000423EBu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000423EB: ;
    ecx = MEM32(esp + 0x10);
    esp = esp + 4;
    POP32(esp, edi);
    MEM32(ebp) = ecx;
    POP32(esp, ebp);
    esp += 8; return; /* ret 4 */

loc_000423FA: ;
    edx = MEM32(esp + 8);
    MEM32(ebp) = edx;
    POP32(esp, ebp);
    esp += 8; return; /* ret 4 */

}

void sub_00042410(void)
{

loc_00042410: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = 0; /* xor self */
    eax = 1;
    MEM32(esi + 4) = eax;
    MEM32(esi + 0x10) = edi;
    MEM32(esi + 8) = eax;
    MEM32(esi + 0x14) = edi;
    MEM32(esi) = 0x1EAB90;
    MEM32(esi + 0x1C) = edi;
    ecx = esi + 0x2C;
    MEM32(esi + 0x20) = edi;
    PUSH32(esp, 0x0004243Bu); sub_00044F20(); /* call 0x00044F20 */

loc_0004243B: ;
    ecx = esi + 0x54;
    MEM32(esi + 0x48) = edi;
    MEM32(esi + 0x44) = edi;
    MEM32(esi + 0x50) = edi;
    PUSH32(esp, 0x0004244Cu); sub_00044F20(); /* call 0x00044F20 */

loc_0004244C: ;
    MEM32(esi + 0x70) = edi;
    MEM32(esi + 0x6C) = edi;
    MEM32(esi + 0x78) = edi;
    MEM32(esi + 0x7C) = edi;
    MEM32(esi + 0x80) = edi;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

void sub_00042470(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00042470: ;
    esp = esp - 0x20;
    PUSH32(esp, ebx);
    MEM32(esp + 4) = ecx;
    eax = MEM32(ecx + 0x38);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = MEM32(ecx + 0x30);
    MEM32(esp + 0x28) = eax;
    eax = MEM32(ecx + 0x68);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    PUSH32(esp, edi);
    MEM32(esp + 0x1C) = esi;
    MEM32(esp + 0x28) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_0004249F; /* je: equal / zero */

loc_00042496: ;
    edx = ZX16(MEM16(eax));
    MEM32(esp + 0x14) = edx;
    goto loc_000424A3;

loc_0004249F: ;
    MEM32(esp + 0x14) = ebp;

loc_000424A3: ;
    MEM32(ecx + 0x28) = ebp;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = ebp;
    ecx = MEM32(esp + 0x10);
    ebx = MEM32(ecx + 0x40);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, ebp (32-bit) */
    MEM32(esp + 0x18) = ebx;
    if (CMP_EQ(_fa, _fb)) goto loc_000426E3; /* je: equal / zero */

loc_000424C0: ;
    edi = ZX16(MEM16(ebx));
    edi = edi + MEM32(esp + 0x14);
    edx = edi * 8 + 4;
    PUSH32(esp, edx);
    PUSH32(esp, 0x000424D4u); sub_0010F511(); /* call 0x0010F511 */

loc_000424D4: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000424EE; /* je: equal / zero */

loc_000424DB: ;
    PUSH32(esp, 0xC1410);
    PUSH32(esp, edi);
    ebp = eax + 4;
    PUSH32(esp, 8);
    PUSH32(esp, ebp);
    MEM32(eax) = edi;
    PUSH32(esp, 0x000424EEu); sub_00012040(); /* call 0x00012040 */

loc_000424EE: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, ebp);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x000424FBu); sub_000423B0(); /* call 0x000423B0 */

loc_000424FB: ;
    _fa = (uint32_t)(MEM16(ebx)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(ebx), 0 (16-bit) */
    MEM32(esp + 0x20) = 0;
    if (CMP_BE(_fa, _fb)) goto loc_00042635; /* jbe: below or equal (unsigned <=) */

loc_0004250D: ;
    eax = ebx + 2;
    MEM32(esp + 0x24) = eax;

loc_00042514: ;
    ecx = MEM32(esp + 0x24);
    edi = MEM32(ecx);
    eax = ZX16(MEM16(edi + ebx + 2));
    edi = edi + ebx;
    eax = eax - 2;
    if ((eax == 0)) goto loc_00042616; /* je: equal / zero */

loc_0004252A: ;
    eax = ZX16(MEM16(edi + 4));
    eax++;
    edx = eax + eax * 2;
    eax = MEM32(esp + 0x2C);
    ecx = MEM32(eax + edx * 2);
    edx = ZX16(MEM16(ecx + eax));
    ecx = ZX16(MEM16(edi));
    ebx = MEM32(esi + ecx * 4 + 4);
    eax = MEM32(esi + edx * 4 + 4);
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x24);
    eax = eax + esi;
    ebx = ebx + esi;
    esi = MEM32(ecx + 0x20);
    ecx = MEM32(ecx + 0x1C);
    PUSH32(esp, eax);
    esi = esi + edx * 8;
    PUSH32(esp, 0x00042562u); sub_00034C10(); /* call 0x00034C10 */

loc_00042562: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004260E; /* je: equal / zero */

loc_0004256C: ;
    eax = ZX16(MEM16(edi + 2));
    eax--;
    if ((eax != 0)) goto loc_000426D8; /* jne: not equal / not zero */

loc_00042577: ;
    PUSH32(esp, 0x20);
    PUSH32(esp, 0x0004257Eu); sub_0010F511(); /* call 0x0010F511 */

loc_0004257E: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042590; /* je: equal / zero */

loc_00042585: ;
    ecx = eax;
    PUSH32(esp, 0x0004258Cu); sub_00046B60(); /* call 0x00046B60 */

loc_0004258C: ;
    edi = eax;
    goto loc_00042592;

loc_00042590: ;
    edi = 0; /* xor self */

loc_00042592: ;
    ecx = MEM32(esi + 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004259F; /* je: equal / zero */

loc_00042599: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x0004259Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004259F: ;
    eax = edi;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 4) = edi;
    if (TEST_Z(_fa, _fb)) goto loc_0004260E; /* je: equal / zero */

loc_000425A8: ;
    MEM32(eax + 4) = ebx;
    ecx = MEM32(esi + 4);
    edx = MEM32(esp + 0x10);
    MEM32(ecx + 8) = edx;
    eax = MEM32(esi + 4);
    ecx = MEM32(ebp);
    MEM32(eax + 0xC) = ecx;
    eax = MEM32(esp + 0x20);
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x14);
    eax = eax + 0x2C;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x000425D3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000425D3: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; sub_00042845(); return; } /* je: equal / zero */

loc_000425DB: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x28);
    MEM32(esi) = edx;
    esi = MEM32(esi + 4);
    edi = MEM32(esp + 0x10);
    eax = MEM32(esi);
    ecx = esi;
    edi = edi + 0x28;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x000425F5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000425F5: ;
    MEM32(edi) = MEM32(edi) + eax;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x28);
    ecx = ecx + 3;
    ecx = ecx & 0xFFFFFFFCu;
    MEM32(eax + 0x28) = ecx;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = MEM32(eax + 0x24) + 1;

loc_0004260E: ;
    ebx = MEM32(esp + 0x18);
    esi = MEM32(esp + 0x1C);

loc_00042616: ;
    edx = MEM32(esp + 0x24);
    eax = MEM32(esp + 0x20);
    edx = edx + 4;
    MEM32(esp + 0x24) = edx;
    edx = ZX16(MEM16(ebx));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(esp + 0x20) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_00042514; /* jl: less (signed <) */

loc_00042635: ;
    ebp = 0; /* xor self */

loc_00042637: ;
    _fa = (uint32_t)(MEM32(esp + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 0x14), ebp (32-bit) */
    MEM32(esp + 0x24) = ebp;
    if (CMP_LE(_fas, _fbs)) goto loc_000427D2; /* jle: less or equal (signed <=) */

loc_00042645: ;
    ecx = MEM32(esp + 0x28);
    ecx = ecx + 2;
    MEM32(esp + 0x20) = ecx;

loc_00042650: ;
    edx = MEM32(esp + 0x20);
    edi = MEM32(edx);
    edx = MEM32(esp + 0x28);
    eax = ZX16(MEM16(edi + edx + 2));
    edi = edi + edx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000427B2; /* jl: less (signed <) */

loc_0004266A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 9 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_000427B2; /* jg: greater (signed >) */

loc_00042673: ;
    ecx = MEM32(esp + 0x10);
    eax = MEM32(ecx + 0x58);
    edx = ZX16(MEM16(edi));
    ebx = MEM32(eax + edx * 4 + 4);
    edx = ZX16(MEM16(edi + 8));
    edx = MEM32(eax + edx * 4 + 4);
    esi = MEM32(ecx + 0x20);
    edx = edx + eax;
    ebx = ebx + eax;
    eax = MEM32(ecx + 0x24);
    ecx = MEM32(ecx + 0x1C);
    PUSH32(esp, edx);
    esi = esi + eax * 8;
    PUSH32(esp, 0x0004269Fu); sub_00034C10(); /* call 0x00034C10 */

loc_0004269F: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000427B2; /* je: equal / zero */

loc_000426A9: ;
    eax = ZX16(MEM16(edi + 2));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00042844; /* jl: less (signed <) */

loc_000426B6: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 9 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00042844; /* jg: greater (signed >) */

loc_000426BF: ;
    PUSH32(esp, 0x50);
    PUSH32(esp, 0x000426C6u); sub_0010F511(); /* call 0x0010F511 */

loc_000426C6: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042734; /* je: equal / zero */

loc_000426CD: ;
    ecx = eax;
    PUSH32(esp, 0x000426D4u); sub_00046700(); /* call 0x00046700 */

loc_000426D4: ;
    edi = eax;
    goto loc_00042736;

loc_000426D8: ;
    __debugbreak(); /* int3 */
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 0x20;
    esp += 4; return; /* ret */

loc_000426E3: ;
    edi = MEM32(esp + 0x14);
    eax = edi * 8 + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0x000426F4u); sub_0010F511(); /* call 0x0010F511 */

loc_000426F4: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042720; /* je: equal / zero */

loc_000426FB: ;
    PUSH32(esp, 0xC1410);
    PUSH32(esp, edi);
    esi = eax + 4;
    PUSH32(esp, 8);
    PUSH32(esp, esi);
    MEM32(eax) = edi;
    PUSH32(esp, 0x0004270Eu); sub_00012040(); /* call 0x00012040 */

loc_0004270E: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, esi);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x0004271Bu); sub_000423B0(); /* call 0x000423B0 */

loc_0004271B: ;
    goto loc_00042637;

loc_00042720: ;
    ecx = MEM32(esp + 0x10);
    esi = 0; /* xor self */
    PUSH32(esp, esi);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x0004272Fu); sub_000423B0(); /* call 0x000423B0 */

loc_0004272F: ;
    goto loc_00042637;

loc_00042734: ;
    edi = 0; /* xor self */

loc_00042736: ;
    ecx = MEM32(esi + 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042743; /* je: equal / zero */

loc_0004273D: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x00042743u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042743: ;
    eax = edi;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 4) = edi;
    if (TEST_Z(_fa, _fb)) goto loc_000427B2; /* je: equal / zero */

loc_0004274C: ;
    MEM32(eax + 4) = ebx;
    eax = MEM32(esi + 4);
    ecx = MEM32(esp + 0x10);
    MEM32(eax + 8) = ecx;
    edx = MEM32(esi + 4);
    eax = MEM32(ebp);
    MEM32(edx + 0xC) = eax;
    eax = MEM32(esp + 0x24);
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x14);
    eax = eax + 0x54;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00042777u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042777: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; sub_00042845(); return; } /* je: equal / zero */

loc_0004277F: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x28);
    MEM32(esi) = edx;
    esi = MEM32(esi + 4);
    edi = MEM32(esp + 0x10);
    eax = MEM32(esi);
    ecx = esi;
    edi = edi + 0x28;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x00042799u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042799: ;
    MEM32(edi) = MEM32(edi) + eax;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x28);
    ecx = ecx + 3;
    ecx = ecx & 0xFFFFFFFCu;
    MEM32(eax + 0x28) = ecx;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = MEM32(eax + 0x24) + 1;

loc_000427B2: ;
    eax = MEM32(esp + 0x24);
    edx = MEM32(esp + 0x20);
    ecx = MEM32(esp + 0x14);
    eax++;
    edx = edx + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    MEM32(esp + 0x24) = eax;
    MEM32(esp + 0x20) = edx;
    if (CMP_L(_fas, _fbs)) goto loc_00042650; /* jl: less (signed <) */

loc_000427D2: ;
    edx = MEM32(esp + 0x2C);
    eax = ZX16(MEM16(edx));
    eax = eax + eax * 2;
    eax = eax + eax + 4;
    ecx = eax;
    ecx = ecx & 3;
    if (0) goto loc_000427F0; /* jbe: below or equal (unsigned <=) */

loc_000427E7: ;
    esi = 4;
    esi = esi - ecx;
    eax = eax + esi;

loc_000427F0: ;
    edi = MEM32(esp + 0x10);
    esi = eax + edx + 0x3C;
    edx = eax + edx + 0x54;
    edi = edi + 0xA4;
    ecx = 6;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    eax = MEM32(esp + 0x10);
    ecx = MEM32(edx);
    eax = eax + 0x90;
    MEM32(eax) = ecx;
    ecx = MEM32(edx + 4);
    MEM32(eax + 4) = ecx;
    ecx = MEM32(edx + 8);
    MEM32(eax + 8) = ecx;
    edx = MEM32(edx + 0xC);
    MEM32(eax + 0xC) = edx;
    eax = MEM32(esp + 0x10);
    POP32(esp, edi);
    POP32(esp, esi);
    fp_push(MEMF(eax + 0x9C)); /* fld float */
    POP32(esp, ebp);
    fp_top() = sqrt(fp_top()); /* fsqrt */
    POP32(esp, ebx);
    MEMF(eax + 0xA0) = (float)fp_top(); fp_pop(); /* fstp */
    SET_LO8(eax, 1);
    esp = esp + 0x20;
    esp += 4; return; /* ret */

loc_00042844: ;
    __debugbreak(); /* int3 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00042845(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00042845: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 0x20;
    esp += 4; return; /* ret */

}

void sub_00042850(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00042850: ;
    esp = esp - 0x18;
    eax = MEM32(esp + 0x20);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0xC) = ecx;
    esi = MEM32(eax + 8);
    eax = MEM32(esp + 0x30);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    PUSH32(esp, edi);
    if (CMP_EQ(_fa, _fb)) goto loc_00042875; /* je: equal / zero */

loc_0004286C: ;
    edi = MEM32(eax + 8);
    MEM32(esp + 0x14) = edi;
    goto loc_0004287B;

loc_00042875: ;
    MEM32(esp + 0x14) = ebx;
    edi = ebx;

loc_0004287B: ;
    ecx = MEM32(esi + 4);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, 0x00042888u); sub_0003E880(); /* call 0x0003E880 */

loc_00042888: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042896; /* je: equal / zero */

loc_0004288C: ;
    ebp = ZX16(MEM16(edi + 2));
    MEM32(esp + 0x18) = ebp;
    goto loc_0004289C;

loc_00042896: ;
    MEM32(esp + 0x18) = ebx;
    ebp = ebx;

loc_0004289C: ;
    edx = MEM32(esp + 0x10);
    MEM32(edx + 0x28) = ebx;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = ebx;
    SET_LO16(eax, MEM16(esi + 2));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(LO16(ebx)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), LO16(ebx) (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042A92; /* je: equal / zero */

loc_000428B7: ;
    edi = ZX16(LO16(eax));
    edi = edi + ebp;
    ecx = edi * 8 + 4;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x000428C9u); sub_0010F511(); /* call 0x0010F511 */

loc_000428C9: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000428E3; /* je: equal / zero */

loc_000428D0: ;
    PUSH32(esp, 0xC1410);
    PUSH32(esp, edi);
    ebx = eax + 4;
    PUSH32(esp, 8);
    PUSH32(esp, ebx);
    MEM32(eax) = edi;
    PUSH32(esp, 0x000428E3u); sub_00012040(); /* call 0x00012040 */

loc_000428E3: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, ebx);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x000428F0u); sub_000423B0(); /* call 0x000423B0 */

loc_000428F0: ;
    edi = 0; /* xor self */
    _fa = (uint32_t)(MEM16(esi + 2)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 2), LO16(edi) (16-bit) */
    MEM32(esp + 0x1C) = edi;
    if (CMP_A(_fa, _fb)) goto loc_00042970; /* ja: above (unsigned >) */

loc_000428FC: ;
    edi = MEM32(esp + 0x14);
    ebx = 0; /* xor self */

loc_00042902: ;
    edx = 0; /* xor self */
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, ebx (32-bit) */
    MEM32(esp + 0x20) = edx;
    if (CMP_G(_fas, _fbs)) goto loc_00042AE3; /* jg: greater (signed >) */

loc_00042910: ;
    eax = MEM32(esp + 0x10);
    eax = eax + 0xA4;
    ecx = 0xBF000000u;
    MEM32(eax) = ecx;
    MEM32(eax + 4) = ecx;
    MEM32(eax + 8) = ecx;
    ecx = 0x3F000000;
    MEM32(eax + 0xC) = ecx;
    MEM32(eax + 0x10) = ecx;
    MEM32(eax + 0x14) = ecx;
    eax = MEM32(esp + 0x10);
    eax = eax + 0x90;
    MEM32(eax) = ebx;
    MEM32(eax + 4) = ebx;
    MEM32(eax + 8) = ebx;
    MEM32(eax + 0xC) = 0x3F800000;
    eax = MEM32(esp + 0x10);
    fp_push(MEMF(eax + 0x9C)); /* fld float */
    POP32(esp, edi);
    fp_top() = sqrt(fp_top()); /* fsqrt */
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    MEMF(eax + 0xA0) = (float)fp_top(); fp_pop(); /* fstp */
    SET_LO8(eax, 1);
    esp = esp + 0x18;
    esp += 16; return; /* ret 12 */

loc_0004296A: ;
    edi = MEM32(esp + 0x1C);
    edi = edi;

loc_00042970: ;
    eax = ZX16(MEM16(esi));
    ecx = MEM32(esp + 0x2C);
    edx = MEM32(ecx + 0x34);
    eax = eax + edi;
    eax = ZX16(MEM16(esi + eax * 2 + 0xC));
    eax = MEM32(edx + eax * 4 + 4);
    eax = eax + edx;
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0004298Fu); sub_0003EB70(); /* call 0x0003EB70 */

loc_0004298F: ;
    edx = ZX16(MEM16(esi + 2));
    ecx = MEM32(esp + 0x2C);
    ecx = MEM32(ecx + 0x34);
    ebx = eax;
    eax = ZX16(MEM16(esi));
    edi = edi + edx;
    eax = eax + edi;
    edx = ZX16(MEM16(esi + eax * 2 + 0xC));
    eax = MEM32(ecx + edx * 4 + 4);
    eax = eax + ecx;
    ecx = MEM32(ebx + 4);
    MEM32(esp + 0x24) = ecx;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x24);
    edi = MEM32(ecx + 0x20);
    ecx = MEM32(ecx + 0x1C);
    PUSH32(esp, eax);
    edi = edi + edx * 8;
    PUSH32(esp, 0x000429CBu); sub_00034C10(); /* call 0x00034C10 */

loc_000429CB: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042A74; /* je: equal / zero */

loc_000429D5: ;
    PUSH32(esp, 0x20);
    PUSH32(esp, 0x000429DCu); sub_0010F511(); /* call 0x0010F511 */

loc_000429DC: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000429F0; /* je: equal / zero */

loc_000429E3: ;
    ecx = eax;
    PUSH32(esp, 0x000429EAu); sub_00046B60(); /* call 0x00046B60 */

loc_000429EA: ;
    MEM32(esp + 0x20) = eax;
    goto loc_000429F8;

loc_000429F0: ;
    MEM32(esp + 0x20) = 0;

loc_000429F8: ;
    ecx = MEM32(edi + 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042A05; /* je: equal / zero */

loc_000429FF: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00042A05u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042A05: ;
    ecx = MEM32(esp + 0x20);
    eax = ecx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(edi + 4) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_00042A74; /* je: equal / zero */

loc_00042A12: ;
    edx = MEM32(esp + 0x24);
    MEM32(eax + 4) = edx;
    eax = MEM32(edi + 4);
    ecx = MEM32(esp + 0x10);
    MEM32(eax + 8) = ecx;
    edx = MEM32(edi + 4);
    eax = MEM32(ebp);
    MEM32(edx + 0xC) = eax;
    ecx = MEM32(edi + 4);
    eax = MEM32(esp + 0x2C);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00042A3Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042A3B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042C18; /* je: equal / zero */

loc_00042A43: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x28);
    ecx = MEM32(edi + 4);
    MEM32(edi) = edx;
    edi = MEM32(esp + 0x10);
    eax = MEM32(ecx);
    edi = edi + 0x28;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x00042A5Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042A5B: ;
    MEM32(edi) = MEM32(edi) + eax;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x28);
    ecx = ecx + 3;
    ecx = ecx & 0xFFFFFFFCu;
    MEM32(eax + 0x28) = ecx;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = MEM32(eax + 0x24) + 1;

loc_00042A74: ;
    eax = MEM32(esp + 0x1C);
    edx = ZX16(MEM16(esi + 2));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(esp + 0x1C) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_0004296A; /* jl: less (signed <) */

loc_00042A89: ;
    ebp = MEM32(esp + 0x18);
    goto loc_000428FC;

loc_00042A92: ;
    eax = ebp * 8 + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00042A9Fu); sub_0010F511(); /* call 0x0010F511 */

loc_00042A9F: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042ACB; /* je: equal / zero */

loc_00042AA6: ;
    PUSH32(esp, 0xC1410);
    PUSH32(esp, ebp);
    esi = eax + 4;
    PUSH32(esp, 8);
    PUSH32(esp, esi);
    MEM32(eax) = ebp;
    PUSH32(esp, 0x00042AB9u); sub_00012040(); /* call 0x00012040 */

loc_00042AB9: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, esi);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x00042AC6u); sub_000423B0(); /* call 0x000423B0 */

loc_00042AC6: ;
    goto loc_00042902;

loc_00042ACB: ;
    ecx = MEM32(esp + 0x10);
    esi = 0; /* xor self */
    PUSH32(esp, esi);
    ecx = ecx + 0x20;
    PUSH32(esp, 0x00042ADAu); sub_000423B0(); /* call 0x000423B0 */

loc_00042ADA: ;
    goto loc_00042902;

loc_00042ADF: ;
    edi = MEM32(esp + 0x14);

loc_00042AE3: ;
    esi = ZX16(MEM16(edi));
    ecx = MEM32(esp + 0x2C);
    eax = MEM32(ecx + 0x34);
    esi = esi + edx;
    edx = ZX16(MEM16(edi + esi * 2 + 0xC));
    edi = MEM32(eax + edx * 4 + 4);
    edi = edi + eax;
    PUSH32(esp, 0x12);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00042B02u); sub_0003EB70(); /* call 0x0003EB70 */

loc_00042B02: ;
    ebx = MEM32(eax + 8);
    MEM32(esp + 0x24) = eax;
    eax = ZX16(MEM16(ebx + 2));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00042BFF; /* jl: less (signed <) */

loc_00042B16: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 9 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00042BFF; /* jg: greater (signed >) */

loc_00042B1F: ;
    eax = MEM32(esp + 0x2C);
    edx = ZX16(MEM16(ebx + 8));
    ecx = MEM32(eax + 0x34);
    eax = MEM32(ecx + edx * 4 + 4);
    eax = eax + ecx;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x24);
    esi = MEM32(ecx + 0x20);
    ecx = MEM32(ecx + 0x1C);
    PUSH32(esp, eax);
    esi = esi + edx * 8;
    PUSH32(esp, 0x00042B46u); sub_00034C10(); /* call 0x00034C10 */

loc_00042B46: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042BFB; /* je: equal / zero */

loc_00042B50: ;
    eax = ZX16(MEM16(ebx + 2));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00042C17; /* jl: less (signed <) */

loc_00042B5D: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 9 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00042C17; /* jg: greater (signed >) */

loc_00042B66: ;
    PUSH32(esp, 0x50);
    PUSH32(esp, 0x00042B6Du); sub_0010F511(); /* call 0x0010F511 */

loc_00042B6D: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042B7F; /* je: equal / zero */

loc_00042B74: ;
    ecx = eax;
    PUSH32(esp, 0x00042B7Bu); sub_00046700(); /* call 0x00046700 */

loc_00042B7B: ;
    ebx = eax;
    goto loc_00042B81;

loc_00042B7F: ;
    ebx = 0; /* xor self */

loc_00042B81: ;
    ecx = MEM32(esi + 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042B8E; /* je: equal / zero */

loc_00042B88: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00042B8Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042B8E: ;
    eax = ebx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 4) = ebx;
    if (TEST_Z(_fa, _fb)) goto loc_00042BFB; /* je: equal / zero */

loc_00042B97: ;
    MEM32(eax + 4) = edi;
    ecx = MEM32(esi + 4);
    edx = MEM32(esp + 0x10);
    MEM32(ecx + 8) = edx;
    eax = MEM32(esi + 4);
    ecx = MEM32(ebp);
    MEM32(eax + 0xC) = ecx;
    eax = MEM32(esp + 0x14);
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x28);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x34);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00042BC4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042BC4: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042C18; /* je: equal / zero */

loc_00042BC8: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x28);
    MEM32(esi) = edx;
    esi = MEM32(esi + 4);
    edi = MEM32(esp + 0x10);
    eax = MEM32(esi);
    ecx = esi;
    edi = edi + 0x28;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x00042BE2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042BE2: ;
    MEM32(edi) = MEM32(edi) + eax;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x28);
    ecx = ecx + 3;
    ecx = ecx & 0xFFFFFFFCu;
    MEM32(eax + 0x28) = ecx;
    eax = MEM32(esp + 0x10);
    MEM32(eax + 0x24) = MEM32(eax + 0x24) + 1;

loc_00042BFB: ;
    ebp = MEM32(esp + 0x18);

loc_00042BFF: ;
    edx = MEM32(esp + 0x20);
    edx++;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ebp (32-bit) */
    MEM32(esp + 0x20) = edx;
    if (CMP_L(_fas, _fbs)) goto loc_00042ADF; /* jl: less (signed <) */

loc_00042C10: ;
    ebx = 0; /* xor self */
    goto loc_00042910;

loc_00042C17: ;
    __debugbreak(); /* int3 */

loc_00042C18: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 0x18;
    esp += 16; return; /* ret 12 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00042C60(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00042C60: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x80);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    PUSH32(esp, edi);
    if (CMP_EQ(_fa, _fb)) goto loc_00042C7B; /* je: equal / zero */

loc_00042C71: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042C7B; /* jne: not equal / not zero */

loc_00042C76: ;
    PUSH32(esp, 0x00042C7Bu); sub_0002E400(); /* call 0x0002E400 */

loc_00042C7B: ;
    ecx = MEM32(esi + 0x7C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042C8C; /* je: equal / zero */

loc_00042C82: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042C8C; /* jne: not equal / not zero */

loc_00042C87: ;
    PUSH32(esp, 0x00042C8Cu); sub_0002E400(); /* call 0x0002E400 */

loc_00042C8C: ;
    ecx = MEM32(esi + 0x78);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    edi = esi + 0x6C;
    if (CMP_EQ(_fa, _fb)) goto loc_00042CA4; /* je: equal / zero */

loc_00042C96: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x00042C9Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042C9C: ;
    MEM32(edi + 4) = ebx;
    MEM32(edi) = ebx;
    MEM32(edi + 0xC) = ebx;

loc_00042CA4: ;
    ecx = MEM32(esi + 0x50);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    edi = esi + 0x44;
    if (CMP_EQ(_fa, _fb)) goto loc_00042CBC; /* je: equal / zero */

loc_00042CAE: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00042CB4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00042CB4: ;
    MEM32(edi + 4) = ebx;
    MEM32(edi) = ebx;
    MEM32(edi + 0xC) = ebx;

loc_00042CBC: ;
    ecx = esi + 0x20;
    PUSH32(esp, 0x00042CC4u); sub_00042370(); /* call 0x00042370 */

loc_00042CC4: ;
    ecx = MEM32(esi + 0x1C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042CD5; /* je: equal / zero */

loc_00042CCB: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042CD5; /* jne: not equal / not zero */

loc_00042CD0: ;
    PUSH32(esp, 0x00042CD5u); sub_0002E400(); /* call 0x0002E400 */

loc_00042CD5: ;
    _fa = (uint32_t)(MEM8(esi + 8)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 8), 4 (8-bit) */
    MEM32(esi) = 0x1E175C;
    if (TEST_NZ(_fa, _fb)) goto loc_00042CED; /* jne: not equal / not zero */

loc_00042CE1: ;
    eax = MEM32(esi + 0x10);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00042CEAu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_00042CEA: ;
    esp = esp + 4;

loc_00042CED: ;
    POP32(esp, edi);
    MEM32(esi) = 0x1E1750;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

void sub_00042D00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00042D00: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    edi = esi + 0x44;
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    ecx = 0x418064;
    PUSH32(esp, 0x00042D17u); sub_00067DE0(); /* call 0x00067DE0 */

loc_00042D17: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042D1F: ;
    ecx = MEM32(edi);
    edx = MEM32(esi + 0x48);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    ecx = esi + 0x2C;
    PUSH32(esp, 0x00042D2Eu); sub_00044F40(); /* call 0x00044F40 */

loc_00042D2E: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042D36: ;
    eax = MEM32(esi + 0x38);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042D41: ;
    eax = MEM32(esi + 0x30);
    ecx = MEM32(esi + 0x34);
    PUSH32(esp, 0x14);
    MEM32(esi + 0x84) = eax;
    MEM32(esi + 0x88) = ecx;
    MEM32(esi + 0x8C) = 0;
    PUSH32(esp, 0x00042D64u); sub_0010F511(); /* call 0x0010F511 */

loc_00042D64: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042D76; /* je: equal / zero */

loc_00042D6B: ;
    ecx = eax;
    PUSH32(esp, 0x00042D72u); sub_00047690(); /* call 0x00047690 */

loc_00042D72: ;
    edi = eax;
    goto loc_00042D78;

loc_00042D76: ;
    edi = 0; /* xor self */

loc_00042D78: ;
    ecx = MEM32(esi + 0x7C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042D89; /* je: equal / zero */

loc_00042D7F: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042D89; /* jne: not equal / not zero */

loc_00042D84: ;
    PUSH32(esp, 0x00042D89u); sub_0002E400(); /* call 0x0002E400 */

loc_00042D89: ;
    MEM32(esi + 0x7C) = edi;
    eax = MEM32(esi + 0x34);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042DA3; /* je: equal / zero */

loc_00042D93: ;
    edx = MEM32(esi + 0x30);
    PUSH32(esp, edx);
    ecx = edi;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00042D9Fu); sub_000476B0(); /* call 0x000476B0 */

loc_00042D9F: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042DA3: ;
    eax = MEM32(esp + 0x10);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E16; /* je: equal / zero */

loc_00042DAB: ;
    edi = esi + 0x6C;
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    ecx = 0x418064;
    PUSH32(esp, 0x00042DBAu); sub_00067DE0(); /* call 0x00067DE0 */

loc_00042DBA: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042DBE: ;
    edx = MEM32(edi);
    eax = MEM32(esi + 0x70);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    ecx = esi + 0x54;
    PUSH32(esp, 0x00042DCDu); sub_00044F40(); /* call 0x00044F40 */

loc_00042DCD: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E0F; /* je: equal / zero */

loc_00042DD1: ;
    PUSH32(esp, 0x14);
    PUSH32(esp, 0x00042DD8u); sub_0010F511(); /* call 0x0010F511 */

loc_00042DD8: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042DE8; /* je: equal / zero */

loc_00042DDF: ;
    ecx = eax;
    PUSH32(esp, 0x00042DE6u); sub_00047690(); /* call 0x00047690 */

loc_00042DE6: ;
    goto loc_00042DEA;

loc_00042DE8: ;
    eax = 0; /* xor self */

loc_00042DEA: ;
    edi = esi + 0x80;
    PUSH32(esp, eax);
    ecx = edi;
    PUSH32(esp, 0x00042DF8u); sub_00042320(); /* call 0x00042320 */

loc_00042DF8: ;
    eax = MEM32(esi + 0x5C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E16; /* je: equal / zero */

loc_00042DFF: ;
    edx = MEM32(esi + 0x58);
    ecx = MEM32(edi);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00042E0Bu); sub_000476B0(); /* call 0x000476B0 */

loc_00042E0B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00042E16; /* jne: not equal / not zero */

loc_00042E0F: ;
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

loc_00042E16: ;
    ecx = esi;
    PUSH32(esp, 0x00042E1Du); sub_00042470(); /* call 0x00042470 */

loc_00042E1D: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

void sub_00042E30(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00042E30: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(eax + 8);
    eax = MEM32(edi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    esi = ecx;
    if (CMP_GE(_fas & _fbs, 0)) goto loc_00042E49; /* jge: greater or equal (signed >=) */

loc_00042E42: ;
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

loc_00042E49: ;
    ecx = MEM32(esp + 0xC);
    edx = MEM32(ecx + 0x34);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, 0x14);
    MEM32(esi + 0x84) = edx;
    MEM32(esi + 0x88) = 0;
    MEM32(esi + 0x8C) = edi;
    PUSH32(esp, 0x00042E6Fu); sub_0010F511(); /* call 0x0010F511 */

loc_00042E6F: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E81; /* je: equal / zero */

loc_00042E76: ;
    ecx = eax;
    PUSH32(esp, 0x00042E7Du); sub_00047690(); /* call 0x00047690 */

loc_00042E7D: ;
    ebx = eax;
    goto loc_00042E83;

loc_00042E81: ;
    ebx = 0; /* xor self */

loc_00042E83: ;
    ecx = MEM32(esi + 0x7C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042E94; /* je: equal / zero */

loc_00042E8A: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042E94; /* jne: not equal / not zero */

loc_00042E8F: ;
    PUSH32(esp, 0x00042E94u); sub_0002E400(); /* call 0x0002E400 */

loc_00042E94: ;
    MEM32(esi + 0x7C) = ebx;
    _fa = (uint32_t)(MEM16(edi)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(edi), 0 (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042EB9; /* je: equal / zero */

loc_00042E9D: ;
    eax = MEM32(esi + 0x84);
    PUSH32(esp, eax);
    ecx = ebx;
    PUSH32(esp, edi);
    PUSH32(esp, 0x00042EACu); sub_000477D0(); /* call 0x000477D0 */

loc_00042EAC: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00042EB9; /* jne: not equal / not zero */

loc_00042EB0: ;
    POP32(esp, ebp);
    POP32(esp, ebx);
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

loc_00042EB9: ;
    ebp = MEM32(esp + 0x1C);
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042F12; /* je: equal / zero */

loc_00042EC1: ;
    edi = MEM32(ebp + 8);
    PUSH32(esp, 0x14);
    PUSH32(esp, 0x00042ECBu); sub_0010F511(); /* call 0x0010F511 */

loc_00042ECB: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042EDD; /* je: equal / zero */

loc_00042ED2: ;
    ecx = eax;
    PUSH32(esp, 0x00042ED9u); sub_00047690(); /* call 0x00047690 */

loc_00042ED9: ;
    ebx = eax;
    goto loc_00042EDF;

loc_00042EDD: ;
    ebx = 0; /* xor self */

loc_00042EDF: ;
    ecx = MEM32(esi + 0x80);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042EF3; /* je: equal / zero */

loc_00042EE9: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00042EF3; /* jne: not equal / not zero */

loc_00042EEE: ;
    PUSH32(esp, 0x00042EF3u); sub_0002E400(); /* call 0x0002E400 */

loc_00042EF3: ;
    MEM32(esi + 0x80) = ebx;
    _fa = (uint32_t)(MEM16(edi)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(edi), 0 (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00042F12; /* je: equal / zero */

loc_00042EFF: ;
    edx = MEM32(esi + 0x84);
    PUSH32(esp, edx);
    ecx = ebx;
    PUSH32(esp, edi);
    PUSH32(esp, 0x00042F0Eu); sub_000477D0(); /* call 0x000477D0 */

loc_00042F0E: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00042EB0; /* je: equal / zero */

loc_00042F12: ;
    eax = MEM32(esp + 0x18);
    ecx = MEM32(esp + 0x14);
    PUSH32(esp, ebp);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = esi;
    PUSH32(esp, 0x00042F24u); sub_00042850(); /* call 0x00042850 */

loc_00042F24: ;
    POP32(esp, ebp);
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

}

void sub_00042F30(void)
{

loc_00042F30: ;
    edx = ZX16(MEM16(ecx + 0xA));
    eax = MEM32(esp + 4);
    eax = eax + eax * 2;
    edx = edx + eax * 4;
    eax = MEM32(ecx + 0xC);
    eax = eax + edx * 2 + 0x68;
    eax = eax + ecx;
    esp += 8; return; /* ret 4 */

}

void sub_00042F50(void)
{

loc_00042F50: ;
    eax = ZX16(MEM16(ecx + 6));
    edx = ZX16(MEM16(ecx + 0xA));
    eax = eax + eax * 2;
    edx = edx + eax * 4;
    eax = MEM32(esp + 4);
    eax = eax + eax * 8;
    edx = edx + eax * 2;
    eax = MEM32(ecx + 0xC);
    eax = eax + edx * 2 + 0x68;
    eax = eax + ecx;
    esp += 8; return; /* ret 4 */

}

void sub_00042F80(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00042F80: ;
    fp_push(MEMF(esp + 8)); /* fld float */
    esp = esp - 0x14;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00042FC7; /* jp: parity */

loc_00042F98: ;
    eax = ZX16(MEM16(esi + 0xA));
    ecx = MEM32(esi + 0xC);
    edi = MEM32(esp + 0x20);
    edx = ecx + eax * 2 + 0x68;
    edx = edx + esi;
    ecx = MEM32(edx);
    eax = edi + 0x24;
    MEM32(eax) = ecx;
    ecx = MEM32(edx + 4);
    MEM32(eax + 4) = ecx;
    edx = MEM32(edx + 8);
    MEM32(eax + 8) = edx;
    eax = 0; /* xor self */
    MEM32(esp + 0x24) = eax;
    goto loc_000430AD;

loc_00042FC7: ;
    fp_push(MEMF(esp + 0x24)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E16FC)); fp_pop(); /* fcomp dword ptr [0x1e16fc] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    eax = ZX16(MEM16(esi + 6));
    if (TEST_NZ(_fa, _fb)) goto loc_00043036; /* jne: not equal / not zero */

loc_00042FDC: ;
    ecx = ZX16(MEM16(esi + 0xA));
    edi = MEM32(esp + 0x20);
    eax = eax + eax * 2;
    edx = ecx + eax * 4;
    eax = MEM32(esi + 0xC);
    eax = eax + edx * 2 + 0x50;
    eax = eax + esi;
    ecx = edi + 0x24;
    MEM32(esp + 0x24) = 0x3F800000;
    fp_push(MEMF(eax)); /* fld float */
    fp_top() = fp_top() + MEMF(eax + 0xC); /* fadd dword ptr [eax + 0xc] */
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    edx = MEM32(esp + 0xC);
    fp_push(MEMF(eax + 0x10)); /* fld float */
    fp_top() = fp_top() + MEMF(eax + 4); /* fadd dword ptr [eax + 4] */
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(eax + 0x14)); /* fld float */
    fp_top() = fp_top() + MEMF(eax + 8); /* fadd dword ptr [eax + 8] */
    eax = MEM32(esp + 0x10);
    MEM32(ecx) = edx;
    MEM32(ecx + 4) = eax;
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    edx = MEM32(esp + 0x14);
    MEM32(ecx + 8) = edx;
    eax = ZX16(MEM16(esi + 8));
    eax--;
    goto loc_000430AD;

loc_00043036: ;
    MEM32(esp + 8) = eax;
    fp_push((double)SMEM32(esp + 8)); /* fild */
    fp_top() = fp_top() * MEMF(esp + 0x24); /* fmul dword ptr [esp + 0x24] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    PUSH32(esp, 0x00043049u); sub_0010F038(); /* call 0x0010F038 */

loc_00043049: ;
    edx = ZX16(MEM16(esi + 0xA));
    edi = MEM32(esp + 0x20);
    MEM32(esp + 8) = eax;
    ecx = eax + eax * 2;
    eax = edx + ecx * 4;
    fp_top() = fp_top() - (double)SMEM32(esp + 8); /* fisub dword ptr [esp + 8] */
    ecx = MEM32(esi + 0xC);
    eax = ecx + eax * 2 + 0x68;
    eax = eax + esi;
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * MEMF(eax + 0xC); /* fmul dword ptr [eax + 0xc] */
    fp_top() = fp_top() + MEMF(eax); /* fadd dword ptr [eax] */
    MEMF(edi + 0x24) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * MEMF(eax + 0x10); /* fmul dword ptr [eax + 0x10] */
    fp_top() = fp_top() + MEMF(eax + 4); /* fadd dword ptr [eax + 4] */
    MEMF(edi + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = fp_top() * MEMF(eax + 0x14); /* fmul dword ptr [eax + 0x14] */
    fp_top() = fp_top() + MEMF(eax + 8); /* fadd dword ptr [eax + 8] */
    MEMF(edi + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    edx = ZX16(MEM16(esi + 8));
    MEM32(esp + 0x20) = edx;
    fp_push((double)SMEM32(esp + 0x20)); /* fild */
    fp_top() = fp_top() * MEMF(esp + 0x24); /* fmul dword ptr [esp + 0x24] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    PUSH32(esp, 0x0004309Du); sub_0010F038(); /* call 0x0010F038 */

loc_0004309D: ;
    MEM32(esp + 0x24) = eax;
    fp_push((double)SMEM32(esp + 0x24)); /* fild */
    fp_top() = fp_st1() - fp_top(); /* fsubr st(1) */
    MEMF(esp + 0x24) = (float)fp_top(); fp_pop(); /* fstp */
    fp_pop(); /* fstp st(0) */

loc_000430AD: ;
    edx = MEM32(esp + 0x24);
    ecx = esp + 0xC;
    PUSH32(esp, ecx);
    ecx = ZX16(MEM16(esi + 6));
    PUSH32(esp, edx);
    edx = eax + eax * 8;
    ecx = ecx + ecx * 2;
    edx = edx << 1;
    eax = edx + ecx * 4;
    ecx = ZX16(MEM16(esi + 0xA));
    edx = MEM32(esi + 0xC);
    eax = eax + ecx;
    ecx = edx + eax * 2 + 0x68;
    ecx = ecx + esi;
    PUSH32(esp, 0x000430DAu); sub_00033A60(); /* call 0x00033A60 */

loc_000430DA: ;
    PUSH32(esp, edi);
    ecx = esp + 0x10;
    PUSH32(esp, 0x000430E4u); sub_0006A9E0(); /* call 0x0006A9E0 */

loc_000430E4: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x14;
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00043120(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00043120: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp & 0xFFFFFFF8u;
    esp = esp - 0x50;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = ecx;
    edx--;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    MEM32(esp + 0x14) = ebp;
    if (CMP_B(_fa, _fb)) goto loc_000431A5; /* jb: below (unsigned <) */

loc_00043139: ;
    ebx = edx;
    ebx = (uint32_t)((int32_t)ebx * (int32_t)0x44);
    ebx = ebx + ebp;

loc_00043140: ;
    esi = 1;
    eax = 0; /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, esi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00043172; /* jb: below (unsigned <) */

loc_0004314B: ;
    MEM32(esp + 0x10) = eax;
    ecx = 0x44;

loc_00043154: ;
    edi = MEM32(esp + 0x10);
    edi = MEM32(edi + ebp);
    ebp = MEM32(esp + 0x14);
    edi = edi - MEM32(ecx + ebp);
    if (((int32_t)edi >= 0)) goto loc_0004316A; /* jns: not sign (positive) */

loc_00043164: ;
    eax = esi;
    MEM32(esp + 0x10) = ecx;

loc_0004316A: ;
    esi++;
    ecx = ecx + 0x44;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00043154; /* jbe: below or equal (unsigned <=) */

loc_00043172: ;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    eax = eax + ebp;
    ecx = 0x11;
    esi = eax;
    edi = esp + 0x18;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = ebx;
    ecx = 0x11;
    edi = eax;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    edi = ebx;
    edx--;
    ecx = 0x11;
    esi = esp + 0x18;
    ebx = ebx - 0x44;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    if (CMP_AE(_fa, _fb)) goto loc_00043140; /* jae: above or equal (unsigned >=) */

loc_000431A5: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 4; return; /* ret */

}

void sub_000431B0(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000431B0: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp & 0xFFFFFFF8u;
    esp = esp - 0x150;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x14) = ecx;
    if (CMP_BE(_fa, _fb)) goto loc_000433A8; /* jbe: below or equal (unsigned <=) */

loc_000431CD: ;
    ebp = 0; /* xor self */
    MEM32(esp + 0x20) = ebp;
    ebx = edx + -1;
    MEM32(esp + 0x1C) = ebp;

loc_000431DA: ;
    MEM32(esp + 0x18) = ebx;
    edi = edi;

loc_000431E0: ;
    eax = ebx;
    eax = eax - ebp;
    edx = eax + 1;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(8) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 8 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00043228; /* ja: above (unsigned >) */

loc_000431EC: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00043201; /* jbe: below or equal (unsigned <=) */

loc_000431F1: ;
    eax = MEM32(esp + 0x14);
    ecx = ebp;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x44);
    ecx = ecx + eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043201u); sub_00043120(); /* call 0x00043120 */

loc_00043201: ;
    eax = MEM32(esp + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000433A8; /* je: equal / zero */

loc_0004320D: ;
    ecx = MEM32(esp + eax * 8 + 0x68);
    edx = MEM32(esp + eax * 8 + 0x6C);
    eax--;
    MEM32(esp + 0x20) = eax;
    MEM32(esp + 0x18) = ecx;
    MEM32(esp + 0x1C) = edx;
    ebx = ecx;
    ebp = edx;
    goto loc_000431E0;

loc_00043228: ;
    ecx = MEM32(esp + 0x14);
    eax = ebp;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    edx = eax + ecx;
    eax = ebx + ebp;
    eax = eax >> 1;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    eax = eax + ecx;
    esi = eax;
    ecx = 0x11;
    edi = esp + 0x28;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    edi = eax;
    ecx = 0x11;
    esi = edx;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    eax = ebp + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    ecx = 0x11;
    esi = esp + 0x28;
    edi = edx;
    MEM32(esp + 0x24) = edx;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ebp = ebx;
    if (CMP_A(_fa, _fb)) goto loc_00043320; /* ja: above (unsigned >) */

loc_00043274: ;
    esi = MEM32(esp + 0x14);
    ecx = eax;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x44);
    esi = esi + ecx;
    ecx = MEM32(edx);
    edi = ecx;
    edi = edi - MEM32(esi);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000432A0; /* jle: less or equal (signed <=) */

loc_00043289: ;
    /* nop */

loc_00043290: ;
    eax++;
    esi = esi + 0x44;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_000432A0; /* ja: above (unsigned >) */

loc_00043298: ;
    edi = ecx;
    edi = edi - MEM32(esi);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (CMP_G(_fas & _fbs, 0)) goto loc_00043290; /* jg: greater (signed >) */

loc_000432A0: ;
    edi = MEM32(esp + 0x14);
    esi = ebp;
    esi = (uint32_t)((int32_t)esi * (int32_t)0x44);
    esi = esi + edi;
    edi = ecx;
    edi = edi - MEM32(esi);
    if (((int32_t)edi >= 0)) goto loc_000432C4; /* jns: not sign (positive) */

loc_000432B1: ;
    edx = esi;

loc_000432B3: ;
    edi = MEM32(edx + -68);
    edx = edx - 0x44;
    esi = ecx;
    ebp--;
    esi = esi - edi;
    if (((int32_t)esi < 0)) goto loc_000432B3; /* js: sign (negative) */

loc_000432C0: ;
    edx = MEM32(esp + 0x24);

loc_000432C4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00043317; /* jae: above or equal (unsigned >=) */

loc_000432C8: ;
    ebx = MEM32(esp + 0x14);
    edi = MEM32(esp + 0x14);
    edx = ebp;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x44);
    edx = edx + ebx;
    ebx = eax;
    ebx = (uint32_t)((int32_t)ebx * (int32_t)0x44);
    ebx = ebx + edi;
    esi = ebx;
    ecx = 0x11;
    edi = esp + 0x28;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = edx;
    edi = ebx;
    ebx = MEM32(esp + 0x18);
    ecx = 0x11;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    eax++;
    edi = edx;
    edx = MEM32(esp + 0x24);
    ebp--;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    ecx = 0x11;
    esi = esp + 0x28;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    if (CMP_BE(_fa, _fb)) goto loc_00043274; /* jbe: below or equal (unsigned <=) */

loc_00043315: ;
    goto loc_0004331C;

loc_00043317: ;
    if (CMP_A(_fa, _fb)) goto loc_0004331C; /* ja: above (unsigned >) */

loc_00043319: ;
    eax = ebp + 1;

loc_0004331C: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0004335A; /* jbe: below or equal (unsigned <=) */

loc_00043320: ;
    ecx = MEM32(esp + 0x14);
    ebp = MEM32(esp + 0x1C);
    eax = ebx;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    eax = eax + ecx;
    ecx = 0x11;
    esi = edx;
    edi = esp + 0x28;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = 0x11;
    esi = eax;
    edi = edx;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = 0x11;
    esi = esp + 0x28;
    edi = eax;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ebx--;
    goto loc_000431DA;

loc_0004335A: ;
    edx = MEM32(esp + 0x1C);
    ecx = ebx;
    esi = eax;
    ecx = ecx - ebp;
    esi = esi - edx;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, ecx (32-bit) */
    ecx = MEM32(esp + 0x20);
    if (CMP_AE(_fa, _fb)) goto loc_0004338A; /* jae: above or equal (unsigned >=) */

loc_0004336E: ;
    MEM32(esp + ecx * 8 + 0x74) = eax;
    eax = ecx;
    MEM32(esp + ecx * 8 + 0x70) = ebx;
    eax++;
    MEM32(esp + 0x18) = ebp;
    ebx = ebp;
    MEM32(esp + 0x20) = eax;
    ebp = edx;
    goto loc_000431E0;

loc_0004338A: ;
    MEM32(esp + 0x1C) = eax;
    eax = MEM32(esp + 0x20);
    eax++;
    MEM32(esp + ecx * 8 + 0x70) = ebp;
    ebp = MEM32(esp + 0x1C);
    MEM32(esp + ecx * 8 + 0x74) = edx;
    MEM32(esp + 0x20) = eax;
    goto loc_000431E0;

loc_000433A8: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 4; return; /* ret */

}

void sub_000433B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000433B0: ;
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    edi = ecx;
    eax = MEM32(edi + 8);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000433EC; /* jle: less or equal (signed <=) */

loc_000433BD: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ebx = 0; /* xor self */

loc_000433C1: ;
    esi = MEM32(edi);
    ecx = MEM32(esi + ebx + 0x34);
    esi = esi + ebx;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000433D7; /* je: equal / zero */

loc_000433CD: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_000433D7; /* jne: not equal / not zero */

loc_000433D2: ;
    PUSH32(esp, 0x000433D7u); sub_0002E400(); /* call 0x0002E400 */

loc_000433D7: ;
    ecx = esi + 8;
    PUSH32(esp, 0x000433DFu); sub_00045C40(); /* call 0x00045C40 */

loc_000433DF: ;
    eax = MEM32(edi + 8);
    ebp++;
    ebx = ebx + 0x44;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000433C1; /* jl: less (signed <) */

loc_000433EA: ;
    POP32(esp, esi);
    POP32(esp, ebx);

loc_000433EC: ;
    eax = MEM32(edi);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000433F4u); sub_0010F1CD(); /* call 0x0010F1CD */

loc_000433F4: ;
    esp = esp + 4;
    POP32(esp, edi);
    POP32(esp, ebp);
    esp += 4; return; /* ret */

}

void sub_00043400(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043400: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 4)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, MEM32(esi + 4) (32-bit) */
    PUSH32(esp, edi);
    if (CMP_L(_fas, _fbs)) goto loc_0004342B; /* jl: less (signed <) */

loc_0004340F: ;
    ecx = MEM32(esi);
    edi = ebx + 3;
    edi = edi & 0xFFFFFFFCu;
    eax = edi;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x00043423u); sub_0010FF6F(); /* call 0x0010FF6F */

loc_00043423: ;
    esp = esp + 8;
    MEM32(esi) = eax;
    MEM32(esi + 4) = edi;

loc_0004342B: ;
    eax = MEM32(esi + 8);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00043467; /* jge: greater or equal (signed >=) */

loc_00043434: ;
    ecx = 0x1E5D1C;
    /* nop */

loc_00043440: ;
    eax = MEM32(esi + 8);
    edx = MEM32(esi);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    eax = eax + edx;
    if ((eax == 0)) goto loc_00043458; /* je: equal / zero */

loc_0004344C: ;
    MEM32(eax + 0xC) = ebp;
    MEM32(eax + 0x10) = ebp;
    MEM32(eax + 8) = ecx;
    MEM32(eax + 0x34) = ebp;

loc_00043458: ;
    edx = MEM32(esi + 8);
    edx++;
    eax = edx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM32(esi + 8) = edx;
    if (CMP_L(_fas, _fbs)) goto loc_00043440; /* jl: less (signed <) */

loc_00043465: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */

loc_00043467: ;
    if (CMP_LE(_fas, _fbs)) goto loc_000434A0; /* jle: less or equal (signed <=) */

loc_00043469: ;
    /* nop */

loc_00043470: ;
    edx = MEM32(esi + 8);
    ecx = MEM32(esi);
    edx--;
    eax = edx;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x44);
    eax = eax + ecx;
    edi = eax;
    MEM32(esi + 8) = edx;
    ecx = MEM32(edi + 0x34);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebp (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00043493; /* je: equal / zero */

loc_00043489: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00043493; /* jne: not equal / not zero */

loc_0004348E: ;
    PUSH32(esp, 0x00043493u); sub_0002E400(); /* call 0x0002E400 */

loc_00043493: ;
    ecx = edi + 8;
    PUSH32(esp, 0x0004349Bu); sub_00045C40(); /* call 0x00045C40 */

loc_0004349B: ;
    _fa = (uint32_t)(MEM32(esi + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 8), ebx (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00043470; /* jg: greater (signed >) */

loc_000434A0: ;
    POP32(esp, edi);
    MEM32(esi + 8) = ebx;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

void sub_000434B0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000434B0: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    esi = edi + 0x54;
    MEM32(edi) = 0x1EABA0;
    ecx = MEM32(esi + 0xC);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000434DE; /* je: equal / zero */

loc_000434C4: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x000434CAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000434CA: ;
    MEM32(esi + 4) = 0;
    MEM32(esi) = 0;
    MEM32(esi + 0xC) = 0;

loc_000434DE: ;
    ecx = edi + 0x48;
    PUSH32(esp, 0x000434E6u); sub_000433B0(); /* call 0x000433B0 */

loc_000434E6: ;
    ecx = edi + 0x44;
    PUSH32(esp, 0x000434EEu); sub_00040D70(); /* call 0x00040D70 */

loc_000434EE: ;
    _fa = (uint32_t)(MEM8(edi + 8)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 8), 4 (8-bit) */
    MEM32(edi) = 0x1E175C;
    if (TEST_NZ(_fa, _fb)) goto loc_00043506; /* jne: not equal / not zero */

loc_000434FA: ;
    ecx = MEM32(edi + 0x10);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x00043503u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_00043503: ;
    esp = esp + 4;

loc_00043506: ;
    MEM32(edi) = 0x1E1750;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

void sub_00043510(void)
{

loc_00043510: ;
    eax = 0; /* xor self */
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi + 0x10) = eax;
    MEM32(esi + 0x14) = eax;
    MEM32(esi) = 0x1EABA0;
    ecx = 1;
    MEM32(esi + 4) = ecx;
    MEM32(esi + 8) = ecx;
    MEM32(esi + 0x44) = eax;
    MEM32(esi + 0x48) = eax;
    MEM32(esi + 0x4C) = eax;
    MEM32(esi + 0x50) = eax;
    ecx = esi + 0x64;
    MEM32(esi + 0x58) = eax;
    MEM32(esi + 0x54) = eax;
    MEM32(esi + 0x60) = eax;
    PUSH32(esp, 0x00043549u); sub_00044F20(); /* call 0x00044F20 */

loc_00043549: ;
    eax = esi;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

void sub_00043580(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043580: ;
    esp = esp - 0x1C;
    eax = MEM32(ecx + 0x78);
    edx = MEM32(esp + 0x20);
    PUSH32(esp, ebp);
    ebp = MEM32(eax + edx * 4 + 2);
    ebp = ebp + eax;
    eax = ZX16(MEM16(ebp + 2));
    eax--;
    MEM32(esp + 8) = ecx;
    if ((eax == 0)) goto loc_000435A5; /* je: equal / zero */

loc_0004359C: ;
    SET_LO8(eax, 1);
    POP32(esp, ebp);
    esp = esp + 0x1C;
    esp += 12; return; /* ret 8 */

loc_000435A5: ;
    eax = MEM32(ebp + 0x34);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x18) = 0;
    if (CMP_BE(_fa & _fb, 0)) goto loc_000436A6; /* jbe: below or equal (unsigned <=) */

loc_000435BB: ;
    eax = ebp + 0x38;
    MEM32(esp + 0x10) = eax;

loc_000435C2: ;
    edx = MEM32(esp + 0x10);
    edi = MEM32(edx);
    edi = edi + ebp;
    _fa = (uint32_t)(MEM16(edi)) & 0xFFFFu; _fb = (uint32_t)(0xFFFF) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(edi), 0xFFFF (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00043687; /* je: equal / zero */

loc_000435D5: ;
    eax = MEM32(ecx + 0x50);
    esi = ecx + 0x48;
    eax++;
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x000435E4u); sub_00043400(); /* call 0x00043400 */

loc_000435E4: ;
    ecx = MEM32(esi + 8);
    edx = MEM32(esi);
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x44);
    eax = ZX16(MEM16(edi));
    esi = ecx + edx + -68;
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, 0x58);
    MEM32(esi) = eax;
    MEM32(esi + 4) = ecx;
    PUSH32(esp, 0x00043603u); sub_0010F511(); /* call 0x0010F511 */

loc_00043603: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043615; /* je: equal / zero */

loc_0004360A: ;
    ecx = eax;
    PUSH32(esp, 0x00043611u); sub_000481F0(); /* call 0x000481F0 */

loc_00043611: ;
    ebx = eax;
    goto loc_00043617;

loc_00043615: ;
    ebx = 0; /* xor self */

loc_00043617: ;
    ecx = MEM32(esi + 0x34);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043628; /* je: equal / zero */

loc_0004361E: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00043628; /* jne: not equal / not zero */

loc_00043623: ;
    PUSH32(esp, 0x00043628u); sub_0002E400(); /* call 0x0002E400 */

loc_00043628: ;
    edx = MEM32(esp + 0x34);
    PUSH32(esp, edx);
    PUSH32(esp, edi);
    ecx = ebx;
    MEM32(esi + 0x34) = ebx;
    PUSH32(esp, 0x00043638u); sub_0004C970(); /* call 0x0004C970 */

loc_00043638: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000436B2; /* je: equal / zero */

loc_0004363C: ;
    edx = MEM32(esp + 0x14);
    ecx = MEM32(esi);
    edx = MEM32(edx + 0x44);
    ecx = MEM32(edx + ecx * 4);
    eax = MEM32(esi + 8);
    edi = esi + 8;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = edi;
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00043654u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043654: ;
    eax = MEM32(esi + 0x34);
    edx = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x0004365Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004365F: ;
    ecx = MEM32(esi + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x1C;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x0004366Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004366C: ;
    ecx = MEM32(esp + 0x1C);
    esi = esi + 0x38;
    MEM32(esi) = ecx;
    edx = MEM32(esp + 0x20);
    ecx = MEM32(esp + 0x14);
    MEM32(esi + 4) = edx;
    eax = MEM32(esp + 0x24);
    MEM32(esi + 8) = eax;

loc_00043687: ;
    eax = MEM32(esp + 0x18);
    esi = MEM32(esp + 0x10);
    edx = MEM32(ebp + 0x34);
    eax++;
    esi = esi + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(esp + 0x18) = eax;
    MEM32(esp + 0x10) = esi;
    if (CMP_B(_fa, _fb)) goto loc_000435C2; /* jb: below (unsigned <) */

loc_000436A6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    SET_LO8(eax, 1);
    POP32(esp, ebp);
    esp = esp + 0x1C;
    esp += 12; return; /* ret 8 */

loc_000436B2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x1C;
    esp += 12; return; /* ret 8 */

}

void sub_000436C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000436C0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    ebx = MEM32(edi + 0x78);
    esi = 0; /* xor self */
    _fa = (uint32_t)(MEM16(ebx)) & 0xFFFFu; _fb = (uint32_t)(LO16(esi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(ebx), LO16(esi) (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_000436E6; /* jbe: below or equal (unsigned <=) */

loc_000436CF: ;
    /* nop */

loc_000436D0: ;
    PUSH32(esp, 0);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x000436DAu); sub_00043580(); /* call 0x00043580 */

loc_000436DA: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000436EC; /* je: equal / zero */

loc_000436DE: ;
    eax = ZX16(MEM16(ebx));
    esi++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_000436D0; /* jb: below (unsigned <) */

loc_000436E6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_000436EC: ;
    POP32(esp, edi);
    POP32(esp, esi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

void sub_00043700(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00043700: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x40;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ecx + 0x70);
    eax = ZX16(MEM16(edi + 2));
    eax = (uint32_t)((int32_t)eax * (int32_t)0x38);
    MEM32(ebp + -16) = ecx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004371Bu); sub_0010F4D0(); /* call 0x0010F4D0 */

loc_0004371B: ;
    ecx = ZX16(MEM16(edi));
    ecx = ecx + ecx * 2;
    ecx = ecx + ecx + 4;
    eax = 0; /* xor self */
    edx = ecx;
    edx = edx & 3;
    esi = esp;
    MEM32(ebp + -4) = eax;
    if (0) goto loc_0004373C; /* jbe: below or equal (unsigned <=) */

loc_00043733: ;
    ebx = 4;
    ebx = ebx - edx;
    ecx = ecx + ebx;

loc_0004373C: ;
    ecx = ecx + edi;
    MEM32(esi) = ecx;
    ecx = 0x3F800000;
    MEM32(esi + 0x24) = ecx;
    MEM32(esi + 0x14) = ecx;
    MEM32(esi + 4) = ecx;
    MEM32(esi + 0xC) = eax;
    MEM32(esi + 8) = eax;
    MEM32(esi + 0x18) = eax;
    MEM32(esi + 0x10) = eax;
    MEM32(esi + 0x20) = eax;
    MEM32(esi + 0x1C) = eax;
    MEM32(esi + 0x28) = eax;
    MEM32(esi + 0x2C) = eax;
    MEM32(esi + 0x30) = eax;
    MEM32(esi + 0x34) = 0xFFFFFFFFu;
    ecx = ZX16(MEM16(edi));
    edx = ecx + ecx * 2;
    edx = edx + edx + 4;
    ecx = edx;
    ecx = ecx & 3;
    if (0) goto loc_0004378A; /* jbe: below or equal (unsigned <=) */

loc_00043781: ;
    ebx = 4;
    ebx = ebx - ecx;
    edx = edx + ebx;

loc_0004378A: ;
    ecx = edx + edi;
    edx = ZX16(MEM16(ecx + 8));
    edi = edx + edx * 8;
    edx = ZX16(MEM16(ecx + 6));
    edx = edx + edx * 2;
    edx = edx << 2;
    edx = edx + edi * 2;
    edi = ZX16(MEM16(ecx + 0xA));
    edx = edx + edi;
    edi = MEM32(ecx + 0xC);
    ebx = edi + edx * 2 + 0x68;
    edx = ebx;
    edx = edx & 0x80000001u;
    if (((int32_t)edx >= 0)) goto loc_000437BD; /* jns: not sign (positive) */

loc_000437B8: ;
    edx--;
    edx = edx | 0xFFFFFFFEu;
    edx++;

loc_000437BD: ;
    if (_flags /* je: equal / zero */) goto loc_000437C2;

loc_000437BF: ;
    ebx = ebx + 2;

loc_000437C2: ;
    ebx = ebx + ecx;
    edi = 0; /* xor self */

loc_000437C6: ;
    _fa = (uint32_t)(MEM32(edi + esi + 0x34)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edi + esi + 0x34), eax (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00043821; /* jge: greater or equal (signed >=) */

loc_000437CC: ;
    ecx = MEM32(edi + esi);
    _fa = (uint32_t)(MEM16(ecx + 0xA)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(ecx + 0xA), LO16(eax) (16-bit) */
    MEM32(ebp + -12) = eax;
    if (CMP_BE(_fa, _fb)) goto loc_0004381D; /* jbe: below or equal (unsigned <=) */

loc_000437D8: ;
    MEM32(ebp + -8) = 0x68;
    /* nop */

loc_000437E0: ;
    edx = MEM32(edi + esi);
    eax = edi + esi + 4;
    PUSH32(esp, eax);
    eax = MEM32(ebp + -8);
    ecx = ZX16(MEM16(eax + edx));
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + -16);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x000437F8u); sub_00043580(); /* call 0x00043580 */

loc_000437F8: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000438C0; /* je: equal / zero */

loc_00043800: ;
    ecx = MEM32(ebp + -8);
    edx = MEM32(edi + esi);
    eax = MEM32(ebp + -12);
    ecx = ecx + 2;
    MEM32(ebp + -8) = ecx;
    ecx = ZX16(MEM16(edx + 0xA));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    MEM32(ebp + -12) = eax;
    if (CMP_B(_fa, _fb)) goto loc_000437E0; /* jb: below (unsigned <) */

loc_0004381B: ;
    eax = 0; /* xor self */

loc_0004381D: ;
    MEM32(edi + esi + 0x34) = eax;

loc_00043821: ;
    edx = MEM32(edi + esi);
    ecx = ZX16(MEM16(edx + 2));
    _fa = (uint32_t)(MEM32(edi + esi + 0x34)) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edi + esi + 0x34), ecx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00043836; /* jne: not equal / not zero */

loc_0004382E: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;
    edi = edi - 0x38;
    goto loc_000438AB;

loc_00043836: ;
    PUSH32(esp, eax);
    edx = ebp + -64;
    PUSH32(esp, edx);
    ecx = ebx;
    MEM32(edi + esi + 0x6C) = 0xFFFFFFFFu;
    MEM32(edi + esi + 0x38) = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004384Eu); sub_00042F80(); /* call 0x00042F80 */

loc_0004384E: ;
    eax = edi + esi + 0x3C;
    PUSH32(esp, eax);
    edx = edi + esi + 4;
    ecx = ebp + -64;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004385Fu); sub_00018FA0(); /* call 0x00018FA0 */

loc_0004385F: ;
    edx = MEM32(edi + esi + 0x34);
    ecx = MEM32(ebp + -4);
    edx++;
    MEM32(edi + esi + 0x34) = edx;
    eax = ZX16(MEM16(ebx + 8));
    edx = eax + eax * 8;
    eax = ZX16(MEM16(ebx + 6));
    ecx++;
    eax = eax + eax * 2;
    eax = eax << 2;
    MEM32(ebp + -4) = ecx;
    ecx = eax + edx * 2;
    edx = ZX16(MEM16(ebx + 0xA));
    eax = MEM32(ebx + 0xC);
    ecx = ecx + edx;
    eax = eax + ecx * 2 + 0x68;
    ecx = eax;
    edi = edi + 0x38;
    ecx = ecx & 0x80000001u;
    if (((int32_t)ecx >= 0)) goto loc_000438A2; /* jns: not sign (positive) */

loc_0004389D: ;
    ecx--;
    ecx = ecx | 0xFFFFFFFEu;
    ecx++;

loc_000438A2: ;
    if (_flags /* je: equal / zero */) goto loc_000438A7;

loc_000438A4: ;
    eax = eax + 2;

loc_000438A7: ;
    ebx = ebx + eax;
    eax = 0; /* xor self */

loc_000438AB: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), eax (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_000437C6; /* jge: greater or equal (signed >=) */

loc_000438B4: ;
    SET_LO8(eax, 1);
    esp = ebp + -76;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 4; return; /* ret */

loc_000438C0: ;
    SET_LO8(eax, 0); /* xor self */
    esp = ebp + -76;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 4; return; /* ret */

}

void sub_000438D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000438D0: ;
    esp = esp - 0x30;
    eax = MEM32(esp + 0x34);
    MEM32(esp) = ecx;
    ecx = ecx + 0x54;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    ecx = 0x418064;
    PUSH32(esp, 0x000438EAu); sub_00067E50(); /* call 0x00067E50 */

loc_000438EA: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043917; /* je: equal / zero */

loc_000438EE: ;
    eax = MEM32(esp);
    ecx = MEM32(eax + 0x54);
    edx = MEM32(eax + 0x58);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    ecx = eax + 0x64;
    PUSH32(esp, 0x00043902u); sub_00044F40(); /* call 0x00044F40 */

loc_00043902: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043917; /* je: equal / zero */

loc_00043906: ;
    eax = MEM32(esp);
    ecx = MEM32(eax + 0x78);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043917; /* je: equal / zero */

loc_00043911: ;
    _fa = (uint32_t)(MEM16(ecx)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(ecx), 0 (16-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0004391F; /* jne: not equal / not zero */

loc_00043917: ;
    SET_LO8(eax, 0); /* xor self */
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

loc_0004391F: ;
    ecx = MEM32(eax + 0x68);
    PUSH32(esp, ebx);
    ebx = MEM32(eax + 0x6C);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x14) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_000439C1; /* je: equal / zero */

loc_00043935: ;
    esi = ZX16(MEM16(ebx));
    edx = esi * 4 + 4;
    PUSH32(esp, edx);
    PUSH32(esp, 0x00043945u); sub_0010F511(); /* call 0x0010F511 */

loc_00043945: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043961; /* je: equal / zero */

loc_0004394C: ;
    PUSH32(esp, 0x23060);
    PUSH32(esp, esi);
    edi = eax + 4;
    PUSH32(esp, 4);
    PUSH32(esp, edi);
    MEM32(eax) = esi;
    PUSH32(esp, 0x0004395Fu); sub_00012040(); /* call 0x00012040 */

loc_0004395F: ;
    goto loc_00043963;

loc_00043961: ;
    edi = 0; /* xor self */

loc_00043963: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, edi);
    ecx = ecx + 0x44;
    PUSH32(esp, 0x00043970u); sub_00040DB0(); /* call 0x00040DB0 */

loc_00043970: ;
    ecx = MEM32(esp + 0x10);
    edi = 0; /* xor self */
    _fa = (uint32_t)(MEM16(ebx)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(ebx), LO16(edi) (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_000439C6; /* jbe: below or equal (unsigned <=) */

loc_0004397B: ;
    goto loc_00043980;

    /* nop */

loc_00043980: ;
    eax = MEM32(esp + 0x14);
    esi = MEM32(ecx + 0x44);
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    PUSH32(esp, ebx);
    ecx = 0x238E28;
    PUSH32(esp, 0x00043994u); sub_000421A0(); /* call 0x000421A0 */

loc_00043994: ;
    ecx = MEM32(esi + edi * 4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = eax;
    if (TEST_Z(_fa, _fb)) goto loc_000439A7; /* je: equal / zero */

loc_0004399D: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_000439A7; /* jne: not equal / not zero */

loc_000439A2: ;
    PUSH32(esp, 0x000439A7u); sub_0002E400(); /* call 0x0002E400 */

loc_000439A7: ;
    MEM32(esi + edi * 4) = ebp;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(ecx + 0x44);
    _fa = (uint32_t)(MEM32(edx + edi * 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx + edi * 4), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000439D6; /* je: equal / zero */

loc_000439B7: ;
    eax = ZX16(MEM16(ebx));
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043980; /* jl: less (signed <) */

loc_000439BF: ;
    goto loc_000439C6;

loc_000439C1: ;
    __debugbreak(); /* int3 */
    ecx = MEM32(esp + 0x10);

loc_000439C6: ;
    eax = MEM32(ecx + 0x70);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000439E2; /* jne: not equal / not zero */

loc_000439CD: ;
    PUSH32(esp, 0x000439D2u); sub_000436C0(); /* call 0x000436C0 */

loc_000439D2: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000439F5; /* jne: not equal / not zero */

loc_000439D6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

loc_000439E2: ;
    PUSH32(esp, 0x000439E7u); sub_00043700(); /* call 0x00043700 */

loc_000439E7: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000439F5; /* jne: not equal / not zero */

loc_000439EB: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

loc_000439F5: ;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x50);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000439D6; /* je: equal / zero */

loc_00043A00: ;
    ecx = MEM32(eax + 0x48);
    ecx = MEM32(ecx + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00043A10u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043A10: ;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x50);
    esi = 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, esi (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00043A53; /* jle: less or equal (signed <=) */

loc_00043A20: ;
    edi = 0x44;

loc_00043A25: ;
    ecx = MEM32(eax + 0x48);
    ecx = MEM32(ecx + edi + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00043A36u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043A36: ;
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    ecx = esp + 0x1C;
    PUSH32(esp, 0x00043A44u); sub_00065F40(); /* call 0x00065F40 */

loc_00043A44: ;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x50);
    esi++;
    edi = edi + 0x44;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043A25; /* jl: less (signed <) */

loc_00043A53: ;
    edx = MEM32(esp + 0x18);
    eax = eax + 0x34;
    MEM32(eax) = edx;
    ecx = MEM32(esp + 0x1C);
    MEM32(eax + 4) = ecx;
    edx = MEM32(esp + 0x20);
    MEM32(eax + 8) = edx;
    fp_push(MEMF(esp + 0x24)); /* fld float */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    eax = MEM32(esp + 0x10);
    ecx = 0x7EFFFFFF;
    edi = 0; /* xor self */
    MEMF(eax + 0x40) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esp + 0x10);
    eax = eax + 0x1C;
    MEM32(eax) = ecx;
    MEM32(eax + 4) = ecx;
    MEM32(eax + 8) = ecx;
    ecx = 0xFEFFFFFFu;
    MEM32(eax + 0xC) = ecx;
    MEM32(eax + 0x10) = ecx;
    MEM32(eax + 0x14) = ecx;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x50);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043AEF; /* jle: less or equal (signed <=) */

loc_00043AA6: ;
    ebx = 0; /* xor self */
    goto loc_00043AB0;

    /* nop */

loc_00043AB0: ;
    ecx = MEM32(eax + 0x48);
    ecx = MEM32(ecx + ebx + 0x34);
    edx = MEM32(ecx);
    eax = esp + 0x28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x14); PUSH32(esp, 0x00043AC1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043AC1: ;
    esi = MEM32(esp + 0x10);
    ecx = esp + 0x34;
    esi = esi + 0x1C;
    PUSH32(esp, ecx);
    ecx = esi;
    PUSH32(esp, 0x00043AD4u); sub_00040230(); /* call 0x00040230 */

loc_00043AD4: ;
    edx = esp + 0x28;
    PUSH32(esp, edx);
    ecx = esi;
    PUSH32(esp, 0x00043AE0u); sub_00040230(); /* call 0x00040230 */

loc_00043AE0: ;
    eax = MEM32(esp + 0x10);
    ecx = MEM32(eax + 0x50);
    edi++;
    ebx = ebx + 0x44;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043AB0; /* jl: less (signed <) */

loc_00043AEF: ;
    edx = MEM32(eax + 0x50);
    ecx = MEM32(eax + 0x48);
    PUSH32(esp, 0x00043AFAu); sub_000431B0(); /* call 0x000431B0 */

loc_00043AFA: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00043B10(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043B10: ;
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x11));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    ecx = esi + 4;
    PUSH32(esp, edi);
    if (TEST_Z(_fa, _fb)) goto loc_00043B23; /* je: equal / zero */

loc_00043B1E: ;
    PUSH32(esp, 0x00043B23u); sub_000472F0(); /* call 0x000472F0 */

loc_00043B23: ;
    eax = MEM32(esi + 0x20);
    PUSH32(esp, ebx);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043B56; /* jle: less or equal (signed <=) */

loc_00043B2D: ;
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x14);
    edi = 0; /* xor self */

loc_00043B34: ;
    eax = MEM32(esi + 0x18);
    ecx = MEM32(esp + 0x18);
    ecx = MEM32(ecx + 8);
    eax = eax + edi;
    PUSH32(esp, eax);
    ecx = ecx + edi;
    edx = ebp;
    PUSH32(esp, 0x00043B4Au); sub_00018FA0(); /* call 0x00018FA0 */

loc_00043B4A: ;
    eax = MEM32(esi + 0x20);
    ebx++;
    edi = edi + 0x30;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043B34; /* jl: less (signed <) */

loc_00043B55: ;
    POP32(esp, ebp);

loc_00043B56: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x24);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, ebx);
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043B78; /* jle: less or equal (signed <=) */

loc_00043B63: ;
    eax = MEM32(esi);
    ecx = MEM32(eax + edi * 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x28); PUSH32(esp, 0x00043B6Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043B6D: ;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043B63; /* jl: less (signed <) */

loc_00043B78: ;
    POP32(esp, edi);
    MEM8(esi + 0x24) = 1;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

void sub_00043B90(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00043B90: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    PUSH32(esp, edi);
    edi = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043BB5; /* jle: less or equal (signed <=) */

loc_00043BA0: ;
    ecx = MEM32(esi);
    ecx = MEM32(ecx + edi * 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x00043BAAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043BAA: ;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043BA0; /* jl: less (signed <) */

loc_00043BB5: ;
    POP32(esp, edi);
    MEM8(esi + 0x24) = 0;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

void sub_00043BC0(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00043BC0: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = MEM32(ebp + 0xC);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x24));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    PUSH32(esp, edi);
    edi = MEM32(ebp + 0x10);
    if (TEST_NZ(_fa, _fb)) goto loc_00043BE3; /* jne: not equal / not zero */

loc_00043BD8: ;
    PUSH32(esp, edi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043BDFu); sub_00043B10(); /* call 0x00043B10 */

loc_00043BDF: ;
    MEM8(esi + 0x24) = 0;

loc_00043BE3: ;
    eax = MEM32(esi + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + 0x10) = 0;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043C37; /* jle: less or equal (signed <=) */

loc_00043BF1: ;
    ecx = MEM32(edi + 8);
    ecx = ecx + 0x28;
    edx = eax;
    /* nop */

loc_00043C00: ;
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_push(MEMF(ecx)); /* fld float */
    fp_push(MEMF(ecx + -4)); /* fld float */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 4) & 7]; /* fmul st(4) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 3) & 7] = fp_top(); fp_pop(); /* fstp st(3) */
    fp_pop(); /* fstp st(0) */
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(ebp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); /* fcomp st(1) */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043C2F; /* je: equal / zero */

loc_00043C2A: ;
    MEMF(ebp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_00043C31;

loc_00043C2F: ;
    fp_pop(); /* fstp st(0) */

loc_00043C31: ;
    ecx = ecx + 0x30;
    edx--;
    if ((edx != 0)) goto loc_00043C00; /* jne: not equal / not zero */

loc_00043C37: ;
    eax = MEM32(esi + 0x14);
    ecx = eax + 0x60;
    edx = MEM32(ecx);
    MEM32(ebp + -12) = edx;
    edx = MEM32(ecx + 4);
    MEM32(ebp + -8) = edx;
    ecx = MEM32(ecx + 8);
    MEM32(ebp + -4) = ecx;
    edx = MEM32(eax + 0x6C);
    SET_LO8(eax, MEM8(ebp + 0x14));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM32(ebp + 0xC) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_00043C8C; /* je: equal / zero */

loc_00043C5B: ;
    PUSH32(esp, 0);
    PUSH32(esp, ebx);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043C6Au); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043C6A: ;
    fp_push(MEMF(ebp + 0x10)); /* fld float */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    PUSH32(esp, ecx);
    eax = ebp + -12;
    ecx = 0x4B6360;
    fp_top() = fp_top() + MEMF(ebp + 0xC); /* fadd dword ptr [ebp + 0xc] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043C84u); sub_00033350(); /* call 0x00033350 */

loc_00043C84: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043D5F; /* je: equal / zero */

loc_00043C8C: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00043CF0; /* jle: less or equal (signed <=) */

loc_00043C98: ;
    MEM32(ebp + 0x14) = ebx;
    goto loc_00043CA0;

    /* nop */

loc_00043CA0: ;
    edx = MEM32(esi + 0x14);
    edi = MEM32(edx + 0x1C);
    eax = MEM32(ebp + 0x14);
    edx = MEM32(esi + 0x18);
    edi = edi + eax;
    eax = MEM32(edi + 0x10);
    eax = eax + eax * 2;
    eax = eax << 4;
    PUSH32(esp, 0);
    eax = eax + edx;
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043CC8u); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043CC8: ;
    eax = MEM32(edi + 4);
    edi = MEM32(ebp + 8);
    edi = MEM32(edi + 4);
    ecx = MEM32(esi);
    eax = MEM32(edi + eax * 4);
    ecx = MEM32(ecx + ebx * 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x24); PUSH32(esp, 0x00043CE1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043CE1: ;
    MEM32(ebp + 0x14) = MEM32(ebp + 0x14) + 0x28;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    ebx++;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043CA0; /* jl: less (signed <) */

loc_00043CF0: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x30);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043D5F; /* je: equal / zero */

loc_00043CFA: ;
    eax = MEM32(0x23A090);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043D0Eu); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043D0E: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043D5F; /* jle: less or equal (signed <=) */

loc_00043D1A: ;
    /* nop */

loc_00043D20: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x28);
    ecx = MEM32(eax + edi * 8 + 4);
    edx = MEM32(esi + 0x18);
    ebx = MEM32(ebp + 8);
    MEM32(ecx + 0x30) = edx;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    eax = MEM32(eax + 0x28);
    eax = MEM32(eax + edi * 8);
    ebx = MEM32(ebx + 4);
    edx = MEM32(esi);
    eax = MEM32(ebx + eax * 4);
    ecx = ecx + edi;
    ecx = MEM32(edx + ecx * 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x24); PUSH32(esp, 0x00043D54u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043D54: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043D20; /* jl: less (signed <) */

loc_00043D5F: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 20; return; /* ret 16 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00043D70(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00043D70: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x24));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    PUSH32(esp, edi);
    edi = MEM32(ebp + 0xC);
    if (TEST_NZ(_fa, _fb)) goto loc_00043D93; /* jne: not equal / not zero */

loc_00043D88: ;
    PUSH32(esp, edi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043D8Fu); sub_00043B10(); /* call 0x00043B10 */

loc_00043D8F: ;
    MEM8(esi + 0x24) = 0;

loc_00043D93: ;
    eax = MEM32(esi + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + 0xC) = 0;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043DE7; /* jle: less or equal (signed <=) */

loc_00043DA1: ;
    ecx = MEM32(edi + 8);
    ecx = ecx + 0x28;
    edx = eax;
    /* nop */

loc_00043DB0: ;
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_push(MEMF(ecx)); /* fld float */
    fp_push(MEMF(ecx + -4)); /* fld float */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 4) & 7]; /* fmul st(4) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 3) & 7] = fp_top(); fp_pop(); /* fstp st(3) */
    fp_pop(); /* fstp st(0) */
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(ebp + 0xC)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); /* fcomp st(1) */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043DDF; /* je: equal / zero */

loc_00043DDA: ;
    MEMF(ebp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_00043DE1;

loc_00043DDF: ;
    fp_pop(); /* fstp st(0) */

loc_00043DE1: ;
    ecx = ecx + 0x30;
    edx--;
    if ((edx != 0)) goto loc_00043DB0; /* jne: not equal / not zero */

loc_00043DE7: ;
    eax = MEM32(esi + 0x14);
    ecx = eax + 0x60;
    edx = MEM32(ecx);
    MEM32(ebp + -12) = edx;
    edx = MEM32(ecx + 4);
    MEM32(ebp + -8) = edx;
    ecx = MEM32(ecx + 8);
    MEM32(ebp + -4) = ecx;
    edx = MEM32(eax + 0x6C);
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM32(ebp + 8) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_00043E3C; /* je: equal / zero */

loc_00043E0B: ;
    PUSH32(esp, 0);
    PUSH32(esp, ebx);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043E1Au); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043E1A: ;
    fp_push(MEMF(ebp + 0xC)); /* fld float */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    PUSH32(esp, ecx);
    eax = ebp + -12;
    ecx = 0x4B6360;
    fp_top() = fp_top() + MEMF(ebp + 8); /* fadd dword ptr [ebp + 8] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043E34u); sub_00033350(); /* call 0x00033350 */

loc_00043E34: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043EEF; /* je: equal / zero */

loc_00043E3C: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043E8E; /* jle: less or equal (signed <=) */

loc_00043E48: ;
    ebx = 0; /* xor self */
    /* nop */

loc_00043E50: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x1C);
    eax = MEM32(eax + ebx + 0x10);
    ecx = eax + eax * 2;
    eax = MEM32(esi + 0x18);
    ecx = ecx << 4;
    PUSH32(esp, 0);
    ecx = ecx + eax;
    PUSH32(esp, ecx);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043E74u); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043E74: ;
    edx = MEM32(esi);
    ecx = MEM32(edx + edi * 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 0x1C); PUSH32(esp, 0x00043E80u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043E80: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    edi++;
    ebx = ebx + 0x28;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043E50; /* jl: less (signed <) */

loc_00043E8E: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x30);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043EEF; /* je: equal / zero */

loc_00043E98: ;
    eax = MEM32(0x23A090);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043EACu); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043EAC: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043EEF; /* jle: less or equal (signed <=) */

loc_00043EB8: ;
    goto loc_00043EC0;

    /* nop */

loc_00043EC0: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x28);
    ecx = MEM32(eax + edi * 8 + 4);
    edx = MEM32(esi + 0x18);
    MEM32(ecx + 0x30) = edx;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    edx = MEM32(esi);
    ecx = ecx + edi;
    ecx = MEM32(edx + ecx * 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 0x1C); PUSH32(esp, 0x00043EE4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00043EE4: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043EC0; /* jl: less (signed <) */

loc_00043EEF: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00043F00(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00043F00: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x24));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    PUSH32(esp, edi);
    edi = MEM32(ebp + 0xC);
    if (TEST_NZ(_fa, _fb)) goto loc_00043F23; /* jne: not equal / not zero */

loc_00043F18: ;
    PUSH32(esp, edi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043F1Fu); sub_00043B10(); /* call 0x00043B10 */

loc_00043F1F: ;
    MEM8(esi + 0x24) = 0;

loc_00043F23: ;
    eax = MEM32(esi + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + 0xC) = 0;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00043F77; /* jle: less or equal (signed <=) */

loc_00043F31: ;
    ecx = MEM32(edi + 8);
    ecx = ecx + 0x28;
    edx = eax;
    /* nop */

loc_00043F40: ;
    fp_push(MEMF(ecx + 4)); /* fld float */
    fp_push(MEMF(ecx)); /* fld float */
    fp_push(MEMF(ecx + -4)); /* fld float */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 3) & 7]; fp_push(_t); } /* fld st(3) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 4) & 7]; /* fmul st(4) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_stack[(g_fp_top + 3) & 7] = fp_top(); fp_pop(); /* fstp st(3) */
    fp_pop(); /* fstp st(0) */
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(ebp + 0xC)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); /* fcomp st(1) */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00043F6F; /* je: equal / zero */

loc_00043F6A: ;
    MEMF(ebp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_00043F71;

loc_00043F6F: ;
    fp_pop(); /* fstp st(0) */

loc_00043F71: ;
    ecx = ecx + 0x30;
    edx--;
    if ((edx != 0)) goto loc_00043F40; /* jne: not equal / not zero */

loc_00043F77: ;
    eax = MEM32(esi + 0x14);
    ecx = eax + 0x60;
    edx = MEM32(ecx);
    MEM32(ebp + -12) = edx;
    edx = MEM32(ecx + 4);
    MEM32(ebp + -8) = edx;
    ecx = MEM32(ecx + 8);
    MEM32(ebp + -4) = ecx;
    edx = MEM32(eax + 0x6C);
    SET_LO8(eax, MEM8(ebp + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM32(ebp + 8) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_00043FCC; /* je: equal / zero */

loc_00043F9B: ;
    PUSH32(esp, 0);
    PUSH32(esp, ebx);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043FAAu); sub_00107DD0(); /* call 0x00107DD0 */

loc_00043FAA: ;
    fp_push(MEMF(ebp + 0xC)); /* fld float */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    PUSH32(esp, ecx);
    eax = ebp + -12;
    ecx = 0x4B6360;
    fp_top() = fp_top() + MEMF(ebp + 8); /* fadd dword ptr [ebp + 8] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00043FC4u); sub_00033350(); /* call 0x00033350 */

loc_00043FC4: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004407F; /* je: equal / zero */

loc_00043FCC: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0004401E; /* jle: less or equal (signed <=) */

loc_00043FD8: ;
    ebx = 0; /* xor self */
    /* nop */

loc_00043FE0: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x1C);
    eax = MEM32(eax + ebx + 0x10);
    ecx = eax + eax * 2;
    eax = MEM32(esi + 0x18);
    ecx = ecx << 4;
    PUSH32(esp, 0);
    ecx = ecx + eax;
    PUSH32(esp, ecx);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044004u); sub_00107DD0(); /* call 0x00107DD0 */

loc_00044004: ;
    edx = MEM32(esi);
    ecx = MEM32(edx + edi * 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x00044010u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00044010: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x24);
    edi++;
    ebx = ebx + 0x28;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00043FE0; /* jl: less (signed <) */

loc_0004401E: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x30);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004407F; /* je: equal / zero */

loc_00044028: ;
    eax = MEM32(0x23A090);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004403Cu); sub_00107DD0(); /* call 0x00107DD0 */

loc_0004403C: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0004407F; /* jle: less or equal (signed <=) */

loc_00044048: ;
    goto loc_00044050;

    /* nop */

loc_00044050: ;
    edx = MEM32(esi + 0x14);
    eax = MEM32(edx + 0x28);
    ecx = MEM32(eax + edi * 8 + 4);
    edx = MEM32(esi + 0x18);
    MEM32(ecx + 0x30) = edx;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x24);
    edx = MEM32(esi);
    ecx = ecx + edi;
    ecx = MEM32(edx + ecx * 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 0x20); PUSH32(esp, 0x00044074u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00044074: ;
    ecx = MEM32(esi + 0x14);
    eax = MEM32(ecx + 0x30);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00044050; /* jl: less (signed <) */

loc_0004407F: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

void sub_00044090(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00044090: ;
    ecx = MEM32(ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000440C8; /* je: equal / zero */

loc_00044096: ;
    eax = MEM32(ecx + -4);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx + -4;
    esi = ecx + eax * 4;
    eax--;
    if (((int32_t)eax < 0)) goto loc_000440BD; /* js: sign (negative) */

loc_000440A4: ;
    PUSH32(esp, ebx);
    ebx = eax + 1;

loc_000440A8: ;
    ecx = MEM32(esi + -4);
    esi = esi - 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000440B9; /* je: equal / zero */

loc_000440B2: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x000440B9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000440B9: ;
    ebx--;
    if ((ebx != 0)) goto loc_000440A8; /* jne: not equal / not zero */

loc_000440BC: ;
    POP32(esp, ebx);

loc_000440BD: ;
    PUSH32(esp, edi);
    PUSH32(esp, 0x000440C3u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000440C3: ;
    esp = esp + 4;
    POP32(esp, edi);
    POP32(esp, esi);

loc_000440C8: ;
    esp += 4; return; /* ret */

}

void sub_000440D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000440D0: ;
    PUSH32(esp, ebx);
    ebx = ecx;
    ecx = MEM32(ebx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004411A; /* je: equal / zero */

loc_000440D9: ;
    eax = MEM32(ecx + -4);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx + -4;
    esi = ecx + eax * 4;
    eax--;
    if (((int32_t)eax < 0)) goto loc_00044105; /* js: sign (negative) */

loc_000440E7: ;
    PUSH32(esp, ebp);
    ebp = eax + 1;
    goto loc_000440F0;

    /* nop */

loc_000440F0: ;
    ecx = MEM32(esi + -4);
    esi = esi - 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044101; /* je: equal / zero */

loc_000440FA: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x00044101u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00044101: ;
    ebp--;
    if ((ebp != 0)) goto loc_000440F0; /* jne: not equal / not zero */

loc_00044104: ;
    POP32(esp, ebp);

loc_00044105: ;
    PUSH32(esp, edi);
    PUSH32(esp, 0x0004410Bu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0004410B: ;
    ecx = MEM32(esp + 0x14);
    esp = esp + 4;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebx) = ecx;
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

loc_0004411A: ;
    edx = MEM32(esp + 8);
    MEM32(ebx) = edx;
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

void sub_00044130(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00044130: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    esi = ecx;
    MEM32(edi + 4) = MEM32(edi + 4) + 1;
    ecx = MEM32(esi + 0x5C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004414C; /* je: equal / zero */

loc_00044142: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_0004414C; /* jne: not equal / not zero */

loc_00044147: ;
    PUSH32(esp, 0x0004414Cu); sub_0002E400(); /* call 0x0002E400 */

loc_0004414C: ;
    MEM32(esi + 0x5C) = edi;
    POP32(esp, edi);
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_00044160(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00044160: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = esi + 4;
    PUSH32(esp, 0x0004416Bu); sub_00047650(); /* call 0x00047650 */

loc_0004416B: ;
    ecx = MEM32(esi + 0x14);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044183; /* je: equal / zero */

loc_00044172: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_0004417C; /* jne: not equal / not zero */

loc_00044177: ;
    PUSH32(esp, 0x0004417Cu); sub_0002E400(); /* call 0x0002E400 */

loc_0004417C: ;
    MEM32(esi + 0x14) = 0;

loc_00044183: ;
    MEM32(esi + 0x20) = 0;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

void sub_00044190(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00044190: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 4)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, MEM32(esi + 4) (32-bit) */
    PUSH32(esp, edi);
    if (CMP_L(_fas, _fbs)) goto loc_000441BB; /* jl: less (signed <) */

loc_0004419E: ;
    ecx = MEM32(esi);
    edi = ebx + 1;
    edi = edi & 0xFFFFFFFEu;
    eax = edi + edi * 4;
    eax = eax << 3;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x000441B3u); sub_0010FF6F(); /* call 0x0010FF6F */

loc_000441B3: ;
    esp = esp + 8;
    MEM32(esi) = eax;
    MEM32(esi + 4) = edi;

loc_000441BB: ;
    eax = MEM32(esi + 8);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_000441E5; /* jge: greater or equal (signed >=) */

loc_000441C4: ;
    eax = MEM32(esi + 8);
    edx = eax + eax * 4;
    eax = MEM32(esi);
    eax = eax + edx * 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000441D6; /* je: equal / zero */

loc_000441D3: ;
    MEM32(eax + 8) = edi;

loc_000441D6: ;
    ecx = MEM32(esi + 8);
    ecx++;
    eax = ecx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM32(esi + 8) = ecx;
    if (CMP_L(_fas, _fbs)) goto loc_000441C4; /* jl: less (signed <) */

loc_000441E3: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */

loc_000441E5: ;
    if (CMP_LE(_fas, _fbs)) goto loc_0004420E; /* jle: less or equal (signed <=) */

loc_000441E7: ;
    ecx = MEM32(esi + 8);
    edx = MEM32(esi);
    ecx--;
    eax = ecx;
    MEM32(esi + 8) = ecx;
    ecx = eax + eax * 4;
    eax = edx + ecx * 8 + 8;
    ecx = MEM32(eax);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00044209; /* je: equal / zero */

loc_000441FF: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044209; /* jne: not equal / not zero */

loc_00044204: ;
    PUSH32(esp, 0x00044209u); sub_0002E400(); /* call 0x0002E400 */

loc_00044209: ;
    _fa = (uint32_t)(MEM32(esi + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 8), ebx (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_000441E7; /* jg: greater (signed >) */

loc_0004420E: ;
    POP32(esp, edi);
    MEM32(esi + 8) = ebx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

void sub_00044220(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00044220: ;
    PUSH32(esp, edi);
    edi = ecx;
    eax = MEM32(edi + 0x18);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0004422Cu); sub_0010F1CD(); /* call 0x0010F1CD */

loc_0004422C: ;
    ecx = MEM32(edi + 0x14);
    esp = esp + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044240; /* je: equal / zero */

loc_00044236: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044240; /* jne: not equal / not zero */

loc_0004423B: ;
    PUSH32(esp, 0x00044240u); sub_0002E400(); /* call 0x0002E400 */

loc_00044240: ;
    PUSH32(esp, esi);
    esi = edi + 4;
    ecx = esi;
    PUSH32(esp, 0x0004424Bu); sub_00047650(); /* call 0x00047650 */

loc_0004424B: ;
    ecx = esi + 4;
    PUSH32(esp, 0x00044253u); sub_00040D70(); /* call 0x00040D70 */

loc_00044253: ;
    ecx = MEM32(esi);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    POP32(esp, esi);
    if (TEST_Z(_fa, _fb)) goto loc_00044264; /* je: equal / zero */

loc_0004425A: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044264; /* jne: not equal / not zero */

loc_0004425F: ;
    PUSH32(esp, 0x00044264u); sub_0002E400(); /* call 0x0002E400 */

loc_00044264: ;
    ecx = edi;
    POP32(esp, edi);
    g_seh_ebp = ebp; sub_00044090(); return; /* tail jmp 0x00044090 */

}

void sub_00044270(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00044270: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 8);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000442A4; /* jle: less or equal (signed <=) */

loc_0004427D: ;
    PUSH32(esp, edi);
    edi = 0; /* xor self */

loc_00044280: ;
    eax = MEM32(esi);
    ecx = MEM32(edi + eax + 8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    eax = edi + eax + 8;
    if (TEST_Z(_fa, _fb)) goto loc_00044298; /* je: equal / zero */

loc_0004428E: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044298; /* jne: not equal / not zero */

loc_00044293: ;
    PUSH32(esp, 0x00044298u); sub_0002E400(); /* call 0x0002E400 */

loc_00044298: ;
    eax = MEM32(esi + 8);
    ebx++;
    edi = edi + 0x28;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00044280; /* jl: less (signed <) */

loc_000442A3: ;
    POP32(esp, edi);

loc_000442A4: ;
    ecx = MEM32(esi);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x000442ACu); sub_0010F1CD(); /* call 0x0010F1CD */

loc_000442AC: ;
    esp = esp + 4;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

void sub_000442C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000442C0: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000442E7; /* jl: less (signed <) */

loc_000442CF: ;
    ecx = MEM32(esi);
    eax = edi * 8;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x000442DFu); sub_0010FF6F(); /* call 0x0010FF6F */

loc_000442DF: ;
    esp = esp + 8;
    MEM32(esi) = eax;
    MEM32(esi + 4) = edi;

loc_000442E7: ;
    _fa = (uint32_t)(MEM32(esi + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 8), edi (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00044312; /* jge: greater or equal (signed >=) */

loc_000442EC: ;
    /* nop */

loc_000442F0: ;
    edx = MEM32(esi + 8);
    eax = MEM32(esi);
    eax = eax + edx * 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044303; /* je: equal / zero */

loc_000442FC: ;
    MEM32(eax + 4) = 0;

loc_00044303: ;
    ecx = MEM32(esi + 8);
    ecx++;
    eax = ecx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    MEM32(esi + 8) = ecx;
    if (CMP_L(_fas, _fbs)) goto loc_000442F0; /* jl: less (signed <) */

loc_00044310: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */

loc_00044312: ;
    if (_flags /* jle: less or equal (signed <=) */) goto loc_00044338;

loc_00044314: ;
    ecx = MEM32(esi + 8);
    ecx--;
    eax = ecx;
    MEM32(esi + 8) = ecx;
    ecx = MEM32(esi);
    eax = ecx + eax * 8 + 4;
    ecx = MEM32(eax);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044333; /* je: equal / zero */

loc_00044329: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044333; /* jne: not equal / not zero */

loc_0004432E: ;
    PUSH32(esp, 0x00044333u); sub_0002E400(); /* call 0x0002E400 */

loc_00044333: ;
    _fa = (uint32_t)(MEM32(esi + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 8), edi (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00044314; /* jg: greater (signed >) */

loc_00044338: ;
    MEM32(esi + 8) = edi;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

void sub_00044340(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00044340: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x2C;
    eax = MEM32(ebp + 0xC);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(eax + 8);
    PUSH32(esp, edi);
    ebx = ecx;
    PUSH32(esp, 0x14);
    MEM32(ebp + -8) = esi;
    MEM32(ebx + 0x7C) = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004435Eu); sub_0010F511(); /* call 0x0010F511 */

loc_0004435E: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044370; /* je: equal / zero */

loc_00044365: ;
    ecx = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004436Cu); sub_00047690(); /* call 0x00047690 */

loc_0004436C: ;
    edi = eax;
    goto loc_00044372;

loc_00044370: ;
    edi = 0; /* xor self */

loc_00044372: ;
    ecx = MEM32(ebx + 0x70);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00044383; /* je: equal / zero */

loc_00044379: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_00044383; /* jne: not equal / not zero */

loc_0004437E: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044383u); sub_0002E400(); /* call 0x0002E400 */

loc_00044383: ;
    MEM32(ebx + 0x70) = edi;
    edi = MEM32(ebp + 8);
    ecx = MEM32(edi + 0x34);
    PUSH32(esp, ecx);
    ecx = MEM32(ebx + 0x70);
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044396u); sub_000477D0(); /* call 0x000477D0 */

loc_00044396: ;
    _fa = (uint32_t)(MEM16(esi + 2)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 2), 0 (16-bit) */
    MEM32(ebp + 0xC) = 0;
    if (CMP_BE(_fa, _fb)) goto loc_000445B4; /* jbe: below or equal (unsigned <=) */

loc_000443A8: ;
    goto loc_000443B0;

    /* nop */

loc_000443B0: ;
    edx = ZX16(MEM16(esi));
    eax = MEM32(ebp + 0xC);
    ecx = MEM32(edi + 0x34);
    edx = edx + eax;
    eax = ZX16(MEM16(esi + edx * 2 + 0xC));
    eax = MEM32(ecx + eax * 4 + 4);
    eax = eax + ecx;
    PUSH32(esp, 0x11);
    PUSH32(esp, eax);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x000443D0u); sub_0003EB70(); /* call 0x0003EB70 */

loc_000443D0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000443F1; /* jne: not equal / not zero */

loc_000443D4: ;
    eax = MEM32(ebp + 0xC);
    ecx = ZX16(MEM16(esi + 2));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    MEM32(ebp + 0xC) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_000443B0; /* jl: less (signed <) */

loc_000443E3: ;
    SET_LO8(eax, 0); /* xor self */
    esp = ebp + -56;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

loc_000443F1: ;
    esi = MEM32(eax + 8);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(ebp + -4) = esi;
    if (TEST_Z(_fa, _fb)) goto loc_000445B4; /* je: equal / zero */

loc_000443FF: ;
    eax = ZX16(MEM16(esi + 2));
    edx = MEM32(edi + 0x34);
    eax = eax << 2;
    PUSH32(esp, eax);
    MEM32(ebp + 8) = edx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044412u); sub_0010F511(); /* call 0x0010F511 */

loc_00044412: ;
    MEM32(ebx + 0x74) = eax;
    ecx = ZX16(MEM16(esi + 2));
    edi = 0; /* xor self */
    esp = esp + 4;
    MEM32(ebx + 0x78) = ecx;
    _fa = (uint32_t)(MEM16(esi + 2)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 2), LO16(edi) (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0004446A; /* jbe: below or equal (unsigned <=) */

loc_00044427: ;
    edx = esi + 4;
    MEM32(ebp + 0xC) = edx;
    /* nop */

loc_00044430: ;
    eax = MEM32(ebp + 0xC);
    edx = MEM32(eax);
    ecx = MEM32(ebp + 8);
    eax = MEM32(ecx + edx * 4 + 4);
    eax = eax + ecx;
    ecx = MEM32(ebx + 0x5C);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044447u); sub_00034C10(); /* call 0x00034C10 */

loc_00044447: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004444F; /* je: equal / zero */

loc_0004444B: ;
    eax = MEM32(eax);
    goto loc_00044452;

loc_0004444F: ;
    eax = eax | 0xFFFFFFFFu;

loc_00044452: ;
    ecx = MEM32(ebx + 0x74);
    MEM32(ecx + edi * 4) = eax;
    ecx = MEM32(ebp + 0xC);
    edx = ZX16(MEM16(esi + 2));
    edi++;
    ecx = ecx + 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, edx (32-bit) */
    MEM32(ebp + 0xC) = ecx;
    if (CMP_L(_fas, _fbs)) goto loc_00044430; /* jl: less (signed <) */

loc_0004446A: ;
    eax = MEM32(ebp + -8);
    edi = ZX16(MEM16(eax));
    eax = edi;
    eax = eax + 3;
    eax = eax & 0xFFFFFFFCu;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004447Du); sub_0010F4D0(); /* call 0x0010F4D0 */

loc_0004447D: ;
    ecx = edi;
    edx = esp;
    edi = edx;
    edx = ecx;
    ecx = ecx >> 2;
    eax = 0; /* xor self */
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM16(esi)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi), LO16(eax) (16-bit) */
    MEM32(ebp + 0xC) = eax;
    if (CMP_BE(_fa, _fb)) goto loc_000445A6; /* jbe: below or equal (unsigned <=) */

loc_000444A1: ;
    MEM32(ebp + 8) = eax;
    goto loc_000444B0;

loc_000444A6: ;
    esi = MEM32(ebp + -4);
    /* nop */

loc_000444B0: ;
    eax = ZX16(MEM16(esi + 2));
    edi = MEM32(ebp + 8);
    ecx = MEM32(ebx + 0x24);
    eax = eax + edi;
    edi = esi + eax * 4 + 4;
    esi = ebx + 0x1C;
    ecx++;
    PUSH32(esp, ecx);
    ecx = esi;
    MEM32(ebp + -12) = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x000444CFu); sub_00044190(); /* call 0x00044190 */

loc_000444CF: ;
    eax = MEM32(esi + 8);
    edx = eax + eax * 4;
    eax = MEM32(esi);
    esi = eax + edx * 8 + -40;
    edx = MEM32(ebp + -8);
    MEM32(esi + 4) = 0xFFFFFFFFu;
    eax = ZX16(MEM16(edx));
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00044507; /* jle: less or equal (signed <=) */

loc_000444EE: ;
    SET_LO16(edi, MEM16(edi + 0x3C));
    edx = edx + 0xC;

loc_000444F5: ;
    _fa = (uint32_t)(MEM16(edx)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(edx), LO16(edi) (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00044504; /* je: equal / zero */

loc_000444FA: ;
    ecx++;
    edx = edx + 2;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000444F5; /* jl: less (signed <) */

loc_00044502: ;
    goto loc_00044507;

loc_00044504: ;
    MEM32(esi + 4) = ecx;

loc_00044507: ;
    ecx = MEM32(ebp + 0xC);
    edx = MEM32(ebp + -12);
    MEM32(esi) = ecx;
    SET_LO16(eax, MEM16(edx + 0x42));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(6) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), 6 (16-bit) */
    ecx = ZX16(LO16(eax));
    if (CMP_B(_fa, _fb)) goto loc_00044521; /* jb: below (unsigned <) */

loc_0004451C: ;
    ecx = 6;

loc_00044521: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esi + 0xC) = ecx;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0004454C; /* jle: less or equal (signed <=) */

loc_0004452A: ;
    ecx = esi + 0x10;
    /* nop */

loc_00044530: ;
    edx = MEM32(ebp + -12);
    edx = MEM32(edx + 0x54);
    edx = MEM32(edx + eax * 4);
    edi = MEM32(ebx + 0x74);
    edx = MEM32(edi + edx * 4);
    MEM32(ecx) = edx;
    edx = MEM32(esi + 0xC);
    eax++;
    ecx = ecx + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00044530; /* jl: less (signed <) */

loc_0004454C: ;
    edi = MEM32(ebp + -4);
    eax = ZX16(MEM16(edi + 2));
    ecx = MEM32(ebp + 8);
    edx = MEM32(ebx + 0x74);
    eax = eax + ecx;
    ecx = MEM32(ebx + 0x78);
    PUSH32(esp, ecx);
    edi = edi + eax * 4 + 4;
    PUSH32(esp, edx);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004456Bu); sub_000483F0(); /* call 0x000483F0 */

loc_0004456B: ;
    ecx = MEM32(esi + 8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004457C; /* je: equal / zero */

loc_00044572: ;
    MEM32(ecx + 4) = MEM32(ecx + 4) - 1;
    if ((MEM32(ecx + 4) != 0)) goto loc_0004457C; /* jne: not equal / not zero */

loc_00044577: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0004457Cu); sub_0002E400(); /* call 0x0002E400 */

loc_0004457C: ;
    edx = MEM32(ebp + 8);
    ecx = MEM32(ebp + -4);
    eax = MEM32(ebp + 0xC);
    MEM32(esi + 8) = edi;
    esi = edi;
    edi = MEM32(esi + 4);
    edi++;
    edx = edx + 0x16;
    MEM32(esi + 4) = edi;
    MEM32(ebp + 8) = edx;
    edx = ZX16(MEM16(ecx));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(ebp + 0xC) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_000444A6; /* jl: less (signed <) */

loc_000445A6: ;
    eax = MEM32(ebx + 0x30);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000445C2; /* jne: not equal / not zero */

loc_000445AD: ;
    eax = MEM32(ebx + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000445C2; /* jne: not equal / not zero */

loc_000445B4: ;
    SET_LO8(eax, 0); /* xor self */
    esp = ebp + -56;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

loc_000445C2: ;
    eax = MEM32(ebx + 0x24);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -28) = 0;
    MEM32(ebp + -24) = 0;
    MEM32(ebp + -20) = 0;
    MEM32(ebp + -16) = 0;
    MEM8(ebp + 0xF) = 0;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00044634; /* jle: less or equal (signed <=) */

loc_000445EB: ;
    esi = 0; /* xor self */
    /* nop */

loc_000445F0: ;
    SET_LO8(eax, MEM8(ebp + 0xF));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0004460D; /* jne: not equal / not zero */

loc_000445F7: ;
    eax = MEM32(ebx + 0x1C);
    ecx = MEM32(esi + eax + 8);
    edx = MEM32(ecx);
    eax = ebp + -28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00044607u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00044607: ;
    MEM8(ebp + 0xF) = 1;
    goto loc_00044629;

loc_0004460D: ;
    ecx = MEM32(ebx + 0x1C);
    ecx = MEM32(esi + ecx + 8);
    edx = MEM32(ecx);
    eax = ebp + -44;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x0004461Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004461D: ;
    ecx = ebp + -44;
    PUSH32(esp, ecx);
    ecx = ebp + -28;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044629u); sub_00065F40(); /* call 0x00065F40 */

loc_00044629: ;
    eax = MEM32(ebx + 0x24);
    edi++;
    esi = esi + 0x28;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000445F0; /* jl: less (signed <) */

loc_00044634: ;
    eax = MEM32(ebx + 0x30);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00044681; /* jle: less or equal (signed <=) */

loc_0004463D: ;
    /* nop */

loc_00044640: ;
    SET_LO8(eax, MEM8(ebp + 0xF));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0004465D; /* jne: not equal / not zero */

loc_00044647: ;
    edx = MEM32(ebx + 0x28);
    ecx = MEM32(edx + esi * 8 + 4);
    eax = MEM32(ecx);
    edx = ebp + -28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00044657u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00044657: ;
    MEM8(ebp + 0xF) = 1;
    goto loc_00044679;

loc_0004465D: ;
    eax = MEM32(ebx + 0x28);
    ecx = MEM32(eax + esi * 8 + 4);
    edx = MEM32(ecx);
    eax = ebp + -44;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x0004466Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004466D: ;
    ecx = ebp + -44;
    PUSH32(esp, ecx);
    ecx = ebp + -28;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00044679u); sub_00065F40(); /* call 0x00065F40 */

loc_00044679: ;
    eax = MEM32(ebx + 0x30);
    esi++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00044640; /* jl: less (signed <) */

loc_00044681: ;
    fp_push(MEMF(ebp + -16)); /* fld float */
    eax = MEM32(ebp + -28);
    fp_top() = sqrt(fp_top()); /* fsqrt */
    ecx = MEM32(ebp + -24);
    edx = ebx + 0x60;
    MEM32(edx) = eax;
    eax = MEM32(ebp + -20);
    MEM32(edx + 4) = ecx;
    MEM32(edx + 8) = eax;
    SET_LO8(eax, 1);
    MEMF(ebx + 0x6C) = (float)fp_top(); fp_pop(); /* fstp */
    esp = ebp + -56;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_000125E0
 * Original: 0x000125E0 - 0x000125F4 (20 bytes, 5 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000125E0(void)
{

loc_000125E0: ;
    eax = MEM32(esp + 4);
    MEM32(ecx + 0xC) = eax;
    ecx = 0x3C64D8;
    PUSH32(esp, 0x000125F1u); sub_00024D30(); /* call 0x00024D30 */

loc_000125F1: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00030600
 * Original: 0x00030600 - 0x00030668 (104 bytes, 33 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00030600(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00030600: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    ebp = ecx;
    PUSH32(esp, 0x0003060Fu); sub_00030460(); /* call 0x00030460 */

loc_0003060F: ;
    SET_LO8(ebx, MEM8(esp + 0x14));
    ecx = 0; /* xor self */
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), LO8(ecx) (8-bit) */
    edi = eax;
    if (CMP_NE(_fa, _fb)) goto loc_00030655; /* jne: not equal / not zero */

loc_0003061B: ;
    edx = edi;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x94);
    eax = MEM32(edx + ebp + 0xC4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    PUSH32(esp, esi);
    esi = edx + ebp;
    if (CMP_EQ(_fa, _fb)) goto loc_0003064A; /* je: equal / zero */

loc_00030632: ;
    MEM16(esi + 0xA6) = LO16(ecx);
    MEM16(esi + 0xA8) = LO16(ecx);
    ecx = esi + 0x64;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0003064Au); sub_001DAB88(); /* call 0x001DAB88 */

loc_0003064A: ;
    MEM32(esi + 0xCC) = 0xFFFFFFFFu;
    POP32(esp, esi);

loc_00030655: ;
    edi = (uint32_t)((int32_t)edi * (int32_t)0x94);
    MEM8(edi + ebp + 0xD0) = LO8(ebx);
    POP32(esp, edi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000306A0
 * Original: 0x000306A0 - 0x000306AF (15 bytes, 4 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000306A0(void)
{

loc_000306A0: ;
    eax = MEM32(ecx + 0x29A);
    ecx = MEM32(esp + 4);
    MEM32(ecx) = eax;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00031570
 * Original: 0x00031570 - 0x000315B3 (67 bytes, 23 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00031570(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00031570: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x1E5154;
    eax = MEM32(0x3D0060);
    ecx = MEM32(eax + 0x14);
    edx = eax;
    eax = eax + 0x14;
    ecx--;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(eax) = ecx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_00031599; /* jg: greater (signed >) */

loc_0003158D: ;
    ecx = MEM32(0x3E25A8);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x18); PUSH32(esp, 0x00031599u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00031599: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    MEM32(esi) = 0x1E5140;
    if (TEST_Z(_fa, _fb)) goto loc_000315AD; /* je: equal / zero */

loc_000315A6: ;
    ecx = esi;
    PUSH32(esp, 0x000315ADu); sub_00039840(); /* call 0x00039840 */

loc_000315AD: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000336A0
 * Original: 0x000336A0 - 0x0003371C (124 bytes, 47 insns)
 * Category: game_vtable
 * CC: thiscall, 3 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000336A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000336A0: ;
    {
        static uint32_t trace_count;
        ++trace_count;
        if (trace_count <= 32) {
            fprintf(stderr,
                    "[VTABLE-336A0] #%u owner=%08X arg0=%08X arg1=%08X arg2=%08X ret=%08X\n",
                    trace_count, ecx, MEM32(esp + 4), MEM32(esp + 8),
                    MEM32(esp + 12), MEM32(esp));
        }
    }
    eax = MEM32(esp + 0xC);
    SET_LO8(edx, MEM8(esp + 8));
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), LO8(ecx) (8-bit) */
    PUSH32(esp, edi);
    MEM32(ebx + 4) = eax;
    MEM8(ebx + 8) = LO8(ecx);
    edi = eax;
    if (CMP_NE(_fa, _fb)) goto loc_000336C2; /* jne: not equal / not zero */

loc_000336BF: ;
    edi = eax + 1;

loc_000336C2: ;
    eax = MEM32(esi + 0x248);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_000336E7; /* jle: less or equal (signed <=) */

loc_000336CC: ;
    edx = esi + 0x208;
    PUSH32(esp, ebp);

loc_000336D3: ;
    ebp = MEM32(edx);
    _fa = (uint32_t)(MEM32(ebp + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 4), edi (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_000336E4; /* jge: greater or equal (signed >=) */

loc_000336DA: ;
    ecx++;
    edx = edx + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000336D3; /* jl: less (signed <) */

loc_000336E2: ;
    goto loc_000336E6;

loc_000336E4: ;
    eax = ecx;

loc_000336E6: ;
    POP32(esp, ebp);

loc_000336E7: ;
    ecx = MEM32(esi + 0x248);
    ecx = ecx - eax;
    ecx = ecx << 2;
    edi = esi + eax * 4 + 0x208;
    PUSH32(esp, ecx);
    edx = edi + 4;
    PUSH32(esp, edi);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00033704u); sub_0010F750(); /* call 0x0010F750 */

loc_00033704: ;
    eax = MEM32(esi + 0x248);
    esp = esp + 0xC;
    eax++;
    MEM32(esi + 0x248) = eax;
    MEM32(edi) = ebx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_00033720
 * Original: 0x00033720 - 0x0003377F (95 bytes, 31 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00033720(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00033720: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x248);
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0003377B; /* jle: less or equal (signed <=) */

loc_0003372F: ;
    edx = MEM32(esp + 8);

loc_00033733: ;
    _fa = (uint32_t)(MEM32(esi + eax * 4 + 0x208)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + eax * 4 + 0x208), edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00033745; /* je: equal / zero */

loc_0003373C: ;
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00033733; /* jl: less (signed <) */

loc_00033741: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

loc_00033745: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_0003377B; /* jle: less or equal (signed <=) */

loc_0003374A: ;
    edx = MEM32(esi + 0x248);
    ecx = esi + eax * 4 + 0x208;
    edx = edx - eax;
    eax = edx * 4 + -4;
    PUSH32(esp, eax);
    edx = ecx + 4;
    PUSH32(esp, edx);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x0003376Bu); sub_0010F750(); /* call 0x0010F750 */

loc_0003376B: ;
    eax = MEM32(esi + 0x248);
    esp = esp + 0xC;
    eax--;
    MEM32(esi + 0x248) = eax;

loc_0003377B: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00037B80
 * Original: 0x00037B80 - 0x00037D36 (438 bytes, 168 insns)
 * Category: game_vtable
 * CC: thiscall, 5 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00037B80(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00037B80: ;
    esp = esp - 0x104;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    SET_LO8(eax, MEM8(edi + 4));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00037BA6; /* jne: not equal / not zero */

loc_00037B92: ;
    PUSH32(esp, 0x1E5320);
    edx = 0x1E52EC;
    ecx = 0x12C;
    PUSH32(esp, 0x00037BA6u); sub_00068FE0(); /* call 0x00068FE0 */

loc_00037BA6: ;
    esi = MEM32(esp + 0x11C);
    eax = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, 0);
    ecx = edi;
    { uint32_t _icall_target = MEM32(eax + 0x54); PUSH32(esp, 0x00037BB7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00037BB7: ;
    ebp = MEM32(esp + 0x114);
    PUSH32(esp, 0);
    ecx = esp + 0x10;
    PUSH32(esp, ecx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x00037BCEu); sub_00037860(); /* call 0x00037860 */

loc_00037BCE: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00037BE0; /* jne: not equal / not zero */

loc_00037BD2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037BE0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 3);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0xC0000000u);
    edx = esp + 0x28;
    PUSH32(esp, edx);
    PUSH32(esp, 0x00037BFAu); sub_00119587(); /* call 0x00119587 */

loc_00037BFA: ;
    ebx = eax;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, 0xFFFFFFFFu (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00037C41; /* jne: not equal / not zero */

loc_00037C01: ;
    PUSH32(esp, 0x00037C06u); sub_0002A76D(); /* call 0x0002A76D */

loc_00037C06: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 2 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00037C28; /* je: equal / zero */

loc_00037C0B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 3 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00037C28; /* je: equal / zero */

loc_00037C10: ;
    edx = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 0x58); PUSH32(esp, 0x00037C19u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00037C19: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037C28: ;
    eax = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, 0x12);
    ecx = edi;
    { uint32_t _icall_target = MEM32(eax + 0x54); PUSH32(esp, 0x00037C32u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00037C32: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037C41: ;
    PUSH32(esp, 0xAC);
    PUSH32(esp, 0x00037C4Bu); sub_0010F511(); /* call 0x0010F511 */

loc_00037C4B: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00037C60; /* je: equal / zero */

loc_00037C52: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ecx = eax;
    PUSH32(esp, 0x00037C5Cu); sub_000376A0(); /* call 0x000376A0 */

loc_00037C5C: ;
    esi = eax;
    goto loc_00037C62;

loc_00037C60: ;
    esi = 0; /* xor self */

loc_00037C62: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x50);
    ebx = esi + 0x58;
    PUSH32(esp, ebx);
    ecx = esi;
    PUSH32(esp, 0x00037C71u); sub_00037710(); /* call 0x00037710 */

loc_00037C71: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00037C94; /* jne: not equal / not zero */

loc_00037C75: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00037D27; /* je: equal / zero */

loc_00037C7D: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x00037C85u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00037C85: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037C94: ;
    eax = MEM32(ebx);
    ecx = MEM32(esi + 0x5C);
    edx = MEM32(esi + 0xA8);
    ecx = ecx + eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00037D18; /* jne: not equal / not zero */

loc_00037CA5: ;
    edx = MEM32(esi + 0x60);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x11C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esp + 0x11C) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00037D18; /* jne: not equal / not zero */

loc_00037CB1: ;
    ecx = MEM32(esp + 0x124);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00037CCE; /* jne: not equal / not zero */

loc_00037CBC: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00037CC2u); sub_001103DC(); /* call 0x001103DC */

loc_00037CC2: ;
    esp = esp + 4;
    MEM32(esi + 0x48) = eax;
    MEM8(esi + 0x4C) = 1;
    goto loc_00037CF4;

loc_00037CCE: ;
    _fa = (uint32_t)(MEM32(esp + 0x128)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 0x128), eax (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00037CED; /* jae: above or equal (unsigned >=) */

loc_00037CD7: ;
    POP32(esp, ebx);
    MEM32(edi + 8) = 0xB;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037CED: ;
    MEM32(esi + 0x48) = ecx;
    MEM8(esi + 0x4C) = 0;

loc_00037CF4: ;
    ecx = MEM32(ebx);
    edi = MEM32(esi + 0x48);
    edx = ecx;
    ecx = ecx >> 2;
    eax = 0; /* xor self */
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    POP32(esp, ebx);
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

loc_00037D18: ;
    MEM32(edi + 8) = 0x12;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00037D27u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00037D27: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebp);
    esp = esp + 0x104;
    esp += 24; return; /* ret 20 */

}

/**
 * sub_000386A0
 * Original: 0x000386A0 - 0x000386B1 (17 bytes, 5 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000386A0(void)
{

loc_000386A0: ;
    eax = MEM32(esp + 4);
    edx = MEM32(esp + 8);
    MEM32(ecx + 8) = eax;
    MEM32(ecx + 0xC) = edx;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0002FE60
 * Original: 0x0002FE60 - 0x0002FE80 (32 bytes, 14 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002FE60(void)
{
    uint32_t _frame_call_esp = 0;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0002FE60: ;
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x60));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0002FE7E; /* jne: not equal / not zero */

loc_0002FE6A: ;
    /* nop */

loc_0002FE70: ;
    eax = MEM32(esi);
    ecx = esi;
    _frame_call_esp = g_esp;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x1C); PUSH32(esp, 0x0002FE77u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002FE77: ;
    if (g_esp != _frame_call_esp) {
        static RECOMP_TLS uint32_t stack_mismatch_count;
        ++stack_mismatch_count;
        if (stack_mismatch_count <= 8u ||
            (stack_mismatch_count & (stack_mismatch_count - 1u)) == 0u) {
            fprintf(stderr,
                    "[FRAME-STACK] count=%u expected=%08X actual=%08X delta=%d\n",
                    stack_mismatch_count, _frame_call_esp, g_esp,
                    (int32_t)(g_esp - _frame_call_esp));
            fflush(stderr);
        }
        /* Xemu enters 0x2FEC0 with the return address at ESP and resumes at
         * 0x2FE77 with only that address consumed.  Keep this verified
         * no-argument vcall boundary exact even when a nested translated
         * callback has an incorrect cleanup annotation. */
        g_esp = _frame_call_esp;
    }
    godzilla_d3d_frame_hook();
    /* On hardware this loop is serialized by display presentation.  The
     * current D3D bridge returns immediately, so explicitly consume one of
     * the runtime's emulated vblanks here to preserve Xbox frame/movie time. */
    xbox_irq_wait_for_vblank();
    {
        static RECOMP_TLS uint32_t loop_count;
        uint32_t event_bus = MEM32(0x003E25A8u);
        ++loop_count;
        if (loop_count <= 8u || (loop_count & (loop_count - 1u)) == 0u) {
            fprintf(stderr,
                    "[MAIN-LOOP] count=%u object=%08X frame=%08X stop=%02X "
                    "step=%08X accum=%08X bus=%08X listeners=%u\n",
                    loop_count, esi, MEM32(esi + 0x30u), MEM8(esi + 0x60u),
                    MEM32(esi + 0x64u), MEM32(esi + 0x6Cu), event_bus,
                    event_bus ? MEM32(event_bus + 0x204u) : 0u);
            fflush(stderr);
        }
    }
    SET_LO8(eax, MEM8(esi + 0x60));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0002FE70; /* je: equal / zero */

loc_0002FE7E: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */
}

/**
 * sub_0002FEC0
 * Original: 0x0002FEC0 - 0x0002FF6F (175 bytes, 60 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002FEC0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_0002FEC0: ;
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0x6C)); /* fld float */
    PUSH32(esp, edi);
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    edi = esi + 0x38;
    ecx = edi;
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0002FEED;

loc_0002FEDA: ;
    MEM32(esi + 0x68) = MEM32(esi + 0x68) + 1;
    eax = MEM32(esi + 0x6C);
    MEM32(esp + 8) = eax;
    PUSH32(esp, 0x0002FEE9u); sub_000691C0();

loc_0002FEE9: ;
    fp_pop();
    goto loc_0002FF2B;

loc_0002FEED: ;
    PUSH32(esp, 0x0002FEF2u); sub_00069410();

loc_0002FEF2: ;
    fp_top() = MEMF(esi + 0x64) - fp_top();
    MEMF(esp + 8) = (float)fp_top();
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop();
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb);
    if (TEST_NZ(_fa, _fb)) goto loc_0002FF19;

loc_0002FF06: ;
    {
        static RECOMP_TLS uint32_t render_tick_count;
        ++render_tick_count;
        if (render_tick_count <= 8u ||
            (render_tick_count & (render_tick_count - 1u)) == 0u) {
            fprintf(stderr,
                    "[FRAME-TICK] count=%u object=%08X frame=%08X "
                    "target=%08X dt=%08X\n",
                    render_tick_count, esi, MEM32(esi + 0x30u),
                    MEM32(MEM32(esi) + 0x48u), MEM32(esp + 8u));
            fflush(stderr);
        }
    }
    eax = MEM32(esp + 8);
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x48); PUSH32(esp, 0x0002FF12u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0002FF12: ;
    fprintf(stderr, "[FRAME-PHASE] limiter-return esp=%08X fp=%u\n", esp, g_fp_top);
    fp_pop();
    MEM32(esi + 0x68) = MEM32(esi + 0x68) + 1;
    goto loc_0002FF20;

loc_0002FF19: ;
    MEM32(esi + 0x68) = 0;

loc_0002FF20: ;
    ecx = edi;
    PUSH32(esp, 0x0002FF27u); sub_000691C0();

loc_0002FF27: ;
    fprintf(stderr, "[FRAME-PHASE] accumulator-return esp=%08X fp=%u\n", esp, g_fp_top);
    MEMF(esp + 8) = (float)fp_top(); fp_pop();

loc_0002FF2B: ;
    ecx = edi;
    PUSH32(esp, 0x0002FF32u); sub_00069470();

loc_0002FF32: ;
    fprintf(stderr, "[FRAME-PHASE] clock-return esp=%08X fp=%u\n", esp, g_fp_top);
    MEMF(esi + 0x8C) = (float)fp_top(); fp_pop();
    ecx = edi;
    PUSH32(esp, 0x0002FF3Fu); sub_00069190();

loc_0002FF3F: ;
    fprintf(stderr, "[FRAME-PHASE] timer-commit-return esp=%08X fp=%u\n", esp, g_fp_top);
    eax = MEM32(esi + 0x30);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb);
    if (TEST_NZ(_fa, _fb)) goto loc_0002FF56;

loc_0002FF46: ;
    ecx = MEM32(0x3E25A8);
    eax = MEM32(esp + 8);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0002FF56u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0002FF56: ;
    fprintf(stderr, "[FRAME-PHASE] event-dispatch-return esp=%08X fp=%u\n", esp, g_fp_top);
    SET_LO8(eax, MEM8(esi + 0x60));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb);
    POP32(esp, edi);
    POP32(esp, esi);
    if (TEST_NZ(_fa, _fb)) goto loc_0002FF6D;

loc_0002FF5F: ;
    ecx = MEM32(0x3E25A8);
    edx = MEM32(ecx);
    fprintf(stderr, "[FRAME-PHASE] event-tail-enter esp=%08X fp=%u object=%08X vtable=%08X target=%08X\n",
            esp, g_fp_top, ecx, edx, MEM32(edx + 0x20));
    esp = esp + 4;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(edx + 0x20)); return;

loc_0002FF6D: ;
    POP32(esp, ecx);
    esp += 4; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00100530
 * Original: 0x00100530 - 0x00100635 (261 bytes, 68 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00100530(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00100530: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0xC9));
    ebx = 0; /* xor self */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001005C8; /* je: equal / zero */

loc_00100544: ;
    ecx = MEM32(esi + 0xC4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001005B8; /* je: equal / zero */

loc_0010054E: ;
    PUSH32(esp, 0x00100553u); sub_000E4A60(); /* call 0x000E4A60 */

loc_00100553: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001005C8; /* je: equal / zero */

loc_00100557: ;
    eax = MEM32(esi + 0xC4);
    _fa = (uint32_t)(MEM8(eax + 0x54A)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x54A), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010059C; /* je: equal / zero */

loc_00100565: ;
    PUSH32(esp, ebx);
    ecx = 0x4AD508;
    PUSH32(esp, 0x00100570u); sub_000DA0F0(); /* call 0x000DA0F0 */

loc_00100570: ;
    ecx = MEM32(esi + 0xB8);
    ecx = MEM32(ecx + 8);
    MEM8(eax + 0x168) = LO8(ebx);
    edx = MEM32(esi + 0xAC);
    ecx = MEM32(edx + ecx * 4);
    edx = MEM32(ecx + 0x100);
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    ecx = 0x4AD62C;
    PUSH32(esp, 0x0010059Cu); sub_000E8F00(); /* call 0x000E8F00 */

loc_0010059C: ;
    eax = MEM32(esi + 0xC4);
    _fa = (uint32_t)(MEM8(eax + 0x54E)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x54E), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001005C1; /* je: equal / zero */

loc_001005AA: ;
    MEM8(esi + 0xC8) = LO8(ebx);
    MEM8(esi + 0xC9) = LO8(ebx);
    goto loc_001005C8;

loc_001005B8: ;
    _fa = (uint32_t)(MEM32(0x4AD640)) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x4AD640), 1 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001005C8; /* je: equal / zero */

loc_001005C1: ;
    MEM8(esi + 0xC8) = 1;

loc_001005C8: ;
    ecx = MEM32(esi + 0xC4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0010062C; /* je: equal / zero */

loc_001005D2: ;
    MEM8(esi + 0x9C) = LO8(ebx);
    MEM8(esi + 0x9D) = 1;
    PUSH32(esp, 0x001005E4u); sub_000E4A60(); /* call 0x000E4A60 */

loc_001005E4: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0010062C; /* je: equal / zero */

loc_001005E8: ;
    ecx = MEM32(esi + 0xC4);
    _fa = (uint32_t)(MEM8(ecx + 0x54A)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x54A), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00100607; /* je: equal / zero */

loc_001005F6: ;
    PUSH32(esp, ebx);
    ecx = 0x4AD508;
    PUSH32(esp, 0x00100601u); sub_000DA0F0(); /* call 0x000DA0F0 */

loc_00100601: ;
    MEM8(eax + 0x168) = LO8(ebx);

loc_00100607: ;
    ecx = MEM32(esi + 0xC4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    MEM8(esi + 0x9C) = 1;
    MEM8(esi + 0x9D) = 1;
    if (CMP_EQ(_fa, _fb)) goto loc_00100626; /* je: equal / zero */

loc_0010061F: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00100626u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00100626: ;
    MEM32(esi + 0xC4) = ebx;

loc_0010062C: ;
    SET_LO8(eax, MEM8(esi + 0xC8));
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_001008D0
 * Original: 0x001008D0 - 0x001008EE (30 bytes, 11 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001008D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001008D0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x001008D8u); sub_001003C0(); /* call 0x001003C0 */

loc_001008D8: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001008E8; /* je: equal / zero */

loc_001008DF: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001008E5u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_001008E5: ;
    esp = esp + 4;

loc_001008E8: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00101F00
 * Original: 0x00101F00 - 0x00102167 (615 bytes, 154 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00101F00(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00101F00: ;
    esp = esp - 0xC;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    ecx = 0x4AD508;
    PUSH32(esp, 0x00101F11u); sub_000DC900(); /* call 0x000DC900 */

loc_00101F11: ;
    _fa = (uint32_t)(MEM8(esi + 0xE8)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0xE8), LO8(eax) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00101F20; /* je: equal / zero */

loc_00101F19: ;
    ecx = esi;
    PUSH32(esp, 0x00101F20u); sub_00101850(); /* call 0x00101850 */

loc_00101F20: ;
    ecx = esi;
    PUSH32(esp, 0x00101F27u); sub_00100640(); /* call 0x00100640 */

loc_00101F27: ;
    eax = MEM32(esi + 0xB4);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00101F96; /* jle: less or equal (signed <=) */

loc_00101F33: ;
    PUSH32(esp, ebx);
    goto loc_00101F40;

    /* nop */
    /* nop */

loc_00101F40: ;
    eax = MEM32(esi + 0xAC);
    eax = MEM32(eax + edi * 4);
    ecx = MEM32(eax + 0x104);
    edx = MEM32(0x3E25A8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ecx = MEM32(eax + 0x108);
    eax = MEM32(edx + 0x180);
    SET_LO8(ebx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00101F6C; /* jle: less or equal (signed <=) */

loc_00101F6A: ;
    SET_LO8(ebx, 1);

loc_00101F6C: ;
    ecx = MEM32(esi + 0xB8);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00101F78u); sub_000DAAF0(); /* call 0x000DAAF0 */

loc_00101F78: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00101F8A; /* je: equal / zero */

loc_00101F7C: ;
    eax = MEM32(eax + 0x4C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00101F8A; /* je: equal / zero */

loc_00101F83: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    SET_LO8(ecx, (TEST_Z(_fa, _fb)) ? 1 : 0); /* sete */
    MEM8(eax) = LO8(ecx);

loc_00101F8A: ;
    eax = MEM32(esi + 0xB4);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00101F40; /* jl: less (signed <) */

loc_00101F95: ;
    POP32(esp, ebx);

loc_00101F96: ;
    ecx = 0x4AD514;
    PUSH32(esp, 0x00101FA0u); sub_00037210(); /* call 0x00037210 */

loc_00101FA0: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00101FBB; /* jne: not equal / not zero */

loc_00101FA4: ;
    ecx = 0x4AD514;
    PUSH32(esp, 0x00101FAEu); sub_00037250(); /* call 0x00037250 */

loc_00101FAE: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00101FBB; /* jne: not equal / not zero */

loc_00101FB2: ;
    edx = MEM32(esi + 0xB8);
    MEM8(edx + 0x67) = LO8(eax);

loc_00101FBB: ;
    ecx = esi;
    PUSH32(esp, 0x00101FC2u); sub_000DDA90(); /* call 0x000DDA90 */

loc_00101FC2: ;
    ecx = MEM32(esi + 0xC4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00101FD6; /* je: equal / zero */

loc_00101FCC: ;
    eax = MEM32(ecx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0xC;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xC)); return; /* indirect tail jmp */

loc_00101FD6: ;
    SET_LO8(eax, MEM8(esi + 0xD0));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102161; /* je: equal / zero */

loc_00101FE4: ;
    eax = MEM32(esi + 0xE4);
    fp_push(MEMF(eax + 0x288)); /* fld float */
    MEM32(eax + 0x284) = 0x3EB33333;
    fp_top() = fp_top() * MEMF(0x1E2848); /* fmul dword ptr [0x1e2848] */
    PUSH32(esp, 0x1F91EC);
    MEMF(eax + 0x270) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esi + 0xE4);
    MEM32(ecx + 0xD4) = 1;
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, 0x00102026u); sub_000E1620(); /* call 0x000E1620 */

loc_00102026: ;
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, 0x95);
    PUSH32(esp, 0x0010203Au); sub_000E1730(); /* call 0x000E1730 */

loc_0010203A: ;
    fp_top() = fp_top() + MEMF(esp + 0x10); /* fadd dword ptr [esp + 0x10] */
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, 0x95);
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00102052u); sub_000E1800(); /* call 0x000E1800 */

loc_00102052: ;
    eax = MEM32(esp + 8);
    fp_top() = fp_top() + fp_top(); /* fadd st(0), st(0) */
    PUSH32(esp, 0xB4000000u);
    PUSH32(esp, 0xFFB4B4B4u);
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = esi;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    edx = MEM32(esp + 0x14);
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    esp = esp - 8;
    MEMF(esp + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(0x4B6378)); /* fild */
    fp_top() = fp_top() * MEMF(0x1E2848); /* fmul dword ptr [0x1e2848] */
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(0x4B6374)); /* fild */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    fp_top() = fp_top() - MEMF(esp + 0x28); /* fsub dword ptr [esp + 0x28] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x001020A7u); sub_000DDBE0(); /* call 0x000DDBE0 */

loc_001020A7: ;
    fp_push((double)SMEM32(0x4B6378)); /* fild */
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, 0x1E27C0);
    fp_top() = fp_top() * MEMF(0x1E2848); /* fmul dword ptr [0x1e2848] */
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    MEMF(ecx + 0xB0) = (float)fp_top(); fp_pop(); /* fstp */
    edx = MEM32(0x4B6374);
    ecx = MEM32(esi + 0xE4);
    MEM32(esp + 0x10) = edx;
    PUSH32(esp, 0x001020E5u); sub_000E1620(); /* call 0x000E1620 */

loc_001020E5: ;
    fp_push((double)SMEM32(esp + 0xC)); /* fild */
    eax = MEM32(esi + 0xE4);
    PUSH32(esp, 0x95);
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    MEMF(eax + 0xAC) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x00102112u); sub_000E10C0(); /* call 0x000E10C0 */

loc_00102112: ;
    edi = MEM32(esi + 0xE4);
    esp = esp + 8;
    PUSH32(esp, 0x1E27C0);
    ecx = edi;
    PUSH32(esp, 0x00102127u); sub_000E1620(); /* call 0x000E1620 */

loc_00102127: ;
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esi + 0xE4);
    PUSH32(esp, 0x95);
    PUSH32(esp, 0x0010213Bu); sub_000E1730(); /* call 0x000E1730 */

loc_0010213B: ;
    fp_top() = fp_top() + MEMF(esp + 0x10); /* fadd dword ptr [esp + 0x10] */
    edx = esi + 0xD1;
    PUSH32(esp, edx);
    fp_top() = fp_top() + MEMF(edi + 0xAC); /* fadd dword ptr [edi + 0xac] */
    MEMF(edi + 0xAC) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esi + 0xE4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0010215Eu); sub_000E1080(); /* call 0x000E1080 */

loc_0010215E: ;
    esp = esp + 8;

loc_00102161: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00103270
 * Original: 0x00103270 - 0x0010333F (207 bytes, 65 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00103270(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00103270: ;
    esp = esp - 0x24;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x30);
    MEM32(edi + 8) = 0;
    MEM32(edi + 4) = 0;
    MEM32(edi) = 0;
    eax = MEM32(ecx + 4);
    edx = MEM32(eax + 4);
    esi = MEM32(edx + ecx + 0x40);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00103337; /* je: equal / zero */

loc_0010329F: ;
    /* nop */

loc_001032A0: ;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x001032A7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001032A7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 2 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0010332C; /* jne: not equal / not zero */

loc_001032B0: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x245B90);
    PUSH32(esp, 0x245A70);
    PUSH32(esp, 0);
    PUSH32(esp, esi);
    PUSH32(esp, 0x001032C4u); sub_00110786(); /* call 0x00110786 */

loc_001032C4: ;
    esp = esp + 0x14;
    ecx = esp + 0x14;
    PUSH32(esp, ecx);
    ecx = eax;
    PUSH32(esp, 0x001032D3u); sub_000DA950(); /* call 0x000DA950 */

loc_001032D3: ;
    fp_push(MEMF(esp + 0x20)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    fp_push(MEMF(esp + 0x24)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x18); /* fsub dword ptr [esp + 0x18] */
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x28)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x1C); /* fsub dword ptr [esp + 0x1c] */
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi)); /* fcom dword ptr [edi] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00103300; /* jne: not equal / not zero */

loc_001032FC: ;
    MEMF(edi) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_00103302;

loc_00103300: ;
    fp_pop(); /* fstp st(0) */

loc_00103302: ;
    fp_push(MEMF(esp + 0xC)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi + 4)); fp_pop(); /* fcomp dword ptr [edi + 4] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00103317; /* jne: not equal / not zero */

loc_00103310: ;
    edx = MEM32(esp + 0xC);
    MEM32(edi + 4) = edx;

loc_00103317: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edi + 8)); fp_pop(); /* fcomp dword ptr [edi + 8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0010332C; /* jne: not equal / not zero */

loc_00103325: ;
    eax = MEM32(esp + 0x10);
    MEM32(edi + 8) = eax;

loc_0010332C: ;
    esi = MEM32(esi + 0x34);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_001032A0; /* jne: not equal / not zero */

loc_00103337: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x24;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00103530
 * Original: 0x00103530 - 0x001035C3 (147 bytes, 55 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00103530(void)
{
    static RECOMP_TLS uint32_t godzilla_attachment_calls;
    uint32_t godzilla_attachment_owner = ecx;
    uint32_t godzilla_attachment_target = MEM32(esp + 4u);
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00103530: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, 0x48);
    PUSH32(esp, 0x0010353Bu); sub_0010F511(); /* call 0x0010F511 */

loc_0010353B: ;
    ebx = 0; /* xor self */
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00103557; /* je: equal / zero */

loc_00103544: ;
    MEM8(eax) = 1;
    ecx = ecx | 0xFFFFFFFFu;
    MEM32(eax + 4) = ecx;
    MEM32(eax + 8) = ecx;
    MEM32(eax + 0xC) = ecx;
    esi = eax;
    goto loc_00103559;

loc_00103557: ;
    esi = 0; /* xor self */

loc_00103559: ;
    edx = MEM32(esp + 0x14);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x245B90);
    PUSH32(esp, 0x245A70);
    PUSH32(esp, ebx);
    ebp = esi + 0x44;
    PUSH32(esp, edx);
    MEM8(esi + 0x10) = LO8(ebx);
    MEM8(esi + 0x30) = LO8(ebx);
    MEM8(esi + 0x41) = LO8(ebx);
    MEM8(esi + 0x42) = LO8(ebx);
    MEM32(ebp) = 0xFFFFFFFFu;
    PUSH32(esp, 0x00103585u); sub_00110786(); /* call 0x00110786 */

loc_00103585: ;
    esp = esp + 0x14;
    PUSH32(esp, 0x8000);
    ecx = 0x226AC8;
    MEM32(esp + 0x18) = eax;
    PUSH32(esp, 0x0010359Bu); sub_0003BDB0(); /* call 0x0003BDB0 */

loc_0010359B: ;
    edi = eax;
    ++godzilla_attachment_calls;
    if (godzilla_attachment_calls <= 24u) {
        fprintf(stderr,
                "[MENU-ATTACH] #%u factory=%08X target=%08X child=%08X pool=%08X vt=%08X "
                "t4=%08X t8=%08X t10=%08X t1c=%08X t24=%08X\n",
                godzilla_attachment_calls, godzilla_attachment_owner,
                godzilla_attachment_target, esi, edi,
                edi ? MEM32(edi) : 0u,
                MEM32(godzilla_attachment_target + 4u),
                MEM32(godzilla_attachment_target + 8u),
                MEM32(godzilla_attachment_target + 0x10u),
                MEM32(godzilla_attachment_target + 0x1Cu),
                MEM32(godzilla_attachment_target + 0x24u));
    }
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001035BA; /* je: equal / zero */

loc_001035A1: ;
    ecx = MEM32(esp + 0x14);
    PUSH32(esp, edi);
    MEM32(edi + 0x10) = ebp;
    PUSH32(esp, 0x001035AEu); sub_000DA920(); /* call 0x000DA920 */

loc_001035AE: ;
    if (godzilla_attachment_calls <= 24u) {
        fprintf(stderr,
                "[MENU-ATTACH-RESULT] #%u ok=%u pool-vt=%08X "
                "target4=%08X target8=%08X target10=%08X target1c=%08X target24=%08X\n",
                godzilla_attachment_calls, (unsigned)LO8(eax), MEM32(edi),
                MEM32(godzilla_attachment_target + 4u),
                MEM32(godzilla_attachment_target + 8u),
                MEM32(godzilla_attachment_target + 0x10u),
                MEM32(godzilla_attachment_target + 0x1Cu),
                MEM32(godzilla_attachment_target + 0x24u));
    }
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_001035BA; /* jne: not equal / not zero */

loc_001035B2: ;
    eax = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    ecx = edi;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x001035BAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001035BA: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/** Main-loop slot +0x48: convert excess frame time to a scheduler delay and
 * return the residual frame delta on the emulated x87 stack. */
void sub_000128F0(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000128F0: ;
    /* The native host loop is already paced by xbox_irq_wait_for_vblank().
     * Calling the retail Xbox scheduler delay here can park the only game
     * thread indefinitely once the asynchronous DPC clock is active.  Return
     * the same minimum residual delta as the original no-delay branch and let
     * the host vblank remain the single pacing authority. */
    fp_push(MEMF(0x1E1884));
    esp += 8;
    return;

    _fa = (uint32_t)MEM8(ecx + 0x70); _fb = 0x20u;
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_00012934;

loc_000128F6: ;
    fp_push(MEMF(esp + 4));
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x2232F4)); fp_pop();
    eax = (eax & 0xFFFF0000u) |
          (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) |
          (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u :
           g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    _fa = (uint32_t)HI8(eax); _fb = 0x41u;
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_00012934;

loc_00012907: ;
    fp_push(MEMF(esp + 4));
    fp_top() -= MEMF(0x2232F4);
    fp_top() *= MEMF(0x1E188C);
    PUSH32(esp, 0x0001291Cu); sub_0010F038();

loc_0001291C: ;
    ecx = eax;
    MEM32(esp + 4) = eax;
    PUSH32(esp, 0x00012927u); sub_00068E30();

loc_00012927: ;
    fp_push((double)SMEM32(esp + 4));
    fp_top() *= MEMF(0x1E1888);
    esp += 8; return;

loc_00012934: ;
    fp_push(MEMF(0x1E1884));
    esp += 8; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/** Main object event-listener entry used by the global event bus. */
void sub_000128D0(void)
{
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    eax = MEM32(esp + 4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000128DAu); sub_00030D20();

loc_000128DA: ;
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    SET_LO8(eax, TEST_NZ(_fa, _fb) ? 1 : 0);
    esp += 8; return;
}

/** Per-frame main object update for event type 2. */
void sub_00012800(void)
{
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]

    eax = MEM32(0x4B6380);
    esp -= 0x24;
    _fa = (uint32_t)eax; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    PUSH32(esp, esi);
    esi = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_0001286E;

    fp_push(MEMF(eax + 0x4C));
    ecx = eax + 0x54;
    edx = MEM32(ecx);
    MEM32(esp + 0x1C) = edx;
    edx = MEM32(ecx + 4);
    ecx = MEM32(ecx + 8);
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop();
    fp_push(MEMF(eax + 0x50));
    MEM32(esp + 0x20) = edx;
    edx = MEM32(eax + 0x48);
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop();
    fp_push(MEMF(eax + 0x40));
    MEM32(esp + 0x24) = ecx;
    ecx = MEM32(eax + 0x3C);
    PUSH32(esp, 0x1ED77C);
    MEM32(esp + 0x14) = edx;
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop();
    fp_push(MEMF(eax + 0x44));
    edx = esp + 8;
    PUSH32(esp, edx);
    MEM32(esp + 0xC) = ecx;
    eax = esp + 0x18;
    PUSH32(esp, eax);
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    MEMF(esp + 0x1C) = (float)fp_top(); fp_pop();
    ecx = 0x2BF328;
    PUSH32(esp, 0x0001286Eu); sub_0010C800();

loc_0001286E: ;
    ecx = 0x2BF328;
    PUSH32(esp, 0x00012878u); sub_0010CE50();

loc_00012878: ;
    eax = MEM32(esi + 0x90);
    _fa = (uint32_t)HI8(eax); _fb = 1u;
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0001288D;
    ecx = 0x4AD508;
    PUSH32(esp, 0x0001288Du); sub_000DF0C0();

loc_0001288D: ;
    SET_LO8(eax, MEM8(esi + 0x98));
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_000128BE;
    ecx = 0x2C2A58;
    MEM8(esi + 0x98) = 0;
    PUSH32(esp, 0x000128A8u); sub_000126A0();

loc_000128A8: ;
    ecx = 0x2C2A58;
    PUSH32(esp, 0x000128B2u); sub_00012600();

loc_000128B2: ;
    PUSH32(esp, 0xFFFFFFFFu);
    ecx = 0x4AD508;
    PUSH32(esp, 0x000128BEu); sub_000DED00();

loc_000128BE: ;
    POP32(esp, esi);
    esp += 0x24;
    esp += 8; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
}

/** Per-frame main object render/event finalizer for event type 3. */
void sub_0002FF70(void)
{
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]

    SET_LO8(eax, MEM8(0x4B6360));
    esp -= 0x100;
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    PUSH32(esp, esi);
    esi = ecx;
    fprintf(stderr, "[FINALIZER] enter enabled=%02X object=%08X draw=%02X frame=%08X\n",
            MEM8(0x4B6360), esi, MEM8(esi + 0x88), MEM32(esi + 0x30));
    if (TEST_Z(_fa, _fb)) goto loc_0002FFF6;

    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x44); PUSH32(esp, 0x0002FF87u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0002FF87: ;
    fprintf(stderr, "[FINALIZER] eligibility-return eax=%08X esp=%08X\n", eax, esp);
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0002FFF6;
    SET_LO8(eax, MEM8(esi + 0x88));
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0002FFEA;

    eax = MEM32(esi + 0x30);
    _fa = (uint32_t)eax; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    eax = 0x1E4F1C;
    if (TEST_NZ(_fa, _fb)) goto loc_0002FFA6;
    eax = 0x1E2754;

loc_0002FFA6: ;
    fp_push(MEMF(esi + 0x8C));
    PUSH32(esp, eax);
    esp -= 8;
    MEMD(esp) = fp_top(); fp_pop();
    ecx = esp + 0x10;
    PUSH32(esp, 0x1E4F0C);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x0002FFC2u); sub_0010F469();

loc_0002FFC2: ;
    fprintf(stderr, "[FINALIZER] overlay-format-return esp=%08X\n", esp);
    esp += 0x14;
    PUSH32(esp, 0xFFFFFFFFu);
    PUSH32(esp, 0x3DCCCCCD);
    PUSH32(esp, 0x3DCCCCCD);
    edx = esp + 0x10;
    PUSH32(esp, edx);
    ecx = 0x4B6360;
    MEM32(0x3CFDA0) = 0;
    fprintf(stderr, "[FINALIZER] overlay-draw-enter esp=%08X\n", esp);
    PUSH32(esp, 0x0002FFEAu); sub_00108360();

loc_0002FFEA: ;
    fprintf(stderr, "[FINALIZER] present-enter esp=%08X\n", esp);
    PUSH32(esp, 1);
    ecx = 0x4B6360;
    PUSH32(esp, 0x0002FFF6u); sub_00107B50();

loc_0002FFF6: ;
    fprintf(stderr, "[FINALIZER] exit esp=%08X\n", esp);
    POP32(esp, esi);
    esp += 0x100;
    esp += 4; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
}

/** Small event-delta listener at a seeded-disassembly gap. */
void sub_00030D50(void)
{
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]

    SET_LO8(eax, MEM8(ecx + 0x18));
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_00030D69;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)MEM32(eax); _fb = 2u;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_NE(_fa, _fb)) goto loc_00030D69;
    fp_push(MEMF(eax + 4));
    fp_top() += MEMF(ecx + 0xC);
    MEMF(ecx + 0xC) = (float)fp_top(); fp_pop();

loc_00030D69: ;
    SET_LO8(eax, 1);
    esp += 8; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
}

/** Main render-eligibility and debug-overlay callback (vtable slot +0x44). */
void sub_00013AD0(void)
{
    static RECOMP_TLS uint32_t godzilla_movie_manager_renders;
    static RECOMP_TLS uint32_t godzilla_startup_loader_completed;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    PUSH32(esp, ecx);
    MEM32(esp) = ecx;
    PUSH32(esp, ebx);
    ecx = 0x4B6360;
    SET_LO8(ebx, 1);
    PUSH32(esp, 0x00013AE2u); sub_00105F90();

loc_00013AE2: ;
    fprintf(stderr, "[RENDER-BRANCH] begin-return eax=%08X object=%08X state=%08X\n",
            eax, MEM32(esp + 4), MEM32(MEM32(esp + 4) + 0x90));
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_00013AE9;
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return;

loc_00013AE9: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(ecx + 0x90);
    _fa = (uint32_t)HI8(eax); _fb = 8u;
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_00013B19;
    __debugbreak();
    eax = MEM32(0x1E1740);
    PUSH32(esp, 0x80);
    PUSH32(esp, eax);
    PUSH32(esp, 0xFF000040u);
    PUSH32(esp, 7);
    PUSH32(esp, 0);
    ecx = 0x4B6360;
    PUSH32(esp, 0x00013B17u); sub_00105FD0();
    goto loc_00013B31;

loc_00013B19: ;
    _fa = (uint32_t)HI8(eax); _fb = 1u;
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (getenv("GODZILLA_SKIP_MOVIES") &&
        ++godzilla_movie_manager_renders > 6u) {
        uint32_t node = MEM32(0x4AD508 + 0x158);
        uint32_t guard = 0;
        int has_frontend_shell = 0;
        while (node && guard++ < 64u) {
            if (MEM32(node) == 0x001F7E1Cu)
                MEM8(node + 0x1AC) = 1;
            else if (MEM32(node) == 0x001F9220u &&
                     !godzilla_startup_loader_completed) {
                /* This loader is the final startup-movie sentinel.  Pulse it
                 * once to enter the shell.  Reusing the pulse for later
                 * front-end loaders creates an 8 -> 10 reload loop and burns
                 * through the temporary heap instead of waiting for UI. */
                MEM8(node + 0xAC) = 1;
                godzilla_startup_loader_completed = 1;
            }
            else if (MEM32(node) != 0x001F9220u)
                has_frontend_shell = 1;
            node = MEM32(node + 0xA4);
        }
        /* Keep the movie decoders out of the native render path, but do not
         * suppress the ordinary shell object which uses this same manager.
         * Its +8 callback advances async UI construction and emits the menu
         * draw stream; starving it here leaves state 0x10 permanently idle. */
        if (!has_frontend_shell) {
            SET_LO8(ebx, 0);
            goto loc_00013B31;
        }
    }
    if (TEST_Z(_fa, _fb)) goto loc_00013B2C;
    ecx = 0x4AD508;
    fprintf(stderr, "[RENDER-BRANCH] movie-enter state=%08X\n", eax);
    PUSH32(esp, 0x00013B28u); sub_000DDFC0();
    fprintf(stderr, "[RENDER-BRANCH] movie-return eax=%08X\n", eax);
    SET_LO8(ebx, LO8(eax));
    goto loc_00013B31;

loc_00013B2C: ;
    fprintf(stderr, "[RENDER-BRANCH] frontend-enter state=%08X\n", eax);
    PUSH32(esp, 0x00013B31u); sub_000136E0();

loc_00013B31: ;
    fprintf(stderr, "[RENDER-BRANCH] content-return eax=%08X\n", eax);
    ecx = MEM32(esp + 4);
    SET_LO8(edx, MEM8(ecx + 0xA48));
    _fa = (uint32_t)LO8(edx); _fb = (uint32_t)LO8(edx);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    eax = ecx + 0xA48;
    if (TEST_Z(_fa, _fb)) goto loc_00013B67;
    edx = MEM32(ecx + 0xA6C);
    ecx = MEM32(ecx + 0xA68);
    PUSH32(esp, 0xB4787878u);
    PUSH32(esp, edx);
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    ecx = 0x4B6360;
    PUSH32(esp, 0x00013B63u); sub_00108360();
    ecx = MEM32(esp + 4);

loc_00013B67: ;
    SET_LO8(eax, MEM8(0x2249CC));
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_00013B75;
    PUSH32(esp, 0x00013B75u); sub_00013940();

loc_00013B75: ;
    ecx = 0x4B6360;
    fprintf(stderr, "[RENDER-BRANCH] end-enter\n");
    PUSH32(esp, 0x00013B7Fu); sub_00105FB0();
    fprintf(stderr, "[RENDER-BRANCH] end-return eax=%08X\n", eax);
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return;
}

/** Retail event-pump vtable target. The seeded disassembler split the
 * original 0x33550-0x33571 body at 0x33569; keep the real instruction span. */
void sub_00033550(void)
{
    esp = esp - 0x10;
    eax = MEM32(ecx);
    edx = esp;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    MEM32(esp + 4) = 3;
    MEM32(esp + 8) = 0;
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x0003356Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }
loc_0003356D: ;
    esp = esp + 0x10;
    esp += 4; return;
}

/** Event-bus per-frame listener drain used by vtable slot +0x20. */
void sub_00033780(void)
{
    uint32_t ebp;
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_ebp;

loc_00033780: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    ecx = MEM32(edi + 0x248);
    eax = 0;
    _fa = (uint32_t)ecx; _fb = (uint32_t)ecx;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000337B3;

loc_00033791: ;
    ecx = edi + 0x208;
    SET_LO8(edx, 1);

loc_000337A0: ;
    esi = MEM32(ecx);
    MEM8(esi + 8) = LO8(edx);
    esi = MEM32(edi + 0x248);
    eax++;
    ecx += 4;
    _fa = (uint32_t)eax; _fb = (uint32_t)esi;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_L(_fas, _fbs)) goto loc_000337A0;

loc_000337B3: ;
    eax = MEM32(edi + 0x248);
    ebp = 0;
    _fa = (uint32_t)eax; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000337FD;

loc_000337BF: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x14);

loc_000337C4: ;
    esi = MEM32(edi + ebp * 4 + 0x208);
    SET_LO8(ecx, MEM8(esi + 8));
    _fa = (uint32_t)LO8(ecx); _fb = (uint32_t)LO8(ecx);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_000337F7;

loc_000337D2: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    ecx = esi;
    MEM8(esi + 8) = 0;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000337DDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_000337DD: ;
    _fa = (uint32_t)LO8(eax); _fb = (uint32_t)LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_000337FC;

loc_000337E1: ;
    eax = MEM32(edi + 0x248);
    _fa = (uint32_t)ebp; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_GE(_fas, _fbs)) goto loc_000337F4;

loc_000337EB: ;
    _fa = (uint32_t)esi; _fb = (uint32_t)MEM32(edi + ebp * 4 + 0x208);
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_EQ(_fa, _fb)) goto loc_000337F7;

loc_000337F4: ;
    ebp = 0xFFFFFFFFu;

loc_000337F7: ;
    ebp++;
    _fa = (uint32_t)ebp; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_L(_fas, _fbs)) goto loc_000337C4;

loc_000337FC: ;
    POP32(esp, ebx);

loc_000337FD: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    esp += 8; return;
}

/** Retail vtable thunk at slot +0x20. */
void sub_000338C0(void)
{
    g_seh_ebp = g_ebp;
    sub_00033780();
}

/** Movie-manager per-frame child update (vtable slot +0x0c).
 *
 * The seeded recovery identified this retail function but it was omitted from
 * the selected translation set.  The manager owns an array at +4 and a count
 * at +0x0c; each child receives its vtable slot +4 call once per frame.  This
 * is the path used by the startup XMV player from sub_000DDFC0. */
void sub_0011EF70(void)
{
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    eax = MEM32(edi + 0x0C);
    esi = 0;
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0011EF93;

loc_0011EF7F: ;
    eax = MEM32(edi + 4);
    ecx = MEM32(eax + esi * 4);
    edx = MEM32(ecx);
    {
        uint32_t _icall_esp = g_esp;
        uint32_t _icall_target = MEM32(edx + 4);
        PUSH32(esp, 0x0011EF8Bu);
        RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
    }

loc_0011EF8B: ;
    eax = MEM32(edi + 0x0C);
    esi++;
    _fa = esi; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_L(_fas, _fbs)) goto loc_0011EF7F;

loc_0011EF93: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return;
}

/** Select one of the two retail movie path prefixes. */
void sub_0011EF10(void)
{
    eax = MEM32(esp + 4);
    if (eax == 0) {
        eax = 0x00208BCCu;
    } else if (eax == 1) {
        eax = 0x00208BD4u;
    } else {
        eax = 0;
    }
    esp += 8; return;
}

/** Construct and register one XMV player owned by the movie manager. */
void sub_0011F0C0(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    uint32_t trace_id;
    uint32_t trace_name = MEM32(esp + 4);
    uint32_t trace_kind = MEM32(esp + 8);
    uint32_t trace_arg2 = MEM32(esp + 0x0C);
    uint32_t trace_arg3 = MEM32(esp + 0x10);
    static uint32_t trace_count;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    trace_id = ++trace_count;
    if (trace_id <= 16) {
        fprintf(stderr,
                "[XMV-CREATE] #%u enter manager=%08X name=%08X kind=%08X arg2=%08X arg3=%08X count=%u array=%08X ret=%08X src='",
                trace_id, ecx, trace_name, trace_kind, trace_arg2, trace_arg3,
                MEM32(ecx + 0x0C), MEM32(ecx + 4), MEM32(esp));
        for (uint32_t i = 0; i < 96; ++i) {
            uint8_t ch = MEM8(trace_name + i);
            if (ch == 0)
                break;
            fputc((ch >= 0x20 && ch < 0x7F) ? ch : '.', stderr);
        }
        fputs("'\n", stderr);
        fflush(stderr);
    }

    /* Audio-bearing startup movies currently depend on the native APU packet
     * completion clock.  Their decode path works, but completion can return
     * through an unimplemented DPC with a corrupt frontend this-pointer.
     * Preserve the video-only TOHO proof and let the retail frontend take its
     * normal missing-movie fallback for PIPEWORKS through GZINTRO. */
    if (trace_name == 0x001F9308u) {
        fprintf(stderr,
                "[XMV-CREATE] #%u bypassing audio movie until APU completion is native\n",
                trace_id);
        eax = 0;
        esp += 20;
        return;
    }

    esp -= 0x218;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    ecx = MEM32(esp + 0x224);
    eax = esp + 0x0C;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = edi;
    PUSH32(esp, 0x0011F0DEu); sub_0011F580();

loc_0011F0DE: ;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u path-status=%08X resolved='", trace_id, eax);
        for (uint32_t i = 0; i < 96; ++i) {
            uint8_t ch = MEM8(esp + 0x0C + i);
            if (ch == 0)
                break;
            fputc((ch >= 0x20 && ch < 0x7F) ? ch : '.', stderr);
        }
        fputs("'\n", stderr);
        fflush(stderr);
    }
    _fa = eax; _fb = 4;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_NE(_fa, _fb)) goto loc_0011F142;

    PUSH32(esp, 0x160);
    PUSH32(esp, 0x0011F0EDu); sub_0010F511();

loc_0011F0ED: ;
    esp += 4;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u allocation=%08X\n", trace_id, eax);
        fflush(stderr);
    }
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0011F142;

    ecx = eax;
    PUSH32(esp, 0x0011F0FBu); sub_0011F160();

loc_0011F0FB: ;
    esi = eax;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u child=%08X vtable=%08X\n",
                trace_id, esi, esi ? MEM32(esi) : 0);
        fflush(stderr);
    }
    _fa = esi; _fb = esi;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    MEM32(esp + 8) = esi;
    if (TEST_Z(_fa, _fb)) goto loc_0011F142;

    edx = esp + 8;
    PUSH32(esp, edx);
    ecx = edi + 4;
    PUSH32(esp, 0x0011F112u); sub_000DF630();

loc_0011F112: ;
    if (trace_id <= 16) {
        fprintf(stderr,
                "[XMV-CREATE] #%u registered count=%u array=%08X child=%08X\n",
                trace_id, MEM32(edi + 0x0C), MEM32(edi + 4), esi);
        fflush(stderr);
    }
    ecx = MEM32(esp + 0x230);
    edx = MEM32(esp + 0x22C);
    eax = MEM32(esi);
    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, ecx);
        ecx = MEM32(esp + 0x22C);
        PUSH32(esp, edx);
        PUSH32(esp, ecx);
        edx = esp + 0x19;
        PUSH32(esp, edx);
        ecx = esi;
        {
            uint32_t _icall_target = MEM32(eax + 8);
            if (trace_id <= 16) {
                fprintf(stderr, "[XMV-CREATE] #%u init-target=%08X path=%08X\n",
                        trace_id, _icall_target, edx);
                fflush(stderr);
            }
            PUSH32(esp, 0x0011F136u);
            RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
        }
    }

loc_0011F136: ;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u init-result=%08X\n", trace_id, eax);
        fflush(stderr);
    }
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_0011F14F;

    eax = MEM32(esi);
    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, 1);
        ecx = esi;
        {
            uint32_t _icall_target = MEM32(eax);
            PUSH32(esp, 0x0011F142u);
            RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
        }
    }

loc_0011F142: ;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u FAIL final-count=%u\n",
                trace_id, MEM32(edi + 0x0C));
        fflush(stderr);
    }
    POP32(esp, edi);
    eax = 0;
    POP32(esp, esi);
    esp += 0x218;
    esp += 20; return;

loc_0011F14F: ;
    if (trace_id <= 16) {
        fprintf(stderr, "[XMV-CREATE] #%u OK child=%08X final-count=%u\n",
                trace_id, esi, MEM32(edi + 0x0C));
        fflush(stderr);
    }
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 0x218;
    esp += 20; return;
}

/** Advance one XMV player and update its presentation timestamp. */
void sub_0011F200(void)
{
    static RECOMP_TLS uint32_t trace_count;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]

    ++trace_count;
    if (trace_count <= 16u || (trace_count & (trace_count - 1u)) == 0u) {
        fprintf(stderr,
                "[XMV-TICK] #%u object=%08X decoder=%08X surface=%08X "
                "done=%02X error=%02X stream=%08X pts=%08X ret=%08X\n",
                trace_count, ecx, MEM32(ecx + 0x148), MEM32(ecx + 0x14C),
                MEM8(ecx + 0x140), MEM8(ecx + 0x141),
                MEM32(ecx + 0x144), MEM32(ecx + 0x130), MEM32(esp));
        if (MEM32(ecx + 0x148) != 0u) {
            uint32_t decoder = MEM32(ecx + 0x148);
            fprintf(stderr,
                    "[XMV-DECODER] #%u cb=%08X ctx=%08X streams=%08X "
                    "packet=%08X pending=%08X ready=%08X active=%08X eof=%08X "
                    "handle=%08X limit=%08X clock=%08X:%08X\n",
                    trace_count, MEM32(decoder + 0x20), MEM32(decoder + 0x24),
                    MEM32(decoder + 0x48), MEM32(decoder + 0x50),
                    MEM32(decoder + 0x60), MEM32(decoder + 0x68),
                    MEM32(decoder + 0x6C), MEM32(decoder + 0x74),
                    MEM32(decoder + 0x7C), MEM32(decoder + 0x80),
                    MEM32(decoder + 0xB4), MEM32(decoder + 0xB0));
        }
        fflush(stderr);
    }

    esp -= 8;
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x141));
    _fa = LO8(eax); _fb = LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_NZ(_fa, _fb)) goto loc_0011F280;

    edx = MEM32(esi + 0x14C);
    eax = esp + 8;
    PUSH32(esp, eax);
    eax = MEM32(esi + 0x148);
    ecx = esp + 8;
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0011F22Du); sub_001B23BC();

loc_0011F22D: ;
    eax = MEM32(esp + 4);
    if (trace_count <= 16u || (trace_count & (trace_count - 1u)) == 0u) {
        fprintf(stderr,
                "[XMV-TICK] #%u decode-status=%08X aux=%08X decoder=%08X\n",
                trace_count, eax, MEM32(esp + 8), MEM32(esi + 0x148));
        fflush(stderr);
    }
    _fa = eax; _fb = 2;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_NE(_fa, _fb)) goto loc_0011F23F;
    MEM8(esi + 0x141) = 1;
    goto loc_0011F251;

loc_0011F23F: ;
    _fa = eax; _fb = 3;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_NE(_fa, _fb)) goto loc_0011F251;
    ecx = MEM32(0x4BB270);
    edx = MEM32(ecx);
    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, 0xFFFFFFFFu);
        {
            uint32_t _icall_target = MEM32(edx + 0x18);
            PUSH32(esp, 0x0011F251u);
            RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
        }
    }

loc_0011F251: ;
    eax = MEM32(esi + 0x148);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0011F25Du); sub_001B2A39();

loc_0011F25D: ;
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    MEM32(esp + 8) = eax;
    fp_push((double)SMEM32(esp + 8));
    if (CMP_GE(_fas & _fbs, 0)) goto loc_0011F26F;
    fp_top() += MEMF(0x1E17EC);

loc_0011F26F: ;
    fp_top() *= MEMF(0x208C4C);
    PUSH32(esp, 0x0011F27Au); sub_0010F038();

loc_0011F27A: ;
    MEM32(esi + 0x130) = eax;

loc_0011F280: ;
    POP32(esp, esi);
    esp += 8;
    esp += 4; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
}

/** XNET's identity element callback at a three-byte seeded-disassembly gap. */
void sub_001A0EED(void)
{
    eax = ecx;
    esp += 4; return;
}

/**
 * sub_00033810
 * Original: 0x00033810 - 0x00033862 (82 bytes, 31 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 */
void sub_00033810(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00033810: ;
    esp = esp - 0x10;
    eax = MEM32(esp + 0x14);
    PUSH32(esp, esi);
    MEM32(esp + 8) = eax;
    PUSH32(esp, edi);
    esi = ecx;
    edx = MEM32(esi);
    eax = esp + 8;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    MEM32(esp + 0xC) = 2;
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x00033831u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_00033831: ;
    eax = MEM32(esi + 0x204);
    edi = 0;
    _fa = (uint32_t)eax; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0003385A;

loc_0003383D: ;
    PUSH32(esp, ebx);
    ebx = esi + 0x1E4;

loc_00033844: ;
    ecx = MEM32(ebx);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x0003384Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0003384B: ;
    eax = MEM32(esi + 0x204);
    edi++;
    ebx += 4;
    _fa = (uint32_t)edi; _fb = (uint32_t)eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_L(_fas, _fbs)) goto loc_00033844;

loc_00033859: ;
    POP32(esp, ebx);

loc_0003385A: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 0x10;
    esp += 8; return;
}

/**
 * sub_0010F317
 * Original: 0x0010F317 - 0x0010F320 (9 bytes, 4 insns)
 * Category: crt
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0010F317(void)
{

loc_0010F317: ;
    PUSH32(esp, 0x19);
    PUSH32(esp, 0x0010F31Eu); sub_00111C55(); /* call 0x00111C55 */

loc_0010F31E: ;
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_00102D50
 * Original: 0x00102D50 - 0x00102F48 (504 bytes, 132 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00102D50(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    uint32_t saved_this;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00102D50: ;
    esp = esp - 0x10;
    PUSH32(esp, esi);
    esi = ecx;
    saved_this = ecx;
    PUSH32(esp, 0);
    ecx = 0x4AD508;
    PUSH32(esp, 0x00102D62u); sub_000DA0F0(); /* call 0x000DA0F0 */

loc_00102D62: ;
    esi = saved_this;
    SET_LO8(ecx, MEM8(eax + 4));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00102D77; /* jne: not equal / not zero */

loc_00102D69: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x24); PUSH32(esp, 0x00102D72u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00102D72: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 4; return; /* ret */

loc_00102D77: ;
    eax = MEM32(esi + 0xD4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00102D9E; /* jne: not equal / not zero */

loc_00102D81: ;
    ecx = MEM32(esi + 0xD0);
    edx = MEM32(ecx * 4 + 0x2483B8);
    PUSH32(esp, edx);
    ecx = esi;
    PUSH32(esp, 0x00102D96u); sub_00102B00(); /* call 0x00102B00 */

loc_00102D96: ;
    esi = saved_this;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102F43; /* je: equal / zero */

loc_00102D9E: ;
    SET_LO8(eax, MEM8(0x2249CA));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102DE2; /* je: equal / zero */

loc_00102DA7: ;
    eax = MEM32(esi + 0xD4);
    _fa = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu; _fb = (uint32_t)(7) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax), 7 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00102DD4; /* je: equal / zero */

loc_00102DB2: ;
    goto loc_00102DC0;

    /* nop */
    goto loc_00102DC0;

    /* nop */

loc_00102DC0: ;
    ecx = MEM32(esi + 0xD4);
    ecx = ecx + 0xC;
    MEM32(esi + 0xD4) = ecx;
    _fa = (uint32_t)(MEM32(ecx)) & 0xFFFFFFFFu; _fb = (uint32_t)(7) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx), 7 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00102DC0; /* jne: not equal / not zero */

loc_00102DD4: ;
    edx = MEM32(esi + 0xD4);
    PUSH32(esp, edx);
    ecx = esi;
    PUSH32(esp, 0x00102DE2u); sub_00102B00(); /* call 0x00102B00 */

loc_00102DE2: ;
    esi = saved_this;
    eax = MEM32(esi + 0xB8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102E07; /* je: equal / zero */

loc_00102DEC: ;
    ecx = MEM32(esi + 0xC0);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102E07; /* je: equal / zero */

loc_00102DF6: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x1C); PUSH32(esp, 0x00102DFBu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00102DFB: ;
    /* The vtable status method is a real thiscall and therefore preserves
     * ESI.  Some recovered nested audio targets currently leak their scratch
     * ESI into the shared register model; restore the controller's this value
     * at the verified ABI boundary before the remainder of this method. */
    esi = saved_this;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 3 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00102E07; /* jne: not equal / not zero */

loc_00102E00: ;
    MEM8(esi + 0xDC) = 1;

loc_00102E07: ;
    SET_LO8(eax, MEM8(esi + 0xDC));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102E31; /* je: equal / zero */

loc_00102E11: ;
    ecx = MEM32(esi + 0xD4);
    ecx = ecx + 0xC;
    PUSH32(esp, ecx);
    ecx = esi;
    MEM8(esi + 0xDC) = 0;
    PUSH32(esp, 0x00102E29u); sub_00102B00(); /* call 0x00102B00 */

loc_00102E29: ;
    esi = saved_this;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102F43; /* je: equal / zero */

loc_00102E31: ;
    SET_LO8(eax, MEM8(esi + 0xC8));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102F22; /* je: equal / zero */

loc_00102E3F: ;
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2828); /* fmul dword ptr [0x1e2828] */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2824); /* fmul dword ptr [0x1e2824] */
    fp_top() = cos(fp_top()); /* fcos */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2820); /* fmul dword ptr [0x1e2820] */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0xCC)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00102EC2; /* jp: parity */

loc_00102EAC: ;
    edx = MEM32(esi + 0x80);
    MEM32(esi + 0xCC) = edx;
    MEM32(esp + 0x10) = 0;
    goto loc_00102EF1;

loc_00102EC2: ;
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + 0xCC); /* fsub dword ptr [esi + 0xcc] */
    fp_top() = fp_top() * MEMF(0x1E27CC); /* fmul dword ptr [0x1e27cc] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_st1() = fp_st1() * fp_top(); fp_pop(); /* fmulp st(1) */
    MEMF(esp + 0x10) = (float)fp_top(); /* fst */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E16FC)); fp_pop(); /* fcomp dword ptr [0x1e16fc] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00102EF1; /* jne: not equal / not zero */

loc_00102EE9: ;
    MEM32(esp + 0x10) = 0x3F800000;

loc_00102EF1: ;
    ecx = esp + 4;
    PUSH32(esp, 0x00102EFAu); sub_00018E90(); /* call 0x00018E90 */

loc_00102EFA: ;
    esi = saved_this;
    ecx = MEM32(esi + 0xBC);
    MEM32(ecx + 0x108) = eax;
    eax = MEM32(esi + 0xBC);
    edx = MEM32(eax);
    ecx = MEM32(edx + 4);
    MEM8(ecx + eax + 0x48) = 1;
    ecx = esi;
    PUSH32(esp, 0x00102F1Du); sub_000DDA90(); /* call 0x000DDA90 */

loc_00102F1D: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 4; return; /* ret */

loc_00102F22: ;
    ecx = 0x4AD60C;
    PUSH32(esp, 0x00102F2Cu); sub_00036ED0(); /* call 0x00036ED0 */

loc_00102F2C: ;
    esi = saved_this;
    eax = MEM32(esi + 0xBC);
    edx = MEM32(eax);
    ecx = MEM32(edx + 4);
    MEM8(ecx + eax + 0x48) = 0;
    ecx = esi;
    PUSH32(esp, 0x00102F43u); sub_000DDA90(); /* call 0x000DDA90 */

loc_00102F43: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/* Retail vtable predicate: this controller remains active until its explicit
 * transition path says otherwise. */
void sub_001023D0(void)
{
    SET_LO8(eax, 0);
    esp += 8; /* ret 4 */
}

/**
 * sub_000307B0
 * Original: 0x000307B0 - 0x00030C48 (1176 bytes, 373 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000307B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000307B0: ;
    _cf = (int)((uint32_t)(esp) < (uint32_t)(0x3C));
    esp = esp - 0x3C;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    eax = esp + 0x18;
    PUSH32(esp, eax);
    ecx = esp + 0x20;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x1D9974);
    MEM32(esp + 0x20) = esi;
    PUSH32(esp, 0x000307D1u); sub_001DAC04(); /* call 0x001DAC04 */

loc_000307D1: ;
    eax = MEM32(esi + 0x294);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    _cf = 0; /* test clears CF */
    SET_LO8(ebx, (CMP_LE(_fas & _fbs, 0)) ? 1 : 0); /* setle */
    ebp = 0; /* xor self */
    ebx--;
    _cf = 0; /* logical op clears CF */
    ebx = ebx & eax;
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(0x58)) >> 32) & 1);
    esi = esi + 0x58;
    goto loc_000307F0;

    /* nop */
    /* nop */

loc_000307F0: ;
    edx = MEM32(esp + 0x18);
    edi = 1;
    ecx = ebp;
    if (LO8(ecx)) _cf = (int)(((edi) >> (32 - (LO8(ecx)))) & 1);
    edi = edi << LO8(ecx);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edx (32-bit) */
    _cf = 0; /* test clears CF */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    _cf = 0; /* test clears CF */
    MEM8(esi + 0x71) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_0003081A; /* je: equal / zero */

loc_00030809: ;
    edx = MEM32(esi + 0x6C);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00030812u); sub_001DA932(); /* call 0x001DA932 */

loc_00030812: ;
    MEM32(esi + 0x6C) = 0;
    ebx--;

loc_0003081A: ;
    _fa = (uint32_t)(MEM32(esp + 0x1C)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esp + 0x1C), edi (32-bit) */
    _cf = 0; /* test clears CF */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    _cf = 0; /* test clears CF */
    MEM8(esi + 0x70) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_00030866; /* je: equal / zero */

loc_00030828: ;
    PUSH32(esp, 0);
    MEM32(esi + -24) = 0;
    PUSH32(esp, 0);
    eax = esi + -24;
    eax = 0x7F7FFFFF;
    PUSH32(esp, ebp);
    PUSH32(esp, 0x1D9974);
    MEM32(esi + -4) = eax;
    MEM32(esi) = eax;
    MEM32(esi + 4) = eax;
    MEM32(esi + 8) = eax;
    MEM32(esi + 0x74) = 0xFFFFFFFFu;
    PUSH32(esp, 0x00030858u); sub_001DA8DC(); /* call 0x001DA8DC */

loc_00030858: ;
    ecx = esi + 0x52;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    MEM32(esi + 0x6C) = eax;
    PUSH32(esp, 0x00030865u); sub_001DA93E(); /* call 0x001DA93E */

loc_00030865: ;
    ebx++;

loc_00030866: ;
    ebp++;
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(0x94)) >> 32) & 1);
    esi = esi + 0x94;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, 4 (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_L(_fas, _fbs)) goto loc_000307F0; /* jl: less (signed <) */

loc_00030876: ;
    ebp = MEM32(esp + 0x14);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebp + 0x294)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, MEM32(ebp + 0x294) (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_000308D8; /* je: equal / zero */

loc_00030882: ;
    ecx = MEM32(ebp + 0xC4);
    SET_LO8(eax, 0); /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_00030890; /* je: equal / zero */

loc_0003088E: ;
    SET_LO8(eax, 1);

loc_00030890: ;
    ecx = MEM32(ebp + 0x158);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_0003089C; /* je: equal / zero */

loc_0003089A: ;
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | 2);

loc_0003089C: ;
    ecx = MEM32(ebp + 0x1EC);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_000308A8; /* je: equal / zero */

loc_000308A6: ;
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | 4);

loc_000308A8: ;
    ecx = MEM32(ebp + 0x280);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_000308B4; /* je: equal / zero */

loc_000308B2: ;
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | 8);

loc_000308B4: ;
    ecx = MEM32(esp + 0x50);
    MEM8(esp + 0x29) = LO8(eax);
    eax = esp + 0x24;
    MEM32(ebp + 0x294) = ebx;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    MEM32(esp + 0x28) = 1;
    MEM8(esp + 0x2C) = LO8(ebx);
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x000308D8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000308D8: ;
    edi = 0; /* xor self */
    MEM32(esp + 0x10) = 0xFFFFFFFFu;
    MEM32(esp + 0x14) = edi;
    esi = ebp + 0x42;
    /* nop */

loc_000308F0: ;
    eax = MEM32(esi + 0x82);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_00030C24; /* je: equal / zero */

loc_000308FE: ;
    ebx = MEM32(esp + 0x10);
    ecx = esp + 0x34;
    PUSH32(esp, ecx);
    ebx++;
    PUSH32(esp, eax);
    MEM32(esp + 0x18) = ebx;
    PUSH32(esp, 0x00030912u); sub_001DAB1C(); /* call 0x001DAB1C */

loc_00030912: ;
    SET_LO8(eax, MEM8(ebp + 0x299));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    _cf = 0; /* test clears CF */
    MEM32(esp + 0x24) = 0;
    if (TEST_Z(_fa, _fb)) goto loc_0003092C; /* je: equal / zero */

loc_00030924: ;
    edx = ebx;
    MEM32(esp + 0x28) = edx;
    goto loc_00030938;

loc_0003092C: ;
    eax = (uint32_t)(int32_t)SMEM8(edi + ebp + 0x29A);
    MEM32(esp + 0x28) = eax;

loc_00030938: ;
    SET_LO16(eax, MEM16(esi + -2));
    edx = MEM32(esp + 0x38);
    _cf = 0; /* logical op clears CF */
    SET_LO16(eax, LO16(eax) ^ LO16(edx));
    ebx = ZX16(LO16(eax));
    edi = 0x22605C;
    goto loc_00030950;

    /* nop */

loc_00030950: ;
    ecx = MEM32(edi + -4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ebx (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_00030996; /* je: equal / zero */

loc_00030957: ;
    eax = MEM32(edi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x16) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x16 (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    MEM32(esp + 0x2C) = eax;
    edx = ZX16(LO16(edx));
    if (CMP_GE(_fas, _fbs)) goto loc_00030970; /* jge: greater or equal (signed >=) */

loc_00030965: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, edx (32-bit) */
    _cf = 0; /* test clears CF */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    MEM8(esp + 0x30) = LO8(eax);
    goto loc_00030984;

loc_00030970: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, edx (32-bit) */
    _cf = 0; /* test clears CF */
    MEM32(esp + 0x30) = 0x3F800000;
    if (TEST_NZ(_fa, _fb)) goto loc_00030984; /* jne: not equal / not zero */

loc_0003097C: ;
    MEM32(esp + 0x30) = 0;

loc_00030984: ;
    ecx = MEM32(esp + 0x50);
    eax = MEM32(ecx);
    edx = esp + 0x24;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00030992u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030992: ;
    edx = MEM32(esp + 0x38);

loc_00030996: ;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(8)) >> 32) & 1);
    edi = edi + 8;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x22609C) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 0x22609C (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_L(_fas, _fbs)) goto loc_00030950; /* jl: less (signed <) */

loc_000309A1: ;
    edi = 0x22609C;

loc_000309A6: ;
    ecx = MEM32(edi + -4);
    SET_LO8(edx, MEM8(esp + ecx + 0x3A));
    SET_LO8(eax, 0x30);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(edx) (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    SET_LO8(eax, _cf ? 0xFFFFFFFF : 0); /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    eax = eax & 0xFF;
    MEM8(esp + ecx + 0x3A) = LO8(eax);
    _fa = (uint32_t)(MEM8(esi + ecx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + ecx), LO8(eax) (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_000309DE; /* je: equal / zero */

loc_000309C1: ;
    ecx = MEM32(edi);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    _cf = 0; /* test clears CF */
    SET_LO8(edx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    MEM32(esp + 0x2C) = ecx;
    ecx = MEM32(esp + 0x50);
    eax = MEM32(ecx);
    MEM8(esp + 0x30) = LO8(edx);
    edx = esp + 0x24;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x000309DEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000309DE: ;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(8)) >> 32) & 1);
    edi = edi + 8;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2260CC) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 0x2260CC (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_L(_fas, _fbs)) goto loc_000309A6; /* jl: less (signed <) */

loc_000309E9: ;
    fp_push(MEMF(ebp + 8)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    PUSH32(esp, 0x000309F7u); sub_0010F038(); /* call 0x0010F038 */

loc_000309F7: ;
    MEM32(esp + 0x20) = eax;
    edi = 0x2260CC;

loc_00030A00: ;
    SET_LO8(ecx, MEM8(ebp + 4));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    _cf = 0; /* test clears CF */
    eax = MEM32(edi + -4);
    if (TEST_Z(_fa, _fb)) goto loc_00030A22; /* je: equal / zero */

loc_00030A0A: ;
    ecx = ZX8(MEM8(esp + eax + 0x3A));
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x20)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(esp + 0x20) (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    SET_LO8(edx, (CMP_LE(_fas, _fbs)) ? 1 : 0); /* setle */
    SET_LO8(edx, LO8(edx) - 1);
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFF;
    MEM8(esp + eax + 0x3A) = LO8(edx);

loc_00030A22: ;
    SET_LO8(ecx, MEM8(esi + eax));
    ebx = esp + eax + 0x3A;
    SET_LO8(eax, MEM8(ebx));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), LO8(eax) (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030A80; /* je: equal / zero */

loc_00030A2F: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0xFF) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0xFF (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0xFF) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0xFF (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    SET_LO8(ecx, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ecx) (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030A56; /* je: equal / zero */

loc_00030A3E: ;
    edx = MEM32(edi);
    ecx = MEM32(esp + 0x50);
    MEM32(esp + 0x2C) = edx;
    edx = esp + 0x24;
    MEM8(esp + 0x30) = LO8(eax);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00030A56u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030A56: ;
    eax = MEM32(edi + 4);
    MEM32(esp + 0x2C) = eax;
    _fa = (uint32_t)(MEM8(ebx)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebx), 0 (8-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    MEM32(esp + 0x30) = 0;
    if (CMP_EQ(_fa, _fb)) goto loc_00030A72; /* je: equal / zero */

loc_00030A6A: ;
    MEM32(esp + 0x30) = 0x3F800000;

loc_00030A72: ;
    ecx = MEM32(esp + 0x50);
    edx = MEM32(ecx);
    eax = esp + 0x24;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x00030A80u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030A80: ;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(0xC)) >> 32) & 1);
    edi = edi + 0xC;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2260E4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 0x2260E4 (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_L(_fas, _fbs)) goto loc_00030A00; /* jl: less (signed <) */

loc_00030A8F: ;
    SET_LO16(eax, MEM16(esp + 0x42));
    _fa = (uint32_t)(MEM16(esi + 8)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 8), LO16(eax) (16-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030ADE; /* je: equal / zero */

loc_00030A9A: ;
    ecx = MEM32(ebp + 0x2C);
    edx = MEM32(ebp + 0xC);
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + 0x1C);
    PUSH32(esp, edx);
    edx = SX16(LO16(eax));
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00030AAFu); sub_00030350(); /* call 0x00030350 */

loc_00030AAF: ;
    ebx = MEM32(esp + 0x50);
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 0x12)); /* fcom dword ptr [esi + 0x12] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    _cf = 0; /* test clears CF */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_00030ADA; /* jnp: not parity */

loc_00030ABD: ;
    ecx = esp + 0x24;
    MEMF(esi + 0x12) = (float)fp_top(); /* fst */
    eax = MEM32(ebx);
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = ebx;
    MEM32(esp + 0x30) = 0;
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00030AD8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030AD8: ;
    goto loc_00030AE2;

loc_00030ADA: ;
    fp_pop(); /* fstp st(0) */
    goto loc_00030AE2;

loc_00030ADE: ;
    ebx = MEM32(esp + 0x50);

loc_00030AE2: ;
    eax = MEM32(esp + 0x44);
    _fa = (uint32_t)(MEM16(esi + 0xA)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 0xA), LO16(eax) (16-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030B2C; /* je: equal / zero */

loc_00030AEC: ;
    edx = MEM32(ebp + 0x30);
    ecx = MEM32(ebp + 0x10);
    PUSH32(esp, edx);
    edx = MEM32(ebp + 0x20);
    eax = SX16(LO16(eax));
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    _cf = (int)((eax) != 0);
    eax = (uint32_t)(-(int32_t)eax);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00030B03u); sub_00030350(); /* call 0x00030350 */

loc_00030B03: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 0x16)); /* fcom dword ptr [esi + 0x16] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    _cf = 0; /* test clears CF */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_00030B2A; /* jnp: not parity */

loc_00030B0D: ;
    MEMF(esi + 0x16) = (float)fp_top(); /* fst */
    edx = MEM32(ebx);
    eax = esp + 0x24;
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    ecx = ebx;
    MEM32(esp + 0x30) = 1;
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x00030B28u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030B28: ;
    goto loc_00030B2C;

loc_00030B2A: ;
    fp_pop(); /* fstp st(0) */

loc_00030B2C: ;
    eax = MEM32(esp + 0x46);
    _fa = (uint32_t)(MEM16(esi + 0xC)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 0xC), LO16(eax) (16-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030B74; /* je: equal / zero */

loc_00030B36: ;
    ecx = MEM32(ebp + 0x34);
    edx = MEM32(ebp + 0x14);
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + 0x24);
    PUSH32(esp, edx);
    edx = SX16(LO16(eax));
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00030B4Bu); sub_00030350(); /* call 0x00030350 */

loc_00030B4B: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 0x1A)); /* fcom dword ptr [esi + 0x1a] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    _cf = 0; /* test clears CF */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_00030B72; /* jnp: not parity */

loc_00030B55: ;
    ecx = esp + 0x24;
    MEMF(esi + 0x1A) = (float)fp_top(); /* fst */
    eax = MEM32(ebx);
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = ebx;
    MEM32(esp + 0x30) = 2;
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00030B70u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030B70: ;
    goto loc_00030B74;

loc_00030B72: ;
    fp_pop(); /* fstp st(0) */

loc_00030B74: ;
    SET_LO16(edi, MEM16(esp + 0x48));
    _fa = (uint32_t)(MEM16(esi + 0xE)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 0xE), LO16(edi) (16-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030BC2; /* je: equal / zero */

loc_00030B7F: ;
    edx = MEM32(ebp + 0x38);
    eax = MEM32(ebp + 0x18);
    ecx = MEM32(ebp + 0x28);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    edx = SX16(LO16(edi));
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00030B94u); sub_00030350(); /* call 0x00030350 */

loc_00030B94: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 0x1E)); /* fcom dword ptr [esi + 0x1e] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    _cf = 0; /* test clears CF */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_00030BC0; /* jnp: not parity */

loc_00030B9E: ;
    ecx = esp + 0x24;
    MEMF(esi + 0x1E) = (float)fp_top(); /* fst */
    eax = MEM32(ebx);
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = ebx;
    MEM32(esp + 0x30) = 3;
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00030BB9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00030BB9: ;
    SET_LO16(edi, MEM16(esp + 0x48));
    goto loc_00030BC2;

loc_00030BC0: ;
    fp_pop(); /* fstp st(0) */

loc_00030BC2: ;
    edx = MEM32(esp + 0x38);
    eax = MEM32(esp + 0x3C);
    ecx = MEM32(esp + 0x40);
    MEM32(esi + -2) = edx;
    edx = MEM32(esp + 0x44);
    MEM32(esi + 2) = eax;
    eax = MEM32(esi + 0x8A);
    MEM32(esi + 6) = ecx;
    MEM32(esi + 0xA) = edx;
    MEM16(esi + 0xE) = LO16(edi);
    _cf = 0; /* logical op clears CF */
    edi = edi | 0xFFFFFFFFu;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030C24; /* je: equal / zero */

loc_00030BEF: ;
    PUSH32(esp, 0x00030BF4u); sub_00029933(); /* call 0x00029933 */

loc_00030BF4: ;
    ecx = MEM32(esi + 0x8A);
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(eax));
    ecx = ecx - eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    _cf = 0; /* test clears CF */
    if (CMP_G(_fas & _fbs, 0)) goto loc_00030C24; /* jg: greater (signed >) */

loc_00030C00: ;
    eax = MEM32(esi + 0x82);
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    if (CMP_EQ(_fa, _fb)) goto loc_00030C1E; /* je: equal / zero */

loc_00030C0C: ;
    edx = esi + 0x22;
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    MEM16(esi + 0x64) = LO16(ecx);
    MEM16(esi + 0x66) = LO16(ecx);
    PUSH32(esp, 0x00030C1Eu); sub_001DAB88(); /* call 0x001DAB88 */

loc_00030C1E: ;
    MEM32(esi + 0x8A) = edi;

loc_00030C24: ;
    edi = MEM32(esp + 0x14);
    edi++;
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(0x94)) >> 32) & 1);
    esi = esi + 0x94;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 4 (32-bit) */
    _cf = (int)(_fa < _fb); /* cmp: CF */
    MEM32(esp + 0x14) = edi;
    if (CMP_L(_fas, _fbs)) goto loc_000308F0; /* jl: less (signed <) */

loc_00030C3C: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    _cf = (int)((((uint64_t)(esp) + (uint64_t)(0x3C)) >> 32) & 1);
    esp = esp + 0x3C;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_000DBA30
 * Original: 0x000DBA30 - 0x000DBA98 (104 bytes, 37 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBA30(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBA30: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0xC);
    PUSH32(esp, ebp);
    ebp = ecx;
    ecx = MEM32(ebp + 0x158);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    if (TEST_Z(_fa, _fb)) goto loc_000DBA83; /* je: equal / zero */

loc_000DBA48: ;
    goto loc_000DBA50;

    /* nop */

loc_000DBA50: ;
    eax = MEM32(ecx + 0xA4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBA5E; /* je: equal / zero */

loc_000DBA5A: ;
    ecx = eax;
    goto loc_000DBA50;

loc_000DBA5E: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    esi = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_000DBA85; /* je: equal / zero */

loc_000DBA64: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 0x28); PUSH32(esp, 0x000DBA6Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBA6B: ;
    esi = MEM32(ebp + 0x158);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBA83; /* je: equal / zero */

loc_000DBA75: ;
    eax = MEM32(esi + 0xA4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBA85; /* je: equal / zero */

loc_000DBA7F: ;
    esi = eax;
    goto loc_000DBA75;

loc_000DBA83: ;
    esi = 0; /* xor self */

loc_000DBA85: ;
    eax = ebx + -1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(7) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 7 (32-bit) */
    if (CMP_A(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* ja: above (unsigned >) */

loc_000DBA91: ;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(eax * 4 + 0xDBC04)); return; /* indirect tail jmp */

}

/**
 * sub_000EA1B0
 * Original: 0x000EA1B0 - 0x000EA315 (357 bytes, 94 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EA1B0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EA1B0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0xDC));
    ebx = 0; /* xor self */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA27D; /* je: equal / zero */

loc_000EA1C4: ;
    _fa = (uint32_t)(MEM32(esi + 0x1A8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x1A8), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EA27D; /* jne: not equal / not zero */

loc_000EA1D0: ;
    edx = MEM32(esi + 0xAC);
    MEM8(esi + 0xDC) = LO8(ebx);
    eax = 0; /* xor self */
    ecx = esi + 0x108;

loc_000EA1E4: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ecx)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(ecx) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA1F6; /* je: equal / zero */

loc_000EA1E8: ;
    eax++;
    ecx = ecx + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000EA1E4; /* jl: less (signed <) */

loc_000EA1F1: ;
    goto loc_000EA27D;

loc_000EA1F6: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM8(esi + 0xDC) = 1;
    ecx = eax;
    if (CMP_GE(_fas, _fbs)) goto loc_000EA209; /* jge: greater or equal (signed >=) */

loc_000EA203: ;
    ecx = MEM32(0x4B0190);

loc_000EA209: ;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x2BC);
    _fa = (uint32_t)(MEM8(ecx + 0x4B0240)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x4B0240), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA21B; /* je: equal / zero */

loc_000EA217: ;
    ecx = eax;
    goto loc_000EA21E;

loc_000EA21B: ;
    ecx = ecx | 0xFFFFFFFFu;

loc_000EA21E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM32(esi + 0x1A4) = ecx;
    ecx = eax;
    if (CMP_GE(_fas, _fbs)) goto loc_000EA230; /* jge: greater or equal (signed >=) */

loc_000EA22A: ;
    ecx = MEM32(0x4B0190);

loc_000EA230: ;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x2BC);
    MEM8(ecx + 0x4B0240) = LO8(ebx);
    PUSH32(esp, eax);
    ecx = 0x4AE558;
    PUSH32(esp, 0x000EA247u); sub_000E3DA0(); /* call 0x000E3DA0 */

loc_000EA247: ;
    PUSH32(esp, 0x1C70);
    PUSH32(esp, 0x000EA251u); sub_0010F511(); /* call 0x0010F511 */

loc_000EA251: ;
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA261; /* je: equal / zero */

loc_000EA258: ;
    ecx = eax;
    PUSH32(esp, 0x000EA25Fu); sub_000E78A0(); /* call 0x000E78A0 */

loc_000EA25F: ;
    goto loc_000EA263;

loc_000EA261: ;
    eax = 0; /* xor self */

loc_000EA263: ;
    MEM32(esi + 0x1A8) = eax;
    MEM8(eax + 0x54F) = 1;
    MEM8(esi + 0x9C) = LO8(ebx);
    MEM8(esi + 0x9D) = 1;

loc_000EA27D: ;
    ecx = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA2FD; /* je: equal / zero */

loc_000EA287: ;
    PUSH32(esp, 0x000EA28Cu); sub_000E4A60(); /* call 0x000E4A60 */

loc_000EA28C: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EA2FD; /* je: equal / zero */

loc_000EA290: ;
    eax = MEM32(esi + 0x1A8);
    MEM8(esi + 0x1A0) = 1;
    MEM8(esi + 0xDC) = LO8(ebx);
    _fa = (uint32_t)(MEM8(eax + 0x54A)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x54A), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA2BC; /* je: equal / zero */

loc_000EA2AB: ;
    PUSH32(esp, ebx);
    ecx = 0x4AD508;
    PUSH32(esp, 0x000EA2B6u); sub_000DA0F0(); /* call 0x000DA0F0 */

loc_000EA2B6: ;
    MEM8(eax + 0x168) = LO8(ebx);

loc_000EA2BC: ;
    ecx = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(MEM8(ecx + 0x54E)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x54E), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA2E6; /* je: equal / zero */

loc_000EA2CA: ;
    eax = MEM32(esi + 0x1A4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000EA2E0; /* jl: less (signed <) */

loc_000EA2D4: ;
    PUSH32(esp, ebx);
    PUSH32(esp, eax);
    ecx = 0x4AE558;
    PUSH32(esp, 0x000EA2E0u); sub_000E33C0(); /* call 0x000E33C0 */

loc_000EA2E0: ;
    MEM8(esi + 0x1A0) = LO8(ebx);

loc_000EA2E6: ;
    ecx = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA2F7; /* je: equal / zero */

loc_000EA2F0: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x000EA2F7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000EA2F7: ;
    MEM32(esi + 0x1A8) = ebx;

loc_000EA2FD: ;
    _fa = (uint32_t)(MEM8(esi + 0x1A0)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x1A0), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EA30C; /* je: equal / zero */

loc_000EA305: ;
    MEM8(0x4AD672) = 1;

loc_000EA30C: ;
    SET_LO8(eax, MEM8(esi + 0x1A0));
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_000EA9A0
 * Original: 0x000EA9A0 - 0x000EA9A8 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EA9A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000EA9A0: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_00103340(); return; /* tail jmp 0x00103340 */

}

/**
 * sub_000DBA98
 * Original: 0x000DBA98 - 0x000DBAC2 (42 bytes, 21 insns)
 * Category: game_vtable
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBA98(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBA98: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBAA0: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x000DBAAAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBAAA: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBAB0; /* je: equal / zero */

loc_000DBAAE: ;
    edi = 0; /* xor self */

loc_000DBAB0: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x000DBAB9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBAB9: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DBAC2
 * Original: 0x000DBAC2 - 0x000DBAEB (41 bytes, 20 insns)
 * Category: game_vtable
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBAC2(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBAC2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBACA: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x000DBAD4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBAD4: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBADA; /* je: equal / zero */

loc_000DBAD8: ;
    edi = 0; /* xor self */

loc_000DBADA: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0xC); PUSH32(esp, 0x000DBAE2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBAE2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DBAEB
 * Original: 0x000DBAEB - 0x000DBB24 (57 bytes, 26 insns)
 * Category: game_vtable
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBAEB(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBAEB: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBAF3: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x000DBAFDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBAFD: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBB03; /* je: equal / zero */

loc_000DBB01: ;
    edi = 0; /* xor self */

loc_000DBB03: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x24); PUSH32(esp, 0x000DBB0Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBB0B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* jne: not equal / not zero */

loc_000DBB13: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0xC); PUSH32(esp, 0x000DBB1Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBB1B: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DBB24
 * Original: 0x000DBB24 - 0x000DBB91 (109 bytes, 44 insns)
 * Category: game_vtable
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBB24(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBB24: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBB2C: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, edi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x2C); PUSH32(esp, 0x000DBB36u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBB36: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBB3C; /* je: equal / zero */

loc_000DBB3A: ;
    edi = 0; /* xor self */

loc_000DBB3C: ;
    ecx = MEM32(ebp + 0x158);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, esi (32-bit) */
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_000DBB64; /* jne: not equal / not zero */

loc_000DBB47: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x14); PUSH32(esp, 0x000DBB4Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBB4C: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBB54: ;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM8(ebp + 0x168) = 1;
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

loc_000DBB64: ;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x14); PUSH32(esp, 0x000DBB6Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBB6B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBB73: ;
    PUSH32(esp, esi);
    ecx = ebp;
    PUSH32(esp, 0x000DBB7Bu); sub_000DB2A0(); /* call 0x000DB2A0 */

loc_000DBB7B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_000DBBFA(); return; } /* je: equal / zero */

loc_000DBB7F: ;
    PUSH32(esp, 0);
    ecx = eax;
    PUSH32(esp, 0x000DBB88u); sub_000DA460(); /* call 0x000DA460 */

loc_000DBB88: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DBB91
 * Original: 0x000DBB91 - 0x000DBC03 (114 bytes, 39 insns)
 * Category: game_vtable
 * CC: cdecl, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DBB91(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DBB91: ;
    eax = MEM32(ebp + 0x108);
    ebx = MEM32(0x2264BC);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000DBBD8; /* jle: less or equal (signed <=) */

loc_000DBBA3: ;
    edi = ebp + 0x104;
    /* nop */

loc_000DBBB0: ;
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x000DBBB8u); sub_00036980(); /* call 0x00036980 */

loc_000DBBB8: ;
    edx = 1;
    ecx = eax;
    edx = edx << LO8(ecx);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000DBBCD; /* jne: not equal / not zero */

loc_000DBBC5: ;
    PUSH32(esp, eax);
    ecx = edi;
    PUSH32(esp, 0x000DBBCDu); sub_00036D30(); /* call 0x00036D30 */

loc_000DBBCD: ;
    eax = MEM32(ebp + 0x108);
    esi++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000DBBB0; /* jl: less (signed <) */

loc_000DBBD8: ;
    esi = MEM32(ebp + 0x158);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DBBFA; /* je: equal / zero */

loc_000DBBE2: ;
    ecx = MEM32(0x2264B8);
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x18); PUSH32(esp, 0x000DBBF0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DBBF0: ;
    esi = MEM32(esi + 0xA4);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000DBBE2; /* jne: not equal / not zero */

loc_000DBBFA: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00103340
 * Original: 0x00103340 - 0x001034A0 (352 bytes, 118 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00103340(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00103340: ;
    esp = esp - 8;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    edi = ecx;
    ebp = 0; /* xor self */
    ecx = edi + -132;
    PUSH32(esp, ebp);
    MEM32(esp + 0x14) = ebp;
    PUSH32(esp, 0x0010335Au); sub_000DAAF0(); /* call 0x000DAAF0 */

loc_0010335A: ;
    PUSH32(esp, ebp);
    PUSH32(esp, 0x245A8C);
    PUSH32(esp, 0x245A70);
    PUSH32(esp, ebp);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0010336Cu); sub_00110786(); /* call 0x00110786 */

loc_0010336C: ;
    esp = esp + 0x14;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00103392; /* je: equal / zero */

loc_00103373: ;
    ecx = eax + 4;
    PUSH32(esp, ecx);
    ecx = MEM32(eax + 0x104);
    PUSH32(esp, 0x00103382u); sub_000E1750(); /* call 0x000E1750 */

loc_00103382: ;
    fp_top() = MEMF(edi + -8) / fp_top(); /* fdivr dword ptr [edi - 8] */
    PUSH32(esp, 0x0010338Au); sub_0010F038(); /* call 0x0010F038 */

loc_0010338A: ;
    ecx = eax;
    MEM32(esp + 0xC) = ecx;
    goto loc_0010339E;

loc_00103392: ;
    MEM32(esp + 0xC) = 0;
    ecx = MEM32(esp + 0xC);

loc_0010339E: ;
    eax = MEM32(edi + -124);
    _fa = (uint32_t)(MEM32(edi + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edi + -16), eax (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_001033A9; /* jle: less or equal (signed <=) */

loc_001033A6: ;
    MEM32(edi + -16) = eax;

loc_001033A9: ;
    edx = MEM32(edi + -16);
    edx = edx + ecx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_001033B8; /* jl: less (signed <) */

loc_001033B2: ;
    eax = eax - ecx;
    eax++;
    MEM32(edi + -16) = eax;

loc_001033B8: ;
    eax = MEM32(edi + -128);
    ecx = MEM32(eax + 4);
    ebx = MEM32(ecx + edi + -68);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00103497; /* je: equal / zero */

loc_001033CA: ;
    PUSH32(esp, esi);
    goto loc_001033D0;

    /* nop */

loc_001033D0: ;
    edx = MEM32(ebx);
    ecx = ebx;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x001033D7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001033D7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0010348B; /* jne: not equal / not zero */

loc_001033E0: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x245A8C);
    PUSH32(esp, 0x245A70);
    PUSH32(esp, 0);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x001033F4u); sub_00110786(); /* call 0x00110786 */

loc_001033F4: ;
    esi = eax;
    eax = MEM32(edi + -124);
    esp = esp + 0x14;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00103405; /* jne: not equal / not zero */

loc_00103400: ;
    ecx = edi + -80;
    goto loc_00103427;

loc_00103405: ;
    PUSH32(esp, ebp);
    ecx = edi + -132;
    PUSH32(esp, 0x00103411u); sub_000DAAF0(); /* call 0x000DAAF0 */

loc_00103411: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00103424; /* je: equal / zero */

loc_00103415: ;
    eax = MEM32(eax + 0x4C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00103424; /* je: equal / zero */

loc_0010341C: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), 0 (8-bit) */
    ecx = edi + -112;
    if (CMP_NE(_fa, _fb)) goto loc_00103427; /* jne: not equal / not zero */

loc_00103424: ;
    ecx = edi + -96;

loc_00103427: ;
    PUSH32(esp, 0x0010342Cu); sub_00018E90(); /* call 0x00018E90 */

loc_0010342C: ;
    MEM32(esi + 0x108) = eax;
    eax = MEM32(edi + -16);
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00103480; /* jl: less (signed <) */

loc_00103439: ;
    ecx = MEM32(esp + 0x10);
    eax = eax + ecx;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00103480; /* jge: greater or equal (signed >=) */

loc_00103443: ;
    edx = MEM32(esi);
    fp_push(MEMF(esp + 0x14)); /* fld float */
    eax = MEM32(edx + 4);
    MEM8(eax + esi + 0x48) = 1;
    ecx = MEM32(esi);
    edx = MEM32(ecx + 4);
    MEM32(edx + esi + 0x28) = 0;
    eax = MEM32(esi);
    ecx = MEM32(eax + 4);
    edx = esi + 4;
    MEMF(ecx + esi + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esi + 0x104);
    PUSH32(esp, edx);
    PUSH32(esp, 0x00103476u); sub_000E1750(); /* call 0x000E1750 */

loc_00103476: ;
    fp_top() = fp_top() + MEMF(esp + 0x14); /* fadd dword ptr [esp + 0x14] */
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_0010348A;

loc_00103480: ;
    eax = MEM32(esi);
    ecx = MEM32(eax + 4);
    MEM8(ecx + esi + 0x48) = 0;

loc_0010348A: ;
    ebp++;

loc_0010348B: ;
    ebx = MEM32(ebx + 0x34);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_001033D0; /* jne: not equal / not zero */

loc_00103496: ;
    POP32(esp, esi);

loc_00103497: ;
    POP32(esp, edi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_000304B0
 * Original: 0x000304B0 - 0x000304BD (13 bytes, 3 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000304B0(void)
{

loc_000304B0: ;
    SET_LO8(eax, MEM8(esp + 4));
    MEM8(ecx + 0x299) = LO8(eax);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000304C0
 * Original: 0x000304C0 - 0x00030522 (98 bytes, 26 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000304C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000304C0: ;
    eax = MEM32(esp + 4);
    edx = MEM32(eax);
    MEM32(ecx + 0x29A) = edx;
    edx = ecx + 0x29E;
    MEM32(edx) = 0xFFFFFFFFu;
    SET_LO8(edx, MEM8(eax));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_000304E9; /* jl: less (signed <) */

loc_000304DE: ;
    edx = SX8(LO8(edx));
    MEM8(edx + ecx + 0x29E) = 0;

loc_000304E9: ;
    SET_LO8(edx, MEM8(eax + 1));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_000304FB; /* jl: less (signed <) */

loc_000304F0: ;
    edx = SX8(LO8(edx));
    MEM8(edx + ecx + 0x29E) = 1;

loc_000304FB: ;
    SET_LO8(edx, MEM8(eax + 2));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_0003050D; /* jl: less (signed <) */

loc_00030502: ;
    edx = SX8(LO8(edx));
    MEM8(edx + ecx + 0x29E) = 2;

loc_0003050D: ;
    SET_LO8(eax, MEM8(eax + 3));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_0003051F; /* jl: less (signed <) */

loc_00030514: ;
    eax = SX8(LO8(eax));
    MEM8(eax + ecx + 0x29E) = 3;

loc_0003051F: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00030670
 * Original: 0x00030670 - 0x00030697 (39 bytes, 18 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00030670(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00030670: ;
    SET_LO8(eax, MEM8(esp + 4));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    MEM8(edi + 0x298) = LO8(eax);
    if (TEST_NZ(_fa, _fb)) goto loc_00030693; /* jne: not equal / not zero */

loc_00030681: ;
    PUSH32(esp, esi);
    esi = 0; /* xor self */

loc_00030684: ;
    eax = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    ecx = edi;
    { uint32_t _icall_target = MEM32(eax + 0x24); PUSH32(esp, 0x0003068Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003068C: ;
    esi++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 4 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00030684; /* jl: less (signed <) */

loc_00030692: ;
    POP32(esp, esi);

loc_00030693: ;
    POP32(esp, edi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000DEB80
 * Original: 0x000DEB80 - 0x000DEB97 (23 bytes, 5 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DEB80(void)
{

loc_000DEB80: ;
    eax = MEM32(ecx + 0x80);
    edx = eax;
    MEM32(ecx + 0x8C) = eax;
    MEM32(ecx + 0x90) = edx;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000E9E00
 * Original: 0x000E9E00 - 0x000E9E57 (87 bytes, 31 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E9E00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E9E00: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0xEC);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esi) = 0x1F764C;
    if (TEST_Z(_fa, _fb)) goto loc_000E9E19; /* je: equal / zero */

loc_000E9E13: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000E9E19u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000E9E19: ;
    ecx = MEM32(esi + 0xE8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E9E29; /* je: equal / zero */

loc_000E9E23: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x000E9E29u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000E9E29: ;
    ecx = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E9E3A; /* je: equal / zero */

loc_000E9E33: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x000E9E3Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000E9E3A: ;
    ecx = esi;
    PUSH32(esp, 0x000E9E41u); sub_000F2120(); /* call 0x000F2120 */

loc_000E9E41: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E9E51; /* je: equal / zero */

loc_000E9E48: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E9E4Eu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000E9E4E: ;
    esp = esp + 4;

loc_000E9E51: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E9E90
 * Original: 0x000E9E90 - 0x000EA1AE (798 bytes, 225 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E9E90(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000E9E90: ;
    esp = esp - 0x18;
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0x80)); /* fld float */
    eax = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    fp_top() = fp_top() * MEMF(0x1E27F0); /* fmul dword ptr [0x1e27f0] */
    MEM32(esp + 0x18) = esi;
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    if (TEST_Z(_fa, _fb)) goto loc_000E9EC6; /* je: equal / zero */

loc_000E9EBE: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(0x1E1884)); /* fld float */

loc_000E9EC6: ;
    fp_push(MEMF(0x1F7780)); /* fld float */
    eax = MEM32(esi + 0xAC);
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    fp_top() = fp_top() + MEMF(0x1EEF78); /* fadd dword ptr [0x1eef78] */
    edi = MEM32(esi + 0x198);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(0x1F777C)); /* fld float */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() + MEMF(0x1F7778); /* fadd dword ptr [0x1f7778] */
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = fp_top() * MEMF(0x1F7774); /* fmul dword ptr [0x1f7774] */
    fp_top() = fp_top() + MEMF(0x1E28EC); /* fadd dword ptr [0x1e28ec] */
    if (CMP_NE(_fa, _fb)) goto loc_000E9F3D; /* jne: not equal / not zero */

loc_000E9F09: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    PUSH32(esp, 0x000E9F12u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F12: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    ebx = ZX8(LO8(eax));
    ebx = ebx | 0xFFFFFF00u;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9F27u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F27: ;
    eax = ZX8(LO8(eax));
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    ebx = ebx | eax;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9F36u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F36: ;
    ecx = ZX8(LO8(eax));
    ebx = ebx | ecx;
    goto loc_000E9F79;

loc_000E9F3D: ;
    edi = MEM32(esi + 0x19C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000E9F7F; /* jne: not equal / not zero */

loc_000E9F47: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    PUSH32(esp, 0x000E9F50u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F50: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    ebx = ZX8(LO8(eax));
    ebx = ebx | 0xFFFFFF00u;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9F65u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F65: ;
    edx = ZX8(LO8(eax));
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    ebx = ebx | edx;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9F74u); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F74: ;
    eax = ZX8(LO8(eax));
    ebx = ebx | eax;

loc_000E9F79: ;
    MEM32(edi + 0x1BC) = ebx;

loc_000E9F7F: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    edi = 0; /* xor self */
    PUSH32(esp, 0x000E9F8Au); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F8A: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    ebx = ZX8(LO8(eax));
    ebx = ebx | 0xFFFFFF00u;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9F9Fu); sub_0010F038(); /* call 0x0010F038 */

loc_000E9F9F: ;
    ecx = ZX8(LO8(eax));
    ebx = ebx | ecx;
    ebx = ebx << 8;
    PUSH32(esp, 0x000E9FACu); sub_0010F038(); /* call 0x0010F038 */

loc_000E9FAC: ;
    edx = ZX8(LO8(eax));
    ebx = ebx | edx;
    eax = ebx;
    eax = eax >> 0x18;
    MEM32(esp + 0x10) = eax;
    eax = ebx;
    eax = eax >> 0x10;
    MEM32(esp + 0x18) = eax;
    eax = ebx;
    eax = eax >> 8;
    MEM32(esp + 0x1C) = eax;
    eax = ZX8(LO8(ebx));
    MEM32(esp + 0x14) = eax;
    esi = esi + 0x138;
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEMF(esp + 0x20) = (float)fp_top(); fp_pop(); /* fstp */

loc_000E9FE7: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    eax = edi;
    if (CMP_GE(_fas & _fbs, 0)) goto loc_000E9FF2; /* jge: greater or equal (signed >=) */

loc_000E9FED: ;
    eax = MEM32(0x4B0190);

loc_000E9FF2: ;
    ebp = MEM32(esi + -16);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x2BC);
    edx = MEM32(ebp);
    ecx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(eax + 0x4B0240)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x4B0240), LO8(ecx) (8-bit) */
    SET_LO8(ecx, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = ebp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x000EA00Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000EA00E: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    eax = edi;
    if (CMP_GE(_fas & _fbs, 0)) goto loc_000EA019; /* jge: greater or equal (signed >=) */

loc_000EA014: ;
    eax = MEM32(0x4B0190);

loc_000EA019: ;
    ebp = MEM32(esi);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x2BC);
    edx = MEM32(ebp);
    ecx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(eax + 0x4B0240)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x4B0240), LO8(ecx) (8-bit) */
    SET_LO8(ecx, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = ebp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x000EA034u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000EA034: ;
    PUSH32(esp, edi);
    PUSH32(esp, 4);
    ecx = 0x4AE558;
    PUSH32(esp, 0x000EA041u); sub_000E2D90(); /* call 0x000E2D90 */

loc_000EA041: ;
    edx = MEM32(esi + 0x10);
    PUSH32(esp, eax);
    edx = edx + 0xB4;
    PUSH32(esp, 0x1E27B4);
    PUSH32(esp, edx);
    PUSH32(esp, 0x000EA056u); sub_000D9FB0(); /* call 0x000D9FB0 */

loc_000EA056: ;
    esp = esp + 0xC;
    PUSH32(esp, edi);
    PUSH32(esp, 2);
    ecx = 0x4AE558;
    PUSH32(esp, 0x000EA066u); sub_000E2D90(); /* call 0x000E2D90 */

loc_000EA066: ;
    PUSH32(esp, eax);
    eax = MEM32(esi + 0x20);
    eax = eax + 0xB4;
    PUSH32(esp, 0x1E27B4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000EA07Au); sub_000D9FB0(); /* call 0x000D9FB0 */

loc_000EA07A: ;
    esp = esp + 0xC;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    eax = edi;
    if (CMP_GE(_fas & _fbs, 0)) goto loc_000EA088; /* jge: greater or equal (signed >=) */

loc_000EA083: ;
    eax = MEM32(0x4B0190);

loc_000EA088: ;
    edx = MEM32(esi + 0x30);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x2BC);
    ecx = MEM32(eax + 0x4B0244);
    PUSH32(esp, ecx);
    edx = edx + 0xB4;
    PUSH32(esp, 0x1E27B4);
    PUSH32(esp, edx);
    PUSH32(esp, 0x000EA0A9u); sub_000D9FB0(); /* call 0x000D9FB0 */

loc_000EA0A9: ;
    eax = MEM32(esi + 0x40);
    ecx = ebx;
    ecx = ecx >> 0x18;
    MEM32(esp + 0x20) = ecx;
    eax = eax + 0xE8;
    fp_push((double)SMEM32(esp + 0x20)); /* fild */
    edx = ebx;
    edx = edx >> 0x10;
    ecx = ZX8(LO8(edx));
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEM32(esp + 0x20) = ecx;
    edx = ebx;
    MEMF(eax + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    edx = edx >> 8;
    fp_push((double)SMEM32(esp + 0x20)); /* fild */
    ecx = ZX8(LO8(edx));
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEM32(esp + 0x20) = ecx;
    ecx = ZX8(MEM8(esp + 0x1C));
    MEMF(eax) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(esp + 0x20)); /* fild */
    edx = ZX8(LO8(ebx));
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEM32(esp + 0x20) = edx;
    edx = ZX8(MEM8(esp + 0x24));
    MEMF(eax + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(esp + 0x20)); /* fild */
    MEM32(esp + 0x20) = ecx;
    ecx = ZX8(MEM8(esp + 0x28));
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    esp = esp + 0xC;
    esi = esi + 4;
    MEMF(eax + 8) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esi + 0x4C);
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    eax = eax + 0xE8;
    MEM32(esp + 0x14) = edx;
    edx = MEM32(esp + 0x20);
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, 4 (32-bit) */
    MEM32(eax + 8) = edx;
    MEMF(eax + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    MEM32(esp + 0x14) = ecx;
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEMF(eax) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    fp_top() = fp_top() * MEMF(0x1E28B8); /* fmul dword ptr [0x1e28b8] */
    MEMF(eax + 4) = (float)fp_top(); fp_pop(); /* fstp */
    if (CMP_L(_fas, _fbs)) goto loc_000E9FE7; /* jl: less (signed <) */

loc_000EA16C: ;
    esi = MEM32(esp + 0x24);
    ecx = esi;
    PUSH32(esp, 0x000EA177u); sub_000F24D0(); /* call 0x000F24D0 */

loc_000EA177: ;
    ecx = MEM32(esi + 0x1A8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    POP32(esp, edi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_000EA19B; /* je: equal / zero */

loc_000EA184: ;
    MEM8(esi + 0x9C) = 0;
    MEM8(esi + 0x9D) = 1;
    eax = MEM32(ecx);
    POP32(esp, esi);
    esp = esp + 0x18;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xC)); return; /* indirect tail jmp */

loc_000EA19B: ;
    SET_LO8(eax, 1);
    MEM8(esi + 0x9C) = LO8(eax);
    MEM8(esi + 0x9D) = LO8(eax);
    POP32(esp, esi);
    esp = esp + 0x18;
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00013A50
 * Original: 0x00013A50 - 0x00013A74 (36 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00013A50(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00013A50: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00013A58u); sub_0010A7B0(); /* call 0x0010A7B0 */

loc_00013A58: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00013A6E; /* je: equal / zero */

loc_00013A5F: ;
    _fa = (uint32_t)(MEM8(esi + 8)) & 0xFFu; _fb = (uint32_t)(0x18) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 8), 0x18 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00013A6E; /* jne: not equal / not zero */

loc_00013A65: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00013A6Bu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_00013A6B: ;
    esp = esp + 4;

loc_00013A6E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00109D50
 * Original: 0x00109D50 - 0x00109D73 (35 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00109D50(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00109D50: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x14);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00109D5F; /* je: equal / zero */

loc_00109D5A: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00109D5Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00109D5F: ;
    _fa = (uint32_t)(MEM32(0x4B637C)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x4B637C), esi (32-bit) */
    POP32(esp, esi);
    if (CMP_NE(_fa, _fb)) goto loc_00109D72; /* jne: not equal / not zero */

loc_00109D68: ;
    MEM32(0x4B637C) = 0;

loc_00109D72: ;
    esp += 4; return; /* ret */

}

/**
 * sub_001023E0
 * Original: 0x001023E0 - 0x001023E7 (7 bytes, 2 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001023E0(void)
{

loc_001023E0: ;
    SET_LO8(eax, MEM8(ecx + 0xAC));
    esp += 4; return; /* ret */

}

/**
 * sub_0010ED00
 * Original: 0x0010ED00 - 0x0010ED5F (95 bytes, 32 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0010ED00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0010ED00: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM8(esi + 0x44) = 1;
    MEM32(esi) = 0x206338;
    if (TEST_Z(_fa, _fb)) goto loc_0010ED1A; /* je: equal / zero */

loc_0010ED14: ;
    ecx = MEM32(eax);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(ecx + 4); PUSH32(esp, 0x0010ED1Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0010ED1A: ;
    eax = MEM32(esi + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0010ED27; /* je: equal / zero */

loc_0010ED21: ;
    edx = MEM32(eax);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x0010ED27u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0010ED27: ;
    eax = MEM32(esi + 0xC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0010ED34; /* je: equal / zero */

loc_0010ED2E: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0010ED34u); sub_0002A65F(); /* call 0x0002A65F */

loc_0010ED34: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    MEM32(esi + 4) = 0;
    MEM32(esi + 8) = 0;
    MEM32(esi + 0xC) = 0;
    if (TEST_Z(_fa, _fb)) goto loc_0010ED59; /* je: equal / zero */

loc_0010ED50: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0010ED56u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0010ED56: ;
    esp = esp + 4;

loc_0010ED59: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0011F1C0
 * Original: 0x0011F1C0 - 0x0011F1F2 (50 bytes, 17 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011F1C0(void)
{
    static RECOMP_TLS uint32_t trace_count;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0011F1C0: ;
    ++trace_count;
    if (trace_count <= 16u || (trace_count & (trace_count - 1u)) == 0u) {
        fprintf(stderr,
                "[XMV-STATUS] #%u object=%08X decoder=%08X surface=%08X "
                "done=%02X error=%02X stream=%08X pts=%08X ret=%08X\n",
                trace_count, ecx, MEM32(ecx + 0x148), MEM32(ecx + 0x14C),
                MEM8(ecx + 0x140), MEM8(ecx + 0x141),
                MEM32(ecx + 0x144), MEM32(ecx + 0x130), MEM32(esp));
        fflush(stderr);
    }
    eax = MEM32(ecx + 0x148);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0011F1D0; /* jne: not equal / not zero */

loc_0011F1CA: ;
    eax = 4;
    esp += 4; return; /* ret */

loc_0011F1D0: ;
    SET_LO8(eax, MEM8(ecx + 0x141));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011F1E0; /* je: equal / zero */

loc_0011F1DA: ;
    eax = 3;
    esp += 4; return; /* ret */

loc_0011F1E0: ;
    SET_LO8(edx, MEM8(ecx + 0x140));
    eax = 0; /* xor self */
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    eax--;
    eax = eax & 2;
    esp += 4; return; /* ret */

}

/**
 * sub_00155132
 * Original: 0x00155132 - 0x00155159 (39 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00155132(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00155132: ;
    PUSH32(esp, 0x00155137u); sub_00154C4D(); /* call 0x00154C4D */

loc_00155137: ;
    _fa = (uint32_t)(MEM32(0x171EE4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x171EE4), 0 (32-bit) */
    ecx = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_00155159(); return; } /* je: equal / zero */

loc_00155143: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00155152; /* je: equal / zero */

loc_00155147: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155152u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155152: ;
    eax = 0x80004005u;
    g_seh_ebp = ebp; g_ebp = ebp; sub_00155176(); return; /* tail jmp 0x00155176 */

}

/**
 * sub_0015598E
 * Original: 0x0015598E - 0x001559A9 (27 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0015598E(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0015598E: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00155996u); sub_00154DB5(); /* call 0x00154DB5 */

loc_00155996: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001559A3; /* je: equal / zero */

loc_0015599D: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001559A3u); sub_00156BA3(); /* call 0x00156BA3 */

loc_001559A3: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001B1AF4
 * Original: 0x001B1AF4 - 0x001B1B2D (57 bytes, 15 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1AF4(void)
{
    static RECOMP_TLS uint32_t trace_count;
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001B1AF4: ;
    ++trace_count;
    if (trace_count <= 16u || (trace_count & (trace_count - 1u)) == 0u) {
        fprintf(stderr,
                "[XMV-STREAM] #%u decoder=%08X file-off=%08X:%08X bytes=%08X "
                "ret=%08X\n",
                trace_count, MEM32(esp + 4), MEM32(esp + 0xC),
                MEM32(esp + 8), MEM32(esp + 0x10), MEM32(esp));
        fflush(stderr);
    }
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x14);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B86(); return; } /* je: equal / zero */

loc_001B1B01: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(esp + 0xC);
    MEM32(eax + 0x94) = ecx;
    ecx = MEM32(esp + 0x10);
    edx = ecx;
    edx = (uint32_t)((int32_t)(int32_t)edx >> 0x1F);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax + 0x80)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, MEM32(eax + 0x80) (32-bit) */
    MEM32(eax + 0x98) = ecx;
    if (CMP_BE(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B2D(); return; } /* jbe: below or equal (unsigned <=) */

loc_001B1B26: ;
    eax = 0x80004005u;
    g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B89(); return; /* tail jmp 0x001B1B89 */

}

/**
 * sub_00155159
 * Original: 0x00155159 - 0x00155179 (32 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00155159(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00155159: ;
    eax = MEM32(esp + 4);
    MEM32(eax + 4) = MEM32(eax + 4) + 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    PUSH32(esp, esi);
    esi = MEM32(eax + 4);
    if (TEST_Z(_fa, _fb)) goto loc_00155173; /* je: equal / zero */

loc_00155168: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155173u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155173: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00155176
 * Original: 0x00155176 - 0x00155179 (3 bytes, 1 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00155176(void)
{

loc_00155176: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001B1B2D
 * Original: 0x001B1B2D - 0x001B1B75 (72 bytes, 24 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1B2D(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001B1B2D: ;
    PUSH32(esp, edi);
    ecx = eax + 0x88;
    edi = MEM32(ecx);
    MEM32(ecx) = MEM32(ecx) & 0;
    ecx = eax + 0x8C;
    PUSH32(esp, ecx);
    PUSH32(esp, 0);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(eax + 0x7C));
    edx = eax + 0x84;
    MEM32(edx) = edi;
    PUSH32(esp, 0x001B1B54u); sub_00118679(); /* call 0x00118679 */

loc_001B1B54: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, edi);
    if (TEST_NZ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B86(); return; } /* jne: not equal / not zero */

loc_001B1B59: ;
    PUSH32(esp, 0x001B1B5Eu); sub_0002A76D(); /* call 0x0002A76D */

loc_001B1B5E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x3E5) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x3E5 (32-bit) */
    if (CMP_EQ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B86(); return; } /* je: equal / zero */

loc_001B1B65: ;
    PUSH32(esp, 0x001B1B6Au); sub_0002A76D(); /* call 0x0002A76D */

loc_001B1B6A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_G(_fas & _fbs, 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B75(); return; } /* jg: greater (signed >) */

loc_001B1B6E: ;
    PUSH32(esp, 0x001B1B73u); sub_0002A76D(); /* call 0x0002A76D */

loc_001B1B73: ;
    g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B89(); return; /* tail jmp 0x001B1B89 */

}

/**
 * sub_001B1B86
 * Original: 0x001B1B86 - 0x001B1B8D (7 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1B86(void)
{

loc_001B1B86: ;
    eax = 0; /* xor self */
    eax++;
    POP32(esp, esi);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_001B1B89
 * Original: 0x001B1B89 - 0x001B1B8D (4 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1B89(void)
{

loc_001B1B89: ;
    POP32(esp, esi);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_001B1B75
 * Original: 0x001B1B75 - 0x001B1B86 (17 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1B75(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_001B1B75: ;
    PUSH32(esp, 0x001B1B7Au); sub_0002A76D(); /* call 0x0002A76D */

loc_001B1B7A: ;
    eax = eax & 0xFFFF;
    eax = eax | 0x80070000u;
    g_seh_ebp = ebp; g_ebp = ebp; sub_001B1B89(); return; /* tail jmp 0x001B1B89 */

}

/**
 * sub_00129750
 * Original: 0x00129750 - 0x00129798 (72 bytes, 18 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00129750(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00129750: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    eax = MEM32(esi + 0xA0);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, edi);
    edi = MEM32(esi);
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_00129860(); return; } /* je: equal / zero */

loc_00129766: ;
    eax = MEM32(edi + 0x140);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_00129860(); return; } /* je: equal / zero */

loc_00129774: ;
    ecx = MEM32(esi + 8);
    ecx = ecx & 0xC0000000u;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x80000000u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x80000000u (32-bit) */
    if (CMP_NE(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_00129798(); return; } /* jne: not equal / not zero */

loc_00129785: ;
    _fa = (uint32_t)(MEM32(esi + 0x1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x200000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esi + 0x1B4), 0x200000 (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_00129798(); return; } /* je: equal / zero */

loc_00129791: ;
    eax = 1;
    g_seh_ebp = ebp; g_ebp = ebp; sub_0012979A(); return; /* tail jmp 0x0012979A */

}

/**
 * sub_00129798
 * Original: 0x00129798 - 0x00129860 (200 bytes, 51 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00129798(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00129798: ;
    eax = 0; /* xor self */
    edx = MEM32(esi + 0xA4);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0012983E; /* jne: not equal / not zero */

loc_001297A8: ;
    _fa = (uint32_t)(MEM32(esi + 0x1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esi + 0x1B4), 0x1000000 (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_001297BC; /* jne: not equal / not zero */

loc_001297B4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012983E; /* je: equal / zero */

loc_001297BC: ;
    _fa = (uint32_t)(MEM32(edi + 0x100)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(edi + 0x100), 0x1000000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012983E; /* je: equal / zero */

loc_001297C8: ;
    SET_LO16(edx, 0x80C0);
    SET_LO8(eax, godzilla_xbox_video_port80c0(MEM32(esi + 0x1C0)));
    eax = eax >> 5;
    eax = ~eax;
    eax = eax & 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x40000000 (32-bit) */
    MEM32(esi + 0x1D0) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_001297F0; /* jne: not equal / not zero */

loc_001297E3: ;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    SET_LO8(ecx, (TEST_Z(_fa, _fb)) ? 1 : 0); /* sete */
    MEM32(esi + 0x1D0) = ecx;

loc_001297F0: ;
    eax = MEM32(esi + 0x1BC);
    eax = eax & 1;
    edx = eax + eax * 2 + 0x5D;
    MEM32(esi + 0xA4) = 1;
    _fa = (uint32_t)(MEM32(esi + edx * 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + edx * 4), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00129831; /* je: equal / zero */

loc_0012980D: ;
    ecx = MEM32(esi + 0x1C0);
    eax = eax + eax * 2;
    edx = MEM32(esi + eax * 4 + 0x178);
    eax = esi + eax * 4;
    ecx++;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ecx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00129831; /* jne: not equal / not zero */

loc_00129825: ;
    edx = MEM32(eax + 0x17C);
    MEM32(0x1363CC) = edx;

loc_00129831: ;
    eax = MEM32(0x1363CC);
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x0012983Eu); sub_0012CA20(); /* call 0x0012CA20 */

loc_0012983E: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    esi = esi + 0x84;
    PUSH32(esp, esi);
    MEM32(edi + 0x140) = 0;
    { uint32_t _icall_target = MEM32(0x1E12E0); PUSH32(esp, 0x00129859u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00129859: ;
    POP32(esp, edi);
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0012979A
 * Original: 0x0012979A - 0x00129860 (198 bytes, 50 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012979A(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012979A: ;
    edx = MEM32(esi + 0xA4);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0012983E; /* jne: not equal / not zero */

loc_001297A8: ;
    _fa = (uint32_t)(MEM32(esi + 0x1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esi + 0x1B4), 0x1000000 (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_001297BC; /* jne: not equal / not zero */

loc_001297B4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012983E; /* je: equal / zero */

loc_001297BC: ;
    _fa = (uint32_t)(MEM32(edi + 0x100)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(edi + 0x100), 0x1000000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012983E; /* je: equal / zero */

loc_001297C8: ;
    SET_LO16(edx, 0x80C0);
    SET_LO8(eax, godzilla_xbox_video_port80c0(MEM32(esi + 0x1C0)));
    eax = eax >> 5;
    eax = ~eax;
    eax = eax & 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x40000000 (32-bit) */
    MEM32(esi + 0x1D0) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_001297F0; /* jne: not equal / not zero */

loc_001297E3: ;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    SET_LO8(ecx, (TEST_Z(_fa, _fb)) ? 1 : 0); /* sete */
    MEM32(esi + 0x1D0) = ecx;

loc_001297F0: ;
    eax = MEM32(esi + 0x1BC);
    eax = eax & 1;
    edx = eax + eax * 2 + 0x5D;
    MEM32(esi + 0xA4) = 1;
    _fa = (uint32_t)(MEM32(esi + edx * 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + edx * 4), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00129831; /* je: equal / zero */

loc_0012980D: ;
    ecx = MEM32(esi + 0x1C0);
    eax = eax + eax * 2;
    edx = MEM32(esi + eax * 4 + 0x178);
    eax = esi + eax * 4;
    ecx++;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ecx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00129831; /* jne: not equal / not zero */

loc_00129825: ;
    edx = MEM32(eax + 0x17C);
    MEM32(0x1363CC) = edx;

loc_00129831: ;
    eax = MEM32(0x1363CC);
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x0012983Eu); sub_0012CA20(); /* call 0x0012CA20 */

loc_0012983E: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    esi = esi + 0x84;
    PUSH32(esp, esi);
    MEM32(edi + 0x140) = 0;
    { uint32_t _icall_target = MEM32(0x1E12E0); PUSH32(esp, 0x00129859u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00129859: ;
    POP32(esp, edi);
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0012983E
 * Original: 0x0012983E - 0x00129860 (34 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012983E(void)
{

loc_0012983E: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    esi = esi + 0x84;
    PUSH32(esp, esi);
    MEM32(edi + 0x140) = 0;
    { uint32_t _icall_target = MEM32(0x1E12E0); PUSH32(esp, 0x00129859u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00129859: ;
    POP32(esp, edi);
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00129860
 * Original: 0x00129860 - 0x00129867 (7 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00129860(void)
{

loc_00129860: ;
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0012A190
 * Original: 0x0012A190 - 0x0012A1F7 (103 bytes, 30 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012A190(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012A190: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0xC);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ebx);
    /* nop */
    esi = MEM32(edi + 0x100);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x1000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A1B9; /* je: equal / zero */

loc_0012A1B0: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1B7u); sub_00129F50(); /* call 0x00129F50 */

loc_0012A1B7: ;
    ebp = eax;

loc_0012A1B9: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFEFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0xFFFFEFFFu (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A246(); return; } /* je: equal / zero */

loc_0012A1C5: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x100000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A1D6; /* je: equal / zero */

loc_0012A1CD: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1D4u); sub_00129A50(); /* call 0x00129A50 */

loc_0012A1D4: ;
    ebp = ebp | eax;

loc_0012A1D6: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x1000000 (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A218(); return; } /* je: equal / zero */

loc_0012A1DE: ;
    eax = MEM32(ebx + 0x820);
    eax = eax | MEM32(ebx + 0x824);
    if ((eax != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A200(); return; } /* jne: not equal / not zero */

loc_0012A1EC: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1F3u); sub_00129940(); /* call 0x00129940 */

loc_0012A1F3: ;
    ebp = ebp | eax;
    g_seh_ebp = ebp; g_ebp = ebp; sub_0012A218(); return; /* tail jmp 0x0012A218 */

}

/**
 * sub_0012A200
 * Original: 0x0012A200 - 0x0012A267 (103 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012A200(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012A200: ;
    MEM32(edi + 0x600100) = 1;
    esi = MEM32(edi + 0x100);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x1000000 (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0012A200; /* jne: not equal / not zero */

loc_0012A218: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x100 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A229; /* je: equal / zero */

loc_0012A220: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A227u); sub_0012A000(); /* call 0x0012A000 */

loc_0012A227: ;
    ebp = ebp | eax;

loc_0012A229: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x10000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A246; /* je: equal / zero */

loc_0012A231: ;
    eax = MEM32(ebx);
    _fa = (uint32_t)(MEM8(eax + 0x8100)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 0x8100), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A246; /* je: equal / zero */

loc_0012A23C: ;
    MEM32(eax + 0x8100) = 1;

loc_0012A246: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_NZ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A1A0(); return; } /* jne: not equal / not zero */

loc_0012A24E: ;
    ecx = MEM32(ebx + 0xB4);
    MEM32(ebx + 0xA4) = ebp;
    MEM32(edi + 0x140) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_0012A218
 * Original: 0x0012A218 - 0x0012A267 (79 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012A218(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012A218: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x100 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A229; /* je: equal / zero */

loc_0012A220: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A227u); sub_0012A000(); /* call 0x0012A000 */

loc_0012A227: ;
    ebp = ebp | eax;

loc_0012A229: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x10000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A246; /* je: equal / zero */

loc_0012A231: ;
    eax = MEM32(ebx);
    _fa = (uint32_t)(MEM8(eax + 0x8100)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 0x8100), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A246; /* je: equal / zero */

loc_0012A23C: ;
    MEM32(eax + 0x8100) = 1;

loc_0012A246: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_NZ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A1A0(); return; } /* jne: not equal / not zero */

loc_0012A24E: ;
    ecx = MEM32(ebx + 0xB4);
    MEM32(ebx + 0xA4) = ebp;
    MEM32(edi + 0x140) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_0012A246
 * Original: 0x0012A246 - 0x0012A267 (33 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012A246(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012A246: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_NZ(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A1A0(); return; } /* jne: not equal / not zero */

loc_0012A24E: ;
    ecx = MEM32(ebx + 0xB4);
    MEM32(ebx + 0xA4) = ebp;
    MEM32(edi + 0x140) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_0012A1A0
 * Original: 0x0012A1A0 - 0x0012A1F7 (87 bytes, 23 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0012A1A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0012A1A0: ;
    esi = MEM32(edi + 0x100);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x1000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A1B9; /* je: equal / zero */

loc_0012A1B0: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1B7u); sub_00129F50(); /* call 0x00129F50 */

loc_0012A1B7: ;
    ebp = eax;

loc_0012A1B9: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFEFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0xFFFFEFFFu (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A246(); return; } /* je: equal / zero */

loc_0012A1C5: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x100000 (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012A1D6; /* je: equal / zero */

loc_0012A1CD: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1D4u); sub_00129A50(); /* call 0x00129A50 */

loc_0012A1D4: ;
    ebp = ebp | eax;

loc_0012A1D6: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, 0x1000000 (32-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A218(); return; } /* je: equal / zero */

loc_0012A1DE: ;
    eax = MEM32(ebx + 0x820);
    eax = eax | MEM32(ebx + 0x824);
    if ((eax != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_0012A200(); return; } /* jne: not equal / not zero */

loc_0012A1EC: ;
    ecx = ebx;
    PUSH32(esp, 0x0012A1F3u); sub_00129940(); /* call 0x00129940 */

loc_0012A1F3: ;
    ebp = ebp | eax;
    g_seh_ebp = ebp; g_ebp = ebp; sub_0012A218(); return; /* tail jmp 0x0012A218 */

}

/**
 * sub_001A3AB7
 * Original: 0x001A3AB7 - 0x001A3AC3 (12 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001A3AB7(void)
{

loc_001A3AB7: ;
    ecx = MEM32(esp + 8);
    PUSH32(esp, 0x001A3AC0u); sub_001A388D(); /* call 0x001A388D */

loc_001A3AC0: ;
    esp += 20; return; /* ret 16 */

}

/**
 * sub_001A3D84
 * Original: 0x001A3D84 - 0x001A3DAC (40 bytes, 14 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001A3D84(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001A3D84: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    eax = MEM32(esi + 0x10);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001A3DA8; /* je: equal / zero */

loc_001A3D90: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x1E12C4); PUSH32(esp, 0x001A3D9Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001A3D9B: ;
    ecx = MEM32(esi + 0x10);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x1E127C); PUSH32(esp, 0x001A3DA4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001A3DA4: ;
    MEM32(esi + 0x10) = MEM32(esi + 0x10) & 0;

loc_001A3DA8: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001AA633
 * Original: 0x001AA633 - 0x001AA64D (26 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA633(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001AA633: ;
    SET_LO8(edx, MEM8(ecx + 0x8C0));
    eax = ZX8(LO8(edx));
    eax--;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x14) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x14 (32-bit) */
    if (CMP_A(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001AA885(); return; } /* ja: above (unsigned >) */

loc_001AA646: ;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(eax * 4 + 0x1AA888)); return; /* indirect tail jmp */

}

/**
 * sub_001AA885
 * Original: 0x001AA885 - 0x001AA888 (3 bytes, 1 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA885(void)
{

loc_001AA885: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001AA6E3
 * Original: 0x001AA6E3 - 0x001AA6FA (23 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA6E3(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _cf = 0; /* carry flag */

loc_001AA6E3: ;
    SET_LO8(eax, MEM8(ecx + 0x8C4));
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) & 0x10);
    _cf = (int)((LO8(eax)) != 0);
    SET_LO8(eax, (uint32_t)(-(int32_t)LO8(eax)));
    SET_LO8(eax, _cf ? 0xFFFFFFFF : 0); /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) & 0xFE);
    PUSH32(esp, 0);
    _cf = (int)((((uint64_t)(LO8(eax)) + (uint64_t)(9)) >> 8) & 1);
    SET_LO8(eax, LO8(eax) + 9);
    g_seh_ebp = ebp; g_ebp = ebp; sub_001AA832(); return; /* tail jmp 0x001AA832 */

}

/**
 * sub_001AA832
 * Original: 0x001AA832 - 0x001AA835 (3 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA832(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_001AA832: ;
    PUSH32(esp, eax);
    g_seh_ebp = ebp; g_ebp = ebp; sub_001AA880(); return; /* tail jmp 0x001AA880 */

}

/**
 * sub_001AA880
 * Original: 0x001AA880 - 0x001AA888 (8 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA880(void)
{

loc_001AA880: ;
    PUSH32(esp, 0x001AA885u); sub_001A8FC6(); /* call 0x001A8FC6 */

loc_001AA885: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001AA710
 * Original: 0x001AA710 - 0x001AA738 (40 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA710(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001AA710: ;
    SET_LO8(eax, MEM8(ecx + 0x8C1));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx + 0x19)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx + 0x19) (8-bit) */
    if (CMP_B(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001AA87D(); return; } /* jb: below (unsigned <) */

loc_001AA71F: ;
    _fa = (uint32_t)(MEM8(ecx + 0x8C4)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ecx + 0x8C4), 0x10 (8-bit) */
    if (TEST_Z(_fa, _fb)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001AA738(); return; } /* je: equal / zero */

loc_001AA728: ;
    MEM8(ecx + 0xA71) = MEM8(ecx + 0xA71) | 8;
    PUSH32(esp, 0);
    PUSH32(esp, 0xC);
    g_seh_ebp = ebp; g_ebp = ebp; sub_001AA880(); return; /* tail jmp 0x001AA880 */

}

/**
 * sub_001AA738
 * Original: 0x001AA738 - 0x001AA746 (14 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA738(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_001AA738: ;
    MEM8(ecx + 0xA73) = MEM8(ecx + 0xA73) | 0xC0;
    eax = 0; /* xor self */
    g_seh_ebp = ebp; g_ebp = ebp; sub_001AA831(); return; /* tail jmp 0x001AA831 */

}

/**
 * sub_001AA831
 * Original: 0x001AA831 - 0x001AA835 (4 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA831(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_001AA831: ;
    PUSH32(esp, eax);
    PUSH32(esp, eax);
    g_seh_ebp = ebp; g_ebp = ebp; sub_001AA880(); return; /* tail jmp 0x001AA880 */

}

/**
 * sub_001AA87D
 * Original: 0x001AA87D - 0x001AA888 (11 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001AA87D(void)
{

loc_001AA87D: ;
    PUSH32(esp, 1);
    PUSH32(esp, edx);
    PUSH32(esp, 0x001AA885u); sub_001A8FC6(); /* call 0x001A8FC6 */

loc_001AA885: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001B13CB
 * Original: 0x001B13CB - 0x001B13D7 (12 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B13CB(void)
{

loc_001B13CB: ;
    ecx = MEM32(esp + 8);
    PUSH32(esp, 0x001B13D4u); sub_001B1286(); /* call 0x001B1286 */

loc_001B13D4: ;
    esp += 20; return; /* ret 16 */

}

/**
 * sub_001B15B6
 * Original: 0x001B15B6 - 0x001B160F (89 bytes, 32 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15B6(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15B6: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B1573
 * Original: 0x001B1573 - 0x001B160F (156 bytes, 58 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1573(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B1573: ;
    /* prefetchnta: cache hint */
    /* prefetchnta: cache hint */
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 4);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 8);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0xC);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x10);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) goto loc_001B1573; /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B157F
 * Original: 0x001B157F - 0x001B160F (144 bytes, 54 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B157F(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B157F: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 4);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 8);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0xC);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x10);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B1584
 * Original: 0x001B1584 - 0x001B160F (139 bytes, 52 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1584(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B1584: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 8);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0xC);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x10);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B1589
 * Original: 0x001B1589 - 0x001B160F (134 bytes, 50 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1589(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B1589: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0xC);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x10);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B158E
 * Original: 0x001B158E - 0x001B160F (129 bytes, 48 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B158E(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B158E: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x10);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B1593
 * Original: 0x001B1593 - 0x001B160F (124 bytes, 46 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1593(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B1593: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x14);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B1598
 * Original: 0x001B1598 - 0x001B160F (119 bytes, 44 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B1598(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B1598: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x18);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B159D
 * Original: 0x001B159D - 0x001B160F (114 bytes, 42 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B159D(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B159D: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x1C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15A2
 * Original: 0x001B15A2 - 0x001B160F (109 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15A2(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15A2: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x20);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15A7
 * Original: 0x001B15A7 - 0x001B160F (104 bytes, 38 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15A7(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15A7: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x24);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15AC
 * Original: 0x001B15AC - 0x001B160F (99 bytes, 36 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15AC(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15AC: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x28);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15B1
 * Original: 0x001B15B1 - 0x001B160F (94 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15B1(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15B1: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x2C);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x30);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15BB
 * Original: 0x001B15BB - 0x001B160F (84 bytes, 30 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15BB(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15BB: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x34);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15C0
 * Original: 0x001B15C0 - 0x001B160F (79 bytes, 28 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15C0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x38);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_001B15C5
 * Original: 0x001B15C5 - 0x001B160F (74 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001B15C5(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_001B15C5: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = MEM32(esi + 0x3C);
    esi = esi + 0x40;
    ecx--;
    if ((ecx != 0)) { g_seh_ebp = ebp; g_ebp = ebp; sub_001B1573(); return; } /* jne: not equal / not zero */

loc_001B15D0: ;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    edx = 0;
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(edx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ecx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B15E8; /* je: equal / zero */

loc_001B15E2: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esi))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esi));
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */

loc_001B15E8: ;
    ecx = eax;
    ecx = ROR32(ecx, 0x10);
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(ecx)) >> 32) & 1);
    eax = eax + ecx;
    ebx = MEM32(esp + 0x10);
    if (0x10) _cf = (int)(((eax) >> ((0x10) - 1)) & 1);
    eax = eax >> 0x10;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 1 (32-bit) */
    _cf = 0; /* test clears CF */
    if (TEST_Z(_fa, _fb)) goto loc_001B1602; /* je: equal / zero */

loc_001B15FE: ;
    SET_LO16(eax, ROR32(LO16(eax), 8));

loc_001B1602: ;
    _cf = (int)((((uint64_t)(LO16(eax)) + (uint64_t)(MEM16(esp + 0xC))) >> 16) & 1);
    SET_LO16(eax, LO16(eax) + MEM16(esp + 0xC));
    POP32(esp, esi);
    { uint64_t _t = (uint64_t)(eax) + (uint64_t)(0) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); eax = (uint32_t)_t; }  /* adc */
    POP32(esp, ebx);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_0011F530
 * Original: 0x0011F530 - 0x0011F580 (80 bytes, 26 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011F530(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0011F530: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0x148);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi) = 0x208C2C;
    if (TEST_Z(_fa, _fb)) goto loc_0011F563; /* je: equal / zero */

loc_0011F543: ;
    eax = MEM32(esi + 0x14C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011F553; /* je: equal / zero */

loc_0011F54D: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0011F553u); sub_00128F50(); /* call 0x00128F50 */

loc_0011F553: ;
    eax = MEM32(esi + 0x148);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011F563; /* je: equal / zero */

loc_0011F55D: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0011F563u); sub_001B20D1(); /* call 0x001B20D1 */

loc_0011F563: ;
    ecx = esi;
    PUSH32(esp, 0x0011F56Au); sub_0011F9F0(); /* call 0x0011F9F0 */

loc_0011F56A: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011F57A; /* je: equal / zero */

loc_0011F571: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0011F577u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0011F577: ;
    esp = esp + 4;

loc_0011F57A: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00154BFD
 * Original: 0x00154BFD - 0x00154C0A (13 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00154BFD(void)
{

loc_00154BFD: ;
    eax = MEM32(esp + 4);
    MEM32(eax + 4) = MEM32(eax + 4) + 1;
    eax = MEM32(eax + 4);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001552F5
 * Original: 0x001552F5 - 0x0015533C (71 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001552F5(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001552F5: ;
    PUSH32(esp, 0x001552FAu); sub_00154C4D(); /* call 0x00154C4D */

loc_001552FA: ;
    _fa = (uint32_t)(MEM32(0x171EE4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x171EE4), 0 (32-bit) */
    ecx = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_0015531C; /* je: equal / zero */

loc_00155306: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00155315; /* je: equal / zero */

loc_0015530A: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155315u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155315: ;
    eax = 0x80004005u;
    goto loc_00155339;

loc_0015531C: ;
    eax = MEM32(esp + 4);
    MEM32(eax + 8) = MEM32(eax + 8) + 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    PUSH32(esp, esi);
    esi = MEM32(eax + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00155336; /* je: equal / zero */

loc_0015532B: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155336u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155336: ;
    eax = esi;
    POP32(esp, esi);

loc_00155339: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0015533C
 * Original: 0x0015533C - 0x0015538A (78 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0015533C(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0015533C: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00155342u); sub_00154C4D(); /* call 0x00154C4D */

loc_00155342: ;
    _fa = (uint32_t)(MEM32(0x171EE4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x171EE4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_00155364; /* je: equal / zero */

loc_0015534E: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0015535D; /* je: equal / zero */

loc_00155352: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x0015535Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0015535D: ;
    eax = 0x80004005u;
    goto loc_00155386;

loc_00155364: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, edi);
    eax = eax + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00155372u); sub_00154C0A(); /* call 0x00154C0A */

loc_00155372: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00155383; /* je: equal / zero */

loc_00155378: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155383u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155383: ;
    eax = edi;
    POP32(esp, edi);

loc_00155386: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00159900
 * Original: 0x00159900 - 0x0015992F (47 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00159900(void)
{

loc_00159900: ;
    eax = MEM32(esp + 4);
    edx = MEM32(esp + 8);
    eax = eax << 5;
    eax = eax + ecx + 0xD8;
    MEM32(eax + 0x18) = edx;
    edx = MEM32(esp + 0xC);
    MEM32(eax + 0x1C) = edx;
    edx = MEM32(esp + 0x10);
    MEM32(eax + 0x14) = edx;
    ecx = MEM32(ecx + 8);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0015992Cu); sub_00159234(); /* call 0x00159234 */

loc_0015992C: ;
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00159EE5
 * Original: 0x00159EE5 - 0x00159FD4 (239 bytes, 74 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00159EE5(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00159EE5: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi + 0x12));
    PUSH32(esp, edi);
    eax = eax & 1;
    edi = eax;
    if ((eax == 0)) goto loc_00159F17; /* je: equal / zero */

loc_00159EF5: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x00159EFCu); sub_00159C2B(); /* call 0x00159C2B */

loc_00159EFC: ;
    eax = MEM32(esi + 0x88);
    eax = ZX8(MEM8(eax + 0xE));
    eax--;
    eax = (uint32_t)((int32_t)(int32_t)eax >> 1);
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x64)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 0x64) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00159F17; /* je: equal / zero */

loc_00159F10: ;
    ecx = esi;
    PUSH32(esp, 0x00159F17u); sub_001598C0(); /* call 0x001598C0 */

loc_00159F17: ;
    ecx = esi;
    PUSH32(esp, 0x00159F1Eu); sub_0015A33F(); /* call 0x0015A33F */

loc_00159F1E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00159FD1; /* jl: less (signed <) */

loc_00159F26: ;
    edx = MEM32(esi + 0x88);
    ecx = ZX16(MEM16(edx + 0xC));
    ecx--;
    PUSH32(esp, ebx);
    if ((ecx == 0)) goto loc_00159F51; /* je: equal / zero */

loc_00159F34: ;
    ecx = ecx - 0x68;
    if ((ecx != 0)) goto loc_00159F89; /* jne: not equal / not zero */

loc_00159F39: ;
    ecx = esi + 0x8C;
    ebx = MEM32(ecx);
    ebx = ebx & 0xFFFEFFFFu;
    ebx = ebx | 0x20000;

loc_00159F4D: ;
    MEM32(ecx) = ebx;
    goto loc_00159F89;

loc_00159F51: ;
    SET_LO8(ecx, MEM8(edx + 0xF));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 8 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00159F82; /* je: equal / zero */

loc_00159F59: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x10 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00159F6C; /* je: equal / zero */

loc_00159F5E: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x20 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00159F89; /* jne: not equal / not zero */

loc_00159F63: ;
    MEM8(esi + 0x8E) = MEM8(esi + 0x8E) | 3;
    goto loc_00159F89;

loc_00159F6C: ;
    ecx = esi + 0x8C;
    ebx = MEM32(ecx);
    ebx = ebx & 0xFFFDFFFFu;
    ebx = ebx | 0x10000;
    goto loc_00159F4D;

loc_00159F82: ;
    MEM8(esi + 0x8E) = MEM8(esi + 0x8E) & 0xFC;

loc_00159F89: ;
    ecx = ZX8(MEM8(edx + 0xE));
    ecx--;
    ecx = ecx << 0x12;
    ecx = ecx ^ MEM32(esi + 0x8C);
    POP32(esp, ebx);
    ecx = ecx & 0x7C0000;
    MEM32(esi + 0x8C) = MEM32(esi + 0x8C) ^ ecx;
    _fa = (uint32_t)(MEM8(edx + 0xE)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx + 0xE), 1 (8-bit) */
    ecx = MEM32(esi + 0x8C);
    if (CMP_BE(_fa, _fb)) goto loc_00159FB8; /* jbe: below or equal (unsigned <=) */

loc_00159FB0: ;
    ecx = ecx | 0x800000;
    goto loc_00159FBE;

loc_00159FB8: ;
    ecx = ecx & 0xFF7FFFFFu;

loc_00159FBE: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(esi + 0x8C) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_00159FD1; /* je: equal / zero */

loc_00159FC8: ;
    POP32(esp, edi);
    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp; g_ebp = ebp; sub_0015AFCF(); return; /* tail jmp 0x0015AFCF */

loc_00159FD1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_000DFB90
 * Original: 0x000DFB90 - 0x000DFB98 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DFB90(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000DFB90: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000DD4D0(); return; /* tail jmp 0x000DD4D0 */

}

/**
 * sub_0015A130
 * Original: 0x0015A130 - 0x0015A17B (75 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0015A130(void)
{
    int _flags = 0; /* fallback flag var */

loc_0015A130: ;
    eax = MEM32(esp + 4);
    eax = eax - 0;
    if ((eax == 0)) goto loc_0015A173; /* je: equal / zero */

loc_0015A139: ;
    eax--;
    if ((eax == 0)) goto loc_0015A16C; /* je: equal / zero */

loc_0015A13C: ;
    eax--;
    if ((eax == 0)) goto loc_0015A165; /* je: equal / zero */

loc_0015A13F: ;
    eax--;
    if ((eax == 0)) goto loc_0015A15E; /* je: equal / zero */

loc_0015A142: ;
    eax--;
    if ((eax == 0)) goto loc_0015A153; /* je: equal / zero */

loc_0015A145: ;
    eax--;
    if ((eax != 0)) goto loc_0015A178; /* jne: not equal / not zero */

loc_0015A148: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x0015A151u); sub_0015A0A2(); /* call 0x0015A0A2 */

loc_0015A151: ;
    goto loc_0015A178;

loc_0015A153: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x0015A15Cu); sub_00159541(); /* call 0x00159541 */

loc_0015A15C: ;
    goto loc_0015A178;

loc_0015A15E: ;
    PUSH32(esp, 0x0015A163u); sub_00159D0C(); /* call 0x00159D0C */

loc_0015A163: ;
    goto loc_0015A178;

loc_0015A165: ;
    PUSH32(esp, 0x0015A16Au); sub_00159B0F(); /* call 0x00159B0F */

loc_0015A16A: ;
    goto loc_0015A178;

loc_0015A16C: ;
    PUSH32(esp, 0x0015A171u); sub_001598C0(); /* call 0x001598C0 */

loc_0015A171: ;
    goto loc_0015A178;

loc_0015A173: ;
    PUSH32(esp, 0x0015A178u); sub_0015AB6F(); /* call 0x0015AB6F */

loc_0015A178: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DD4D0
 * Original: 0x000DD4D0 - 0x000DD508 (56 bytes, 19 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DD4D0(void)
{

loc_000DD4D0: ;
    esp = esp - 0x30;
    PUSH32(esp, esi);
    esi = ecx;
    edx = MEM32(esi + -8);
    ecx = MEM32(esp + 0x38);
    eax = esp + 4;
    PUSH32(esp, eax);
    eax = MEM32(edx + 4);
    PUSH32(esp, ecx);
    ecx = eax + esi + -8;
    PUSH32(esp, 0x000DD4EFu); sub_000DAC00(); /* call 0x000DAC00 */

loc_000DD4EF: ;
    PUSH32(esp, 1);
    ecx = esp + 8;
    PUSH32(esp, ecx);
    ecx = esi + -144;
    PUSH32(esp, 0x000DD501u); sub_0002F260(); /* call 0x0002F260 */

loc_000DD501: ;
    POP32(esp, esi);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0011EEF0
 * Original: 0x0011EEF0 - 0x0011EF0F (31 bytes, 10 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011EEF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0011EEF0: ;
    eax = MEM32(ecx + 0x18);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011EF03; /* je: equal / zero */

loc_0011EEF7: ;
    edx = MEM32(ecx + 0x14);
    ecx = MEM32(esp + 4);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = eax; PUSH32(esp, 0x0011EF00u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0011EF00: ;
    esp += 8; return; /* ret 4 */

loc_0011EF03: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, 0x0011EF0Cu); sub_000301C0(); /* call 0x000301C0 */

loc_0011EF0C: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001553F1
 * Original: 0x001553F1 - 0x0015543E (77 bytes, 24 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001553F1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001553F1: ;
    /* Companion XMV DirectSound packet-release method.  The hardware path
     * reports DSERR_ALLOCATED without an MCPX voice; packet retirement is
     * emulated in the decoder, so releasing an emulated packet succeeds. */
    eax = 0;
    esp += 8; return; /* ret 4 */

#if 0
    PUSH32(esp, esi);
    PUSH32(esp, 0x001553F7u); sub_00154C4D(); /* call 0x00154C4D */

loc_001553F7: ;
    _fa = (uint32_t)(MEM32(0x171EE4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x171EE4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_00155419; /* je: equal / zero */

loc_00155403: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00155412; /* je: equal / zero */

loc_00155407: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155412u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155412: ;
    eax = 0x80004005u;
    goto loc_0015543A;

loc_00155419: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(eax + 0x24);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00155426u); sub_00159B37(); /* call 0x00159B37 */

loc_00155426: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00155437; /* je: equal / zero */

loc_0015542C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x00155437u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00155437: ;
    eax = edi;
    POP32(esp, edi);

loc_0015543A: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */
#endif

}

/**
 * sub_00155489
 * Original: 0x00155489 - 0x001554DA (81 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00155489(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00155489: ;
    /* Native XMV fallback: this is the DirectSound packet-status method.  Its
     * retail implementation reaches MCPX voice accounting and returns
     * DSERR_ALLOCATED (0x88780032) because no native APU voices exist yet.
     * XMV packets are retired by the decoder fallback, so report S_OK here. */
    /* arg1 points at the caller's packet-completion word.  The retail method
     * clears bit zero once the voice has released the packet; without that
     * out-parameter update sub_001B20D1 deliberately retries forever. */
    if (MEM32(esp + 8) != 0)
        MEM8(MEM32(esp + 8) + 2) = MEM8(MEM32(esp + 8) + 2) & 0xFEu;
    eax = 0;
    esp += 12; return; /* ret 8 */

#if 0
    PUSH32(esp, esi);
    PUSH32(esp, 0x0015548Fu); sub_00154C4D(); /* call 0x00154C4D */

loc_0015548F: ;
    _fa = (uint32_t)(MEM32(0x171EE4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x171EE4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_001554B1; /* je: equal / zero */

loc_0015549B: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001554AA; /* je: equal / zero */

loc_0015549F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x001554AAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001554AA: ;
    eax = 0x80004005u;
    goto loc_001554D6;

loc_001554B1: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(eax + 0x24);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(esp + 0x10));
    PUSH32(esp, 0x001554C2u); sub_001595B3(); /* call 0x001595B3 */

loc_001554C2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_001554D3; /* je: equal / zero */

loc_001554C8: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x171EF0);
    { uint32_t _icall_target = MEM32(0x1E1230); PUSH32(esp, 0x001554D3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001554D3: ;
    eax = edi;
    POP32(esp, edi);

loc_001554D6: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */
#endif

}

/**
 * sub_00159E00
 * Original: 0x00159E00 - 0x00159E88 (136 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00159E00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00159E00: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = esi + 0x68;
    PUSH32(esp, 3);
    ecx = edi;
    PUSH32(esp, 0x00159E10u); sub_0015942A(); /* call 0x0015942A */

loc_00159E10: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00159E3F; /* je: equal / zero */

loc_00159E14: ;
    eax = MEM32(edi);
    MEM8(eax + 0x3F) = 0x80;
    eax = esi + 0x12;
    _fa = (uint32_t)(MEM16(eax)) & 0xFFFFu; _fb = (uint32_t)(0x1000) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test MEM16(eax), 0x1000 (16-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00159E34; /* je: equal / zero */

loc_00159E24: ;
    MEM16(eax) = MEM16(eax) & 0xEFFF;
    SET_LO16(ecx, MEM16(eax));
    SET_LO16(ecx, LO16(ecx) | 0x2000);
    MEM16(eax) = LO16(ecx);

loc_00159E34: ;
    PUSH32(esp, 1);
    ecx = esi;
    PUSH32(esp, 0x00159E3Du); sub_00159C2B(); /* call 0x00159C2B */

loc_00159E3D: ;
    goto loc_00159E82;

loc_00159E3F: ;
    SET_LO8(eax, MEM8(esi + 0x12));
    SET_LO8(eax, LO8(eax) & 3);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 3 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00159E82; /* jne: not equal / not zero */

loc_00159E48: ;
    ecx = esi;
    PUSH32(esp, 0x00159E4Fu); sub_00159D1C(); /* call 0x00159D1C */

loc_00159E4F: ;
    SET_LO8(eax, LO8(eax) & 3);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00159E82; /* jne: not equal / not zero */

loc_00159E55: ;
    _fa = (uint32_t)(MEM32(esi + 0x19C)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x19C), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00159E82; /* jne: not equal / not zero */

loc_00159E5E: ;
    _fa = (uint32_t)(MEM16(esi + 0x12)) & 0xFFFFu; _fb = (uint32_t)(0x2800) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test MEM16(esi + 0x12), 0x2800 (16-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00159E6F; /* je: equal / zero */

loc_00159E66: ;
    ecx = esi;
    PUSH32(esp, 0x00159E6Du); sub_0015960D(); /* call 0x0015960D */

loc_00159E6D: ;
    goto loc_00159E82;

loc_00159E6F: ;
    eax = 0x400;
    _fa = (uint32_t)(MEM16(esi + 0x12)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test MEM16(esi + 0x12), LO16(eax) (16-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00159E82; /* jne: not equal / not zero */

loc_00159E7A: ;
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x00159E82u); sub_0015ABC9(); /* call 0x0015ABC9 */

loc_00159E82: ;
    eax = 0; /* xor self */
    POP32(esp, edi);
    eax++;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_000DE5C0
 * Original: 0x000DE5C0 - 0x000DE5C8 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DE5C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000DE5C0: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000DD430(); return; /* tail jmp 0x000DD430 */

}

/**
 * sub_000EA980
 * Original: 0x000EA980 - 0x000EA996 (22 bytes, 12 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EA980(void)
{

loc_000EA980: ;
    ecx = ecx - MEM32(ecx + -4);
    goto loc_000EA990;

    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */
    __debugbreak(); /* int3 */

loc_000EA990: ;
    MEM32(ecx + -20) = MEM32(ecx + -20) + 1;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000EF780
 * Original: 0x000EF780 - 0x000EFC4C (1228 bytes, 315 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EF780(void)
{
    static RECOMP_TLS uint32_t godzilla_frontend_updates;
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000EF780: ;
    esp = esp - 0x18;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0x80)); /* fld float */
    SET_LO8(ebx, 1);
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esi + 0x248)); fp_pop(); /* fcomp dword ptr [esi + 0x248] */
    PUSH32(esp, edi);
    if (getenv("GODZILLA_SKIP_MOVIES") && ++godzilla_frontend_updates > 5u) {
        /* The retail update sets this once its timed startup presentation has
         * completed.  XMV-less boot has no decoder clock to finish the wait,
         * so emit the same completion state after preserving the first five
         * real updates which construct and draw the initial shell screen. */
        MEM8(esi + 0x1AC) = 1;
        POP32(esp, edi);
        POP32(esp, esi);
        POP32(esp, ebx);
        esp = esp + 0x18;
        esp += 4; return;
    }
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(HI8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), HI8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000EF7A2; /* jne: not equal / not zero */

loc_000EF79C: ;
    MEM8(esi + 0x1AC) = LO8(ebx);

loc_000EF7A2: ;
    edi = MEM32(esi + 0x1E0);
    fp_push(MEMF(esi + 0x248)); /* fld float */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    fp_top() = fp_top() - MEMF(esi + 0x80); /* fsub dword ptr [esi + 0x80] */
    if (TEST_Z(_fa, _fb)) goto loc_000EF82F; /* je: equal / zero */

loc_000EF7B8: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E16FC)); /* fcom dword ptr [0x1e16fc] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000EF82F; /* jp: parity */

loc_000EF7C5: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); /* fcom dword ptr [0x1e1884] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000EF7DA; /* jp: parity */

loc_000EF7D2: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(0x1E1884)); /* fld float */

loc_000EF7DA: ;
    fp_push(MEMF(0x1E16FC)); /* fld float */
    fp_top() = fp_top() - fp_st1(); /* fsub st(1) */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    PUSH32(esp, 0x000EF7EDu); sub_0010F038(); /* call 0x0010F038 */

loc_000EF7ED: ;
    fp_pop(); /* fstp st(0) */
    ecx = MEM32(edi + 0x14);
    eax = ZX8(LO8(eax));
    eax = eax << 0x18;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EF806; /* jne: not equal / not zero */

loc_000EF7FC: ;
    SET_LO8(ecx, MEM8(edi + 0x82));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EF817; /* je: equal / zero */

loc_000EF806: ;
    ecx = edi;
    MEM8(edi + 0x82) = 0;
    MEM32(edi + 0x14) = eax;
    PUSH32(esp, 0x000EF817u); sub_0002F320(); /* call 0x0002F320 */

loc_000EF817: ;
    eax = MEM32(esi + 0x1E0);
    ecx = MEM32(eax + 0x88);
    edx = MEM32(ecx + 4);
    MEM8(edx + eax + 0xD0) = LO8(ebx);
    goto loc_000EF831;

loc_000EF82F: ;
    fp_pop(); /* fstp st(0) */

loc_000EF831: ;
    edx = 0; /* xor self */
    eax = esi + 0x1E8;
    /* nop */

loc_000EF840: ;
    ecx = 0; /* xor self */

loc_000EF842: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x1B0)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(esi + 0x1B0) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EF859; /* jne: not equal / not zero */

loc_000EF84A: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x1C8)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esi + 0x1C8) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EF859; /* jne: not equal / not zero */

loc_000EF852: ;
    edi = MEM32(eax);
    MEM8(edi + 0x48) = LO8(ebx);
    goto loc_000EF85F;

loc_000EF859: ;
    edi = MEM32(eax);
    MEM8(edi + 0x48) = 0;

loc_000EF85F: ;
    ecx++;
    eax = eax + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 3 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000EF842; /* jl: less (signed <) */

loc_000EF868: ;
    edx++;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(7) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 7 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000EF840; /* jl: less (signed <) */

loc_000EF86E: ;
    SET_LO8(eax, MEM8(esi + 0x244));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000EF886; /* jne: not equal / not zero */

loc_000EF878: ;
    eax = MEM32(esi + 0x1C4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_000EF886; /* jge: greater or equal (signed >=) */

loc_000EF882: ;
    eax = 0; /* xor self */
    goto loc_000EF88B;

loc_000EF886: ;
    eax = 2;

loc_000EF88B: ;
    ecx = MEM32(esi + 0x1D0);
    MEM32(ecx + 0x7C) = eax;
    edx = MEM32(esi + 0x1D4);
    MEM32(edx + 0x7C) = eax;
    ecx = MEM32(esi + 0x1D8);
    MEM32(ecx + 0x7C) = eax;
    edx = MEM32(esi + 0x1DC);
    MEM32(edx + 0x7C) = eax;
    eax = MEM32(esi + 0x23C);
    ecx = MEM32(eax);
    edx = MEM32(ecx + 4);
    PUSH32(esp, ebp);
    ebp = 0; /* xor self */
    MEM8(edx + eax + 0x48) = 0;
    MEM32(esp + 0x10) = ebp;
    ebx = ebx | 0xFFFFFFFFu;
    /* nop */

loc_000EF8D0: ;
    eax = MEM32(esi + 0x1C8);
    edx = MEM32(esi + 0x1B0);
    eax = eax + eax * 2;
    eax = eax + edx;
    eax = eax + eax * 2;
    ecx = MEM32(esi + eax * 4 + 0xB0);
    eax = MEM32(esi + 0x1C4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    edi = MEM32(ecx + ebp * 4);
    if (CMP_NE(_fa, _fb)) goto loc_000EFACC; /* jne: not equal / not zero */

loc_000EF8FC: ;
    edx = MEM32(edi + 0x118);
    eax = 0xFFFFD762u;
    MEM32(edx + 0x108) = eax;
    ecx = MEM32(edi + 0x114);
    MEM32(ecx + 0x108) = eax;
    edx = MEM32(edi + 0x110);
    MEM32(edx + 0x108) = eax;
    ecx = MEM32(edi + 0x10C);
    _fa = (uint32_t)(MEM32(ecx + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 0x14), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EF93A; /* jne: not equal / not zero */

loc_000EF930: ;
    SET_LO8(eax, MEM8(ecx + 0x82));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EF949; /* je: equal / zero */

loc_000EF93A: ;
    MEM8(ecx + 0x82) = 0;
    MEM32(ecx + 0x14) = ebx;
    PUSH32(esp, 0x000EF949u); sub_0002F320(); /* call 0x0002F320 */

loc_000EF949: ;
    ebp = MEM32(edi + 0x118);
    ecx = MEM32(esi + 0x23C);
    ebp = ebp + 4;
    eax = ebp;
    ecx = ecx + 4;
    edx = eax + 1;

loc_000EF960: ;
    SET_LO8(ebx, MEM8(eax));
    eax++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000EF960; /* jne: not equal / not zero */

loc_000EF967: ;
    eax = eax - edx;
    SET_LO8(eax, MEM8(eax + ebp + -1));
    MEM8(ecx) = LO8(eax);
    MEM8(ecx + 1) = LO8(ebx);
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1EF074); /* fmul dword ptr [0x1ef074] */
    eax = MEM32(esi + 0x23C);
    edx = MEM32(eax);
    edx = MEM32(edx + 4);
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = cos(fp_top()); /* fcos */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x1C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x80)); /* fld float */
    MEM8(edx + eax + 0x48) = 1;
    fp_top() = fp_top() * MEMF(0x1E28E4); /* fmul dword ptr [0x1e28e4] */
    eax = MEM32(esi + 0x23C);
    eax = eax + 4;
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x20) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_000EF9E0;

    /* nop */

loc_000EF9E0: ;
    SET_LO8(edx, MEM8(ecx));
    ecx++;
    MEM8(eax) = LO8(edx);
    eax++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000EF9E0; /* jne: not equal / not zero */

loc_000EF9EA: ;
    eax = MEM32(edi + 0x118);
    edx = MEM32(eax);
    ecx = MEM32(esi + 0x23C);
    ebx = MEM32(ecx);
    edx = MEM32(edx + 4);
    eax = MEM32(edx + eax + 0x2C);
    ebx = MEM32(ebx + 4);
    MEM32(ebx + ecx + 0x2C) = eax;
    eax = MEM32(edi + 0x118);
    ecx = eax + 4;
    PUSH32(esp, ecx);
    ecx = MEM32(eax + 0x104);
    PUSH32(esp, 0x000EFA1Du); sub_000E1620(); /* call 0x000E1620 */

loc_000EFA1D: ;
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esi + 0x23C);
    ecx = MEM32(eax + 0x104);
    edx = eax + 4;
    PUSH32(esp, edx);
    PUSH32(esp, 0x000EFA36u); sub_000E1620(); /* call 0x000E1620 */

loc_000EFA36: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    edi = MEM32(edi + 0x118);
    ecx = MEM32(edi);
    edx = MEM32(ecx + 4);
    fp_top() = fp_top() + MEMF(edx + edi + 0x28); /* fadd dword ptr [edx + edi + 0x28] */
    eax = MEM32(esi + 0x23C);
    ecx = MEM32(eax);
    edx = MEM32(ecx + 4);
    fp_top() = fp_top() - fp_st1(); /* fsub st(1) */
    MEMF(edx + eax + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFA71u); sub_0010F038(); /* call 0x0010F038 */

loc_000EFA71: ;
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    edi = ZX8(LO8(eax));
    edi = edi | 0xFFFFFF00u;
    edi = edi << 8;
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFA92u); sub_0010F038(); /* call 0x0010F038 */

loc_000EFA92: ;
    fp_push(MEMF(esp + 0x20)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    eax = ZX8(LO8(eax));
    edi = edi | eax;
    edi = edi << 8;
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFAAFu); sub_0010F038(); /* call 0x0010F038 */

loc_000EFAAF: ;
    edx = MEM32(esi + 0x23C);
    ebp = MEM32(esp + 0x10);
    ecx = ZX8(LO8(eax));
    edi = edi | ecx;
    MEM32(edx + 0x108) = edi;
    ebx = ebx | 0xFFFFFFFFu;
    goto loc_000EFB5B;

loc_000EFACC: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_000EFB13; /* jl: less (signed <) */

loc_000EFAD0: ;
    ecx = MEM32(edi + 0x118);
    eax = 0xFF787878u;
    MEM32(ecx + 0x108) = eax;
    edx = MEM32(edi + 0x114);
    MEM32(edx + 0x108) = eax;
    ecx = MEM32(edi + 0x110);
    MEM32(ecx + 0x108) = eax;
    ecx = MEM32(edi + 0x10C);
    _fa = (uint32_t)(MEM32(ecx + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 0x14), eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EFB0E; /* jne: not equal / not zero */

loc_000EFB04: ;
    SET_LO8(edx, MEM8(ecx + 0x82));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EFB5B; /* je: equal / zero */

loc_000EFB0E: ;
    MEM32(ecx + 0x14) = eax;
    goto loc_000EFB4F;

loc_000EFB13: ;
    edx = MEM32(edi + 0x118);
    MEM32(edx + 0x108) = ebx;
    eax = MEM32(edi + 0x114);
    MEM32(eax + 0x108) = ebx;
    ecx = MEM32(edi + 0x110);
    MEM32(ecx + 0x108) = ebx;
    ecx = MEM32(edi + 0x10C);
    _fa = (uint32_t)(MEM32(ecx + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 0x14), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EFB4C; /* jne: not equal / not zero */

loc_000EFB42: ;
    SET_LO8(eax, MEM8(ecx + 0x82));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EFB5B; /* je: equal / zero */

loc_000EFB4C: ;
    MEM32(ecx + 0x14) = ebx;

loc_000EFB4F: ;
    MEM8(ecx + 0x82) = 0;
    PUSH32(esp, 0x000EFB5Bu); sub_0002F320(); /* call 0x0002F320 */

loc_000EFB5B: ;
    ebp++;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(0xA) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, 0xA (32-bit) */
    MEM32(esp + 0x10) = ebp;
    if (CMP_L(_fas, _fbs)) goto loc_000EF8D0; /* jl: less (signed <) */

loc_000EFB69: ;
    edi = MEM32(esi + 0x240);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    POP32(esp, ebp);
    if (TEST_Z(_fa, _fb)) goto loc_000EFC28; /* je: equal / zero */

loc_000EFB78: ;
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2828); /* fmul dword ptr [0x1e2828] */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2824); /* fmul dword ptr [0x1e2824] */
    fp_top() = cos(fp_top()); /* fcos */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x80)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2820); /* fmul dword ptr [0x1e2820] */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() + MEMF(0x1E16FC); /* fadd dword ptr [0x1e16fc] */
    fp_top() = fp_top() * MEMF(0x1E2604); /* fmul dword ptr [0x1e2604] */
    MEMF(esp + 0x1C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFBDFu); sub_0010F038(); /* call 0x0010F038 */

loc_000EFBDF: ;
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    ebx = ZX8(LO8(eax));
    ebx = ebx | 0xFFFFFF00u;
    ebx = ebx << 8;
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFC00u); sub_0010F038(); /* call 0x0010F038 */

loc_000EFC00: ;
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    edx = ZX8(LO8(eax));
    ebx = ebx | edx;
    ebx = ebx << 8;
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x000EFC1Du); sub_0010F038(); /* call 0x0010F038 */

loc_000EFC1D: ;
    eax = ZX8(LO8(eax));
    ebx = ebx | eax;
    MEM32(edi + 0x108) = ebx;

loc_000EFC28: ;
    ecx = esi;
    PUSH32(esp, 0x000EFC2Fu); sub_000DDA90(); /* call 0x000DDA90 */

loc_000EFC2F: ;
    esi = MEM32(esi + 0x1E4);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    POP32(esp, edi);
    if (TEST_Z(_fa, _fb)) goto loc_000EFC46; /* je: equal / zero */

loc_000EFC3A: ;
    edx = MEM32(esi);
    ecx = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x18;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(edx + 0xC)); return; /* indirect tail jmp */

loc_000EFC46: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x18;
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00102AE0
 * Original: 0x00102AE0 - 0x00102AFE (30 bytes, 11 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00102AE0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00102AE0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00102AE8u); sub_00102630(); /* call 0x00102630 */

loc_00102AE8: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00102AF8; /* je: equal / zero */

loc_00102AEF: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00102AF5u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_00102AF5: ;
    esp = esp + 4;

loc_00102AF8: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000DD430
 * Original: 0x000DD430 - 0x000DD4C3 (147 bytes, 46 insns)
 * Category: game_callback
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DD430(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DD430: ;
    esp = esp - 0x30;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + -20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DD4BC; /* je: equal / zero */

loc_000DD43D: ;
    edx = MEM32(esi + -280);
    ecx = MEM32(esp + 0x38);
    eax = esp + 4;
    PUSH32(esp, eax);
    eax = MEM32(edx + 4);
    PUSH32(esp, ecx);
    ecx = eax + esi + -280;
    PUSH32(esp, 0x000DD45Cu); sub_000DAC00(); /* call 0x000DAC00 */

loc_000DD45C: ;
    edx = MEM32(esi + -20);
    ecx = esi + -276;
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x000DD46Cu); sub_000E1140(); /* call 0x000E1140 */

loc_000DD46C: ;
    ecx = MEM32(esi + -20);
    eax = MEM32(esi + -16);
    edx = MEM32(ecx + 0x14);
    esp = esp + 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000DD486; /* jne: not equal / not zero */

loc_000DD47C: ;
    SET_LO8(edx, MEM8(ecx + 0x82));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DD495; /* je: equal / zero */

loc_000DD486: ;
    MEM8(ecx + 0x82) = 0;
    MEM32(ecx + 0x14) = eax;
    PUSH32(esp, 0x000DD495u); sub_0002F320(); /* call 0x0002F320 */

loc_000DD495: ;
    eax = MEM32(esi + -20);
    ecx = MEM32(esi + -12);
    MEM32(eax + 0xD0) = ecx;
    edx = MEM32(esi + -20);
    eax = MEM32(esi + -8);
    MEM32(edx + 0xD4) = eax;
    ecx = MEM32(esi + -20);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    eax = esp + 8;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x000DD4BCu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DD4BC: ;
    POP32(esp, esi);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000EF2F0
 * Original: 0x000EF2F0 - 0x000EF380 (144 bytes, 43 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EF2F0(void)
{
    static RECOMP_TLS uint32_t godzilla_shell_load_polls;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EF2F0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x1E4);
    ebx = 0; /* xor self */
    if (getenv("GODZILLA_SKIP_MOVIES") && ecx != 0) {
        ++godzilla_shell_load_polls;
        if (godzilla_shell_load_polls <= 40u)
            fprintf(stderr,
                    "[SHELL-LOAD] poll=%u shell=%08X loader=%08X "
                    "done=%02X cancel=%02X active=%02X/%02X\n",
                    godzilla_shell_load_polls, esi, ecx,
                    MEM8(ecx + 0x549), MEM8(ecx + 0x54E),
                    MEM8(esi + 0x1AC), MEM8(esi + 0x1CC));
        /* With XMV playback disabled the Xbox asynchronous loader never gets
         * the movie-thread completion pulse.  Its work has already run on the
         * host by this point, so provide that pulse after a short grace period
         * and let the retail cleanup/transition logic consume it normally. */
        if (godzilla_shell_load_polls > 30u)
            MEM8(ecx + 0x549) = 1;
    }
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EF363; /* je: equal / zero */

loc_000EF300: ;
    PUSH32(esp, 0x000EF305u); sub_000E4A60(); /* call 0x000E4A60 */

loc_000EF305: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EF363; /* je: equal / zero */

loc_000EF309: ;
    eax = MEM32(esi + 0x1E4);
    _fa = (uint32_t)(MEM8(eax + 0x54A)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 0x54A), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EF328; /* je: equal / zero */

loc_000EF317: ;
    PUSH32(esp, ebx);
    ecx = 0x4AD508;
    PUSH32(esp, 0x000EF322u); sub_000DA0F0(); /* call 0x000DA0F0 */

loc_000EF322: ;
    MEM8(eax + 0x168) = LO8(ebx);

loc_000EF328: ;
    ecx = MEM32(esi + 0x1E4);
    _fa = (uint32_t)(MEM8(ecx + 0x54E)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x54E), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EF33E; /* je: equal / zero */

loc_000EF336: ;
    MEM8(esi + 0x1AC) = LO8(ebx);
    goto loc_000EF344;

loc_000EF33E: ;
    MEM8(esi + 0x1CC) = LO8(ebx);

loc_000EF344: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EF34F; /* je: equal / zero */

loc_000EF348: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x000EF34Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000EF34F: ;
    MEM32(esi + 0x1E4) = ebx;
    MEM8(esi + 0x9C) = 1;
    MEM8(esi + 0x9D) = 1;

loc_000EF363: ;
    _fa = (uint32_t)(MEM8(esi + 0x1AC)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x1AC), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000EF37B; /* je: equal / zero */

loc_000EF36B: ;
    _fa = (uint32_t)(MEM32(esi + 0x1E4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x1E4), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000EF37B; /* jne: not equal / not zero */

loc_000EF373: ;
    POP32(esp, esi);
    eax = 1;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_000EF37B: ;
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0003EE90
 * Original: 0x0003EE90 - 0x0003EEE5 (85 bytes, 34 insns)
 * Category: game_vtable
 * CC: thiscall, 3 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003EE90(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    uint32_t trace_dest = MEM32(esp + 4);
    uint32_t trace_size = MEM32(esp + 8);
    uint32_t trace_offset = MEM32(esp + 0xC);
    uint32_t trace_seek_result = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003EE90: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0003EED9; /* je: equal / zero */

loc_0003EE9B: ;
    ecx = MEM32(esp + 0x10);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0003EEAAu); sub_001188C0(); /* call 0x001188C0 */

loc_0003EEAA: ;
    trace_seek_result = eax;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0003EECD; /* je: equal / zero */

loc_0003EEAF: ;
    eax = MEM32(esp + 0xC);
    ecx = MEM32(esp + 8);
    PUSH32(esp, 0);
    edx = esp + 0x14;
    PUSH32(esp, edx);
    edx = MEM32(esi + 4);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0003EEC9u); sub_00118679(); /* call 0x00118679 */

loc_0003EEC9: ;
    if (g_mainmenu_bundle_trace) {
        static uint32_t mainmenu_bundle_read_count;
        uint32_t trace_id = ++mainmenu_bundle_read_count;
        if (trace_id <= 24u) {
            fprintf(stderr,
                    "[MAINMENU-BUNDLE-READ] #%u file=%08X off=%08X size=%08X dst=%08X seek=%08X read=%08X first=%08X\n",
                    trace_id, MEM32(esi + 4), trace_offset, trace_size,
                    trace_dest, trace_seek_result, eax,
                    trace_size >= 4 ? MEM32(trace_dest) : 0);
            fflush(stderr);
        }
    }
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0003EEDF; /* jne: not equal / not zero */

loc_0003EECD: ;
    PUSH32(esp, 0x0003EED2u); sub_0002A76D(); /* call 0x0002A76D */

loc_0003EED2: ;
    ecx = eax;
    PUSH32(esp, 0x0003EED9u); sub_000301C0(); /* call 0x000301C0 */

loc_0003EED9: ;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

loc_0003EEDF: ;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_000688D0
 * Original: 0x000688D0 - 0x000688EA (26 bytes, 8 insns)
 * Category: game_vtable
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000688D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */

loc_000688D0: ;
    eax = MEM32(esp + 4);
    eax = MEM32(eax + 8);
    MEM32(eax) = MEM32(eax) - 1;
    if ((MEM32(eax) != 0)) goto loc_000688E7; /* jne: not equal / not zero */

loc_000688DB: ;
    MEM32(esp + 4) = eax;
    ecx = ecx + 0xC;
    g_seh_ebp = ebp; g_ebp = ebp; sub_00068800(); return; /* tail jmp 0x00068800 */

loc_000688E7: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000BAF80
 * Original: 0x000BAF80 - 0x000BAF86 (6 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000BAF80(void)
{

loc_000BAF80: ;
    eax = 8;
    esp += 4; return; /* ret */

}

/**
 * sub_000E9DE0
 * Original: 0x000E9DE0 - 0x000E9DEE (14 bytes, 3 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E9DE0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000E9DE0: ;
    ecx = ecx - MEM32(ecx + -4);
    ecx = ecx - 0x90;
    g_seh_ebp = ebp; g_ebp = ebp; sub_000EA9D0(); return; /* tail jmp 0x000EA9D0 */

}

/**
 * sub_000E9DF0
 * Original: 0x000E9DF0 - 0x000E9DF8 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E9DF0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000E9DF0: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000EAAA0(); return; /* tail jmp 0x000EAAA0 */

}

/**
 * sub_000EAC60
 * Original: 0x000EAC60 - 0x000EAC68 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EAC60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000EAC60: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000ECCA0(); return; /* tail jmp 0x000ECCA0 */

}

/**
 * sub_000F0210
 * Original: 0x000F0210 - 0x000F022E (30 bytes, 11 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000F0210(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000F0210: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000F0218u); sub_000EF660(); /* call 0x000EF660 */

loc_000F0218: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000F0228; /* je: equal / zero */

loc_000F021F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000F0225u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000F0225: ;
    esp = esp + 4;

loc_000F0228: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000F2B40
 * Original: 0x000F2B40 - 0x000F2B73 (51 bytes, 17 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000F2B40(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000F2B40: ;
    PUSH32(esp, esi);
    esi = ecx + -180;
    PUSH32(esp, edi);
    edi = esi + 0xB4;
    ecx = edi;
    PUSH32(esp, 0x000F2B55u); sub_000F22F0(); /* call 0x000F22F0 */

loc_000F2B55: ;
    ecx = edi;
    PUSH32(esp, 0x000F2B5Cu); sub_000DE840(); /* call 0x000DE840 */

loc_000F2B5C: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000F2B6C; /* je: equal / zero */

loc_000F2B63: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000F2B69u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000F2B69: ;
    esp = esp + 4;

loc_000F2B6C: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000DFB60
 * Original: 0x000DFB60 - 0x000DFB6E (14 bytes, 3 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DFB60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000DFB60: ;
    ecx = ecx - MEM32(ecx + -4);
    ecx = ecx - 0x90;
    g_seh_ebp = ebp; g_ebp = ebp; sub_000E0430(); return; /* tail jmp 0x000E0430 */

}

/**
 * sub_0003F320
 * Original: 0x0003F320 - 0x0003F368 (72 bytes, 22 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003F320(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003F320: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x1E5CBC;
    PUSH32(esp, 0x0003F32Eu); sub_0003F070(); /* call 0x0003F070 */

loc_0003F32E: ;
    _fa = (uint32_t)(MEM8(esi + 8)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 8), 4 (8-bit) */
    MEM32(esi) = 0x1E175C;
    if (TEST_NZ(_fa, _fb)) goto loc_0003F346; /* jne: not equal / not zero */

loc_0003F33A: ;
    eax = MEM32(esi + 0x10);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0003F343u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0003F343: ;
    esp = esp + 4;

loc_0003F346: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    MEM32(esi) = 0x1E1750;
    if (TEST_Z(_fa, _fb)) goto loc_0003F362; /* je: equal / zero */

loc_0003F353: ;
    _fa = (uint32_t)(MEM8(esi + 8)) & 0xFFu; _fb = (uint32_t)(0x18) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 8), 0x18 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0003F362; /* jne: not equal / not zero */

loc_0003F359: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0003F35Fu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0003F35F: ;
    esp = esp + 4;

loc_0003F362: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00068AE0
 * Original: 0x00068AE0 - 0x00068AEF (15 bytes, 6 insns)
 * Category: game_callback
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00068AE0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00068AE0: ;
    ecx = MEM32(0x418064);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00068AEE; /* je: equal / zero */

loc_00068AEA: ;
    eax = MEM32(ecx);
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(MEM32(eax)); return; /* indirect tail jmp */

loc_00068AEE: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00073870
 * Original: 0x00073870 - 0x00073881 (17 bytes, 6 insns)
 * Category: game_callback
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00073870(void)
{

loc_00073870: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0007387Bu); sub_0011139C(); /* call 0x0011139C */

loc_0007387B: ;
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E2390
 * Original: 0x000E2390 - 0x000E260B (635 bytes, 187 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E2390(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000E2390: ;
    SET_LO8(eax, MEM8(esp + 8));
    esp = esp - 0x40;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_000E23AF; /* jne: not equal / not zero */

loc_000E23A0: ;
    eax = MEM32(esi + 0xD8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM8(esp + 0x54) = 0;
    if (TEST_NZ(_fa, _fb)) goto loc_000E23B4; /* jne: not equal / not zero */

loc_000E23AF: ;
    MEM8(esp + 0x54) = 1;

loc_000E23B4: ;
    edx = MEM32(esp + 0x50);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E23DE; /* je: equal / zero */

loc_000E23BC: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E23C8; /* je: equal / zero */

loc_000E23C0: ;
    ecx = esi + 0x88;
    goto loc_000E23CA;

loc_000E23C8: ;
    ecx = 0; /* xor self */

loc_000E23CA: ;
    eax = esp + 0x1C;
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E23D4u); sub_00018FA0(); /* call 0x00018FA0 */

loc_000E23D4: ;
    ecx = esp + 0x1C;
    MEM32(esp + 0x50) = ecx;
    goto loc_000E23F6;

loc_000E23DE: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E23EE; /* je: equal / zero */

loc_000E23E2: ;
    edx = esi + 0x88;
    MEM32(esp + 0x50) = edx;
    goto loc_000E23F6;

loc_000E23EE: ;
    MEM32(esp + 0x50) = 0;

loc_000E23F6: ;
    PUSH32(esp, 0);
    ecx = esi;
    PUSH32(esp, 0x000E23FFu); sub_0002EBA0(); /* call 0x0002EBA0 */

loc_000E23FF: ;
    _fa = (uint32_t)(MEM8(esi + 0x7C)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x7C), 2 (8-bit) */
    ebx = MEM32(esp + 0x54);
    if (TEST_NZ(_fa, _fb)) goto loc_000E25D1; /* jne: not equal / not zero */

loc_000E240D: ;
    eax = MEM32(esi + 0xD4);
    eax--;
    if ((eax == 0)) goto loc_000E2435; /* je: equal / zero */

loc_000E2416: ;
    eax--;
    if ((eax == 0)) goto loc_000E2423; /* je: equal / zero */

loc_000E2419: ;
    MEM32(esp + 0x54) = 0;
    goto loc_000E244D;

loc_000E2423: ;
    eax = esi + 0x2A4;
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x000E2431u); sub_000E2230(); /* call 0x000E2230 */

loc_000E2431: ;
    fp_top() = -fp_top(); /* fchs */
    goto loc_000E2449;

loc_000E2435: ;
    ecx = esi + 0x2A4;
    PUSH32(esp, ecx);
    ecx = esi;
    PUSH32(esp, 0x000E2443u); sub_000E2230(); /* call 0x000E2230 */

loc_000E2443: ;
    fp_top() = fp_top() * MEMF(0x1E2920); /* fmul dword ptr [0x1e2920] */

loc_000E2449: ;
    MEMF(esp + 0x54) = (float)fp_top(); fp_pop(); /* fstp */

loc_000E244D: ;
    edx = esi + 0x2A4;
    ecx = esi;
    MEM32(esi + 0x3A4) = edx;
    MEM32(esi + 0x3A8) = 0;
    PUSH32(esp, 0x000E246Au); sub_000E2040(); /* call 0x000E2040 */

loc_000E246A: ;
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(esp + 0x10) = 0;
    if (TEST_Z(_fa, _fb)) goto loc_000E25D1; /* je: equal / zero */

loc_000E247C: ;
    PUSH32(esp, ebp);
    /* nop */

loc_000E2480: ;
    PUSH32(esp, edi);
    ecx = esi;
    MEM32(esp + 0x14) = 0;
    PUSH32(esp, 0x000E2490u); sub_000E1620(); /* call 0x000E1620 */

loc_000E2490: ;
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x000E249Cu); sub_000E1750(); /* call 0x000E1750 */

loc_000E249C: ;
    MEMF(esp + 0x1C) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esi + 0xD0);
    eax--;
    if ((eax == 0)) goto loc_000E24B4; /* je: equal / zero */

loc_000E24A9: ;
    eax--;
    if ((eax != 0)) goto loc_000E24C2; /* jne: not equal / not zero */

loc_000E24AC: ;
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    goto loc_000E24BE;

loc_000E24B4: ;
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2920); /* fmul dword ptr [0x1e2920] */

loc_000E24BE: ;
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */

loc_000E24C2: ;
    eax = MEM32(esp + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000E24E2; /* jne: not equal / not zero */

loc_000E24CA: ;
    fp_push(MEMF(esi + 0x270)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x268); /* fmul dword ptr [esi + 0x268] */
    fp_top() = fp_top() - MEMF(esp + 0x1C); /* fsub dword ptr [esp + 0x1c] */
    fp_top() = MEMF(esp + 0x58) - fp_top(); /* fsubr dword ptr [esp + 0x58] */
    MEMF(esp + 0x58) = (float)fp_top(); fp_pop(); /* fstp */

loc_000E24E2: ;
    fp_push(MEMF(esi + 0x278)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000E250C; /* jp: parity */

loc_000E24F5: ;
    fp_push(MEMF(esi + 0x27C)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E1884)); fp_pop(); /* fcomp dword ptr [0x1e1884] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_000E258C; /* jnp: not parity */

loc_000E250C: ;
    ebp = MEM32(esi + 0x14);
    eax = MEM32(esi + 0x28C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000E2523; /* jne: not equal / not zero */

loc_000E2519: ;
    SET_LO8(ecx, MEM8(esi + 0x82));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E2534; /* je: equal / zero */

loc_000E2523: ;
    ecx = esi;
    MEM8(esi + 0x82) = 0;
    MEM32(esi + 0x14) = eax;
    PUSH32(esp, 0x000E2534u); sub_0002F320(); /* call 0x0002F320 */

loc_000E2534: ;
    fp_push(MEMF(esi + 0x270)); /* fld float */
    eax = MEM32(esp + 0x54);
    fp_top() = fp_top() * MEMF(esi + 0x27C); /* fmul dword ptr [esi + 0x27c] */
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    esp = esp - 8;
    fp_top() = fp_top() + MEMF(esp + 0x68); /* fadd dword ptr [esp + 0x68] */
    ecx = esi;
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x270)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x278); /* fmul dword ptr [esi + 0x278] */
    fp_top() = fp_top() + MEMF(esp + 0x20); /* fadd dword ptr [esp + 0x20] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E256Cu); sub_000E13A0(); /* call 0x000E13A0 */

loc_000E256C: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x14)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esi + 0x14) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000E257B; /* jne: not equal / not zero */

loc_000E2571: ;
    SET_LO8(eax, MEM8(esi + 0x82));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E258C; /* je: equal / zero */

loc_000E257B: ;
    ecx = esi;
    MEM8(esi + 0x82) = 0;
    MEM32(esi + 0x14) = ebp;
    PUSH32(esp, 0x000E258Cu); sub_0002F320(); /* call 0x0002F320 */

loc_000E258C: ;
    ecx = MEM32(esp + 0x58);
    edx = MEM32(esp + 0x10);
    eax = MEM32(esp + 0x54);
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    ecx = esi;
    PUSH32(esp, 0x000E25A4u); sub_000E13A0(); /* call 0x000E13A0 */

loc_000E25A4: ;
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x274); /* fadd dword ptr [esi + 0x274] */
    ecx = esi;
    fp_top() = fp_top() + MEMF(esp + 0x58); /* fadd dword ptr [esp + 0x58] */
    MEMF(esp + 0x58) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x000E25BDu); sub_000E2040(); /* call 0x000E2040 */

loc_000E25BD: ;
    ecx = MEM32(esp + 0x14);
    edi = eax;
    ecx++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(esp + 0x14) = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_000E2480; /* jne: not equal / not zero */

loc_000E25D0: ;
    POP32(esp, ebp);

loc_000E25D1: ;
    _fa = (uint32_t)(MEM8(esi + 0x7C)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x7C), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000E2602; /* jne: not equal / not zero */

loc_000E25D7: ;
    eax = MEM32(esi + 0xCC);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000E2602; /* jle: less or equal (signed <=) */

loc_000E25E3: ;
    ecx = MEM32(esi + 0xC4);
    ecx = MEM32(ecx + edi * 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    eax = esp + 0x20;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x000E25F7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000E25F7: ;
    eax = MEM32(esi + 0xCC);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000E25E3; /* jl: less (signed <) */

loc_000E2602: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0x40;
    esp += 12; return; /* ret 8 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0010C760
 * Original: 0x0010C760 - 0x0010C76E (14 bytes, 4 insns)
 * Category: game_callback
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0010C760(void)
{

loc_0010C760: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, 0x0010C769u); sub_0010C5C0(); /* call 0x0010C5C0 */

loc_0010C769: ;
    eax = 0; /* xor self */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E0430
 * Original: 0x000E0430 - 0x000E0459 (41 bytes, 13 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E0430(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E0430: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000E0438u); sub_000E0460(); /* call 0x000E0460 */

loc_000E0438: ;
    ecx = esi + 0x90;
    PUSH32(esp, 0x000E0443u); sub_000DE840(); /* call 0x000DE840 */

loc_000E0443: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E0453; /* je: equal / zero */

loc_000E044A: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E0450u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000E0450: ;
    esp = esp + 4;

loc_000E0453: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000EA9D0
 * Original: 0x000EA9D0 - 0x000EAA03 (51 bytes, 14 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EA9D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EA9D0: ;
    PUSH32(esp, esi);
    esi = ecx + -180;
    ecx = esi + 0xB4;
    PUSH32(esp, 0x000EA9E2u); sub_000EAA10(); /* call 0x000EAA10 */

loc_000EA9E2: ;
    ecx = esi + 0x144;
    PUSH32(esp, 0x000EA9EDu); sub_000DE840(); /* call 0x000DE840 */

loc_000EA9ED: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EA9FD; /* je: equal / zero */

loc_000EA9F4: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000EA9FAu); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000EA9FA: ;
    esp = esp + 4;

loc_000EA9FD: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000EAAA0
 * Original: 0x000EAAA0 - 0x000EAAD3 (51 bytes, 17 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EAAA0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EAAA0: ;
    PUSH32(esp, esi);
    esi = ecx + -460;
    PUSH32(esp, edi);
    edi = esi + 0x1CC;
    ecx = edi;
    PUSH32(esp, 0x000EAAB5u); sub_000EAAE0(); /* call 0x000EAAE0 */

loc_000EAAB5: ;
    ecx = edi;
    PUSH32(esp, 0x000EAABCu); sub_000DE840(); /* call 0x000DE840 */

loc_000EAABC: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000EAACC; /* je: equal / zero */

loc_000EAAC3: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000EAAC9u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000EAAC9: ;
    esp = esp + 4;

loc_000EAACC: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000ECCA0
 * Original: 0x000ECCA0 - 0x000ECCD3 (51 bytes, 17 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000ECCA0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000ECCA0: ;
    PUSH32(esp, esi);
    esi = ecx + -312;
    PUSH32(esp, edi);
    edi = esi + 0x138;
    ecx = edi;
    PUSH32(esp, 0x000ECCB5u); sub_000ECCE0(); /* call 0x000ECCE0 */

loc_000ECCB5: ;
    ecx = edi;
    PUSH32(esp, 0x000ECCBCu); sub_000DE840(); /* call 0x000DE840 */

loc_000ECCBC: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000ECCCC; /* je: equal / zero */

loc_000ECCC3: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000ECCC9u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000ECCC9: ;
    esp = esp + 4;

loc_000ECCCC: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0003EDE0
 * Original: 0x0003EDE0 - 0x0003EE64 (132 bytes, 56 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003EDE0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003EDE0: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    edi = ecx;
    ecx = MEM32(edi + 0xC);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x0003EDF2u); sub_0003EBE0(); /* call 0x0003EBE0 */

loc_0003EDF2: ;
    ebp = eax;
    if (g_mainmenu_bundle_trace) {
        static uint32_t mainmenu_bundle_lookup_count;
        uint32_t trace_id = ++mainmenu_bundle_lookup_count;
        if (trace_id <= 96u) {
            uint32_t archive = MEM32(edi + 0xC);
            fprintf(stderr,
                    "[MAINMENU-BUNDLE-LOOKUP] #%u node=%08X archive=%08X table=%08X entries=%u result=%08X name='",
                    trace_id, edi, archive,
                    archive ? MEM32(archive + 0x34) : 0,
                    archive ? ZX16(MEM16(archive + 0x1C)) : 0,
                    ebp);
            for (uint32_t i = 0; i < 96; ++i) {
                uint8_t ch = MEM8(ebx + i);
                if (ch == 0)
                    break;
                fputc((ch >= 0x20 && ch < 0x7F) ? ch : '.', stderr);
            }
            fputs("'\n", stderr);
            fflush(stderr);
        }
    }
    eax = 0; /* xor self */
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0003EE02; /* jne: not equal / not zero */

loc_0003EDFA: ;
    POP32(esp, edi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

loc_0003EE02: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x18);
    ecx = ebx;
    MEM32(esi + 0x104) = edi;
    MEM8(esi) = LO8(eax);
    MEM8(esi + 0x108) = LO8(eax);
    edi = ecx + 1;
    /* nop */

loc_0003EE20: ;
    SET_LO8(edx, MEM8(ecx));
    ecx++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0003EE20; /* jne: not equal / not zero */

loc_0003EE27: ;
    ecx = ecx - edi;
    ecx++;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x100 (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0003EE3B; /* jb: below (unsigned <) */

loc_0003EE32: ;
    POP32(esp, esi);
    POP32(esp, edi);
    POP32(esp, ebp);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

loc_0003EE3B: ;
    edi = esi + 1;
    ecx = ebx;
    edi = edi - ebx;

loc_0003EE42: ;
    SET_LO8(edx, MEM8(ecx));
    MEM8(edi + ecx) = LO8(edx);
    ecx++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0003EE42; /* jne: not equal / not zero */

loc_0003EE4C: ;
    ecx = MEM32(ebp + 0xC);
    MEM32(esi + 0x20C) = eax;
    MEM32(esi + 0x208) = ecx;
    POP32(esp, esi);
    POP32(esp, edi);
    POP32(esp, ebp);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000DA450
 * Original: 0x000DA450 - 0x000DA458 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DA450(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000DA450: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000E0860(); return; /* tail jmp 0x000E0860 */

}

/**
 * sub_000E0860
 * Original: 0x000E0860 - 0x000E088D (45 bytes, 13 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E0860(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E0860: ;
    PUSH32(esp, esi);
    esi = ecx + -280;
    ecx = esi + 0x118;
    PUSH32(esp, 0x000E0872u); sub_000D9F80(); /* call 0x000D9F80 */

loc_000E0872: ;
    PUSH32(esp, 0x000E0877u); sub_000DE840(); /* call 0x000DE840 */

loc_000E0877: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E0887; /* je: equal / zero */

loc_000E087E: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E0884u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000E0884: ;
    esp = esp + 4;

loc_000E0887: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000DFE70
 * Original: 0x000DFE70 - 0x000DFEBB (75 bytes, 29 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DFE70(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000DFE70: ;
    PUSH32(esp, edi);
    edi = ecx;
    ecx = MEM32(edi + 0x44);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(edi) = 0x1F4350;
    if (TEST_Z(_fa, _fb)) goto loc_000DFE8D; /* je: equal / zero */

loc_000DFE80: ;
    PUSH32(esp, edi);
    PUSH32(esp, 0x000DFE86u); sub_000DD600(); /* call 0x000DD600 */

loc_000DFE86: ;
    MEM32(edi + 0x44) = 0;

loc_000DFE8D: ;
    ecx = MEM32(edi + 0x3C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DFEA5; /* je: equal / zero */

loc_000DFE94: ;
    PUSH32(esp, esi);

loc_000DFE95: ;
    eax = MEM32(ecx);
    esi = MEM32(ecx + 0x34);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000DFE9Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DFE9E: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    ecx = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_000DFE95; /* jne: not equal / not zero */

loc_000DFEA4: ;
    POP32(esp, esi);

loc_000DFEA5: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DFEB5; /* je: equal / zero */

loc_000DFEAC: ;
    PUSH32(esp, edi);
    PUSH32(esp, 0x000DFEB2u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000DFEB2: ;
    esp = esp + 4;

loc_000DFEB5: ;
    eax = edi;
    POP32(esp, edi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001035D0
 * Original: 0x001035D0 - 0x001039BC (1004 bytes, 306 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001035D0(void)
{
    static RECOMP_TLS uint32_t s_mainmenu_direct_assets[16];
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_001035D0: ;
    esp = esp - 0x30;
    PUSH32(esp, esi);
    esi = ecx;
    {
        static uint32_t s_mainmenu_render_probe;
        if (s_mainmenu_render_probe < 64u) {
            fprintf(stderr,
                    "[MAINMENU-RENDER] n=%u this=%08X count=%u selection=%u list=%08X phase=%08X\n",
                    s_mainmenu_render_probe, esi, MEM32(esi + -120), MEM32(esi + -124),
                    MEM32(esi + -132), MEM32(esi + -8));
        }
        ++s_mainmenu_render_probe;
    }
    eax = MEM32(esi + -124);
    MEM32(esp + 0x10) = eax;
    eax = eax + eax;
    MEM32(esp + 0xC) = eax;
    fp_push((double)SMEM32(esp + 0xC)); /* fild */
    PUSH32(esp, edi);
    fp_top() = fp_top() * MEMF(0x1F9358); /* fmul dword ptr [0x1f9358] */
    fp_push(MEMF(esp + 0x3C)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + -116); /* fmul dword ptr [esi - 0x74] */
    MEMF(esp + 0x3C) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() - MEMF(esi + -20); /* fsub dword ptr [esi - 0x14] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 0x3C)); /* fcom dword ptr [esp + 0x3c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0010360F; /* jne: not equal / not zero */

loc_00103609: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x3C)); /* fld float */

loc_0010360F: ;
    fp_push(MEMF(esp + 0x3C)); /* fld float */
    fp_top() = -fp_top(); /* fchs */
    MEMF(esp + 0x3C) = (float)fp_top(); fp_pop(); /* fstp */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 0x3C)); /* fcom dword ptr [esp + 0x3c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0010362A; /* jp: parity */

loc_00103624: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 0x3C)); /* fld float */

loc_0010362A: ;
    fp_top() = fp_top() + MEMF(esi + -20); /* fadd dword ptr [esi - 0x14] */
    eax = MEM32(esi + -8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEMF(esi + -20) = (float)fp_top(); fp_pop(); /* fstp */
    if (TEST_NZ(_fa, _fb)) goto loc_0010363C; /* jne: not equal / not zero */

loc_00103637: ;
    MEMF(esi + -20) = (float)fp_top(); fp_pop(); /* fstp */
    goto loc_0010363E;

loc_0010363C: ;
    fp_pop(); /* fstp st(0) */

loc_0010363E: ;
    eax = MEM32(esi + -120);
    edi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esp + 0x3C) = edi;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_001039B4; /* jle: less or equal (signed <=) */

loc_0010364F: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    MEM32(esp + 0x24) = edi;
    ebp = esi + -132;
    goto loc_00103660;

    /* nop */

loc_00103660: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x245B90);
    PUSH32(esp, 0x245A70);
    PUSH32(esp, 0);
    PUSH32(esp, edi);
    ecx = ebp;
    PUSH32(esp, 0x00103676u); sub_000DAAF0(); /* call 0x000DAAF0 */

loc_00103676: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0010367Cu); sub_00110786(); /* call 0x00110786 */

loc_0010367C: ;
    esp = esp + 0x14;
    PUSH32(esp, edi);
    ecx = ebp;
    ebx = eax;
    PUSH32(esp, 0x00103689u); sub_000DD510(); /* call 0x000DD510 */

loc_00103689: ;
    if (edi < 16u)
        s_mainmenu_direct_assets[edi] = ebx;
    /* Direct PWK loads do not carry the cached-resource wrapper which keeps
     * the virtual render base's node handle refreshed.  A menu visibility
     * pass clears that non-owning handle after its first use, while the
     * derived object continues to own the live node at +0x08.  Mirror the
     * retail wrapper contract each frame before the menu updates the item. */
    if (MEM32(ebx + 0x80u) == 0u && MEM32(ebx + 8u) != 0u) {
        static uint32_t s_mainmenu_rebridge_probe;
        MEM32(ebx + 0x80u) = MEM32(ebx + 8u);
        if (s_mainmenu_rebridge_probe < 36u)
            fprintf(stderr,
                    "[PWK-RENDER-REBRIDGE] n=%u index=%u object=%08X node=%08X interface=%08X\n",
                    s_mainmenu_rebridge_probe, edi, ebx, MEM32(ebx + 8u), ebx + 0x78u);
        ++s_mainmenu_rebridge_probe;
    }
    {
        static uint32_t s_mainmenu_item_probe;
        if (s_mainmenu_item_probe < 18u) {
            uint32_t item_vtable = MEM32(ebx);
            uint32_t item_off = MEM32(item_vtable + 4);
            uint32_t item_obj = ebx + item_off;
            fprintf(stderr,
                    "[MAINMENU-ITEM] n=%u index=%u asset=%08X handle=%08X vt=%08X off=%08X obj=%08X "
                    "words=%08X,%08X,%08X,%08X objwords=%08X,%08X,%08X,%08X\n",
                    s_mainmenu_item_probe, edi, ebx, eax, item_vtable, item_off, item_obj,
                    MEM32(ebx), MEM32(ebx + 4), MEM32(ebx + 8), MEM32(ebx + 12),
                    MEM32(item_obj), MEM32(item_obj + 4), MEM32(item_obj + 8), MEM32(item_obj + 12));
        }
        ++s_mainmenu_item_probe;
    }
    ecx = edi;
    ecx = ecx & 0x80000007u;
    MEM32(esp + 0x20) = eax;
    if (((int32_t)ecx >= 0)) goto loc_0010369C; /* jns: not sign (positive) */

loc_00103697: ;
    ecx--;
    ecx = ecx | 0xFFFFFFF8u;
    ecx++;

loc_0010369C: ;
    edx = 6;
    edx = edx - ecx;
    MEM32(esp + 0x14) = edx;
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    eax = edi;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 7;
    fp_top() = fp_top() * MEMF(0x1EE0A0); /* fmul dword ptr [0x1ee0a0] */
    eax = eax + edx;
    eax = (uint32_t)((int32_t)(int32_t)eax >> 3);
    eax = eax << 1;
    MEM32(esp + 0x14) = eax;
    eax = MEM32(ebx);
    fp_push((double)SMEM32(esp + 0x14)); /* fild */
    ecx = MEM32(eax + 4);
    fp_top() = fp_top() * MEMF(0x1E267C); /* fmul dword ptr [0x1e267c] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_top() = fp_top() + MEMF(esi + -20); /* fadd dword ptr [esi - 0x14] */
    MEMF(esp + 0x14) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push((double)SMEM32(esp + 0x44)); /* fild */
    fp_top() = fp_top() * MEMF(0x1EE0A0); /* fmul dword ptr [0x1ee0a0] */
    fp_top() = fp_top() - MEMF(esi + -20); /* fsub dword ptr [esi - 0x14] */
    MEM8(ecx + ebx + 0x48) = 1;
    fp_top() = fabs(fp_top()); /* fabs */
    fp_top() = fp_top() * MEMF(0x1F9354); /* fmul dword ptr [0x1f9354] */
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1F8AC8)); fp_pop(); /* fcomp dword ptr [0x1f8ac8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00103713; /* jp: parity */

loc_00103709: ;
    MEM32(esp + 0x18) = 0x3F800000;
    goto loc_0010375A;

loc_00103713: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1E16F8)); fp_pop(); /* fcomp dword ptr [0x1e16f8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00103740; /* jne: not equal / not zero */

loc_00103724: ;
    edx = MEM32(ebx);
    eax = MEM32(edx + 4);
    PUSH32(esp, edi);
    ecx = ebp;
    MEM8(eax + ebx + 0x48) = 0;
    MEM32(esp + 0x1C) = 0;
    PUSH32(esp, 0x0010373Eu); sub_00103220(); /* call 0x00103220 */

loc_0010373E: ;
    goto loc_0010375A;

loc_00103740: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() - MEMF(0x1F8AC8); /* fsub dword ptr [0x1f8ac8] */
    fp_top() = fp_top() * MEMF(0x1F9350); /* fmul dword ptr [0x1f9350] */
    fp_top() = MEMF(0x1E16FC) - fp_top(); /* fsubr dword ptr [0x1e16fc] */
    MEMF(esp + 0x18) = (float)fp_top(); fp_pop(); /* fstp */

loc_0010375A: ;
    ecx = MEM32(esi + -128);
    edx = MEM32(ecx + 4);
    fp_push(MEMF(edx + esi + -84)); /* fld float */
    eax = edx + esi;
    fp_push(MEMF(eax + -80)); /* fld float */
    { fp_st1() = atan2(fp_st1(), fp_top()); fp_pop(); } /* fpatan */
    PUSH32(esp, edi);
    ecx = ebp;
    MEM8(esp + 0x48) = 0;
    fp_top() = fp_top() + MEMF(esp + 0x18); /* fadd dword ptr [esp + 0x18] */
    MEMF(esp + 0x18) = (float)fp_top(); /* fst */
    fp_top() = cos(fp_top()); /* fcos */
    fp_top() = fp_top() * MEMF(esi + -16); /* fmul dword ptr [esi - 0x10] */
    fp_top() = -fp_top(); /* fchs */
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = sin(fp_top()); /* fsin */
    fp_top() = fp_top() * MEMF(esi + -16); /* fmul dword ptr [esi - 0x10] */
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00103799u); sub_000DAAF0(); /* call 0x000DAAF0 */

loc_00103799: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001037CA; /* je: equal / zero */

loc_0010379D: ;
    eax = MEM32(eax + 0x4C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001037CA; /* je: equal / zero */

loc_001037A4: ;
    SET_LO8(ecx, MEM8(eax));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001037CC; /* je: equal / zero */

loc_001037AA: ;
    eax = esi + -112;
    edx = MEM32(eax);
    MEM32(esp + 0x30) = edx;
    edx = MEM32(eax + 4);
    MEM32(esp + 0x34) = edx;
    edx = MEM32(eax + 8);
    eax = MEM32(eax + 0xC);
    MEM32(esp + 0x38) = edx;
    MEM32(esp + 0x3C) = eax;
    goto loc_001037EA;

loc_001037CA: ;
    SET_LO8(ecx, 0); /* xor self */

loc_001037CC: ;
    edx = esi + -96;
    eax = MEM32(edx);
    MEM32(esp + 0x30) = eax;
    eax = MEM32(edx + 4);
    MEM32(esp + 0x34) = eax;
    eax = MEM32(edx + 8);
    edx = MEM32(edx + 0xC);
    MEM32(esp + 0x38) = eax;
    MEM32(esp + 0x3C) = edx;

loc_001037EA: ;
    fp_push(MEMF(esp + 0x3C)); /* fld float */
    fp_top() = fp_top() * MEMF(esp + 0x18); /* fmul dword ptr [esp + 0x18] */
    MEMF(esp + 0x3C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMD(0x1F9348)); fp_pop(); /* fcomp qword ptr [0x1f9348] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_001038F0; /* jp: parity */

loc_0010380B: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x1C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, MEM32(esp + 0x1C) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_001038F0; /* jne: not equal / not zero */

loc_00103815: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001038C6; /* je: equal / zero */

loc_0010381D: ;
    eax = MEM32(esi + -128);
    ecx = MEM32(eax + 4);
    fp_push(MEMF(ecx + esi + -84)); /* fld float */
    eax = ecx + esi;
    fp_push(MEMF(eax + -80)); /* fld float */
    MEM8(esp + 0x44) = 1;
    { double _t = fp_st1(); fp_push(_t); } /* fld st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = g_fp_stack[(g_fp_top + 2) & 7] * fp_top(); fp_pop(); /* fmulp st(2) */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    g_fp_stack[(g_fp_top + 2) & 7] = g_fp_stack[(g_fp_top + 2) & 7] + fp_top(); fp_pop(); /* faddp st(2) */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    fp_top() = sqrt(fp_top()); /* fsqrt */
    fp_st1() = fp_top(); fp_pop(); /* fstp st(1) */
    fp_top() = MEMF(0x1E16FC) / fp_top(); /* fdivr dword ptr [0x1e16fc] */
    fp_push(MEMF(0x1F9340)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x10); /* fsub dword ptr [esp + 0x10] */
    { double _t = fp_st1(); fp_push(_t); } /* fld st(1) */
    fp_top() = fp_top() * MEMF(eax + -84); /* fmul dword ptr [eax - 0x54] */
    fp_top() = fp_top() * MEMF(esi + -12); /* fmul dword ptr [esi - 0xc] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() * MEMF(0x1F933C); /* fmul dword ptr [0x1f933c] */
    fp_top() = MEMF(esp + 0x28) - fp_top(); /* fsubr dword ptr [esp + 0x28] */
    MEMF(esp + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    fp_top() = fp_top() * MEMF(eax + -80); /* fmul dword ptr [eax - 0x50] */
    fp_top() = fp_top() * MEMF(esi + -12); /* fmul dword ptr [esi - 0xc] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() * MEMF(0x1F933C); /* fmul dword ptr [0x1f933c] */
    fp_top() = MEMF(esp + 0x2C) - fp_top(); /* fsubr dword ptr [esp + 0x2c] */
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = fp_top() * MEMF(0x1F933C); /* fmul dword ptr [0x1f933c] */
    fp_push(MEMF(esi + -68)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + -100); /* fsub dword ptr [esi - 0x64] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() + MEMF(esi + -100); /* fadd dword ptr [esi - 0x64] */
    MEMF(esp + 0x3C) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + -80)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + -112); /* fsub dword ptr [esi - 0x70] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() + MEMF(esi + -112); /* fadd dword ptr [esi - 0x70] */
    MEMF(esp + 0x30) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + -76)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + -108); /* fsub dword ptr [esi - 0x6c] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() + MEMF(esi + -108); /* fadd dword ptr [esi - 0x6c] */
    MEMF(esp + 0x34) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + -72)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + -104); /* fsub dword ptr [esi - 0x68] */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    fp_top() = fp_top() + MEMF(esi + -104); /* fadd dword ptr [esi - 0x68] */
    MEMF(esp + 0x38) = (float)fp_top(); fp_pop(); /* fstp */
    fp_pop(); /* fstp st(0) */

loc_001038C6: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x1F22D0)); fp_pop(); /* fcomp dword ptr [0x1f22d0] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_001038DE; /* jp: parity */

loc_001038D7: ;
    ecx = ebp;
    PUSH32(esp, 0x001038DEu); sub_001030E0(); /* call 0x001030E0 */

loc_001038DE: ;
    SET_LO8(eax, MEM8(esp + 0x44));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001038F0; /* je: equal / zero */

loc_001038E6: ;
    PUSH32(esp, edi);
    ecx = ebp;
    PUSH32(esp, 0x001038EEu); sub_00103130(); /* call 0x00103130 */

loc_001038EE: ;
    goto loc_001038F8;

loc_001038F0: ;
    PUSH32(esp, edi);
    ecx = ebp;
    PUSH32(esp, 0x001038F8u); sub_001031B0(); /* call 0x001031B0 */

loc_001038F8: ;
    edx = MEM32(ebx);
    fp_push(MEMF(0x1E26AC)); /* fld float */
    eax = MEM32(edx + 4);
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    edx = MEM32(esp + 0x24);
    ecx = eax + ebx + 0x28;
    eax = MEM32(esp + 0x28);
    MEM32(ecx) = edx;
    edx = MEM32(esp + 0x2C);
    MEM32(ecx + 4) = eax;
    MEM32(ecx + 8) = edx;
    eax = MEM32(ebx);
    PUSH32(esp, ecx);
    ecx = MEM32(eax + 4);
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = ecx + ebx + 4;
    PUSH32(esp, 0x00103931u); sub_00069990(); /* call 0x00069990 */

loc_00103931: ;
    fp_push(MEMF(esp + 0x3C)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x00103946u); sub_0010F038(); /* call 0x0010F038 */

loc_00103946: ;
    fp_push(MEMF(esp + 0x30)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(eax));
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x0010395Fu); sub_0010F038(); /* call 0x0010F038 */

loc_0010395F: ;
    fp_push(MEMF(esp + 0x34)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    SET_LO8(ebx, LO8(eax));
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    ebx = ebx << 8;
    PUSH32(esp, 0x00103979u); sub_0010F038(); /* call 0x0010F038 */

loc_00103979: ;
    fp_push(MEMF(esp + 0x38)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1E2738); /* fmul dword ptr [0x1e2738] */
    edx = ZX8(LO8(eax));
    ebx = ebx | edx;
    ebx = ebx << 8;
    fp_top() = fp_top() + MEMF(0x1E2604); /* fadd dword ptr [0x1e2604] */
    PUSH32(esp, 0x00103996u); sub_0010F038(); /* call 0x0010F038 */

loc_00103996: ;
    ecx = MEM32(esp + 0x20);
    eax = ZX8(LO8(eax));
    ebx = ebx | eax;
    MEM32(ecx + 0x44) = ebx;
    /* Visibility helpers above consume/clear the virtual-base handle.  The
     * global scene renderer runs after this callback, so publish the derived
     * node once more at the end of the item update. */
    if (edi < 16u && s_mainmenu_direct_assets[edi] != 0u) {
        uint32_t owner = s_mainmenu_direct_assets[edi];
        if (MEM32(owner + 8u) != 0u)
            MEM32(owner + 0x80u) = MEM32(owner + 8u);
    }
    eax = MEM32(esi + -120);
    edi++;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    MEM32(esp + 0x44) = edi;
    if (CMP_L(_fas, _fbs)) goto loc_00103660; /* jl: less (signed <) */

loc_001039B2: ;
    POP32(esp, ebp);
    POP32(esp, ebx);

loc_001039B4: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x30;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0010BC70
 * Original: 0x0010BC70 - 0x0010BC8A (26 bytes, 9 insns)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0010BC70(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0010BC70: ;
    eax = MEM32(esp + 4);
    MEM32(ecx + 0xC) = eax;
    eax = MEM32(esp + 8);
    MEM32(ecx + 0x14) = eax;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    SET_LO8(ecx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    SET_LO8(eax, LO8(ecx));
    esp += 12; return; /* ret 8 */

}

/**
 * sub_000454C0
 * Original: 0x000454C0 - 0x000454D4 (20 bytes, 8 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000454C0(void)
{

loc_000454C0: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    PUSH32(esp, 0x000454CDu); sub_000349C0(); /* call 0x000349C0 */

loc_000454CD: ;
    MEM32(esi + 0x3C) = MEM32(esi + 0x3C) + esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000F9DC0
 * Original: 0x000F9DC0 - 0x000F9DC9 (9 bytes, 4 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000F9DC0(void)
{

loc_000F9DC0: ;
    eax = 0; /* xor self */
    MEM32(ecx + 0x70) = eax;
    MEM32(ecx + 0x7C) = eax;
    esp += 4; return; /* ret */

}

/**
 * sub_00047D60
 * Original: 0x00047D60 - 0x00047DA8 (72 bytes, 28 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00047D60(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00047D60: ;
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(MEM16(esi + 0x16)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 0x16), 0 (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00047D87; /* je: equal / zero */

loc_00047D6A: ;
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    eax = esi + 0x60;
    PUSH32(esp, eax);
    ecx = esi + 0x18;
    PUSH32(esp, 0x00047D7Cu); sub_00018F30(); /* call 0x00018F30 */

loc_00047D7C: ;
    ecx = MEM32(esi + 0x6C);
    MEM32(edi + 0xC) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

loc_00047D87: ;
    edx = MEM32(esp + 8);
    esi = esi + 0x60;
    eax = MEM32(esi);
    MEM32(edx) = eax;
    ecx = MEM32(esi + 4);
    MEM32(edx + 4) = ecx;
    eax = MEM32(esi + 8);
    MEM32(edx + 8) = eax;
    ecx = MEM32(esi + 0xC);
    MEM32(edx + 0xC) = ecx;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00045DA0
 * Original: 0x00045DA0 - 0x00045DFB (91 bytes, 34 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00045DA0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00045DA0: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    eax = MEM32(eax + 0x2C);
    ecx = eax + 0xD0;
    PUSH32(esp, 0x00045DB4u); sub_0010A9B0(); /* call 0x0010A9B0 */

loc_00045DB4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00045DF9; /* je: equal / zero */

loc_00045DB8: ;
    ecx = MEM32(esi + 4);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00045DC1u); sub_00109D80(); /* call 0x00109D80 */

loc_00045DC1: ;
    ecx = MEM32(esi + 8);
    edx = MEM32(ecx);
    edi = eax;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(edx + 0xC); PUSH32(esp, 0x00045DCCu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00045DCC: ;
    ecx = MEM32(esi + 8);
    MEM32(esi + 0x1C) = eax;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x00045DD8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00045DD8: ;
    MEM32(esi + 0x20) = eax;
    ecx = MEM32(eax + 0xC);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    SET_LO8(ecx, (CMP_A(_fa & _fb, 0)) ? 1 : 0); /* seta */
    MEM8(esi + 0x28) = LO8(ecx);
    ecx = MEM32(esi + 8);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x18); PUSH32(esp, 0x00045DEEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00045DEE: ;
    eax = MEM32(eax * 4 + 0x1F970C);
    MEM32(esi + 0x24) = eax;
    POP32(esp, edi);

loc_00045DF9: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00047DB0
 * Original: 0x00047DB0 - 0x00047ED2 (290 bytes, 99 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00047DB0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00047DB0: ;
    esp = esp - 0x1C;
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(MEM16(esi + 0x16)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(esi + 0x16), 0 (16-bit) */
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x28);
    if (CMP_EQ(_fa, _fb)) goto loc_00047EC0; /* je: equal / zero */

loc_00047DC6: ;
    eax = 0x7EFFFFFF;
    MEM32(edi) = eax;
    MEM32(edi + 4) = eax;
    MEM32(edi + 8) = eax;
    eax = 0xFEFFFFFFu;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    MEM32(edi + 0xC) = eax;
    MEM32(edi + 0x10) = eax;
    MEM32(edi + 0x14) = eax;
    ecx = MEM32(esi + 0x78);
    eax = MEM32(ecx + 0x10);
    edx = MEM32(ecx);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    MEM32(esp + 0x14) = eax;
    PUSH32(esp, 0);
    eax = esp + 0x38;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00047DFCu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00047DFC: ;
    eax = MEM32(esi + 0x10);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_BE(_fa & _fb, 0)) goto loc_00047EAF; /* jbe: below or equal (unsigned <=) */

loc_00047E09: ;
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x30);
    edi = edi;

loc_00047E10: ;
    ecx = ebp;
    edx = MEM32(ecx);
    eax = MEM32(ecx + 4);
    ecx = MEM32(ecx + 8);
    MEM32(esp + 0x18) = eax;
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x24); /* fmul dword ptr [esi + 0x24] */
    MEM32(esp + 0x1C) = ecx;
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    MEM32(esp + 0x14) = edx;
    fp_top() = fp_top() * MEMF(esi + 0x30); /* fmul dword ptr [esi + 0x30] */
    edx = esp + 0x20;
    PUSH32(esp, edx);
    ecx = edi;
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x18); /* fmul dword ptr [esi + 0x18] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x1C); /* fmul dword ptr [esi + 0x1c] */
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x28); /* fmul dword ptr [esi + 0x28] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 0x20)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x34); /* fmul dword ptr [esi + 0x34] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 0x20)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x38); /* fmul dword ptr [esi + 0x38] */
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x20); /* fmul dword ptr [esi + 0x20] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 0x1C)); /* fld float */
    fp_top() = fp_top() * MEMF(esi + 0x2C); /* fmul dword ptr [esi + 0x2c] */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    fp_top() = fp_top() + MEMF(esi + 0x3C); /* fadd dword ptr [esi + 0x3c] */
    MEMF(esp + 0x24) = (float)fp_top(); fp_pop(); /* fstp */
    fp_top() = fp_top() + MEMF(esi + 0x40); /* fadd dword ptr [esi + 0x40] */
    MEMF(esp + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x2C)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x44); /* fadd dword ptr [esi + 0x44] */
    MEMF(esp + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00047E9Cu); sub_00040230(); /* call 0x00040230 */

loc_00047E9C: ;
    ecx = MEM32(esp + 0x10);
    eax = MEM32(esi + 0x10);
    ebx++;
    ebp = ebp + ecx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00047E10; /* jb: below (unsigned <) */

loc_00047EAE: ;
    POP32(esp, ebp);

loc_00047EAF: ;
    ecx = MEM32(esi + 0x78);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0xC); PUSH32(esp, 0x00047EB7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00047EB7: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x1C;
    esp += 8; return; /* ret 4 */

loc_00047EC0: ;
    esi = esi + 0x48;
    ecx = 6;
    recomp_rep_movs(4); /* rep movsd */
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x1C;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0003B4D0
 * Original: 0x0003B4D0 - 0x0003B50B (59 bytes, 18 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003B4D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003B4D0: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x1E55D4;
    eax = MEM32(esi + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0003B4EB; /* je: equal / zero */

loc_0003B4E0: ;
    PUSH32(esp, eax);
    ecx = 0x3C6610;
    PUSH32(esp, 0x0003B4EBu); sub_0002E800(); /* call 0x0002E800 */

loc_0003B4EB: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0003B505; /* je: equal / zero */

loc_0003B4F2: ;
    MEM32(0x238ACC) = MEM32(0x238ACC) - 1;
    eax = MEM32(0x238AC8);
    MEM32(esi) = eax;
    MEM32(0x238AC8) = esi;

loc_0003B505: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E07E0
 * Original: 0x000E07E0 - 0x000E07E8 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E07E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000E07E0: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000E0FB0(); return; /* tail jmp 0x000E0FB0 */

}

/**
 * sub_000E0810
 * Original: 0x000E0810 - 0x000E0818 (8 bytes, 2 insns)
 * Category: game_vtable
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E0810(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */

loc_000E0810: ;
    ecx = ecx - MEM32(ecx + -4);
    g_seh_ebp = ebp; g_ebp = ebp; sub_000DD250(); return; /* tail jmp 0x000DD250 */

}

/**
 * sub_000E0FB0
 * Original: 0x000E0FB0 - 0x000E0FDD (45 bytes, 17 insns)
 * CC: cdecl, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E0FB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E0FB0: ;
    PUSH32(esp, esi);
    esi = ecx + -120;
    PUSH32(esp, edi);
    edi = esi + 0x78;
    ecx = edi;
    PUSH32(esp, 0x000E0FBFu); sub_000E06B0(); /* call 0x000E06B0 */

loc_000E0FBF: ;
    ecx = edi;
    PUSH32(esp, 0x000E0FC6u); sub_000DE840(); /* call 0x000DE840 */

loc_000E0FC6: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E0FD6; /* je: equal / zero */

loc_000E0FCD: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E0FD3u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_000E0FD3: ;
    esp = esp + 4;

loc_000E0FD6: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000DD250
 * Original: 0x000DD250 - 0x000DD41B (459 bytes, 151 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DD250(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_000DD250: ;
    esp = esp - 0x118;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x120);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, ebp (32-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    MEM32(esp + 0x1C) = 0;
    MEM32(esp + 0x20) = 0;
    MEM32(esp + 0x24) = 0;
    MEM32(esp + 0x14) = ebx;
    MEM32(esp + 0x18) = ebp;
    MEM8(esp + 0x28) = 0;
    esi = ebx;
    MEM32(esp + 0x10) = 0x3F800000;
    if (CMP_EQ(_fa, _fb)) goto loc_000DD33C; /* je: equal / zero */

loc_000DD29C: ;
    /* nop */

loc_000DD2A0: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, 3 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_000DD321; /* ja: above (unsigned >) */

loc_000DD2A5: ;
    { uint32_t _jt = MEM32(ebp * 4 + 0xDD41C); /* switch: 4 entries, 4 targets */
    if (_jt == 0x000DD2ACu) goto loc_000DD2AC;
    if (_jt == 0x000DD2E3u) goto loc_000DD2E3;
    if (_jt == 0x000DD302u) goto loc_000DD302;
    if (_jt == 0x000DD30Eu) goto loc_000DD30E;
    g_seh_ebp = ebp; g_ebp = ebp; RECOMP_ITAIL(_jt); return; }

loc_000DD2AC: ;
    eax = MEM32(edi + -120);
    ecx = MEM32(eax + 4);
    eax = ecx + edi;
    edx = esp + 0x10;
    PUSH32(esp, edx);
    ecx = eax + -76;
    PUSH32(esp, ecx);
    edx = eax + -72;
    PUSH32(esp, edx);
    eax = eax + 0xFFFFFFB0u;
    PUSH32(esp, eax);
    PUSH32(esp, 0x1F42B8);
    PUSH32(esp, esi);
    PUSH32(esp, 0x000DD2D1u); sub_00110B23(); /* call 0x00110B23 */

loc_000DD2D1: ;
    esp = esp + 0x18;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_000DD321; /* jge: greater or equal (signed >=) */

loc_000DD2D9: ;
    MEM32(esp + 0x10) = 0x3F800000;
    goto loc_000DD321;

loc_000DD2E3: ;
    eax = esp + 0x20;
    PUSH32(esp, eax);
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    edx = esp + 0x24;
    PUSH32(esp, edx);
    PUSH32(esp, 0x1F411C);
    PUSH32(esp, esi);
    PUSH32(esp, 0x000DD2FDu); sub_00110B23(); /* call 0x00110B23 */

loc_000DD2FD: ;
    esp = esp + 0x14;
    goto loc_000DD321;

loc_000DD302: ;
    eax = esp + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x1E27B4);
    goto loc_000DD318;

loc_000DD30E: ;
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x1F42B4);

loc_000DD318: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000DD31Eu); sub_00110B23(); /* call 0x00110B23 */

loc_000DD31E: ;
    esp = esp + 0xC;

loc_000DD321: ;
    PUSH32(esp, 0x20);
    PUSH32(esp, esi);
    PUSH32(esp, 0x000DD329u); sub_0010F330(); /* call 0x0010F330 */

loc_000DD329: ;
    esi = eax;
    esp = esp + 8;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DD333; /* je: equal / zero */

loc_000DD332: ;
    esi++;

loc_000DD333: ;
    ebp++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000DD2A0; /* jne: not equal / not zero */

loc_000DD33C: ;
    fp_push(MEMF(esp + 0x20)); /* fld float */
    edx = MEM32(edi + -120);
    fp_top() = fp_top() * MEMF(0x1F35C8); /* fmul dword ptr [0x1f35c8] */
    eax = MEM32(edx + 4);
    esp = esp - 0xC;
    ecx = eax + edi + -116;
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x28)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1F35C8); /* fmul dword ptr [0x1f35c8] */
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x30)); /* fld float */
    fp_top() = fp_top() * MEMF(0x1F35C8); /* fmul dword ptr [0x1f35c8] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x000DD377u); sub_00069B30(); /* call 0x00069B30 */

loc_000DD377: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(edi + -120);
    eax = MEM32(edx + 4);
    PUSH32(esp, ecx);
    ecx = eax + edi + -116;
    PUSH32(esp, 0x000DD38Bu); sub_000152B0(); /* call 0x000152B0 */

loc_000DD38B: ;
    esi = MEM32(esp + 0x18);
    ecx = MEM32(edi + -72);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM8(edi + -55) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_000DD3A1; /* je: equal / zero */

loc_000DD39E: ;
    MEM8(ecx + 0x12) = LO8(eax);

loc_000DD3A1: ;
    ecx = esp + 0x28;
    PUSH32(esp, ecx);
    ecx = 0x4AD508;
    PUSH32(esp, 0x000DD3B0u); sub_000DC790(); /* call 0x000DC790 */

loc_000DD3B0: ;
    edx = esp + 0x28;
    PUSH32(esp, edx);
    PUSH32(esp, ebx);
    MEM32(edi + -8) = eax;
    PUSH32(esp, 0x000DD3BEu); sub_0010F680(); /* call 0x0010F680 */

loc_000DD3BE: ;
    esp = esp + 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DD3DD; /* je: equal / zero */

loc_000DD3C5: ;
    ecx = esp + 0x28;
    esi = ecx + 1;
    /* nop */

loc_000DD3D0: ;
    SET_LO8(edx, MEM8(ecx));
    ecx++;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000DD3D0; /* jne: not equal / not zero */

loc_000DD3D7: ;
    ecx = ecx - esi;
    ecx = ecx + eax;
    goto loc_000DD3F5;

loc_000DD3DD: ;
    PUSH32(esp, 0x29);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x000DD3E5u); sub_00110280(); /* call 0x00110280 */

loc_000DD3E5: ;
    esp = esp + 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000DD3F1; /* je: equal / zero */

loc_000DD3EC: ;
    eax++;
    MEM32(esp + 0x14) = eax;

loc_000DD3F1: ;
    ecx = MEM32(esp + 0x14);

loc_000DD3F5: ;
    SET_LO8(eax, MEM8(ecx));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_000DD410; /* je: equal / zero */

loc_000DD3FF: ;
    /* nop */

loc_000DD400: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x20 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000DD408; /* je: equal / zero */

loc_000DD404: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(9) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 9 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000DD410; /* jne: not equal / not zero */

loc_000DD408: ;
    SET_LO8(eax, MEM8(ecx + 1));
    ecx++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000DD400; /* jne: not equal / not zero */

loc_000DD410: ;
    eax = ecx;
    esp = esp + 0x118;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00047BF0
 * Original: 0x00047BF0 - 0x00047BF6 (6 bytes, 2 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00047BF0(void)
{

loc_00047BF0: ;
    eax = MEM32(ecx + 0x78);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00047D10
 * Original: 0x00047D10 - 0x00047D16 (6 bytes, 2 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00047D10(void)
{

loc_00047D10: ;
    eax = MEM32(ecx + 0x74);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00047D20
 * Original: 0x00047D20 - 0x00047D25 (5 bytes, 2 insns)
 * Category: game_vtable
 * CC: thiscall, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00047D20(void)
{

loc_00047D20: ;
    eax = ZX16(MEM16(ecx + 0x14));
    esp += 4; return; /* ret */

}

/**
 * sub_0003EAB0
 * Original: 0x0003EAB0 - 0x0003EACF (31 bytes, 11 insns)
 * Category: game_vtable
 * CC: thiscall, 1 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003EAB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003EAB0: ;
    _fa = (uint32_t)(MEM8(esp + 4)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 4), 1 (8-bit) */
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x1E5C4C;
    if (TEST_Z(_fa, _fb)) goto loc_0003EAC9; /* je: equal / zero */

loc_0003EAC0: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0003EAC6u); sub_0010F0F2(); /* call 0x0010F0F2 */

loc_0003EAC6: ;
    esp = esp + 4;

loc_0003EAC9: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0002E7C0
 * Original: 0x0002E7C0 - 0x0002E7F4 (52 bytes, 17 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002E7C0(void)
{

loc_0002E7C0: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    esi = ecx;
    PUSH32(esp, edi);
    ecx = esi + 4;
    PUSH32(esp, 0x0002E7D1u); sub_0002E550(); /* call 0x0002E550 */

loc_0002E7D1: ;
    edx = MEM32(esi + 0x18C);
    ecx = MEM32(esi + 0x188);
    edx--;
    MEM32(esi + 0x18C) = edx;
    eax = MEM32(edi + 0x38);
    ecx = ecx - eax;
    POP32(esp, edi);
    MEM32(esi + 0x188) = ecx;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * Vtable-only attachment copy helper.  The retail body copies the source
 * packet's type field into the freshly allocated clone.
 * Original: 0x00039500 - 0x0003950D
 */
void sub_00039500(void)
{
    eax = MEM32(esp + 4);
    edx = MEM32(eax + 0x10);
    MEM32(ecx + 0x10) = edx;
    esp += 8; return; /* ret 4 */
}

/** Original: 0x00039560 - 0x00039588 */
void sub_00039560(void)
{
    uint32_t _fa = 0, _fb = 0;
    eax = MEM32(ecx + 0x10);
    _fa = eax; _fb = eax;
    if (TEST_Z(_fa, _fb)) goto loc_0003957A;
    eax = MEM32(eax);
    ecx = MEM32(ecx + 0x18);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0xC);
    PUSH32(esp, 0x00039577u); sub_00109D90();
    esp += 8; return;
loc_0003957A:
    ecx = MEM32(esp + 4);
    PUSH32(esp, 0xFFFFFFFFu);
    PUSH32(esp, 0x00039585u); sub_0010A2A0();
    esp += 8; return;
}

/**
 * Vtable-only menu attachment updater recovered from the retail XBE.
 * Original: 0x000399F0 - 0x00039B2D
 */
void sub_000399F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edi = ecx;
    MEM32(edi + 0xC) &= 0xFFFFFFFEu;
    edx = ZX8(MEM8(esi + 2));
    ebx = 0;
    eax = 0;
    _fa = edx; _fb = ebx; _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_LE(_fas, _fbs)) goto loc_00039A28;

    ecx = esi + 0x24;
    PUSH32(esp, ebp);
loc_00039A10:
    _fa = MEM16(ecx); _fb = 0x1F;
    _fas = (int16_t)_fa; _fbs = (int16_t)_fb;
    if (CMP_AE(_fa, _fb)) goto loc_00039A24;
    ebp = ZX8(MEM8(esi + 2));
    eax++;
    ecx += 0xC;
    _fa = eax; _fb = ebp; _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_L(_fas, _fbs)) goto loc_00039A10;
    goto loc_00039A27;
loc_00039A24:
    edx += 3;
loc_00039A27:
    POP32(esp, ebp);

loc_00039A28:
    _fa = edx; _fb = 7; _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_G(_fas, _fbs)) goto loc_00039A3B;
    ecx = esi;
    PUSH32(esp, 0x00039A34u); sub_0010B350();
    _fa = eax; _fb = ebx; _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    MEM32(edi + 0x18) = eax;
    if (CMP_GE(_fas, _fbs)) goto loc_00039A43;

loc_00039A3B:
    POP32(esp, edi);
    POP32(esp, esi);
    SET_LO8(eax, 1);
    POP32(esp, ebx);
    esp += 8; return;

loc_00039A43:
    eax = MEM32(esi + 0x10);
    _fa = eax; _fb = ebx;
    if (CMP_EQ(_fa, _fb)) goto loc_00039AB0;
    _fa = eax; _fb = 5;
    if (CMP_EQ(_fa, _fb)) goto loc_00039AB0;

    eax = ZX8(MEM8(esi + 2));
    eax += 3;
    ecx = eax + eax * 2;
    eax = 1;
    MEM16(esi + ecx * 4) = LO16(eax);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x26) = LO8(eax);
    ecx = ZX8(MEM8(esi + 2));
    edx = MEM32(edi + 0x18);
    SET_LO8(edx, MEM8(edx * 4 + 0x226808));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x27) = LO8(edx);
    ecx = ZX8(MEM8(esi + 2));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x28) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x29) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x2A) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x2B) = LO8(ebx);
    goto loc_00039B12;

loc_00039AB0:
    eax = ZX8(MEM8(esi + 2));
    eax += 3;
    ecx = eax + eax * 2;
    eax = 1;
    MEM16(esi + ecx * 4) = LO16(eax);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x26) = LO8(eax);
    edx = MEM32(edi + 0x18);
    ecx = ZX8(MEM8(esi + 2));
    SET_LO8(edx, MEM8(edx * 4 + 0x226808));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x27) = LO8(edx);
    ecx = ZX8(MEM8(esi + 2));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x28) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x29) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    ecx = ecx + ecx * 2;
    MEM8(esi + ecx * 4 + 0x2A) = LO8(ebx);
    ecx = ZX8(MEM8(esi + 2));
    edx = ecx + ecx * 2;
    MEM8(esi + edx * 4 + 0x2B) = LO8(ebx);
    MEM32(esi + 0x10) = eax;

loc_00039B12:
    SET_LO8(ebx, MEM8(esi + 2));
    SET_LO8(edx, MEM8(esi));
    SET_LO8(ebx, LO8(ebx) + 1);
    MEM8(esi + 2) = LO8(ebx);
    MEM32(esi + 0xC) = eax;
    SET_LO8(edx, LO8(edx) | 0x80);
    MEM8(esi) = LO8(edx);
    MEM32(edi + 0xC) |= eax;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return;
}
