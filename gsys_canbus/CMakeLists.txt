gsys_add_library(gsys_canbus)

target_sources(gsys_canbus 
    PRIVATE
    gsys_canbus_fifo.c
)

target_include_directories(gsys_canbus
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gsys_canbus
    PUBLIC gsys_remote_display_lib
)
