PROJECT_NAME = Wave-Function-Collapse

# Setting compilers for meson
export CC=clang
export CXX=clang++

# PREFIX overrides the 'prefix' option of Meson's function project() on 'ninja install'.
PREFIX = ${HOME}/${PROJECT_NAME}

BUILD_RELEASE = build/release
BUILD_DEBUG   = build/debug
FILE_RELEASE  = ${BUILD_RELEASE}/build.ninja
FILE_DEBUG    = ${BUILD_DEBUG}/build.ninja

.PHONY:	help release debug clean_release clean_debug clean format

help:
	@echo '----------------------------------------------------------------'
	@echo 'Usage:'
	@echo '  make release       : create "bin-&-lib" of the release version'
	@echo '  make debug         : create "bin-&-lib" of the debug version '
	@echo ' '
	@echo '  make format        : format the project source files'
	@echo ' '
	@echo '  make clean_release : remove the "release" intermediate files'
	@echo '  make clean_debug   : remove the "debug"   intermediate files'
	@echo '  make clean_bin     : remove the file from the "bin" directory'
	@echo '  make clean         : make clean_debug and clean_release'
	@echo '----------------------------------------------------------------'

release: ${FILE_RELEASE} ${PREFIX}
	ninja -v clang-format install -C ${BUILD_RELEASE}

${FILE_RELEASE}:
	meson --buildtype=release --prefix=${PREFIX} ${BUILD_RELEASE}

clean_release:
	\rm -fr ${BUILD_RELEASE}

debug: ${FILE_DEBUG} ${PREFIX}
	ninja -v clang-format install -C ${BUILD_DEBUG}

${FILE_DEBUG}:
	meson --buildtype=debug --prefix=${PREFIX} ${BUILD_DEBUG}

clean_debug:
	\rm -fr ${BUILD_DEBUG}

clean_bin:
	\rm -fr bin

clean: clean_release clean_debug clean_bin

$(PREFIX):
	mkdir -p ${PREFIX}/bin

format:
	ninja -v clang-format -C ${BUILD_RELEASE}
