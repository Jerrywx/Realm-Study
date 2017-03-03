//
//  JRNetWorkManager.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/2.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import Alamofire

enum JRNetWorkMethond {
	case GET
	case POST
}

/// 网络管理工具
class JRNetWorkManager: NSObject {

	/// 网络单粒
	static let shared = JRNetWorkManager()
	
}

// MARK: - 公共上行参数
extension JRNetWorkManager {
	
}

// MARK: - 网络工具
extension JRNetWorkManager {
	
	func myRequest(_ url: URLConvertible,
	               method: HTTPMethod = .get,
	               parameters: Parameters? = nil,
	               encoding: ParameterEncoding = URLEncoding.default,
	               headers: HTTPHeaders? = nil,
	               completion: @escaping (_ json: AnyObject?, _ isSuccess: Bool) -> ()) {
		
		Alamofire.request(url, method: method,
		                  parameters: parameters,
		                  encoding: encoding,
		                  headers: headers).responseJSON { (response) in
							print(response.result)
							completion(response.result.value as AnyObject?, true)
		}
	}
	
	/// 注册token
	///
	/// - Parameter token: token
	func registerUserToken(token: String) {
		
	}
	
}

// MARK: - 网络测试
extension JRNetWorkManager {
	
	func testNetWork() {
		JRNetWorkManager.shared.myRequest("https://api.weibo.com/2/statuses/home_timeline.json?access_token=2.00fxAYtCVXkvuB58b1c81191OUuc7E") { (json, isSuccess) in
			if isSuccess {
				print("成功")
				//				print(String(data: json as! Data, encoding: .utf8)!)
				print(json!)
			}
		}
	}
}

