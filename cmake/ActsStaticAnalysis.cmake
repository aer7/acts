if(ACTS_RUN_CLANG_TIDY)
  find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
  if(NOT CLANG_TIDY_COMMAND)
    message(WARNING "ACTS_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
    set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
  else()
    message(STATUS "Setting up clang-tidy run")

    set(_chks "")
    list(APPEND _chks "-*")
    # list(APPEND _chks "readability-*")
    # list(APPEND _chks "-readability-redundant-member-init")
    # list(APPEND _chks "misc-*")
    # list(APPEND _chks "-misc-unused-parameters")
    # list(APPEND _chks "bugprone-*")
    # list(APPEND _chks "performance-*")
    # list(APPEND _chks "modernize-*")
    # list(APPEND _chks "-modernize-use-auto")
    # list(APPEND _chks "-modernize-use-trailing-return-type")
    # list(APPEND _chks "clang-analyzer-deadcode.*")
    # list(APPEND _chks "clang-analyzer-*")
    # list(APPEND _chks "-clang-analyzer-osx.*")
    # list(APPEND _chks "-clang-analyzer-unix.*")
    # list(APPEND _chks "cppcoreguidelines-*")
    # list(APPEND _chks "-cppcoreguidelines-pro-type-vararg")
    # list(APPEND _chks "-cppcoreguidelines-owning-memory")
    # list(APPEND _chks "-cppcoreguidelines-pro-bounds-constant-array")

    list(APPEND _chks "readability-inconsistent-declaration-parameter-name")
    list(APPEND _chks "readability-named-parameter")
    list(APPEND _chks "readability-container-size-empty")
    list(APPEND _chks "modernize-use-using")
    list(APPEND _chks "readability-braces-around-statements")
    list(APPEND _chks "modernize-use-override")
    list(APPEND _chks "modernize-use-equals-default")
    list(APPEND _chks "readability-implicit-bool-cast")
    list(APPEND _chks "readability-implicit-bool-conversion")
    list(APPEND _chks "modernize-use-default-member-init")
    list(APPEND _chks "performance-unnecessary-value-param")
    list(APPEND _chks "performance-move-const-arg")
    list(APPEND _chks "performance-for-range-copy")
    list(APPEND _chks "modernize-use-equals-default")
    list(APPEND _chks "modernize-use-nullptr")
    list(APPEND _chks "cppcoreguidelines-pro-type-member-init")
    list(APPEND _chks "cppcoreguidelines-init-variables")
    list(APPEND _chks "clang-analyzer-optin.cplusplus.UninitializedObject")
    list(JOIN _chks "," CLANG_TIDY_CHECKS)

    message(STATUS "Configured checks")
    foreach(_chk ${_chks})
      message(STATUS "|-> ${_chk}")
    endforeach()

    set(_errs "")
    # list(APPEND _errs "readability-inconsistent-declaration-parameter-name")
    # list(APPEND _errs "readability-named-parameter")
    # list(APPEND _errs "readability-container-size-empty")
    # list(APPEND _errs "modernize-use-using")
    # list(APPEND _errs "readability-braces-around-statements")
    # list(APPEND _errs "modernize-use-override")
    # list(APPEND _errs "modernize-use-equals-default")
    # list(APPEND _errs "readability-implicit-bool-cast")
    # list(APPEND _errs "readability-implicit-bool-conversion")
    # list(APPEND _errs "modernize-use-default-member-init")
    # list(APPEND _errs "performance-unnecessary-value-param")
    # list(APPEND _errs "performance-move-const-arg")
    # list(APPEND _errs "performance-for-range-copy")
    # list(APPEND _errs "modernize-use-equals-default")
    # list(APPEND _errs "modernize-use-nullptr")
    list(JOIN _errs "," CLANG_TIDY_ERRORS)

    message(STATUS "Enabled errors:")
    foreach(_err ${_errs})
      message(STATUS "|-> ${_err}")
    endforeach()

    
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};-checks=${CLANG_TIDY_CHECKS};-header-filter='.*';-warnings-as-errors=${CLANG_TIDY_ERRORS}")
  endif()
endif()
