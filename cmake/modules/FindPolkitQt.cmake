# - Try to find Polkit-qt
# Once done this will define
#
#  POLKITQT_FOUND - system has Polkit-qt
#  POLKITQT_INCLUDE_DIR - the Polkit-qt include directory
#  POLKITQT_LIB - Link these to use Polkit-qt
#  POLKITQT_DEFINITIONS - Compiler switches required for using Polkit-qt

# Copyright (c) 2008, Adrien Bustany, <madcat@mymadcat.com>
# Copyright (c) 2009, Daniel Nicoletti, <dantti85-pk@yahoo.com.br>
#
# Redistribution and use is allowed according to the terms of the GPLv2+ license.

IF (POLKITQT_INCLUDE_DIR AND POLKITQT_LIB)
    SET(POLKITQT_FIND_QUIETLY TRUE)
ENDIF (POLKITQT_INCLUDE_DIR AND POLKITQT_LIB)

# FIND_PATH( POLKITQT_INCLUDE_DIR PolicyKit/policykit-qt/Polkit-qt )
FIND_PATH( POLKITQT_INCLUDE_DIR PolicyKit/polkit-qt/ )

FIND_LIBRARY( POLKITQT_LIB NAMES polkit-qt )

IF (POLKITQT_INCLUDE_DIR AND POLKITQT_LIB)
   SET(POLKITQT_FOUND TRUE)
ELSE (POLKITQT_INCLUDE_DIR AND POLKITQT_LIB)
   SET(POLKITQT_FOUND FALSE)
ENDIF (POLKITQT_INCLUDE_DIR AND POLKITQT_LIB)

SET(POLKITQT_INCLUDE_DIR ${POLKITQT_INCLUDE_DIR}/PolicyKit/polkit-qt ${POLKITQT_INCLUDE_DIR}/PolicyKit/)

IF (POLKITQT_FOUND)
  IF (NOT POLKITQT_FIND_QUIETLY)
    MESSAGE(STATUS "Found Polkit-qt: ${POLKITQT_LIB}")
  ENDIF (NOT POLKITQT_FIND_QUIETLY)
ELSE (POLKITQT_FOUND)
  IF (POLKITQT_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could NOT find Polkit-qt")
  ENDIF (POLKITQT_FIND_REQUIRED)
ENDIF (POLKITQT_FOUND)

MARK_AS_ADVANCED(POLKITQT_INCLUDE_DIR POLKITQT_LIB)
