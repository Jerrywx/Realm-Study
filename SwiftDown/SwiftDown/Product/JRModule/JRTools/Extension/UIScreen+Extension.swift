//
//  Screen+Extension.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/9.
//  Copyright © 2017年 王潇. All rights reserved.
//

import Foundation


// MARK: - 屏幕拓展
extension UIScreen{
	
	/// 获取屏幕宽度
	///
	/// - Returns: 屏幕宽度
	static func scrren_W() -> CGFloat {
		return UIScreen.main.bounds.size.width
	}
	
	/// 获取屏幕高度
	///
	/// - Returns: 屏幕高度
	static func screen_H() -> CGFloat {
		return UIScreen.main.bounds.size.height
	}
	
	/// 屏幕宽度
	var screenW: CGFloat {
		return UIScreen.main.bounds.size.width
	}
	
	/// 屏幕高度
	var screenH: CGFloat {
		return UIScreen.main.bounds.size.height
	}
	
	/// TabBar 高度
	var tabBarH: CGFloat {
		return 49
	}
	
}
