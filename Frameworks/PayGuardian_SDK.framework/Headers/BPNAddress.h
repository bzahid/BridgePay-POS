#import <Foundation/Foundation.h>


@interface BPNAddress : NSObject

@property (copy, nonatomic, nullable) NSString *street;

@property (copy, nonatomic, nullable) NSString *city;

@property (copy, nonatomic, nullable) NSString *zip;

@property (copy, nonatomic, nullable) NSString *country;

@property (copy, nonatomic, nullable) NSString *phone;

@property (copy, nonatomic, nullable) NSString *email;


@end
