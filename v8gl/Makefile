
ARCHES = ia32 x64 arm
MODES = release debug
ANDROID_ARCHES = android_ia32 android_arm

ARCH = $(basename $@)

BUILDS = $(foreach mode,$(MODES),$(addsuffix .$(mode),$(ARCHES)))
ANDROID_BUILDS = $(foreach mode,$(MODES), $(addsuffix .$(mode),$(ANDROID_ARCHES)))

AR=ar
RANLIB=ranlib
CC=g++

STATIC_INCLUDES = -I../external/libpng/include \
	-I../external/v8/include

STATIC_LIBRARIES =  lib/$(ARCH)/libpng.a \
	lib/$(ARCH)/libv8_base.a \
	lib/$(ARCH)/libv8_nosnapshot.a

SHARED_LIBRARIES = -lglut -lGLU -lGL -lpthread -lz -lm

LDFLAGS = $(STATIC_LIBRARIES) $(SHARED_LIBRARIES)


#
# V8GL game runtime
#

CFLAGS = -D__V8GL__ -D__WEBGL__

HEADER_FILES = src/v8gl.h \
	src/binding/gl.h \
	src/binding/webgl.h \
	src/binding/glu.h \
	src/binding/glut.h \
	src/lib/fs.h \
	src/lib/os.h \
	src/api/arraybuffer.h \
	src/api/navigator.h \
	src/api/script.h \
	src/api/text.h \
	src/api/texture.h
 

SRC_FILES = src/v8gl.cpp \
	src/binding/gl.cpp \
	src/binding/webgl.cpp \
	src/binding/glu.cpp \
	src/binding/glut.cpp \
	src/lib/fs.cpp \
	src/lib/os.cpp \
	src/api/arraybuffer.cpp \
	src/api/navigator.cpp \
	src/api/script.cpp \
	src/api/text.cpp \
	src/api/texture.cpp


LIB_ARCH = $(basename $(build))
V8GL_ROOT = $(shell pwd)
OUTDIR = ./out/$@

clean:
	rm -rf ./out/
	rm -rf ./lib/
	rm ./src/js/console.h
	rm ./src/js/interval.h
	rm ./src/js/timeout.h


builtin-js:
	cd src/ && xxd -i "js/console.js" "js/console.h"
	cd src/ && xxd -i "js/interval.js" "js/interval.h"
	cd src/ && xxd -i "js/timeout.js" "js/timeout.h"


$(BUILDS): builtin-js $(HEADER_FILES)
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/main.cpp $(SRC_FILES) -o $(OUTDIR)/v8gl $(LDFLAGS)
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/v8gl.cpp -c -o $(OUTDIR)/v8gl.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/binding/gl.cpp -c -o $(OUTDIR)/binding_gl.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/binding/webgl.cpp -c -o $(OUTDIR)/binding_webgl.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/binding/glu.cpp -c -o $(OUTDIR)/binding_glu.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/binding/glut.cpp -c -o $(OUTDIR)/binding_glut.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/lib/fs.cpp -c -o $(OUTDIR)/lib_fs.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/lib/os.cpp -c -o $(OUTDIR)/lib_os.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/api/arraybuffer.cpp -c -o $(OUTDIR)/api_arraybuffer.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/api/navigator.cpp -c -o $(OUTDIR)/api_navigator.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/api/script.cpp -c -o $(OUTDIR)/api_script.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/api/text.cpp -c -o $(OUTDIR)/api_text.o
	$(CC) -Wall $(CFLAGS) $(STATIC_INCLUDES) src/api/texture.cpp -c -o $(OUTDIR)/api_texture.o
	$(AR) rc $(OUTDIR)/libv8gl.a $(OUTDIR)/v8gl.o \
	$(OUTDIR)/binding_gl.o $(OUTDIR)/binding_webgl.o \
	$(OUTDIR)/binding_glu.o $(OUTDIR)/binding_glut.o \
	$(OUTDIR)/lib_fs.o $(OUTDIR)/lib_os.o \
	$(OUTDIR)/api_arraybuffer.o \
	$(OUTDIR)/api_navigator.o $(OUTDIR)/api_script.o \
	$(OUTDIR)/api_text.o $(OUTDIR)/api_texture.o
	$(RANLIB) $(OUTDIR)/libv8gl.a


$(ANDROID_ARCHES): $(addprefix $$@.,$(MODES))

$(ANDROID_BUILDS): builtin-js must-set-ANDROID_NDK_ROOT Makefile.android
	mkdir -p $(OUTDIR)
	@$(MAKE) -f Makefile.android $(subst .,,$(suffix $@)) \
		ARCH="$(basename $@)" \
		OUTDIR="$(OUTDIR)"

must-set-ANDROID_NDK_ROOT:
ifndef ANDROID_NDK_ROOT
	$(error ANDROID_NDK_ROOT must be set)
endif
 
