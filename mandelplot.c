#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//scales a number that was previously on range [nMin:nMax] to [nMin:nMax], meant to convert pixels of an image to mandelbrot
long double scalePixel(int n, int nMax,int nMin, long double newMin, long double newMax){
	long double scaled = (((long double)(n - nMin) * (newMax - newMin))/ ((long double)(nMax - nMin))) + newMin;
  return scaled;
}

unsigned char* escapeTimeData(int width, int height, int iterations, long double xLow, long double xHigh, long double yLow, long double yHigh){
  unsigned char *data = malloc(width*height*sizeof(unsigned char));//pointer that allocates width*height bytes to store the ints as a 2d array
	for(int j = 0; j < height; j++){
		long double y0 = scalePixel(j, height, 0, yLow, yHigh);
		for(int i = 0; i < width; i++){
			long double x0 = scalePixel(i, width, 0, xLow, xHigh);
			//math part
			long double x = 0.0;
			long double y = 0.0;
			long double xtemp, ytemp;
			int iter = 0;
			while(iter < iterations && x + y < 4){
				xtemp = x;
				ytemp = y;
				x = xtemp*xtemp - ytemp*ytemp + x0;
				y = 2*xtemp*ytemp + y0;
				iter++;
			}
			data[j*width+i] = (unsigned char) (255 - scalePixel(iter, iterations, 0, 0, 255));
		}
	}
   return data;
}
int main(int argc, char *argv[]){
  //take plot dimensions, mandelbrot scale dimensions (default up top), iterations?
  //form of ./name $width $height -xMin $min -xMax $max -yMin $ymin -yMax $ymax
  if(argc < 3){
    printf("Need to supply width and height (pixels) as args\n");
  }
  int width;
  int height;
  width = atoi(argv[1]);
  height = atoi(argv[2]);
  printf("width: %i, height: %i\n",width, height);
  printf("beginning now\n");
  unsigned char *dataArr2 = escapeTimeData(width, height, 80, -2.5, 1, -1, 1);
  stbi_write_png("outputsample.png", width, height, 1, dataArr2, width);
  return 1;
}
