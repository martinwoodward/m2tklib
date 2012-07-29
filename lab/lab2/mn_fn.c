/*

  mn_fn.c
  
*/


#include "mn.h"
#include <stdlib.h>

int mn_fn_empty(mn_type mn, int msg, void *arg)
{
  switch(msg)
  {
    case MN_MSG_NONE:
      break;
    case MN_MSG_OPEN:
      break;
    case MN_MSG_CLOSE:
      break;
    case MN_MSG_COPY:
      break;
    case MN_MSG_GET_DISPLAY_STRING:
      *(char **)arg = "empty";
      return 1;
  }
  return 1;
}

