//
//  JRWebView.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/9.
//  Copyright © 2017年 王潇. All rights reserved.
//

import WebKit

class JRWebView: WKWebView {
	
	override init(frame: CGRect, configuration: WKWebViewConfiguration) {
		super.init(frame: frame, configuration: configuration)
		
	}
	
	required init?(coder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}

}

// MARK: - 公共方法
extension JRWebView {

	/// 加载页面
	///
	/// - Parameter url: url
	func loadWeb(urlString: String) {
		///
		let request: NSURLRequest = NSURLRequest(url: NSURL(string: urlString) as! URL)
		///
		load(request as URLRequest)
	}
	
}
