//
//  JRBookServer.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookServer: NSObject {

	
	/// 加载书籍目录
	///
	/// - Parameters:
	///   - bookId: 书籍ID
	///   - completion: 加载完成回调
	static func loadBookLog(bookId: String, completion: @escaping (_ json: [JRBookChapterModel]?, _ isSuccess: Bool) -> ()) {
		
		let param:[String : Any] = ["bookId" : bookId]
		
		JRNetWorkManager.shared.myRequest(JRIgnoreFile.Url_kbookLog,
		                                  parameters: param) { (json: AnyObject?, isSuccess: Bool) in
			
											if !isSuccess || json == nil {
												return
											}
											
			let list:[String : Any] = json as! [String : Any]

			let dic:[String : Any] = list["result"] as! [String : Any]
			let data:[[String: Any]] = dic["chapterList"] as! [[String: Any]]
			
			let array = NSArray.yy_modelArray(with: JRBookChapterModel.self, json: data)
			///
			completion(array as? [JRBookChapterModel], isSuccess)
		}
		
	}

	/// 加载章节内容
	///
	/// - Parameter chapterId: 章节ID
	static func loadChapter(bookId: String, chapterId: String, chapterModel: JRBookChapterModel? , type: String = "0") {

		/// 下载章节内容参数
		let param: [String:String] = ["bookId": bookId,
		                              "chapterId":chapterId,
		                              "type":type,
		                              "version":"4.6.1"]
		
		/// 下载章节内容
		JRNetWorkManager.shared.myRequest(JRIgnoreFile.Url_kChapterDownLoad, parameters: param) { (json:AnyObject?, isSuccess: Bool) in
			
			/*
				bookId = 479435;
				chapterId = 8167891;
				chapterName = "\U4e5d\U6708\Uff01";
				content = "<p>\U3010";
				key = "<null>";
				status = 1;
			*/
			
			print("=====\(String(describing: json))")
			
			
			
		}
	}
	
	
	
}
