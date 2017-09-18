//
//  JRBookChapterModel.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookChapterModel: NSObject {

	/*
	bookId = 479435;
	chapterId = 8167891;
	chapterName = "\U4e5d\U6708\Uff0c\U54b1\U4eec\U80fd\U75af\U72c2\U4e00\U6b21\U4e48\Uff01";
	content = "<p>\U3010";
	key = "<null>";
	status = 1;
	*/
	
	/// -- 章节目录数据
	// 章节价格
	var actualPrice: CGFloat?
	// 书籍ID
	var bookId: String?
	// 章节ID
	var chapterId: String?
	// 创建时间
	var createTime: TimeInterval?
	// 是否是VIP
	var isVip: Bool?
	// 章节名称
	var name: String?
	// 章节是否已经购买
	var status: Bool = true
	// 章节字数
	var wordCount: Int = 0
	
	/// -- 章节内容数据
	// 章节内容
	var content: String?
	// 章节key [用于购买]
	var key: String?
//	var status: Int?
	
	// 章节内容是否已经下载
	var isDowload: Bool = false
	// 章节页数
	var pageNumb: Int = 0
	// 分页列表
	var pageList: [JRBookPageModel]?
	


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
