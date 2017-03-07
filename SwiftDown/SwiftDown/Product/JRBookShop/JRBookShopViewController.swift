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
		
		setupUI()
    }
}

// MARK: - 初始化UI
extension JRBookShopViewController {
	
	/// 初始化UI
	func setupUI() {
		
		scrollView.frame = view.bounds
		view.addSubview(scrollView)
		scrollView.backgroundColor = #colorLiteral(red: 0, green: 1, blue: 0, alpha: 1)
		
	}
	
}
