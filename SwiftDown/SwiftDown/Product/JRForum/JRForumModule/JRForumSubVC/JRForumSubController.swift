//
//  JRForumSubController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/11.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumSubController: JRBaseViewController {

	var lastPosition:CGFloat = 0
	
	weak var superVC: JRForumViewController?
	var tableView: JRTableView?
	
    override func viewDidLoad() {
        super.viewDidLoad()

		automaticallyAdjustsScrollViewInsets = false
		
		view.backgroundColor = UIColor.clear
		
		let frame = CGRect(x: 0, y: 44, width: UIScreen.scrren_W(), height: UIScreen.screen_H() - 44 - 64)
		tableView = JRTableView(frame: frame, style: .grouped)
		view.addSubview(tableView!)
		//		tableView?.separatorStyle = .none
		tableView?.delegate = self
		tableView?.dataSource = self
		tableView?.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
    }
}

// MARK: - UITableViewDataSource, UITableViewDelegate
extension JRForumSubController: UITableViewDataSource, UITableViewDelegate {
	
	/// UITableViewDataSource
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 20
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "cell")
		
		cell?.textLabel?.text = "cell - \(indexPath.row)"
		
		return cell!
	}
	
	/// UITableViewDelegate
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		
		
//		if superVC?.scrollModel == 0 && superVC?.scrollModel2 == 0 {
//			tableView?.contentOffset = CGPoint(x: 0, y: 0)
//		} else {
//			superVC?.scrollModel2 = 1
//		}
		
		let y = scrollView.contentOffset.y
		
		
//		if scrollView.contentOffset.y > 100 && (lastPosition - y) > 0 {
//			superVC?.scrollModel2 = 1
//		} else {
//			superVC?.scrollModel2 = 0
//		}
		
		if scrollView.contentOffset.y < 100 {
			superVC?.scrollModel2 = 0
		}
		
		
		if scrollView.contentOffset.y <= 0 {
			superVC?.scrollModel2 = 0
		}
		
		lastPosition = y
	}
	
}

