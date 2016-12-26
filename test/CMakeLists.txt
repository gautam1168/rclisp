add_executable(runtests run_tests.c)
target_link_libraries(runtests cmocka)

add_executable(repltests repl_tests.c ../src/interpreter.c ../src/repl.c)
target_link_libraries(repltests cmocka)
