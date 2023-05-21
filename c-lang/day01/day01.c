#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rstrip(char *buffer);
int compare_reverse(const void *a, const void *b);

int main(int argc, char **argv) {
  if (argc != 3 || (*argv[1] != 'a' && *argv[1] != 's')) {
    fprintf(stderr, "USAGE: %s <(a)ctual>/<(s)ample> <sum of top n calories>\n",
            argv[0]);
    return -1;
  }
  char choice = *argv[1];
  char *file_name;

  if (choice == 'a') {
    file_name = "actual.txt";
  } else {
    file_name = "sample.txt";
  }

  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    fprintf(stderr, "Problems in opening the FILE\n");
    return -1;
  }

  int calories[1000], count = 0;
  int curr_sum = 0;
  char line[100];

  while (fgets(line, sizeof(line), file) != NULL) {
    if (strcmp(line, "\n") == 0) {
      calories[count] = curr_sum;
      curr_sum = 0;
      count++;
      continue;
    }

    rstrip(line);

    curr_sum += atoi(line);
  }

  qsort(calories, count, sizeof(calories[0]), compare_reverse);

  // Part One
  fprintf(stdout, "The Elf with the max Calories has %d Calories in his bag.\n",
          calories[0]);

  // Part Two
  int ans_sum = 0;
  for (int i = 0; i < atoi(argv[2]); i++) {
    ans_sum += calories[i];
  }
  fprintf(stdout,
          "The elves with the top 3 most Calories have %d calories in total.\n",
          ans_sum);

  fclose(file);

  return 0;
}

void rstrip(char *buffer) {
  size_t s = strlen(buffer);
  if (s && (buffer[s - 1] == '\n')) {
    buffer[--s] = 0;
  }
}

int compare_reverse(const void *a, const void *b) {
  const int *num1 = (const int *)a;
  const int *num2 = (const int *)b;
  // Compare in reverse order
  if (*num1 < *num2) {
    return 1;
  } else if (*num1 > *num2) {
    return -1;
  } else {
    return 0;
  }
}
