#ifndef EDIT_SCREEN_CALLBACKS_H
#define EDIT_SCREEN_CALLBACKS_H

#include <cstdint>

void toggle_play_pause();
void change_pattern(uint8_t channel);
void change_note(uint8_t channel, uint8_t note);

#endif