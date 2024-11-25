# Paths.
set(SRC_DIR ../source)

# Add sources for the main project
set(SOURCES
    ${SRC_DIR}/board.cpp
)
set(HEADERS
    ${SRC_DIR}/board.h
    ${SRC_DIR}/cell.h
)

# Create the main executable
add_executable(test ./main.cpp ${SOURCES})

# Include directories
target_include_directories(test PRIVATE
    ${SRC_DIR}
)