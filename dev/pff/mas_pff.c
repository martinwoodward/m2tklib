/*

  mas_pff.c
  
  mass storage device for petite fat file system (http://elm-chan.org/fsw/ff/00index_p.html)

  part of m2tklib (Mini Interative Interface Toolkit Library)
  
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

#include <string.h>
#include "mas.h"
#include "pff.h"

FATFS mas_pff_fs;
DIR mas_pff_dir;
FILINFO mas_pff_fi;

static uint8_t mas_pff_init(uint8_t chip_select)
{
  FRESULT fr;
  fr = pf_mount(&mas_pff_fs);
  if ( fr == FR_OK )
    return 1;
  return 0;
}

/*
  Description:
    Requrest for a specific file at a specified position within the directory
*/

static uint8_t mas_pff_get_nth_file(const char *path, uint16_t n, char *buf, uint8_t *is_dir)
{
  FRESULT fr;
  uint16_t c = 0;
  fr = pf_opendir(&mas_pff_dir, path);
  if ( fr != FR_OK )
    return 0;
  
  while( c < 0x0ffff)
  {
    fr = pf_readdir(&mas_pff_dir, &mas_pff_fi);
    if ( fr != FR_OK )
      return 0;
    if ( mas_pff_fi.fname[0] == '\0' )
      return 0;
    if ( c == n )
    {
      strcpy(buf, mas_pff_fi.fname);
      if ( (mas_pff_fi.fattrib & AM_DIR) != 0 )
      {
        *is_dir = 1;
      }
      else
      {
        *is_dir = 0;        
      }
      return 1;
    }
    c++;
  }
  return 0;
}

static uint16_t mas_pff_get_cnt(const char *path)
{
  FRESULT fr;
  uint16_t c = 0;
  fr = pf_opendir(&mas_pff_dir, path);
  if ( fr != FR_OK )
    return 0;
  
  while( c < 0x0ffff)
  {
    fr = pf_readdir(&mas_pff_dir, &mas_pff_fi);
    if ( fr != FR_OK )
      break;
    c++;
  }
  return c;
}


uint8_t mas_device_pff(uint8_t msg, void *arg)
{
  if ( msg == MAS_MSG_GET_DIR_ENTRY_AT_POS )
  {
    mas_arg_get_dir_entry_at_pos_t *a = ((mas_arg_get_dir_entry_at_pos_t *)arg);
    return mas_pff_get_nth_file(a->path, a->n, a->buf, &(a->is_dir));
  }
  else if ( msg == MAS_MSG_GET_DIR_ENTRY_CNT )
  {
    mas_arg_get_dir_entry_cnt_t *a = ((mas_arg_get_dir_entry_cnt_t *)arg);    
    a->cnt = mas_pff_get_cnt(a->path);
    return 1;
  }
  else if ( msg == MAS_MSG_INIT )
  {
    mas_arg_init_t *a = ((mas_arg_init_t *)arg);   
    return mas_pff_init(a->cs_pin);
  }
  return 0;
}

