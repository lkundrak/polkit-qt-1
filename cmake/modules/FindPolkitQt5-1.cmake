# - Try to find PolkitQt5-1
# Once done this will define
#
#  POLKITQT-1_FOUND - system has Polkit-qt5
#  POLKITQT-1_INCLUDE_DIR - the Polkit-qt5 include directory
#  POLKITQT-1_LIBRARIES - Link these to use all Polkit-qt5 libs
#  POLKITQT-1_CORE_LIBRARY - Link this to use the polkit-qt5-core library only
#  POLKITQT-1_GUI_LIBRARY - Link this to use GUI elements in polkit-qt5 (polkit-qt5-gui)
#  POLKITQT-1_AGENT_LIBRARY - Link this to use the agent wrapper in polkit-qt5
#  POLKITQT-1_DEFINITIONS - Compiler switches required for using Polkit-qt5
#
# The minimum required version of PolkitQt5-1 can be specified using the
# standard syntax, e.g. find_package(PolkitQt5-1 1.0)

# Copyright (c) 2010, Dario Freddi, <drf@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# Support POLKITQT-1_MIN_VERSION for compatibility:
if ( NOT PolkitQt5-1_FIND_VERSION AND POLKITQT-1_MIN_VERSION )
  set ( PolkitQt5-1_FIND_VERSION ${POLKITQT-1_MIN_VERSION} )
endif ( NOT PolkitQt5-1_FIND_VERSION AND POLKITQT-1_MIN_VERSION )

set( _PolkitQt5-1_FIND_QUIETLY  ${PolkitQt5-1_FIND_QUIETLY} )
find_package( PolkitQt5-1 ${PolkitQt5-1_FIND_VERSION} QUIET NO_MODULE PATHS ${LIB_INSTALL_DIR}/PolkitQt5-1/cmake )
set( PolkitQt5-1_FIND_QUIETLY ${_PolkitQt5-1_FIND_QUIETLY} )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( PolkitQt5-1 DEFAULT_MSG PolkitQt5-1_CONFIG )

if (POLKITQT-1_FOUND)
    if (NOT POLKITQT-1_INSTALL_DIR STREQUAL CMAKE_INSTALL_PREFIX)
        message("WARNING: Installation prefix does not match PolicyKit install prefixes. You probably will need to move files installed "
                "in POLICY_FILES_INSTALL_DIR and by dbus_add_activation_system_service to the ${POLKITQT-1_INSTALL_DIR} prefix")
    endif (NOT POLKITQT-1_INSTALL_DIR STREQUAL CMAKE_INSTALL_PREFIX)
endif (POLKITQT-1_FOUND)
