//
//  JRWebViewViewController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRWebViewViewController: JRBaseViewController {

	/// webView
	let webView = JRWebView()
	/// urlString
	var urlString: String? = nil
	
    override func viewDidLoad() {
        super.viewDidLoad()

		setupUI()
    }
}

// MARK: - UI设置
extension JRWebViewViewController {
	
	/// 设置UI
	func setupUI() {
		
		/// 设置 webView
		webView.frame = view.bounds
		webView.delegate = self
		view.addSubview(webView)
		
		guard
		let url = urlString
		else {
			return
		}
		/// 加载webView
		webView.loadWeb(urlString: url)
	}
}

// MARK: - JRWebViewDelegate
extension JRWebViewViewController: JRWebViewDelegate {
	
	/// 打开测试控制器
	///
	/// - Parameter js_Content: js字符串
	func openTestVC(js_Content: String) {
		let testVC = JRTestViewController()
		testVC.label.text = js_Content
		navigationController?.pushViewController(testVC, animated: true)
	}
	
	/// 使用WebView方式打开
	///
	/// - Parameter urlString: url字符串
	func openWithWebView(urlString: String) {
		let webVC = JRWebViewViewController()
		webVC.urlString = urlString
		navigationController?.pushViewController(webVC, animated: true)
	}
	
}


