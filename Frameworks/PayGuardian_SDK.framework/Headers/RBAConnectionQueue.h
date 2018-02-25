#import <Foundation/Foundation.h>

@interface RBAConnectionQueue : NSObject

- (void)suspend;
- (void)resume;

- (void)run:(void (^)(void))block;
- (void)run:(void (^)(void))block afterBlockProcessed:(void (^)(void))afterProcessed;
- (void)run:(void (^)(void))block
processingDelay:(NSTimeInterval)processingDelay
afterBlockProcessed:(void (^)(void))afterProcessed;

@end
