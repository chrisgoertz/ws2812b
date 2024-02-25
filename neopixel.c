#include "neopixel.h"
#include "main.h"



void neopixel_bar(RGB_Color_t color, uint16_t from, uint16_t to){
    
    for(uint16_t i = from; (i < to) && (i <= WS2812_FB_SIZE); i++){
        ws2812_fb_set(color, i);
    }

}

void neopixel_pxl(RGB_Color_t color, uint16_t pos){
    ws2812_fb_set(color, pos);
}

void update(uint32_t rt){
    static uint16_t index = 0;
    static uint16_t pxlPos = 0;
    RGB_Color_t color ={10,10,10};
    if(index >= 10000){
        ws2812_fb_clear();
        neopixel_pxl(color, pxlPos++ );
        ws2812_fb_send();
        if(pxlPos >= WS2812_FB_SIZE){
            pxlPos = 0;
        }
        index = 0;
    }
    index++;
}
