.PHONY: build run clean

build:
	./build.sh

run:
	cd web && python3 -m http.server 8000

clean:
	rm -rf build && cd web && rm mandelbrot.js mandelbrot.wasm
