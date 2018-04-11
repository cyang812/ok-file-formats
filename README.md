# ok-file-formats

This library is forkd by [there](https://github.com/brackeen/ok-file-formats)

## MODIDY

- 1 add a bmp encoder. So you can use `ok-file-formats` library to decode a png or jpg file to  RAW data, and then use `writeToBMP()` to encode RAW data and write to a bmp file.

- 2 add a example to show how to use bmp encoder.

- 3 add a way to input file from buffer. So the png or jpg data could input by a file and a data buffer. You can use this way when you embeded device dosen't have a file system or the image data come from stream. 

## TEST

- 1 If you just want to test a png or jpg file transform to a bmp file, you just need to read example.c , and undef the macro `USE_FILE_BUFFER` in `user_file_buf.h`.

- 2 If you need decode data that from a buffer not a file, you need def the macro. The project file tree is like that.

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

