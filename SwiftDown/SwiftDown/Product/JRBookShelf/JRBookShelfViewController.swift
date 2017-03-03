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
		testNetWork(param: JRNetWorkURL.getPublicParam(param: ["forumId" : "116320"]))
	}
	
	func testNetWork(param:[String : String]) {
		
		let token = "NjY6ZWVhOTJjYWM5OThiYWM0ZWQ1ZjRkYzY1NmM0Mzg2Mjk="
		let tok = String(format: "Token token=\"%@\"", token)

		let header: HTTPHeaders = ["Authorization" : tok, "zhauth":token]
		
		JRNetWorkManager.shared.myRequest("http://api1.zongheng.com/iosapi/forum/detail", 
		                                  method: HTTPMethod.post,
		                                  parameters: param,
		                                  encoding: URLEncoding.default, 
		                                  headers: header) { (json, isSuccess) in
			print("成功")
			if let js = json {
				print(js)
			}
		}
	}
	
}
