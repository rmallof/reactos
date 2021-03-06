
add_definitions(
    -D_NTHALDLL_
    -D_NTHAL_)

include_directories(
    include
    ${REACTOS_SOURCE_DIR}/ntoskrnl/include)

function(add_hal _halname)
    cmake_parse_arguments(_haldata "" "" "SOURCES;COMPONENTS" ${ARGN})

    # Handle the spec file for the dll name
    spec2def(${_halname}.dll ../hal.spec ADD_IMPORTLIB)

    # Create the actual target
    if(NOT MSVC)
        foreach(_component ${_haldata_COMPONENTS})
            list(APPEND _haldata_SOURCES "$<TARGET_OBJECTS:lib_hal_${_component}>")
        endforeach()
        add_library(${_halname} SHARED
            ${_haldata_SOURCES}
            ${CMAKE_CURRENT_BINARY_DIR}/hal.def)
    else()
        foreach(_component ${_haldata_COMPONENTS})
            list(APPEND _haldata_LIBS "lib_hal_${_component}")
        endforeach()
        add_library(${_halname} SHARED
            ${_haldata_SOURCES}
            ${CMAKE_CURRENT_BINARY_DIR}/hal.def)
        target_link_libraries(${_halname} ${_haldata_LIBS})
    endif()

    target_link_libraries(${_halname} libcntpr)
    add_importlibs(${_halname} ntoskrnl)
    #add_pch(${_halname} include/hal.h)
    add_dependencies(${_halname} psdk bugcodes asm)
    set_entrypoint(${_halname} HalInitSystem 8)
    set_subsystem(${_halname} native)
    set_image_base(${_halname} 0x00010000)
    add_cd_file(TARGET ${_halname} DESTINATION reactos/system32 NO_CAB FOR all)
    if(MSVC)
        add_target_link_flags(${_halname} "/ignore:4216 /ignore:4078")
    else()
        target_link_libraries(${_halname} -lgcc)
    endif()
endfunction()

# The components
include(generic.cmake)
include(acpi.cmake)
include(apic.cmake)

if(ARCH STREQUAL "i386")
    include(pcidata.cmake)
    include(legacy.cmake)
    include(up.cmake)
    include(pic.cmake)
    include(minihal.cmake)

    # hal
    add_hal(hal SOURCES up/halup.rc COMPONENTS generic legacy up pic)
    add_hal(halacpi SOURCES acpi/halacpi.rc COMPONENTS generic acpi up pic)
    add_hal(halapic SOURCES acpi/halacpi.rc COMPONENTS generic legacy up apic)
    add_hal(halaacpi SOURCES acpi/halacpi.rc COMPONENTS generic acpi up apic)

    #add_hal(halmps SOURCES up/halup.rc COMPONENTS generic legacy smp pic)
    #add_hal(halmacpi SOURCES acpi/halacpi.rc COMPONENTS generic acpi smp pic)
    #add_hal(halmapic SOURCES acpi/halacpi.rc COMPONENTS generic legacy smp apic)
    #add_hal(halmaacpi SOURCES acpi/halacpi.rc COMPONENTS generic acpi smp apic)

elseif(ARCH STREQUAL "amd64")

    list(APPEND HAL_SOURCE
        generic/spinlock.c
        amd64/x86bios.c
        amd64/halinit.c
        amd64/processor.c)

    add_hal(hal SOURCES ${HAL_SOURCE} COMPONENTS generic acpi apic)

endif()
