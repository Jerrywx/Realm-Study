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
	
	/// 代理对象
	weak var delegate: JRWebViewDelegate?
	
	override init(frame: CGRect, configuration: WKWebViewConfiguration) {
		super.init(frame: frame, configuration: configuration)
		uiDelegate			= self
		navigationDelegate  = self
		scrollView.decelerationRate = 0.998
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
	
	/// webView js 调用 原生操作
	///
	/// - Parameter jscontent: js内容
	func webViewNativeAction(jscontent: String) {
		delegate?.openTestVC()
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
	
	/// 在发送请求之前，决定是否跳转
	///
	/// - Parameters:
	///   - webView: 当前webView
	///   - navigationAction: webView请求
	///   - decisionHandler: weiView响应回调
	func webView(_ webView: WKWebView, decidePolicyFor navigationAction: WKNavigationAction, decisionHandler: @escaping (WKNavigationActionPolicy) -> Void) {
		
		/// 获取去请求 url
		guard let requestUrl = navigationAction.request.url?.absoluteString else {
			return
		}
		
		/// 解析请求 url
		if (requestUrl.hasPrefix(JRIgnoreFile.js_urlHeader)) {
			webViewNativeAction(jscontent: requestUrl)
			decisionHandler(.cancel);
		} else {
			decisionHandler(.allow);
		}
	}
	
	/// 在收到响应后，决定是否跳转
	///
	/// - Parameters:
	///   - webView: 当前webView
	///   - navigationResponse: webView响应
	///   - decisionHandler: weiView响应回调
	func webView(_ webView: WKWebView, decidePolicyFor navigationResponse: WKNavigationResponse, decisionHandler: @escaping (WKNavigationResponsePolicy) -> Void) {
		decisionHandler(.allow);
	}
	
}

// MARK: - WKUIDelegate
extension JRWebView: WKUIDelegate {
	
}


/// JRWebView 代理协议
@objc protocol JRWebViewDelegate {
	
	/// 打开测试控制器
	func openTestVC()
	
}


