ewilib
======

Generic and reusable ADTs collection


Build guidelines
----------------

* Linux: 

  - :code:`sudo apt-get install cmake`
  - :code:`sudo apt-get install check`
  - :code:`sudo apt-get install pkg-config`
  - from the root dir of the project, execute :code:`make`

* Windows: 

  - download and install cmake: http://www.cmake.org/files/v3.3/cmake-3.3.1-win32-x86.exe
  - follow the instructions for installing 'check' on Windows: http://check.sourceforge.net/web/install.html#visualstudios
  - alter the file tests/CMakeLists.txt: change PATH_TO_EXE to the path to the executable you installed in the previous step
  - from the root dir of the project, execute :code:`make.bat`


Future plans
------------

* Make the possibility for the backbone model to support the idea of `multigraphs`_
* Make the "error handling" behave in a way that it doesn't kill the running process


.. _`multigraphs`: https://en.wikipedia.org/wiki/Multigraph
