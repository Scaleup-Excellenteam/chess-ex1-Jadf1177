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

add_executable (Chess
        ""
        include/Piece.h
        include/Board.h
        include/ChessUnit.h
        include/Pieces/Rook.h
        include/Pieces/Knight.h
        include/Pieces/Bishop.h
        include/Pieces/Queen.h
        include/Pieces/King.h
        include/Pieces/Pawn.h
        include/ChessExceptions.h
        include/PriorityQueue.h
        include/MoveEvaluator.h
        include/Move.h
        include/ThreadPool.h
        src/Board.cpp
        src/ChessUnit.cpp
        src/Pieces/Rook.cpp
        src/Pieces/Knight.cpp
        src/Pieces/Bishop.cpp
        src/Pieces/Queen.cpp
        src/Pieces/King.cpp
        src/Pieces/Pawn.cpp
        src/PriorityQueue.cpp
        src/MoveEvaluator.cpp
        src/Move.cpp
        src/ThreadPool.cpp
        src/Chess.cpp
        src/main.cpp
)


add_subdirectory (include)
add_subdirectory (src)



