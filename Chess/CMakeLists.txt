cmake_minimum_required (VERSION 3.15)

project (Chess)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Chess "" include/Piece.h  include/Board.h src/Board.cpp include/Pieces/Rook.h src/Pieces/Rook.cpp include/Pieces/Knight.h src/Pieces/Knight.cpp include/Pieces/Bishop.h src/Pieces/Bishop.cpp include/Pieces/Queen.h src/Pieces/Queen.cpp include/Pieces/King.h src/Pieces/King.cpp include/Pieces/Pawn.h src/Pieces/Pawn.cpp "include/ChessExceptions.h" "include/PriorityQueue.h" "src/PriorityQueue.cpp" "include/MoveEvaluator.h" "src/MoveEvaluator.cpp" "include/Move.h" "src/Move.cpp"  "include/ThreadPool.h" "src/ThreadPool.cpp")


add_subdirectory (include)
add_subdirectory (src)



