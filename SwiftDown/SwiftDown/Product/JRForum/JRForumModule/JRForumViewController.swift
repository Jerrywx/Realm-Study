//
//  JRForumViewController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumViewController: JRBaseViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

		title = "圈子"
        view.backgroundColor = #colorLiteral(red: 0.4745098054, green: 0.8392156959, blue: 0.9764705896, alpha: 1)
    }
	
	override func viewWillAppear(_ animated: Bool) {
		super.viewWillAppear(animated)
		
//		self.tabBarController?.tabBar
		
		var frame = self.tabBarController?.tabBar.frame
		frame?.origin.y = UIScreen.screen_H()
		
		transitionCoordinator?.animate(alongsideTransition: { _ in
			self.navigationController?.navigationBar.subviews.first?.alpha = 0
		}, completion: nil)
		
		transitionCoordinator?.animateAlongsideTransition(in: self.tabBarController?.view, animation: { _ in
			self.tabBarController?.tabBar.frame = frame!
		}, completion: nil)
	}
	
	
	
	override func viewWillDisappear(_ animated: Bool) {
		super.viewWillDisappear(animated)

		transitionCoordinator?.animate(alongsideTransition: { _ in
			self.navigationController?.navigationBar.subviews.first?.alpha = 1
		}, completion: nil)
		
		var frame = self.tabBarController?.tabBar.frame
		frame?.origin.y = UIScreen.screen_H() - 49
		
		transitionCoordinator?.animateAlongsideTransition(in: self.tabBarController?.view, animation: { _ in
			self.tabBarController?.tabBar.frame = frame!
		}, completion: nil)
	}

//	override func viewWillAppear(_ animated: Bool) {
//		super.viewWillAppear(animated)
//
//		navigationController?.navigationBar.setBackgroundImage(UIImage(), for: .default)
//		//去掉导航栏底部的黑线
//		navigationController?.navigationBar.shadowImage = UIImage()
//	}
//	
//	override func viewWillDisappear(_ animated: Bool) {
//		super.viewWillDisappear(animated)
//		navigationController?.navigationBar.setBackgroundImage(nil, for: .default)
//		navigationController?.navigationBar.shadowImage = nil
//	}
}
