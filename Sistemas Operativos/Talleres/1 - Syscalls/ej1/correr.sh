#!/bin/bash
make clean
make
strace -f ../hai64 ls &> salida_hai64_ls
strace -f ./copia_hai ls &> salida_copia_hai_ls