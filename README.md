# Blinkray: A full-constexpr C++ raytracer

`constexpr` is a C++ specifier making calculations at compile time rather than at execution.

The purpose of this project is to elevate it to an extreme (and arguably stupid) level by processing an entire image with raytracing algorithm for scenes including several lights, several objects, and several material types with reflection, transparency, refraction, shadows and more.

When full constexpr mode is enabled, the entire image is processed during compilation, the resulting .bmp file is stored as a string in compiled program, resulting in an executable doing nothing more than a print of this image in stdout.

## Ray-tracing features

* Basic shapes: Sphere, Cylinder, Plane
* Objects limits to "cut" such shapes
* Spot and directional lights with shadows
* Ambient, diffuse and specular material lighting
* Plain, tiled and textured materials
* Reflection, transparency and refraction
* Perspective, orthographic and fisheye cameras

## Demo

![Demo](/demo.png)

On the ground, front and back (behind the camera): planes with checkboard materials.

From left to right : a transparent sphere with a refraction index of 1.51, an opaque red sphere cut two times, an opaque blue cylinder, and a fully reflective sphere.

## Usage

Since everything must be done at compile time, scene description is a C++ code file to include at compilation. Different scenes can be found in _scenes/_ directory.

Compilation and execution can be done using _blink.sh_. Default run shall render _scene_test_, the demo image, and store it in _output.bmp_ file :
```
./blink.sh
```
It is equivalent to specify all those parameters:
```
./blink.sh scene_test -DIMAGE_WIDTH=800 -DIMAGE_HEIGHT=600
```
Be careful: trying to render a higher resolution may result in stack overflow, because the stack size may be insufficient to store the entire resulting image !

Now, to render it in full constexpr mode, simply add `-DFULL_CONSTEXPR` to the command line. Also, let's drastically reduce resolution, because processing at compile-time is roughly 600 times slower than processing at run-time:
```
./blink.sh scene_test -DIMAGE_WIDTH=80 -DIMAGE_HEIGHT=60 -DFULL_CONSTEXPR
```
This time, you should notice compilation is quite longer, but the resulting executable is nearly instant, because it is nothing more than a print in stdout.

Also, if you binary compare compiled executable _blink_ and printed image _output.bmp_, you will notice _output.bmp_ is entierely contained inside _blink_.

## Dependencies

Use clang++ version 18. Nothing else.

(clang tends to have way better performance and memory usage on very long constexpr builds than GCC.)
