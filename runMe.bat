cmake ./CMakeLists.txt
cmake --install .
cmake --build .
copy testfiles\students10000.txt .
copy testfiles\students10000.txt Debug\students10000.txt
Debug\ScoreCalculator.exe
