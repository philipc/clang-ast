Clang AST Printer

DESCRIPTION:

Use libclang to parse a C/C++ program and print the resulting AST.
This is probably only useful to people working on tools based
on libclang.

BUILDING:

You'll need a copy of clang.  I've only tested the SVN version of clang.

There are two methods of building.

1. Building within the clang build tree.

- Check out the clang-tools-extra repository within the clang tree.
- Link the clang-ast directory to tools/clang/tools/extra/clang-ast
- Link the clang-ast/test directory to tools/clang/tools/extra/test/clang-ast 
- Add this line to tools/clang/tools/extra/CMakeLists.txt:
	add_subdirectory(clang-ast)
- Build llvm as normal

2. Building standalone.

- Build and install libclang.
- Configure and build clang-ast by running:
	cmake -D CLANG_AST_STANDLONE=1 .
	make

RUNNING:

ast [-i] [-l] [-f <pattern>] -- <compiler options> <filename>

-i prints implicit nodes

-l prints the source location of nodes

-f <pattern> only prints nodes below declarations whose name
matches the pattern

Currently the compiler options need to specify include paths etc.
Compilation database support is planned to avoid the need for this.

EXAMPLES:

See the test cases for many examples of commands and output.
