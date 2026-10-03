cmake_minimum_required(VERSION 3.20)
project(godzilla_damm_recomp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(XBOXRECOMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../repos/Repos/xboxrecomp"
    CACHE PATH "Path to xboxrecomp")
add_subdirectory("${XBOXRECOMP_DIR}" "${CMAKE_BINARY_DIR}/xboxrecomp")

set(RECOMP_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/game/recomp/gen"
    CACHE PATH "Directory containing generated recomp C sources")
file(GLOB RECOMP_GEN_SOURCES CONFIGURE_DEPENDS
    "${RECOMP_GEN_DIR}/*.c")

add_executable(godzilla_damm
    src/game/main.c
    src/game/recomp_manual.c
    src/game/recomp_vtable_generated.c
    ${RECOMP_GEN_SOURCES}
)

target_link_libraries(godzilla_damm PRIVATE xboxrecomp d3d11 dxgi dxguid xinput winmm dbghelp)
target_include_directories(godzilla_damm PRIVATE
    "${RECOMP_GEN_DIR}"
    "${XBOXRECOMP_DIR}/templates/runtime"
    "${XBOXRECOMP_DIR}/include"
)
target_compile_definitions(godzilla_damm PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _CRT_SECURE_NO_WARNINGS
)

if(MSVC)
    target_compile_options(godzilla_damm PRIVATE /bigobj)
    # MSVC's optimizing backend can terminate without a diagnostic while
    # processing the large machine-generated translation units.  Keep the
    # handwritten runtime optimized, but compile generated guest code without
    # optimizer transforms; this does not alter the translated guest behavior.
    set_source_files_properties(${RECOMP_GEN_SOURCES} PROPERTIES COMPILE_FLAGS "/w /Od")
    target_link_options(godzilla_damm PRIVATE /STACK:16777216 /DEBUG /MAP)
endif()

set_target_properties(godzilla_damm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
