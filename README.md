# ok-file-formats

This library is forkd by [there](https://github.com/brackeen/ok-file-formats)

## MODIFY

- 1 add a bmp encoder. So you can use `ok-file-formats` library to decode a png or jpg file to  RAW data, and then use `writeToBMP()` to encode RAW data and write to a bmp file.

- 2 add a example to show how to use bmp encoder.

- 3 add a way to input file from buffer. So the png or jpg data could input by a file or a data buffer. You can use this way when you embeded device dosen't have a file system or the image data come from stream. 

- 4 add a RGB888 color format. In original library, there are two color formats, which are RGBA8888 and BGRA8888, but the alpha is always 255. So we can just ignore the alpha data and reduce the output file size.

## TEST

- 1 If you just want to test a png or jpg file transform to a bmp file, you just need to read `example.c` , and undefined the macro `USE_FILE_BUFFER` in `user_file_buf.h`.

- 2 If you need decode data that from a buffer not a file, you need def the macro `USE_FILE_BUFFER` in `user_file_buf.h`. 

- 3 If you want to reduce the bmp file size by ignoring alpha data, you need def the macro `JUST_USE_RGB` in `ok_jpg.h`.

**The project file tree is like that.**

  ```
	│  example.c
	│  testjpg.jpg
	│  testpng.png
	│  user_file_buf.c
	│  user_file_buf.h
	│
	└─lib
		ok_jpg.c
		ok_jpg.h
		ok_png.c
		ok_png.h
  ```

example:
```c
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
```
