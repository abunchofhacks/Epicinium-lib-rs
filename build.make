build: | $(OUT_DIR)/.guard
	cp --recursive --update --preserve ./epicinium $(OUT_DIR)/
	cd $(OUT_DIR)/epicinium && $(MAKE) libepicinium
.PHONY: build
