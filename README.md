# Mandelbrot em WebAssembly (C++ + JavaScript)

## Descrição do Projeto

Este projeto implementa a geração do **Conjunto de Mandelbrot** utilizando:

- **C++** para realizar o cálculo matemático pesado do fractal.
- **WebAssembly (WASM)** como ponte para executar o código C++ no navegador.
- **JavaScript + HTML (Canvas)** para renderizar o fractal em uma página web.

A motivação do projeto é demonstrar a integração entre linguagens de baixo nível (C++) e tecnologias web modernas, explorando desempenho e interoperabilidade via WebAssembly.

---

## Estrutura do Repositório

```text
.
├── build/                 # Arquivos gerados pelo CMake + Emscripten
│   ├── mandelbrot.js      # Wrapper JS gerado pelo Emscripten
│   └── mandelbrot.wasm    # Binário WebAssembly
├── web/                   # Frontend da aplicação
│   ├── index.html         # Página principal
│   ├── main.js            # Código JS que chama o WASM
│   ├── mandelbrot.js     # Arquivo copiado do build/
│   └── mandelbrot.wasm   # Arquivo copiado do build/
├── mandelbrot.cpp         # Implementação em C++ do fractal
├── CMakeLists.txt         # Configuração do build para WebAssembly
├── build.sh               # Script para compilar o projeto
├── README.md              # Este arquivo
└── LICENSE
```
---

##  Dependências, Compilação, Execução, Integração e Makefile

### Dependências
Para compilar e executar o projeto, é necessário ter instalado:
- Git
- CMake
- Python 3 (para rodar o servidor HTTP local)
- Emscripten SDK (emsdk)

#### Instalação do Emscripten (Linux)
Comandos para instalar o Emscripten:
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    ./emsdk install latest
    ./emsdk activate latest
    source ./emsdk_env.sh

O comando `source ./emsdk_env.sh` deve ser executado em todo novo terminal antes de compilar o projeto.

###  Como Compilar o Projeto (Gerar WebAssembly)
Na raiz do repositório:
    chmod +x build.sh
    ./build.sh

Após a compilação, os arquivos gerados estarão em:
- build/mandelbrot.js
- build/mandelbrot.wasm

Copie os arquivos para a pasta web/:
    cp build/mandelbrot.js web/
    cp build/mandelbrot.wasm web/

###  Como Executar o Projeto (Rodar no Navegador)
WebAssembly não funciona abrindo o HTML direto pelo arquivo, é necessário um servidor HTTP.

Entre na pasta web/:
    cd web

Inicie um servidor local com Python:
    python3 -m http.server 8000

Abra no navegador:
    http://localhost:8000

Clique no botão “Gerar Fractal” para renderizar o Conjunto de Mandelbrot.

###  Integração entre C++ e JavaScript (WASM)
O C++ implementa o cálculo do fractal de Mandelbrot e escreve os pixels em um buffer de memória linear. O código é compilado para WebAssembly utilizando Emscripten. O JavaScript chama as funções exportadas do C++ (`allocate_buffer` e `generate_mandelbrot`), acessa diretamente a memória linear do WASM por meio de `Module.HEAPU8`, converte o buffer em `ImageData` e renderiza o resultado no elemento `<canvas>` do HTML. Essa abordagem demonstra interoperabilidade real entre linguagens, utilizando compartilhamento de memória entre JavaScript e C++ via WebAssembly.
