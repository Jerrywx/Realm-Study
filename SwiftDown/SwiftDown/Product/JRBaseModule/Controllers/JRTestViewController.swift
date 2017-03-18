//
//  JRTestViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/17.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRTestViewController: JRBaseViewController {

	let label:UILabel = UILabel()
	
	
    override func viewDidLoad() {
        super.viewDidLoad()

		label.frame				= view.bounds
		label.numberOfLines		= 0
		view.addSubview(label)
    }
	
}
