include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY git@github.com:KIWI-FORK/fmt.git
  GIT_TAG 11.1.4
)

FetchContent_MakeAvailable(fmt)