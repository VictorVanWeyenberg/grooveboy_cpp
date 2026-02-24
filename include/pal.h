#ifndef PAL_H
#define PAL_H

#define MEM_PAL 0x05000000

#define MEM_BG_PAL ((uint16_t *)(MEM_PAL))
#define MEM_OBJ_PAL ((uint16_t *)(MEM_PAL + 0x200))

void write_background_palette(Binary data);
void write_object_palette(Binary data);

#endif
