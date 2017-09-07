//
//  JRForumSegment.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/7.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumSegment: UIView {

	/// 获取圈子头部选择器
	///
	/// - Returns: 返回圈子选择器
	static func forumHeaderSegment() -> JRForumSegment {
		let frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: 40)
		let segment = JRForumSegment(frame: frame)
		segment.backgroundColor = #colorLiteral(red: 0.9764705896, green: 0.850980401, blue: 0.5490196347, alpha: 1)
		return segment
	}

}
