cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

fenix_project( TARGET ex_04 PROJECT EXAMPLE_04 )



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
target_link_libraries( ${PROJECT_TARGET_NAME} tracing )
target_link_libraries( ${PROJECT_TARGET_NAME} tools )
target_link_libraries( ${PROJECT_TARGET_NAME} runtime )

install( TARGETS ${PROJECT_TARGET_NAME} DESTINATION bin )
install( FILES ${PROJECT_SOURCE_DIR}/${PROJECT_TARGET_NAME}.cfg DESTINATION etc OPTIONAL )
