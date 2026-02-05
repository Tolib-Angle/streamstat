# streamstat

streamstat is a C++23 command-line tool for streaming statistical processing of CSV files.
It merges records by event timestamp and computes the median incrementally, writing output
only when the median changes.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

