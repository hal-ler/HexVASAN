cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DLLVM_ENABLE_ASSERTIONS=ON \
-DLLVM_BUILD_TESTS=OFF \
-DLLVM_BUILD_EXAMPLES=OFF \
-DLLVM_INCLUDE_TESTS=OFF \
-DLLVM_INCLUDE_EXAMPLES=OFF \
-DLLVM_TARGETS_TO_BUILD="X86" \
-DCMAKE_C_FLAGS="-fstandalone-debug -fuse-ld=gold" \
-DCMAKE_CXX_FLAGS="-fstandalone-debug -fuse-ld=gold" \
 ../llvm
