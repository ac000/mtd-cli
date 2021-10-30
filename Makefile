TARGETS = mtd-cli hdrchk

.PHONY: all $(TARGETS)
all: $(TARGETS)

MAKE_OPTS = --no-print-directory V=$V

.PHONY: mtd-cli
mtd-cli:
	@echo -e "Building: mtd-cli"
	@$(MAKE) $(MAKE_OPTS) -C src/

.PHONY: hdrchk
hdrchk:
	@echo -e "Checking Headers"
	@$(MAKE) $(MAKE_OPTS) -C src/ hdrchk

.PHONY: clean
clean:
	@echo -e "Cleaning: mtdac"
	@$(MAKE) $(MAKE_OPTS) -C src/ clean
