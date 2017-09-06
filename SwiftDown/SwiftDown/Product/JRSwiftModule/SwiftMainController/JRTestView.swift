//
//  JRTestView.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRTestView: UIView {

    /*
    // Only override draw() if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func draw(_ rect: CGRect) {
        // Drawing code
    }
    */
	
//	override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
//		print("======== 子View")
//	}
	
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		print("======== 子View")
	}

}
