#import "CSBlockStreamHandle.h"

#import "../../Crypto/aes.h"

@interface XADRARAESHandle:CSBlockStreamHandle
{
	CSHandle *parent;
	off_t startoffs;

	aes_decrypt_ctx aes;
	uint8_t iv[16],block[16],buffer[65536];
}

+(NSData *)keyForPassword:(NSString *)password salt:(NSData *)salt brokenHash:(BOOL)brokenhash;

-(instancetype)initWithHandle:(CSHandle *)handle key:(NSData *)keydata;
-(instancetype)initWithHandle:(CSHandle *)handle length:(off_t)length key:(NSData *)keydata;
-(instancetype)initWithHandle:(CSHandle *)handle RAR5Key:(NSData *)keydata IV:(NSData *)ivdata;
-(instancetype)initWithHandle:(CSHandle *)handle length:(off_t)length RAR5Key:(NSData *)keydata IV:(NSData *)ivdata;

-(void)resetBlockStream;
-(int)produceBlockAtOffset:(off_t)pos;

@end
