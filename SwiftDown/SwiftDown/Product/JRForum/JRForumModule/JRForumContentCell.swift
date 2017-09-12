//
//  JRForumContentCell.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/7.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumContentCell: UITableViewCell {

	var lastIndex = 0
	
	var beginOffset: CGFloat = 0
	
	/// 滑动方向 wsy
	var direction:Bool = false
	/// 当前显示索引
	var currentIndex = 0
	/// 将要显示索引
	var willAppearIndex = 0
	
	
	///
	weak var superVC: JRForumViewController? {
		didSet {
			for vc in controllerList! {
				vc.superVC = superVC
			}
		}
	}
	
	/// segment
	let segmentH = CGFloat(44);
	
	let segment = UIView()
	
	let segmentControl = UISegmentedControl(items: ["置顶", "全部", "图片"])
	
	/// pageViewController
	let pageViewController = UIPageViewController(transitionStyle: .scroll,
	                                              navigationOrientation: .horizontal,
	                                              options: [UIPageViewControllerOptionSpineLocationKey : UIPageViewControllerSpineLocation.min])
	
	/// collectionView
	var collectionView: UICollectionView?
	
	/// layout
	var layout = UICollectionViewFlowLayout()
	
	/// 子控制器
	var controllerList: [JRForumSubController]?
	
	
	override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
		super.init(style: style, reuseIdentifier: reuseIdentifier)
		setupUI()
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
}

// MARK: - 初始化界面
extension JRForumContentCell: UIPageViewControllerDataSource, UIPageViewControllerDelegate {
	
	///
	func setupUI() {
		///
		contentView.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		
		pageViewController.delegate   = self
		pageViewController.dataSource = self
		
		addContentController()
		
		contentView.addSubview(pageViewController.view)
		
		for view in pageViewController.view.subviews {
			if view.isKind(of: UIScrollView.self) {
				let scroll = view as! UIScrollView
				scroll.delegate = self
			}
		}
	}

	/// 添加子控制器
	func addContentController() {
		
		/// 选择器
		segment.frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: segmentH)
		segmentControl.frame = CGRect(x: 50, y: 8, width: UIScreen.scrren_W() - 100, height: segmentH - 16)
		segmentControl.tintColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
		segmentControl.selectedSegmentIndex = 0
		segmentControl.addTarget(self, action: #selector(segmentAction(segment:)), for: .valueChanged)
		/// 控制器
		let vc1 = JRForumSubController()
		let vc2 = JRForumSubController()
		let vc3 = JRForumSubController()
		controllerList = [vc1, vc2, vc3]
		
		pageViewController.view.addSubview(segmentControl)
		pageViewController.setViewControllers([vc1], direction: .forward, animated: true, completion: nil)
	}
	
	/// 选择器事件
	func segmentAction(segment: UISegmentedControl) {
		
		var direction: UIPageViewControllerNavigationDirection = .forward
		if segment.selectedSegmentIndex < lastIndex {
			direction = .reverse
		}
		lastIndex = segment.selectedSegmentIndex
		let vc = controllerList?[segment.selectedSegmentIndex]
		pageViewController.setViewControllers([vc!], direction: direction, animated: true, completion: nil)
	}
	
	/// 布局
	override func layoutSubviews() {
		super.layoutSubviews()
		
		let frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(), height: UIScreen.screen_H() - 64 - segmentH)
		pageViewController.view.frame = CGRect(x: 0, y: 0, width: UIScreen.scrren_W(),
		                                       height: UIScreen.screen_H() - 64)
		for vc in controllerList! {
			vc.view.frame = frame
			print("frame: \(vc.view.frame)")
		}
	}
	
	
	/// 向上翻页
	///
	/// - Parameters:
	///   - pageViewController: pageViewController
	///   - viewController: 当前显示的控制器
	/// - Returns: 将要显示的控制器
	func pageViewController(_ pageViewController: UIPageViewController, viewControllerBefore viewController: UIViewController) -> UIViewController? {
		
		/// 记录滑动方向
		direction = false
		
		/// 获取控制器
		let indexVC = controllerList?.index(of: viewController as! JRForumSubController)
		
		guard
			let index = indexVC,
			let list = controllerList
			else {
				return nil
		}
		
		if index == NSNotFound || index == 0 {
			return nil
		}
		return list[index - 1]
	}
	
	/// 向下翻页
	///
	/// - Parameters:
	///   - pageViewController: pageViewController
	///   - viewController: 显示的控制器
	/// - Returns: 返回将要显示的控制器
	func pageViewController(_ pageViewController: UIPageViewController, viewControllerAfter viewController: UIViewController) -> UIViewController? {
		
		/// 记录滑动方向
		direction = true
		
		/// 获取控制器
		let indexVC = controllerList?.index(of: viewController as! JRForumSubController)
		
		guard
			let index = indexVC,
			let list = controllerList
			else {
				return nil
		}
		
		if index == NSNotFound || index == list.count - 1 {
			return nil
		}
		
		return list[index + 1]
	}
	
	
	/// 将要显示控制器
	///
	/// - Parameters:
	///   - pageViewController: pageViewController
	///   - pendingViewControllers: 将要显示的控制器列表
	func pageViewController(_ pageViewController: UIPageViewController,
	                        willTransitionTo pendingViewControllers: [UIViewController]) {
		
		let vc = pendingViewControllers.first
		let index = controllerList?.index(of: vc as! JRForumSubController)
		
		/// 保存将要显示的索引
		willAppearIndex = index ?? 0
//		print("----\(pendingViewControllers.count) ----- \(String(describing: index))")
	}
	
//	func pageViewController(_ pageViewController: UIPageViewController,
//	                        didFinishAnimating finished: Bool, 
//	                        previousViewControllers: [UIViewController],
//	                        transitionCompleted completed: Bool) {
//		let vc = previousViewControllers.first
//		let index = controllerList?.index(of: vc as! JRForumSubController)
//		print("======\(previousViewControllers.count) ----- \(String(describing: index))")
//	}
	
}

// MARK: - UIScrollViewDelegate
extension JRForumContentCell: UIScrollViewDelegate {

	/// 停止滑动
	func scrollViewDidEndDecelerating(_ scrollView: UIScrollView) {
		
		let vc = pageViewController.viewControllers?.first as! JRForumSubController
		
		guard let index = controllerList?.index(of: vc) else {
			return
		}
		segmentControl.selectedSegmentIndex = index
		
		/// 保存当前索引
		currentIndex = index
	}
	
	/// scrollView 滑动回调
	///
	/// - Parameter scrollView: 被滑动的 scrollview
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		
		let x = scrollView.contentOffset.x
		var scale = x / UIScreen.scrren_W()
		if scale > 1 {
			scale = scale - 1
		}
		
		let pan = scrollView.panGestureRecognizer
		
		switch pan.state {
		case .began:
			beginOffset = x
			break
			
		case .changed:
			if beginOffset > x {
				direction = false
			} else {
				direction = true
			}
			break
			
		case .cancelled, .failed:
			print("、、、、失败 \(x)  --------- \(pan.state.rawValue)")
			break
			
		default:
			break
		}
		
//		print("====== \(pan.state.rawValue)")
//		print("--------- \(x) - \(UIScreen.scrren_W()) ==== \(scale)")
		
		/// 需要三个参数  当前索引  滑动方向  滑动比例
		let param = String(format:"参数列表:%@ -- %.2f --- %zd -- %zd" , direction.description, scale, currentIndex, willAppearIndex)
//		print("----- 参数列表: \(direction) -- \(scale) --- \(currentIndex) -- \(willAppearIndex)")
		print(param)
		
	}
	
}

