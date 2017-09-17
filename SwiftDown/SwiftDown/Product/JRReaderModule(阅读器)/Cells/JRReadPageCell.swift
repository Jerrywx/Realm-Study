//
//  JRReadPageCell.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRReadPageCell: UICollectionViewCell {

//	let label = UILabel(frame: UIScreen.main.bounds)
	let label = UILabel(frame: CGRect(x: 0, y: 0, width: UIScreen.main.bounds.size.width, height: 300))
	
	/// 章节索引
	var index: Int?
	
	/// 章节模型
	var chapterModel: JRBookChapterModel?
	
	/// cell 索引
	var indexPath: IndexPath? {
		didSet {
			label.text = "第 -- \(indexPath?.section ?? 0)"
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
// 初始化界面
extension JRReadPageCell {
	// 初始化界面
	func setupUI() {
		
		///
		contentView.addSubview(label)
		label.font = UIFont.systemFont(ofSize: 22)
		label.textAlignment = .center
		label.numberOfLines = 0
		label.backgroundColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
	}
}

