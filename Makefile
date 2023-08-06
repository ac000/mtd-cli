TARGETS = mtd-cli hdrchk

.PHONY: all $(TARGETS)
all: $(TARGETS)

MAKE_OPTS = --no-print-directory

.PHONY: mtd-cli
mtd-cli:
	@echo "Building: mtd-cli"
	@$(MAKE) $(MAKE_OPTS) -C src/

.PHONY: hdrchk
hdrchk:
	@echo "Checking Headers"
	@$(MAKE) $(MAKE_OPTS) -C src/ hdrchk

.PHONY: clean
clean:
	@echo "Cleaning: mtdac"
	@$(MAKE) $(MAKE_OPTS) -C src/ clean
