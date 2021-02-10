cmake_minimum_required(VERSION 3.10)

project(EXRImporterPlugin)

set(OpenEXRLibraryPath "" CACHE STRING "OpenEXR library path")
set(OpenEXRIncludePath "" CACHE STRING "OpenEXR include path")
set(OpenEXRSuffix "-2_5" CACHE STRING "")

add_definitions(-DOPENEXR_DLL)

link_directories(${OpenEXRLibraryPath})
include_directories(${OpenEXRIncludePath})

add_library(EXRImporterPlugin SHARED EXRImporterPlugin.cpp)

target_link_libraries(EXRImporterPlugin
	IlmThread${OpenEXRSuffix}
	Imath${OpenEXRSuffix}
	IexMath${OpenEXRSuffix}
	Iex${OpenEXRSuffix}
	Half${OpenEXRSuffix}
	IlmImf${OpenEXRSuffix}
	IlmImfUtil${OpenEXRSuffix}
)

