
add_definitions(-D__WINESRC__)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)
spec2def(qedit.dll qedit.spec)

list(APPEND SOURCE
    main.c
    mediadet.c
    samplegrabber.c
    ${CMAKE_CURRENT_BINARY_DIR}/qedit.def)

add_library(qedit SHARED ${SOURCE} qedit.rc)
set_module_type(qedit win32dll)
target_link_libraries(qedit strmiids uuid wine)
add_importlibs(qedit ole32 oleaut32 msvcrt kernel32 ntdll)
add_pch(qedit qedit_private.h)
add_cd_file(TARGET qedit DESTINATION reactos/system32 FOR all)
