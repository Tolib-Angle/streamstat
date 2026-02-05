# streamstat
streamstat is a C++23 command-line tool for streaming statistical processing of CSV files. It scans directories, filters input files, merges records by event timestamp, and computes the median incrementally. Output is written only when the median changes. The architecture is modular and extensible for new statistics and data sources.
