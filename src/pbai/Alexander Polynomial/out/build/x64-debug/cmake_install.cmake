# Install script for directory: C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/install/x64-debug")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/int_polynomial/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/double_polynomial/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/double_matrix/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/int_polynomial_matrix/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/pd_code/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/braid/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/trace_jones_polynomial/cmake_install.cmake")
  include("C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/misc/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/fgye1/OneDrive/Documents/GitHub/Knot-Theory/Alexander Polynomial/out/build/x64-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
