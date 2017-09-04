//
//  JRBookCoverTransitionAnimated.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/29.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverTransitionAnimated: NSObject ,UIViewControllerAnimatedTransitioning {

	var fromFrame: CGRect?
	
	func transitionDuration(using transitionContext: UIViewControllerContextTransitioning?) -> TimeInterval {
		return 0.5
	}
	
	func animateTransition(using transitionContext: UIViewControllerContextTransitioning) {
		
		let containerView = transitionContext.containerView
		
		guard
			let fromVC = transitionContext.viewController(forKey: .from),
			let toVC = transitionContext.viewController(forKey: .to)
			else {
				return
		}
		
		let fromView = fromVC.view
		let toView = toVC.view
		let duration = transitionDuration(using: transitionContext)
		
		let width = UIScreen.main.bounds.size.width
		let height = UIScreen.main.bounds.size.height
		
		
		///
		if toVC.isBeingPresented {
			containerView.addSubview(toView!)
			
			toView?.backgroundColor = UIColor.clear
			
//			toView?.frame = fromFrame ?? CGRect.zero
			UIView.animate(withDuration: duration, animations: {
				toView?.frame = CGRect(x: 0, y: 0, width: width, height: height)
				toView?.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
			}, completion: { _ in
				transitionContext.completeTransition(!transitionContext.transitionWasCancelled)
			})
		}
		
		if fromVC.isBeingDismissed {
			UIView.animate(withDuration: duration, animations: {
				fromView?.backgroundColor = UIColor.clear
			}, completion: { _ in
				transitionContext.completeTransition(!transitionContext.transitionWasCancelled)
			})
		}
	}
	
}
