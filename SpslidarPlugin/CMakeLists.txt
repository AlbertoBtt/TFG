option( PLUGIN_STANDARD_SPSLIDAR "Install spslidar plugin" OFF )

if ( PLUGIN_STANDARD_SPSLIDAR )
	project( SpslidarPlugin )
	 
	AddPlugin( NAME ${PROJECT_NAME} )
		
	add_subdirectory( include )
	add_subdirectory( src )
	add_subdirectory( ui )
endif()
