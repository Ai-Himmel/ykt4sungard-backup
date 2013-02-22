
#pragma once

#define MY_STRING_DEFUALT_LEN 512
typedef struct 
{
	char *data;
	int length;
	int size;
}my_string_t;

static my_string_t alloc_mystring()
{
	my_string_t str;
	str.data = new char[MY_STRING_DEFUALT_LEN];
	str.size = MY_STRING_DEFUALT_LEN;
	str.length = 0;
	return str;
}

static void free_mystring(my_string_t *str)
{
	if(str->size > 0 && str->data)
	{
		delete [] str->data;
		str->length =0;
		str->size = 0;
	}
}

static void resize_mystring(my_string_t *str,int newsize)
{
	str->data = new(str->data) char[newsize];
	str->size = newsize;
}


static int read_file_line(my_string_t *str,FILE *fp)
{
	int c;
	while(1)
	{
		c = fgetc(fp);
		//printf(" character[%d]\n",c);
		switch(c)
		{
		case 255:
		case -1:
			if(feof(fp))
				return 1;
			return -1;
		case '\r':
			break;
		case '\n':
			// 读取成功一行
			return 0;
		case '\\':
			// 换行后读取下一行
			break;
		default:
			if(str->length >= (str->size-1))
				resize_mystring(str,str->size + MY_STRING_DEFUALT_LEN);
			str->data[str->length++] = c;
			break;
		}
	}
	return 1;
}

static int trim_line(my_string_t *str)
{
	int pos;
	if(str->length == 0)
		return 0;
	for(pos=0;pos < str->length;++pos)
		if(str->data[pos] == ' ' || str->data[pos] == '\t')
			continue;
		else
			break;
	int left;
	for(left=str->length - 1;left > pos;--left)
		if(str->data[left] == ' ' || str->data[left] == '\t')
			continue;
		else
			break;
	str->length = left+1;
	str->data[str->length] = 0;
	return pos;
}