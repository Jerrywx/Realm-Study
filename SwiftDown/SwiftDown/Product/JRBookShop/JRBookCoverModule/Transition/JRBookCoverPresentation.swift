//
//  JRBookCoverPresentation.swift
//  SwiftDown
//
//  Created by wxiao on 2017/8/29.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookCoverPresentation: UIPresentationController {

	var imgView: UIImageView?
	
	override func presentationTransitionWillBegin() {
		
		let presentedVC = presentedViewController as! JRBookCoverController
		
		_ = presentedViewController.transitionCoordinator?.animate(alongsideTransition: { _ in

			var f = presentedVC.bookImageView?.frame
//			f?.origin.x = 0
//			f?.origin.y = 0
//			f?.size.width = UIScreen.main.bounds.size.width
//			f?.size.height = UIScreen.main.bounds.size.height
			
			let width: CGFloat = 135.0
			f?.origin.x = (UIScreen.main.bounds.size.width - width) * 0.5
			f?.origin.y = 72
			f?.size.width = width
			f?.size.height = (width / 3) * 4//(width / (presentedVC.bookImageView?.frame.width)!) * (presentedVC.bookImageView?.frame.height)!
			
			presentedVC.bookImageView?.frame = f!
		}, completion: nil)
		
		if imgView != nil {
			imgView?.isHidden = true
		}

	}
	
	override func presentationTransitionDidEnd(_ completed: Bool) {
		
	}
	
	override func dismissalTransitionWillBegin() {
		let presentedVC = presentedViewController as! JRBookCoverController
		_ = presentedViewController.transitionCoordinator?.animate(alongsideTransition: { _ in
			presentedVC.bookImageView?.frame = presentedVC.presentingFrame!
		}, completion: nil)
	}
	
	override func dismissalTransitionDidEnd(_ completed: Bool) {
		if imgView != nil {
			imgView?.isHidden = false
		}
	}
	
	override func containerViewWillLayoutSubviews() {
		
	}
	
	override func containerViewDidLayoutSubviews() {
		
	}
}
