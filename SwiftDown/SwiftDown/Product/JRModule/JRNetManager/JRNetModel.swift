//
//  JRNetModel.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/18.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

/// 网络请求状态
///
/// - unknown: 未知状态 [默认值]
/// - success: 请求成功
/// - error: 请求失败
enum JRNetWorkCode: String {
	case unknown = "0"		/// 未知
	case success = "200"		/// 成功
	case error   = "500"
}


class JRNetModel: NSObject {

	/*
	code = 200;
	message = ok;
	result =
	*/
	/// 请求状态
//	var code: JRNetWorkCode?
	var code: String?
	/// 请求状态信息
	var message: String?
	/// 请求结果
	var result: AnyObject?
	
}
