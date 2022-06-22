include(ExternalProject)

if (VENDOR_LIBVTERM)
    externalproject_add(libvterm_vendored
        PREFIX ${CMAKE_BINARY_DIR}/libvterm
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libvterm
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ./build.sh
            PREFIX=${CMAKE_BINARY_DIR}/root
            CFLAGS=-O3\ -g\ -fPIC
        BUILD_IN_SOURCE YES
        INSTALL_COMMAND ./build.sh install
    )
endif()
