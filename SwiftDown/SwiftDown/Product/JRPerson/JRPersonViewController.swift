//
//  JRPersonViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRPersonViewController: JRBaseViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }
	
	///
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		print(JRNetWorkURL.getWebPublicParam(urlString: "http://app.zongheng.com/ios/index") ?? "//")
	}
}
