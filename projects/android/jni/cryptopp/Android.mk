LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

MAIN_PATH := $(LOCAL_PATH)../../../../libs/cryptopp
SOURCE_PATH := ../../../../libs/cryptopp
INCLUDE_PATH := $(LOCAL_PATH)../../../../libs/cryptopp


# main shared library
include $(CLEAR_VARS)
LOCAL_MODULE    := cryptopp
LOCAL_SRC_FILES := $(SOURCE_PATH)/3way.cpp \
		   $(SOURCE_PATH)/adler32.cpp \
		   $(SOURCE_PATH)/algebra.cpp \
		   $(SOURCE_PATH)/algparam.cpp \
		   $(SOURCE_PATH)/arc4.cpp \
		   $(SOURCE_PATH)/asn.cpp \
		   $(SOURCE_PATH)/authenc.cpp \
		   $(SOURCE_PATH)/base32.cpp \
		   $(SOURCE_PATH)/base64.cpp \
		   $(SOURCE_PATH)/basecode.cpp \
		   $(SOURCE_PATH)/bench.cpp \
		   $(SOURCE_PATH)/bench2.cpp \
		   $(SOURCE_PATH)/bfinit.cpp \
		   $(SOURCE_PATH)/blowfish.cpp \
		   $(SOURCE_PATH)/blumshub.cpp \
		   $(SOURCE_PATH)/camellia.cpp \
		   $(SOURCE_PATH)/cast.cpp \
		   $(SOURCE_PATH)/casts.cpp \
		   $(SOURCE_PATH)/cbcmac.cpp \
		   $(SOURCE_PATH)/ccm.cpp \
		   $(SOURCE_PATH)/channels.cpp \
		   $(SOURCE_PATH)/cmac.cpp \
		   $(SOURCE_PATH)/cpu.cpp \
		   $(SOURCE_PATH)/crc.cpp \
		   $(SOURCE_PATH)/cryptlib.cpp \
		   $(SOURCE_PATH)/cryptlib_bds.cpp \
		   $(SOURCE_PATH)/datatest.cpp \
		   $(SOURCE_PATH)/default.cpp \
		   $(SOURCE_PATH)/des.cpp \
		   $(SOURCE_PATH)/dessp.cpp \
		   $(SOURCE_PATH)/dh.cpp \
 		   $(SOURCE_PATH)/dh2.cpp \
		   $(SOURCE_PATH)/dll.cpp \
		   $(SOURCE_PATH)/dlltest.cpp \
		   $(SOURCE_PATH)/dsa.cpp \
		   $(SOURCE_PATH)/eax.cpp \
		   $(SOURCE_PATH)/ec2n.cpp \
		   $(SOURCE_PATH)/eccrypto.cpp \
		   $(SOURCE_PATH)/ecp.cpp \
		   $(SOURCE_PATH)/elgamal.cpp \
		   $(SOURCE_PATH)/emsa2.cpp \
		   $(SOURCE_PATH)/eprecomp.cpp \
		   $(SOURCE_PATH)/esign.cpp \
		   $(SOURCE_PATH)/files.cpp \
		   $(SOURCE_PATH)/filters.cpp \
		   $(SOURCE_PATH)/fips140.cpp \
		   $(SOURCE_PATH)/fipsalgt.cpp \
		   $(SOURCE_PATH)/fipstest.cpp \
		   $(SOURCE_PATH)/gcm.cpp \
		   $(SOURCE_PATH)/gf256.cpp \
		   $(SOURCE_PATH)/gf2_32.cpp \
		   $(SOURCE_PATH)/gf2n.cpp \
		   $(SOURCE_PATH)/gfpcrypt.cpp \
		   $(SOURCE_PATH)/gost.cpp \
		   $(SOURCE_PATH)/gzip.cpp \
		   $(SOURCE_PATH)/hex.cpp \
		   $(SOURCE_PATH)/hmac.cpp \
		   $(SOURCE_PATH)/hrtimer.cpp \
		   $(SOURCE_PATH)/ida.cpp \
		   $(SOURCE_PATH)/idea.cpp \
		   $(SOURCE_PATH)/integer.cpp \
		   $(SOURCE_PATH)/iterhash.cpp \
		   $(SOURCE_PATH)/luc.cpp \
		   $(SOURCE_PATH)/mars.cpp \
		   $(SOURCE_PATH)/marss.cpp \
		   $(SOURCE_PATH)/md2.cpp \
		   $(SOURCE_PATH)/md4.cpp \
		   $(SOURCE_PATH)/md5.cpp \
		   $(SOURCE_PATH)/misc.cpp \
		   $(SOURCE_PATH)/modes.cpp \
		   $(SOURCE_PATH)/mqueue.cpp \
		   $(SOURCE_PATH)/mqv.cpp \
		   $(SOURCE_PATH)/nbtheory.cpp \
		   $(SOURCE_PATH)/network.cpp \
		   $(SOURCE_PATH)/oaep.cpp \
		   $(SOURCE_PATH)/osrng.cpp \
		   $(SOURCE_PATH)/panama.cpp \
		   $(SOURCE_PATH)/pch.cpp \
		   $(SOURCE_PATH)/pkcspad.cpp \
		   $(SOURCE_PATH)/polynomi.cpp \
		   $(SOURCE_PATH)/pssr.cpp \
		   $(SOURCE_PATH)/pubkey.cpp \
		   $(SOURCE_PATH)/queue.cpp \
		   $(SOURCE_PATH)/rabin.cpp \
		   $(SOURCE_PATH)/randpool.cpp \
		   $(SOURCE_PATH)/rc2.cpp \
		   $(SOURCE_PATH)/rc5.cpp \
		   $(SOURCE_PATH)/rc6.cpp \
		   $(SOURCE_PATH)/rdtables.cpp \
		   $(SOURCE_PATH)/regtest.cpp \
		   $(SOURCE_PATH)/rijndael.cpp \
		   $(SOURCE_PATH)/ripemd.cpp \
		   $(SOURCE_PATH)/rng.cpp \
		   $(SOURCE_PATH)/rsa.cpp \
		   $(SOURCE_PATH)/rw.cpp \
		   $(SOURCE_PATH)/safer.cpp \
		   $(SOURCE_PATH)/salsa.cpp \
		   $(SOURCE_PATH)/seal.cpp \
		   $(SOURCE_PATH)/seed.cpp \
		   $(SOURCE_PATH)/serpent.cpp \
		   $(SOURCE_PATH)/sha.cpp \
		   $(SOURCE_PATH)/shacal2.cpp \
		   $(SOURCE_PATH)/shark.cpp \
		   $(SOURCE_PATH)/sharkbox.cpp \
		   $(SOURCE_PATH)/simple.cpp \
		   $(SOURCE_PATH)/skipjack.cpp \
		   $(SOURCE_PATH)/socketft.cpp \
		   $(SOURCE_PATH)/sosemanuk.cpp \
		   $(SOURCE_PATH)/square.cpp \
		   $(SOURCE_PATH)/squaretb.cpp \
		   $(SOURCE_PATH)/strciphr.cpp \
		   $(SOURCE_PATH)/tea.cpp \
		   $(SOURCE_PATH)/test.cpp \
		   $(SOURCE_PATH)/tftables.cpp \
		   $(SOURCE_PATH)/tiger.cpp \
		   $(SOURCE_PATH)/tigertab.cpp \
		   $(SOURCE_PATH)/trdlocal.cpp \
		   $(SOURCE_PATH)/ttmac.cpp \
		   $(SOURCE_PATH)/twofish.cpp \
		   $(SOURCE_PATH)/validat1.cpp \
		   $(SOURCE_PATH)/validat2.cpp \
		   $(SOURCE_PATH)/validat3.cpp \
		   $(SOURCE_PATH)/vmac.cpp \
		   $(SOURCE_PATH)/wait.cpp \
		   $(SOURCE_PATH)/wake.cpp \
		   $(SOURCE_PATH)/whrlpool.cpp \
		   $(SOURCE_PATH)/winpipes.cpp \
		   $(SOURCE_PATH)/xtr.cpp \
		   $(SOURCE_PATH)/xtrcrypt.cpp \
		   $(SOURCE_PATH)/zdeflate.cpp \
		   $(SOURCE_PATH)/zinflate.cpp \
		   $(SOURCE_PATH)/zlib.cpp
 
include $(BUILD_STATIC_LIBRARY)