# Install script for directory: /home/erdog1/embeddPython/drogon

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/erdog1/embeddPython/build/drogon/libdrogon.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drogon" TYPE FILE FILES
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/Attribute.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/CacheMap.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/Cookie.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/DrClassMap.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/DrObject.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/DrTemplate.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/DrTemplateBase.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpAppFramework.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpBinder.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpClient.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpController.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpFilter.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpRequest.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpResponse.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpSimpleController.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpTypes.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/HttpViewData.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/IntranetIpFilter.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/IOThreadStorage.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/LocalHostFilter.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/MultiPart.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/NotFound.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/Session.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/UploadFile.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/WebSocketClient.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/WebSocketConnection.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/WebSocketController.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/drogon.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/version.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/drogon_callbacks.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/PubSubService.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drogon/orm" TYPE FILE FILES
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/ArrayParser.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Criteria.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/DbClient.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Exception.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Field.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/FunctionTraits.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Mapper.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Result.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/ResultIterator.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/Row.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/RowIterator.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/SqlBinder.h"
    "/home/erdog1/embeddPython/drogon/orm_lib/inc/drogon/orm/RestfulController.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drogon/utils" TYPE FILE FILES
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/FunctionTraits.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/Utilities.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/any.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/string_view.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/HttpConstraint.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/utils/OStringStream.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drogon/plugins" TYPE FILE FILES
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/plugins/Plugin.h"
    "/home/erdog1/embeddPython/drogon/lib/inc/drogon/plugins/SecureSSLRedirector.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon" TYPE FILE FILES
    "/home/erdog1/embeddPython/build/drogon/CMakeFiles/DrogonConfig.cmake"
    "/home/erdog1/embeddPython/build/drogon/DrogonConfigVersion.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/FindUUID.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/FindJsoncpp.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/FindSQLite3.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/FindMySQL.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/Findpg.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/FindBrotli.cmake"
    "/home/erdog1/embeddPython/drogon/cmake_modules/Findcoz-profiler.cmake"
    "/home/erdog1/embeddPython/drogon/cmake/DrogonUtilities.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon/DrogonTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon/DrogonTargets.cmake"
         "/home/erdog1/embeddPython/build/drogon/CMakeFiles/Export/lib/cmake/Drogon/DrogonTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon/DrogonTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon/DrogonTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon" TYPE FILE FILES "/home/erdog1/embeddPython/build/drogon/CMakeFiles/Export/lib/cmake/Drogon/DrogonTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Drogon" TYPE FILE FILES "/home/erdog1/embeddPython/build/drogon/CMakeFiles/Export/lib/cmake/Drogon/DrogonTargets-noconfig.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/erdog1/embeddPython/build/drogon/trantor/cmake_install.cmake")
  include("/home/erdog1/embeddPython/build/drogon/examples/cmake_install.cmake")
  include("/home/erdog1/embeddPython/build/drogon/drogon_ctl/cmake_install.cmake")

endif()

