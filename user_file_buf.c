#include "user_file_buf.h"

static uint32_t file_cnt = 0;

FILE_BUF *fopen_buf(const uint8_t *buf_src, uint32_t buf_len)
{
	printf("fopen_buf!\n");

	FILE_BUF *file_buf = (FILE_BUF *)malloc(sizeof(FILE_BUF));
	if(file_buf)
	{
		file_buf->base    = buf_src;
		file_buf->ptr     = buf_src;
		file_buf->ptr_idx = 0;
		file_buf->fSize   = buf_len;

		return file_buf;
	}
	else
	{
		return 0;
	}
}

uint32_t fread_buf(FILE_BUF *file_buf, uint8_t *dst, uint32_t count)
{
	uint32_t ret = 0;

//	printf("fread_buf! count = %d ", count);

	if( (file_buf->ptr_idx + count) < file_buf->fSize )
	{
		memmove(dst, file_buf->ptr, count);
		file_buf->ptr    += count;
		file_buf->ptr_idx += count;
		ret = count;
	}
	else
	{
		int32_t cnt = 0;
		cnt = file_buf->fSize - file_buf->ptr_idx;

		if(cnt > 0)
		{
			memmove(dst, file_buf->ptr, cnt);
			file_buf->ptr	 += cnt;
			file_buf->ptr_idx += cnt;
		}
		else if(cnt < 0)
		{
			printf("fread_buf err!\n");
			while(1);
		}

		ret = cnt;
	}

	file_cnt += ret;

//	printf("ret = %d\n", ret);
	return ret;
}

uint32_t fseek_buf(FILE_BUF *file_buf, uint32_t count)
{
	uint32_t ret = 0;

//	printf("fseek_printf! count = %d\n", count);

	if( (file_buf->ptr_idx + count) < file_buf->fSize )
	{
		file_buf->ptr 	  += count;
		file_buf->ptr_idx += count;

		ret = 0;
	}
	else
	{
		ret = 1;
	}

	return ret;
}

void fclose_buf(FILE_BUF *file_buf)
{
	printf("fclose_buf!\n");
	printf("file_cnt = %d\n", file_cnt);

	if(file_buf)
	{
		free(file_buf);
	}
}
