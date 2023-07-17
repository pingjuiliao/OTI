add_compiler_rt_component(oti)

if (OS_NAME MATCHES "Linux")
  set(OTI_SOURCES
    oti.cpp
    )
  set(OTI_HEADERS
    oti.h
  )
  include_directories(..)
  set(OTI_CFLAGS ${SANITIZER_COMMON_CFLAGS})
  append_rtti_flag(OFF OTI_CFLAGS)

  foreach(arch ${OTI_SUPPORTED_ARCH})
    add_compiler_rt_runtime(clang_rt.oti
      STATIC
      ARCHS ${arch}
      SOURCES ${OTI_SOURCES}
      $<TARGET_OBJECTS:RTInterception.${arch}>
      $<TARGET_OBJECTS:RTSanitizerCommon.${arch}>
      $<TARGET_OBJECTS:RTSanitizerCommonLibc.${arch}>
      ADDITIONAL_HEADERS ${OTI_HEADERS}
      CFLAGS ${OTI_CFLAGS}
      PARENT_TARGET oti)
    add_sanitizer_rt_symbols(clang_rt.oti
      ARCHS ${arch}
      )
    add_dependencies(oti
      clang_rt.oti-${arch}-symbols)
  endforeach()
endif()
