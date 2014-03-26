#include <cstdio>

int main(int argc, const char* argv[])
{
  printf(" === Trying (-1), (0), (1), and (1.231) ===\n");

  printf("%%f : %f\n", -1);
  printf("%%f : %f\n", 0);
  printf("%%f : %f\n", 1);
  printf("%%f : %f\n", 1.231);

  printf("%%d : %d\n", -1);
  printf("%%d : %d\n", 0);
  printf("%%d : %d\n", 1);
  printf("%%d : %d\n", 1.231);

  printf("%%u : %u\n", -1);
  printf("%%u : %u\n", 0);
  printf("%%u : %u\n", 1);
  printf("%%u : %u\n", 1.231);
}
