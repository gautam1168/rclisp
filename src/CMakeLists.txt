#Compile hashtest
add_executable(hashtest hashtest.c hashmap.c)
add_executable(NFAtest NFAtest.c NFA.c)
add_executable(NFAexpr NFAexpr.c NFA.c)
add_executable(NFAbranching NFAbranching.c NFA.c)
add_executable(NFAzeromore NFAzeromore.c NFA.c)
add_executable(NFAonemore NFAonemore.c NFA.c)
add_executable(compileFSM compileFSM.c NFA.c)
