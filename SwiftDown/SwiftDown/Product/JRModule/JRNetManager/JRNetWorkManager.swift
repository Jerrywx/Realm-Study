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
	
	/// 普通网络请求
	///
	/// - Parameters:
	///   - url: 请求地址
	///   - method: 请求方法
	///   - parameters: 请求参数
	///   - encoding: 编码
	///   - headers: 请求头设置
	///   - completion: 请求完成回调
	func myRequest(_ url: URLConvertible,
	               method: HTTPMethod = .post,
	               parameters: Parameters? = nil,
	               encoding: ParameterEncoding = URLEncoding.default,
	               headers: HTTPHeaders? = nil,
	               completion: @escaping (_ json: AnyObject?, _ isSuccess: Bool) -> ()) {
		
		/// 注册token
		let header: HTTPHeaders = registerUserToken()
		
		/// 请求方法
		Alamofire.request(url, method: method,
		                  parameters: parameters,
		                  encoding: encoding,
		                  headers: header).responseJSON { (response) in
							print(response.result)
							completion(response.result.value as AnyObject?, true)
		}
	}
	
	/// 注册token
	///
	/// - Parameter token: token
	func registerUserToken(_ token: String = "") -> HTTPHeaders {
		
		/// 注册token
		let token = "NjY6ZWVhOTJjYWM5OThiYWM0ZWQ1ZjRkYzY1NmM0Mzg2Mjk="
		let tok = String(format: "Token token=\"%@\"", token)
		let header: HTTPHeaders = ["Authorization" : tok, "zhauth":token]
		/// 返回请求头设置
		return header
	}
	
}

// MARK: - 网络测试
extension JRNetWorkManager {
	
	/// 基本网络请求测试
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

