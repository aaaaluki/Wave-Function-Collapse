# Project dependencies
project_deps += meson.get_compiler('c').find_library('m', required : true)
project_deps += dependency('cairo')

# Project sources
main_source = files('main.c')
project_sources += main_source

subdir('utils')
