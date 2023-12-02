project(
    'tschuss',
    'c',
    default_options: ['c_std=c2x', 'warning_level=3'],
    version: '1.4.2',
    license: 'MIT'
)

sysconfdir = get_option('sysconfdir')

src = [
    'src/main.c',
    'src/conf.c',
    'src/buttons.c'
]

layershell = dependency('gtk-layer-shell-0', required: false)

project_dependencies = [
    dependency('gtk+-3.0', method: 'pkg-config'),
    dependency('libconfig'),
    layershell
]

add_project_arguments(
    [
        '-Wno-missing-braces',
        '-Wno-unused-parameter',
        '-Wno-unused-result',
        '-Wno-unused-variable',
        '-Wno-format',
        '-Ofast'
    ],
    language: 'c'
)

if layershell.found()
    add_project_arguments('-DLAYERSHELL=1', language : 'c')
endif

install_data(['tschuss.conf', 'style.css'], install_dir: sysconfdir / 'tschuss')

executable(
    meson.project_name(),
    src,
    dependencies : project_dependencies,
    install : true,
)