prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=@CMAKE_INSTALL_PREFIX@
libdir=@LIB_INSTALL_DIR@
includedir=@CMAKE_INSTALL_PREFIX@/include

Name: polkit-qt5-1
Description: Convenience library for using polkit with a Qt-styled API
Version: @POLKITQT-1_VERSION_STRING@
Requires: polkit-qt5-core-1 polkit-qt5-gui-1 polkit-qt5-agent-1
Libs: -L${libdir} -lpolkit-qt5-core-1 -lpolkit-qt5-gui-1 -lpolkit-qt5-agent-1
Cflags: -I${includedir}
