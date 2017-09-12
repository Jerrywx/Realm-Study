//
//  JRForumSubController.swift
//  SwiftDown
//
//  Created by wxiao on 2017/9/11.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRForumSubController: JRBaseViewController {

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

extension JRForumSubController: UITableViewDataSource, UITableViewDelegate {
	
	func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return 20
	}
	
	func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: "cell")
		
		cell?.textLabel?.text = "cell - \(indexPath.row)"
		
		return cell!
	}
	
	override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	override func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	func scrollViewDidScroll(_ scrollView: UIScrollView) {
		
		if superVC?.scrollModel == 0 && superVC?.scrollModel2 == 0 {
			tableView?.contentOffset = CGPoint(x: 0, y: 0)
		} else {
			superVC?.scrollModel2 = 1
		}
		if scrollView.contentOffset.y <= 0 {
			superVC?.scrollModel2 = 0
		}
	}
	
}

