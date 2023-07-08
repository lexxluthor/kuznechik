# Block Cipher Kuzhnechik 
## Implementation of "Kuznechik" aka "Kuznyechik" aka "Grasshopper" cipher in C++

#### General Informantion 
"KUZNECHIK" = KUZmin, NECHaev I Kompaniya (Kuzmin, Nechaev and Company)
"Kuznechik" [GOST3412-2015] is a symmetric block cipher based on a substitution–permutation network, though the key schedule employs a Feistel network. It has a block size of 128 bits and key length of 256 bits.

#### Documentation:

GOST (in English) https://datatracker.ietf.org/doc/html/rfc7801
GOST (in Russian) https://tc26.ru/standard/gost/GOST_R_3412-2015.pdf
#### Running code

Make sure you have CMake installed on your system. If not, download it from the official CMake website (https://cmake.org/download)
To compile and run this code use IDE that supports CMake or open terminal in the build directory and run
    cmake CMakeLists.txt 
    make 
    ./Kuznechik 
The program will execute the tests and display error messages if the tests fail. If all tests pass, "All tests have been successfully passed" will be displayed.
