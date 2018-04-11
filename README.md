# ok-file-formats

This library is forkd by [there](https://github.com/brackeen/ok-file-formats)

## MODIDY

- 1 add a bmp encoder. So you can use `ok-file-formats` library to decode a png or jpg file to  RAW data, and then use `writeToBMP()` to encode RAW data and write to a bmp file.

- 2 add a example to show how to use bmp encoder.

## TEST

- 1 If you just want to test a png or jpg file transform to a bmp file, you just need to read example.c , and project file tree is like that.

  ```t
  │  example.c
  │  testjpg.jpg
  │  testpng.png
  └─lib
        ok_jpg.c
        ok_jpg.h
        ok_png.c
        ok_png.h
  ```

