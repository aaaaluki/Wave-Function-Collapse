utilstest_sources = files(
    'numutilstest.cc',
    'stringutilstest.cc'
)

utilstest_deps = []

utilstest_libs = [
    utils_lib
]

utilstest = executable('utilstest',
    [utilstest_sources, test_main],
    include_directories : inc,
    dependencies : [utilstest_deps, test_deps],
    link_with : [utilstest_libs, test_libs])

test('utils test', utilstest,
    verbose : true)

project_test_sources += utilstest_sources
all_test_deps += utilstest_deps
all_test_libs += utilstest_libs
