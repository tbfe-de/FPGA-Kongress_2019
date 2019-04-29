ALL_STEP_VARIANTS=\
	step0-1\
	step0-2\
	step0-3\
	step1-1\
	step1-2\
	step1-3\
	step2-1\
	step2-2\
	step2-3\
	step3-1\
	step3-2\
	step3-3\

# leave an EMPTY line above (or remove trailing `\`)

# chhose compiler here
  CC = g++
# CC = clang++

all: $(ALL_STEP_VARIANTS)
	@echo "All variants up-to-date"
step0-1: step0.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=1 $<
step0-2: step0.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=2 $<
step0-3: step0.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=3 $<
step1-1: step1.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=1 $<
step1-2: step1.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=2 $<
step1-3: step1.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=3 $<
step2-1: step2.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=1 $<
step2-2: step2.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=2 $<
step2-3: step2.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=3 $<
step3-1: step3.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=1 $<
step3-2: step3.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=2 $<
step3-3: step3.cpp
	$(CC) -o $@ -std=c++14 -DTESTCASE=3 $<
# -----------------------------------
clean:
	@rm -f $(ALL_STEP_VARIANTS)
realclean: clean
	@rm -f a.out core *.o
# -----------------------------------
.PHONY: all clean realclean
