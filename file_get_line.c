#include "nickdun.h" 

/** 

* input_buf – this buff chaining cmds 

* @info: args structure 

* @buf:  buf location 

* @len:  this is buffer location 

* 

* Return: bytes read 

*/ 

ssize_t input_buf(info_t *info, char **buf, size_t *len) 

{ 

	ssize_t r = 0; 

	size_t len_p = 0; 

  

	if (!*len) /* none left in buffer, replenish it */ 

	{ 

		/*bfree((void **)info->cmd_buf);*/ 

		free(*buf); 

		*buf = NULL; 

		signal(SIGINT, sigintHandler); 

#if USE_GETLINE 

		r = getline(buf, &len_p, stdin); 

#else 

		r = _getline(info, buf, &len_p); 

#endif 

		if (r > 0) 

		{ 

			if ((*buf)[r - 1] == '\n') 

			{ 

				(*buf)[r - 1] = '\0'; /* avoid trailsof  new-line */ 

				r--; 

			} 

			info->linecount_flag = 1; 

			remove_comments(*buf); 

			build_history_list(info, *buf, info->histcount++); 

			/* if (_strchr(*buf, ';')) if is  a cmd chain? */ 

			{ 

				*len = r; 

				info->cmd_buf = buf; 

			} 

		} 

	} 

	return (r); 

} 

  

/** 

* get_input – this line-get subtract newline 

* @info: args  datatype struct 

* 

* Return:  document bytes 

*/ 

ssize_t get_input(info_t *info) 

{ 

	static char *buf; /* the ';' cmd buff chaining */ 

	static size_t i, j, len; 

	ssize_t r = 0; 

	char **buf_p = &(info->arg), *p; 

  

	_putchar(BUF_FLUSH); 

	r = input_buf(info, &buf, &len); 

	if (r == -1) /* EOF */ 

		return (-1); 

	if (len) /* is there  cmd left in buffer chain  */ 

	{ 

		j = i; /* init a repetation to now buffer range */ 

		p = buf + i; /* restore get pointer */ 

  

		check_chain(info, buf, &j, i, len); 

		while (j < len) /* repeat to colon -semi or destination */ 

		{ 

			if (is_chain(info, buf, &j)) 

				break; 

			j++; 

		} 

  

		i = j + 1; /* add the null passing ';'' */ 

		if (i >= len) /*  desti of buf? */ 

		{ 

			i = len = 0; /* default length and position  */ 

			info->cmd_buf_type = CMD_NORM; 

		} 

  

		*buf_p = p; /* retrace ponter curent cmd position */ 

		return (_strlen(p)); /* retrace range  current cmd */ 

	} 

  

	*buf_p = buf; /* if not chained, retrace buf to_getline() */ 

	return (r); /* retrace range of buff from _getline() */ 

} 

  

/** 

* read_buf – buf read 

* @info: arg struct 

* @buf: the buf 

* @i: size 

* 

* Return: r 

*/ 

ssize_t read_buf(info_t *info, char *buf, size_t *i) 

{ 

	ssize_t r = 0; 

  

	if (*i) 

		return (0); 

	r = read(info->readfd, buf, READ_BUF_SIZE); 

	if (r >= 0) 

		*i = r; 

	return (r); 

} 

  

/** 

* _getline – call line input from stdin 

* @info: args datatype struct 

* @ptr: location pointer to buf, allocate or nul 

* @length: range of allocated ptr buf if not NULL 

* 

* Return: s 

*/ 

int _getline(info_t *info, char **ptr, size_t *length) 

{ 

	static char buf[READ_BUF_SIZE]; 

	static size_t i, len; 

	size_t k; 

	ssize_t r = 0, s = 0; 

	char *p = NULL, *new_p = NULL, *c; 

  

	p = *ptr; 

	if (p && length) 

		s = *length; 

	if (i == len) 

		i = len = 0; 

  

	r = read_buf(info, buf, &len); 

	if (r == -1 || (r == 0 && len == 0)) 

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

* sigintHandler – disable the control 

* @sig_num: the number signalling 

* 

* Return: void 

*/ 

void sigintHandler(__attribute__((unused))int sig_num) 

{ 

	_puts("\n"); 

	_puts("$ "); 

	_putchar(BUF_FLUSH); 

} 
