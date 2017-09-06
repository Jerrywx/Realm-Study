//
//  Dictionary+Extension.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/6.
//  Copyright © 2017年 王潇. All rights reserved.
//

import Foundation

extension Dictionary {
	
	/// 字符串转字典
	///
	/// - Parameter string: 要转换字典的字符串
	/// - Returns: 返回字典
	static func dictionaryWith(string: String) -> [String : Any]? {
		
		/// 字符串转 Data
		guard
		let data = string.data(using: .utf8)
		else {
			return nil
		}
		
		/// Data 转 字典
		let jsDict = try? JSONSerialization.jsonObject(with: data, options: .mutableContainers)
		
		/// 返回字典
		return jsDict as? [String : Any]
	}
	
	
}
