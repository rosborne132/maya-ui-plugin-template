all: clean generate

clean:
	@echo "Cleaning up build..."
	rm -rf .qmake.stash
	rm -rf main.mak
	rm -rf build

generate:
	@echo "Generating files..."
	${DEVKIT_LOCATION}/devkit/bin/qmake main.pro

build-plugin:
	@echo "Building project..."
	make -f main.mak
