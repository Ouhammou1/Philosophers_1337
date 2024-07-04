
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef 	BUFFER_SIZE 
#define 	BUFFER_SIZE 3
#endif



char 	*get_next_line(int fd);
char 	*ft_string(char *str ,int fd);
char 	*ft_strjoin(char *str ,char  *buffer);
int 	ft_strlen(char *s);
int 	ft_strchar(char *s  , char c);
char 	*return_line(char 	*str);



#endif
