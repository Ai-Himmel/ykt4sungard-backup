package com.sungard.ticketsys.page.runBus;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusManager;
import com.sungard.ticketsys.component.InputComponet;
import com.sungard.ticketsys.component.InputTextField;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.component.ValidateType;

public class BusAddDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusAddDlg.class);

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;

	private JLabel lb_busno = null;

	private JLabel lb_bustype = null;
	
	private JLabel lb_seatcount = null;

	private InputTextField tf_busno = null;
	
	private InputTextField tf_bustype = null;
	
	private InputTextField tf_seatcount = null;

	private JButton bt_reset = null;

	private BusPanel busPanel = null;

	public BusAddDlg(JFrame parentFrame, BusPanel busPanel) {
		super(parentFrame, " ", true);
		this.busPanel = busPanel;
		this.setModal(true);
		setTitle("新增车辆");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 300);
		this.setLocationRelativeTo(busPanel);
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
			lb_title.setText("添加车辆信息");
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
			lb_busno = new JLabel();
			lb_busno.setBounds(new Rectangle(0, 0, 66, 26));
			lb_busno.setText("车牌号：");
			
			lb_bustype = new JLabel();
			lb_bustype.setBounds(new Rectangle(0, 50, 66, 26));
			lb_bustype.setText("车型：");
			
			lb_seatcount = new JLabel();
			lb_seatcount.setBounds(new Rectangle(0, 100, 66, 26));
			lb_seatcount.setText("座位数：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 130));
			left.add(lb_busno, null);
			left.add(lb_bustype, null);
			left.add(lb_seatcount, null);
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
			tf_busno = InputComponet.textField(right,tf_busno, "车牌号", ValidateType.STRING, true, 0, 0);
			tf_bustype = InputComponet.textField(right,tf_bustype, "车型", ValidateType.STRING, false, 0, 50);
			tf_seatcount = InputComponet.textField(right,tf_seatcount, "座位数", ValidateType.INT, true, 0, 100);
		}
		return right;
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
					
					// 验证输入的数据是否合法
					boolean flag = Validate.checkInputData(right, lb_error);
					
					if (flag && BusManager.getInstance().checkBusIsUsed(tf_busno.getText().trim())) {
						lb_error.setText("提交失败：车牌号已存在，请重新输入!");
						flag = false;
					}
					
					if (flag) {
						
						try {
							//新增车辆信息
							Bus bus = new Bus();
							bus.setBusNo(tf_busno.getText());
							bus.setBusType(tf_bustype.getText());
							bus.setSeatCount(Integer.parseInt(tf_seatcount.getText().trim()));
							bus.setBusState(Bus.STATE_UN_USER);
							BusManager.getInstance().saveBus(bus);
							
							// 清空编辑页面
							clearInput();
							
							//关闭对话框
							dispose();
							
							JOptionPane.showMessageDialog(busPanel, "新增车辆信息成功", "SUCCESS",
									JOptionPane.NO_OPTION);
							
							//返回查询页面
							busPanel.getBus();
							busPanel.getSelect_all().setSelected(false);
						} catch (Exception e2) {
							logger.error("新增车辆失败，失败原因:" + e2.getMessage());
							dispose();
							JOptionPane.showMessageDialog(busPanel, "新增车辆失败!",
									"ERROE!!!", JOptionPane.ERROR_MESSAGE);
						}
							
						}
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
	private void clearInput(){
		//清空编辑页面 
		tf_busno.setText("");
		tf_bustype.setText("");
		tf_seatcount.setText("");
		lb_error.setText("");
	}

	
}

