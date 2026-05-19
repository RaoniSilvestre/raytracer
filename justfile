build_dir := "build"
app_name := "app_threaded"
scene := "normal-test"

default: build

setup:
    CXX=clang++ CC=clang cmake -S . -B {{build_dir}}
    ln -sf {{build_dir}}/compile_commands.json .

build:
    cmake --build {{build_dir}}

run *args=scene: build
    ./{{build_dir}}/src/{{app_name}} {{args}}

test: build
    ctest --test-dir {{build_dir}} --output-on-failure

clean:
    rm -rf {{build_dir}} compile_commands.json


@watch *args=scene:
    watchexec -d 250 -w src -e cpp,hpp --clear -- just run {{args}}

@watch-test:
    watchexec -d 250 -w src -w tests -e cpp,hpp --clear -- just test
