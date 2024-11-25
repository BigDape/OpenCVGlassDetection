# Install script for directory: D:/code/hivision/log/src/log4qt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/hikvision")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/code/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/log/src/log4qt/log4qt_d.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/code/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/bin/log4qt_d.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt" TYPE FILE FILES
    "D:/code/hivision/log/src/log4qt/appender.h"
    "D:/code/hivision/log/src/log4qt/appenderskeleton.h"
    "D:/code/hivision/log/src/log4qt/asyncappender.h"
    "D:/code/hivision/log/src/log4qt/basicconfigurator.h"
    "D:/code/hivision/log/src/log4qt/binaryfileappender.h"
    "D:/code/hivision/log/src/log4qt/binarylayout.h"
    "D:/code/hivision/log/src/log4qt/binarylogger.h"
    "D:/code/hivision/log/src/log4qt/binaryloggingevent.h"
    "D:/code/hivision/log/src/log4qt/binarylogstream.h"
    "D:/code/hivision/log/src/log4qt/binarytotextlayout.h"
    "D:/code/hivision/log/src/log4qt/binarywriterappender.h"
    "D:/code/hivision/log/src/log4qt/consoleappender.h"
    "D:/code/hivision/log/src/log4qt/dailyfileappender.h"
    "D:/code/hivision/log/src/log4qt/dailyrollingfileappender.h"
    "D:/code/hivision/log/src/log4qt/fileappender.h"
    "D:/code/hivision/log/src/log4qt/hierarchy.h"
    "D:/code/hivision/log/src/log4qt/layout.h"
    "D:/code/hivision/log/src/log4qt/level.h"
    "D:/code/hivision/log/src/log4qt/log4qtdefs.h"
    "D:/code/hivision/log/src/log4qt/log4qt.h"
    "D:/code/hivision/log/src/log4qt/log4qtshared.h"
    "D:/code/hivision/log/src/log4qt/log4qtsharedptr.h"
    "D:/code/hivision/log/src/log4qt/logger.h"
    "D:/code/hivision/log/src/log4qt/loggerrepository.h"
    "D:/code/hivision/log/src/log4qt/loggingevent.h"
    "D:/code/hivision/log/src/log4qt/logmanager.h"
    "D:/code/hivision/log/src/log4qt/logstream.h"
    "D:/code/hivision/log/src/log4qt/mainthreadappender.h"
    "D:/code/hivision/log/src/log4qt/mdc.h"
    "D:/code/hivision/log/src/log4qt/ndc.h"
    "D:/code/hivision/log/src/log4qt/patternlayout.h"
    "D:/code/hivision/log/src/log4qt/propertyconfigurator.h"
    "D:/code/hivision/log/src/log4qt/qmllogger.h"
    "D:/code/hivision/log/src/log4qt/rollingbinaryfileappender.h"
    "D:/code/hivision/log/src/log4qt/rollingfileappender.h"
    "D:/code/hivision/log/src/log4qt/signalappender.h"
    "D:/code/hivision/log/src/log4qt/simplelayout.h"
    "D:/code/hivision/log/src/log4qt/simpletimelayout.h"
    "D:/code/hivision/log/src/log4qt/systemlogappender.h"
    "D:/code/hivision/log/src/log4qt/ttcclayout.h"
    "D:/code/hivision/log/src/log4qt/writerappender.h"
    "D:/code/hivision/log/src/log4qt/xmllayout.h"
    "D:/code/hivision/log/src/log4qt/wdcappender.h"
    "D:/code/hivision/log/src/log4qt/colorconsoleappender.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/helpers" TYPE FILE FILES
    "D:/code/hivision/log/src/log4qt/helpers/appenderattachable.h"
    "D:/code/hivision/log/src/log4qt/helpers/binaryclasslogger.h"
    "D:/code/hivision/log/src/log4qt/helpers/classlogger.h"
    "D:/code/hivision/log/src/log4qt/helpers/configuratorhelper.h"
    "D:/code/hivision/log/src/log4qt/helpers/datetime.h"
    "D:/code/hivision/log/src/log4qt/helpers/dispatcher.h"
    "D:/code/hivision/log/src/log4qt/helpers/factory.h"
    "D:/code/hivision/log/src/log4qt/helpers/initialisationhelper.h"
    "D:/code/hivision/log/src/log4qt/helpers/logerror.h"
    "D:/code/hivision/log/src/log4qt/helpers/optionconverter.h"
    "D:/code/hivision/log/src/log4qt/helpers/patternformatter.h"
    "D:/code/hivision/log/src/log4qt/helpers/properties.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/spi" TYPE FILE FILES "D:/code/hivision/log/src/log4qt/spi/filter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/varia" TYPE FILE FILES
    "D:/code/hivision/log/src/log4qt/varia/binaryeventfilter.h"
    "D:/code/hivision/log/src/log4qt/varia/debugappender.h"
    "D:/code/hivision/log/src/log4qt/varia/denyallfilter.h"
    "D:/code/hivision/log/src/log4qt/varia/levelmatchfilter.h"
    "D:/code/hivision/log/src/log4qt/varia/levelrangefilter.h"
    "D:/code/hivision/log/src/log4qt/varia/listappender.h"
    "D:/code/hivision/log/src/log4qt/varia/nullappender.h"
    "D:/code/hivision/log/src/log4qt/varia/stringmatchfilter.h"
    )
endif()

