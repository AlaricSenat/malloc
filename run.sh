#!/bin/sh
export DYLD_LIBRARY_PATH=. 
export DYLD_INSERT_LIBRARIES="libft_malloc.so" 
export DYLD_FORCE_FLAT_NAMESPACE=1 
export MallocLogFile=./malloc.log 
export MallocStackLogging=1

export LD_PRELOAD=./libft_malloc.so
$@
