# Mandelplot

Mandelplot is a small command line project that generates images of [the Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) according to custom arguments

## Installation

Use git or wget to download the `mandelplot.c` and `stbi_image_write.h` files.
```bash
git clone https://github.com/caseyryan22465/mandelplot.git
```
or
```bash
wget https://raw.githubusercontent.com/caseyryan22465/mandelplot/main/mandelplot.c
wget https://github.com/nothings/stb/raw/master/stb_image_write.h
```
and compile `mandelplot.c` with the compiler of your choice

## Usage
run the compiled executable with the args `width height` to generate a $WIDTHx$HEIGHT png image of the mandelbrot set. Ex: `./mandelplot 1920 1080` will output a 1920x1080 image of the mandelbrot set to the current directory, titled `output.png`

## About
This project is mainly me trying to wrap my head around the Mandelbrot set and complex numbers a bit more.  I watched a couple of the mandelbrot zoom videos and wanted to make one myself, so this is working towards that.

Image write library is from the [stb](https://github.com/nothings/stb/blob/master/stb_image_write.h) repo by [nothings](https://github.com/nothings)
## License
[MIT](https://choosealicense.com/licenses/mit/)
