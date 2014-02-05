enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/agent
)

add_executable(polkit-qt5-test
    test.cpp
)

target_link_libraries(polkit-qt5-test
    polkit-qt5-core-1
)
qt5_use_modules(polkit-qt5-test
    Core DBus Test
)

add_test(BaseTest ${CMAKE_CURRENT_BINARY_DIR}/polkit-qt5-test)
