#ifndef LIB_H
# define LIB_H

# include <ctype.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>

int			ft_isspace(char c);
ssize_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, char c);
char		*ft_strncat(char *s1, char *s2, int n);
int			ft_strncmp( const char * s1, const char * s2, size_t n );
char		*ft_strndup(const char *src, size_t n);
int			ft_isspace(char c);
int			ft_arrlen(char **arr);
void		*ft_memset(void *data, char c, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_itoa(char *str, int n);
void		ft_flush(int socket);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_atoi(const char *str);

int			command_size(char *command);
void		command_free(char **command);
bool		command_split(char **command, const char *final);

#endif
