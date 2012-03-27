/*

  m2ghu8gfb.c
  
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


  problem:
      text entry with select (no auto down):
      text field has NORMAL_FOCUS, child char receive NORMAL_NO_FOCUS
      one solution would be to apply the level information

*/

#include "m2.h"
#include "m2ghu8g.h"

/*
  focus cursor: box
  buttom style: frame
*/

uint8_t m2_gh_u8g_bf(m2_gfx_arg_p  arg)
{
  switch(arg->msg)
  {
    case M2_GFX_MSG_DRAW_NORMAL_NO_FOCUS:
      if ( (arg->font & 4) != 0 )
      {
        m2_u8g_current_text_color = m2_u8g_fg_text_color;
      	m2_u8g_draw_frame(arg->x, arg->y, arg->w, arg->h);
      }
      else
      {
        m2_u8g_current_text_color = m2_u8g_fg_text_color;
      }
      break;
    case M2_GFX_MSG_DRAW_NORMAL_PARENT_FOCUS:
      break;
    case M2_GFX_MSG_DRAW_NORMAL_FOCUS:
      if ( (arg->font & 4) != 0 )
      {
        m2_u8g_current_text_color = m2_u8g_bg_text_color;
      }
      else
      {
        m2_u8g_current_text_color = m2_u8g_bg_text_color;
      }
      m2_u8g_draw_box(arg->x, arg->y, arg->w, arg->h);
      break;
    case M2_GFX_MSG_DRAW_SMALL_FOCUS:
      m2_u8g_current_text_color = m2_u8g_bg_text_color;
      m2_u8g_draw_box(arg->x, arg->y, arg->w, arg->h);
      break;
    case M2_GFX_MSG_DRAW_NORMAL_DATA_ENTRY:
      m2_u8g_current_text_color = m2_u8g_fg_text_color;
      u8g_DrawHLine(m2_u8g, arg->x, m2_u8g_height_minus_one - arg->y, arg->w);
      break;
    case M2_GFX_MSG_DRAW_SMALL_DATA_ENTRY:
      m2_u8g_current_text_color = m2_u8g_fg_text_color;
      u8g_DrawHLine(m2_u8g, arg->x, m2_u8g_height_minus_one - arg->y, arg->w);
      break;
    case M2_GFX_MSG_DRAW_GO_UP:
      /* does not work because of missing xor...
         also: can not be fixed with FRAME_DRAW_AT_END
       m2_u8g_current_text_color = m2_u8g_bg_text_color; */
      m2_u8g_draw_box(arg->x, arg->y, arg->w, arg->h/2);
      break;
    case M2_GFX_MSG_DRAW_ICON:
      m2_u8g_draw_icon(arg->x, arg->y, arg->font, arg->icon);
      break;
    case M2_GFX_MSG_GET_NORMAL_BORDER_HEIGHT:
      if ( (arg->font & 4) != 0 )
	return 2;
      return 0;
    case M2_GFX_MSG_GET_NORMAL_BORDER_WIDTH:
      if ( (arg->font & 4) != 0 )
	return 2;
      return 0;
    case M2_GFX_MSG_GET_NORMAL_BORDER_X_OFFSET:
      if ( (arg->font & 4) != 0 )
	return 1;
      return 0;
    case M2_GFX_MSG_GET_NORMAL_BORDER_Y_OFFSET:
      if ( (arg->font & 4) != 0 )
	return 1;
      return 0;
    case M2_GFX_MSG_GET_SMALL_BORDER_HEIGHT:
      return 0;
    case M2_GFX_MSG_GET_SMALL_BORDER_WIDTH:
      return 0;
    case M2_GFX_MSG_GET_SMALL_BORDER_X_OFFSET:
      return 0;
    case M2_GFX_MSG_GET_SMALL_BORDER_Y_OFFSET:
      return 0;
      
    case M2_GFX_MSG_GET_READONLY_BORDER_HEIGHT:
      return 0;
    case M2_GFX_MSG_GET_READONLY_BORDER_WIDTH:
      return 0;
    case M2_GFX_MSG_GET_READONLY_BORDER_X_OFFSET:
      return 0;
    case M2_GFX_MSG_GET_READONLY_BORDER_Y_OFFSET:
      return 0;
    case M2_GFX_MSG_GET_LIST_OVERLAP_HEIGHT:
      return 0;
    case M2_GFX_MSG_GET_LIST_OVERLAP_WIDTH:
      return 0;
    case M2_GFX_MSG_GET_ICON_WIDTH:
      return m2_u8g_get_icon_width(arg->font, arg->icon);
    case M2_GFX_MSG_GET_ICON_HEIGHT:
      return m2_u8g_get_icon_height(arg->font, arg->icon);
    case M2_GFX_MSG_IS_FRAME_DRAW_AT_END:
      return 0; /* focus (highlight) is drawn first, then the text string */
  }

  return m2_gh_u8g_base(arg);
}
