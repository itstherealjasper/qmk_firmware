/**
 * Utilities for QMK oled animations
 *
 * Copyright (c) Marek Piechut
 * MIT License
 */
#pragma once

//-------- CONFIGURATION START --------
#ifndef ANIM_FRAME_TIME
#    define ANIM_FRAME_TIME 20
#endif
//-------- CONFIGURATION END--------

#define ANIM_WPM_WIDTH 22
#define OLED_ROWS OLED_DISPLAY_HEIGHT / 4

static uint32_t anim_timer = 0;
static uint8_t current_frame = 255;

static void oled_render_anim_frame(const char **frames, uint8_t frames_len) {

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_TIME) { 
        anim_timer = timer_read32();

        if (current_frame < frames_len) {
            const char *frame = frames[current_frame];
            oled_write_raw(frame, 512);
            current_frame++;
        } else {
            oled_clear();
        }
    }
}

static void activate_animation(void) {
    current_frame = 0;
}