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
	/// - Parameter bookId: 书籍ID
	static func loadBookLog(bookId: String, completion: @escaping (_ json: [JRBookChapterModel]?, _ isSuccess: Bool) -> ()) {
		
		let param:[String : Any] = ["bookId" : bookId]
		
		JRNetWorkManager.shared.myRequest(JRIgnoreFile.Url_kbookLog,
		                                  parameters: param) { (json: AnyObject?, isSuccess: Bool) in
			
											if !isSuccess || json == nil {
												return
											}
											
			let list:[String : Any] = json as! [String : Any]
			
//			guard
//				let list = json as! [String : Any]
//			else {
//				return
//			}
			
			let dic:[String : Any] = list["result"] as! [String : Any]
			let data:[[String: Any]] = dic["chapterList"] as! [[String: Any]]
			
			let array = NSArray.yy_modelArray(with: JRBookChapterModel.self, json: data)
			///
			completion(array as? [JRBookChapterModel], isSuccess)
		}
		
	}
	
	
}
