
target_sources( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/ActionA.cpp
		${CMAKE_CURRENT_LIST_DIR}/SpslidarServerPlugin.cpp
		${CMAKE_CURRENT_LIST_DIR}/spslidardownloaddlg.cpp
		${CMAKE_CURRENT_LIST_DIR}/serverinfo.cpp
)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)
