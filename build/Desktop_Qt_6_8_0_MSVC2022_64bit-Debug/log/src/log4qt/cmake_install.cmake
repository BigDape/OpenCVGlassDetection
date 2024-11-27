# Install script for directory: D:/v0.0.2/hivision/log/src/log4qt

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/v0.0.2/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/log/src/log4qt/log4qt_d.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/v0.0.2/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/bin/log4qt_d.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt" TYPE FILE FILES
    "D:/v0.0.2/hivision/log/src/log4qt/appender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/appenderskeleton.h"
    "D:/v0.0.2/hivision/log/src/log4qt/asyncappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/basicconfigurator.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binaryfileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binarylayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binarylogger.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binaryloggingevent.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binarylogstream.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binarytotextlayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/binarywriterappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/consoleappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/dailyfileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/dailyrollingfileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/fileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/hierarchy.h"
    "D:/v0.0.2/hivision/log/src/log4qt/layout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/level.h"
    "D:/v0.0.2/hivision/log/src/log4qt/log4qtdefs.h"
    "D:/v0.0.2/hivision/log/src/log4qt/log4qt.h"
    "D:/v0.0.2/hivision/log/src/log4qt/log4qtshared.h"
    "D:/v0.0.2/hivision/log/src/log4qt/log4qtsharedptr.h"
    "D:/v0.0.2/hivision/log/src/log4qt/logger.h"
    "D:/v0.0.2/hivision/log/src/log4qt/loggerrepository.h"
    "D:/v0.0.2/hivision/log/src/log4qt/loggingevent.h"
    "D:/v0.0.2/hivision/log/src/log4qt/logmanager.h"
    "D:/v0.0.2/hivision/log/src/log4qt/logstream.h"
    "D:/v0.0.2/hivision/log/src/log4qt/mainthreadappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/mdc.h"
    "D:/v0.0.2/hivision/log/src/log4qt/ndc.h"
    "D:/v0.0.2/hivision/log/src/log4qt/patternlayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/propertyconfigurator.h"
    "D:/v0.0.2/hivision/log/src/log4qt/qmllogger.h"
    "D:/v0.0.2/hivision/log/src/log4qt/rollingbinaryfileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/rollingfileappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/signalappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/simplelayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/simpletimelayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/systemlogappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/ttcclayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/writerappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/xmllayout.h"
    "D:/v0.0.2/hivision/log/src/log4qt/wdcappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/colorconsoleappender.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/helpers" TYPE FILE FILES
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/appenderattachable.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/binaryclasslogger.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/classlogger.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/configuratorhelper.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/datetime.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/dispatcher.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/factory.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/initialisationhelper.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/logerror.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/optionconverter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/patternformatter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/helpers/properties.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/spi" TYPE FILE FILES "D:/v0.0.2/hivision/log/src/log4qt/spi/filter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/varia" TYPE FILE FILES
    "D:/v0.0.2/hivision/log/src/log4qt/varia/binaryeventfilter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/debugappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/denyallfilter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/levelmatchfilter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/levelrangefilter.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/listappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/nullappender.h"
    "D:/v0.0.2/hivision/log/src/log4qt/varia/stringmatchfilter.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/v0.0.2/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/log/src/log4qt/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
