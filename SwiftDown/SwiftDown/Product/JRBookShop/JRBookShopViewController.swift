//
//  JRBookShopViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import HMSegmentedControl

class JRBookShopViewController: JRBaseViewController {

	/// UISCrollView
	let scrollView: UIScrollView = UIScrollView()
	let segmentControl: HMSegmentedControl = HMSegmentedControl()

    override func viewDidLoad() {
        super.viewDidLoad()
		self.automaticallyAdjustsScrollViewInsets = false
		setupUI()
    }
}

// MARK: - Action Methond
extension JRBookShopViewController {
	
	func segmentAct(sender: HMSegmentedControl) {
		print(sender.selectedSegmentIndex)
		
		let w = CGFloat(sender.selectedSegmentIndex) * UIScreen.main.screenW
		let rect = CGRect(x: w, y: 64 + 40, width: UIScreen.main.screenW, height: 1)
		scrollView.scrollRectToVisible(rect, animated: true)
	}
	
}

// MARK: - UIScrollViewDelegate
extension JRBookShopViewController: UIScrollViewDelegate {
	
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		let index:UInt = UInt(scrollView.contentOffset.x / UIScreen.main.screenW)
		print("======== \(index) --- \(scrollView.contentOffset.x)")
		segmentControl.setSelectedSegmentIndex(index, animated: true)
	}
}

// MARK: - 初始化UI
extension JRBookShopViewController {
	
	/// 初始化UI
	fileprivate func setupUI() {
		
		/// Segment
		segmentControl.frame = CGRect(x: 0, y: 64, width: UIScreen.main.screenW, height: 40)
		segmentControl.backgroundColor	= #colorLiteral(red: 0.9764705896, green: 0.850980401, blue: 0.5490196347, alpha: 1)
		segmentControl.sectionTitles	= ["精选", "免费", "排行", "书库"]
		segmentControl.titleTextAttributes = [NSFontAttributeName : UIFont.systemFont(ofSize: 14)]
		segmentControl.selectedTitleTextAttributes = [NSFontAttributeName : UIFont.systemFont(ofSize: 16),
		                                              NSForegroundColorAttributeName:#colorLiteral(red: 0.521568656, green: 0.1098039225, blue: 0.05098039284, alpha: 1)]
		segmentControl.selectionIndicatorLocation = .down
		segmentControl.segmentWidthStyle = .fixed
		segmentControl.selectionIndicatorHeight = 3;
		segmentControl.selectionIndicatorColor = #colorLiteral(red: 0.7450980544, green: 0.1568627506, blue: 0.07450980693, alpha: 1)
		segmentControl.addTarget(self, action: #selector(segmentAct(sender:)), for: .valueChanged)
		view.addSubview(segmentControl)
		
		/// scrollView
		let height = UIScreen.screen_H() - 64 - 49 - 40
		let frame = CGRect(x: 0, y: 64 + 40,
		                   width: UIScreen.scrren_W(), 
		                   height: height)
		scrollView.frame			= frame
		scrollView.delegate			= self;
		scrollView.contentSize		= CGSize(width: UIScreen.main.screenW * 4, height: height)
		scrollView.isPagingEnabled	= true
		view.addSubview(scrollView)
	}
	
	/// 添加频道
	private func addChannel() {
		
		
		
	}
}
