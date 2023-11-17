#include "nickdun.h" 

/** 

* get_history_file - obtain  history file 

* @info: Param Strct 

* 

* Return: string 

*/ 

  

char *get_history_file(info_t *info) 

{ 

        char *buf, *dir; 

  

        dir = _getenv(info, "HOME="); 

        if (!dir) 

                return (NULL); 

        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2)); 

        if (!buf) 

                return (NULL); 

        buf[0] = 0; 

        _strcpy(buf, dir); 

        _strcat(buf, "/"); 

        _strcat(buf, HIST_FILE); 

        return (buf); 

} 

  

/** 

* write_history -  attach to an existing file 

* @info: Param Strut 

* 

* Return:success 1, or -1 

*/ 

int write_history(info_t *info) 

{ 

        ssize_t fd; 

        char *filename = get_history_file(info); 

        list_t *node = NULL; 

  

        if (!filename) 

                return (-1); 

  

        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); 

        free(filename); 

        if (fd == -1) 

                return (-1); 

        for (node = info->history; node; node = node->next) 

        { 

                _putsfd(node->str, fd); 

                _putfd('\n', fd); 

        } 

        _putfd(BUF_FLUSH, fd); 

        close(fd); 

        return (1); 

} 

  

/** 

* read_history - Reading hist  file 

* @info: Param Strct 

* 

* Return: on success  histcount, otherwise 0 

*/ 

int read_history(info_t *info) 

{ 

        int y, last = 0, linecount = 0; 

        ssize_t fd, rdlen, fsize = 0; 

        struct stat st; 

        char *buf = NULL, *filename = get_history_file(info); 

  

        if (!filename) 

                return (0); 

  

        fd = open(filename, O_RDONLY); 

        free(filename); 

        if (fd == -1) 

                return (0); 

        if (!fstat(fd, &st)) 

                fsize = st.st_size; 

        if (fsize < 2) 

                return (0); 

        buf = malloc(sizeof(char) * (fsize + 1)); 

        if (!buf) 

                return (0); 

        rdlen = read(fd, buf, fsize); 

        buf[fsize] = 0; 

        if (rdlen <= 0) 

                return (free(buf), 0); 

        close(fd); 

        for (y = 0; y < fsize; y++) 

                if (buf[y] == '\n') 

                { 

                        buf[y] = 0; 

                        build_history_list(info, buf + last, linecount++); 

                        last = y + 1; 

                } 

        if (last != y) 

                build_history_list(info, buf + last, linecount++); 

        free(buf); 

        info->histcount = linecount; 

        while (info->histcount-- >= HIST_MAX) 

                delete_node_at_index(&(info->history), 0); 

        renumber_history(info); 

        return (info->histcount); 

} 

  

/** 

* build_history_list - takes entry to  history linked list 

* @info: Strct holding potential arg. Used to maintain 

* @buf: Buffer 

* @linecount:  Hist count 

* 

* Return:  Success Always 0 

*/ 

int build_history_list(info_t *info, char *buf, int linecount) 

{ 

        list_t *node = NULL; 

  

        if (info->history) 

                node = info->history; 

        add_node_end(&node, buf, linecount); 

  

        if (!info->history) 

                info->history = node; 

        return (0); 

} 

  

/** 

* renumber_history - renumber histo  linked list 

* @info: Strut holding arg 

* 

* Return: New histo count 

*/ 

int renumber_history(info_t *info) 

{ 

        list_t *node = info->history; 

        int y = 0; 

  

        while (node) 

        { 

                node->num = y++; 

                node = node->next; 

        } 

        return (info->histcount = y); 

} 
