//
//  JRForumHeader.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/7.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumHeader: UIView {
	
	/// 创建圈子头部
	///
	/// - Returns: 返回圈子头部
	static func forumHeader() -> JRForumHeader {
		
		let farme = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: 185)
		let forumHeader = JRForumHeader(frame: farme)
		forumHeader.backgroundColor = #colorLiteral(red: 0.4745098054, green: 0.8392156959, blue: 0.9764705896, alpha: 1)
		return forumHeader
	}
	
	/// 初始化界面
	func setupUI() {
		
	}
}
