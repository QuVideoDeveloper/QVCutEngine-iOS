#ifndef _MAC_IPHONE_H_
#define _MAC_IPHONE_H_

#if defined(__IPHONE__)
#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <OpenGL/gl3.h>
#import <OpenGL/glext.h>
#import <AppKit/AppKit.h>
#import <CoreVideo/CVOpenGLTextureCache.h>
#elif TARGET_OS_IPHONE
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import <OpenGLES/EAGLDrawable.h>
#import <CoreVideo/CVOpenGLESTextureCache.h>
#import <UIKit/UIKit.h>
#endif

#endif
#endif // _MAC_IPHONE_H_
