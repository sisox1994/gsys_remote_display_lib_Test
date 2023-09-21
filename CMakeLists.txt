gsys_add_library(gsys_remote_display_lib)

target_sources(gsys_remote_display_lib 
    PRIVATE
    gsys_data_processor.c
    gsys_device_configurator.c
    gsys_ebike_data_collection.c
    gsys_inc/gsys_remote_display_lib.h
)

target_include_directories(gsys_remote_display_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/gsys_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/gsys_inc/gsys_data_structure
)


target_link_libraries(gsys_remote_display_lib
    PUBLIC gsys_canbus
    PUBLIC gsys_rx_data
    PUBLIC gsys_tx_data
)

add_subdirectory(gsys_canbus)
add_subdirectory(gsys_rx_data)
add_subdirectory(gsys_tx_data)
