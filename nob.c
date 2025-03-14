#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "lib/nob.h"
#include <string.h>

#define BUILD_FOLDER "build/"

#define builder_cc(cmd) cmd_append(cmd, "cc")
#define builder_output(cmd, output_path) cmd_append(cmd, "-o", output_path)
#define builder_inputs(cmd, ...) cmd_append(cmd, __VA_ARGS__)
#define builder_libs(cmd) cmd_append(cmd, "-lm")
#define builder_flags(cmd)                                                     \
  cmd_append(cmd, "-Wall", "-Wextra", "-Wswitch-enum", "-ggdb")
#define builder_include_path(cmd, include_path)                                \
  cmd_append(cmd, temp_sprintf("-I%s", include_path))

int main(int argc, char *argv[]) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  const char *program_name = shift(argv, argc);

  Nob_Cmd cmd = {0};

  builder_cc(&cmd);
  builder_inputs(&cmd, "main.c");
  builder_output(&cmd, "main");
  builder_libs(&cmd);
  builder_flags(&cmd);

  if (!cmd_run_sync_and_reset(&cmd))
    return 1;

  if (argc <= 0)
    return 0;

  const char *command_name = shift(argv, argc);
  if (strcmp(command_name, "run") == 0) {
    cmd_append(&cmd, "./main");
    if (!cmd_run_sync_and_reset(&cmd))
      return 1;
  } else {
    nob_log(ERROR, "Invalid command");
  }

  return 0;
}
