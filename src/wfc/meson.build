wfc_sources = files(
    'samples.c'
)

wfc_deps = [
    cairo_dep
]

wfc_lib = library('wfc',
                  wfc_sources,
                  include_directories : inc,
                  dependencies : wfc_deps)

project_sources += wfc_sources
project_libs += wfc_lib
