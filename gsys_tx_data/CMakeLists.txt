gsys_add_library(gsys_tx_data)

target_sources(gsys_tx_data 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/data_frame/gsys_active_data_encoder.c
    ${CMAKE_CURRENT_SOURCE_DIR}/data_frame/gsys_response_data_encoder.c
    ${CMAKE_CURRENT_SOURCE_DIR}/remote_frame/gsys_remote_data_encoder.c
)

target_include_directories(gsys_tx_data 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gsys_tx_data
    PUBLIC gsys_canbus
    PUBLIC gsys_remote_display_lib
)
