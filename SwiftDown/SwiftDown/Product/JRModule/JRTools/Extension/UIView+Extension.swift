//
//  UIView+Extension.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import Foundation


import Foundation

extension UIView {
	
	/// 设置 View 的x
	var x: CGFloat {
		set {
			var newFarme = self.frame
			newFarme.origin.x = x
			self.frame = newFarme
		}
		
		get {
			return self.frame.origin.x
		}
	}
	
	/// 设置 View 的 y
//	var y: CGFloat {
//		set {
//			var newFarme = frame
//			newFarme.origin.y = y
//			frame = newFarme
//		}
//		
//		get {
//			return frame.origin.y
//		}
//	}
	
	/// UIView y
	var y : CGFloat {
		
		get {
			return frame.origin.y
		}
		
		set {
			var tmpFrame: CGRect = frame
			tmpFrame.origin.y = newValue
			frame = tmpFrame
		}
	}
	
	
}
