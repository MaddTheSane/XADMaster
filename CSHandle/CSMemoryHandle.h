#import "CSHandle.h"

#define CSMemoryHandle XADMemoryHandle

@interface CSMemoryHandle:CSHandle
{
	NSData *backingdata;
	off_t memorypos;
}

+(instancetype)memoryHandleForReadingData:(NSData *)data;
+(instancetype)memoryHandleForReadingBuffer:(const void *)buf length:(unsigned)len;
+(instancetype)memoryHandleForReadingMappedFile:(NSString *)filename;
+(instancetype)memoryHandleForWriting;

// Initializers
-(instancetype)initWithData:(NSData *)dataobj;
-(instancetype)initAsCopyOf:(CSMemoryHandle *)other;

// Public methods
-(NSData *)data;
-(NSMutableData *)mutableData;

// Implemented by this class
@property (NS_NONATOMIC_IOSONLY, readonly) off_t fileSize;
@property (NS_NONATOMIC_IOSONLY, readonly) off_t offsetInFile;
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL atEndOfFile;

-(void)seekToFileOffset:(off_t)offs;
-(void)seekToEndOfFile;
//-(void)pushBackByte:(int)byte;
-(int)readAtMost:(int)num toBuffer:(void *)buffer;
-(void)writeBytes:(int)num fromBuffer:(const void *)buffer;

-(NSData *)fileContents;
-(NSData *)remainingFileContents;
-(NSData *)readDataOfLength:(int)length;
-(NSData *)readDataOfLengthAtMost:(int)length;
-(NSData *)copyDataOfLength:(int)length;
-(NSData *)copyDataOfLengthAtMost:(int)length;

@end
