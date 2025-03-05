#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "srm.h"

#define RECYCLE_DIR "/recycle/"

void srm_move_to_recycle(const char *path)
{
  printf("Moving %s to %s\n", path, RECYCLE_DIR);
  // TODO: Implement file move logic with random prefix
}

void srm_list()
{
  printf("Listing files in %s\n", RECYCLE_DIR);
  // TODO: Implement file listing
}

void srm_restore(const char *filename)
{
  printf("Restoring %s\n", filename);
  // TODO: Implement restore logic
}

void srm_restore_all()
{
  printf("Restoring all files from %s\n", RECYCLE_DIR);
  // TODO: Implement restore all logic
}

void srm_purge()
{
  printf("Permanently deleting all files in %s\n", RECYCLE_DIR);
  // TODO: Implement purge logic
}
