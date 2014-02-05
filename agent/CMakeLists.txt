set(polkit_qt_agent_SRCS
    polkitqt1-agent-session.cpp
    polkitqt1-agent-listener.cpp
    listeneradapter.cpp
    polkitqtlistener.cpp
)

add_library(polkit-qt5-agent-1 SHARED ${polkit_qt_agent_SRCS})

qt5_use_modules(polkit-qt5-agent-1 Core)

target_link_libraries(polkit-qt5-agent-1
    ${POLKIT_LIBRARIES}
    ${POLKIT_AGENT_LIBRARY}
    polkit-qt5-core-1
)

set_target_properties(polkit-qt5-agent-1 PROPERTIES VERSION ${POLKITQT-1_LIBRARY_VERSION}
                                SOVERSION ${POLKITQT-1_ABI_VERSION}
                                DEFINE_SYMBOL MAKE_POLKITQT1_LIB)

install(TARGETS polkit-qt5-agent-1 ${INSTALL_TARGETS_DEFAULT_ARGS})
