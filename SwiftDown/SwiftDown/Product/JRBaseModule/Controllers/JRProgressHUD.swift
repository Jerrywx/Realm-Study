  //
//  JRProgressHUD.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/18.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import MBProgressHUD

class JRProgressHUD: NSObject {

}

// MARK: - Loading HUD
extension JRProgressHUD {
	
	/// 显示 Loading 界面
	///
	/// - Parameters:
	///   - toView: 将要显示 loading 的View 默认主 window
	///   - animation: 是否动画  默认是
	///   - hideAll: 是否隐藏之前的 loading 默认隐藏
	///   - enabled: loading 是否可touch 默认不可以
	static func showLoading(toView: UIView = UIApplication.shared.keyWindow!,
	                        animation: Bool = true, 
	                        hideAll: Bool = true, 
	                        enabled: Bool = false) {
		
		if hideAll {
			/// 隐藏之前显示的 loading
		}
		
		let loading = MBProgressHUD.showAdded(to: toView, animated: animation)
		loading.isUserInteractionEnabled = enabled
	}
	
	/// 隐藏 Loading 界面
	///
	/// - Parameters:
	///   - fromView: 隐藏 Loadong 的界面 默认主 window
	///   - animationed: 是否动画 默认是
	static func hideLoading(fromView: UIView = UIApplication.shared.keyWindow!,
	                        animationed: Bool = true) {
		MBProgressHUD.hide(for: fromView, animated: animationed)
	}
	
}

// MARK: - Toast HID
extension JRProgressHUD {
	
	/// 显示 Toast
	///
	/// - Parameters:
	///   - message: Toast 内容
	///   - loading: 是否包含 loading
	///   - toView: 将要显示 Toast 的界面	默认主window
	///   - delay: Toast 显示时间 默认: 1.5s
	///   - animationed: Toast 显示是否有动画效果 默认:trues
	///   - hideAll: Toadt 显示前是否隐藏其他 提示 默认:trues
	static func shwoToast(message: String,
	                      loading: Bool = false,
	                      toView: UIView = UIApplication.shared.keyWindow!,
	                      delay:TimeInterval = 1.5,
	                      animationed: Bool = true,
	                      hideAll: Bool = true) {
		
		/// 显示内容为空 退出
		if message.lengthOfBytes(using: .utf8) == 0 {
			return
		}
		
		/// 是否隐藏其他
		if hideAll {
			JRProgressHUD.hideLoading(fromView: toView, animationed: animationed)
		}
		
		/// 创建 Toast
		let toast = MBProgressHUD.showAdded(to: toView, animated: animationed)
		
		/// 是否显示 loading
		if false == loading {
			toast.mode = .text
		}
		
		/// 设置 Toast
		toast.isUserInteractionEnabled = false
		toast.label.text = message
		/// 隐藏
		toast.hide(animated: animationed, afterDelay: delay)
	}
}









