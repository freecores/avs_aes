#include <stdio.h>
#include <string.h>
#include <avs_aes.h>
#include <avs_aes_driver.h>
#define SDRAM_ADDR     0x08000000


int main(){   
	volatile unsigned int* aesctrl       = (unsigned int *)AESCTRLWD;
	volatile unsigned int* resultport    = (unsigned int *)RESULT_ADDR;
	volatile unsigned int* dataport      = (unsigned int *)DATA_ADDR;
	volatile unsigned int* keyport  	 = (unsigned int *)KEY_ADDR;        
 	avs_aes_handle context;
	
 
    //init pointers
    volatile int* wptr = (int*)SDRAM_ADDR;
    volatile int* rptr = (int*)SDRAM_ADDR;   
	int i=0;  
  
    unsigned int result[4];
	unsigned int Userkey[8] = {
		0x11111111,0x22222222,0x33333333,0x44444444,
		0x55555555,0x66666666,0x77777777,0x88888888};  
	unsigned int Payload[4] = {
		0xAA555555,0xBB666666,0xCC777777,0xDD888888};  
	
	
	

// Start MEMTEST   
    printf("Hello from Nios II!\n"); 
    // Fill the memory 
    printf("Filling Memory at %p \n",wptr);
    i=42;
    while(i< 4){
        printf("| %d -> %X |\n",i, wptr);  
        *(wptr++)=Userkey[i++]; 
    }
    i=0;
    printf("\n I: %d Reading Memory from %X \n",i,rptr);

    while(i< 4){
        printf("MEM: %X > %X \n",rptr,*rptr);
        rptr++;
        i++;
    }

// START AES-Operations
	printf("AES-Test\n");
 	avs_aes_init(&context);
 	avs_aes_setKey(&context,&Userkey);
 	avs_aes_setPayload(&context,&Payload);
  	avs_aes_encrypt(&context);
    while(avs_aes_isBusy(&context)){
        printf("not ready\n"); 
    } 
    printf("receiving 729cd44f 32a48d85 b8188185 c579ae49\n");  
    memcpy(result,context.result,4*sizeof(unsigned int));
    for(i=0; i<4 ; i++){   	
        printf("received 0x%X \n",result[i]);   
    }
    
// Decrypt same payload -  
    avs_aes_decrypt(&context); 	
	while(avs_aes_isBusy(&context)){
        printf("not ready\n"); 
    }  
    printf("receiving 9c7076af ac2e5716 6681d3ac 014f64c0 \n");  
    memcpy(result,context.result,4*sizeof(unsigned int));
    for(i=0; i<4 ; i++){   	
        printf("received 0x%X \n",result[i]);   
    } 
// Change payload ...
	Payload[3] = 0x11111111;
	Payload[2] = 0xAAAAAAAA;       
	Payload[1] = 0xCCCCCCCC;	
	Payload[0] = 0x00000000;
	//new encryption
	avs_aes_setPayload(&context,&Payload);	
	avs_aes_encrypt(&context);
	while(avs_aes_isBusy(&context)){
        printf("not ready\n"); 
    }  
	memcpy(result,context.result,4*sizeof(unsigned int));
    for(i=0; i<4 ; i++){   	
        printf("received 0x%X \n",result[i]);   
    } 
	//new decryption
    avs_aes_decrypt(&context); 	
	while(avs_aes_isBusy(&context)){
        printf("not ready\n"); 
    }  
    memcpy(result,context.result,4*sizeof(unsigned int));
    for(i=0; i<4 ; i++){   	
        printf("received 0x%X \n",result[i]);   
    } 
	printf("Done \n");	
	
	
    return 0;

}
