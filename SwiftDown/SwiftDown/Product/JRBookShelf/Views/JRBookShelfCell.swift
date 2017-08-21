//
//  JRBookShelfCell.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/17.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import SDWebImage

class JRBookShelfCell: UICollectionViewCell {
	
	/// 封面
	var imageView: UIImageView?
	/// 未读标识
	var tipImage: UIImageView?
	/// 书名
	var bookName: UILabel?
	var bookName2: UILabel?
	/// 更新章节
	var updateTip: UILabel?
	/// 更新时间
	var updateTime: UILabel?
	/// 阅读记录
	var readLog: UILabel?
	/// 分隔线
	let line = UIView()
	
	
	var bookModel: JRInternalBookModel? {
		didSet {
			
			guard
				let model: JRInternalBookModel = bookModel
			else {
				return
			}
			
			bookName?.text = model.name
			bookName2?.text = model.name
			
			imageView?.sd_setImage(with: NSURL(string: model.picUrl!)! as URL, completed: nil)
			
		}
	}
	
	
	var layout: UICollectionViewLayout? {
		didSet {
			if layout == nil {
				return
			}
			
//			let newL = layout as! UICollectionViewFlowLayout
//			
//			let frame = CGRect(x: 0, y: 15,
//			                   width: newL.itemSize.width,
//			                   height: newL.itemSize.width / 54 * 72)
//			
//			/// Item
//			if newL.minimumInteritemSpacing == 20 {
//				
//				
//				bookName2?.frame = CGRect(x: 0, y: 15 + newL.itemSize.width / 54 * 72 + 2,
//				                          width: newL.itemSize.width, height: 14)
//				UIView.animate(withDuration: 0.3, animations: {
//					
//					self.itemLayout(x: newL.itemSize.width, frame: frame)
//				})
//				
//			} else {
//				/// Cell
//				UIView.animate(withDuration: 0.3, animations: {
//					self.lineLayout()
//				})
//			}
		}
	}
	
	override init(frame: CGRect) {
		super.init(frame: frame)
		setupUI()
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
}

// MARK: - Description
extension JRBookShelfCell {
	
	/// 初始化界面
	func setupUI() {
		
//		backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		
		/// 书籍封面
		imageView = UIImageView(frame: CGRect(x: 20, y: (111 - 72) * 0.5, width: 54, height: 72))
		contentView.addSubview(imageView!)

		/// 未读提示
		tipImage = UIImageView(frame: CGRect(x: 94, y: 27, width: 10, height: 10))
		tipImage?.layer.cornerRadius = 5
		tipImage?.backgroundColor = #colorLiteral(red: 0.9865261844, green: 0.275442052, blue: 0.2275855754, alpha: 1)
		contentView.addSubview(tipImage!)
		
		/// 书籍名称
		bookName = UILabel(frame: CGRect(x: 110, y: 25, width: 200, height: 14))
		bookName?.text = "书籍名称"
		bookName?.font = UIFont.systemFont(ofSize: 14)
		contentView.addSubview(bookName!)
		
		bookName2 = UILabel(frame: CGRect.zero)
		bookName2?.text		= "书籍名称"
		bookName2?.font		= UIFont.systemFont(ofSize: 14)
		bookName2?.alpha	= 0
		bookName2?.textAlignment = .center
		contentView.addSubview(bookName2!)
		
		/// 更新提醒
		updateTip = UILabel(frame: CGRect(x: 94, y: 50, width: 200, height: 14))
		updateTip?.text			= "最新:第636章 掉不懂的饼"
		updateTip?.font			= UIFont.systemFont(ofSize: 11)
		updateTip?.textColor	= #colorLiteral(red: 0.501960814, green: 0.501960814, blue: 0.501960814, alpha: 1)
		contentView.addSubview(updateTip!)
		
		/// 更新时间
		updateTime = UILabel(frame: CGRect(x: 94, y: 75, width: 200, height: 12))
		updateTime?.textColor = #colorLiteral(red: 0.6000000238, green: 0.6000000238, blue: 0.6000000238, alpha: 1)
		updateTime?.font = UIFont.systemFont(ofSize: 12)
		updateTime?.text = "3个月前更新"
		contentView.addSubview(updateTime!)
		
		/// 阅读进度
		let x = UIScreen.main.bounds.size.width - 20 - 80
		readLog = UILabel(frame: CGRect(x: x, y: 75, width: 80, height: 12))
		readLog?.text = "3/142"
		readLog?.textColor = #colorLiteral(red: 0.6000000238, green: 0.6000000238, blue: 0.6000000238, alpha: 1)
		readLog?.font = UIFont.systemFont(ofSize: 12)
		readLog?.textAlignment = .right
		contentView.addSubview(readLog!)
		
		
		line.frame = CGRect(x: 20, y: 110, width: UIScreen.main.bounds.width, height: 0.5)
		line.backgroundColor = UIColor.black.withAlphaComponent(0.1)
		contentView.addSubview(line)
		
		imageView?.backgroundColor = #colorLiteral(red: 0.8039215803, green: 0.8039215803, blue: 0.8039215803, alpha: 1)
		
		
		
	}
	
	
	override func willTransition(from oldLayout: UICollectionViewLayout, to newLayout: UICollectionViewLayout) {

		let newL = newLayout as! UICollectionViewFlowLayout

		let frame = CGRect(x: 0, y: 15,
		                   width: newL.itemSize.width,
		                   height: newL.itemSize.width / 54 * 72)
		
		/// Item
		if newL.minimumInteritemSpacing == 20 {
			
			
			bookName2?.frame = CGRect(x: 0, y: 20 + newL.itemSize.width / 54 * 72 + 2,
			                          width: newL.itemSize.width, height: 14)
			UIView.animate(withDuration: 0.3, animations: {
				
				self.itemLayout(x: newL.itemSize.width, frame: frame)
			})
			
		} else {
			/// Cell
			UIView.animate(withDuration: 0.3, animations: {
				self.lineLayout()
			})
		}
	}
	
	/// -----
	func lineLayout() {
		self.imageView?.frame = CGRect(x: 20, y: (111 - 72) * 0.5, width: 54, height: 72)
		self.tipImage?.frame = CGRect(x: 94, y: 27, width: 10, height: 10)
		self.line.alpha = 1
		self.bookName?.alpha = 1
		self.updateTip?.alpha = 1
		self.bookName2?.alpha = 0
		self.updateTime?.alpha = 1
		self.readLog?.alpha = 1
	}
	
	/// ||||
	func itemLayout(x: CGFloat, frame: CGRect) {
		self.imageView?.frame = frame
		
		self.tipImage?.frame = CGRect(x: x - 5,
		                              y: 10,
		                              width: 10, height: 10)
		
		self.line.alpha = 0
		self.bookName?.alpha = 0
		self.bookName2?.alpha = 1
		self.updateTip?.alpha = 0
		self.updateTime?.alpha = 0
		self.readLog?.alpha = 0
	}
	
	
	override func didTransition(from oldLayout: UICollectionViewLayout, to newLayout: UICollectionViewLayout) {
//		layout = newLayout
	}
	
	override func layoutSubviews() {
		super.layoutSubviews()
//		print("----------- \(String(describing: bookName?.alpha))")
//		print("-=============================")
		
		
		
	}
}


