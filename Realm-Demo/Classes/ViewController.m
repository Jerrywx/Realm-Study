//
//  ViewController.m
//  Realm-Demo
//
//  Created by wxiao on 16/1/8.
//  Copyright © 2016年 wxiao. All rights reserved.
//

#import "ViewController.h"
#import "Person.h"
#import "Dog.h"
#import <Realm/Realm.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
	[super viewDidLoad];

	RLMRealm *realm = [RLMRealm defaultRealm];
	[realm transactionWithBlock:^{
		[Person createInRealm:realm withValue:@[@"John", @[@[@"Fido", @1]]]];
		[Person createInRealm:realm withValue:@[@"Mary", @[@[@"Rex", @2]]]];
	}];
	RLMResults *allDogs = [Dog allObjects];
	for (Dog *dog in allDogs) {
		NSArray *ownerNames = [dog.owners valueForKeyPath:@"name"];
		NSLog(@"%@ has %lu owners (%@)", dog.name, (unsigned long)ownerNames.count, ownerNames);
	}
	
//	Dog *d1 = [[Dog alloc] init];
//	d1.name = @"1111";
//	d1.age = 22;
//	
//	Dog *d2 = [[Dog alloc] init];
//	d2.name = @"1111";
//	d2.age = 22;
//	
//	
//	RLMRealm *realm = [RLMRealm defaultRealm];
//	[realm beginWriteTransaction];
//	[realm addObjects:@[d1, d2]];
//	[realm commitWriteTransaction];
}

@end
