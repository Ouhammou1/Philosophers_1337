#include "get_next_line.h"


char 	*ft_string(char *str ,int fd)
{
	int a = 1;
	char *buffer;
	buffer = (char *)malloc( (BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)	
		return NULL;
	
	while (a > 0 &&  ft_strchar(str , '\n') == 0) 
	{
		a = read(fd , buffer , BUFFER_SIZE);
		if( a == -1)
		{
			free(buffer);
			buffer = NULL;
			break;
		}
		buffer[a]= '\0';
		str = ft_strjoin(str , buffer);
	}
	free(buffer);
	buffer = NULL;
	return str;
}
char 	*return_line(char 	*str)
{
		int i =0;
		if (str[0] == '\0')
		{
			return NULL;
		}
		
		while (str[i] != '\0')
		{
			if( str [i] == '\n')
			{
				i++;
				break;
			}
			i++;
		}
		char *ptr = (char *)malloc((i + 1) * sizeof(char));
		if(!ptr)
			return NULL;
		
		int j =0;
		while (j < i)
		{
			ptr[j] = str[j];
			j++;
		}
		ptr[i] = '\0';
		return ptr;
}

char	*next_str(char	 *str)
{
	int k=0;
	while (str[k] != '\0' && str[k] != '\n')
	{
		k++;
	}
	if(str[k] == '\n')
		k++;
	if(str[k] == '\0')
		return (free (str), str = NULL,  NULL);
	
	
	int len = ft_strlen(str) - k;
	char *ptr = (char *)malloc((len + 1) * sizeof(char));
	if(ptr == NULL)
		return NULL;
	int i =0;
	while (i < len)
	{
		ptr[i] = str[k];
		i++;
		k++;
	}
	ptr[i] = '\0';
	free(str);
	str = NULL;
	return ptr;
}



char *get_next_line(int fd)
{
	static char *str ;
	char *line;

	if(fd < 0 || read(fd ,0,0) == -1 || BUFFER_SIZE <= 0 )
	{
		free(str);
		str = NULL;
		return NULL;
	}
	str  = ft_string(str , fd);
	if(str == NULL)
		return NULL;

	line = return_line(str);
	str =  next_str(str);
	return line;
}

// int main ()
// {
// 	int fd = open("text.txt" , O_RDONLY);
// 	if( fd < 0 )
// 		printf("File not found !");
// 	char *str;

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	str  = get_next_line(fd);
// 	printf("string ===> %s", str);

// 	return  0;
// }