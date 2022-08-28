add_library(Util
	emalloc.c
	erealloc.c
	reopen_binary.c
	gcd.c
	lcm.c
)
target_include_directories(Util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
