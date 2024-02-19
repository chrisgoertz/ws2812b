/**
 * @file ws2812b.h
 * @author Christian Görtz (chris.goertz@gmx.de)
 * @brief Easy to use NeoPixel library.
 * Makes use of Timer1 controlled via DMA.
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef WS2812B_H_
#define WS2812B_H_

#ifdef __cplusplus
  extern "C"{
#endif

/* includes */
#include <stdint.h>

/* Constants */
#define WS2812_FB_SIZE (16)

/* Structs */
typedef struct{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
}RGB_Color_t;

/**
 * @brief set all pixels in framebuffer to off state.
 * 
 */
void ws2812_fb_clear();

/**
 * @brief write the framebuffer to led strip.
 * 
 */
void ws2812_fb_send();

/**
 * @brief Configure one particular pixel in framebuffer.
 * 
 * @param color: RGB_Color_t
 * @param pos: pixel position in framebuffer.
 */
void ws2812_fb_set(RGB_Color_t color, uint32_t pos);

/**
 * @brief Write one Pixel direct to led strip.
 * 
 * @param red: int
 * @param green: int
 * @param blue: int
 */
void ws2812_send(int red, int green, int blue);

/**
 * @brief Write one Pixel direct to led strip.
 * 
 * @param c: RGB_Color_t
 */
void ws2812_send_color(RGB_Color_t c);

/**
 * @brief Wait the reset period
 * 
 */
void ws2812_reset();

/**
 * @brief Write red pixel to led strip.
 * 
 */
void ws2812_red();

/**
 * @brief Write green pixel to led strip.
 * 
 */
void ws2812_green();

/**
 * @brief Write blue pixel to led strip.
 * 
 */
void ws2812_blue();

/**
 * @brief Test the led strip.
 * 
 */
void ws2812_test();
#ifdef __cplusplus
  }
#endif
#endif /* WS2812B_H_ */
