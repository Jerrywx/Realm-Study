//
//  JRBookCoverHeader.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/4.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverHeader: UIView {

	
	/// 获取书封头部
	///
	/// - Returns: 返回书封页面 头部
	class func bookHeaederView() -> JRBookCoverHeader {
		
		/// 创建书封头部
		let headerView = JRBookCoverHeader(frame: CGRect(x: 0, y: 0, 
		                                                 width: UIScreen.scrren_W(),
		                                                 height: 400))
		
		headerView.backgroundColor = #colorLiteral(red: 0.9764705896, green: 0.850980401, blue: 0.5490196347, alpha: 1)
		
		return headerView
	}
	

}
