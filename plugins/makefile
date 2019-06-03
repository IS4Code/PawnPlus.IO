GPP = g++ -m32 -std=c++11 -Ilib -Isrc -fno-stack-protector
GCC = gcc -m32 -Ilib -Isrc -fno-stack-protector
LINK = $(GPP) -lstdc++
PP_OUTFILE = "./PawnPlus_IO.so"

COMPILE_FLAGS = -c -O3 -fPIC -w -DLINUX -pthread -fno-operator-names -ftemplate-depth=2048

PawnPlus_IO = -D PawnPlus_IO $(COMPILE_FLAGS)

all: PawnPlus_IO

clean:
	-rm -f *~ *.o *.so
  
static: GPP = g++ -m32 -std=c++11 -Ilib -Isrc -fno-stack-protector -static-libgcc -static-libstdc++
static: GCC = gcc -m32 -Ilib -Isrc -fno-stack-protector -static-libgcc -static-libstdc++
static: LINK = $(GPP)
static: all

PawnPlus_IO: clean
	$(GCC) $(PawnPlus_IO) ./lib/sdk/amx/*.c
	$(GPP) $(PawnPlus_IO) ./lib/sdk/*.cpp
	$(GCC) $(PawnPlus_IO) ./lib/subhook/*.c
	$(GPP) $(PawnPlus_IO) ./src/api/*.cpp
	$(GPP) $(PawnPlus_IO) ./src/utils/*.cpp
	$(GPP) $(PawnPlus_IO) ./src/objects/*.cpp
	$(GPP) $(PawnPlus_IO) ./src/modules/*.cpp
	$(GPP) $(PawnPlus_IO) ./src/natives/*.cpp
	$(GPP) $(PawnPlus_IO) ./src/*.cpp
	$(LINK) -fshort-wchar -pthread -shared -o $(PP_OUTFILE) *.o
