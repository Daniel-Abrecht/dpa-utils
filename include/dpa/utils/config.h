/**
 * \file
 * \copydoc dpa-u-config
 */
/**
 * \addtogroup dpa-u-utils Utils
 * @{
 * \addtogroup dpa-u-config Config
 * @{
 * This is an empty placeholder config file.
 * When building & installing the library, if you need special config options, use the `make config=/path/to/config`.
 * That will set the DPA_U_CONFIG macro, and then include the file.
 * Using one of the presets in the `mk/` folder using `make use=target` may do the same.
 * After installation with `make install`, this config file will be replaced with the specified config file.
 * When using the installed library, you can also use the DPA_U_CONFIG macro to include any config file you want.
 *
 * Here are some macros which can be overwritten in the config:
 * | Name | Description |
 * |------|-------------|
 * | DPA_U_NO_THREADS | Disable things related to c11 thread and atomics. No longer make things thread save. Useful if C11 threads are not available. |
 * | DPA_U_SEED_SIZE | \copydoc DPA_U_SEED_SIZE |
 * | DPA_U_THREADS_POLYFILL | \copydoc DPA_U_THREADS_POLYFILL |
 *
 * This program assumes the `endian.h` exists, and contains the `BYTE_ORDER`, as defined by POSIX.
 * Some systems do not have it. If you define the `BYTE_ORDER` macro in this config, you won't need the `endian.h` config.
 * @}
 * @}
 */
