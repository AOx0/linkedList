default:
  just --list

init:
  cmake -S. -B cmake-build

build: init
  cmake --build cmake-build

build_release: init
  cmake --build cmake-build --config Release

test: build
  cd cmake-build && ctest --output-on-failure

run: build && exec

run_release: build_release && exec

exec:
    ./cmake-build/linkedList

clean:
  rm -rf cmake-build
