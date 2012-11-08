*****************************************************************************************
openEXR Raytracer v. 1.0

author: Alison Cooper (c) 2012

*****************************************************************************************

This is a raytracer program that utilizes the openEXR library. On Ubuntu, to install the
appropriate libraries please visit this page: 

http://packages.ubuntu.com/search?keywords=openexr

The viewer will be necessary to view output.

To compile the program, run the makefile command: make raytra

Information about running the program:

Option 1:

./raytra inputfile.txt output.exr

This takes an input text file (which may reference .obj files) and renders the image
described in that file. The output is the .exr file given as the second argument.

./raytra inputfile.txt output.exr n m

n and m are integers. 

They have to do with pixel and shadow ray distribution/stratification for making crisper
images. n deals with camera rays to a pixel, m deals with shadow rays to an area light.
As such, m is only appropriate to be >1 if an area light is contained in the scene file.
The program doesn't do anything with m if there is no area light. Increasing n will increase
the crispness of the image. Both significantly increase computation time.

Example files to run:

./raytra test3.txt out.exr 3 1

This will take a minute or so to run, and generates a very nice simple image with spheres,
some triangles, and mirror reflection.

./raytra creative.txt creative.exr 3 1

This image is all spheres, and draws a man on the moon. It takes longer than the first example
to render. To reduce computation time, run it with n = 1. The output image will not be very
crisp, though.

./raytra bicycle.txt bicycle.exr

This files uses .obj files and renders a bicycle with mirror reflections and shadows. Giving
it 3 1 for n and m will take over 21 minutes to render. There is an exr file of this output
image in the repository.

To view output images:

exrdisplay outputfile.exr


