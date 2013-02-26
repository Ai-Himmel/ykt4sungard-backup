package com.sungard.ticketsys.page.runBus;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.page.ticket.PrintRerTickDlg;
import com.sungard.ticketsys.service.BusManager;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;

public class SetRunBusDlg extends JDialog{
	
	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(PrintRerTickDlg.class);
	
	private JPanel newuser = null;
	private JLabel lb_title = null;
	private JPanel left = null;
	private JPanel right = null;
	private JButton bt_submit = null;
	private JButton bt_cancel = null;

	// 字段名
	private JLabel lb_bus = null;
	
	// 字段值
	private JComboBox cb_bus = null;

	private Boolean isOk = false;
	
	private BusserDay sleBusserDay;
	//运输车牌号
	private String busNo ;


public SetRunBusDlg(JFrame parentFrame,BusserDay sleBusserDay)
   {
		super(parentFrame, " ", true);
		this.setModal(true);
		try {
			inidata(sleBusserDay);
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
		this.setSize(300, 160);
		setLocation((d.width - getWidth()) / 2, (d.height - getHeight()) / 2);
   
   }

private void jbInit() throws Exception {
	this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	this.setResizable(false);
	this.setLayout(null);
	this.add(getNewuser(), null);
	this.requestFocus();
}

/**
 * This method initializes detail
 * 
 * @return javax.swing.JPanel
 */
private JPanel getNewuser() {
	if (newuser == null) {
		lb_title = new JLabel();
		lb_title.setBounds(new Rectangle(5, 18, 285, 30));
		lb_title.setText(" 请设置车次["+sleBusserDay.getSerdayId()+"]的运输车辆");
		lb_title.setHorizontalAlignment(JLabel.CENTER);
		lb_title.setForeground(Color.BLUE);
		lb_title.setFont(new Font("宋体", Font.BOLD, 14));
		newuser = new JPanel();
		newuser.setLayout(null);
		newuser.setBounds(new Rectangle(0, 0, 285, 160));
		newuser.add(getLeft(), null);
		newuser.add(getRight(), null);
		newuser.add(getBt_submit(), null);
		newuser.add(lb_title, null);
		newuser.add(getBt_cancel(), null);
	}
	return newuser;
}

/**
 * This method initializes left
 * 
 * @return javax.swing.JPanel
 */
private JPanel getLeft() {
	if (left == null) {
		lb_bus = new JLabel();
		lb_bus.setBounds(new Rectangle(0, 0, 66, 26));
		lb_bus.setText("运输车辆：");
		left = new JPanel();
		left.setLayout(null);
		left.setBounds(new Rectangle(40, 60, 68, 30));
		left.add(lb_bus, null);
	}
	return left;
}

/**
 * This method initializes right
 * 
 * @return javax.swing.JPanel
 */
private JPanel getRight() {
	if (right == null) {
		right = new JPanel();
		right.setLayout(null);
		right.setBounds(new Rectangle(110, 60, 150, 30));
		right.add(getCb_bus(), null);
	}
	return right;
}

/**
 * 运输车辆
 * 
 * @return
 */
private JComboBox getCb_bus() {
	if (cb_bus == null) {
		cb_bus = new JComboBox();
		cb_bus.setBounds(new Rectangle(0, 0, 135, 26));
		cb_bus.addItem("-------- 请选择 --------");
        List<Bus> busList = BusManager.getInstance().getAllBus();
        for (int i = 0; i < busList.size(); i++) {
        	Bus myBus = (Bus) busList.get(i);
        	cb_bus.addItem(myBus.getBusNo());
        }
		cb_bus.addPopupMenuListener(new PopupMenuListener() {
			public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
				cb_bus.removeAllItems();
				cb_bus.addItem("-------- 请选择 --------");
		        List<Bus> busList = BusManager.getInstance().getAllBus();
		        for (int i = 0; i < busList.size(); i++) {
		        	Bus myBus = (Bus) busList.get(i);
		        	cb_bus.addItem(myBus.getBusNo());
		        }
			}

			public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
			}

			public void popupMenuCanceled(PopupMenuEvent e) {
			}
		});
	}
	return cb_bus;
}


/**
 * This method initializes bt_submit
 * 
 * @return javax.swing.JButton
 */
private JButton getBt_submit() {
	if (bt_submit == null) {
		bt_submit = new JButton();
		bt_submit.setBounds(new Rectangle(70, 100, 63, 23));
		bt_submit.setText("确定");
		bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		bt_submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			    //设置输入值
				if (getCb_bus().getSelectedIndex() != 0) {
					busNo = getCb_bus().getSelectedItem().toString();
				}
				else {
					busNo = null;
				}
				setBusNo(busNo);
				setIsOk(true);
				dispose();
			}
		});
	}
	return bt_submit;
}

/**
 * This method initializes bt_concel
 * 
 * @return javax.swing.JButton
 */
private JButton getBt_cancel() {
	if (bt_cancel == null) {
		bt_cancel = new JButton();
		bt_cancel.setBounds(new Rectangle(140, 100, 63, 23));
		bt_cancel.setText("取消");
		bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		bt_cancel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				getCb_bus().setSelectedItem(0);
				setBusNo(null);
				setIsOk(false);
				dispose();
			}
		});
	}
	return bt_cancel;
}

public Boolean getIsOk() {
	return isOk;
}

public void setIsOk(Boolean isOk) {
	this.isOk = isOk;
}

public void inidata(BusserDay sleBusserDay){
	setSleBusserDay(sleBusserDay);
	setIsOk(false);
}

public BusserDay getSleBusserDay() {
	return sleBusserDay;
}

public void setSleBusserDay(BusserDay sleBusserDay) {
	this.sleBusserDay = sleBusserDay;
}

public String getBusNo() {
	return busNo;
}

public void setBusNo(String busNo) {
	this.busNo = busNo;
}

}