
list(APPEND SOURCE
    image.c
    integrity.c
    testlist.c)

add_executable(imagehlp_winetest ${SOURCE})
set_module_type(imagehlp_winetest win32cui)
add_importlibs(imagehlp_winetest msvcrt kernel32)
add_cd_file(TARGET imagehlp_winetest DESTINATION reactos/bin FOR all)
