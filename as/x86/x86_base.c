/* Including header file */
#include "x86_base.h"

u8
rex(int w, int r, int x, int b) {
	return 0x40
			| (w<<3)
			| (r<<2)
			| (x<<1)
			| b;
}

u8
modrm(u8 mod, u8 reg, u8 rm) {
	return (mod << 6)
			| ((reg & 7) << 3)
			| (rm & 7);
}

u8
sib(u8 scale, u8 index, u8 base) {
	return (scale << 6)
			| ((index & 7) << 3)
			| (base & 7);
}

/* Basic byte writer for Opcodes and Prefixes */
int
emit_u8(u8* out, u8 v) {
	out[0] = v;
	return 1;
}

/* For multi byte values, write 
   to an array and return the size. */
int
imm8(u8* out, u8 v) {
	out[0] = v;
	return 1;
}

int
imm16(u8* out, u16 v) {
	out[0] = v & 0xFF;
	out[1] = v >> 8;
	return 2;
}

int
imm32(u8* out, u32 v) {
	out[0] = v;
	out[1] = v >> 8;
	out[2] = v >> 16;
	out[3] = v >> 24;
	return 4;
}

int
imm64(u8* out, u64 v) {
	imm32(out, v);
	imm32(out + 4, v >> 32);
	return 8;
}

/* Displacement wrappers (for clarity) */
int
disp8(u8* out, u8 v) {
	out[0] = v;
	return 1;
}

int
disp32(u8* out, u32 v) {
	out[0] = v;
	out[1] = v >> 8;
	out[2] = v >> 16;
	out[3] = v >> 24;
	return 4;
}