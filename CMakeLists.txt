cmake_minimum_required(VERSION 3.16)

project(hikvision VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("当前路径为：${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tool)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpulib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/camare)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/socket)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/database)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/log)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unittest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
enable_testing()
add_test(test_app ${CMAKE_SOURCE_DIR}/build/test/test_app)



# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# set(TS_FILES hikvision_zh_CN.ts)

# set(PROJECT_SOURCES
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#         mainwindow.ui
#         ${TS_FILES}
# )

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(hikvision
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET hikvision APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# else()
#     if(ANDROID)
#         add_library(hikvision SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(hikvision
#             ${PROJECT_SOURCES}
#         )
#     endif()

#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# endif()

# target_link_libraries(hikvision PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.hikvision)
# endif()
# set_target_properties(hikvision PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# include(GNUInstallDirs)
# add_subdirectory(./log/)
# install(TARGETS hikvision
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(hikvision)
# endif()
