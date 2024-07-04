
#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i =0;
	while ( s[i] != '\0')
	{
		i++;
	}
	return i;
}

char 	*ft_strjoin(char *str ,char  *buffer)
{
	if(buffer == NULL)
		return NULL;
	if(str == NULL)
	{
		str  = (char *)malloc( 1 + sizeof(char));
		if(!str)
			return NULL;
		str[0]='\0';
	}
	int len_1 = ft_strlen(str);
	int len_2 = ft_strlen(buffer);
	int i =0;
	char *ptr  = (char *)malloc((len_1 + len_2 +1) * sizeof(char));
	if(!ptr)
	{
		free(str);
		str = NULL;
		return 	NULL;
	}
	
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	int j =0;
	while (buffer[j] != '\0')
	{
		ptr[i] = buffer[j];
		i++;
		j++;
	}
	ptr[i]  = '\0';
	free(str);
	str = NULL;
	return ptr;
}

int 	ft_strchar(char *s  , char c)
{
	if( !s)	
		return 0;

	int i =0;
	while (s[i] != '\0')
	{
		if( s[i] == c)
		{
			return 1;
		}
		i++;
	}
	return 0;
}
