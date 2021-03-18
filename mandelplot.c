#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


//mandelbrot only between these values

//scales a number that was previously on range [0:nMax] to [nMin:nMax], meant to convert pixels of an image to mandelbrot
long double scalePixel(int n, int nMax, long double newMin, long double newMax){
  long double scaled = ((((long double) n / (long double) nMax)) * (newMax-newMin)) + newMin;
  return scaled;
}

//Maybe TODO?? make a BMP writer (write binary).
//void toImage (int width, int height, char fileName){
//  FILE * out = fopen(filename, "wb+");//set out = opened file with write binary data and create if doesnt exist
//  out
//}
unsigned char* escapeTimeData(int width, int height, int iterations, long double xLow, long double xHigh, long double yLow, long double yHigh){
  unsigned char *data = malloc(width*height*sizeof(unsigned char));//pointer that allocates width*height bytes to store the ints as a 2d array
  for(int i = 0; i < width; i++){
    long double x0 = scalePixel(i, width, xLow, xHigh);
    for(int j = 0; j < height; j++){
      long double y0 = scalePixel(j, height, yLow, yHigh);
      long double x = 0.0;
      long double y = 0.0;
      long double xtemp = 0.0;
      long double ytemp = 0.0;
      int iter = 0;
      while(iter < iterations && x + y <= 4){
	xtemp = ((x*x) - (y*y)) + x0;
	ytemp = (2*x*y) + y0;
	x = xtemp;
	y = ytemp;
	iter++;
      }
      data[i*height+j] = (unsigned char) (255-scalePixel(iter, iterations, 0, 255));//unsigned char because image pixel data is 1 byte (0-255), so using int would be 4 bytes and mess up 3/4 of the points
    }
  }
  return data;
}

void printArr(int row, int col, int *data){
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      printf("data[%i][%i] = %i\n",i,j,data[i*col + j]);
    }
  }
  return;
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
  int dataArr[500][500];
  for(int i = 0; i < 500; i++){
    for(int j = 0; j < 500; j++){
      dataArr[i][j]= (int)scalePixel(i+j,1000,0,255);
    }
  }
  stbi_write_png("outputsample.png", width, height, 1, dataArr2, width);
  return 1;
}
