//
//  JRReaderViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRReaderViewController: JRBaseViewController {

	/// layout
	let layout = UICollectionViewFlowLayout()
	/// collectionView
	var collectionView: UICollectionView?
	/// 章节数量
	var totalChapterNumber = 21//101
	var minChapter = 0
	var maxChapter = 20
	
	/// 偏移章节
	var chapterOffset: Int = 0
	
	/// 书籍模型
	var bookModel: JRInternalBookModel?
	/// 章节模型
	var chapterList: [JRBookChapterModel]?
	
	
    override func viewDidLoad() {
        super.viewDidLoad()
		setupUI()
		
		loadData()
    }
}

/// 加载数据
extension JRReaderViewController {
	
	/// 加载数据
	func loadData() {
		
		guard
		let bookId = bookModel?.bookId
		else { return }

		/// 获取 bookID 加载书籍目录
		JRBookServer.loadBookLog(bookId: bookId) { (models: [JRBookChapterModel]?, isSuccess: Bool) in
			guard
				let list = models
			else { return }
			self.chapterList = list
//			self.totalChapterNumber = list.count
			self.collectionView?.reloadData()
			
			/// 下载第一章节
			let model:JRBookChapterModel = list.first!
			let chapters = [list[0], list[1], list[2]]

			JRBookServer.loadChapter(bookId: model.bookId!, chapters: chapters)
		}
	}
}

// MARK: - 初始化界面
extension JRReaderViewController {
	
	/// 初始化界面
	func setupUI() {
		///
		view.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		navigationController?.navigationBar.isHidden = true
		
		/// layout
		layout.minimumLineSpacing = 0
		layout.minimumInteritemSpacing = 0
		layout.itemSize = UIScreen.main.bounds.size
		
		///
		collectionView = UICollectionView(frame: view.bounds,
		                                  collectionViewLayout: layout)
		collectionView?.delegate 	= self
		collectionView?.dataSource 	= self
		collectionView?.backgroundColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
		collectionView?.bounces = false
		collectionView?.register(JRReadPageCell.self, forCellWithReuseIdentifier: "cell")
		view.addSubview(collectionView!)
		
		if #available(iOS 11.0, *) {
			collectionView?.contentInsetAdjustmentBehavior = .never
		}
	}

	/// 隐藏导航栏
	override var prefersStatusBarHidden: Bool {
		return true
	}
}

// MARK: - UICollectionViewDataSource, UICollectionViewDelegate
extension JRReaderViewController: UICollectionViewDataSource, UICollectionViewDelegate {
	
	func numberOfSections(in collectionView: UICollectionView) -> Int {
		return totalChapterNumber
	}
	
	func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
		return 1
	}
	
	func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
		
		let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "cell", for: indexPath) as! JRReadPageCell
		
		if indexPath.section % 2 == 0 {
			cell.backgroundColor = UIColor.red
		} else {
			cell.backgroundColor = UIColor.yellow
		}
		if chapterList != nil {
			if ((chapterList?.count)! + chapterOffset) > indexPath.section {
				let model:JRBookChapterModel = chapterList![indexPath.section + chapterOffset]
				cell.label.text = model.name
				cell.chapterModel = model
				cell.index = chapterList?.index(of: model)
			} else {
				cell.indexPath = indexPath
			}
		} else {
			cell.indexPath = indexPath
		}
		
		
		
		return cell
	}
	
	/// 滑动停止
	func scrollViewDidEndDecelerating(_ scrollView: UIScrollView) {
		
		
//		let cells = collectionView?.visibleCells
//		let cell: JRReadPageCell = cells?.first as! JRReadPageCell
//
//		let indexPath = collectionView?.indexPath(for: cell)
//
////		print("============================\(indexPath) - \(cell.label.text)")
//
//		guard
//		let section = indexPath?.section
//		else {
//			return
//		}
//
//		let chapterIndex = cell.index
//
//		/// 大于时
//		if section >= maxChapter {
//			// 21 15
//			chapterOffset = chapterIndex! - (totalChapterNumber / 2 + 1)
//			collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//			                               with: nil,
//			                               waitUntilDone: false)
//			let y = collectionView?.contentOffset.y
//			let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//			let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
//			collectionView?.contentOffset = point
//		}
//
//		/// 小于时
//		if section <= minChapter {
//
//			/// 书籍顶部
//			if chapterIndex! <= (totalChapterNumber / 2 + 1) {
//				chapterOffset = 0
//
//				collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//				                                with: nil,
//				                                waitUntilDone: false)
//				let y = collectionView?.contentOffset.y
//				let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(chapterIndex! - 1) + of)
//				collectionView?.contentOffset = point
//
//			} else {
//				chapterOffset = chapterIndex! - (totalChapterNumber / 2 + 1)
//				collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//				                                with: nil,
//				                                waitUntilDone: false)
//				let y = collectionView?.contentOffset.y
//				let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
//				collectionView?.contentOffset = point
//			}
//		}
		
	}
	
	func scrollViewDidEndDragging(_ scrollView: UIScrollView, willDecelerate decelerate: Bool) {
//		let cells = collectionView?.visibleCells
//		let cell: JRReadPageCell = cells?.first as! JRReadPageCell
//
//		let indexPath = collectionView?.indexPath(for: cell)
//
//		//		print("============================\(indexPath) - \(cell.label.text)")
//
//		guard
//			let section = indexPath?.section
//			else {
//				return
//		}
//
//		let chapterIndex = cell.index
//
//		/// 大于时
//		if section >= maxChapter {
//			// 21 15
//			chapterOffset = chapterIndex! - (totalChapterNumber / 2 + 1)
//			collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//			                                with: nil,
//			                                waitUntilDone: false)
//			let y = collectionView?.contentOffset.y
//			let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//			let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
//			collectionView?.contentOffset = point
//		}
//
//		/// 大于时
//		if section <= minChapter {
//
//			/// 书籍顶部
//			if chapterIndex! <= (totalChapterNumber / 2 + 1) {
//				chapterOffset = 0
//
//				collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//				                                with: nil,
//				                                waitUntilDone: false)
//				let y = collectionView?.contentOffset.y
//				let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(chapterIndex! - 1) + of)
//				collectionView?.contentOffset = point
//
//			} else {
//				chapterOffset = chapterIndex! - (totalChapterNumber / 2 + 1)
//				collectionView?.performSelector(onMainThread: #selector(collectionView?.reloadData),
//				                                with: nil,
//				                                waitUntilDone: false)
//				let y = collectionView?.contentOffset.y
//				let of = y! - UIScreen.main.bounds.size.height * CGFloat((section - 1))
//				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
//				collectionView?.contentOffset = point
//			}
//		}
	}

	func collectionView(_ collectionView: UICollectionView, willDisplay cell: UICollectionViewCell, forItemAt indexPath: IndexPath) {
		
		print("--------------- \(indexPath)");
		guard
			let cel: JRReadPageCell = cell as? JRReadPageCell
			else {
				return
		}
		
		print("--------------- 1");
		guard
			let chapterIndex = cel.index
		else {
				return
		}
		print("--------------- 2");
		/// 大于时
		if indexPath.section >= maxChapter {
			// 21 15
			chapterOffset = chapterIndex - (totalChapterNumber / 2 + 1)
			collectionView.performSelector(onMainThread: #selector(collectionView.reloadData),
			                                with: nil,
			                                waitUntilDone: false)
			let y = collectionView.contentOffset.y
			let of = y - UIScreen.main.bounds.size.height * CGFloat((indexPath.section - 1))
			let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
			collectionView.contentOffset = point
		}
		
		/// 小于时
		if indexPath.section <= minChapter {
			
			/// 书籍顶部
			if chapterIndex <= (totalChapterNumber / 2 + 1) {
				chapterOffset = 0
				
				if chapterIndex == 0 {return}
				
				collectionView.performSelector(onMainThread: #selector(collectionView.reloadData),
				                                with: nil,
				                                waitUntilDone: false)
				let y = collectionView.contentOffset.y
				let of = y - UIScreen.main.bounds.size.height * CGFloat((indexPath.section - 1))
				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(chapterIndex - 1) + of)
				collectionView.contentOffset = point
				
			} else {
				chapterOffset = chapterIndex - (totalChapterNumber / 2 + 1)
				collectionView.performSelector(onMainThread: #selector(collectionView.reloadData),
				                                with: nil,
				                                waitUntilDone: false)
				let y = collectionView.contentOffset.y
				let of = y - UIScreen.main.bounds.size.height * CGFloat((indexPath.section - 1))
				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * 10 + of)
				collectionView.contentOffset = point
			}
		}
		print("--------------- 3");
	}
	
}


