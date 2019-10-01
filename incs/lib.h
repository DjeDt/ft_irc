/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:53:16 by Dje               #+#    #+#             */
/*   Updated: 2019/10/01 10:56:30 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <ctype.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>

# define SECRET_KEY		"Super_Secret_Key"
# define KEY_LEN		0x10
# define N				0x100

typedef struct		s_r4
{
	bool			flag;
	int				cyph;
	int				size;
	char			*key;
	unsigned char	cypher[N];
}					t_r4;

int					ft_isspace(char c);
ssize_t				ft_strlen(const char *str);
char				*ft_strchr(const char *s, char c);
char				*ft_strncat(char *s1, char *s2, int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(const char *src, size_t n);
int					ft_isspace(char c);
int					ft_arrlen(char **arr);
void				*ft_memset(void *data, char c, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_itoa(char *str, int n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_atoi(const char *str);
int					command_size(char *command);
void				command_free(char **command);
bool				command_split(char **command, const char *final);
void				ft_swap(unsigned char *x, unsigned char *y);
void				rc4_permutation(char *key, unsigned char *cypher);
void				rc4_decrypt(char *key, unsigned char *encrypted, \
						unsigned char *decrypted, int size);
void				rc4_encrypt(char *key, unsigned char *plain, \
						unsigned char *encrypted, int size);

#endif
