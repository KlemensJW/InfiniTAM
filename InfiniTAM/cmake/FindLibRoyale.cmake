find_path(LibRoyale_ROOT royale_license.txt 
	PATHS ${LibRoyale_ROOT} "/home/parallels/Desktop/Bachelorarbeit/libroyale-4.24.0.1201-LINUX-arm-64Bit/" "/usr/local")

find_library(LibRoyale_LIBRARY
	NAMES libroyale.so
	PATHS "${LibRoyale_ROOT}/bin" {CMAKE_LIB_PATH}
)

find_path(LibRoyale_INCLUDE_DIR royale.hpp 
	PATHS "${LibRoyale_ROOT}/include"
)

if (LibRoyale_LIBRARY AND LibRoyale_INCLUDE_DIR AND LibRoyale_ROOT)
	set(LibRoyale_FOUND TRUE)
else ()
	set(LibRoyale_FOUND FALSE)
endif()