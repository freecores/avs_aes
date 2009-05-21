#ifndef AVS_AES_H_
#define AVS_AES_H_


#define KEYWORDS    	8
#define AES_BASEADDR    0x40000 
#define KEY_ADDR        AES_BASEADDR+0x00
#define DATA_ADDR       AES_BASEADDR+0x08
#define RESULT_ADDR     AES_BASEADDR+0x10
#define AESCTRLWD       AES_BASEADDR+0x18 

typedef struct{
	volatile unsigned int* key;
	volatile unsigned int* payload;
	volatile unsigned int* result;
	volatile unsigned int* control;	
} avs_aes_handle;


void avs_aes_init(avs_aes_handle* context);
void avs_aes_setKey(avs_aes_handle* context, unsigned int* key);
void avs_aes_setPayload(avs_aes_handle* context, unsigned int* payload);
void avs_aes_setKeyvalid(avs_aes_handle* context);

void avs_aes_encrypt(avs_aes_handle* context);
void avs_aes_decrypt( avs_aes_handle* context);
int avs_aes_isBusy(avs_aes_handle* context);


#endif /*AVS_AES_H_*/
