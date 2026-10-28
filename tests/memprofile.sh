#!/bin/bash

set -euo pipefail

rm -rf build_ref build_memopt && mkdir build_ref build_memopt
cmake -GNinja -S . -B build_ref \
    -DOQS_MINIMAL_BUILD="SIG_mqom_mqom3_cat5_gf16_short_ct;SIG_snova_SNOVA_V_K" \
    -DOQS_MEMOPT_BUILD="OFF"
ninja -C build_ref
cmake -GNinja -S . -B build_memopt \
    -DOQS_MINIMAL_BUILD="SIG_mqom_mqom3_cat5_gf16_short_ct;SIG_snova_SNOVA_V_K" \
    -DOQS_MEMOPT_BUILD="ON"
ninja -C build_memopt
valgrind --version  # valgrind-3.27.1
valgrind --tool=massif \
    --stacks=yes \
    --time-unit=B \
    --massif-out-file="./build_ref/test_sig_SNOVA_V_K" \
    ./build_ref/tests/test_sig SNOVA_V_K 0 0 0
valgrind --tool=massif \
    --stacks=yes \
    --time-unit=B \
    --massif-out-file="./build_memopt/test_sig_SNOVA_V_K" \
    ./build_memopt/tests/test_sig SNOVA_V_K 0 0 0
valgrind --tool=massif \
    --stacks=yes \
    --time-unit=B \
    --massif-out-file="./build_ref/test_sig_mqom3_cat5_gf16_short_ct" \
    ./build_ref/tests/test_sig mqom3_cat5_gf16_short_ct 0 0 0
valgrind --tool=massif \
    --stacks=yes \
    --time-unit=B \
    --massif-out-file="./build_memopt/test_sig_mqom3_cat5_gf16_short_ct" \
    ./build_memopt/tests/test_sig mqom3_cat5_gf16_short_ct 0 0 0

echo "========== MQOM CAT5 GF16 Short CT MEMOPT ==========" >> results.txt
ms_print build_memopt/test_sig_mqom3_cat5_gf16_short_ct >> results.txt
echo "========== MQOM CAT5 GF16 Short CT REF    ==========" >> results.txt
ms_print build_ref/test_sig_mqom3_cat5_gf16_short_ct >> results.txt
echo "========== SNOVA V K MEMOPT               ==========" >> results.txt
ms_print build_memopt/test_sig_SNOVA_V_K >> results.txt
echo "========== SNOVA V K REF                  ==========" >> results.txt
ms_print build_ref/test_sig_SNOVA_V_K >> results.txt

