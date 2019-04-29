ALL_STEP_VARIANTS=\
	step0\
	step1\
	step2\
	step3a\

# leave an EMPTY line above (or remove trailing `\`)

# chhose compiler here
  CC = g++
# CC = clang++

all: $(ALL_STEP_VARIANTS)
	@echo "All variants up-to-date"
.cpp:
	$(CC) -o $@ -std=c++14 $<
# -----------------------------------
clean:
	@rm -f $(ALL_STEP_VARIANTS)
realclean: clean
	@rm -f a.out core *.o
# -----------------------------------
.PHONY: all clean realclean
