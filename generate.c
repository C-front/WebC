#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FuncType)(FILE *fp, void*);

int generate(FuncType func,char file_name[],   void* args) {
  size_t html_size;
  FILE *fp;
  fp = fopen(file_name, "w");
  if (fp == NULL) {
    return 1;
  }
  func(fp, args);
  fclose(fp);
  return 0;
}