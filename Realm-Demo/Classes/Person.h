//
//  Person.h
//  Realm-Demo
//
//  Created by wxiao on 16/1/8.
//  Copyright © 2016年 wxiao. All rights reserved.
//

#import <Realm/Realm.h>
#import "Dog.h"

@interface Person : RLMObject
@property NSString      *name;
@property RLMArray<Dog> *dogs;
@end

// This protocol enables typed collections. i.e.:
// RLMArray<Person>
RLM_ARRAY_TYPE(Person)
