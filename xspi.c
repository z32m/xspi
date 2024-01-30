#include <xspi.h>
#include <string.h>

#define STATIC_BUF_SIZE 16

int spi_write_read(struct spi_dt_spec *spi, void *send, size_t send_len, void *recv, size_t recv_len)
{
    size_t buf_size = send_len + recv_len;

    uint8_t tx_st[STATIC_BUF_SIZE];
    uint8_t rx_st[STATIC_BUF_SIZE];

    uint8_t *tx_buffer = buf_size > STATIC_BUF_SIZE ? k_malloc(buf_size) : tx_st;
    uint8_t *rx_buffer = buf_size > STATIC_BUF_SIZE ? k_malloc(buf_size) : rx_st;

    memset(tx_buffer, 0, buf_size);
    memset(tx_buffer, 0, buf_size);
    memcpy(tx_buffer, send, send_len);

    const struct spi_buf tx_buf = {
        .buf = tx_buffer,
        .len = buf_size};

    struct spi_buf rx_buf = {
        .buf = rx_buffer,
        .len = buf_size,
    };

    const struct spi_buf_set rx = {
        .buffers = &rx_buf,
        .count = recv_len};

    const struct spi_buf_set tx = {
        .buffers = &tx_buf,
        .count = send_len};

    int err = spi_transceive_dt(spi, &tx, &rx);

    if (recv_len > 0)
        memcpy(recv, rx_buffer + send_len, recv_len);

    if (buf_size > STATIC_BUF_SIZE)
    {
        k_free(tx_buffer);
        k_free(rx_buffer);
    }
    
    return err;
}
