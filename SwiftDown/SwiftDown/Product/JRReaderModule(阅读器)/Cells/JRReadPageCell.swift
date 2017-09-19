//
//  JRReadPageCell.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/9/16.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import YYText

class JRReadPageCell: UICollectionViewCell {

//	let label = UILabel(frame: UIScreen.main.bounds)
	let label = UILabel(frame: CGRect(x: 0, y: 0, width: UIScreen.main.bounds.size.width, height: 40))
	
	let content = YYLabel(frame: CGRect(x: 20, y: 40,
	                                    width: UIScreen.scrren_W() - 40,
	                                    height: UIScreen.screen_H() - 80))
	
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
		
		content.numberOfLines = 0
		content.displaysAsynchronously = true
		content.textVerticalAlignment = .top
		contentView.addSubview(content)
		
	}
}

