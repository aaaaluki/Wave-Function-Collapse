utils_sources = []
utils_sources += files('numutils.c')
utils_sources += files('printutils.c')

utils_lib = static_library('utils',
                            utils_sources,
                            include_directories : inc)

project_libs += utils_lib
project_sources += utils_sources
