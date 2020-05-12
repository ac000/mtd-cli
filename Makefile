TARGETS = mtd-cli

.PHONY: all $(TARGETS)
all: $(TARGETS)

MAKE_OPTS = --no-print-directory V=$V

.PHONY: mtd-cli
mtd-cli:
	@echo -e "Building: mtd-cli"
	@$(MAKE) $(MAKE_OPTS) -C src/

.PHONY: clean
clean:
	@echo -e "Cleaning: mtdac"
	@$(MAKE) $(MAKE_OPTS) -C src/ clean
