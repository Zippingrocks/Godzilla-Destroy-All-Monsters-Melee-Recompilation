#include <stdio.h>
#include <string.h>
#include "nv2a_vsh_emulator.h"

static const uint32_t program51[][4] = {
    {0,0x00EC001B,0x08361800,0x20B08800}, {0,0x00EC201B,0x08363800,0x20B04800},
    {0,0x00EC401B,0x08365800,0x20B02800}, {0,0x00EC601B,0x08367800,0x20B01800},
    {0,0x0047401A,0xC4355800,0x20B0E800}, {0,0x06AD351A,0x9C3553FF,0x10B88858},
    {0,0x02000C00,0x0800106D,0xA0A0F84C}, {0,0x02000C00,0x0800106D,0xA0A0F854},
    {0,0x00AD371A,0x9C357000,0x20B04858}, {0,0x00AD271A,0x9C347000,0x20902858},
    {0,0x00AD551A,0xAC355000,0x20908860}, {0,0x00AD571A,0xAC357000,0x20B04860},
    {0,0x00AD471A,0xAC347000,0x20A02860}, {0,0x00CC601B,0x08367800,0x20A08828},
    {0,0x0087601A,0xC400286A,0xF0B0E801},
};

static void set4(float *bank, int i, float x, float y, float z, float w)
{
    float *p = bank + i * 4;
    p[0] = x; p[1] = y; p[2] = z; p[3] = w;
}

int main(void)
{
    Nv2aVshProgram program;
    Nv2aVshCPUFullExecutionState full;
    Nv2aVshExecutionState state = nv2a_vsh_emu_initialize_full_execution_state(&full);
    Nv2aVshParseResult parsed;
    memset(&full, 0, sizeof(full));
    state = nv2a_vsh_emu_initialize_full_execution_state(&full);

    set4(full.input_regs, 0, -78.7576f, 7.82109f, 1.0f, 1.0f);
    set4(full.input_regs, 3, -0.69727f, 0.117539f, 0.707107f, 1.0f);
    set4(full.input_regs, 6, 0.0911693f, 0.216476f, 0.0f, 1.0f);
    set4(full.input_regs, 7, 1.0f, 1.0f, 1.0f, 1.0f);
    set4(full.input_regs, 10, 0.716809f, 0.114335f, 0.687832f, 1.0f);
    set4(full.input_regs, 11, 5.96047e-8f, -0.986465f, 0.163975f, 1.0f);

    set4(full.context_regs, 58, 320.0f, -240.0f, 16777215.0f, 0.0f);
    set4(full.context_regs, 59, 320.531f, 240.531f, 0.0f, 0.0f);
    set4(full.context_regs, 60, 0.0f, 0.5f, 1.0f, 2.0f);
    set4(full.context_regs, 61, -1.0f, 0.0f, 1.0f, 2.0f);
    set4(full.context_regs, 62, 0.0f, 0.0f, -1.0f, 0.0f);
    set4(full.context_regs, 96, 1.66581f, 0.0f, 0.0f, 0.0f);
    set4(full.context_regs, 97, 0.0f, 1.87384f, -1.19244f, -284.115f);
    set4(full.context_regs, 98, -1.07879e-37f, -0.49442f, -0.776946f, 405.535f);
    set4(full.context_regs, 99, -1.07771e-37f, -0.493925f, -0.776169f, 406.13f);
    set4(full.context_regs, 103, 0.0f, 0.5f, 1.0f, 2.0f);
    set4(full.context_regs, 105, 0.0f, 0.0f, -0.0f, 1.0f);
    set4(full.context_regs, 106, 0.0f, 0.0f, -0.0f, 1.0f);
    set4(full.context_regs, 113, 0.0f, 0.0f, 0.0f, 1.0f);

    parsed = nv2a_vsh_parse_program(&program, &program51[0][0],
                                    sizeof(program51) / sizeof(program51[0]));
    printf("parse=%d\n", (int)parsed);
    if (parsed != NV2AVPR_SUCCESS) return 1;
    nv2a_vsh_emu_execute(&state, &program);
    for (int i = 0; i < 13; ++i) {
        float *v = full.output_regs + i * 4;
        printf("o%d=(%.9g,%.9g,%.9g,%.9g)\n", i, v[0], v[1], v[2], v[3]);
    }
    nv2a_vsh_program_destroy(&program);
    return 0;
}
