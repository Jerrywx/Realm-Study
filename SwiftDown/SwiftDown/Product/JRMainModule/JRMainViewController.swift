//
//  JRMainViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRMainViewController: UITabBarController {

    override func viewDidLoad() {
        super.viewDidLoad()

        setupUI()
    }
}

// MARK: - 初始化子控制器
extension JRMainViewController {
	
	/// 初始化UI
	fileprivate func setupUI() {
		view.backgroundColor = #colorLiteral(red: 0, green: 1, blue: 0, alpha: 1)
		createChildControllers()
	}
	
	/// 创建子控制器
	private func createChildControllers() {
		
		let shelf = JRBookShelfViewController()
		let shop  = JRBookShopViewController()
		let forum = JRForumViewController()
		let person = JRPersonViewController()
		
		shelf.title  = "书架"
		shop.title   = "书城"
		forum.title  = "圈子"
		person.title = "个人"
		
		shelf.tabBarItem.setTitleTextAttributes([NSForegroundColorAttributeName : UIColor.cz_color(withHex: 0xdf3d3d)], for: .highlighted)
		shop.tabBarItem.setTitleTextAttributes([NSForegroundColorAttributeName : UIColor.cz_color(withHex: 0xdf3d3d)], for: .highlighted)
		forum.tabBarItem.setTitleTextAttributes([NSForegroundColorAttributeName : UIColor.cz_color(withHex: 0xdf3d3d)], for: .highlighted)
		person.tabBarItem.setTitleTextAttributes([NSForegroundColorAttributeName : UIColor.cz_color(withHex: 0xdf3d3d)], for: .highlighted)
		
		
		shelf.tabBarItem.image = #imageLiteral(resourceName: "shujia_xiabiaoqian")
		shelf.tabBarItem.selectedImage = #imageLiteral(resourceName: "shujiaanxia_xiabiaoqian")
		
		shop.tabBarItem.image = #imageLiteral(resourceName: "shucheng_xiabiaoqian")
		shop.tabBarItem.selectedImage = #imageLiteral(resourceName: "shuchenganxia_xiabiaoqian")
		
		forum.tabBarItem.image = #imageLiteral(resourceName: "quanzi_xiabiaoqian")
		forum.tabBarItem.selectedImage = #imageLiteral(resourceName: "quanzianxia_xiabiaoqian")
		
		person.tabBarItem.image = #imageLiteral(resourceName: "wode_xiabiaoqian")
		person.tabBarItem.selectedImage = #imageLiteral(resourceName: "wodeanxia_xiabiaoqian")
		
		let shelfNav  = JRNavigationController(rootViewController: shelf)
		let shopNav   = JRNavigationController(rootViewController: shop)
		let forumNav  = JRNavigationController(rootViewController: forum)
		let personNav = JRNavigationController(rootViewController: person)
		
		self.viewControllers = [shelfNav, shopNav, forumNav, personNav]
	}
}
