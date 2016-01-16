#import "CSStreamHandle.h"

#ifndef __MACTYPES__
#define Byte zlibByte
#include <zlib.h>
#undef Byte
#else
#include <zlib.h>
#endif

#define CSZlibHandle XADZlibHandle

extern NSString *CSZlibException;

@interface CSZlibHandle:CSStreamHandle
{
	CSHandle *parent;
	off_t startoffs;
	z_stream zs;
	BOOL inited,seekback,endstreamateof;

	uint8_t inbuffer[0x4000];
}

+(instancetype)zlibHandleWithHandle:(CSHandle *)handle;
+(instancetype)zlibHandleWithHandle:(CSHandle *)handle length:(off_t)length;
+(instancetype)deflateHandleWithHandle:(CSHandle *)handle;
+(instancetype)deflateHandleWithHandle:(CSHandle *)handle length:(off_t)length;

// Intializers
-(instancetype)initWithHandle:(CSHandle *)handle length:(off_t)length header:(BOOL)header name:(NSString *)descname;
-(instancetype)initAsCopyOf:(CSZlibHandle *)other;

// Public methods
-(void)setSeekBackAtEOF:(BOOL)seekateof;
-(void)setEndStreamAtInputEOF:(BOOL)endateof;

// Implemented by this class
-(void)resetStream;
-(int)streamAtMost:(int)num toBuffer:(void *)buffer;

// Internal methods
-(void)_raiseZlib;

@end
