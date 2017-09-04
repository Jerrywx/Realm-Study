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
	
	/// ===========
	/// 书封内容
	var tableView: UITableView?
	
	/// 书封头部
	var tableViewHeaeder = JRBookCoverHeader.bookHeaederView()
	
	
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
		
		
		print("===============================")
	}

}


extension JRBookCoverController {
	
	/// 初始化界面
	func setupUI() {
		
		/// 设置书籍名称
		title = bookName
		
		/// 返回按钮
		backBtn.frame = CGRect(x: 25, y: 25, width: 40, height: 30)
		backBtn.setTitle("返回", for: .normal)
		backBtn.setTitleColor(#colorLiteral(red: 0.2392156869, green: 0.6745098233, blue: 0.9686274529, alpha: 1), for: .normal)
		view.addSubview(backBtn)
		backBtn.isHidden = true
		backBtn.addTarget(self, action: #selector(backAction(sender:)), for: .touchUpInside)
		
		
		/// 书封 tableView
		let tFrame = CGRect(x: 0, y: 64, width: UIScreen.scrren_W(), height: UIScreen.screen_H() - 64)
		tableView = UITableView(frame: tFrame)
		tableView?.delegate		= self
		tableView?.dataSource	= self
		tableView?.tableHeaderView = tableViewHeaeder
		tableView?.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
		view.addSubview(tableView!)
		
		
		
		/// 书封图片
		bookImageView = UIImageView(frame: presentingFrame!)
		
		//		bookImageView = UIImageView(frame: CGRect(x: 0, y: 0,
		//		                                          width: (presentingFrame?.size.width)!,
		//		                                          height: (presentingFrame?.size.height)!))
		view.addSubview(bookImageView!)
		bookImageView?.backgroundColor = UIColor.red
		bookImageView?.image = bookImage
	}
	
	/// 返回操作
	func backAction(sender: UIButton) {
		dismiss(animated: true, completion: nil)
		sender.isHidden = true
	}
	
}

// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRBookCoverController: UITableViewDataSource, UITableViewDelegate {
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 20
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "cell")
		
		cell?.textLabel?.text = "cell - \(indexPath.row)"
		
		return cell!
	}
	
	
	func tableView(_ tableView: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
		
//		let array = tableView.indexPathsForVisibleRows
//		let firstIndexPath = array?.first
//		
//		//设置anchorPoint
//		cell.layer.anchorPoint = CGPoint(x: 0, y: 0.5)
//		//为了防止cell视图移动，重新把cell放回原来的位置
//		cell.layer.position = CGPoint(x: 0, y: cell.layer.position.y)
//		
//		
//		//设置cell 按照z轴旋转90度，注意是弧度
//		if ((firstIndexPath?.row)! < indexPath.row) {
//			cell.layer.transform = CATransform3DMakeRotation(CGFloat(M_PI_2), 0, 0, 1.0);
//		}else{
//			cell.layer.transform = CATransform3DMakeRotation(-(CGFloat)(M_PI_2), 0, 0, 1.0);
//		}
//		cell.alpha = 0.0;
//		UIView.animate(withDuration: 1) { 
//			cell.layer.transform = CATransform3DIdentity;
//			cell.alpha = 1.0;
//		}

		
		
		let initialDelay: CGFloat = 0.2
		let stutter: CGFloat = 0.06

		let r = CGFloat(indexPath.row)
		let delay = initialDelay + (r * stutter)
		
//		let cardCell = cell;
		
//		cell.contentView.transform =  CGAffineTransform(translationX: UIScreen.scrren_W(), y: 0);
		cell.contentView.transform =  CGAffineTransform(translationX: 0, y: 400);
		
		
		UIView.animate(withDuration: 1.0,
		               delay: TimeInterval(delay), 
		               options: UIViewAnimationOptions(rawValue: 0), animations: {
			cell.contentView.transform = CGAffineTransform.identity
		}, completion: nil)
		
		
//		UIView.animate(withDuration: 1.5,
//					   delay: TimeInterval(delay),
//					   usingSpringWithDamping: 0.0,
//					   initialSpringVelocity: 0,
//					   options: UIViewAnimationOptions(rawValue: 0),
//					   animations: {
//
//			cell.contentView.transform = CGAffineTransform.identity;
//
//		}, completion: nil)
		
//		UIView.animate(withDuration: 1, 
//		               delay: TimeInterval(delay),
//		               usingSpringWithDamping: 0.0,
//		               initialSpringVelocity: 0, 
//		               options: UIViewAnimationOptions(rawValue: 0), 
//		               animations: {
//						
//			cell.contentView.transform = CGAffineTransform.identity;
//						
//		}, completion: nil)
		
		
		
//		[UIView animateWithDuration:1. delay:initialDelay + ((indexPath.row) * stutter) usingSpringWithDamping:0.6 initialSpringVelocity:0 options:0 animations:^{
//			cardCell.contentView.transform = CGAffineTransformIdentity;
//			} completion:NULL];
		
//		if (isShowAnimation) {
//			UITableViewCell *cardCell = (UITableViewCell *)cell;
//			
//			cardCell.contentView.transform =  CGAffineTransformMakeTranslation(SCREEN_WIDTH, 0);
//			[UIView animateWithDuration:1. delay:initialDelay + ((indexPath.row) * stutter) usingSpringWithDamping:0.6 initialSpringVelocity:0 options:0 animations:^{
//				cardCell.contentView.transform = CGAffineTransformIdentity;
//				} completion:NULL];
//			
//			if (indexPath.row == 10) {
//				isShowAnimation = NO;
//			}
//		}
		
		
	}
	
	
	
}



