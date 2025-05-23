# SConstruct
import os

SOURCE_DIR = './src'
BUILD_DIR = './build'

env = Environment()

debug = ARGUMENTS.get('debug', 0)
if int(debug):
    print("Building with debug flags")
    env.Append(CCFLAGS=['-g', '-O0'])  # Debug flags for GCC/clang
    env.Append(CPPDEFINES=['DEBUG'])    # Add DEBUG macro

SConscript(
    f'{SOURCE_DIR}/SConscript',
    variant_dir=BUILD_DIR,
    duplicate=0,
    exports={'env': env}
)