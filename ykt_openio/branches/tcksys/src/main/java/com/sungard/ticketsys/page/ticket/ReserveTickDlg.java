package com.sungard.ticketsys.page.ticket;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusManager;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.TicketManager;
import com.sungard.ticketsys.component.InputComponet;
import com.sungard.ticketsys.component.InputTextField;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.component.ValidateType;

public class ReserveTickDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(ReserveTickDlg.class);

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	private JLabel lb_error = null;

	private JLabel lb_reservecount = null;
	private JLabel lb_memo = null;

	private InputTextField tf_reservecount = null;
	private JScrollPane jScrollPane_desc = null;
	private JTextPane jTextPane_desc = null;

	// 本车次信息
	private BusserDay sleBusserDay = null;
	private BusSer currBusSer = null;
	private Line currLine = null;

	private JButton bt_reset = null;

	private TickePanel tickePanel = null;

	// 输入值
	private int reservecount;
	private String desc;

	public ReserveTickDlg(JFrame parentFrame, TickePanel tickePanel) {
		super(parentFrame, " ", true);
		this.tickePanel = tickePanel;
		this.setModal(true);
		setTitle("预留票窗口");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 300);
		this.setLocationRelativeTo(tickePanel);
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
			lb_title.setBounds(new Rectangle(0, 15, 400, 30));
			lb_title.setText("预留票窗口");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));

			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 200, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);

			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 400, 300));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(lb_title, null);

			newuser.add(getBt_submit(), null);
			newuser.add(getBt_cancel(), null);
			newuser.add(getBt_reset(), null);

			newuser.add(lb_error, null);
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
			lb_reservecount = new JLabel();
			lb_reservecount.setBounds(new Rectangle(0, 0, 66, 26));
			lb_reservecount.setText("预留票数：");

			lb_memo = new JLabel();
			lb_memo.setBounds(new Rectangle(0, 50, 66, 26));
			lb_memo.setText("备注：");

			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 130));
			left.add(lb_reservecount, null);
			left.add(lb_memo, null);
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
			right.setBounds(new Rectangle(100, 60, 260, 130));
			tf_reservecount = InputComponet.textField(right, tf_reservecount,
					"预留票数", ValidateType.INT, true, 0, 0);
			right.add(getJScrollPane_desc(), null);
		}
		return right;
	}

	/**
	 * 
	 * This method initializes jScrollPane_desc
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getJScrollPane_desc() {
		if (jScrollPane_desc == null) {
			jScrollPane_desc = new JScrollPane();
			jScrollPane_desc.setBounds(new Rectangle(0, 50, 250, 60));
			jScrollPane_desc.setViewportView(getJTextPane_desc());
		}
		return jScrollPane_desc;
	}

	/**
	 * This method initializes jTextPane_desc
	 * 
	 * @return javax.swing.JTextPane
	 */
	private JTextPane getJTextPane_desc() {
		if (jTextPane_desc == null) {
			jTextPane_desc = new JTextPane();
		}
		return jTextPane_desc;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(60, 240, 63, 23));
			bt_submit.setText("提交");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {

					// 验证输入的值是否合格
					boolean flag = checkeData();

					if (flag) {

						try {
							// 预留票
							reservecount = Integer.parseInt(tf_reservecount
									.getText().trim());
							TicketManager.getInstance().reserveTicket(
									sleBusserDay, reservecount,
									getJTextPane_desc().getText());

							// 清空编辑页面
							clearInput();

							// 关闭对话框
							dispose();

							JOptionPane.showMessageDialog(tickePanel, "预留票成功",
									"SUCCESS", JOptionPane.NO_OPTION);

							// 返回查询页面
							tickePanel.getSerSet();
							tickePanel.getSelect_all().setSelected(false);
						} catch (Exception e2) {
							// 关闭对话框
							dispose();
							JOptionPane.showMessageDialog(tickePanel, "车次["+sleBusserDay.getSerdayId()+"]预留票失败:"+e2
									.getMessage(), "ERROE!!!",
									JOptionPane.ERROR_MESSAGE);
						}

					}
				}

			});
		}
		return bt_submit;
	}

	private boolean checkeData() {

		if (!Validate.checkInputData(right, lb_error)) {
			return false;
		}
		// 判断车次是否已过期
		Date now = new Date();
		Calendar cnow = Calendar.getInstance();
		cnow.setTime(now);

		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		Date departTime = null;
		try {
			departTime = sdf.parse(sleBusserDay.getDepartDate()
					+ currBusSer.getDepartTime());
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Calendar cdepartTime = Calendar.getInstance();
		cdepartTime.setTime(departTime);
		if (cnow.after(cdepartTime)) {
			logger.error("发车时间已过，不可售票");
			lb_error.setText("提交失败：发车时间已过，不可售票!");
			return false;
		}

		return true;
	}

	/**
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(250, 240, 63, 23));
			bt_cancel.setText("取消");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					clearInput();
					dispose();
				}
			});
		}
		return bt_cancel;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(160, 240, 63, 23));
			bt_reset.setText("重置");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					clearInput();
				}
			});
		}
		return bt_reset;
	}

	/**
	 * 清空当前输入控件
	 */
	private void clearInput() {
		// 清空输入框
		tf_reservecount.setText("");
		getJTextPane_desc().setText("");
		lb_error.setText("");
	}

	public void setInfo_BusserDay(BusserDay sleBusserDay) {
		this.sleBusserDay = sleBusserDay;
		this.currBusSer = BusSerManager.getInstance().getBusSer(
				sleBusserDay.getBusSerNo());
		this.currLine = LineManager.getInstance().getLine(
				currBusSer.getLineName());
	}

}
