cmake_minimum_required(VERSION 3.10.0)

project (PhonemeExtractor)

add_subdirectory(Submodules)

# find the Qt5 package
find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(SourceCode)
add_subdirectory(SoundFileToDtfMagFile)
