find_path(MAVSDK_ROOT
		NAMES include/mavsdk/mavsdk.h
	PATHS ${MAVSDK_ROOT} "/usr/local" "/usr")

find_path(MAVSDK_INCLUDE_DIR mavsdk.h
	PATHS "${MAVSDK_ROOT}"
)

if (MAVSDK_INCLUDE_DIR AND MAVSDK_ROOT)
	set(MAVSDK_FOUND TRUE)
else ()
	set(MAVSDK_FOUND FALSE)
endif()
