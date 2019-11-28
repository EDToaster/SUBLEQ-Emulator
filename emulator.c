#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INFINITY 1000000

void run(int64_t *program) {
  int64_t pc = 0;

  while (pc >= 0) {
    int64_t *instruction = &program[pc];

    pc += 3;

    if (instruction[0] == -1) {
      //stdin
      program[instruction[1]] = getchar();
    } else if (instruction[1] == -1) {
      //stdout
      putchar(program[instruction[0]]);
      fflush(stdout);
    } else {
      program[instruction[1]] -= program[instruction[0]];

      if (program[instruction[1]] <= 0) {
        pc = instruction[2];
      }
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  size_t pc = 0;
  int64_t *program = malloc(INFINITY * sizeof(uint32_t));
  while (fscanf(fp, "%ld", &program[pc++]) > 0);
  fclose(fp);

  run(program);


  return 0;

}