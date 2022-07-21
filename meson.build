# =======
# Project
# =======
project(
    'Wave Function Collapse', ['c', 'cpp'],
    default_options: ['c_std=c11', 'cpp_std=c++11'],
    version: 'v0.1'
)

# Variables tracking sources and libraries
library_path = []
project_sources = []
project_header_files = []
project_test_sources = []

inc = [include_directories('include')]
subdir('include')

# This triggers the builds of sources
project_deps = []
project_libs = []
subdir('src')

project_bin = executable('wfc',
  main_source,
  include_directories : inc,
  dependencies : project_deps,
  link_with : project_libs,
  install: true)

summary({'bindir': get_option('bindir'),
        'libdir': get_option('libdir'),
        'datadir': get_option('datadir'),
        }, section: 'Directories')

# Make test if specified
gtest = subproject('gtest')
if get_option('enable-tests')
  subdir('tests')
endif

run_target('format',
  command : [
    'clang-format',
    '-i',
    '-style=file',
    project_sources,
    project_header_files,
    project_test_sources,
  ]
)

run_target('tidy',
  command : [
    'clang-tidy',
    '--format-style=file',
    project_sources,
    project_header_files,
    project_test_sources,
  ]
)
