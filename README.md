# Mandelbrot em WebAssembly (C++ + JavaScript)

## Descrição do Projeto

Este projeto implementa a geração do **Conjunto de Mandelbrot** utilizando:

- **C++** para realizar o cálculo matemático pesado do fractal.
- **WebAssembly (WASM)** como ponte para executar o código C++ no navegador.
- **JavaScript + HTML (Canvas)** para renderizar o fractal em uma página web.

A motivação do projeto é demonstrar a integração entre **C++ e JavaScript** por meio de WebAssembly, explorando desempenho e interoperabilidade entre linguagens com modelos de execução distintos.

###  Integração entre C++ e JavaScript (WASM)
O C++ implementa o cálculo do fractal de Mandelbrot e escreve os pixels em um buffer de memória linear. O código é compilado para WebAssembly utilizando Emscripten. O JavaScript chama as funções exportadas do C++ (`allocate_buffer` e `generate_mandelbrot`), acessa diretamente a memória linear do WASM por meio de `Module.HEAPU8`, converte o buffer em `ImageData` e renderiza o resultado no elemento `<canvas>` do HTML. Essa abordagem demonstra interoperabilidade real entre linguagens, utilizando compartilhamento de memória entre JavaScript e C++ via WebAssembly.

---

## Estrutura do Repositório

```text
.
├── build/                 # Arquivos gerados pelo CMake + Emscripten
│   ├── mandelbrot.js      # Wrapper JS gerado pelo Emscripten - será movido para /web
│   └── mandelbrot.wasm    # Binário WebAssembly - será movido para /web
├── web/                   # Frontend da aplicação
│   ├── index.html         # Página principal
│   ├── main.js            # Código JS que chama o WASM
│   ├── mandelbrot.js      # Arquivo gerado após o 'make build'
│   └── mandelbrot.wasm    # Arquivo gerado após o 'make build'
├── mandelbrot.cpp         # Implementação em C++ do fractal
├── CMakeLists.txt         # Configuração do build para WebAssembly
├── build.sh               # Script de compilação (Emscripten + CMake) - é utilizado somente pelo 'make build'
├── Makefile               # Atalhos para build e execução (run) e clean do projeto
├── README.md              # Este arquivo
├── LICENSE                # MIT
└── Documentação.pdf       # Documentação da implementação
```
---

#  COMO COMPILAR E EXECUTAR

## Dependências
Para compilar e executar o projeto, é necessário ter instalado:
- Git
- CMake
- Python 3 (para rodar o servidor HTTP local)
- Emscripten SDK (emsdk)

#### Instalação do Emscripten (Linux)
Comandos para instalar o Emscripten: <br>
```
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    ./emsdk install latest
    ./emsdk activate latest
    source ./emsdk_env.sh
```
Para que não tenha que se rodar o comando `source ./emsdk_env.sh` em todo novo terminal antes de compilar o projeto, pode-se executar o seguinte comando (sim, inteiro) no terminal para que o Emscripten seja devidamente adicionado ao PATH: <br>
```
if ! grep -q "Configuração Emscripten" ~/.bashrc; then
    echo '
# Configuração Emscripten
export EMSDK=~/emsdk
export EMSDK_NODE=~/emsdk/node/22.16.0_64bit/bin/node
export PATH=$EMSDK:$EMSDK/upstream/emscripten:$EMSDK/node/22.16.0_64bit/bin:$PATH' >> ~/.bashrc
    echo "Configuração adicionada ao ~/.bashrc"
else
    echo "Configuração já existe no ~/.bashrc"
fi
```

##  Como Compilar o Projeto (Gerar WebAssembly)
Na raiz do repositório:
```
    chmod +x build.sh
    make build
```
Esse comando realiza as seguintes etapas:

- Compila o código **C++** para **WebAssembly (WASM)** utilizando o **Emscripten**
- Gera os arquivos **`mandelbrot.wasm`** e **`mandelbrot.js`** na pasta `build/`
- Copia automaticamente os arquivos **`mandelbrot.wasm`** e **`mandelbrot.js`** para a pasta **`web/`**

##  Como Executar o Projeto (Rodar no Navegador)
O projeto também fornece um atalho para iniciar o servidor local:

Digite o comando na raiz do repositório:
```
    make run
```

Depois, abra no navegador:
    http://localhost:8000

Clique no botão “Gerar Fractal” para renderizar o Conjunto de Mandelbrot.

Iniciar um servidor HTTP local é necessário pois WebAssembly não funciona corretamente abrindo o HTML direto pelo arquivo (file://).

##  Clean
Ao estar na raiz do repositório, se for rodado o comando `make clean`, a pasta `/build`, juntamente com os arquivos `mandelbrot.js` e `mandelbrot.wasm` (ambos encontrados na pasta /web) serão removidos.

