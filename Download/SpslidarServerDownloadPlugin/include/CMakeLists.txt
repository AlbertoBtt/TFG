
target_sources( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/ActionA.h
		${CMAKE_CURRENT_LIST_DIR}/SpslidarServerPlugin.h
		${CMAKE_CURRENT_LIST_DIR}/spslidardownloaddlg.h
		${CMAKE_CURRENT_LIST_DIR}/serverinfo.h
)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)
