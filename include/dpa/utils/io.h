#ifndef DPA_UTILS_IO_H
#define DPA_UTILS_IO_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>

#include <stdio.h>

#define dpa_u_fwrite(bo, io) fwrite(dpa_u_bo_data((bo)), dpa_u_bo_get_size((bo)), 1, (io))
#define dpa_u_fputs(bo, io) dpa_u_fwrite((bo),(io))
#define dpa_u_puts(bo) (dpa_u_fputs(dpa_u_v_bo_ro((bo)),stdout),puts(""))

#endif
