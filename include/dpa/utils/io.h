#ifndef DPA_UTILS_IO_H
#define DPA_UTILS_IO_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>

#include <stdio.h>

dpa_u_export inline size_t dpa_u_fwrite_p(dpa_u_bo_simple_ro_t bo, FILE* io){
  return fwrite(dpa_u_bo_data(bo), 1, dpa_u_bo_get_size(bo), io);
}
#define dpa_u_fwrite(bo, io) dpa_u_fwrite_p(dpa_u_t_bo_simple_ro((bo)), (io))
#define dpa_u_fputs(bo, io) dpa_u_fwrite((bo),(io))
dpa_u_export inline int dpa_u_puts_p(dpa_u_bo_simple_ro_t bo){
  fwrite(dpa_u_bo_data(bo), 1, dpa_u_bo_get_size(bo), stdout);
  return puts("");
}
#define dpa_u_puts(bo) dpa_u_puts_p(dpa_u_t_bo_simple_ro((bo)))

#endif
