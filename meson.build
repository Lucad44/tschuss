project(
    'tschuss',
    'c',
    default_options: ['c_std=c23'],
    version: '1.4.2',
    license: 'MIT'
)

datadir = get_option('datadir')
sysconfdir = get_option('sysconfdir')

src = [
    'src/main.c',
    'src/conf.c',
    'src/button.c'
]

if get_option('bash-completions')
  bashdir = datadir + '/bash-completion/completions'
  install_data('completions/wlogout.bash', install_dir: bashdir)
endif

if get_option('fish-completions')
  fishdir = datadir + '/fish/completions'
  install_data('completions/wlogout.fish', install_dir: fishdir)
endif

if get_option('zsh-completions')
  zshdir = datadir + '/zsh/site-functions'
  install_data('completions/_wlogout', install_dir: zshdir)
endif

project_dependencies = [
    dependency('gtk+-3.0')
]

install_data(['tschuss.conf', 'style.css'], install_dir: sysconfdir / 'tschuss')

executable(
    meson.project_name(),
    dependencies: project_dependencies,
    src,
    install: true
)