//
//  Dog.h
//  Realm-Demo
//
//  Created by wxiao on 16/1/8.
//  Copyright © 2016年 wxiao. All rights reserved.
//

#import <Realm/Realm.h>

@interface Dog : RLMObject
@property NSString *name;
@property NSInteger age;
@property (readonly) NSArray *owners; // Realm doesn't persist this property because it is readonly
@end

// This protocol enables typed collections. i.e.:
// RLMArray<Dog>
RLM_ARRAY_TYPE(Dog)
