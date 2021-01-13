cmake_minimum_required(VERSION 3.19)

# Update this as you add new source files.
set(SRC
	src/moddef.c
	)

# Read project metadata from ModInfo.json.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/ModInfo.json" MOD_INFO)
string(JSON MOD_NAME
	GET ${MOD_INFO} name)
string(JSON MOD_VERSION
	GET ${MOD_INFO} version)
string(JSON MOD_DESCRIPTION
	GET ${MOD_INFO} description)

# Define project.
project(${MOD_NAME}
	VERSION ${MOD_VERSION}
	DESCRIPTION ${MOD_DESCRIPTION}
	LANGUAGES C)

# Set cmake defaults.
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "lib${MOD_NAME}-${MOD_VERSION}"
		CACHE PATH "..." FORCE)
endif()

# Include CPack.
set(CPACK_PACKAGE_FILE_NAME "lib${MOD_NAME}-${MOD_VERSION}")
include(CPack)

# Include GenerateExportHeader.
include(GenerateExportHeader)

# Include AERMRE.
set(AERMRE_SCRIPT_REL "aer/mre/lib/cmake/AERMRETargets.cmake")
include("$ENV{AER_GAMEDIR}/${AERMRE_SCRIPT_REL}")

# Add mod shared library target.
add_library(${MOD_NAME} SHARED ${SRC})
generate_export_header(${MOD_NAME}
	BASE_NAME MOD
	EXPORT_FILE_NAME include/export.h)
set_target_properties(${MOD_NAME} PROPERTIES
	C_VISIBILITY_PRESET hidden
	CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)
target_include_directories(${MOD_NAME}
	PRIVATE include
	PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_compile_options(${MOD_NAME}
	PRIVATE -m32
	PRIVATE -Wall
	PRIVATE -Wextra
	PRIVATE -Werror)
target_link_options(${MOD_NAME}
	PRIVATE -m32
	PRIVATE -rdynamic)
target_link_libraries(${MOD_NAME}
	PRIVATE AERMRE::aermre)

# Add installation target.
install(TARGETS
  ${MOD_NAME} LIBRARY)
install(FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/ModInfo.json"
  DESTINATION ".")
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
  install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
    DESTINATION ".")
endif()
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/NOTICE.txt")
  install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/NOTICE.txt"
    DESTINATION ".")
endif()
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
  install(DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    DESTINATION ".")
endif()
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ACKNOWLEGMENTS")
  install(DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/ACKNOWLEGMENTS"
    DESTINATION ".")
endif()
