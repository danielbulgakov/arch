export LD_LIBRARY_PATH=thirdparty/SFML-3.0.0/lib:$LD_LIBRARY_PATH
export FONT_PATH=thirdparty/fonts/SF-Pro-Rounded-Regular.otf
rm -rf build
scons -Q
./build/main