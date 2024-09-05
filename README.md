# TinyVM

TinyVM is a lightweight virtual machine designed to execute a set of basic arithmetic and logical operations. It reads binary files and processes them according to the instructions defined within the file. This project is written in C and provides a simple example of how a virtual machine can be implemented.

## Features

- **Arithmetic Operations**: Basic operations like addition, subtraction, multiplication, and division.
- **Logical Operations**: Includes comparison operations such as equal, less than, greater than, and logical operations like AND, OR, and NOT.
- **Graphics Integration**: Utilizes the `raylib` library to implement simple graphics functions (like window management, pixel drawing, and text rendering).

## Installation and Usage

### Compiling the Project

Ensure you have `gcc` and `raylib` installed on your system. To compile the project, run the following command in your terminal:

```bash
build.bat
```

Or manually execute the command:

```bash
gcc main.c -I. -L. -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe
```

### Running the Project

After compilation, you can run the executable `main.exe`. You can specify a binary file with instructions as an argument:

```bash
main.exe <your_binary_file>
```

If no binary file is provided, the program will prompt you to enter a file path.

## Dependencies

- [raylib](https://www.raylib.com/) - A simple and easy-to-use graphics library.

## Example

To run a simple example:

```bash
main.exe example.bin
```

## Contributing

Contributions are welcome! Feel free to submit issues or create Pull Requests.

## License

This project is released under the "No License" terms. You are free to use, copy, modify, and distribute this software for any purpose, with or without fee, and without any restrictions.

**No License**

To the extent possible under law, the author(s) disclaim all copyright and related or neighboring rights to this work. 

**You can use, copy, modify, and distribute the work, even for commercial purposes, without asking permission.**

Note: The raylib library and its associated files (e.g., `raylib.h`, `raylib-lib binary.7z`, etc.) are subject to their respective licenses as defined by the raylib project. Please make sure to comply with the terms of the raylib license when using these files.

For more information about the concept of "No License", please refer to [ChooseALicense.com](https://choosealicense.com/no-permission/).
