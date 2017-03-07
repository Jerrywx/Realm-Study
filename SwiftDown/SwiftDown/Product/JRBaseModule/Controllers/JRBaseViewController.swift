//
//  JRBaseViewController.swift
//  SwiftDown
//
//  Created by 王潇 on 2017/3/1.
//  Copyright © 2017年 王潇. All rights reserved.
//

import UIKit

class JRBaseViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
		view.backgroundColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
    }
}

// MARK: - UITableViewDelegate
extension JRBaseViewController {
	
	func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
		return 0.1
	}
	
	func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
		return 0.1
	}
}

