snappy-msvc
=============
Simple Microsoft Visual Studio project file and missing stdint.h file 
that makes it easier to build Google's snappy library on Windows

Dependencies
==============
* Google's snappy library

Usage
==========
* Download snappy from http://code.google.com/p/snappy and extract to <snappy_dir>
* cd snappy_dir
* git clone https://github.com/kmanley/snappy-msvc
* cd snappy-msvc
* Open snappy.sln
* Choose Build/Rebuild Solution
* The static lib will end up in <snappy_dir>/snappy-msvc/Debug (or Release)

Licenses
=============
* Google snappy and stdint.h use the BSD license
  http://www.opensource.org/licenses/bsd-license.php

* snappy-msvc is unlicensed/public domain

Credits
============
* Google, for the snappy library
  http://code.google.com/p/snappy

* stdint.h
  Copyright (c) 2005-2011 Paul Hsieh
  http://www.azillionmonkeys.com/qed/index.html
  
