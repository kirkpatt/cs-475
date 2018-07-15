# Numsizes I'll use:
# 2^10  1024
# 2^11  2048
# 2^12  4096
# 2^13  8192
# 2^14  16384
# 2^15  32768
# 2^16  65536
# 2^17  131072
# 2^18  262144
# 2^19  524288
# 2^20  1048576
# 2^21  2097152
# 2^22  4194304
# 2^23  8388608
# Because not using powers of 2 mucks it all up.
# Same for local size, powers of 2 are needed.
# 2^0   1
# 2^1   2
# 2^2   4
# 2^3   8
# 2^4   16
# 2^5   32
# 2^6   64
# 2^7   128
# 2^8   256
# 2^9   512
# 2^10  1024

# local size 32
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=1024 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=2048 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=4096 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=8192 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=16384 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=32768 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=65536 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=131072 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=262144 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=524288 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=1048576 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=2097152 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=4194304 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third
g++ -o third third.cpp -DLOCAL_SIZE=32 -DNUM_ELEMENTS=8388608 /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp > /dev/null
./third

