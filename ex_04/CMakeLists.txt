cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

fenix_project( TARGET ex_04 PROJECT EXAMPLE_04 )



###########################################################################################
#                                                                                         #
#                             Compilation include directories                             #
#                                                                                         #
###########################################################################################
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_GEN_DIR} )
include_directories( ${TRACING_SOURCE_DIR}/api )
include_directories( ${BASE_SOURCE_DIR}/api )
include_directories( ${OSW_SOURCE_DIR}/api )
include_directories( ${TOOLS_SOURCE_DIR}/api )
include_directories( ${RUNTIME_SOURCE_DIR}/api )



###########################################################################################
#                                                                                         #
#                                Linkage include directories                              #
#                                                                                         #
###########################################################################################
link_directories( ${RUNTIME_BINARY_DIR} )



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

find_files_by_ext( RECURSE FILES IDL_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_IDL} )
generate_xdls( XDL_FILES ${IDL_FILES} GENERATED_FILES PROJECT_GEN_IDL_FILES )

find_files_by_ext( RECURSE FILES DDL_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_DDL} )
generate_xdls( XDL_FILES ${DDL_FILES} GENERATED_FILES PROJECT_GEN_DDL_FILES )

find_files_by_ext( RECURSE FILES PROTO_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_PROTO} )
generate_gpbs( PROTO_FILES ${PROTO_FILES} GENERATED_FILES PROJECT_GEN_PROTO_FILES )

find_files_by_ext( RECURSE FILES PLANTUML_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_PLANTUML} )
generate_plantumls( PLANTUML_FILES ${PLANTUML_FILES} GENERATED_FILES PROJECT_GEN_PLANTUML_FILES )



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
   ${PROJECT_GEN_IDL_FILES}
   ${PROJECT_GEN_DDL_FILES}
   ${PROJECT_GEN_PROTO_FILES}
)

target_link_libraries( ${PROJECT_TARGET_NAME} ${RUNTIME_TARGET_NAME} )

install( TARGETS ${PROJECT_TARGET_NAME} DESTINATION bin )
install( FILES ${PROJECT_SOURCE_DIR}/${PROJECT_TARGET_NAME}.cfg DESTINATION etc OPTIONAL )
