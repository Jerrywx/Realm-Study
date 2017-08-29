//
//  JRBookCoverTransition.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/29.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverTransition: NSObject, UIViewControllerTransitioningDelegate {

	var fromFrame: CGRect?
	
	var imgView: UIImageView?
	
	/// presented 动画
	func animationController(forPresented presented: UIViewController, presenting: UIViewController, source: UIViewController) -> UIViewControllerAnimatedTransitioning? {

		let animation = JRBookCoverTransitionAnimated()
		animation.fromFrame = fromFrame
		return animation
	}
	
	/// dismissed 动画
	func animationController(forDismissed dismissed: UIViewController) -> UIViewControllerAnimatedTransitioning? {
		let animation = JRBookCoverTransitionAnimated()
		animation.fromFrame = fromFrame
		return animation
	}
	
	/// 转场处理
	func presentationController(forPresented presented: UIViewController, presenting: UIViewController?, source: UIViewController) -> UIPresentationController? {
		
		let presentation = JRBookCoverPresentation(presentedViewController: presented, presenting: presenting)
		presentation.imgView = imgView
		return presentation;
	}
	
}
