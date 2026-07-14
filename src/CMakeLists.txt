add_library(nixreg
	bitbuffer.cpp
	NixieDigitMap.cpp
)

target_include_directories(nixreg PUBLIC ${PROJECT_SOURCE_DIR}/include)
