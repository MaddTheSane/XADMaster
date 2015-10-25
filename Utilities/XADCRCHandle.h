#import "CSStreamHandle.h"
#import "Checksums.h"
#import "Progress.h"
#import "CRC.h"

@interface XADCRCHandle:CSStreamHandle
{
	CSHandle *parent;
	uint32_t crc,initcrc,compcrc;
	const uint32_t *table;
}

+(instancetype)IEEECRC32HandleWithHandle:(CSHandle *)handle
correctCRC:(uint32_t)correctcrc conditioned:(BOOL)conditioned;
+(instancetype)IEEECRC32HandleWithHandle:(CSHandle *)handle length:(off_t)length
correctCRC:(uint32_t)correctcrc conditioned:(BOOL)conditioned;
+(instancetype)IBMCRC16HandleWithHandle:(CSHandle *)handle length:(off_t)length
correctCRC:(uint32_t)correctcrc conditioned:(BOOL)conditioned;
+(instancetype)CCITTCRC16HandleWithHandle:(CSHandle *)handle length:(off_t)length
correctCRC:(uint32_t)correctcrc conditioned:(BOOL)conditioned;

-(instancetype)initWithHandle:(CSHandle *)handle length:(off_t)length initialCRC:(uint32_t)initialcrc
correctCRC:(uint32_t)correctcrc CRCTable:(const uint32_t *)crctable;

-(void)resetStream;
-(int)streamAtMost:(int)num toBuffer:(void *)buffer;

@property (readonly) BOOL hasChecksum;
-(BOOL)isChecksumCorrect;

@end


