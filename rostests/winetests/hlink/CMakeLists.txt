
add_definitions(-D__ROS_LONG64__)

list(APPEND SOURCE
    browse_ctx.c
    hlink.c
    testlist.c)

add_executable(hlink_winetest ${SOURCE})
set_module_type(hlink_winetest win32cui)
add_importlibs(hlink_winetest hlink ole32 msvcrt kernel32)
add_cd_file(TARGET hlink_winetest DESTINATION reactos/bin FOR all)
