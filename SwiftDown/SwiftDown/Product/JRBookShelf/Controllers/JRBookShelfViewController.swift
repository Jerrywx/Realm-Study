//
//  JRBookShelfViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit
import Alamofire
import MBProgressHUD

class JRBookShelfViewController: JRBaseViewController {

	/// tableView
	var tableView:UITableView?

	override func viewDidLoad() {
        super.viewDidLoad()
		
		/// 初始化界面
		setupUI()
    }
}


// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRBookShelfViewController: UITableViewDataSource, UITableViewDelegate {
	
	/// UITableViewDataSource
	func numberOfSections(in tableView: UITableView) -> Int {
		return 4
	}
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 4
	}

	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		
		let cell = tableView.dequeueReusableCell(withIdentifier: "selfCell")
		
		cell?.textLabel?.text = "selfCell-" + "\(indexPath.row)"
		
		return cell!
	}
	
	/// UITableViewDelegate
	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
		
		/// 点击状态
		MBProgressHUD.showAdded(to: view, animated: true)
		
		/// Lodaing
		let delay = DispatchTime.now() + DispatchTimeInterval.seconds(4)
		DispatchQueue.main.asyncAfter(deadline: delay) {
			MBProgressHUD.hide(for: self.view, animated: true)
		}
		
		/// 加载内置书
		testNetWork()
	}
}


// MARK: - 初始化界面
extension JRBookShelfViewController {
	
	/// 初始化界面
	fileprivate func setupUI() {
		
		view.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
		
		tableView = UITableView(frame: view.bounds, style: .grouped)
		tableView?.rowHeight  = 66
		tableView?.delegate   = self
		tableView?.dataSource = self
		tableView?.register(UITableViewCell.self, forCellReuseIdentifier: "selfCell")
		view.addSubview(tableView!)
	}
}


// MARK: - 测试部分
extension JRBookShelfViewController {

	/// 点击屏幕
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		/// 网络测试
		//		JRNetWorkManager.shared.testNetWork()
		/// 公共上行基础信息测试
		testNetWork(param: JRNetWorkURL.getPublicParam(param: ["forumId" : "116320"]))
	}
	
	/// 网络请求
	func testNetWork(param:[String : Any] = [:]) {
		/// http://api1.zongheng.com/iosapi/forum/detail 圈子
		/// http://api1.zongheng.com/iosapi/book/builtInBook 内置书
		JRNetWorkManager.shared.myRequest("http://api1.zongheng.com/iosapi/book/builtInBook",
		                                  method: HTTPMethod.post,
		                                  parameters: param,
		                                  encoding: URLEncoding.default,
		                                  headers: nil) { (json, isSuccess) in
											print("成功")
											if let js = json {
												print(js)
											}
		}
	}
}

