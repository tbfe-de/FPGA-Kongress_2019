ALL_STEP_VARIANTS=\
	step0-c\
	step0-cpp-classic-typedef\
	step0-cpp11-type-alias\
	step1-c-struct\
	step1-cpp-struct\
	step2-cpp-classic\
	step2-cpp-modern\
	step3\
	step4\
	step5\

# leave an EMPTY line above (or remove trailing `\`)

# chhose compiler here
  CC = g++
# CC = clang++

all: $(ALL_STEP_VARIANTS)
	@echo "All variants up-to-date"
step0-c: step0.cpp
	$(CC) -o $@ -xc-std=c99 $<
step0-cpp-classic-typedef: step0.cpp
	$(CC) -o $@ -std=c++98 -DCLASSIC_TYPEDEF $<
step0-cpp11-type-alias: step0.cpp
	$(CC) -o $@ -std=c++98 $<
step1-c-struct: step1.cpp
	$(CC) -o $@ -xc-std=c99 $<
step1-cpp-struct: step1.cpp
	$(CC) -o $@ -std=c++98 $<
step2-cpp-classic: step2.cpp
	$(CC) -o $@ -std=c++98 $<
step2-cpp-modern: step2.cpp
	$(CC) -o $@ -std=c++11 $<
step3: step3.cpp
	$(CC) -o $@ -std=c++14 $<
step4: step4.cpp pxtn.h
	$(CC) -o $@ -std=c++14 $<
step5: step5.cpp pxtn.h
	$(CC) -o $@ -std=c++14 $<
# -----------------------------------
clean:
	@rm -f $(ALL_STEP_VARIANTS)
realclean: clean
	@rm -f a.out core *.o
# -----------------------------------
.PHONY: all clean realclean
