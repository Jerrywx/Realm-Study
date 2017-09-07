//
//  JRForumViewController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumViewController: JRBaseViewController {

	/// tableView
	var tableView: UITableView?
	
	/// Offset
	var nowOffset: CGFloat = 0
	
    override func viewDidLoad() {
        super.viewDidLoad()

		title = "圈子"
        view.backgroundColor = #colorLiteral(red: 0.4745098054, green: 0.8392156959, blue: 0.9764705896, alpha: 1)
		
		automaticallyAdjustsScrollViewInsets = false
		setupUI()
    }
	
	override func viewWillAppear(_ animated: Bool) {
		super.viewWillAppear(animated)

		/// 转场时导航栏透明度动画
		transitionCoordinator?.animate(alongsideTransition: { _ in
			self.navigationController?.navigationBar.subviews.first?.alpha = 0
		}, completion: nil)
		
		/// 转场时 tabBar动画
		transitionCoordinator?.animateAlongsideTransition(in: self.tabBarController?.view,
		                                                  animation: { _ in
			self.tabBarController?.tabBar.y = UIScreen.screen_H()
		}, completion: nil)
	}
	
	override func viewWillDisappear(_ animated: Bool) {
		super.viewWillDisappear(animated)

		/// 转场时导航栏透明度动画
		transitionCoordinator?.animate(alongsideTransition: { _ in
			self.navigationController?.navigationBar.subviews.first?.alpha = 1
		}, completion: nil)

		/// 转场时 tabBar动画
		transitionCoordinator?.animateAlongsideTransition(in: self.tabBarController?.view,
		                                                  animation: { _ in
			self.tabBarController?.tabBar.y = UIScreen.screen_H() - 49
		}, completion: nil)
	}
}

// MARK: - 设施UI
extension JRForumViewController {
	
	func setupUI() {
		
		tableView = UITableView(frame: view.bounds, style: .grouped)
		tableView?.delegate = self
		tableView?.dataSource = self
		tableView?.register(UITableViewCell.self, forCellReuseIdentifier: "normal")
		view.addSubview(tableView!)
	}
}

// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRForumViewController: UITableViewDataSource, UITableViewDelegate {
	
	///: - UITableViewDataSource
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 30
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "normal")
		
		cell?.textLabel?.text = "---- \(indexPath.row)"
		
		return cell!
	}

	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
	}
	
	func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
		return 60
	}
	
	override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	override func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	
	///: - UITableViewDelegate
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		
		///
		let y = scrollView.contentOffset.y
		
		nowOffset = y - nowOffset
		
		navigationBarOption(scrollView: scrollView, y: y)
		
		nowOffset = y
	}
	
	/// 导航栏处理
	///
	/// - Parameter y: contentOffset.y
	func navigationBarOption(scrollView: UIScrollView, y: CGFloat) {
		
		/// 透明度
		if y > 150 {
			self.navigationController?.navigationBar.subviews.first?.alpha = 1
		} else {
			let alpha: CGFloat = y / 150.0
			self.navigationController?.navigationBar.subviews.first?.alpha = alpha
		}
		
		let needChange = y + (UIScreen.screen_H() * 1.5) > scrollView.contentSize.height
		
		/// 位置
		if y > 200 && !needChange{
			
			guard
			let navBar = navigationController
			else {
				return
			}
			
			navBar.navigationBar.y = navBar.navigationBar.y - nowOffset
			
			if navBar.navigationBar.y < -44 {
				navBar.navigationBar.y = -44
			}
			
			if navBar.navigationBar.y > 20 {
				navBar.navigationBar.y = 20
			}
		}
	}
	
}





/*
/// 控制器转场时 导航栏动画
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
*/
