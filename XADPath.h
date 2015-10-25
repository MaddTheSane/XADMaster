#import "XADString.h"

#define XADUnixPathSeparator "/"
#define XADWindowsPathSeparator "\\"
#define XADEitherPathSeparator "/\\"
#define XADNoPathSeparator ""

@interface XADPath:NSObject <XADString,NSCopying>
{
	XADPath *parent;

	NSArray *cachedcanonicalcomponents;
	NSString *cachedencoding;
}

+(instancetype)emptyPath;
+(instancetype)pathWithString:(NSString *)string;
+(instancetype)pathWithStringComponents:(NSArray *)components;
+(instancetype)separatedPathWithString:(NSString *)string;
+(instancetype)decodedPathWithData:(NSData *)bytedata encodingName:(NSString *)encoding separators:(const char *)separators;
+(instancetype)analyzedPathWithData:(NSData *)bytedata source:(XADStringSource *)stringsource
separators:(const char *)pathseparators;

-(instancetype)init;
-(instancetype)initWithParent:(XADPath *)parentpath;
-(instancetype)initWithPath:(XADPath *)path parent:(XADPath *)parentpath;

-(BOOL)isAbsolute;
-(BOOL)isEmpty;
-(BOOL)isEqual:(id)other;
-(BOOL)isCanonicallyEqual:(id)other;
-(BOOL)isCanonicallyEqual:(id)other encodingName:(NSString *)encoding;
-(BOOL)hasPrefix:(XADPath *)other;
-(BOOL)hasCanonicalPrefix:(XADPath *)other;
-(BOOL)hasCanonicalPrefix:(XADPath *)other encodingName:(NSString *)encoding;

-(int)depth; // Note: Does not take . or .. paths into account.
-(int)depthWithEncodingName:(NSString *)encoding;
-(NSArray *)pathComponents;
-(NSArray *)pathComponentsWithEncodingName:(NSString *)encoding;
-(NSArray *)canonicalPathComponents;
-(NSArray *)canonicalPathComponentsWithEncodingName:(NSString *)encoding;
-(void)_addPathComponentsToArray:(NSMutableArray *)components encodingName:(NSString *)encoding;

-(NSString *)lastPathComponent;
-(NSString *)lastPathComponentWithEncodingName:(NSString *)encoding;
-(NSString *)firstPathComponent;
-(NSString *)firstPathComponentWithEncodingName:(NSString *)encoding;
-(NSString *)firstCanonicalPathComponent;
-(NSString *)firstCanonicalPathComponentWithEncodingName:(NSString *)encoding;

-(XADPath *)pathByDeletingLastPathComponent;
-(XADPath *)pathByDeletingLastPathComponentWithEncodingName:(NSString *)encoding;
-(XADPath *)pathByDeletingFirstPathComponent;
-(XADPath *)pathByDeletingFirstPathComponentWithEncodingName:(NSString *)encoding;

-(XADPath *)pathByAppendingXADStringComponent:(XADString *)component;
-(XADPath *)pathByAppendingPath:(XADPath *)path;
-(XADPath *)_copyWithParent:(XADPath *)newparent;

// These are safe for filesystem use, and adapted to the current platform.
-(NSString *)sanitizedPathString;
-(NSString *)sanitizedPathStringWithEncodingName:(NSString *)encoding;

// XADString interface.
// NOTE: These are not guaranteed to be safe for usage as filesystem paths,
// only for display!
-(BOOL)canDecodeWithEncodingName:(NSString *)encoding;
-(NSString *)string;
-(NSString *)stringWithEncodingName:(NSString *)encoding;
-(NSData *)data;
-(void)_appendPathToData:(NSMutableData *)data;

-(BOOL)encodingIsKnown;
-(NSString *)encodingName;
-(float)confidence;

-(XADStringSource *)source;

#ifdef __APPLE__
-(BOOL)canDecodeWithEncoding:(NSStringEncoding)encoding;
-(NSString *)stringWithEncoding:(NSStringEncoding)encoding;
-(NSString *)sanitizedPathStringWithEncoding:(NSStringEncoding)encoding;
-(NSStringEncoding)encoding;
#endif

// Other interfaces.
-(NSUInteger)hash;
-(id)copyWithZone:(NSZone *)zone;

// Deprecated.
-(XADPath *)safePath; // Deprecated. Use sanitizedPathString: instead.

// Subclass methods.
-(BOOL)_isPartAbsolute;
-(BOOL)_isPartEmpty;
-(int)_depthOfPartWithEncodingName:(NSString *)encoding;
-(void)_addPathComponentsOfPartToArray:(NSMutableArray *)array encodingName:(NSString *)encoding;
-(NSString *)_lastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(NSString *)_firstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingLastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingFirstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(BOOL)_canDecodePartWithEncodingName:(NSString *)encoding;
-(void)_appendPathForPartToData:(NSMutableData *)data;
-(XADStringSource *)_sourceForPart;

@end


@interface XADStringPath:XADPath
{
	NSString *string;
}

-(instancetype)initWithComponentString:(NSString *)pathstring;
-(instancetype)initWithComponentString:(NSString *)pathstring parent:(XADPath *)parentpath;
-(instancetype)initWithPath:(XADStringPath *)path parent:(XADPath *)parentpath;

-(BOOL)_isPartAbsolute;
-(BOOL)_isPartEmpty;
-(int)_depthOfPartWithEncodingName:(NSString *)encoding;
-(void)_addPathComponentsOfPartToArray:(NSMutableArray *)array encodingName:(NSString *)encoding;
-(NSString *)_lastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(NSString *)_firstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingLastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingFirstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(BOOL)_canDecodePartWithEncodingName:(NSString *)encoding;
-(void)_appendPathForPartToData:(NSMutableData *)data;
-(XADStringSource *)_sourceForPart;

-(BOOL)isEqual:(id)other;
-(NSUInteger)hash;

@end

@interface XADRawPath:XADPath
{
	NSData *data;
	XADStringSource *source;
	const char *separators;
}

-(instancetype)initWithData:(NSData *)bytedata source:(XADStringSource *)stringsource
separators:(const char *)pathseparators;
-(instancetype)initWithData:(NSData *)bytedata source:(XADStringSource *)stringsource
separators:(const char *)pathseparators parent:(XADPath *)parentpath;
-(instancetype)initWithPath:(XADRawPath *)path parent:(XADPath *)parentpath;

-(BOOL)_isPartAbsolute;
-(BOOL)_isPartEmpty;
-(int)_depthOfPartWithEncodingName:(NSString *)encoding;
-(void)_addPathComponentsOfPartToArray:(NSMutableArray *)array encodingName:(NSString *)encoding;
-(NSString *)_lastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(NSString *)_firstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingLastPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(XADPath *)_pathByDeletingFirstPathComponentOfPartWithEncodingName:(NSString *)encoding;
-(BOOL)_canDecodePartWithEncodingName:(NSString *)encoding;
-(void)_appendPathForPartToData:(NSMutableData *)data;
-(XADStringSource *)_sourceForPart;

@end

