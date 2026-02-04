#pragma once

/* Including libraries */
#include <stdint.h>
#include "../../include/type.h"

/* Function prototypes */
u8 rex(int w, int r, int x, int b);
u8 modrm(u8 mod, u8 reg, u8 rm);
u8 sib(u8 scale, u8 index, u8 base);

int imm16(u8* out, u16 v);
int imm32(u8* out, u32 v);
int imm64(u8* out, u64 v);