//
//  JRForumViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import HMSegmentedControl

class JRForumViewController: JRBaseViewController {

	/// tableView
	lazy var scrollView = UIScrollView()
	///
	let segmentControl: HMSegmentedControl = HMSegmentedControl()
	
    override func viewDidLoad() {
        super.viewDidLoad()
		
		self.automaticallyAdjustsScrollViewInsets = false
		
		setupUI()
    }
}

// MARK: - Action Methond
extension JRForumViewController {
	
	func segmentAct(sender: HMSegmentedControl) {
		print(sender.selectedSegmentIndex)
		
		let w = CGFloat(sender.selectedSegmentIndex) * UIScreen.main.screenW
		let rect = CGRect(x: w, y: 64 + 40, width: UIScreen.main.screenW, height: 1)
		scrollView.scrollRectToVisible(rect, animated: true)
	}	
}

// MARK: - UIScrollViewDelegate
extension JRForumViewController: UIScrollViewDelegate {
	
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		let index:UInt = UInt(scrollView.contentOffset.x / UIScreen.main.screenW)
		segmentControl.setSelectedSegmentIndex(index, animated: true)
	}
}

// MARK: - 初始化界面
extension JRForumViewController {
	
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
		segmentControl.frame = CGRect(x: 0, y: 64, width: UIScreen.main.screenW, height: 40)
		segmentControl.backgroundColor	= #colorLiteral(red: 0.9764705896, green: 0.850980401, blue: 0.5490196347, alpha: 1)
		segmentControl.sectionTitles	= ["热帖", "圈子"]
		segmentControl.titleTextAttributes = [NSFontAttributeName : UIFont.systemFont(ofSize: 14)]
		segmentControl.selectedTitleTextAttributes = [NSFontAttributeName : UIFont.systemFont(ofSize: 16),
		                                              NSForegroundColorAttributeName:#colorLiteral(red: 0.521568656, green: 0.1098039225, blue: 0.05098039284, alpha: 1)]
		segmentControl.selectionIndicatorLocation = .down
		segmentControl.segmentWidthStyle = .fixed
		segmentControl.selectionIndicatorHeight = 3;
		segmentControl.selectionIndicatorColor = #colorLiteral(red: 0.7450980544, green: 0.1568627506, blue: 0.07450980693, alpha: 1)
		segmentControl.addTarget(self, action: #selector(segmentAct(sender:)), for: .valueChanged)
		view.addSubview(segmentControl)
		
		addWebView()
	}
	
	private func addWebView() {
		
		let h = UIScreen.main.screenH - 64 - 40 - 49
		
		let webView: JRWebView = JRWebView(frame: CGRect(x: 0,
		                                                 y: 0, width: UIScreen.main.screenW, height: h))
		scrollView.addSubview(webView)
		webView.loadWeb(urlString: JRIgnoreFile.Url_KthreadIndex)
		
		let webView2: JRWebView = JRWebView(frame: CGRect(x: UIScreen.main.screenW,
		                                                  y: 0, width: UIScreen.main.screenW, height: h))
		scrollView.addSubview(webView2)
		webView2.loadWeb(urlString: JRIgnoreFile.Url_kForumIndex)
	}
}
