include(FetchContent)

FetchContent_Declare(
    stdexec
    GIT_REPOSITORY https://github.com/NVIDIA/stdexec.git
    GIT_TAG main
    
)
FetchContent_MakeAvailable(stdexec)
