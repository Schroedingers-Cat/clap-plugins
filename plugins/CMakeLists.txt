find_package(Boost REQUIRED COMPONENTS serialization iostreams)

add_subdirectory(io)
add_subdirectory(gui)

add_library(
  clap-plugins SHARED
  clap-entry.cc
  parameters.cc
  parameters.hh
  parameter-interpolator.hh
  core-plugin.hh
  core-plugin.cc
  stream-helper.hh

  path-provider.hh
  path-provider.cc

  abstract-gui.hh
  remote-gui.hh
  remote-gui.cc

  plugs/dc-offset/dc-offset.hh
  plugs/dc-offset/dc-offset.cc
  plugs/gain/gain.hh
  plugs/gain/gain.cc
  plugs/transport/transport-info.hh
  plugs/transport/transport-info.cc)

target_link_libraries(clap-plugins clap-helpers clap-io Boost::serialization Boost::iostreams)
target_link_libraries(clap-plugins -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/linux-clap-plugins.version)
target_link_libraries(clap-plugins -Wl,-z,defs)
set_target_properties(clap-plugins PROPERTIES CXX_STANDARD 20 SUFFIX ".clap" PREFIX "")

install(TARGETS clap-plugins DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/clap")
install(DIRECTORY qml DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/clap")