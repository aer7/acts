# Find the ONNX Runtime include directory and library.
#
# This module defines the `onnxruntime` imported target that encodes all
# necessary information in its target properties.

find_library(
  OnnxRuntime_LIBRARY
  NAMES onnxruntime
  PATHS ${onnxruntime_DIR}
  PATH_SUFFIXES lib lib32 lib64
  DOC "The ONNXRuntime library")
  
if(NOT OnnxRuntime_LIBRARY)
  message(FATAL_ERROR "onnxruntime library not found")
else()
  message(STATUS "Found OnnxRuntime library at ${OnnxRuntime_LIBRARY}")
endif()

find_path(
  OnnxRuntime_INCLUDE_DIR
  NAMES core/session/onnxruntime_cxx_api.h #core/session/providers/cuda_provider_factory.h
  PATHS ${onxxruntime_DIR}
  PATH_SUFFIXES include include/onnxruntime
  DOC "The ONNXRuntime include directory")
  
if(NOT OnnxRuntime_INCLUDE_DIR)
  message(FATAL_ERROR "onnxruntime includes not found")
else()
  message(STATUS "Found OnnxRuntime includes at ${OnnxRuntime_INCLUDE_DIR}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  OnnxRuntime
  REQUIRED_VARS OnnxRuntime_LIBRARY OnnxRuntime_INCLUDE_DIR)

add_library(OnnxRuntime SHARED IMPORTED)
set_property(TARGET OnnxRuntime PROPERTY IMPORTED_LOCATION ${OnnxRuntime_LIBRARY})
set_property(TARGET OnnxRuntime PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OnnxRuntime_INCLUDE_DIR})
set_property(TARGET OnnxRuntime PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${OnnxRuntime_INCLUDE_DIR})

mark_as_advanced(OnnxRuntime_FOUND OnnxRuntime_INCLUDE_DIR OnnxRuntime_LIBRARY)
