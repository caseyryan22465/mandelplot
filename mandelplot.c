#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//scales a number that was previously on range [nMin:nMax] to [nMin:nMax], meant to convert pixels of an image to mandelbrot
long double scalePixel(int n, int nMax,int nMin, long double newMin, long double newMax){
  //long double scaled = (((((long double) n - nMin) / (long double) (nMax-nMin))) * (newMax-newMin)) + newMin;
	long double scaled = (((long double)(n - nMin) * (newMax - newMin))/ ((long double)(nMax - nMin))) + newMin;
  return scaled;
}

void scaleTest(int n, int nMax,int nMin, long double newMin, long double newMax){
	printf("scale %i on range %i %i to range %Lf %Lf\n", n, nMin, nMax, newMin, newMax);
	long double out = scalePixel(n, nMax, nMin, newMin, newMax);
	printf("result: %Lf\n", out);
}

unsigned char* escapeTimeData(int width, int height, int iterations, long double xLow, long double xHigh, long double yLow, long double yHigh){
  unsigned char *data = malloc(width*height*sizeof(unsigned char));//pointer that allocates width*height bytes to store the ints as a 2d array
  int countx = 0;
  /*for(int i = (-1*(width/2)); i < width/2; i++){//mandelbrot done from (0,0)=center, image plotting done from (0,0) = top left
    long double x0 = scalePixel(i, width/2, (-1*width/2), xLow, xHigh);
    int county = 0;
    for(int j = (height/2); j > (-1*(height/2)); j--){//same as above, have to convert from mandel to digital
      long double y0 = scalePixel(j, height/2,(-1*width/2), yLow, yHigh);
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
      //if(countx % 100 == 0 & county % 100 ==0){
	//printf("pixel (%i, %i) getting value %i\n", countx, county, (unsigned char) (255-scalePixel(iter, iterations, 0, 0, 255)));
      //}
      data[countx*height+county] = (unsigned char) (255-scalePixel(iter, iterations, 0, 0, 255));//unsigned char because image pixel data is 1 byte (0-255), so using int would be 4 bytes and mess up 3/4 of the points
      county++;
    }
    countx++;
  }*/
	for(int i = 0; i < width; i++){
		long double x0 = scalePixel(i, width, 0, xLow, xHigh);
		for(int j = 0; j < height; j++){
			long double y0 = scalePixel(j, height, 0, yLow, yHigh);
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
			data[i*height+j] = (unsigned char) (255 - scalePixel(iter, iterations, 0, 0, 255));
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
  stbi_write_png("outputsample.png", width, height, 1, dataArr2, height);
  return 1;
}
