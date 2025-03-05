#ifndef SRM_H

#define SRM_H

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"  // Errors
#define COLOR_GREEN   "\033[32m"  // Success
#define COLOR_YELLOW  "\033[33m"  // Warnings
#define COLOR_BLUE    "\033[34m"  // Info

void srm_move_to_recycle(const char *path);
void srm_list();
void srm_restore(const char *filename);
void srm_restore_all();
void srm_purge();

#endif
