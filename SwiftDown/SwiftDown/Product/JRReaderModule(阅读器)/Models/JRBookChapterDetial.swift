//
//  JRBookChapterDetial.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/18.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookChapterDetial: NSObject {

	var bookId: String?
	var chapterId: String?
	var chapterName: String?
	var content: String?
	var key: String?
	var status: Int = 0
	
	override var description: String {
		return "\(bookId!) - \(chapterId!) - \(content!)\n"
	}
}
