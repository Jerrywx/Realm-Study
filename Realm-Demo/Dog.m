//
//  Dog.m
//  Realm-Demo
//
//  Created by wxiao on 16/1/8.
//  Copyright © 2016年 wxiao. All rights reserved.
//

#import "Dog.h"

@implementation Dog

// Specify default values for properties

//+ (NSDictionary *)defaultPropertyValues
//{
//    return @{};
//}

// Specify properties to ignore (Realm won't persist these)

//+ (NSArray *)ignoredProperties
//{
//    return @[];
//}

- (NSArray *)owners {
	return [self linkingObjectsOfClass:@"Person" forProperty:@"dogs"];
}

@end