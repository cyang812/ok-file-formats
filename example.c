#include "example.h"
#include "user_file_buf.h"
#include "ok_png.h"
#include "ok_jpg.h"
#include <stdio.h>

#define PNG_PATH "\\testpng.png"
#define JPG_PATH "\\testjpg.jpg"

/*
 * param idx: item id
 */
uint8_t writeToBMP(const uint8_t *data, uint32_t data_len, uint32_t item_id, uint32_t xsize, uint32_t ysize)
{
	uint8_t header[54] =
	{
    	0x42, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    uint32_t file_size = (uint32_t)xsize * (uint32_t)ysize * 4 + 54;
    header[2] = (unsigned char)(file_size &0x000000ff);
    header[3] = (file_size >> 8) & 0x000000ff;
    header[4] = (file_size >> 16) & 0x000000ff;
    header[5] = (file_size >> 24) & 0x000000ff;

    uint32_t width = xsize;
    header[18] = width & 0x000000ff;
    header[19] = (width >> 8) & 0x000000ff;
    header[20] = (width >> 16) & 0x000000ff;
    header[21] = (width >> 24) & 0x000000ff;

    uint32_t height = ysize;
    header[22] = height & 0x000000ff;
    header[23] = (height >> 8) & 0x000000ff;
    header[24] = (height >> 16) & 0x000000ff;
    header[25] = (height >> 24) & 0x000000ff;

    uint8_t filename_buf[100];
    sprintf(filename_buf, "test%04d.bmp", item_id);

    FILE *file;
    file = fopen(filename_buf, "wb");
    if(!file)
    {
        printf("unable creat file!\n");
        return 0;
    }
    else
    {
		//header
		fwrite(header, sizeof(uint8_t), 54, file);

    	//image
        fwrite(data, sizeof(uint8_t), data_len, file);
    }

    printf("write file succ, file name = %s, len = %d\n", filename_buf, data_len);
    fclose(file);
}


/*
 * param idx: item id
 */
uint8_t dec_png(uint8_t idx)
{
	FILE *file = fopen(PNG_PATH, "rb");
	if(!file)
	{
		printf("file name: %s\n", PNG_PATH);
		printf("open file err!\n");
	}

    ok_png *image = ok_png_read(file, OK_PNG_COLOR_FORMAT_BGRA | OK_JPG_FLIP_Y);
    fclose(file);

    if(image->data)
    {
    	printf("Got image %s", PNG_PATH);
        printf(" Size: %li x %li\n", (uint32_t)image->width, (uint32_t)image->height);
        printf("has alpha = %d\n", image->has_alpha);

		uint32_t xsize = image->width;
		uint32_t ysize = image->height;
		uint32_t length = image->width * image->height * 4;
		uint8_t  *dst = image->data;

		writeToBMP(dst, length, idx, xsize, ysize);
    }
    else
    {
        printf("err msg = %s\n", image->error_message);
    }

    ok_png_free(image);

    return 0;
}

uint8_t dec_jpg(uint8_t idx)
{
	FILE *file = fopen(JPG_PATH, "rb");
	if(!file)
	{
		printf("file name: %s\n", JPG_PATH);
		printf("open file err!\n");
	}

    ok_jpg *image = ok_jpg_read(file, OK_JPG_COLOR_FORMAT_BGRA | OK_JPG_FLIP_Y);
    fclose(file);

    if(image->data)
    {
    	printf("Got image %s", JPG_PATH);
        printf(" Size: %li x %li\n", (uint32_t)image->width, (uint32_t)image->height);

		uint32_t xsize = image->width;
		uint32_t ysize = image->height;
		uint32_t length = image->width * image->height * 4;
		uint8_t  *dst = image->data;

		writeToBMP(dst, length, idx, xsize, ysize);
    }
    else
    {
		printf("err msg = %s\n", image->error_message);
    }

    ok_jpg_free(image);
    return 0;
}

void dec_png_buf()
{
	FILE_BUF *file = fopen_buf(test_png, sizeof(test_png));
	if(!file)
	{
		printf("open file err!\n");
	}
	else
	{
		printf("fsize = %d\n", file->fSize);
	}

    ok_png *image = ok_png_read(file, OK_PNG_COLOR_FORMAT_BGRA | OK_PNG_FLIP_Y);
    fclose_buf(file);

    if(image->data)
    {
    	printf("Got image ");
        printf(" Size: %li x %li\n", (uint32_t)image->width, (uint32_t)image->height);

		uint32_t xsize = image->width;
		uint32_t ysize = image->height;
		uint32_t length = image->width * image->height * 4;
		uint8_t *dst = image->data;

		writeToBMP(dst, length, 3, xsize, ysize);
    }
    else
    {
		printf("err msg = %s\n", image->error_message);
    }

    ok_png_free(image);
}

void dec_jpg_buf()
{
	FILE_BUF *file = fopen_buf(test_jpg, sizeof(test_jpg));
	if(!file)
	{
		printf("open file err!\n");
	}
	else
	{
		printf("fsize = %d\n", file->fSize);
	}

    ok_jpg *image = ok_jpg_read(file, OK_JPG_COLOR_FORMAT_BGRA | OK_JPG_FLIP_Y);
    fclose_buf(file);

    if(image->data)
    {
    	printf("Got image ");
        printf(" Size: %li x %li\n", (uint32_t)image->width, (uint32_t)image->height);

		uint32_t xsize = image->width;
		uint32_t ysize = image->height;
		uint32_t length = image->width * image->height * 4;
		uint8_t *dst = image->data;

		writeToBMP(dst, length, 4, xsize, ysize);
    }
    else
    {
		printf("err msg = %s\n", image->error_message);
    }

    ok_jpg_free(image);
}

int main()
{

#ifndef USE_FILE_BUFFER
	dec_png(1);
	dec_jpg(2);
#else
	dec_png_buf();
	dec_jpg_buf();
#endif

    return 0;
}
