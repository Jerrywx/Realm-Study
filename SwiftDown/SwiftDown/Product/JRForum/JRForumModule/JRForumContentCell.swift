//
//  JRForumContentCell.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/7.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumContentCell: UITableViewCell {

	/// collectionView
	var collectionView: UICollectionView?
	
	/// layout
	var layout = UICollectionViewFlowLayout()
	
	/// 父控制器
	weak var superVC: JRForumViewController?
	
	
	/// 子控制器
	var childVCs: [UIViewController]?
	
	override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
		super.init(style: style, reuseIdentifier: reuseIdentifier)
		setupUI()
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
}

// MARK: - 初始化界面
extension JRForumContentCell {
	
	///
	func setupUI() {

		///
		addSubViewControllers()
		
		///
		layout.itemSize				= CGSize(width: UIScreen.scrren_W(), height: UIScreen.screen_H() - 40 - 64)
		layout.scrollDirection		= .horizontal
		layout.minimumLineSpacing	= 0
		layout.minimumInteritemSpacing = 0
		
		///
		collectionView = UICollectionView(frame: CGRect(x: 0, y: 0,
		                                                width: UIScreen.scrren_W(),
		                                                height: UIScreen.screen_H() - 40 - 64),
		                                  collectionViewLayout: layout)
		collectionView?.delegate		= self
		collectionView?.dataSource		= self
		collectionView?.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		collectionView?.isPagingEnabled = true
		collectionView?.register(UICollectionViewCell.self, forCellWithReuseIdentifier: "col")
		contentView.addSubview(collectionView!)
	}

	func addSubViewControllers() {

		let width = UIScreen.scrren_W()
		let height = UIScreen.screen_H() - 104
		
		let topVC = JRForumTopViewController()
		superVC?.addChildViewController(topVC)
		topVC.view.frame = CGRect(x: 0, y: 0, width: width, height: height)
		
		let allVC = JRForumAllViewController()
		superVC?.addChildViewController(allVC)
		allVC.view.frame = CGRect(x: 0, y: 0, width: width, height: height)
		
		let picVC = JRForumPicViewController()
		superVC?.addChildViewController(picVC)
		picVC.view.frame = CGRect(x: 0, y: 0, width: width, height: height)

		childVCs = [topVC, allVC, picVC]
	}
}

extension JRForumContentCell: UICollectionViewDataSource, UICollectionViewDelegate {
	
	func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
		return 3
	}
	
	func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
		let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "col", for: indexPath)
//		cell.backgroundColor = UIColor.cz_random()
		let vc = childVCs?[indexPath.row] as! UIViewController
		cell.contentView.addSubview(vc.view)
		
		return cell
	}
	
}

