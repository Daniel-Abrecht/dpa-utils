#ifndef DPA_UTILS_IO_H
#define DPA_UTILS_IO_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>
#include <stdio.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-io IO Functions
 * @{
 * Some utility functions for doing IO, writing to files and such, using data from BOs.
 */

/**
 * Write the contents of a BO to a file
 * \param bo The BO
 * \param io The file to write to
 * \returns -1 on error
 */
#define dpa_u_fputs(bo, io) dpa_u_fwrite((bo),(io))
/**
 * \copydoc dpa_u_fputs
 */
#define dpa_u_fwrite(bo, io) dpa_u_fwrite_p(dpa_u_to_bo((bo)), (io))
dpa__u_api inline size_t dpa_u_fwrite_p(dpa_u_bo_t bo, FILE* io){
  return fwrite(dpa_u_bo_get_data(bo), 1, dpa_u_bo_get_size(bo), io);
}

/**
 * Write a BO to stdout, followed by a newline
 * \param bo The BO
 * \returns -1 on error
 */
#define dpa_u_puts(bo) dpa_u_puts_p(dpa_u_to_bo((bo)))
dpa__u_api inline int dpa_u_puts_p(dpa_u_bo_t bo){
  fwrite(dpa_u_bo_get_data(bo), 1, dpa_u_bo_get_size(bo), stdout);
  return puts("");
}

/** @} */
/** @} */

#endif
