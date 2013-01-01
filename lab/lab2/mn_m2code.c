/*

  mn_m2code.c 
  
  Helper functions to generate the code
  
*/
  
#include "stddef.h"
#include "stdio.h"
#include "mn.h"

/*================================================*/


void mn_BuildCodeStr(const char *s)
{
  printf("%s", s);
}

void mn_BuildCodeLabel(mn_type n)
{
  mn_BuildCodeStr(mn_GetLabelString(n));  
}

void mn_BuildCodeListLabel(mn_type n)
{
  mn_BuildCodeStr("list_");
  mn_BuildCodeStr(mn_GetLabelString(n));  
}

/* build M2_LIST with all sub elements */
void mn_BuildCodeListStatement(mn_type n)
{
  int is_first = 1;
  mn_BuildCodeStr("M2_LIST(");
  mn_BuildCodeListLabel(n);
  mn_BuildCodeStr(") = {");
  
  n = n->d;
  while( n != NULL )
  {
    if ( is_first == 0 )
    {
      mn_BuildCodeStr(",");
    }
    is_first = 0;
    mn_BuildCodeStr("&");
    mn_BuildCodeLabel(n);
  }
  mn_BuildCodeStr("};\n");
}

static void mn_BuildCodeSub(mn_type n)
{
  mn_type d;
  if ( n == NULL )
    return;
  d = n->d;
  while( d != NULL )
  {
    mn_BuildCodeSub(d);
    d = d->n;
  }
  n->fn(n, MN_MSG_C_CODE, NULL);
}

void mn_BuildCode(mn_type n)
{
  mn_BuildSeqNr(n, 1);
  mn_BuildCodeSub(n);
}

