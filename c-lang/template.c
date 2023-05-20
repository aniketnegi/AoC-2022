#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2 || *argv[1] != 'a' || *argv[1] != 's') {
    fprintf(stderr, "USAGE: %s <(a)ctual>/<(s)ample>", argv[0]);
    return -1;
  }
  char choice = *argv[1];
  char *file_name;

  if (choice == 'a') {
    char *file_name = "../data/day%d/actual.txt";
  } else {
    char *file_name = "../data/day%d/sample.txt";
  }

  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    fprintf(stderr, "Problems in opening the FILE\n");
    return -1;
  }

  char buffer[100];

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    fprintf(stdout, "%s\n", buffer);
  }

  fclose(file);

  return 0;
}
