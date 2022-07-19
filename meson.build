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

inc = [include_directories('src/include')]
subdir('src/include')

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
