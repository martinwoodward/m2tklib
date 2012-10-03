/*

  m2elstr.c
  
  base class for any string elements

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

#include <stddef.h>
#include "m2.h"
#include <string.h>

#ifdef M2_EL_MSG_DBG_SHOW
#include <stdio.h>
#endif

uint8_t m2_el_xbm_get_w(m2_el_fnarg_p fn_arg)
{
  return m2_rom_get_u8(fn_arg->element, offsetof(m2_el_xbm_t, w));
}

uint8_t m2_el_xbm_get_h(m2_el_fnarg_p fn_arg)
{
  return m2_rom_get_u8(fn_arg->element, offsetof(m2_el_xbm_t, h));
}

const char *m2_el_xbm_get_ptr(m2_el_fnarg_p fn_arg)
{
  return (const char *)m2_rom_get_rom_ptr(fn_arg->element, offsetof(m2_el_xbm_t, ptr));
}


M2_EL_FN_DEF(m2_el_xbmlabelp_fn)
{
  uint8_t font = 0;

  
  switch(fn_arg->msg)
  {
    case M2_EL_MSG_GET_LIST_LEN:
      return 0;  /* not a list, return 0 */
     case M2_EL_MSG_IS_READ_ONLY:
      return 1;
    case M2_EL_MSG_GET_HEIGHT:
      return m2_gfx_add_readonly_border_height(m2_el_fmfmt_opt_get_val_zero_default( fn_arg, 'b' ), font, m2_el_xbm_get_h(fn_arg));
    case M2_EL_MSG_GET_WIDTH:
      return m2_gfx_add_readonly_border_width(m2_el_fmfmt_opt_get_val_zero_default( fn_arg, 'b' ), font, m2_el_xbm_get_w(fn_arg));
#ifdef M2_EL_MSG_DBG_SHOW
    case M2_EL_MSG_DBG_SHOW:
      return 0;
#endif
    case M2_EL_MSG_SHOW:
      {
        m2_pos_p b = (m2_pos_p)(fn_arg->data);
	
	if ( m2_is_frame_draw_at_end == 0 )
	  m2_el_fnfmt_fn(fn_arg);
	
	m2_gfx_draw_xbm_p_add_readonly_border_offset(
	  m2_el_fmfmt_opt_get_val_zero_default( fn_arg, 'b' ), 
	  b->x, 
	  b->y, 
	  m2_el_xbm_get_w(fn_arg),
	  m2_el_xbm_get_h(fn_arg),
	  m2_el_xbm_get_ptr(fn_arg));
	
      	if ( m2_is_frame_draw_at_end != 0 )
	        m2_el_fnfmt_fn(fn_arg);
      }
      return 1;    
  }
  return m2_el_fnfmt_fn(fn_arg);
}

m2_rom_void_p m2_el_xbmroot_get_ae(m2_el_fnarg_p fn_arg)
{
  return (m2_rom_void_p)m2_rom_get_ram_ptr(fn_arg->element, offsetof(m2_el_xbmroot_t, element));
}

M2_EL_FN_DEF(m2_el_xbmrootp_fn)
{
  uint8_t font = 0;
  
  switch(fn_arg->msg)
  {
    case M2_EL_MSG_GET_LIST_LEN:
      return 0;  /* not a list, return 0 */
    case M2_EL_MSG_GET_HEIGHT:
      return m2_gfx_add_normal_border_height(font, m2_el_xbm_get_h(fn_arg));
    case M2_EL_MSG_GET_WIDTH:
      return m2_gfx_add_normal_border_width(font, m2_el_xbm_get_w(fn_arg));
#ifdef M2_EL_MSG_DBG_SHOW
    case M2_EL_MSG_DBG_SHOW:
      return 0;
#endif
    case M2_EL_MSG_SHOW:
      {
        m2_pos_p b = (m2_pos_p)(fn_arg->data);
	
	if ( m2_is_frame_draw_at_end == 0 )
	  m2_el_fnfmt_fn(fn_arg);

      m2_gfx_draw_xbm_p_add_normal_border_offset(
	  b->x, 
	  b->y, 
	  m2_el_xbm_get_w(fn_arg),
	  m2_el_xbm_get_h(fn_arg),
	  m2_el_xbm_get_ptr(fn_arg));
	
	
      	if ( m2_is_frame_draw_at_end != 0 )
	        m2_el_fnfmt_fn(fn_arg);
      }
      return 1;    
    case M2_EL_MSG_SELECT:
      m2_nav_set_root(fn_arg->nav,  m2_el_xbmroot_get_ae(fn_arg), m2_el_fmfmt_opt_get_val_zero_default(fn_arg, 'n'), m2_el_fmfmt_opt_get_val_zero_default(fn_arg, 'v'));
      return 1;
  }
  return m2_el_fnfmt_fn(fn_arg);
}

