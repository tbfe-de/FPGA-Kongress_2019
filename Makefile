TO_READ=\
	down_to_earth_cplusplus-toread\
	the_xilinx_tcl_store-toread.html\

# ^^^^^^ KEEP EMPTY LINE ABOVE (or remove last backslash)

DOTDOT_ZIP=\
	../FPGA-Kongress_2019.zip
DOTDOT_TGZ=\
	../FPGA-Kongress_2019.tgz

all: $(TO_READ)
	@echo "all printable input updated."
down_to_earth_cplusplus-toread.html: down_to_earth_cplusplus.html
	ex $(@:-toread.html=.html) +'f $@' +'%s/^--\n\n//' +'%s/\n\n--$$//' +wq!
the_xilinx_tcl_store-toread.html: the_xilinx_tcl_store.html
	ex $(@:-toread.html=.html) +'f $@' +'%s/^--\n\n//' +'%s/\n\n--$$//' +wq!

$(DOTDOT_ZIP): $(TO_READ)
	rm -f $@
	zip -r $@ *
$(DOTDOT_TGZ): $(TO_READ)
	rm -f $@
	tar cvzf $@ *

