
add_definitions(
    -D__WINESRC__
    -DUSE_WIN32_OPENGL)

include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(d3d9.dll d3d9.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    buffer.c
    d3d9_main.c
    device.c
    directx.c
    query.c
    shader.c
    stateblock.c
    surface.c
    swapchain.c
    texture.c
    vertexdeclaration.c
    volume.c
    version.rc
    ${CMAKE_CURRENT_BINARY_DIR}/d3d9_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/d3d9.def)

add_library(d3d9 SHARED ${SOURCE})
set_module_type(d3d9 win32dll UNICODE)
target_link_libraries(d3d9 wine)
add_importlibs(d3d9 wined3d msvcrt kernel32 ntdll)
add_pch(d3d9 d3d9_private.h)
add_cd_file(TARGET d3d9 DESTINATION reactos/system32 FOR all)
