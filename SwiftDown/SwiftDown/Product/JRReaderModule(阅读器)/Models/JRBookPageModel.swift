//
//  JRBookPageModel.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/17.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookPageModel: NSObject {

	/// 书籍ID
	var bookId: String?
	/// 章节ID
	var chapterId: String?
	/// 章节名称
	var chapterName: String?
	/// 章节内容			【不存储】
	var content: String?
	/// key购买使用
	var key: String?
	/// ...
	var status: Int?
	
	/// ---
	/// 当前页面显示 属性字符串
	var aContent: NSAttributedString?
	/// 页码
	var pageNumb: Int = 0
	/// 总页数
	var totalPage: Int = 0
	
	
}
