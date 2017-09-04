//
//  JRBookCoverController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/29.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverController: JRBaseViewController {

	/// 返回按钮
	let backBtn = UIButton()
	
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

	/// view touchBegan事件
//	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
//		dismiss(animated: true, completion: nil)
//	}

	/// view 显示完成
	override func viewDidAppear(_ animated: Bool) {
		super.viewDidAppear(animated)
		backBtn.isHidden = false
	}

}





extension JRBookCoverController {
	
	/// 初始化界面
	func setupUI() {
		
		/// 设置书籍名称
		title = bookName
		
		/// 书封图片
		bookImageView = UIImageView(frame: presentingFrame!)
		
//		bookImageView = UIImageView(frame: CGRect(x: 0, y: 0,
//		                                          width: (presentingFrame?.size.width)!,
//		                                          height: (presentingFrame?.size.height)!))
		view.addSubview(bookImageView!)
		bookImageView?.backgroundColor = UIColor.red
		bookImageView?.image = bookImage
		
		
		/// 返回按钮
		backBtn.frame = CGRect(x: 25, y: 25, width: 40, height: 30)
		backBtn.setTitle("返回", for: .normal)
		backBtn.setTitleColor(#colorLiteral(red: 0.2392156869, green: 0.6745098233, blue: 0.9686274529, alpha: 1), for: .normal)
		view.addSubview(backBtn)
		backBtn.isHidden = true
		backBtn.addTarget(self, action: #selector(backAction(sender:)), for: .touchUpInside)
		
	}
	
	/// 返回操作
	func backAction(sender: UIButton) {
		dismiss(animated: true, completion: nil)
		sender.isHidden = true
	}
	
}



