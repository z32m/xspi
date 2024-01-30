#ifndef __xspi_h__
#define __xspi_h__

#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>

int spi_write_read(struct spi_dt_spec *spi, void *send, size_t send_len, void *recv, size_t recv_len);
#define spi_write(spi, send, send_len) spi_write_read(spi, send, send_len, NULL, 0)

#endif