#include "ws2812b.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define RESET_PULSES (10)
#define DATABITS (24)
#define DATASIZE (DATABITS + RESET_PULSES)

extern TIM_HandleTypeDef htim1;
extern bool datasendflag;
RGB_Color_t framebuffer[WS2812_FB_SIZE];

void ws2812_fb_clear() { memset(framebuffer, 0x00, WS2812_FB_SIZE * 3); }

void ws2812_fb_send() {
  for (uint32_t i = 0; i < WS2812_FB_SIZE; i++) {
    ws2812_send_color(framebuffer[i]);
  }
}

void ws2812_fb_set(RGB_Color_t color, uint32_t pos) {
  framebuffer[pos] = color;
}

void ws2812_send(int red, int green, int blue) {
  uint32_t data = (green << 16) | (red << 8) | blue;
  uint32_t indx = 0;
  const uint32_t HIGH_CLOCKS = (htim1.Init.Period * 2) / 3;
  const uint32_t LOW_CLOCKS = htim1.Init.Period / 3;
  volatile uint16_t pwmData[DATASIZE];

  /* format data */
  for (int i = (DATABITS - 1); i >= 0; i--) {

    if (data & (1 << i)) {
      pwmData[indx++] = HIGH_CLOCKS;
    } else {
      pwmData[indx++] = LOW_CLOCKS;
    }
  }
  /* wait reset period */
  for (int i = 0; i < RESET_PULSES; i++) {
    pwmData[indx++] = 0;
  }

  /* Send data to led strip */
  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, DATASIZE);
  /* WAIT until DMA has send the data */
  while (!datasendflag) {
  };
  /* ready to write next data */
  datasendflag = false;
}

void ws2812_send_color(RGB_Color_t c) { ws2812_send(c.red, c.green, c.blue); }

void ws2812_reset() {
  uint16_t pwmData[RESET_PULSES];
  for (int i = 0; i < RESET_PULSES; i++) {
    pwmData[i] = 0;
  }
  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData,
                        RESET_PULSES);
  while (!datasendflag) {
  };
  datasendflag = false;
}

void ws2812_red() { ws2812_send(5, 0, 0); }

void ws2812_green() { ws2812_send(0, 5, 0); }

void ws2812_blue() { ws2812_send(0, 0, 5); }

void ws2812_off() { ws2812_send(0, 0, 0); }

void ws2812_test(int t) {
  RGB_Color_t red = {5, 0, 0};
  RGB_Color_t green = {0, 10, 0};
  RGB_Color_t blue = {0, 0, 10};

  switch (t) {
  case 0:
    for (uint8_t i = 0; i < WS2812_FB_SIZE; i++) {
      ws2812_fb_set(red, i);
    }
    break;
  case 1:
    ws2812_fb_set(blue, 5);
    break;
  case 2:
    ws2812_fb_set(green, 9);
    break;
  case 3:
    ws2812_fb_clear();
    break;
  }
  ws2812_fb_send();
}

