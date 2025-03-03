cmake_minimum_required(VERSION 3.10)
project(imagotagScaffold C)

# Add the executable for the "imagotagScaffold" target
add_executable(imagotagScaffold
  src/main.c
  src/hal.h
  src/board.h
)

set(CMAKE_EXECUTABLE_SUFFIX "")

# Include directories
target_include_directories(imagotagScaffold PRIVATE
  src
  "${TOOLKIT_DIR}/lib/libmf/include/"
)

# Set the properties for the "imagotagScaffold" target
set_target_properties(imagotagScaffold PROPERTIES
  XCL "${TOOLKIT_DIR}/config/devices/On Semiconductor/lnk51ew_AX8052F143.xcl"
)


# Set the compiler flags for the "imagotagScaffold" target
target_compile_options(imagotagScaffold PRIVATE
  $<$<COMPILE_LANGUAGE:C>:
    --dptr=1,16,separate
    --core=plain
    --place_constants=code
    --data_model=small
    --code_model=near
    --clib
    -e
    --calling_convention=idata_reentrant
    -D__DATA_MODEL__=1
    -D__CALLING_CONVENTION__=2
  >
)



# Set the linker flags for the target
target_link_options(imagotagScaffold PRIVATE
  -Fubrof
  "SHELL:-D_CODE_SIZE=59389"
  "SHELL:-D_XDATA_SIZE=8192"
  "SHELL:-D_IDATA_SIZE=256"
  "SHELL:-D_PDATA_STACK_SIZE=0x40"       # 64 bytes for pdata stack
  "SHELL:-D_XDATA_STACK_SIZE=0x400"      # 1024 bytes for xdata stack
  "SHELL:-D_IDATA_STACK_SIZE=0x40"       # 64 bytes for idata stack
  "SHELL:-D_EXTENDED_STACK_START=0x00"
  "SHELL:-D_EXTENDED_STACK_END=0x00"
  "SHELL:-D_EXTENDED_STACK_SIZE=0x00"
  "SHELL:-D_NR_OF_VIRTUAL_REGISTERS=8"
  "SHELL:-D_CODEBANK_START=0"
  "SHELL:-D_CODEBANK_END=0"
  "SHELL:-D_XDATA_HEAP_SIZE=0x800"       # 2048 bytes for xdata heap
  "SHELL:-D_FAR_HEAP_SIZE=0x800"         # 2048 bytes for far heap
  "SHELL:-D_HUGE_HEAP_SIZE=0x800"        # 2048 bytes for huge heap
  "SHELL:-D_FAR22_HEAP_SIZE=0x800"       # 2048 bytes for far22 heap
  "SHELL:-D?PBANK=0xD9"
  -xe
  -xm
  -xs
  -xo
  "SHELL:-Ointel-standard=.hex"
  -f $<TARGET_PROPERTY:XCL>
)

# Add the static libraries
target_link_libraries(imagotagScaffold PRIVATE
  "${TOOLKIT_DIR}/lib/clib/cl-pli-nsic-1e16x01.r51"
  "${TOOLKIT_DIR}/lib/libmf/iar/libmf-pli-nsic-1e16x01.r51"
)