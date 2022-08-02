# Project dependencies
cairo_dep = dependency('cairo')
m_dep = cc.find_library('m', required : true)

project_deps += cairo_dep
project_deps += m_dep

# Project sources
main_source = files('main.c')
project_sources += main_source

subdir('argparse')
subdir('utils')
subdir('wfc')
