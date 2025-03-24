cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

fenix_project( TARGET ex_03 PROJECT EXAMPLE_03 )



###########################################################################################
#                                                                                         #
#                             Compilation include directories                             #
#                                                                                         #
###########################################################################################
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_GEN_DIR} )



###########################################################################################
#                                                                                         #
#                                Linkage include directories                              #
#                                                                                         #
###########################################################################################



###########################################################################################
#                                                                                         #
#                                   Compile definitions                                   #
#                                                                                         #
###########################################################################################



###########################################################################################
#                                                                                         #
#                                      Code generation                                    #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES ADL_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_ADL} )
generate_xdls( XDL_FILES ${ADL_FILES} GENERATED_FILES PROJECT_GEN_ADL_FILES )



###########################################################################################
#                                                                                         #
#                                   Build source file list                                #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES PROJECT_SOURCE_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_CPP_SRC} )
msg_wrn( "PROJECT_SOURCE_FILES = " ${PROJECT_SOURCE_FILES} )



###########################################################################################
#                                                                                         #
#                                      Debug messages                                     #
#                                                                                         #
###########################################################################################
print_variables( )



add_executable(
   ${PROJECT_TARGET_NAME}
   ${PROJECT_SOURCE_FILES}
   ${PROJECT_GEN_ADL_FILES}
)

target_link_libraries( ${PROJECT_TARGET_NAME} dlt )
target_link_libraries( ${PROJECT_TARGET_NAME} ${TARGET_PREFIX}tracing )
target_link_libraries( ${PROJECT_TARGET_NAME} ${TARGET_PREFIX}tools )
target_link_libraries( ${PROJECT_TARGET_NAME} ${TARGET_PREFIX}runtime )

install( TARGETS ${PROJECT_TARGET_NAME} DESTINATION bin/carpc/ )

install(
      FILES ${PROJECT_SOURCE_DIR}/configuration.cfg
      DESTINATION etc/carpc/
      RENAME ${PROJECT_TARGET_NAME}.cfg
   )
