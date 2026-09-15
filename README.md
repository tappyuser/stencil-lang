# Stencil
Stencil is a parser that parses C code and generates the CST(Concrete Syntax Tree). It would also be able to generate an AST (Abstract Syntax Tree). 

## [Building](#Building)
## Project Structure

# Building
## Requirements
To build stencil, you need to have some requirements. 
```bash
git # or git bash if you are using Windows
make
clang >=22.1.8 or gcc >=16.2.1
```

To clone the project, you need the project
```bash
git clone https://github.com/tappyuser/stencil-lang.git
```

## Windows
To build the project, you need to be in the directory were you cloned the project.
```bash
cd stencil-lang
make lib 
make 
```
