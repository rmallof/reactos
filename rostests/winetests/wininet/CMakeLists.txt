
list(APPEND SOURCE
    ftp.c
    generated.c
    http.c
    internet.c
    url.c
    urlcache.c
    testlist.c)

add_executable(wininet_winetest ${SOURCE})
set_module_type(wininet_winetest win32cui)
add_importlibs(wininet_winetest wininet crypt32 ws2_32 user32 advapi32 msvcrt kernel32)
add_cd_file(TARGET wininet_winetest DESTINATION reactos/bin FOR all)
