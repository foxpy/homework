add_library(CmdOpts
	cmdopts_parse.c
	cmdopts_free.c
	cmdopts_num_posopts.c
	cmdopts_get_posopt.c
	cmdopts_exists.c
	cmdopts_get_opt.c
)
target_include_directories(CmdOpts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
