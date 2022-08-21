project_test_sources = []
all_test_deps = []
all_test_libs = []

gtest_dep = gtest.get_variable('gtest_dep')
thread_dep = dependency('threads')
test_main = files('tests_main.cc')

test_deps = [
    gtest_dep,
    thread_dep
]

test_libs = []

# Add subdirs here
subdir('argparse')
subdir('utils')

# This executable contains all the tests
project_test_sources += test_main
all_test_deps += test_deps
all_test_libs += test_libs

all_tests = executable('all_tests',
    test_main,
    include_directories : inc,
    dependencies : all_test_deps,
    link_with : all_test_libs)
