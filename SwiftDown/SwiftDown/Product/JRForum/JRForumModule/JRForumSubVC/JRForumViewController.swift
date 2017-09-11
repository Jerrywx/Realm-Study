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
	
	/// 用户信息高度
	let userInfoH  = UIScreen.screen_H() * 0.382 - 44
	/// 滚动模式
	var scrollModel = 0		/// 标识当前tableView 滚动状态
	var scrollModel2 = 0	/// 标识子控制器中 tableView 滚动状态
	
	/// 圈子头部
	var forumHeader = JRForumHeader.forumHeader()
	
	/// 内容选择器
	var segment = JRForumSegment.forumHeaderSegment()
	
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
		
		let frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: UIScreen.screen_H())
		tableView				= UITableView(frame: frame, style: .plain)
		tableView?.delegate		= self
		tableView?.dataSource	= self
		tableView?.tableHeaderView = forumHeader
		tableView?.register(JRForumContentCell.self, forCellReuseIdentifier: "normal")
		tableView?.contentInset = UIEdgeInsets(top: -64, left: 0, bottom: 0, right: 0)
		view.addSubview(tableView!)
	}
}

// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRForumViewController: UITableViewDataSource, UITableViewDelegate {
	
	///: - UITableViewDataSource
	
	func numberOfSections(in tableView: UITableView) -> Int {
		return 1
	}
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 1
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "normal") as! JRForumContentCell
		cell.superVC = self
		cell.selectionStyle = .none
		return cell
	}

	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
	}
	
	
	func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
		return UIScreen.screen_H() - segment.height - 64
	}
	
	override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
		return 40
	}
	
	override func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
		return segment
	}
	
	
	///: - UITableViewDelegate
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		
		///
		let y = scrollView.contentOffset.y
		
		nowOffset = y - nowOffset
		navigationBarOption(scrollView: scrollView, y: y)
		nowOffset = y
		
		///
		tableViewScroll(y)
	}
	
	/// 个人中心滚动模式控制
	///
	/// - Parameter scrollView: 当前scrollview
	func tableViewScroll(_ y: CGFloat) {
		/// 滚动模式
		let margin = userInfoH - 64;
		
		if y >= margin || scrollModel2 == 1 {
			tableView?.contentOffset = CGPoint(x: 0, y: margin)
			scrollModel = 1
		} else if (scrollModel2 == 0) {
			scrollModel = 0
		}
		
	}
	
	/// 导航栏处理
	///
	/// - Parameter y: contentOffset.y
	func navigationBarOption(scrollView: UIScrollView, y: CGFloat) {
		
		let alphaHeight: CGFloat = 185.0 - 64
		
		/// 透明度
		if y > alphaHeight {
			self.navigationController?.navigationBar.subviews.first?.alpha = 1
		} else {
			let alpha: CGFloat = y / alphaHeight
			self.navigationController?.navigationBar.subviews.first?.alpha = alpha
		}
		
		/// 固定 选在器
		if y > alphaHeight {
			scrollView.contentOffset = CGPoint(x: 0, y: alphaHeight)
		}
		
		/// 关闭 导航栏隐藏
		return
		let needChange = y + (UIScreen.screen_H() * 1) > scrollView.contentSize.height
		
		/// 位置
		if y > alphaHeight && !needChange{
			
			guard
			let navBar = navigationController
			else {
				return
			}
			
			/// 修改 NavigationBar 位置
			navBar.navigationBar.y = navBar.navigationBar.y - nowOffset
			
			/// 限制 NavigationBar 位置
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
