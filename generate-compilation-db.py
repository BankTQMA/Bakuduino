import os

Import("env")  # noqa: F821  (provided by SCons/PlatformIO)

# Include toolchain headers (without this, clangd can't find e.g. <machine/endian.h>)
env.Replace(COMPILATIONDB_INCLUDE_TOOLCHAIN=True)

# Write the database to the project root, where clangd looks for it
env.Replace(COMPILATIONDB_PATH=os.path.join("$PROJECT_DIR", "compile_commands.json"))
