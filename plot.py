from PIL import Image, ImageDraw
from mandelbrot import mandelbrot, MAX_ITER
import argparse
import math
import time
import os

def plot(width, height, chunkPctSize, outName, outPath):
    # Image size (pixels)
    WIDTH = int(width)
    HEIGHT = int(height)

    # Plot window
    RE_START = -2
    RE_END = 1
    IM_START = -1
    IM_END = 1

    palette = []

    im = Image.new('RGB', (WIDTH, HEIGHT), (0, 0, 0))
    draw = ImageDraw.Draw(im)

    #render stats vars
    linesForChunk = math.ceil(WIDTH/(100/chunkPctSize))
    initialTime = time.time()
    timeSinceLastChunk = time.time()

    for x in range(0, WIDTH):
        if(x % linesForChunk == 0):
            print(str(int((x/linesForChunk)*chunkPctSize)) + "% complete, took " + str(round((time.time() - timeSinceLastChunk), 2)) + "s")
            timeSinceLastChunk = time.time()
        for y in range(0, HEIGHT):
            # Convert pixel coordinate to complex number
            c = complex(RE_START + (x / WIDTH) * (RE_END - RE_START),
                        IM_START + (y / HEIGHT) * (IM_END - IM_START))
            # Compute the number of iterations
            m = mandelbrot(c)
            # The color depends on the number of iterations
            color = 255 - int(m * 255 / MAX_ITER)
            # Plot the point
            draw.point([x, y], (color, color, color))

    im.save(outPath + "\\" + outName, 'PNG')
    print("finished and saved as: " + outPath + "\\" + outName + ", render took " + str(round(time.time()-initialTime, 2)) + " seconds")
    return

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description= "Generate an image of the mandelbrot set at a custom resolution")
    parser.add_argument("w", metavar="width", type=int, nargs = 1, help = "render width, in pixels")
    parser.add_argument("h", metavar="height", type=int, nargs = 1, help = "render height, in pixels")
    parser.add_argument("-p", metavar="percent", type=float, default=[2.0], nargs = 1, help = "percent to display progress update, default=2.0")
    parser.add_argument("-d", metavar="outputDir", type=str, default=os.getcwd() + '\img', help = "path to directory to write image to")
    parser.add_argument("-n", metavar="outputName", type=str, help = "name of output image, defaults to img/output_$WIDTHx$HEIGHT.png")
    args = parser.parse_args()
    if(args.n is None):
        args.n = 'output_' + str(args.w[0]) + 'x' + str(args.h[0]) + '.png'
    if not os.path.exists(args.d):
        os.makedirs(args.d)
    plot(args.w[0],args.h[0],float(args.p[0]), args.n, args.d)
