# Builds the webui module

add_subdirectory(lib)

add_definitions(-DQT_NO_KEYWORDS -DWT_NO_SLOT_MACROS)
# link_libraries( )
include_directories(${Wt_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

set(QT_DONT_USE_QTGUI 1)
set(QT_USE_QTNETWORK 1)
include(${QT_USE_FILE})

set(SOURCES
    webapplication.cpp
    webmessagemodel.cpp
    weblogindialog.cpp
    webmessagemodelitem.cpp
    webmessageprocessor.cpp
    webui.cpp)

set(MOC_HDRS
    webapplication.h
    weblogindialog.h
    webmessagemodel.h
    webmessagemodelitem.h
    webmessageprocessor.h
    webui.h)

set(HEADERS
    webui.h)

qt4_wrap_cpp(MOC ${MOC_HDRS} ${SPHDR} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

include_directories(${CMAKE_SOURCE_DIR}/src/common
                    ${CMAKE_SOURCE_DIR}/src/client
                    ${CMAKE_SOURCE_DIR}/src/webui
                    ${CMAKE_SOURCE_DIR}/src/webui/lib
                    ${CMAKE_CURRENT_BINARY_DIR})

add_library(mod_webui STATIC ${SOURCES} ${SPSRC} ${MOC} ${DBUS} ${UI} ${HEADERS})
target_link_libraries(mod_webui ${Wt_LIBRARIES} ${Boost_LIBRARIES} ${QT_LIBRARIES} wtwithqt)
add_dependencies(mod_webui mod_common mod_client)

