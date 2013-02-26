package com.sungard.ticketsys.page.ticket;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.border.TitledBorder;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.TicketManager;


public class PrintRerTickDlg extends JDialog{
	
	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(PrintRerTickDlg.class);
	
	private JPanel newuser = null;
	private JLabel lb_title = null;
	private JPanel left = null;
	private JPanel right = null;
	private JButton bt_submit = null;
	private JButton bt_cancel = null;

	// 字段名
	private JLabel lb_payType = null;
	private JLabel lb_ticketType = null;
	private JLabel lb_price = null;
	
	// 字段值
	private JComboBox cb_payType = null;
	private JComboBox cb_ticketType = null;
	private JLabel lb_priceD = null;

	private TicketLog ticketLog;
	private BusSer currBusSer;
	private Boolean isOk = false;


public PrintRerTickDlg(JFrame parentFrame,TicketLog ticketLog)
   {
		super(parentFrame, " ", true);
		this.setModal(true);
		try {
			inidata(ticketLog);
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
		this.setSize(300, 260);
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
		lb_title.setBounds(new Rectangle(10, 18, 270, 30));
		lb_title.setText(" 请选择座位号["+ticketLog.getSeatNo()+"]的支付、票务类型");
		lb_title.setHorizontalAlignment(JLabel.CENTER);
		lb_title.setForeground(Color.BLUE);
		lb_title.setFont(new Font("宋体", Font.BOLD, 14));
		newuser = new JPanel();
		newuser.setLayout(null);
		newuser.setBounds(new Rectangle(0, 0, 270, 260));
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
		lb_payType = new JLabel();
		lb_payType.setBounds(new Rectangle(0, 0, 66, 26));
		lb_payType.setText("支付类型：");
		lb_ticketType = new JLabel();
		lb_ticketType.setBounds(new Rectangle(0, 50, 66, 26));
		lb_ticketType.setText("票务类型：");
		lb_price = new JLabel();
		lb_price.setBounds(new Rectangle(0, 100, 66, 26));
		lb_price.setText("票价：");
		left = new JPanel();
		left.setLayout(null);
		left.setBounds(new Rectangle(40, 60, 68, 130));
		left.add(lb_payType, null);
		left.add(lb_ticketType, null);
		left.add(lb_price, null);
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
		right.setBounds(new Rectangle(110, 60, 150, 130));
		right.add(getCb__payType(), null);
		right.add(getCb__ticketType(), null);
		right.add(getLb_price(), null);
	}
	return right;
}

/**
 * 付款方式
 * 
 * @return
 */
private JComboBox getCb__payType() {
	if (cb_payType == null) {
		cb_payType = new JComboBox();
		cb_payType.setBounds(new Rectangle(0, 0, 100, 26));
		cb_payType.addItem(TicketLog.PAY_TYPE_CASH);
		cb_payType.addPopupMenuListener(new PopupMenuListener() {
			public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
				cb_payType.removeAllItems();
				cb_payType.addItem(TicketLog.PAY_TYPE_CASH);
				cb_payType.addItem(TicketLog.PAY_TYPE_CARD);
			}

			public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
			}

			public void popupMenuCanceled(PopupMenuEvent e) {
			}
		});
	}
	return cb_payType;
}

/**
 * 
 * @return
 */
private JComboBox getCb__ticketType() {
	if (cb_ticketType == null) {
		cb_ticketType = new JComboBox();
		cb_ticketType.setBounds(new Rectangle(0, 50, 100, 26));
		cb_ticketType.addItem(TicketLog.TICKET_TYPE_MORM);
		cb_ticketType.addPopupMenuListener(new PopupMenuListener() {
			public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
				cb_ticketType.removeAllItems();
				cb_ticketType.addItem(TicketLog.TICKET_TYPE_MORM);
				cb_ticketType.addItem(TicketLog.TICKET_TYPE_PER);
			}

			public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
			}

			public void popupMenuCanceled(PopupMenuEvent e) {
			}
		});
		cb_ticketType.addItemListener(new ItemListener() {

			public void itemStateChanged(ItemEvent e) {
				String ticketType = cb_ticketType.getSelectedItem()+"";
				//如果为普通票，这票价为普通价
				if(currBusSer!=null){
						if (ticketType.equals(TicketLog.TICKET_TYPE_MORM)){
						getLb_price().setText(currBusSer.getPrice());
					}else if(ticketType.equals(TicketLog.TICKET_TYPE_PER)){
						getLb_price().setText(currBusSer.getPerferPrice());
					}
				}
				
				

			}
		});
	}
	return cb_ticketType;
}

/**
 * 票价
 * 
 * @return
 */
private JLabel getLb_price() {
	if (lb_priceD == null) {
		lb_priceD = new JLabel();
		lb_priceD.setBounds(new Rectangle(0, 100, 100, 26));
	}
	return lb_priceD;
}

/**
 * This method initializes bt_submit
 * 
 * @return javax.swing.JButton
 */
private JButton getBt_submit() {
	if (bt_submit == null) {
		bt_submit = new JButton();
		bt_submit.setBounds(new Rectangle(70, 200, 63, 23));
		bt_submit.setText("确定");
		bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		bt_submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			    //设置输入值
				ticketLog.setPayType(getCb__payType().getSelectedItem()+"");
				ticketLog.setTicketType(getCb__ticketType().getSelectedItem()+"");
				ticketLog.setPrice(getLb_price().getText());
				setTicketLog(ticketLog);
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
		bt_cancel.setBounds(new Rectangle(140, 200, 63, 23));
		bt_cancel.setText("取消");
		bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		bt_cancel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				getCb__payType().setSelectedItem(0);
				getCb__ticketType().setSelectedItem(0);
				setIsOk(false);
				dispose();
			}
		});
	}
	return bt_cancel;
}


public TicketLog getTicketLog() {
	return ticketLog;
}

public void setTicketLog(TicketLog ticketLog) {
	this.ticketLog = ticketLog;
}

public Boolean getIsOk() {
	return isOk;
}

public void setIsOk(Boolean isOk) {
	this.isOk = isOk;
}

public void inidata(TicketLog ticketLog){
	setTicketLog(ticketLog);
    currBusSer = BusSerManager.getInstance().getBusSer(ticketLog.getBusSerno());
	getLb_price().setText(currBusSer.getPrice());
	setIsOk(false);
}

}