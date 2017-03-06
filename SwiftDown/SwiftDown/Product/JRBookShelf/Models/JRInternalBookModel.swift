//
//  JRInternalBookModel.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/3.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import YYModel

class JRInternalBookModel: NSObject {
	
	var bookId: String?
	var categoryName: String?
	var name: String?
	var authorId: String?
	var authorImg: String?
	var authorName: String?
	
	
}

// MARK: - 数据加载
extension JRInternalBookModel {
	
	/// 加载内置书
	static func loadInternalBook(completion:@escaping (_ list: [JRInternalBookModel]?, _ isSuccess: Bool) -> ()) {
		JRNetWorkManager.shared.myRequest(JRIgnoreFile.Url_InternalBook) { (json: AnyObject?, isSuccess: Bool) in
			
			/// 数据判断
			guard let jsonData = json else {
				completion(nil, false)
				return
			}
			
			/// 数据处理
			let result = jsonData["result"] as! [[String : AnyObject]]
			let array = NSArray.yy_modelArray(with: JRInternalBookModel.self, json: result)
			completion(array as? [JRInternalBookModel], true)
			
		}
	}
	
	/// 内置书模型描述
	override var description: String {
		return yy_modelDescription()
	}
}

/*
{
	bookId		= 472776;
	categoryName = "\U90fd\U5e02\U5f02\U80fd";
	name			= "\U8d85\U54c1\U900f\U89c6";
	authorId	= 15951103;
	authorImg	= "<null>";
	authorName	= "\U674e\U95f2\U9c7c";

	authorization = 4;
	categoryId	= 1097;

	chapterCount = 1768;
	description = ;
	female		= 0;
	firstChapterIdNoIntroduction = 7836407;
	isAutoBuyChapter	= 0;
	keywords			= "\U70ed\U8840,\U723d\U6587,\U9752\U6625,\U594b\U6597,\U7231\U60c5";
	latestChapterId		= 35975593;
	latestChapterName	= "1767\U7ae0 \U89e3\U653e\U51b0\U4e4b\U661f\U5927\U76d1\U72f1";
	latestChapterUpateDateStr = "4\U5c0f\U65f6\U524d";

	picUrl			= "htt";
	serialStatus	= 0;
	totalWord		= 5916952;
	type			= 3;
	updateTime		= 1488515388000;
},

*/
