.PHONY: clean cmake build test

all: cmake build

clean:
	@rm -rf build

cmake:
	@mkdir -p build
	@cd build; cmake ..

build: cmake
	@cd build; $(MAKE) -s

test: build
	@echo
	@./build/tests/test_runner ${CK_RUN_SUITE}

scanleak: build
	@echo
	@CK_FORK=no valgrind --leak-check=full ./build/tests/test_runner ${CK_RUN_SUITE}
