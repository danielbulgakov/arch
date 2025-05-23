export FONT_PATH=thirdparty/fonts/SF-Pro-Rounded-Regular.otf
export LD_LIBRARY_PATH=thirdparty/SFML-3.0.0/lib:$LD_LIBRARY_PATH
rm -rf build
scons -Q debug=1
gdb ./build/main