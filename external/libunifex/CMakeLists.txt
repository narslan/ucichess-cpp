include(FetchContent)

FetchContent_Declare(
    libunifex
    GIT_REPOSITORY https://github.com/facebookexperimental/libunifex.git
    GIT_TAG ef9db15be6464c4d207d625b809da477aed2ff74
    
)
FetchContent_MakeAvailable(libunifex)
