#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
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
  FILE *meta = fopen(METADATA_FILE, "r");
  if (!meta)
  {
    perror(COLOR_YELLOW "No deleted files found." COLOR_RESET);
    return;
  }

  char stored_new_path[512], stored_original_path[512];

  printf(COLOR_BLUE "Deleted Files:\n" COLOR_RESET);
  printf("-----------------------------\n");

  while (fscanf(meta, "%s %s", stored_new_path, stored_original_path) == 2)
  {
    printf(COLOR_GREEN "Original: %s\n" COLOR_RESET, stored_original_path);
    printf(COLOR_YELLOW "Stored as: %s\n" COLOR_RESET, stored_new_path);
    printf("-----------------------------\n");
  }

  fclose(meta);
}

void srm_restore(const char *filename)
{
  FILE *meta = fopen(METADATA_FILE, "r");
  if (!meta)
  {
    perror(COLOR_RED "Error opening metadata file" COLOR_RESET);
    return;
  }

  char temp_file[] = "/recycle/.metadata_tmp";
  FILE *temp = fopen(temp_file, "w");
  if (!temp)
  {
    perror(COLOR_RED "Error creating temp metadata file" COLOR_RESET);
    fclose(meta);
    return;
  }

  char line[1024], stored_new_path[512], stored_original_path[512];
  int restored = 0;

  while (fgets(line, sizeof(line), meta))
  {
    if (sscanf(line, "%s %s", stored_new_path, stored_original_path) != 2)
    {
      continue; // Skip invalid lines
    }

    // Check if the file to restore matches the stored filename
    const char *stored_filename = strrchr(stored_new_path, '_');
    if (stored_filename && strcmp(stored_filename + 1, filename) == 0)
    {
      // Move the file back
      if (rename(stored_new_path, stored_original_path) == 0)
      {
        printf(COLOR_BLUE "Restored '%s' to '%s'\n" COLOR_RESET, filename, stored_original_path);
        restored = 1;
        continue; // Skip writing this entry back to metadata
      }
      else
      {
        perror("Error restoring file");
      }
    }

    // Keep other metadata entries
    fprintf(temp, "%s %s\n", stored_new_path, stored_original_path);
  }

  fclose(meta);
  fclose(temp);

  // Replace old metadata file with updated version
  rename(temp_file, METADATA_FILE);

  if (!restored)
  {
    printf(COLOR_RED "File '%s' not found in /recycle/\n" COLOR_RESET, filename);
  }
}

void srm_restore_all()
{
  FILE *meta = fopen(METADATA_FILE, "r");
  if (!meta)
  {
    perror("Error opening metadata file");
    return;
  }

  char stored_new_path[512], stored_original_path[512];
  int restored_count = 0;

  while (fscanf(meta, "%s %s", stored_new_path, stored_original_path) == 2)
  {
    if (rename(stored_new_path, stored_original_path) == 0)
    {
      printf("Restored: %s -> %s\n", stored_new_path, stored_original_path);
      restored_count++;
    }
    else
    {
      perror("Error restoring file");
    }
  }

  fclose(meta);

  // Remove metadata file if all files were restored
  if (restored_count > 0)
  {
    remove(METADATA_FILE);
    printf("All files restored successfully!\n");
  }
  else
  {
    printf("No files found to restore.\n");
  }
}

void srm_purge()
{
  DIR *dir = opendir(RECYCLE_DIR);
  if (!dir)
  {
    perror(COLOR_RED "Error opening /recycle/" COLOR_RESET);
    return;
  }

  struct dirent *entry;
  char filepath[512];

  while ((entry = readdir(dir)) != NULL)
  {
    // Skip "." and ".." directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
    {
      continue;
    }

    // Construct full file path
    snprintf(filepath, sizeof(filepath), "%s%s", RECYCLE_DIR, entry->d_name);

    // Remove the file
    if (remove(filepath) != 0)
    {
      perror(COLOR_RED "Error deleting file" COLOR_RESET);
    }
    else
    {
      printf(COLOR_YELLOW "Deleted: %s\n" COLOR_RESET, filepath);
    }
  }

  closedir(dir);

  // Remove the metadata file
  if (remove(METADATA_FILE) == 0)
  {
    printf(COLOR_YELLOW "Deleted metadata file.\n" COLOR_RESET);
  }

  printf(COLOR_GREEN "Recycle bin purged successfully.\n" COLOR_RESET);
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
