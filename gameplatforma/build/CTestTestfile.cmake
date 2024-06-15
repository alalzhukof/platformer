# CMake generated Testfile for 
# Source directory: /Users/alekseizhukov/Desktop/gameplatforma
# Build directory: /Users/alekseizhukov/Desktop/gameplatforma/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PlayerTest "/Users/alekseizhukov/Desktop/gameplatforma/build/PlayerTest")
set_tests_properties(PlayerTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/alekseizhukov/Desktop/gameplatforma/CMakeLists.txt;53;add_test;/Users/alekseizhukov/Desktop/gameplatforma/CMakeLists.txt;0;")
add_test(MenuTest "/Users/alekseizhukov/Desktop/gameplatforma/build/MenuTest")
set_tests_properties(MenuTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/alekseizhukov/Desktop/gameplatforma/CMakeLists.txt;54;add_test;/Users/alekseizhukov/Desktop/gameplatforma/CMakeLists.txt;0;")
subdirs("_deps/doctest-build")
