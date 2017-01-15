The CanvasCV project
====================
This is an interactive canvas like drawing library for OpenCV.
Currently only C++ is supported.
Note also that this is a beta version and there are opened issues.

What is it good for ?
---------------------
For a user interface with interactive GUI without any external GUI toolkit dependencies.

## Supported features:

### Supported interactive shapes:
* Line
* Arrow
* TextBox
* LineCrossing
* Quadrilateral
* Rectangle
* ShapesConnector
* LabeledShapesConnector

### Capabilities:
* All shapes are draggable
* All shapes are editable
* Support for create/modify/delete callbacks

Build and install
-----------------
## Linux Building / Installing
### Build dependencies
Make sure these are installed first and that their executables are **in your path**:
* **cmake** - should already be installed since you built OpenCV by yourself.
* **git** (optional) - you can also download the sources from GitHub.

### Prepare to build
```
git clone https://github.com/sagi-z/CanvasCV.git
cd CanvasCV
mkdir build
cd build
```

### By default cmake is building without the C++ demo
```
cmake ..
make
```

### Here is how to build the test
```
cmake -DBUILD_TEST=ON ..
make
```

### Install option 1 for Linux (from the build directory):
```
sudo make install
```

### C++ Install option 2 for Linux - cleaner (from the build directory):
```
cpack -G DEB
sudo dpkg -i ./canvascv-0.9.0-Linux.deb
```

C++ Usage
---------
### Linux
Assuming installation in '/usr/local', add to cflags '-I/usr/local/include' and to link flags '-L/usr/local/lib -lcanvascv'

Here is a minimal *CMakeLists.txt* example:
```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(myapp)

FIND_PACKAGE(OpenCV 3.1.0 REQUIRED)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS} "/usr/local/include")

ADD_EXECUTABLE(myapp main.cpp)

FIND_LIBRARY(CanvasCV_LIB canvascv "/usr/local/lib")
TARGET_LINK_LIBRARIES (myapp ${CanvasCV_LIB} ${OpenCV_LIBS})
```

### Windows
make sure the include path and link path and library are set correctly.

### C++ code example
See main.cpp

