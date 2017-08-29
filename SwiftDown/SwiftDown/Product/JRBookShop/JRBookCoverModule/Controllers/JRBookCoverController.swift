//
//  JRBookCoverController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/29.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverController: JRBaseViewController {

	/// 书籍封面图
	var bookImageView: UIImageView?
	
	/// 转场初始位置
	var presentingFrame: CGRect?

	/// 书籍封面
	var bookImage: UIImage?
	
	/// 书籍名称
	var bookName: String? {
		didSet {
			title = bookName
		}
	}
	
    override func viewDidLoad() {
        super.viewDidLoad()

		setupUI()
    }

	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		dismiss(animated: true, completion: nil)
	}
	
}

extension JRBookCoverController {
	
	/// 初始化界面
	func setupUI() {
		
		/// 设置书籍名称
		title = bookName
		
		/// 
		bookImageView = UIImageView(frame: CGRect(x: 0, y: 0,
		                                          width: (presentingFrame?.size.width)!,
		                                          height: (presentingFrame?.size.height)!))
		view.addSubview(bookImageView!)
		bookImageView?.backgroundColor = UIColor.red
		bookImageView?.image = bookImage
		
		
	}
	
}



