## Building the project
1. Creating the executables follows standard `cmake` procedure:
```
    mkdir build
    cd build
    cmake ..
```

2. Compile the code:
```
    make
```

3. After that go to folder `../bin` and run executable (you also need to send
`.doa` file that describes nondeterministic finite automaton with ***1-symbol
transitions*** and ***only numbers contained in state names***. It would write
the result in output file):
```
    ./runProgram in.doa out.doa
```

4. To run `UnitTests` in `bin`:
```
    ./runUnitTests
```

5. To get `coverage-report` use:
```
    ./get
```