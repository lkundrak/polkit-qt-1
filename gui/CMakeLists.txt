set(polkit_qt_gui_SRCS
    polkitqt1-gui-action.cpp
    polkitqt1-gui-actionbutton.cpp
    polkitqt1-gui-actionbuttons.cpp
)

add_library(polkit-qt5-gui-1 SHARED ${polkit_qt_gui_SRCS})

qt5_use_modules(polkit-qt5-gui-1 Core DBus Gui Widgets)

target_link_libraries(polkit-qt5-gui-1
    ${POLKIT_LIBRARIES}
    polkit-qt5-core-1
)
qt5_use_modules(polkit-qt5-gui-1
    Widgets DBus
)

set_target_properties(polkit-qt5-gui-1 PROPERTIES VERSION ${POLKITQT-1_LIBRARY_VERSION}
                                SOVERSION ${POLKITQT-1_ABI_VERSION}
                                DEFINE_SYMBOL MAKE_POLKITQT1_LIB)

install(TARGETS polkit-qt5-gui-1 ${INSTALL_TARGETS_DEFAULT_ARGS})
