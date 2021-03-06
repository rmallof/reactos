
add_definitions(
    -D__WINESRC__
    -D_URLMON_
    -DENTRY_PREFIX=URLMON_
    -DPROXY_DELEGATION
    -DWINE_REGISTER_DLL
    -DPROXY_CLSID_IS="{0x79EAC9F1,0xBAF9,0x11CE,{0x8C,0x82,0x00,0xAA,0x00,0x4B,0xA9,0x0B}}")

#remove_definitions(-D_WIN32_WINNT=0x502)
#add_definitions(-D_WIN32_WINNT=0x600)

include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)
spec2def(urlmon.dll urlmon.spec ADD_IMPORTLIB)
add_rpcproxy_files(urlmon_urlmon.idl)

list(APPEND SOURCE
    axinstall.c
    bindctx.c
    binding.c
    bindprot.c
    download.c
    file.c
    format.c
    ftp.c
    gopher.c
    http.c
    internet.c
    mimefilter.c
    mk.c
    protocol.c
    sec_mgr.c
    session.c
    umon.c
    umstream.c
    uri.c
    urlmon_main.c
    usrmarshal.c
    ${CMAKE_CURRENT_BINARY_DIR}/proxy.dlldata.c
    ${CMAKE_CURRENT_BINARY_DIR}/urlmon_urlmon_p.c
    ${CMAKE_CURRENT_BINARY_DIR}/urlmon_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/urlmon.def)

add_library(urlmon SHARED ${SOURCE} urlmon.rc)
set_module_type(urlmon win32dll)
target_link_libraries(urlmon uuid wine ${PSEH_LIB})
add_importlibs(urlmon rpcrt4 propsys ole32 oleaut32 shlwapi shell32 wininet user32 advapi32 advpack msvcrt kernel32 ntdll)
add_pch(urlmon urlmon_main.h)
add_cd_file(TARGET urlmon DESTINATION reactos/system32 FOR all)
