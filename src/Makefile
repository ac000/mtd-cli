APPNAME = mtd-cli

GIT_VERSION = \"$(shell git describe --always --long --dirty --all)\"

DEPDIR  := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(@F).Td

CC	= gcc
CFLAGS += -Wall -Wextra -Wdeclaration-after-statement -Wvla \
	  -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition \
	  -std=gnu11 -g -O2 -Wp,-D_FORTIFY_SOURCE=2 --param=ssp-buffer-size=4 \
	  -fno-common -fPIE -fexceptions -I../../libmtdac/include \
	  -DGIT_VERSION=${GIT_VERSION} -pipe
LDFLAGS += -L../../libmtdac/src -Wl,-z,now,-z,defs,-z,relro,--as-needed -pie
LIBS	 = -lmtdac
POSTCOMPILE = @mv -f $(DEPDIR)/$(@F).Td $(DEPDIR)/$(@F).d && touch $@

ifeq ($(CC),gcc)
        GCC_MAJOR  := $(shell gcc -dumpfullversion -dumpversion | cut -d . -f 1)
        GCC_MINOR  := $(shell gcc -dumpfullversion -dumpversion | cut -d . -f 2)
        GCC_SUB	   := $(shell gcc -dumpfullversion -dumpversion | cut -d . -f 3)
        GCC_VER_OK := $(shell test $(GCC_MAJOR) -ge 5 -a $(GCC_MINOR) -ge 1 \
			-a $(GCC_SUB) -ge 1 && echo 1)

        ifneq "$(GCC_VER_OK)" "1"
                # For GCC < 5.1.1
                CFLAGS += -Wno-missing-field-initializers
        endif
endif

sources = $(wildcard *.c)
objects = $(sources:.c=.o)

ifeq ($(ASAN),1)
        override ASAN = -fsanitize=address
endif

v = @
ifeq ($V,1)
	v =
endif

.PHONY: all
all: $(APPNAME)

$(APPNAME): $(objects)
	@echo "  LNK  $@"
	$(v)$(CC) $(LDFLAGS) $(ASAN) -o $@ $(objects) $(LIBS)

%.o: %.c
%.o: %.c $(DEPDIR)/%.o.d
	@echo "  CC   $@"
	$(v)$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

headers := $(wildcard *.h)
hdrobjs := $(headers:.h=.gch)

hdrchk: $(hdrobjs)
%.gch: %.h
%.gch: %.h $(DEPDIR)/%.gch.d
	@echo "  CC   $<"
	$(v)$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.o.d,$(basename $(sources))))
include $(wildcard $(patsubst %,$(DEPDIR)/%.gch.d,$(basename $(headers))))

.PHONY: clean
clean:
	$(v)rm -f *.o *.gch $(APPNAME)
	$(v)rm -f $(DEPDIR)/*
	$(v)rmdir $(DEPDIR)
