argparsetest_sources = files(
    'argparsetest.cc'
)

argparsetest_deps = []

argparsetest_libs = [
    argparse_lib
]

argparsetest = executable('argparsetest',
    [argparsetest_sources, test_main],
    include_directories : inc,
    dependencies : [argparsetest_deps, test_deps],
    link_with : [argparsetest_libs, test_libs])

test('argparse test', argparsetest,
    verbose : true)

project_test_sources += argparsetest_sources
all_test_deps += argparsetest_deps
all_test_libs += argparsetest_libs
