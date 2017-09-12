//
//  JRTableView.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRTableView: UITableView, UIGestureRecognizerDelegate {

	override init(frame: CGRect, style: UITableViewStyle) {
		super.init(frame: frame, style: style)
		self.panGestureRecognizer.delegate = self
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	func gestureRecognizer(_ gestureRecognizer: UIGestureRecognizer,  shouldRecognizeSimultaneouslyWith otherGestureRecognizer: UIGestureRecognizer) -> Bool {
		return true
	}
}

// MARK: - <#Description#>
extension JRTableView {
	
	
	
}

