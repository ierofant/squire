add_executable(read_ktsuk_ini EXCLUDE_FROM_ALL read_ktsuk_ini.cpp)
add_executable(write_ktsuk_ini EXCLUDE_FROM_ALL write_ktsuk_ini.cpp)

add_custom_target(ktsuk_examples DEPENDS 
				    read_ktsuk_ini
				    write_ktsuk_ini)
