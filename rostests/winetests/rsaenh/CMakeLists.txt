
add_executable(rsaenh_winetest rsaenh.c testlist.c)
set_module_type(rsaenh_winetest win32cui)
add_importlibs(rsaenh_winetest advapi32 msvcrt kernel32)
add_cd_file(TARGET rsaenh_winetest DESTINATION reactos/bin FOR all)
