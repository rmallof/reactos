

include_directories(
    BEFORE include
    ${REACTOS_SOURCE_DIR}/include/reactos/drivers)

spec2def(msafd.dll msafd.spec)

list(APPEND SOURCE
    msafd.rc
    misc/dllmain.c
    misc/event.c
    misc/helpers.c
    misc/sndrcv.c
    misc/stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/msafd.def)

add_library(msafd SHARED ${SOURCE})

set_module_type(msafd win32dll UNICODE)

add_importlibs(msafd advapi32 msvcrt kernel32 ntdll)
add_pch(msafd msafd.h)
add_cd_file(TARGET msafd DESTINATION reactos/system32 FOR all)
