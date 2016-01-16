#import "CSHandle.h"

#import <stdio.h>

#define CSFileHandle XADFileHandle

extern NSString *CSCannotOpenFileException;
extern NSString *CSFileErrorException;

@interface CSFileHandle:CSHandle
{
	FILE *fh;
	BOOL close;

	NSLock *multilock;
	CSFileHandle *parent;
	off_t pos;
}

+(instancetype)fileHandleForReadingAtPath:(NSString *)path;
+(instancetype)fileHandleForWritingAtPath:(NSString *)path;
+(instancetype)fileHandleForPath:(NSString *)path modes:(NSString *)modes;

// Initializers
-(instancetype)initWithFilePointer:(FILE *)file closeOnDealloc:(BOOL)closeondealloc name:(NSString *)descname;
-(instancetype)initAsCopyOf:(CSFileHandle *)other;
-(void)close;

// Public methods
-(FILE *)filePointer;

// Implemented by this class
@property (NS_NONATOMIC_IOSONLY, readonly) off_t fileSize;
@property (NS_NONATOMIC_IOSONLY, readonly) off_t offsetInFile;
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL atEndOfFile;

-(void)seekToFileOffset:(off_t)offs;
-(void)seekToEndOfFile;
-(void)pushBackByte:(int)byte;
-(int)readAtMost:(int)num toBuffer:(void *)buffer;
-(void)writeBytes:(int)num fromBuffer:(const void *)buffer;

// Internal methods
-(void)_raiseError;
-(void)_setMultiMode;

@end
