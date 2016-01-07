#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char src[] = "hello";
  char dst[] = "world";

  char *result = strcat(dst, "hello");

  printf("%s", result);
  return 0;
}
