//
//  JRWebView.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/9.
//  Copyright © 2017年 王潇. All rights reserved.
//

import WebKit
import MBProgressHUD

class JRWebView: WKWebView {
	
	override init(frame: CGRect, configuration: WKWebViewConfiguration) {
		super.init(frame: frame, configuration: configuration)
		self.uiDelegate = self
		self.navigationDelegate = self
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

// MARK: - WKNavigationDelegate
extension JRWebView: WKNavigationDelegate {
	
	/// 开始加载WebView
	///
	/// - Parameters:
	///   - webView: 当前webView
	///   - navigation: webView 导航
	func webView(_ webView: WKWebView, didStartProvisionalNavigation navigation: WKNavigation!) {
		MBProgressHUD.showAdded(to: webView, animated: true)
	}
	
	/// webView 加载完成
	///
	/// - Parameters:
	///   - webView: 当前webView
	///   - navigation: webView 导航
	func webView(_ webView: WKWebView, didFinish navigation: WKNavigation!) {
		MBProgressHUD.hide(for: webView, animated: true)
	}
	
	/// webView 加载失败
	///
	/// - Parameters:
	///   - webView: 当前 webView
	///   - navigation: webview 导航
	///   - error: 错误原因
	func webView(_ webView: WKWebView, didFail navigation: WKNavigation!, withError error: Error) {
		MBProgressHUD.hide(for: webView, animated: true)
	}
	
	func webView(_ webView: WKWebView, decidePolicyFor navigationResponse: WKNavigationResponse, decisionHandler: @escaping (WKNavigationResponsePolicy) -> Void) {
		
		print(navigationResponse.response.url ?? "error")
		decisionHandler(.allow);
	}
	
}

// MARK: - WKUIDelegate
extension JRWebView: WKUIDelegate {
	
	
	
}


