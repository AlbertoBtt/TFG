
target_sources( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/ActionA.h
		${CMAKE_CURRENT_LIST_DIR}/SpslidarPlugin.h
		${CMAKE_CURRENT_LIST_DIR}/serverinfo.h
		${CMAKE_CURRENT_LIST_DIR}/spslidardownloaddlg.h
		${CMAKE_CURRENT_LIST_DIR}/boundingboxDTO.h
		${CMAKE_CURRENT_LIST_DIR}/coord.h
		${CMAKE_CURRENT_LIST_DIR}/datasetdlg.h
		${CMAKE_CURRENT_LIST_DIR}/datasetdto.h
		${CMAKE_CURRENT_LIST_DIR}/workspacedlg.h
		${CMAKE_CURRENT_LIST_DIR}/workspacedto.h
		${CMAKE_CURRENT_LIST_DIR}/spslidaruploaddlg.h
		${CMAKE_CURRENT_LIST_DIR}/uploaddlg.h
)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)
