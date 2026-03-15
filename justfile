build_dir := "build"
app_name := "app"
scene := "scenes/scene01.xml"

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
