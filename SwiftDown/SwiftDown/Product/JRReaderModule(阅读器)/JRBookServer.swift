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
	static func loadChapter(bookId: String,
	                        chapters:[JRBookChapterModel],
	                        type: String = "0", 
	                        completion: @escaping (_ isSuccess: Bool) -> ()) {

		/// 参数判断
		if bookId.characters.count == 0 || chapters.count == 0 {
			//MARK:- 请求失败处理
			return
		}
		
		/// 拼接参数
		var chapterIds: [String] = [String]()
		for model in chapters {
			chapterIds.append(model.chapterId!)
		}
		let chapterId: String = chapterIds.joined(separator: ",")
		let param: [String:String] = ["bookId": bookId,
		                              "chapterId":chapterId,
		                              "type":type,
		                              "version":"4.6.1"]

		/// 下载章节内容
		JRNetWorkManager.shared.myRequest(JRIgnoreFile.Url_kChapterDownLoad, parameters: param) { (json:AnyObject?, isSuccess: Bool) in
			
			/// 请求成功
			if isSuccess {

				guard
					let jsonData: [AnyHashable : Any] = json as? [AnyHashable : Any]
				else {
					return
				}
				
				/// 解析请求数据
				let response = JRNetModel.yy_model(with: jsonData)

				/// 请求成功
				if response?.code == JRNetWorkCode.success.rawValue {
					guard
						let result = response?.result
					else {
							return
					}
					
					let models:[JRBookChapterDetial] = NSArray.yy_modelArray(with: JRBookChapterDetial.self, json: result) as! [JRBookChapterDetial]
					
					
					var i = 0
					///
					for model in models {
						let list:[JRBookPageModel] = operatorModels(model: model)
						
						let mm = chapters[i]
						mm.pageList = list
						mm.pageNumb = list.count
						mm.isDowload = true
						
						i = i + 1
					}
					
					completion(true)
				} else {
					completion(false)
				}
			} else {
				completion(false)
			}
		}
	}
	
	/// 解析章节数据
	static func operatorModels(model: JRBookChapterDetial) -> [JRBookPageModel] {
		
		/// 段落
		let paragraphStyle = NSMutableParagraphStyle()
		paragraphStyle.alignment 		= .justified
		paragraphStyle.lineSpacing 		= 10
		paragraphStyle.paragraphSpacing	= 15
		
		let attri = [NSFontAttributeName: UIFont.systemFont(ofSize: 15),
		             NSParagraphStyleAttributeName:paragraphStyle]
		
		if model.content == nil {
			return [JRBookPageModel]()
		}
		
		/// 属性字符串
		let maString = NSMutableAttributedString(string: model.content!, attributes: attri)
		
		
		let frameSetter = CTFramesetterCreateWithAttributedString(maString)
		
		let bounds = CGRect(x: 0, y: 0, width: UIScreen.scrren_W() - 40, height: UIScreen.screen_H() - 80)
		let path = CGPath(rect: bounds, transform: nil)
		
		var currentOffset:Int		= 0;
		var currentInnerOffset:Int	= 0;
		var hasMorePages: Bool		= true;
		
		var mArrays = [JRBookPageModel]()
		var index = 1
		
		while hasMorePages {
			
			let frame = CTFramesetterCreateFrame(frameSetter,
			                                     CFRange(location: currentInnerOffset, length: 0),
			                                     path, nil)
			
			let range = CTFrameGetVisibleStringRange(frame)
			
			///
			if range.location + range.length < maString.length {
				
				currentOffset += range.length;
				currentInnerOffset += range.length;
				
				let rag = NSMakeRange(range.location, range.length)
//				let aSS:NSAttributedString = maString.attributedSubstring(from: rag)
				
				let mm = JRBookPageModel()
				mm.bookId = model.bookId
				mm.chapterId = model.chapterId
				mm.chapterName = model.chapterName
				mm.aContent = maString.attributedSubstring(from: rag)
				mm.pageNumb = index
				mArrays.append(mm)
				index = index + 1
				
			} else {
				let rag	= NSMakeRange(range.location, maString.length - range.location)
				
				let mm = JRBookPageModel()
				mm.bookId = model.bookId
				mm.chapterId = model.chapterId
				mm.chapterName = model.chapterName
				mm.aContent = maString.attributedSubstring(from: rag)
				
				mm.pageNumb = index
				mArrays.append(mm)
				index = index + 1
				hasMorePages = false
			}
			
			
			
		}
		
		return mArrays
	}
	
}




















