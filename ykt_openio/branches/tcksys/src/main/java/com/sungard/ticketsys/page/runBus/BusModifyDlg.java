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

public class BusModifyDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusModifyDlg.class);

	private JPanel globPanel = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;

	private JLabel lb_busno = null;

	private JLabel lb_bustype = null;
	
	private JLabel lb_seatcount = null;

	private JLabel tf_busno = null;
	
	private InputTextField tf_bustype = null;
	
	private InputTextField tf_seatcount = null;
	
	private BusPanel busPanel = null;

	public Bus info_bus=null;

	public BusModifyDlg(JFrame parentFrame,BusPanel busPanel) {
		super(parentFrame, " ", true);
		this.busPanel = busPanel;
		this.setModal(true);
		setTitle("更新车辆");
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
		this.add(getGlobPanel(), null);
		this.requestFocus();
	}


	

	/**
	 * This method initializes detail
	 *
	 * @return javax.swing.JPanel
	 */
	private JPanel getGlobPanel() {
		if (globPanel == null) {
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(0, 15, 400, 30));
			lb_title.setText("更新车辆信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 200, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);
			
			globPanel = new JPanel();
			globPanel.setLayout(null);
			globPanel.setBounds(new Rectangle(0, 0, 400, 300));
			globPanel.add(getLeft(), null);
			globPanel.add(getRight(), null);
			globPanel.add(getBt_submit(), null);
			globPanel.add(lb_title, null);
			globPanel.add(lb_error, null);
			globPanel.add(getBt_cancel(), null);
		}
		return globPanel;
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
			left.add(lb_seatcount,null);
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
			right.add(getTf_busno(), null);
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
			bt_submit.setBounds(new Rectangle(125, 240, 63, 23));
			bt_submit.setText("提交");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					
					// 验证输入的数据是否合法
					boolean flag = Validate.checkInputData(right, lb_error);
					
					if (flag) {
						try {
							//更新信息
							info_bus.setBusType(tf_bustype.getText());
							info_bus.setSeatCount(Integer.parseInt(tf_seatcount.getText().trim()));
							BusManager.getInstance().updateBus(info_bus);
							
							//关闭对话框
							dispose();
							
							JOptionPane.showMessageDialog(busPanel, "车辆["+ info_bus.getBusNo()+ "]信息更新成功", "更新车辆信息", JOptionPane.NO_OPTION);
							
							// 返回查询页面
							busPanel.getBus();
							busPanel.getSelect_all().setSelected(false);
						} catch (Exception e2) {
							logger.error("更新车辆["+ info_bus.getBusNo()+ "]信息失败，失败原因:" + e2.getMessage());
							dispose();
							JOptionPane.showMessageDialog(busPanel,"更新车辆["+ info_bus.getBusNo()+ "]信息失败!",
									"ERROE!!!", JOptionPane.ERROR_MESSAGE);
						}
							
						}
					}
			});
		}
		return bt_submit;
	}

	public void setInfo_Bus(Bus info_bus) {
		this.info_bus = info_bus;
		getTf_busno().setText(info_bus.getBusNo());
		tf_bustype.setText(info_bus.getBusType());
		tf_seatcount.setText(info_bus.getSeatCount()+"");
	}

	/**
	 * This method initializes bt_concel
	 *
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(220, 240, 63, 23));
			bt_cancel.setText("取消");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					dispose();
				}
			});
		}
		return bt_cancel;
	}

	/**
	 * This method initializes tf_busname
	 *
	 * @return javax.swing.JTextField
	 */
	private JLabel getTf_busno() {
		if (tf_busno == null) {
			tf_busno = new JLabel();
			tf_busno.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return tf_busno;
	}
	
	
}


