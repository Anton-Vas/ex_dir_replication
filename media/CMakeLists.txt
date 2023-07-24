
# target_sources(
#     ${CMAKE_PROJECT_NAME}
#     PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/.hpp
#     ${CMAKE_CURRENT_LIST_DIR}/.cpp
# )

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)