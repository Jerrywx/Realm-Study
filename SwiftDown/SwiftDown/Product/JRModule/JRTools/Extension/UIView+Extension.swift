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
	
	/// UIView x
	var x: CGFloat {
		set {
			var tmpFrame = self.frame
			tmpFrame.origin.x = newValue
			self.frame = tmpFrame
		}
		
		get {
			return self.frame.origin.x
		}
	}

	/// UIView y
	var y: CGFloat {
		
		get {
			return frame.origin.y
		}
		
		set {
			var tmpFrame: CGRect = frame
			tmpFrame.origin.y = newValue
			frame = tmpFrame
		}
	}
	
	/// UIView height
	var height: CGFloat {
		get {
			return frame.size.height
		}
		
		set {
			var tmpFrame: CGRect = frame
			tmpFrame.size.height = newValue
			frame = tmpFrame
		}
	}
	
	/// UIView width
	var width: CGFloat {
		get {
			return frame.size.width
		}
		
		set {
			var tmpFrame: CGRect = frame
			tmpFrame.size.width = newValue
			frame = tmpFrame
		}
	}
	
}
