build_dir := "build"
app_name := "app"

default: build

setup:
    CXX=clang++ CC=clang cmake -S . -B {{build_dir}}
    ln -sf {{build_dir}}/compile_commands.json .

build:
    cmake --build {{build_dir}}

run: build
    ./{{build_dir}}/src/{{app_name}}

test: build
    ctest --test-dir {{build_dir}} --output-on-failure

clean:
    rm -rf {{build_dir}} compile_commands.json
