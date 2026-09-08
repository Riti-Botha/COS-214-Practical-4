# TaskForge: Emergency Response Management

TaskForge demonstrates the Composite, Iterator, State and Decorator patterns in a
coherent emergency-response application.

## Team members

- Riti Botha
- Deon Steenkamp
- Connor Human

## Docker environment

Build the image and run the complete application:

```sh
docker build -t taskforge-env .
docker run --rm taskforge-env
```

For an interactive development shell with the repository mounted:

```sh
docker run -it --rm -v "$(pwd)":/workspace -w /workspace taskforge-env bash
```

## Compilation

The supplied Makefile builds with C++11 and produces an executable named
`taskforge`:

```sh
make
```


## Program execution

```sh
./taskforge
```

The program runs three connected scenarios covering recursive dispatch,
independent snapshot traversal with a runtime addition, stacked decorators, and
valid and rejected lifecycle transitions.


## Debugging and memory investigation

The Docker image includes GDB and Valgrind:

```sh
gdb ./taskforge
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

The `docs/` directory and repository root contain the exported UML diagrams and
the recorded GDB/Valgrind investigation evidence used in the submitted report.
