# minimum cmake version supported
cmake_minimum_required (VERSION 2.6)

# application project
project (whenBlock)

# The sources to be used
file(GLOB SOURCE_FILES "*.cpp")

# Output
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")

# Define the executable to be generated
set(TOOL_NAME "whenBlock")
set(PROJ_NAME "tools")
add_executable(${TOOL_NAME} ${SOURCE_FILES})

# Add the project static libs at linking
target_link_libraries (${TOOL_NAME} wallet token ${BASE_LIBS})

# Testing
# Define paths to test folder and gold folder
set(TEST_EXE "${EXECUTABLE_OUTPUT_PATH}/${TOOL_NAME}")
set(TEST_PATH "${TEST_PATH}/${PROJ_NAME}/${TOOL_NAME}")
set(GOLD_PATH "${GOLD_PATH}/${PROJ_NAME}/${TOOL_NAME}")

# Additional target to make the README.md
build_readme(${CMAKE_CURRENT_SOURCE_DIR} ${TOOL_NAME})

# Function to run an individual test case
function(run_test testName)
     run_the_test(${TEST_PATH} ${GOLD_PATH} ${testName} ${TEST_EXE} ${ARGN})
endfunction(run_test)

# Function to Concatenate multiple files in a single output file
# Rename or move to root CMakeLists.txt if you cosider it handy
#
# Parameters :
# input_list - input files (list)
# output_file - output file
function(concatenate_files input_list output_file)
    file(WRITE ${OUT} "")
    foreach(FILENAME ${input_list})
        file(READ ${FILENAME} CONTENTS)
	file(APPEND ${output_file} "${CONTENTS}")
    endforeach()
endfunction(concatenate_files)

# We need to generate for test 01 the input files blocks.txt and dates.txt. How?

# NOTE FROM JAY: I PUT THESE FILES IN THE GOLD FOLDER AND CHANGE CWD TO GOLD TO RUN THE TEST

# Group them in a list
#set(INPUT_LIST "/path/to/blocks.txt" "/path/To/dates.txt")

# Once we have them we can concatenate both files using the function concatenate_files
# set(OUTPUT_TEST_FILE "/path/to/results.txt")
#add_custom_command(OUTPUT ${OUTPUT_TEST_FILE} COMMAND concatenate_files ${INPUT_LIST} ${OUTPUT_TEST_FILE})


# Enter one line for each individual test
run_test("whenBlock_README"                       "-th")
run_test("whenBlock_noparams"                     )
run_test("whenBlock_invalid_option_1"             "-x")
run_test("whenBlock_invalid_option_2"             "a")
run_test("whenBlock_invalid_option_3"             "0-0")
run_test("whenBlock_invalid_long_option_1"        "--none")
run_test("whenBlock_invalid_long_option_2"        "--alone" " 0" " --invalid")
run_test("whenBlock_invalid_block_1"              "0x0a")
run_test("whenBlock_invalid_block_2"              "1ppppppp")
run_test("whenBlock_out_of_range_block"           "40000000000000000000000000000")
run_test("whenBlock_mixed_options"                "-avlh")
run_test("whenBlock_mixed_block_and_date"         "2017-03-02" " 123123")
run_test("whenBlock_first_block"                  "0")
run_test("whenBlock_intermediate_block_1"         "1000000")
run_test("whenBlock_intermediate_block_2"         "2677160")
run_test("whenBlock_not_present_block"            "5000000")
run_test("whenBlock_block_with_leading_zeroes"    "000000011")
run_test("whenBlock_invalid_alone_syntax_1"       "-a")
run_test("whenBlock_invalid_alone_syntax_2"       "-a"      " 2015-03-02")
run_test("whenBlock_invalid_alone_syntax_3"       "-a"      " pppppp1")
run_test("whenBlock_invalid_alone_syntax_4"       "-a"      " 0pppppp")
run_test("whenBlock_invalid_long_alone_syntax_1"  "--alone")
run_test("whenBlock_invalid_long_alone_syntax_2"  "--alone" " 2015-03-02")
run_test("whenBlock_invalid_long_alone_syntax_3"  "--alone" " pppppp1")
run_test("whenBlock_invalid_long_alone_syntax_4"  "--alone" " 0pppppp")
run_test("whenBlock_invalid_list_syntax_1" "-l"   " -a")
run_test("whenBlock_invalid_list_syntax_2" "-l"   " 213123213")
run_test("whenBlock_invalid_list_syntax_3" "-l"   " 2015-03-02")
run_test("whenBlock_invalid_list_syntax_4" "-l"   " -a"      " 23123")
run_test("whenBlock_invalid_long_list_syntax_1"   "--list"   " -a")
run_test("whenBlock_invalid_long_list_syntax_2"   "--list"   " 213123213")
run_test("whenBlock_invalid_long_list_syntax_3"   "--list"   " -k" " 2015-03-02")
run_test("whenBlock_invalid_long_list_syntax_4"   "--list"   " 2015-03-02")
run_test("whenBlock_list_dates"                   "-l")
run_test("whenBlock_list_dates_long"              "--list")
run_test("whenBlock_invalid_verbose_syntax"       "-v")
run_test("whenBlock_verbose_valid_block"          "-v"        " 1000")
run_test("whenBlock_verbose_level_1"              "-v:1"      " 1000")
run_test("whenBlock_verbose_level_2"              "-v:j"      " 1000")
run_test("whenBlock_invalid_long_verbose_syntax"  "--verbose")
run_test("whenBlock_long_verbose_valid_block"     "--verbose" " 1000")
run_test("whenBlock_combined_options_1"           "-a"        " -v" " 10000")
run_test("whenBlock_combined_options_2"           "-a"        " --verbose" " 10000")
run_test("whenBlock_combined_options_3"           "--alone"   " --verbose" " 10000")
run_test("whenBlock_special_block_first"          "first")
run_test("whenBlock_special_block_iceage"         "iceage")
run_test("whenBlock_special_block_homestead"      "homestead")
run_test("whenBlock_special_block_daofund"        "daofund")
run_test("whenBlock_special_block_daohack"        "daohack")
run_test("whenBlock_special_block_daofork"        "daofork")
run_test("whenBlock_special_block_tangerine"      "tangerine")
run_test("whenBlock_special_block_spurious"       "spurious")
run_test("whenBlock_special_block_stateclear"     "stateclear")
run_test("whenBlock_special_block_not_found"      "idonotexist")
run_test("whenBlock_special_block_multi1"         "stateclear" " iceage" " 4001001")
run_test("whenBlock_special_block_multi2"         "stateclear" " iceage" " 4001001" " junk")
run_test("whenBlock_help"                         "-h")
run_test("whenBlock_long_help"                    "--help")
run_test("whenBlock_02"                           "--file:blocks.txt")
run_test("whenBlock_03"                           "--file:dates.txt")

# Installation steps
install(TARGETS ${TOOL_NAME} RUNTIME DESTINATION bin)
