# 获取所有直接子目录（绝对路径）
file(GLOB sub_dir
    LIST_DIRECTORIES true    # 仅保留目录
    "${CMAKE_CURRENT_LIST_DIR}/src/*"
)

foreach(test ${sub_dir})
    get_filename_component(test_name "${test}" NAME_WE)
    add_executable(${test_name} "${test}/${test_name}.cpp")

    target_include_directories(
        ${test_name}
        PUBLIC
        "${diff}"
    )
    target_link_libraries(
        ${test_name}
        GTest::GTest
        GTest::Main
    )
    target_compile_definitions(
        ${test_name} 
        PRIVATE
        TEST_DATA_PATH="${test}" # 传递数据的宏
    )

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
