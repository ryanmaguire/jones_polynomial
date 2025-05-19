# CMakeList.txt : CMake project for Alexander Polynomial, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CXXFLAGS  "-Weverything -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

set (CMAKE_C_STANDARD 90)

project (apoly)

# Add source to this project's executable.
add_executable (apoly main.c "trace_jones_polynomial/trace_jones_polynomial.h" "trace_jones_polynomial/big_omega.c" "misc/misc.h")

add_subdirectory(int_polynomial)
target_link_libraries(apoly int_polynomial)

add_subdirectory(double_polynomial)
target_link_libraries(apoly double_polynomial)

add_subdirectory(double_matrix)
target_link_libraries(apoly double_matrix)

add_subdirectory(int_polynomial_matrix)
target_link_libraries(apoly int_polynomial_matrix)

add_subdirectory(pd_code)
target_link_libraries(apoly pd_code)

add_subdirectory(braid)
target_link_libraries(apoly braid)

add_subdirectory(trace_jones_polynomial)
target_link_libraries(apoly trace_jones_polynomial)

add_subdirectory(misc)
target_link_libraries(apoly misc)


# TODO: Add tests and install targets if needed.
