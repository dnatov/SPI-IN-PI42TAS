
if(NOT "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitinfo.txt" IS_NEWER_THAN "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Users/dnatov/AppData/Local/Programs/Git/cmd/git.exe"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/JeroenVandezande/LowLevelCInterfaces.git" "lowlevelcinterfaces-src"
    WORKING_DIRECTORY "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/JeroenVandezande/LowLevelCInterfaces.git'")
endif()

execute_process(
  COMMAND "C:/Users/dnatov/AppData/Local/Programs/Git/cmd/git.exe"  checkout v1.1.0 --
  WORKING_DIRECTORY "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v1.1.0'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Users/dnatov/AppData/Local/Programs/Git/cmd/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitinfo.txt"
    "C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/GSDSoftware/OtherRepos/SPI-IN-PI42TAS/build/_deps/lowlevelcinterfaces-subbuild/lowlevelcinterfaces-populate-prefix/src/lowlevelcinterfaces-populate-stamp/lowlevelcinterfaces-populate-gitclone-lastrun.txt'")
endif()

