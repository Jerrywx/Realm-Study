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
	/// 内容 cell
	let contentCell = JRForumContentCell()
	/// 用户信息高度
	let userInfoH  = UIScreen.screen_H() * 0.382 - 44
	/// 滚动模式
	var scrollModel = 0		/// 标识当前tableView 滚动状态
	var scrollModel2 = 0	/// 标识子控制器中 tableView 滚动状态
	/// 圈子头部
	var forumHeader = JRForumHeader.forumHeader()
	/// 内容选择器
	var segment = JRForumSegment.forumHeaderSegment()
	
	
	//// ------
	var topPosition: CGFloat = 0
	var allPosition: CGFloat = 0
	var picPosition: CGFloat = 0
	/// 当前显示索引
	var curretnIndex = 0
	/// 是否跟新位置
	var updateLocation: Bool = true
	
	
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
		
		contentCell.superVC = self
		
		let frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: UIScreen.screen_H())
		tableView				= UITableView(frame: frame, style: .grouped)
		tableView?.delegate		= self
		tableView?.dataSource	= self
		tableView?.tableHeaderView = forumHeader
		tableView?.register(JRForumContentCell.self, forCellReuseIdentifier: "normal")
		tableView?.showsVerticalScrollIndicator = false
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
		return contentCell
	}

	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
	}
	
	func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
		return UIScreen.screen_H() - 64
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
		
		/// 保存索引
		saveLocation(curretnIndex)
		
		/// 滚动模式
		let margin = userInfoH - 64;

		if y >= margin {
			scrollModel2 = 1
		}
		
		if y >= margin || scrollModel2 == 1 {
//		if y >= margin {
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
		
		let alphaHeight: CGFloat = userInfoH - 64
		
		/// 透明度
		if y > alphaHeight {
			self.navigationController?.navigationBar.subviews.first?.alpha = 1
		} else {
			let alpha: CGFloat = y / alphaHeight
			self.navigationController?.navigationBar.subviews.first?.alpha = alpha
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

// MARK: - 内容切换动画相关
extension JRForumViewController {
	
	func saveIndex(index: Bool) {
		updateLocation = index
	}

	/// 保存当前位置坐标
	///
	/// - Parameter currentIndex: 当前的位置
	func saveLocation(_ currentIndex: NSInteger) {
		
		/// 保存索引
		self.curretnIndex = currentIndex

		if !updateLocation {
			return
		}
		
		/// 记录位置
		switch currentIndex {
		case 0:
			topPosition = tableView?.contentOffset.y ?? 0
			break
			
		case 1:
			allPosition = tableView?.contentOffset.y ?? 0
			break
			
		case 2:
			picPosition = tableView?.contentOffset.y ?? 0
			break
		default:
			break
		}
		
		print("A:\(topPosition) B:\(allPosition) C:\(picPosition) ---- \(currentIndex)")
		
	}
	
	/// 切换动画
	///
	/// - Parameters:
	///   - currentIndex: 当前内容索引
	///   - nextIndex: 将要显示内容索引
	///   - percentage: 切换百分比
	///   - direction: 切换方向
	func changeLocation(currentIndex: NSInteger, nextIndex: NSInteger, percentage: CGFloat, direction: Bool) {
		
		/// 判断动画条件
		/// 滑动到 最左侧 或者 最右侧 继续滑动时  不做动画
		if (direction == false && currentIndex == 0) || (direction == true && nextIndex == 2) {
			return
		}
		
		/// 获取 动画结束位置
		var endPosition = topPosition
		if nextIndex == 1 {
			endPosition = allPosition
		} else if nextIndex == 2 {
			endPosition = picPosition
		}
		
		/// 获取 动画开始位置
		var index = 0
		if direction == true {
			index = nextIndex - 1
		} else {
			index = nextIndex + 1
		}
		
		var startPosition = topPosition
		if index == 1 {
			startPosition = allPosition
		} else if index == 2 {
			startPosition = picPosition
		}
		
		/// 当动画 开始位置 和 结束位置相同时 不做动画
		if startPosition == endPosition {
			return
		}
		
		/// 计算实时动画位置
		let length = endPosition - startPosition
		let location = percentage * length
		
		print("----\(startPosition)  \(endPosition)--\(location)")
		
		/// 指定动画
		tableView?.setContentOffset(CGPoint(x: 0, y: startPosition + location), animated: false)
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
