// RUN: %clangxx_asan  %s -o %t
// RUN: not %run %t   2>&1 | FileCheck %s --check-prefix=CHECK --check-prefix=A1
// RUN: not %run %t 1 2>&1 | FileCheck %s --check-prefix=CHECK --check-prefix=A2
// RUN: %env_asan_opts=intercept_memmem=0 %run %t

#include <string.h>
int main(int argc, char **argv) {
  char a1[] = {1, 2, 3, 4, 5, 6, 7, 8};
  char a2[] = {3, 4, 5};
  void *res;
  if (argc == 1)
    res = memmem(a1, sizeof(a1) + 1, a2, sizeof(a2));  // BOOM
  else
    res = memmem(a1, sizeof(a1), a2, sizeof(a2) + 1);  // BOOM
  // CHECK: AddressSanitizer: stack-buffer-overflow
  // CHECK: {{#0.*memmem}}
  // CHECK: {{#1.*main}}
  // A1: 'a1' <== Memory access at offset
  // A2: 'a2' <== Memory access at offset
  return res == NULL;
}
