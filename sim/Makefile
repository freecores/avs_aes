VCOM    = /usr/local/bin/vcom 
VCOMOPS = -explicit -check_synthesis -2002 -quiet 
#MAKEFLAGS = --silent
HDL_DIR = ../hdl/


##
# aes_ecb files
##
AES_ECB_SRC_DIR = $(HDL_DIR)aes_ecb/
AES_ECB_SRC =$(AES_ECB_SRC_DIR)aes_ecb_pkg.vhd \
		 $(AES_ECB_SRC_DIR)mux2.vhd \
	 	 $(AES_ECB_SRC_DIR)mux3.vhd \
 		 $(AES_ECB_SRC_DIR)memory_word.vhd \
		 $(AES_ECB_SRC_DIR)addroundkey.vhd \
		 $(AES_ECB_SRC_DIR)aes_fsm_encrypt.vhd \
		 $(AES_ECB_SRC_DIR)aes_fsm_decrypt.vhd \
		 $(AES_ECB_SRC_DIR)keyexpansionV2.vhd \
		 $(AES_ECB_SRC_DIR)mixcol.vhd \
		 $(AES_ECB_SRC_DIR)mixcol_fwd.vhd \
		 $(AES_ECB_SRC_DIR)mixcol_inv.vhd \
		 $(AES_ECB_SRC_DIR)sbox.vhd \
		 $(AES_ECB_SRC_DIR)sboxM4k.vhd \
		 $(AES_ECB_SRC_DIR)shiftrow.vhd \
		 $(AES_ECB_SRC_DIR)shiftrow_fwd.vhd \
		 $(AES_ECB_SRC_DIR)shiftrow_inv.vhd \
		 $(AES_ECB_SRC_DIR)aes_core.vhd \
		 $(AES_ECB_SRC_DIR)avs_aes.vhd \
		 $(AES_ECB_SRC_DIR)avs_aes_tb.vhd 

#######################################
all: simaes

clean:
	rm -rf .deps
	rm -rf *_lib

.deps: 
	mkdir .deps > /dev/null 2>&1

aes_ecb_lib: 
	vlib aes_ecb_lib

libs: aes_ecb_lib

aes_ecb: .deps aes_ecb_lib .deps/aes_ecb
.deps/aes_ecb: $(AES_ECB_SRC)  
	@echo --
	@echo building AES_ECB
	@echo --
	$(VCOM) $(VCOMOPS) -work aes_ecb_lib  $^
	touch .deps/aes_ecb

simaes: aes_ecb
	vsim -title "AVS_AES" -do ecb.do -lib aes_ecb_lib avs_aes_tb
