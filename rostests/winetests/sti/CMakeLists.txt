
add_executable(sti_winetest sti.c testlist.c)
set_module_type(sti_winetest win32cui)
add_importlibs(sti_winetest ole32 msvcrt kernel32)
add_cd_file(TARGET sti_winetest DESTINATION reactos/bin FOR all)
