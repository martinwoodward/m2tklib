/*

  m2ghu8gutl.c
  
  utility procedures for the u8g graphics handler
  
  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2012  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "m2.h"
#include "m2ghu8g.h"

u8g_t *m2_u8g = NULL;
u8g_uint_t m2_u8g_height_minus_one;
uint8_t m2_u8g_fg_text_color;
uint8_t m2_u8g_bg_text_color;
uint8_t m2_u8g_current_text_color;
uint8_t m2_u8g_draw_color;

uint8_t m2_gh_u8g_current_depth;
uint8_t m2_gh_u8g_invert_at_depth = 255;



void m2_SetU8g(u8g_t *u8g)
{
  m2_u8g = u8g;
  m2_u8g_height_minus_one = u8g_GetHeight(u8g);
  m2_u8g_height_minus_one--;
  
  /* force lower left edge of a text as reference */
  u8g_SetFontPosBottom(m2_u8g);

  m2_u8g_fg_text_color = u8g_GetDefaultForegroundColor(m2_u8g);
  m2_u8g_bg_text_color = u8g_GetDefaultBackgroundColor(m2_u8g);
  m2_u8g_current_text_color = m2_u8g_fg_text_color;
  m2_u8g_draw_color = u8g_GetDefaultForegroundColor(m2_u8g);
}

void m2_u8g_draw_frame(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  u8g_uint_t y;
  y = m2_u8g_height_minus_one;
  y -= y0;
  y -= h;
  u8g_SetColorIndex(m2_u8g, m2_u8g_draw_color);
  u8g_DrawFrame(m2_u8g, x0, y, w, h);
  /*
  printf("draw_frame: x=%d y=%d w=%d h=%d\n", x0, y, w, h);
  */
}

void m2_u8g_draw_frame_shadow(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  u8g_uint_t y;
  y = m2_u8g_height_minus_one;
  y -= y0;
  y -= h;
  w--;
  h--;
  u8g_SetColorIndex(m2_u8g, m2_u8g_draw_color);
  u8g_DrawFrame(m2_u8g, x0, y, w, h);
  u8g_DrawVLine(m2_u8g, x0+w, y+1, h);
  u8g_DrawHLine(m2_u8g, x0+1, y+h, w);
  
}

void m2_u8g_draw_box(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  u8g_uint_t y;
  y = m2_u8g_height_minus_one;
  y -= y0;
  y -= h;
  u8g_SetColorIndex(m2_u8g, m2_u8g_draw_color);
  u8g_DrawBox(m2_u8g, x0, y, w, h);
}



/*
  00000000 0x00
  01111110 0x7e
  01000010 0x42
  01000010 0x42
  01000010 0x42
  01000010 0x42
  01111110 0x7e
  00000000 0x00

  00000000 0x00
  01111111 0x7f
  01000011 0x43
  01100110 0x66
  01111110 0x7e
  01011010 0x5a
  01111110 0x7e
  00000000 0x00

dog_pgm_uint8_t m2_dogm_icon0[8] = {0x00, 0x7e, 0x042, 0x042, 0x042, 0x042, 0x07e, 0x00};
dog_pgm_uint8_t m2_dogm_icon1[8] = {0x00, 0x7f, 0x043, 0x066, 0x07e, 0x05a, 0x07e, 0x00};


  11111111 0xff
  10000001 0x81
  10000001 0x81
  10000001 0x81
  10000001 0x81
  10000001 0x81
  10000001 0x81
  11111111 0xff

  11111111 0xff
  10000001 0x81
  10111101 0xbd
  10111101 0xbd
  10111101 0xbd
  10111101 0xbd
  10000001 0x81
  11111111 0xff

*/

u8g_pgm_uint8_t m2_u8g_icon0[8] = {0x0ff, 0x081, 0x081, 0x081, 0x081, 0x081, 0x081, 0x0ff};
u8g_pgm_uint8_t m2_u8g_icon1[8] = {0x0ff, 0x081, 0x0bd, 0x0bd, 0x0bd, 0x0bd, 0x081, 0x0ff};

/*
#define M2_ICON_TOGGLE_ACTIVE 1
#define M2_ICON_TOGGLE_INACTIVE 2 
#define M2_ICON_RADIO_ACTIVE 3
#define M2_ICON_RADIO_INACTIVE 4
*/

void m2_u8g_draw_icon(uint8_t x, uint8_t y, uint8_t font, uint8_t icon)
{
  const u8g_pgm_uint8_t *ptr = m2_u8g_icon0;
  if ( icon == M2_ICON_TOGGLE_ACTIVE || icon == M2_ICON_RADIO_ACTIVE )
    ptr = m2_u8g_icon1;
  //dog_SetBitmapP(x,y+7,ptr,8,8);

  u8g_SetColorIndex(m2_u8g, m2_u8g_current_text_color);
  u8g_DrawBitmapP(m2_u8g, x, m2_u8g_height_minus_one - (y+8), 1, 8, ptr);
}

uint8_t m2_u8g_get_icon_height(uint8_t font, uint8_t icon)
{
  return 8;
}

uint8_t m2_u8g_get_icon_width(uint8_t font, uint8_t icon)
{
  return 8;
}


const u8g_fntpgm_uint8_t *m2_gh_u8g_fonts[4];
int8_t m2_gh_u8g_ref_dx[4];

const u8g_fntpgm_uint8_t *m2_u8g_get_font(uint8_t font)
{
  font &= 3;
  return m2_gh_u8g_fonts[font];
}

int8_t m2_u8g_get_reference_delta_x(uint8_t font)
{
  font &= 3;
  return m2_gh_u8g_ref_dx[font];
}


uint8_t m2_gh_u8g_base(m2_gfx_arg_p  arg)
{
  /* Do a safety check here: Abort if m2_SetU8g has not been called */
  if ( m2_u8g == NULL )
    return 0;


  /* Proceed with normal message processing */
  switch(arg->msg)
  {
    case M2_GFX_MSG_INIT:		
      break;
    case M2_GFX_MSG_START:
      break;
    case M2_GFX_MSG_END:
      break;
    case M2_GFX_MSG_DRAW_HLINE:
      u8g_DrawHLine(m2_u8g, arg->x, m2_u8g_height_minus_one - arg->y, arg->w);
      break;
    case M2_GFX_MSG_DRAW_VLINE:
      u8g_DrawVLine(m2_u8g, arg->x, m2_u8g_height_minus_one - arg->y, arg->h);  
      break;
    case M2_GFX_MSG_DRAW_BOX:
      m2_u8g_draw_box(arg->x, arg->y, arg->w, arg->h);
      break;
    case M2_GFX_MSG_DRAW_TEXT:
      {
	      u8g_uint_t x = arg->x;
	      u8g_uint_t y;

        u8g_SetColorIndex(m2_u8g, m2_u8g_current_text_color);
        u8g_SetFont(m2_u8g, m2_u8g_get_font(arg->font));
        u8g_SetFontPosBottom(m2_u8g);
              
	      if ( (arg->font & 8) != 0 )
        {
	        if ( arg->w != 0 )
	        {
	          x = arg->w;
	          x -= u8g_GetStrWidth(m2_u8g, arg->s);
	          x >>= 1;
	          x += arg->x;
	        }
        }
        y = m2_u8g_height_minus_one;
	      y -= arg->y;
          x -= u8g_GetStrX(m2_u8g, arg->s);
	      u8g_DrawStr(m2_u8g, x, y, arg->s);
        // printf("DRAW_TEXT: x=%d y=%d s=%s\n", x, y, arg->s);
      }
      break;
    case M2_GFX_MSG_DRAW_TEXT_P:
      {
	      u8g_uint_t x = arg->x;
	      u8g_uint_t y;
        
        u8g_SetColorIndex(m2_u8g, m2_u8g_current_text_color);
        u8g_SetFont(m2_u8g, m2_u8g_get_font(arg->font));
        u8g_SetFontPosBottom(m2_u8g);
        
	      if ( (arg->font & 8) != 0 )
        {
	        if ( arg->w != 0 )
	        {
	          x = arg->w;
	          x -= u8g_GetStrWidthP(m2_u8g, (const u8g_pgm_uint8_t *)arg->s);
	          x >>= 1;
	          x += arg->x;
	        }
        }
        y = m2_u8g_height_minus_one;
      	y -= arg->y;
        x -= u8g_GetStrXP(m2_u8g, (const u8g_pgm_uint8_t *)arg->s);
      	u8g_DrawStrP(m2_u8g, x, y, (const u8g_pgm_uint8_t *)arg->s);
      }
      break;
    case M2_GFX_MSG_SET_FONT:
      {
	      uint8_t idx;
	      idx = arg->font;
	      idx &=3;
	      m2_gh_u8g_fonts[idx] = (const u8g_fntpgm_uint8_t *)(arg->s);
        u8g_SetFont(m2_u8g, m2_gh_u8g_fonts[idx]);
        m2_gh_u8g_ref_dx[idx] = u8g_GetGlyphDeltaX(m2_u8g, 'm');
      }
      return 0;
    case M2_GFX_MSG_GET_TEXT_WIDTH:
      u8g_SetFont(m2_u8g, m2_u8g_get_font(arg->font));
      return u8g_GetStrPixelWidth(m2_u8g, arg->s);
    case M2_GFX_MSG_GET_TEXT_WIDTH_P:
      u8g_SetFont(m2_u8g, m2_u8g_get_font(arg->font));
      return u8g_GetStrPixelWidthP(m2_u8g, (const u8g_pgm_uint8_t *)arg->s);
    case M2_GFX_MSG_GET_CHAR_WIDTH:
      return m2_u8g_get_reference_delta_x(arg->font);
    case M2_GFX_MSG_GET_CHAR_HEIGHT:
      u8g_SetFont(m2_u8g, m2_u8g_get_font(arg->font));
      return u8g_GetFontLineSpacing(m2_u8g);
      
    case M2_GFX_MSG_GET_DISPLAY_WIDTH:
      /* printf("display width = %d\n", (int)u8g_GetWidth(m2_u8g)); */
      return u8g_GetWidth(m2_u8g);
    case M2_GFX_MSG_GET_DISPLAY_HEIGHT:
      /* printf("display height = %d\n", (int)u8g_GetHeight(m2_u8g)); */
      return u8g_GetHeight(m2_u8g);
    case M2_GFX_MSG_DRAW_VERTICAL_SCROLL_BAR:
      /* scroll bar: "total" total number of items */
      /* scroll bar: "top" topmost item (first visible item) 0 .. total-visible*/
      /* scroll bar: "visible" number of visible items 0 .. total-1 */

      m2_u8g_draw_frame(arg->x, arg->y, arg->w, arg->h);
      {
      	uint16_t h, y;
	
       	h = m2_utl_sb_get_slider_height(arg->h-2, arg->total, arg->visible);
      	y = m2_utl_sb_get_slider_position(arg->h-2, h, arg->total, arg->visible, arg->top); 	
      	m2_u8g_draw_box(arg->x+1, arg->y+arg->h-1-h-y, arg->w-2, h);
      }
      return 1;
    case M2_GFX_MSG_DRAW_ICON:
      m2_u8g_draw_icon(arg->x, arg->y, arg->font, arg->icon);
      break;
    case M2_GFX_MSG_GET_ICON_WIDTH:
      return m2_u8g_get_icon_width(arg->font, arg->icon);
    case M2_GFX_MSG_GET_ICON_HEIGHT:
      return m2_u8g_get_icon_height(arg->font, arg->icon);
    
    /*
      The following two messages are used to track the current depth within the gfx driver.
      As soon as the depth changes, the current depth is assigned to the variable m2_gh_u8g_current_depth
      At any depth the gfx drive can decide to invert the font, marked by m2_gh_u8g_invert_at_depth.
      m2_gh_u8g_invert_at_depth must be set in the driver, however it is reset by LEVEL_UP
    */
    case M2_GFX_MSG_LEVEL_DOWN:
      //printf("down %d\n", arg->top);
      m2_gh_u8g_current_depth = arg->top;
      break;
    case M2_GFX_MSG_LEVEL_UP:
      // printf("up %d\n", arg->top);
      m2_gh_u8g_current_depth = arg->top;
      if ( m2_gh_u8g_invert_at_depth+1 >= m2_gh_u8g_current_depth )
      {
        // printf("invert remove %d\n", m2_gh_u8g_invert_at_depth);
        m2_gh_u8g_invert_at_depth = 255;
      }
      break;
  }
  return m2_gh_dummy(arg);
}


