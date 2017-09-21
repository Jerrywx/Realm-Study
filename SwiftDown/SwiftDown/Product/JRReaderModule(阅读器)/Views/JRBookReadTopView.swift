//
//  JRBookReadTopView.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/21.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookReadTopView: UIView {

	var appear:Bool = false {
		didSet {
			if appear {
				appearTopView()
			} else {
				disAppearTopView()
			}
//			if appear != nil {
//				if appear! {
//					appearTopView()
//				} else {
//					disAppearTopView()
//				}
//			}
		}
	}
	
	class func bookReadTopView() -> JRBookReadTopView {
		
		let frame = CGRect(x: 0, y: -64, width: UIScreen.scrren_W(), height: 64)
		let topView = JRBookReadTopView(frame: frame)
		topView.setupUI()
		return topView
	}
}

///
extension JRBookReadTopView {
	
	///
	func setupUI() {
		 backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
	}
	/// 显示 topView
	func appearTopView() {
		UIView.animate(withDuration: 0.3) { 
			self.y = 0
		}
	}
	
	/// 隐藏 topView
	func disAppearTopView() {
		UIView.animate(withDuration: 0.3) {
			self.y = -64
		}
	}
}

