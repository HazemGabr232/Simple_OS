# Simple_OS
simple OS for educational purposes 

# building cross compiler 

to build cross compiler install the following packages first 

- gmp    `sudo apt-get install libgmp3-dev`
- mpfr   `sudo apt-get install libmpfr-dev`
- libmpc `sudo apt-get install libmpc-dev`
- gcc (usually exists)

then follow the following [instructions](https://github.com/cfenollosa/os-tutorial/tree/master/11-kernel-crosscompiler)

then add the following to ~/.bashrc

- `export PREFIX="/usr/local/i386elfgcc"`
- `export TARGET=i386-elf`
- `export PATH="$PREFIX/bin:$PATH"`
 
# compile and run 

- to compile use `make` 
- to clean use `make clean`
- to run use `make run`

# useful sources 
- [tuhdo/os01](https://github.com/tuhdo/os01)
- [cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [os-dev](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [littleosbook](https://littleosbook.github.io)
