# doc/reference

# Input: built_files_root, project_source_root, legacy_widgets_for_gtkmm_pcname, perl,
#        hg_ccg_basenames, extra_h_files, built_file_targets, install_datadir,
#        dist_cmd, python3
# Output: install_docdir, install_devhelpdir

tag_file_modules = [
  'mm-common-libstdc++',
  'sigc++-2.0',
  'glibmm-2.4',
]
doxygen_tagfiles = ''
docinstall_flags = []
foreach module : tag_file_modules
  depmod = dependency(module, required: false)
  if depmod.found()
    doxytagfile = depmod.get_pkgconfig_variable('doxytagfile')
    htmlrefpub = depmod.get_pkgconfig_variable('htmlrefpub', default: '')
    htmlrefdir = depmod.get_pkgconfig_variable('htmlrefdir', default: '')
    if htmlrefpub == ''
      htmlrefpub = htmlrefdir
    elif htmlrefdir == ''
      htmlrefdir = htmlrefpub
    endif
    doxygen_tagfiles += ' "' + doxytagfile + '=' + htmlrefpub + '"'
    if not htmlrefdir.endswith('/')
      htmlrefdir += '/'
    endif
    docinstall_flags += ['-l', doxytagfile.split('/')[-1] + '@' + htmlrefdir]
  endif
endforeach

book_name = legacy_widgets_for_gtkmm_pcname
book_title = meson.project_name() + ' Reference Manual'

# Configuration data for Doxyfile.
doc_conf_data = configuration_data()
doc_conf_data.set('configure_input',
  'doc/reference/Doxyfile. Generated from Doxyfile.in by meson.configure_file().')
doc_conf_data.set('PACKAGE_NAME', meson.project_name())
doc_conf_data.set('PACKAGE_VERSION', meson.project_version())
doc_conf_data.set('abs_top_builddir', built_files_root)
doc_conf_data.set('abs_top_srcdir', project_source_root)
doc_conf_data.set('LEGACY_WIDGETS_FOR_GTKMM_MODULE_NAME', book_name)
doc_conf_data.set('DOXYGEN_TAGFILES', doxygen_tagfiles)
doc_conf_data.set('PERL', perl.path())

configure_file(
  input: 'Doxyfile.in',
  output: '@BASENAME@',
  configuration: doc_conf_data,
)

# Installation directories relative to {prefix}.
install_docdir = install_datadir / 'doc' / book_name
install_reference_docdir = install_docdir / 'reference'
install_devhelpdir = install_datadir / 'devhelp' / 'books' / book_name

if not build_documentation
  # Documentation shall not be built or installed.
  # Return to the calling meson.build file.
  subdir_done()
endif

# Built input .h files to Doxygen.
built_h_files = []
foreach file : hg_ccg_basenames
  built_h_files += built_files_root / 'legacy_widgets_for_gtk' / 'legacy_widgets_for_gtkmm' / file + '.h'
endforeach

# Hand-coded input .h files to Doxygen.
src_h_files = []
foreach file : extra_h_files
  if file != 'wrap_init.h'
    src_h_files += project_source_root / 'legacy_widgets_for_gtk' / 'legacy_widgets_for_gtkmm' / file
  endif
endforeach
src_h_files += project_source_root / 'legacy_widgets_for_gtk' / 'legacy_widgets_for_gtkmm.h'

doctool_dir = project_source_root / 'untracked' / 'doc' # MMDOCTOOLDIR
doctool_dist_dir = 'untracked' / 'doc' # Relative to MESON_DIST_ROOT

if built_file_targets.length() > 0
  # .h files have been generated from .hg files (maintainer mode).
  tag_file = custom_target('html_and_tag',
    input: src_h_files,
    output: book_name + '.tag',
    command: [
      python3, doc_reference, 'doxygen',
      doctool_dir,
      '@OUTPUT@',
      built_h_files,
      '@INPUT@',
    ],
    build_by_default: build_documentation,
    depends: built_file_targets,
    install: true,
    install_dir: install_reference_docdir,
  )
else
  # All .h files are stored in the source tree (not maintainer mode).
  tag_file = custom_target('html_and_tag',
    input: src_h_files + built_h_files,
    output: book_name + '.tag',
    command: [
      python3, doc_reference, 'doxygen',
      doctool_dir,
      '@OUTPUT@',
      '@INPUT@',
    ],
    build_by_default: build_documentation,
    install: true,
    install_dir: install_reference_docdir,
  )
endif

devhelp_file = custom_target('devhelp',
  input: tag_file,
  output: book_name + '.devhelp2',
  command: [
    python3, doc_reference, 'devhelp',
    doctool_dir,
    '@INPUT@',
    '@OUTPUT@',
    book_name,
    book_title,
  ],
  build_by_default: build_documentation,
)

# Install Devhelp file and html files.
meson.add_install_script(
  python3.path(), doc_reference, 'install_doc',
  doctool_dir,
  devhelp_file.full_path(),
  install_devhelpdir,
  install_reference_docdir / 'html',
  docinstall_flags
)

if not meson.is_subproject()
  # Distribute built files and files copied by mm-common-prepare.
  # (add_dist_script() is not allowed in a subproject)
  meson.add_dist_script(
    python3.path(), dist_cmd,
    python3.path(), doc_reference, 'dist_doc',
    doctool_dir,
    doctool_dist_dir,
    meson.current_build_dir(),
    tag_file.full_path(),
    devhelp_file.full_path(),
  )
endif
