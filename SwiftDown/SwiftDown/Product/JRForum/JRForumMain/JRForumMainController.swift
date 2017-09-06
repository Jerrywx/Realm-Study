//
//  JRForumMainController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import HMSegmentedControl

class JRForumMainController: JRBaseViewController {

	/// tableView
	lazy var scrollView = UIScrollView()
	
    override func viewDidLoad() {
        super.viewDidLoad()
		
		self.automaticallyAdjustsScrollViewInsets = false
		setupUI()
    }
	

	
	/// MARK: - Lazy Loading
	/// 选择器 ["热帖", "圈子"]
	lazy var segmentControl: HMSegmentedControl = {
		
		let segmentControl = HMSegmentedControl()
		
		segmentControl.frame			= CGRect(x: 0, y: 64, width: UIScreen.main.screenW, height: 40)
		segmentControl.backgroundColor	= #colorLiteral(red: 0.9764705896, green: 0.850980401, blue: 0.5490196347, alpha: 1)
		segmentControl.sectionTitles	= ["热帖", "圈子"]
		segmentControl.titleTextAttributes			= [NSFontAttributeName : UIFont.systemFont(ofSize: 14)]
		segmentControl.selectedTitleTextAttributes	= [NSFontAttributeName : UIFont.systemFont(ofSize: 16),
		                                          	   NSForegroundColorAttributeName:#colorLiteral(red: 0.521568656, green: 0.1098039225, blue: 0.05098039284, alpha: 1)]
		segmentControl.segmentWidthStyle		= .fixed
		segmentControl.selectionIndicatorColor	= #colorLiteral(red: 0.7450980544, green: 0.1568627506, blue: 0.07450980693, alpha: 1)
		segmentControl.selectionIndicatorHeight = 3;
		segmentControl.selectionIndicatorLocation = .down
		segmentControl.addTarget(self, action: #selector(segmentAct(sender:)), for: .valueChanged)
		
		return segmentControl
	}()

}

// MARK: - Action Methond
extension JRForumMainController {
	
	func segmentAct(sender: HMSegmentedControl) {
		print(sender.selectedSegmentIndex)
		
		let w = CGFloat(sender.selectedSegmentIndex) * UIScreen.main.screenW
		let rect = CGRect(x: w, y: 64 + 40, width: UIScreen.main.screenW, height: 1)
		scrollView.scrollRectToVisible(rect, animated: true)
	}	
}

// MARK: - UIScrollViewDelegate
extension JRForumMainController: UIScrollViewDelegate {
	
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		let index:UInt = UInt(scrollView.contentOffset.x / UIScreen.main.screenW)
		segmentControl.setSelectedSegmentIndex(index, animated: true)
	}
}

// MARK: - 初始化界面
extension JRForumMainController {
	
	/// 初始化UI
	fileprivate func setupUI() {

		///
		let h = UIScreen.main.screenH - 64 - 40 - 49
		let w = UIScreen.main.screenW
		scrollView.frame		= CGRect(x: 0, y: 64 + 40, width: w, height: h)
		scrollView.contentSize	= CGSize(width: w * 2, height: h)
		scrollView.delegate		= self
		scrollView.isPagingEnabled = true
		view.addSubview(scrollView)
		
		///
		view.addSubview(segmentControl)
		
		addWebView()
	}
	
	private func addWebView() {
		
		let h = UIScreen.main.screenH - 64 - 40 - 49
		
		let webView: JRWebView = JRWebView(frame: CGRect(x: 0,
		                                                 y: 0, width: UIScreen.main.screenW, height: h))
		scrollView.addSubview(webView)
		webView.loadWeb(urlString: JRNetWorkURL.getWebPublicParam(urlString: JRIgnoreFile.Url_KthreadIndex)!)
		
		
		let webView2: JRWebView = JRWebView(frame: CGRect(x: UIScreen.main.screenW,
		                                                  y: 0, width: UIScreen.main.screenW, height: h))
		scrollView.addSubview(webView2)
		webView2.loadWeb(urlString: JRNetWorkURL.getWebPublicParam(urlString: JRIgnoreFile.Url_kForumIndex)!)
		
		webView.delegate = self
		webView2.delegate = self;
	}
}

// MARK: - JRWebViewDelegate
extension JRForumMainController: JRWebViewDelegate {
	/// 使用WebView方式打开
	///
	/// - Parameter urlString: url字符串
	func openWithWebView(urlString: String) {
		
	}

	
	func openTestVC(js_Content: String) {
		let testVC = JRTestViewController()
		testVC.label.text = js_Content
		navigationController?.pushViewController(testVC, animated: true)
	}

	func openWithBookCover(bookID: String) {
		let bookVC = JRBookCoverController()
		navigationController?.pushViewController(bookVC, animated: true)
	}
	
	func openWithThread(forumId: String, threadId: String) {
		let threadVC = JRThreadViewController()
		navigationController?.pushViewController(threadVC, animated: true)
	}
	
	func openWithForum(forumId: String) {
		let forumVC = JRForumViewController()
		navigationController?.pushViewController(forumVC, animated: true)
	}
}



