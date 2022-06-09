find_library(libserialport-lib serialport NAMES serialport libserialport REQUIRED)
find_path(libserialport-incl NAMES libserialport.h REQUIRED)

add_library(libserialport INTERFACE IMPORTED GLOBAL)

target_include_directories(libserialport INTERFACE ${libserialport-incl})
target_link_libraries(libserialport INTERFACE ${libserialport-lib})

add_library(libserialport::libserialport ALIAS libserialport)