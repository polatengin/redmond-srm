#ifndef SRM_H

#define SRM_H

void srm_move_to_recycle(const char *path);
void srm_list();
void srm_restore(const char *filename);
void srm_restore_all();
void srm_purge();

#endif
