#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srm.h"

void print_usage()
{
  printf("Usage: srm [options] <file/folder> [file/folder] [file/folder] ...\n");
  printf("Options:\n");
  printf("  --list           List deleted files\n");
  printf("  --restore <file> Restore a deleted file\n");
  printf("  --restore-all    Restore all deleted files\n");
  printf("  --purge          Permanently delete all files in /recycle\n");
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    print_usage();
    return 1;
  }

  if (strcmp(argv[1], "--list") == 0)
  {
    srm_list();
  }
  else if (strcmp(argv[1], "--restore") == 0)
  {
    if (argc < 3)
    {
      fprintf(stderr, "Error: Specify a file to restore.\n");
      return 1;
    }
    srm_restore(argv[2]);
  }
  else if (strcmp(argv[1], "--restore-all") == 0)
  {
    srm_restore_all();
  }
  else if (strcmp(argv[1], "--purge") == 0)
  {
    srm_purge();
  }
  else
  {
    for (int i = 1; i < argc; i++) {
      srm_move_to_recycle(argv[i]);
    }
  }

  return 0;
}
