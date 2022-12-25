PROJECT_NAME = cpputils
DIR_PATH=$(shell realpath .)
DIR_NAME=$(shell basename ${DIR_PATH})

prepare:
	mkdir -p build
	cmake -S . -B build

build: prepare
	cd build; make

install: build
	cd build; make install

uninstall:
	cd build; make uninstall

clean:
	rm -rf build

tar:
	cd ..; tar cvfz ./${DIR_NAME}/${PROJECT_NAME}.tar.gz --exclude-from=${DIR_NAME}/.gitignore ${DIR_NAME}
