# Mandelplot

Mandelplot is a small command line project that generates images of [the Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) according to custom arguments

## Installation

Use git and pip to install the package and dependencies

```bash
git clone https://github.com/caseyryan22465/mandelplot.git
```
navigate into the directory, then install the requirements
```bash
pip install -r requirements.txt
```

## Usage

```bash
py mandelplot.py 1920 1080
#generates 1920x1080 image of the mandelbrot set at img/output_1920x1080.png

py mandelplot.py $width $height -n $name -p $progressInterval -d $dir
#generates width x height image and updates user every $progressInterval percent. Stores to $dir/$name

py mandelplot.py -h
#displays help
```

## About
This project is mainly me trying to wrap my head around the Mandelbrot set and complex numbers a bit more. Currently the important parts of the code are from [CodinGame](https://www.codingame.com/playgrounds/2358/how-to-plot-the-mandelbrot-set/mandelbrot-set) and I just made it generate according to arguments given from the command line. However, I am porting it to C for performance and practice reasons, so this is just a starting point I can test against
## License
[MIT](https://choosealicense.com/licenses/mit/)