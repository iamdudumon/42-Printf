#include "ft_printf.h"

void clean_buffer(t_buffer *buf, int *res)
{
    if (buf->len > 0)
    {
        write(1, buf->content, buf->len);
        *res += buf->len;
        buf->len = 0;
    }
}

void store_buffer(t_buffer *buf, int *res, char ch)
{
    if (buf->len == BUFFER_SIZE)
        clean_buffer(buf, res);
    buf->content[buf->len] = ch;
    buf->content[buf->len + 1] = '\0';
    (buf->len)++;
}