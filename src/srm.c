#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "srm.h"

#define RECYCLE_DIR "/recycle/"
#define METADATA_FILE "/recycle/.metadata"

/**
 * Generates a random prefix for the file.
 */
void generate_random_prefix(char *buffer, size_t length)
{
  srand(time(NULL));
  snprintf(buffer, length, "%08x", rand());
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

/**
 * Moves a file or folder to the recycle directory.
 */
void srm_move_to_recycle(const char *path)
{
  struct stat path_stat;

  // Check if file/folder exists
  if (stat(path, &path_stat) != 0)
  {
    perror("Error: File does not exist");
    return;
  }

  // Ensure /recycle/ directory exists
  if (access(RECYCLE_DIR, F_OK) != 0)
  {
    if (mkdir(RECYCLE_DIR, 0777) != 0)
    {
      perror("Error creating /recycle/ directory");
      return;
    }
  }

  // Generate random prefix
  char prefix[9];
  generate_random_prefix(prefix, sizeof(prefix));

  // Extract filename from path
  const char *filename = strrchr(path, '/');
  filename = (filename) ? filename + 1 : path;

  // Construct new path
  char new_path[512];
  snprintf(new_path, sizeof(new_path), "%s%s_%s", RECYCLE_DIR, prefix, filename);

  // Move the file
  if (rename(path, new_path) != 0)
  {
    perror("Error moving file");
    return;
  }

  // Store original path in metadata
  FILE *meta = fopen(METADATA_FILE, "a");
  if (meta)
  {
    fprintf(meta, "%s %s\n", new_path, path);
    fclose(meta);
  }
  else
  {
    perror("Error writing metadata");
  }

  printf("Moved '%s' to '%s'\n", path, new_path);
}
