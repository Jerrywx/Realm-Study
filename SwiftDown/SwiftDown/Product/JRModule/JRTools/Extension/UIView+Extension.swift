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
	
	var x: CGFloat {
		set {
			var frame = self.frame
			frame.origin.x = x
			self.frame = frame
		}
		
		get {
			return self.frame.origin.x
		}
	}
	
	
	
}
