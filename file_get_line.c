#include "nickdun.h"
/**
 * input_buf - Buffer chained command
 * @info: param struct
 * @buf:  buff address
 * @len:  buff address
 *
 * Return: Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
        ssize_t f = 0;
        size_t len_p = 0;

        if (!*len) /* if nothg left in the bufr, fill it */
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                f = getline(buf, &len_p, stdin);
#else
                f = _getline(info, buf, &len_p);
#endif
                if (f > 0)
                {
                        if ((*buf)[f - 1] == '\n')
                        {
                                (*buf)[f - 1] = '\0'; /* remove trailing newline */
                                f--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';')) is this a command chain? */
                        {
                                *len = f;
                                info->cmd_buf = buf;
                        }
                }
        }
        return (f);
}

/**
 * get_input - obtain line minus newline
 * @info: param struct
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
        static char *buf; /* the ';' command chain buffer */
        static size_t i, j, len;
        ssize_t f = 0;
        char **buf_p = &(info->arg), *p;

        _putchar(BUF_FLUSH);
        f = input_buf(info, &buf, &len);
        if (f == -1) /* EOF */
                return (-1);
        if (len) /* we have commands left in the chain buffer */
        {
                j = i; /* init new iterator to current buf position */
                p = buf + i; /* get pointer for return */

                check_chain(info, buf, &j, i, len);
                while (j < len) /* iterate to semicolon or end */
                {
                        if (is_chain(info, buf, &j))
                                break;
                        j++;
                }

                i = j + 1; /* increment past nulled ';'' */
                if (i >= len) /* reached end of buffer? */
                {
                        i = len = 0; /* reset position and length */
                        info->cmd_buf_type = CMD_NORM;
                }

                *buf_p = p; /* pass back pointer to current command position */
                return (_strlen(p)); /* return length of current command */
        }

        *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
        return (f); /* return length of buffer from _getline() */
}

/**
 * read_buf - read buff
 * @info: param struct
 * @buf: buff
 * @i: next
 *
 * Return: f
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
        ssize_t f = 0;

        if (*i)
                return (0);
        f = read(info->readfd, buf, READ_BUF_SIZE);
        if (f >= 0)
                *i = f;
        return (f);
}

/**
 * _getline - obtain next line of input from STDIN
 * @info: param struct
 * @ptr: ptr address to buff preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t i, len;
        size_t k;
        ssize_t f = 0, s = 0;
        char *p = NULL, *new_p = NULL, *c;

        p = *ptr;
        if (p && length)
                s = *length;
        if (i == len)
                i = len = 0;

        f = read_buf(info, buf, &len);
        if (f == -1 || (f == 0 && len == 0))
                return (-1);

        c = _strchr(buf + i, '\n');
        k = c ? 1 + (unsigned int)(c - buf) : len;
        new_p = _realloc(p, s, s ? s + k : k + 1);
        if (!new_p) /* MALLOC FAILURE! */
                return (p ? free(p), -1 : -1);

        if (s)
                _strncat(new_p, buf + i, k - i);
        else
                _strncpy(new_p, buf + i, k - i + 1);

        s += k - i;
        i = k;
        p = new_p;

        if (length)
                *length = s;
        *ptr = p;
        return (s);
}

/**
 * sigintHandler - Blck ctrl-C
 * @sig_num: signal num
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}
