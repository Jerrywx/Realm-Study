//
//  JRNetWorkURL.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/2.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

//import <CommonCrypto/CommonCrypto.h>

class JRNetWorkURL: NSObject { }

// MARK: - 网络请求上行参数
extension JRNetWorkURL {
	
	/// 获取网络请求上行参数
	///
	/// - Parameter param: 功能参数
	/// - Returns: 请求上行参数
	static func getPublicParam(param: [String : Any]?) -> [String:Any] {

		/// 获取基础参数
		var mParam = publicUpwardConcatenation()
		/// 合并参数
		for (k, v) in param ?? [:]{
			mParam.updateValue(v, forKey: k)
		}
		mParam["sig"] = getParamSign(param: mParam);
		/// 中文转义
		let keys = mParam.keys
		for key in keys {
			let value: String = mParam[key]! as! String
			mParam.updateValue(value.addingPercentEncoding(withAllowedCharacters: .urlQueryAllowed)!,
			                   forKey: key)
		}
		return mParam
	}
	
	/// 获取公共上行参数
	///
	/// - Returns: 返回客户端基本信息
	static func publicUpwardConcatenation() -> [String : Any] {
		
		var publicUpwardDict: [String:String] = [:];
		
		publicUpwardDict["channelType"]		= "AppStore"
		publicUpwardDict["channelId"]		= "0"
		publicUpwardDict["installId"]		= "5d9252cd8cf00290e07c0618ae143e5869280f5f"
		publicUpwardDict["modelName"]		= "iPhoneSimulator"
		publicUpwardDict["brand"]			= "Apple"
		publicUpwardDict["model"]			= "iPhoneSimulator"
		publicUpwardDict["os"]				= "ios"
		publicUpwardDict["osVersion"]		= "9.3"
		publicUpwardDict["clientVersion"]	= "4.0.0"
		publicUpwardDict["screenW"]			= "1242"
		publicUpwardDict["screenH"]			= "2208"
		publicUpwardDict["userId"]			= "10"
		publicUpwardDict["appId"]			= "ZHKXS"
		publicUpwardDict["api_key"]			= "27A28A4D4B24022E543E"
		
		return publicUpwardDict
	}
	
	/// 参数签名
	///
	/// - Parameter param: 请求参数
	/// - Returns: 参数签名
	static func getParamSign(param: [String : Any]) -> String {
		
		var sign: String = String()
		let keys: Array = param.keys.sorted(by: {$0 < $1})
		
		for i in 0..<keys.count {
			let key = keys[i]
			if(i == 0){
				sign.append(String(format: "%@=%@", key, param[key]! as! String))
			}else{
				sign.append(String(format: "&%@=%@", key, param[key]! as! String))
			}
		}
		return JRIgnoreFile.encryptSign(sign: sign)
	}
}

// MARK: - webView加载参数
extension JRNetWorkURL {
	
	/// 获取web上行参数
	///
	/// - Parameter urlString: web URL
	/// - Returns: 返回添加上行参数后的 url
	static func getWebPublicParam(urlString: String) -> String? {
		
		/// 根据字符串 创建 url
		guard let url = URL(string: urlString) else {
			return nil
		}
		
		/// 截取url参数数组
		let param: [String]? = url.query?.components(separatedBy: "&")
		var params: [String : Any] = [String : Any]()
		
		/// 检测 参数 合法性
		if (param != nil) {
			for item in param! {
				
				let tmArray	= item.components(separatedBy: "=")
				
				if tmArray.count == 2 {
					let key		= tmArray[0] as String
					let value	= tmArray[1] as String
					params[key] = value
				}
			}
		}
		
		/// 获取 web上行参数
//		let webParam = combineWithPublicParam(param: params)
		let webParam = publicUpwardConcatenation()
		
		/// 参数排序部分
		var newString = urlString
		if (url.query == nil) {
			newString += "?"
		} else {
			newString += "&"
		}
		
		var array: [String] = [String]()
		
		for (key, value) in webParam {
			array.append("\(key)=\(value)")
		}
	
		newString += array.joined(separator: "&")
		
		return newString
	}
	
	/// 拼接webView 参数 与 公共上行参数
	///
	/// - Parameter param: webView 参数
	/// - Returns: web上行参数
	static func combineWithPublicParam(param: [String : Any]) -> [String : Any] {
		
		/// 1. 获取公共上行参数
		var publicParam = publicUpwardConcatenation()
		
		/// 2. 拼接参数
		for (key, value) in param {
			publicParam[key] = value
		}
		
		/// 3. 返回 web上行参数
		return publicParam
	}
	
	
}


// MARK: - 加密方法
// 注: 在 bridge 文件中引入 #import <CommonCrypto/CommonCrypto.h>
extension JRNetWorkURL {
	// Use of unresolved identifier 'CC_MD5'
	static func md5String(str:String) -> String{
		let cStr = str.cString(using: String.Encoding.utf8);
		let buffer = UnsafeMutablePointer<UInt8>.allocate(capacity: 16)
		CC_MD5(cStr!,(CC_LONG)(strlen(cStr!)), buffer)
		let md5String = NSMutableString();
		for i in 0 ..< 16{
			md5String.appendFormat("%02x", buffer[i])
		}
		free(buffer)
		return md5String as String
	}
}

