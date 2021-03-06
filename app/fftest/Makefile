
PRJ_RELROOT := ../..
include $(PRJ_RELROOT)/buildpath.mk

default_target: all

#-------------------------------------------------------------------
# Project
#-------------------------------------------------------------------
PRJ_NAME := fftest
PRJ_TYPE := exe
PRJ_INCS := ffmpeg
PRJ_LIBS := zlib
PRJ_OSLB := 

#-------------------------------------------------------------------
# Configure build
#-------------------------------------------------------------------
include $(PRJ_LIBROOT)/config.mk

ifeq ($(PROC),arm)
UNSUPPORTED := PROC=$(PROC) not supported
include $(PRJ_LIBROOT)/unsupported.mk
else

ifeq ($(BUILD)$(PROC),vsx64)
	UNSUPPORTED := PROC=$(PROC) + BUILD=$(BUILD) is not supported
	include $(PRJ_LIBROOT)/unsupported.mk
else

ifneq ($(BUILD),vs)
	UNSUPPORTED := BUILD=$(BUILD) is not supported
	include $(PRJ_LIBROOT)/unsupported.mk
else

ifeq ($(PLATFORM),windows)
	ifeq ($(BUILD),vs)
		PRJ_INCS := $(CFG_LIB2BLD)/dep/etc/ffmpeg/inc/windows/vs xlibs $(PRJ_INCS)
		PRJ_PLIB := ffa ffb ffc ffd x264 vpx openssl_a openssl_b
		ifeq ($(OS),win64)
			PRJ_LIBP := $(PRJ_LIBP) $(CFG_LIBROOT)/xlibs/x64
		else
			PRJ_LIBP := $(PRJ_LIBP) $(CFG_LIBROOT)/xlibs/x86
			PRJ_WINX := libgcc.a libmingwex.a
		endif
	else
		PRJ_INCS := $(CFG_LIB2BLD)/dep/etc/ffmpeg/inc/windows/gcc $(PRJ_INCS) zlib
		PRJ_LIBS := $(PRJ_LIBS) ffa ffb ffc ffd ffa ffb ffc ffd x264 vpx \
								openssl_a openssl_b openssl_a openssl_b zlib
	endif
else
	PRJ_INCS := $(CFG_LIB2BLD)/dep/etc/ffmpeg/inc/posix $(PRJ_INCS)
	PRJ_LIBS := $(PRJ_LIBS) ffa ffb ffc ffd ffa ffb ffc ffd x264 vpx \
							openssl_a openssl_b openssl_a openssl_b zlib
	PRJ_OSLB := $(PRJ_OSLB)
endif

#-------------------------------------------------------------------
# File locations
#-------------------------------------------------------------------
export LOC_TAG := def
include $(PRJ_LIBROOT)/build.mk

#-------------------------------------------------------------------
# Execute the build
#-------------------------------------------------------------------
include $(PRJ_LIBROOT)/go.mk

endif

endif

endif
