imageprocess
============

to build use commands

cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 <path/to/src>

where the path to source is the relative location of source code
The currend working directory is used as the location of the build files.

in the same directory then run:

make

then to run the program use:
./ImageProcessMain <args>

args can be:
-facedetect
	runs face detection algorithm, prints accuracy in terminal
	input images should be placed in the images folder.
	the path to thte image directorys should be "images/[train or test]/[non-]face"
-sobel
	creates sobel.jpg
-noise
	create 3 noise reduced images
-threshold
	apply threshold and output image
-enhance
	apply enhancement
