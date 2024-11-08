# Install script for directory: D:/GlassCV1015/hikvision/log/log4qt

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/GlassCV1015/hikvision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/log/log4qt/log4qt.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt" TYPE FILE FILES
    "D:/GlassCV1015/hikvision/log/log4qt/appender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/appenderskeleton.h"
    "D:/GlassCV1015/hikvision/log/log4qt/asyncappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/basicconfigurator.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binaryfileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binarylayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binarylogger.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binaryloggingevent.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binarylogstream.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binarytotextlayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/binarywriterappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/consoleappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/dailyfileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/dailyrollingfileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/fileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/hierarchy.h"
    "D:/GlassCV1015/hikvision/log/log4qt/layout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/level.h"
    "D:/GlassCV1015/hikvision/log/log4qt/log4qtdefs.h"
    "D:/GlassCV1015/hikvision/log/log4qt/log4qt.h"
    "D:/GlassCV1015/hikvision/log/log4qt/log4qtshared.h"
    "D:/GlassCV1015/hikvision/log/log4qt/log4qtsharedptr.h"
    "D:/GlassCV1015/hikvision/log/log4qt/logger.h"
    "D:/GlassCV1015/hikvision/log/log4qt/loggerrepository.h"
    "D:/GlassCV1015/hikvision/log/log4qt/loggingevent.h"
    "D:/GlassCV1015/hikvision/log/log4qt/logmanager.h"
    "D:/GlassCV1015/hikvision/log/log4qt/logstream.h"
    "D:/GlassCV1015/hikvision/log/log4qt/mainthreadappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/mdc.h"
    "D:/GlassCV1015/hikvision/log/log4qt/ndc.h"
    "D:/GlassCV1015/hikvision/log/log4qt/patternlayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/propertyconfigurator.h"
    "D:/GlassCV1015/hikvision/log/log4qt/qmllogger.h"
    "D:/GlassCV1015/hikvision/log/log4qt/rollingbinaryfileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/rollingfileappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/signalappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/simplelayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/simpletimelayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/systemlogappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/ttcclayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/writerappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/xmllayout.h"
    "D:/GlassCV1015/hikvision/log/log4qt/wdcappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/colorconsoleappender.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/helpers" TYPE FILE FILES
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/appenderattachable.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/binaryclasslogger.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/classlogger.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/configuratorhelper.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/datetime.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/dispatcher.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/factory.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/initialisationhelper.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/logerror.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/optionconverter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/patternformatter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/helpers/properties.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/spi" TYPE FILE FILES "D:/GlassCV1015/hikvision/log/log4qt/spi/filter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log4qt/varia" TYPE FILE FILES
    "D:/GlassCV1015/hikvision/log/log4qt/varia/binaryeventfilter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/debugappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/denyallfilter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/levelmatchfilter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/levelrangefilter.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/listappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/nullappender.h"
    "D:/GlassCV1015/hikvision/log/log4qt/varia/stringmatchfilter.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/GlassCV1015/hikvision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/log/log4qt/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
