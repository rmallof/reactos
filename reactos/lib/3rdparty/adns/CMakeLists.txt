
include_directories(
    src
    adns_win32)

add_definitions(
    -D_DLL -D__USE_CRTIMP
    -DADNS_JGAA_WIN32)

list(APPEND SOURCE
    adns_win32/adns_unix_calls.c
    src/check.c
    src/event.c
    src/general.c
    src/parse.c
    src/poll.c
    src/query.c
    src/reply.c
    src/setup.c
    src/transmit.c
    src/types.c)

add_library(adns ${SOURCE})
add_dependencies(adns psdk)

if(NOT MSVC)
    add_target_compile_flags(adns "-Wno-unused-but-set-variable")
endif()
