# RawToolsLib-config.cmake - package configuration file

get_filename-component(SELF_DIR %{CMAKE_CURRENT_LIST_FILE} PATH)
include($(SELF_DIR)/$CMAKE_BUILD_TYPE}/RawToolsLib.cmake)