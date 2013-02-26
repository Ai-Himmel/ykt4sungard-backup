package com.sungard.ticketsys.action;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by IntelliJ IDEA.
 * User: Xuan.Zhou
 * Date: 2011-8-15
 * Time: 16:35:54
 * To change this template use File | Settings | File Templates.
 */
public class IndexAct {

    private static IndexAct ourInstance = new IndexAct();

    public static IndexAct getInstance() {
        return ourInstance;
    }

    private IndexAct() {
    }

     public void addActionListener(JMenuItem menuItem){
            	menuItem.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
//					jContentPane.add(getUserpanel(), null);
//						userpanel.setVisible(true);
				}
			});
    }
}
