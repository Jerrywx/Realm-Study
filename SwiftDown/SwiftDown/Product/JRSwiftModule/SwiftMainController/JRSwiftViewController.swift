//
//  JRSwiftViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/11.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRSwiftViewController: JRBaseViewController {

	///
	let tableView = UITableView()
	var dataSource: [String]?
	
    override func viewDidLoad() {
        super.viewDidLoad()
		
		commentInit()
		setupUI()
    }
}

// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRSwiftViewController: UITableViewDataSource, UITableViewDelegate {
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return dataSource?.count ?? 0
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		
		let cell = tableView.dequeueReusableCell(withIdentifier: "cell")
		
		cell?.textLabel?.text = dataSource?[indexPath.row] ?? ""
		
		return cell!
	}
	
	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
	}
	
}


// MARK: - 初始化界面
extension JRSwiftViewController {
	
	func setupUI() {
	
		/// setup tableView
		tableView.frame			= view.bounds
		tableView.delegate		= self
		tableView.dataSource	= self
		view.addSubview(tableView)
		tableView.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
		
	}
	
	/// 初始化数据
	func commentInit() {
		
		dataSource = ["内建集合类型",
		              "集合类型协议",
		              "可选值",
		              "结构体和类",
		              "函数",
		              "字符串",
		              "错误处理",
		              "泛型",
		              "协议",
		              "互用性",]
		
	}
}



