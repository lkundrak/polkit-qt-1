include_directories(
    ${CMAKE_SOURCE_DIR}/agent
)

set(polkit_agent_example_SRCS
    main.cpp
    pkagentexample.cpp
    klistener.cpp
)

add_executable(polkit-agent-example
    ${polkit_agent_example_SRCS}
)

target_link_libraries(polkit-agent-example
    polkit-qt5-agent-1
    polkit-qt5-core-1
)

qt5_use_modules(polkit-agent-example
    Widgets
)
