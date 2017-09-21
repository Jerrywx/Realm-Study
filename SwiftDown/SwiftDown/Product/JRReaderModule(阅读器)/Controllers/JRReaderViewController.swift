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
	
	
	/// 头部View
	let topView: JRBookReadTopView = JRBookReadTopView.bookReadTopView()
	/// 底部View
	let bottomView: JRBookReadBottomView = JRBookReadBottomView.bookReaedBottomView()
	
	
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

			/// 下载第一章节
			let model:JRBookChapterModel = list.first!
			let chapters = [list[0], list[1], list[2]]

			/// 下载前三章节
			JRBookServer.loadChapter(bookId: model.bookId!, chapters: chapters, completion: { (isSuccess:Bool) in
				self.collectionView?.reloadData()
			})
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
//			collectionView?.contentInsetAdjustmentBehavior = .never
		}
		
		/// 添加点击事件
		let tap = UITapGestureRecognizer(target: self, action: #selector(openControlView))
		collectionView?.addGestureRecognizer(tap)
		
		/// 添加 控制view
		view.addSubview(topView)
		view.addSubview(bottomView)
	}

	/// 打开控制View
	func openControlView() {
		topView.appear = !topView.appear;
		bottomView.appear = !bottomView.appear;
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
		
		guard
		let list = chapterList
		else {
			return 1
		}
		
		let model = list[section + chapterOffset]
		
		if model.pageList != nil && (model.pageList?.count)! > 0 {
			return (model.pageList?.count)!
		}
		
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
				
				if model.isDowload {
					
					if (model.pageList?.count)! > indexPath.row {
						let m:JRBookPageModel = model.pageList![indexPath.row]
						cell.content.attributedText = m.aContent
						
						cell.label.text = "\((model.name)!) - \(indexPath.row + 1)/\((model.pageList?.count)!)"
						
					} else {
						cell.content.attributedText = nil
					}
				} else {
					cell.content.attributedText = nil
				}
				
			} else {
				cell.indexPath = indexPath
			}
		} else {
			cell.indexPath = indexPath
		}
		
		return cell
	}

	func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
//		if indexPath.section == 0 {
//			collectionView.reloadData()
//		}
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

	///
	func collectionView(_ collectionView: UICollectionView, 
	                    willDisplay cell: UICollectionViewCell, 
	                    forItemAt indexPath: IndexPath) {
		
		///
		print("--------- \(indexPath)")
		
		guard
			let cel: JRReadPageCell = cell as? JRReadPageCell
			else { return }
		guard
			let chapterIndex = cel.index
		else { return }

		/// 大于时
		if indexPath.section >= maxChapter {
			// 21 15
			chapterOffset = chapterIndex - (totalChapterNumber / 2 + 1)
			collectionView.performSelector(onMainThread: #selector(collectionView.reloadData),
			                                with: nil,
			                                waitUntilDone: false)
//			let y = collectionView.contentOffset.y
//			let of = y - UIScreen.main.bounds.size.height * CGFloat((indexPath.section - 1))
			
			let pageCount = topPage(section: indexPath.section, count: 11) - 1
//			let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(pageCount) + of)
			let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(pageCount))
			collectionView.contentOffset = point
			
			
//			let indexPath = IndexPath(row: 0, section: 11)
//			collectionView.scrollToItem(at: indexPath, at: .top, animated: false)
//
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
//				let y = collectionView.contentOffset.y
//				let of = y - UIScreen.main.bounds.size.height * CGFloat((indexPath.section - 1))
//				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(chapterIndex - 1) + of)
				
				let pageCount = topPage(section: indexPath.section, count: chapterIndex)
				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(pageCount))
				collectionView.contentOffset = point
				
			} else {
				chapterOffset = chapterIndex - (totalChapterNumber / 2 + 1)
				collectionView.performSelector(onMainThread: #selector(collectionView.reloadData),
				                                with: nil,
				                                waitUntilDone: false)
//				let y = collectionView.contentOffset.y
				
				let pageCount = topPage(section: indexPath.section, count: 12)
				let point = CGPoint(x: 0, y: UIScreen.main.bounds.size.height * CGFloat(pageCount))
				collectionView.contentOffset = point
			}
		}
	
		//// 加载未加载章节
		loadNewChapter(index: indexPath.section + chapterOffset)
		
	}
	
	func topPage(section: Int, count: Int) -> Int {
		
		var numb = 0
		
		for i in chapterOffset..<chapterOffset + count {
			let model = chapterList?[i]
			
			if model?.pageList == nil {
				numb = numb + 1
			} else {
				numb = numb + (model?.pageList?.count)!
			}
		}
		return numb
	}
	
	
	/// 加载指定章节
	///
	/// - Parameter index: 章节索引
	func loadNewChapter(index: Int) {
		
		///
		let model:JRBookChapterModel = (chapterList?[index])!
		
		if model.isDowload {
			return
		}
		
		JRBookServer.loadChapter(bookId: model.bookId!, chapters: [model], completion: { (isSuccess:Bool) in

			var ind = index
			if index >= self.maxChapter {
				ind = index - self.chapterOffset
			}
			
			let indexSet = NSIndexSet(index: ind)
			print("================== AAA \(indexSet)")
			
			self.collectionView?.performBatchUpdates({
				self.collectionView?.reloadSections(indexSet as IndexSet)
			}, completion: nil)
		})
		
	}
	
}








