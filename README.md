# Stencil
Stencil is a parser that parses C code and generates the CST(Concrete Syntax Tree). It would also be able to generate an AST (Abstract Syntax Tree). 

## [Installation](#Installation)
## [Building](#Building)

# Installation
## Requirements
To build stencil, you need to have some requirements. 
```bash
git # or git bash if you are using Windows
make
clang >=22.1.8 or gcc >=16.2.1
```

## MacOS
```zsh 
sudo brew install make clang # or gcc
```

## Linux
On fedora
```bash
sudo dnf install make clang # or gcc
```


On Debian based distro
```bash
sudo apt install make clang # or gcc
```


On Arch based distro
```bash
sudo pacman -S make clang # or gcc
```

# Building
To clone the project
```bash
git clone https://github.com/tappyuser/stencil-lang.git
```

To build the project
```bash
cd stencil-lang
make -C lib clean && make -C lib
make clean
make build
```

To run the project, make sure you are in the stencil-lang directory
```bash
./bin/main
```

