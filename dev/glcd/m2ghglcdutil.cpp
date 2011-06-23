/*

  m2ghglcdutil.cpp
  
  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

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
#include <glcd.h>
#include "fonts/Arial14.h"         
#include "fonts/SystemFont5x7.h"

uint8_t m2_is_glcd_init = 0;

extern "C" uint8_t m2_gh_glcd_y(uint8_t y)
{
  uint8_t val;
  val = GLCD.Height;
  val--;
  val -= y;
  return val;
}

extern "C" uint8_t m2_gh_glcd_get_font_height(m2_gfx_arg_p  arg)
{
  if ( (arg->font & 1) == 0 )
    return 8;
  return 16;    
}

extern "C" uint8_t m2_gh_glcd_get_font_corrcetion(m2_gfx_arg_p  arg)
{
  if ( (arg->font & 1) == 0 )
    return 1;
  return 2;    
}

extern "C" void m2_gh_glcd_set_font(uint8_t font)
{
  font &= 1;
  if ( font == 0 )
      GLCD.SelectFont(System5x7); 
  else 
      GLCD.SelectFont(Arial14); 
}

/* y0 is in m2 coordinate system, (x0,y0) = (0,0) = lower left edge  */
extern "C" void m2_gh_glcd_draw_frame(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  w--;
  h--;
  y0 +=h;
  GLCD.DrawRect(x0, m2_gh_glcd_y(y0), w, h);
}

/* y0 is in m2 coordinate system, (x0,y0) = (0,0) = lower left edge  */
extern "C" void m2_gh_glcd_draw_xorbox(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  w--;
  h--;
  y0 +=h;
  GLCD.InvertRect(x0, m2_gh_glcd_y(y0), w, h);
}
