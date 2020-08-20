export BUILD_DIR = build
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_CHECK_DIR)
	@rm -rf $(DOCS_DIR)

.PHONY: build
build:
	mkdir -p build && cd ./build && cmake .. -D TEST_MODE=FALSE && make

.PHONY: run
run:
	cd build && ./TEST_PROJECT

.PHONY: test
test:
	mkdir -p build && cd ./build && cmake .. -D TEST_MODE=TRUE  && make && ./TEST
