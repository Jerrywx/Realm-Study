//
//  JRBookReadVottomView.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/21.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookReadBottomView: UIView {

	var appear:Bool = false {
		didSet {
			if appear {
				appearBottomView()
			} else {
				disAppearBottomView()
			}
		}
	}
	
	
	class func bookReaedBottomView() -> JRBookReadBottomView {
	
		let frame = CGRect(x: 0, y: UIScreen.screen_H(), width: UIScreen.scrren_W(), height: 111)
		let bottomView = JRBookReadBottomView(frame: frame)
		bottomView.setupUI()
		return bottomView
	}

}

extension JRBookReadBottomView {
	
	///
	func setupUI() {
		backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
	}
	
	/// 显示底部
	func appearBottomView() {
		UIView.animate(withDuration: 0.3) { 
			self.y = UIScreen.screen_H() - 111
		}
	}
	
	/// 隐藏底部
	func disAppearBottomView() {
		UIView.animate(withDuration: 0.3) {
			self.y = UIScreen.screen_H()
		}
	}
	
}

