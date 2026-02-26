let Module;

async function init() {
    Module = await createModule();
}

init();

async function render() {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    const width = canvas.width;
    const height = canvas.height;

    const ptr = Module._allocate_buffer(width, height);

    Module._generate_mandelbrot(
        width,
        height,
        -0.5,
        0.0,
        300.0,
        500
    );

    const imageData = ctx.createImageData(width, height);

    const wasmMemory = new Uint8ClampedArray(
        Module.HEAPU8.buffer,
        ptr,
        width * height * 4
    );

    imageData.data.set(wasmMemory);

    ctx.putImageData(imageData, 0, 0);
}

