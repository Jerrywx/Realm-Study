//
//  JRBookShopViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookShopViewController: JRBaseViewController {

	/// UISCrollView
	let scrollView: UIScrollView = UIScrollView()
	
    override func viewDidLoad() {
        super.viewDidLoad()
		self.automaticallyAdjustsScrollViewInsets = false
		setupUI()
    }
}

// MARK: - 初始化UI
extension JRBookShopViewController {
	
	/// 初始化UI
	fileprivate func setupUI() {
		let height = UIScreen.screen_H() - 64 - 49
		let frame = CGRect(x: 0, y: 64,
		                   width: UIScreen.scrren_W(), 
		                   height: height)
		
		scrollView.frame = frame
		scrollView.isPagingEnabled = true
		scrollView.contentSize = CGSize(width: UIScreen.main.screenW * 4, height: height)
		view.addSubview(scrollView)
	}
	
	/// 添加频道
	private func addChannel() {
		
		
		
	}
	
}
