//
//  JRNetWorkURL.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/2.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRNetWorkURL: NSObject { }

// MARK: - 公共上行参数
extension JRNetWorkURL {
	
	
	static func getPublicParam() -> [String:Any] {
		
		
		
		return [:]
	}
	
	/// 获取公共伤上行基础参数
	///
	/// - Returns: 返回客户端基本信息
	static func publicUpwardConcatenation() -> [String : String] {
		
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
	static func getParamSign(param: [String : String]) -> String {
		
		var sign: String = String()
		let keys: Array = param.keys.sorted(by: {$0 > $1})
		for i in 0..<keys.count {
			let key = keys[i]
			if(i == 0){
				sign.append(String(format: "%@=%@", key, param[key]!))
			}else{
				sign.append(String(format: "&%@=%@", key, param[key]!))
			}
		}
		return sign
	}
	// userId=10&screenW=1242&screenH=2208&osVersion=9.3&os=ios&modelName=iPhoneSimulator&model=iPhoneSimulator&installId=5d9252cd8cf00290e07c0618ae143e5869280f5f&clientVersion=4.0.0&channelType=AppStore&channelId=0&brand=Apple&appId=ZHKXS&api_key=27A28A4D4B24022E543E
}

