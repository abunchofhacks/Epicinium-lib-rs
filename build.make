build: | $(OUT_DIR)/bin/variant
	cp --recursive --update --preserve ./epicinium $(OUT_DIR)/
	cd $(OUT_DIR)/epicinium && $(MAKE) libepicinium
.PHONY: build
