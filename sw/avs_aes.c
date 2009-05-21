#include <avs_aes.h>
#include <string.h>

void avs_aes_init(avs_aes_handle* context){
	context->key	= (unsigned int*) KEY_ADDR;
	context->payload= (unsigned int*) DATA_ADDR;
	context->result	= (unsigned int*) RESULT_ADDR;
	context->control  	= (unsigned int*) AESCTRLWD;
	*(context->control) = 0x00000000;
}

void avs_aes_setKey(avs_aes_handle* context, unsigned int* key){
	int i=0;
	unsigned int* target_ptr = (unsigned int* )context->key;
	// Invalidate old key;
	*(context->control) &= (~0x00000080);
	for(i=0; i<KEYWORDS; i++){
		*(target_ptr++) = *(key++);
	}
	// validate key;
	*(context->control) |= 0x00000080;
}

void avs_aes_setPayload(avs_aes_handle* context, unsigned int* payload){
	int i=0;
	unsigned int* target_ptr = (unsigned int* )context->payload;
	for(i=0; i<4; i++){
		*(target_ptr++) = *(payload++);
	}	
}


void avs_aes_setKeyvalid(avs_aes_handle* context){
	*(context->control) |= 0x00000080;
}

void avs_aes_encrypt(avs_aes_handle* context){
	*(context->control) |= 0x00000001;
}

void avs_aes_decrypt(avs_aes_handle* context){
	*(context->control) |= 0x00000002;
}

int avs_aes_isBusy(avs_aes_handle* context){
	unsigned int mycontrol = *(context->control);	
	return mycontrol & 0x03; 
}
