gsys_add_library(gsys_rx_data)

target_sources(gsys_rx_data 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/data_frame/active_data/gsys_active_data_monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/data_frame/event_data/gsys_event_data_monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/remote_frame/gsys_remote_frame_monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/data_frame/gsys_data_frame_monitor.c
)

target_include_directories(gsys_rx_data 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gsys_rx_data
    PUBLIC gsys_canbus
    PUBLIC gsys_remote_display_lib
)
