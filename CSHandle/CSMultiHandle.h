#import "CSHandle.h"

#define CSMultiHandle XADMultiHandle

extern NSString *CSSizeOfSegmentUnknownException;

@interface CSMultiHandle:CSHandle
{
	NSArray *handles;
	NSInteger currhandle;
}

+(instancetype)multiHandleWithHandleArray:(NSArray *)handlearray;
+(instancetype)multiHandleWithHandles:(CSHandle *)firsthandle,...;

// Initializers
-(instancetype)initWithHandles:(NSArray *)handlearray;
-(instancetype)initAsCopyOf:(CSMultiHandle *)other;

// Public methods
-(NSArray *)handles;
-(CSHandle *)currentHandle;

// Implemented by this class
-(off_t)fileSize;
-(off_t)offsetInFile;
-(BOOL)atEndOfFile;

-(void)seekToFileOffset:(off_t)offs;
-(void)seekToEndOfFile;
-(int)readAtMost:(int)num toBuffer:(void *)buffer;

// Internal methods
-(void)_raiseSizeUnknownForSegment:(NSInteger)i;

@end
