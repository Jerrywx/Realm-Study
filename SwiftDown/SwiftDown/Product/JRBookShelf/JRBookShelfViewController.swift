//
//  JRBookShelfViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import Alamofire

class JRBookShelfViewController: JRBaseViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }

	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		/// 网络测试
//		JRNetWorkManager.shared.testNetWork()
		/// 公共上行基础信息测试
		print(JRNetWorkURL.getPublicParam(param: ["TEST" : "哈哈哈"]))
		/// 测试参数签名
//		print(JRNetWorkURL.getParamSign(param: JRNetWorkURL.publicUpwardConcatenation()))
	}
	
}
