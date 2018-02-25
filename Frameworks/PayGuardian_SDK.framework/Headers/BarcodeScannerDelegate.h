#import <Foundation/Foundation.h>

@protocol BarcodeScannerDelegate <NSObject>
- (void) onBarcodeScanned:(NSString *) data
                symbology:(NSString *) symbology;
@end
