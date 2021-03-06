//
//  JRBookShelfViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import Alamofire
import MBProgressHUD

class JRBookShelfViewController: JRBaseViewController {

	/// layout
	var layout: UICollectionViewFlowLayout?
	var layout2: UICollectionViewFlowLayout?
	/// UICollectionView
	var collectionView: UICollectionView?
	/// 数据模型
	var listModel: [JRInternalBookModel]?
	
	/// 转场代理
	let transition = JRBookCoverTransition()
	/// 转场位置
	var presentingFrame: CGRect = CGRect(x: 0, y: 0, width: 0, height: 0)

	override func viewDidLoad() {
        super.viewDidLoad()
		/// 初始化界面
		setupUI()
		if #available(iOS 11.0, *) {
//			collectionView?.contentInsetAdjustmentBehavior = .automatic
		} else {
			// Fallback on earlier versions
		}
		/// 加载数据
		loadData()
    }
	
	/// 加载数据
	func loadData() {
		
		/// 点击状态
		MBProgressHUD.showAdded(to: view, animated: true)
		
		/// 加载内置书
		JRInternalBookModel.loadInternalBook { (list: [JRInternalBookModel]?, isSuccess: Bool) in

			MBProgressHUD.hide(for: self.view, animated: true)
			
			guard let list = list else {
				return;
			}
			self.listModel = list
			
			
			let mm = JRInternalBookModel()
			mm.name = "神品透视"
			mm.bookId = "567556"
			mm.picUrl = "http://i.gtimg.cn/qqlive/img/jpgcache/files/qqvideo/x/xv8ntbbe9ccug5o.jpg"
			self.listModel?.append(mm)

			
//			self.listModel?.append(contentsOf: list)

			self.collectionView?.reloadData()
		}
	}

	override func viewDidAppear(_ animated: Bool) {
		super.viewDidAppear(animated)
//		UIApplication.shared.setStatusBarHidden(false, with: .none)
		navigationController?.navigationBar.isHidden = false
	}

}

// MARK: - 初始化界面
extension JRBookShelfViewController {
	
	/// 初始化界面
	fileprivate func setupUI() {
		
		view.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		
		/// layout
		layout = UICollectionViewFlowLayout()
		layout?.itemSize = CGSize(width: UIScreen.main.bounds.width, height: 111)
		layout?.minimumLineSpacing = 0
		layout?.minimumInteritemSpacing = 0
		
		layout2 = UICollectionViewFlowLayout()
		layout2?.itemSize = CGSize(width: 85, height: 168)
		layout2?.minimumLineSpacing = 20
		layout2?.minimumInteritemSpacing = 20
	
		/// UICollectionView
		collectionView = UICollectionView(frame: view.bounds, collectionViewLayout: layout!)
		collectionView?.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		collectionView?.delegate	= self
		collectionView?.dataSource	= self
		collectionView?.alwaysBounceVertical = true
		collectionView?.register(JRBookShelfCell.self, forCellWithReuseIdentifier: "book")
		view.addSubview(collectionView!)
		collectionView?.contentInset = UIEdgeInsets(top: 0, left: 20, bottom: 0, right: 20)
		
		/// 添加长按手势
		let longPressGresture = UILongPressGestureRecognizer(target: self, action: #selector(longPressAction(longGesture:)))
		collectionView?.addGestureRecognizer(longPressGresture)

		/// 右侧切换按钮
		let rightButton = UIBarButtonItem(title: "+", 
		                                  style: .plain, 
		                                  target: self, 
		                                  action: #selector(changeView(sender:)))
		navigationItem.rightBarButtonItem = rightButton
	}
	
	/// 切换视图
	func changeView(sender: UIBarButtonItem) {
		print("切换视图 \(sender.tag)")
		if sender.tag == 0 {
			sender.tag = 1
			collectionView?.setCollectionViewLayout(layout2!, animated: true)
		} else {
			sender.tag = 0
			collectionView?.setCollectionViewLayout(layout!, animated: true)
		}
	}
	
	/// 长按操作
	func longPressAction(longGesture: UILongPressGestureRecognizer) {
		
		let p = longGesture.location(in: collectionView)
	
		switch longGesture.state {
			case .began:
				
				guard
					let selectIndexPath = collectionView?.indexPathForItem(at: p),
					let cell: JRBookShelfCell = collectionView?.cellForItem(at: selectIndexPath) as? JRBookShelfCell
					else {
						collectionView?.endInteractiveMovement()
						return
				}
				
				collectionView?.bringSubview(toFront: cell)
				collectionView?.beginInteractiveMovementForItem(at: selectIndexPath)
				UIView.animate(withDuration: 0.2, animations: { 
					cell.transform = cell.transform.scaledBy(x: 1.1, y: 1.1)
				})
			break
			
			case .changed:

				UIView.animate(withDuration: 0.2, animations: {
					self.collectionView?.updateInteractiveMovementTargetPosition(longGesture.location(in: longGesture.view))
				})
				
			break
			
			case .ended:
				collectionView?.endInteractiveMovement()
			break
			default:
				collectionView?.cancelInteractiveMovement()
				break
		}
	}

}


// MARK: - UICollectionViewDataSource, UICollectionViewDelegate
extension JRBookShelfViewController: UICollectionViewDataSource, UICollectionViewDelegate {
	
	@available(iOS 6.0, *)
	func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
		guard let models = listModel else {
			return 0
		}
		return models.count
	}
	
	func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
		
		let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "book", for: indexPath) as! JRBookShelfCell
		
//		cell.layout = layout2
		let model = listModel?[indexPath.row]
		cell.bookModel = model

		return cell
	}
	
	/// 点击 cell
	func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
	
		guard
		let models = listModel
		else {
			return
		}
		let model = models[indexPath.row]

		/// 打开书架书籍
//		openBookCover(model, indexPath: indexPath)
		
		let readerVC = JRReaderViewController()
		readerVC.title 		= model.name
		readerVC.bookModel 	= model
		readerVC.hidesBottomBarWhenPushed = true
		navigationController?.pushViewController(readerVC, animated: true)
	}

	/// 是否可移动
	func collectionView(_ collectionView: UICollectionView, canMoveItemAt indexPath: IndexPath) -> Bool {
		return true
	}
	
	/// 移动排序
	func collectionView(_ collectionView: UICollectionView, moveItemAt sourceIndexPath: IndexPath, to destinationIndexPath: IndexPath) {
		let model = listModel?[sourceIndexPath.row]
		listModel?.remove(at: sourceIndexPath.row)
		listModel?.insert(model!, at: destinationIndexPath.row)
	}
	
}

// MARK: - 书架操作事件
extension JRBookShelfViewController {
	
	/// 点击书架书籍打开书封页面
	///
	/// - Parameter bookModel: 书籍模型
	fileprivate func openBookCover(_ bookModel: JRInternalBookModel, indexPath: IndexPath) {
		
		/// 获取封面坐标
		let cell = collectionView?.cellForItem(at: indexPath) as! JRBookShelfCell
		let imgView = cell.imageView
		
		let frame: CGRect = cell.convert((imgView?.frame)!, to: self.view) as CGRect
		
		let bookVC = JRBookCoverController()
		bookVC.bookName					= bookModel.name
		transition.fromFrame			= frame
		bookVC.presentingFrame			= frame
		bookVC.bookImage				= cell.imageView?.image
		transition.imgView				= cell.imageView
		bookVC.transitioningDelegate	= transition
		bookVC.modalPresentationStyle	= .custom
		present(bookVC, animated: true, completion: nil)
//		navigationController?.pushViewController(bookVC, animated: true)

	}
}


// MARK: - 测试部分
extension JRBookShelfViewController {

	/// 点击屏幕
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		/// 网络测试
		//		JRNetWorkManager.shared.testNetWork()
		/// 公共上行基础信息测试
		testNetWork(param: JRNetWorkURL.getPublicParam(param: ["forumId" : "116320"]))
	}
	
	/// 网络请求
	func testNetWork(param:[String : Any] = [:]) {
		/// http://api1.zongheng.com/iosapi/forum/detail 圈子
		/// http://api1.zongheng.com/iosapi/book/builtInBook 内置书
		JRNetWorkManager.shared.myRequest("http://api1.zongheng.com/iosapi/book/builtInBook",
		                                  method: HTTPMethod.post,
		                                  parameters: param,
		                                  encoding: URLEncoding.default,
		                                  headers: nil) { (json, isSuccess) in
											print("成功")
											if let js = json {
												print(js)
											}
		}
	}
}





