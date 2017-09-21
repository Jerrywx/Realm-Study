//
//  JRBookLogViewController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/21.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBookLogViewController: JRBaseViewController {

	/// tableView
	var tableView: UITableView?
	
	/// 目录数组
	var logArray:[JRBookChapterModel] = [JRBookChapterModel]() {
		
		didSet {
			if logArray.count > 0 {
				tableView?.reloadData()
			}
		}
	}
	
    override func viewDidLoad() {
        super.viewDidLoad()

        setupUI()
    }
}

///
extension JRBookLogViewController {
	
	///
	func setupUI() {
		
		title = "目录"
		
		tableView = UITableView(frame: view.bounds, style: .grouped)
		tableView?.delegate = self
		tableView?.dataSource = self
		tableView?.register(UITableViewCell.self, forCellReuseIdentifier: "logCell")
		view.addSubview(tableView!)
	}
}


extension JRBookLogViewController: UITableViewDataSource, UITableViewDelegate {
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return logArray.count
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "logCell")
		
		let model:JRBookChapterModel = logArray[indexPath.row]
		
		let name = model.name ?? ""
		
		cell?.textLabel?.text = "\(indexPath.row)、\(name)"
		
		return cell!
	}
	
	func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		tableView.deselectRow(at: indexPath, animated: true)
	}
	
}

