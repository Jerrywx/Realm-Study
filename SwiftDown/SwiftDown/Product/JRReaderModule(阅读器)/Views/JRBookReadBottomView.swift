//
//  JRBookReadVottomView.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/21.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookReadBottomView: UIView {

	weak var delegate: JRReaderViewController?
	
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
		backgroundColor = UIColor.black.withAlphaComponent(0.6)
		
		let count = 4
		let w: CGFloat = UIScreen.scrren_W() / CGFloat(count)
		let y: CGFloat = 40
		let h: CGFloat = frame.size.height - y
		
		for i in 0..<count {
			let x = CGFloat(i) * w
			let button = UIButton(frame: CGRect(x: x, y: y, width: w, height: h))
			button.tag = i
			button.setTitle("目录", for: .normal)
			button.addTarget(self, action: #selector(operateBookRead(sender:)), for: .touchUpInside)
			addSubview(button)
		}
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

extension JRBookReadBottomView {

	/// 底部操作
	func operateBookRead(sender: UIButton) {
		delegate?.openOther(sender: sender)
	}
}


/// JRWebView 代理协议
@objc protocol JRBookReadBottomViewDelegate {

	func openOther(sender:UIButton);

}

