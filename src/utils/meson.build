utils_sources = files(
    'numutils.c',
    'printutils.c',
    'stringutils.c'
)

utils_lib = static_library('utils',
                            utils_sources,
                            include_directories : inc)

project_sources += utils_sources
project_libs += utils_lib
