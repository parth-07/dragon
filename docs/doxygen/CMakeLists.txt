find_package(Doxygen REQUIRED)

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in)
set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg)

configure_file(${DOXYFILE_IN} ${DOXYFILE} @ONLY)

add_custom_target(docs
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT "Generate dragon doxygen documentation"
                  VERBATIM)