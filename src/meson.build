# Project dependencies
dep_cairo = dependency('cairo')
dep_x11 = dependency('X11')

# Project sources
sources = [
    'main.c',
]

executable(
    'wfc',
    sources: sources,
    dependencies: [dep_cairo, dep_x11],
    include_directories: inc,
    link_args: ['-lm'],
    install: true,
)
