//
//  JRBookChapterModel.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookChapterModel: NSObject {

	var actualPrice: CGFloat?
	var bookId: String?
	var chapterId: String?
	var createTime: TimeInterval?
	var isVip: Bool?
	var name: String?
	var status: Int = 0
	var wordCount: Int = 0
	
	/// 模型描述
	override var description: String {
		guard
		let name = name,
		let chapterId = chapterId
		else {
			return "空"
		}
		return "\(chapterId), \(name), \(wordCount)"
	}
}
