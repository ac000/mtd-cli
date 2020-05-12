APPNAME = mtd-cli

DEPDIR  := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

CC	= gcc
CFLAGS	= -Wall -Wextra -Wdeclaration-after-statement -Wvla -g -O2 -Wp,-D_FORTIFY_SOURCE=2 --param=ssp-buffer-size=4 -fPIC -fexceptions -I../../libmtdac/include
LDFLAGS = -L../../libmtdac/src -Wl,-z,now,-z,defs,-z,relro,--as-needed -fpie
LIBS	= -ljansson -lmtdac
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

sources     = $(wildcard *.c)
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
	@echo -e "  LNK\t$@"
	$(v)$(CC) $(LDFLAGS) $(ASAN) -o $@ $(objects) $(LIBS)

%.o: %.c
%.o: %.c $(DEPDIR)/%.d
	@echo -e "  CC\t$@"
	$(v)$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(sources))))

.PHONY: clean
clean:
	$(v)rm -f $(objects) $(APPNAME)
	$(v)rm -f $(DEPDIR)/*
	$(v)rmdir $(DEPDIR)
