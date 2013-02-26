package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.component.InputComboBox;
import com.sungard.ticketsys.component.InputComponet;
import com.sungard.ticketsys.component.InputTextField;
import com.sungard.ticketsys.component.TimeField;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.component.ValidateType;

public class BusSerAddDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusSerAddDlg.class);

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	private JLabel lb_error = null;

	// 字段名称
	private JLabel lb_busSerno = null;
	private JLabel lb_departtime = null;
	private JLabel lb_linename = null;
	private JLabel lb_price = null;
	private JLabel lb_perfectprice = null;
	private JLabel lb_maxcount = null;

	// 输入字段
	private InputTextField tf_busSerno = null;
	private TimeField tf_departtime = null;
	private InputComboBox cb_linename = null;
	private InputTextField tf_price = null;
	private InputTextField tf_perfectprice = null;
	private InputTextField tf_maxcount = null;

	private JButton bt_reset = null;

	private BusSerPanel busSerPanel = null;

	public BusSerAddDlg(JFrame parentFrame, BusSerPanel busSerPanel) {
		super(parentFrame, " ", true);
		this.busSerPanel = busSerPanel;
		this.setModal(true);
		setTitle("新增班次");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 450);
		this.setLocationRelativeTo(busSerPanel);
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
			lb_title.setText("新增班次");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));

			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 350, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);

			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 400, 450));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
			newuser.add(lb_error, null);
			newuser.add(getBt_cancel(), null);
			newuser.add(getBt_reset(), null);
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
			lb_busSerno = new JLabel();
			lb_busSerno.setBounds(new Rectangle(0, 0, 66, 26));
			lb_busSerno.setText("班次号：");
			
			lb_departtime = new JLabel();
			lb_departtime.setBounds(new Rectangle(0, 50, 66, 26));
			lb_departtime.setText("发车时间：");
			
			lb_linename = new JLabel();
			lb_linename.setBounds(new Rectangle(0, 100, 66, 26));
			lb_linename.setText("路线名称：");
			
			lb_price = new JLabel();
			lb_price.setBounds(new Rectangle(0, 150, 66, 26));
			lb_price.setText("普通票价：");
			
			lb_perfectprice = new JLabel();
			lb_perfectprice.setBounds(new Rectangle(0, 200, 66, 26));
			lb_perfectprice.setText("内部票价：");
			
			lb_maxcount = new JLabel();
			lb_maxcount.setBounds(new Rectangle(0, 250, 66, 26));
			lb_maxcount.setText("票数上限：");
			
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 280));
			left.add(lb_busSerno, null);
			left.add(lb_departtime, null);
			left.add(lb_linename, null);
			left.add(lb_price, null);
			left.add(lb_perfectprice, null);
			left.add(lb_maxcount, null);
			
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
			right.setBounds(new Rectangle(100, 60, 280, 280));
			tf_busSerno = InputComponet.textField(right,tf_busSerno, "班次号", ValidateType.STRING, true, 0, 0);
			tf_departtime = InputComponet.timeField(right, tf_departtime, "发车时间", lb_error, true, 0, 50);
			right.add(getCb_linename(), null);
			tf_price = InputComponet.moneyField(right, tf_price, "普通票价", true, 0, 150);
			tf_perfectprice = InputComponet.moneyField(right, tf_perfectprice, "内部票价", true, 0, 200);
			tf_maxcount = InputComponet.textField(right,tf_maxcount,"票数上限",ValidateType.INT, true, 0, 250);
		}
		return right;
	}

	/**
	 * This method initializes cb_category
	 * 
	 * @return javax.swing.JComboBox
	 */
	private InputComboBox getCb_linename() {
		if (cb_linename == null) {
			cb_linename = new InputComboBox();
			cb_linename.setNotNull(true);
			cb_linename.setName("路线");
			cb_linename.setBounds(new Rectangle(0, 100, 250, 26));
			cb_linename.addItem("-------- 请选择 --------");
			List<Line> lines = LineManager.getInstance().getAllLine();
			for (int i = 0; i < lines.size(); i++) {
				Line myLine = (Line) lines.get(i);
				cb_linename.addItem(myLine.getLineName());
			}
			cb_linename.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_linename.removeAllItems();
					cb_linename.addItem("-------- 请选择 --------");
					List<Line> lines = LineManager.getInstance().getAllLine();
					for (int i = 0; i < lines.size(); i++) {
						Line myLine = (Line) lines.get(i);
						cb_linename.addItem(myLine.getLineName());
					}
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_linename;
	}


	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(60, 390, 63, 23));
			bt_submit.setText("提交");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {

					// 验证输入的数据是否合法
					boolean flag = Validate.checkInputData(right, lb_error);
					
					if (flag && BusSerManager.getInstance().checkBusSerIsUsed( tf_busSerno.getText().trim())) {
						lb_error.setText("提交失败：班次号已存在，请重新输入!");
						flag = false;
					}
					
					if(flag && Integer.parseInt(tf_maxcount.getText().trim())>200){
						lb_error.setText("提交失败：票数上限不能大于200!");
						flag = false;
					}
					
					if (flag) {
						try {
							// 新增班次信息
							BusSer busSer = new BusSer();
							busSer.setSerilNo(tf_busSerno.getText().trim());
							busSer.setDepartTime(tf_departtime.getDepartTime());
							busSer.setLineName(getCb_linename().getSelectedItem()+ "");
							busSer.setPrice(tf_price.getText().trim());
							busSer.setPerferPrice(tf_perfectprice.getText().trim());
							busSer.setMaxCount(Integer.parseInt(tf_maxcount.getText().trim()));
							BusSerManager.getInstance().saveBusSer(busSer);

							// 清空编辑页面
							clearInput();
							
							//关闭对话框
							dispose();
							
							//提示新增成功
							JOptionPane.showMessageDialog(busSerPanel, "新增班次信息成功","SUCCESS", JOptionPane.NO_OPTION);

							// 返回查询页面
							busSerPanel.getBusSer();
							busSerPanel.getSelect_all().setSelected(false);
						} catch (Exception e2) {
							logger.error("新增班次失败，失败原因:" + e2.getMessage());
							dispose();
							JOptionPane.showMessageDialog(busSerPanel, "新增班次失败!",
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
			bt_cancel.setBounds(new Rectangle(250, 390, 63, 23));
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
			bt_reset.setBounds(new Rectangle(160, 390, 63, 23));
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
		tf_busSerno.setText("");
		tf_departtime.clearTimeField();
		getCb_linename().setSelectedIndex(0);
		tf_price.setText("");
		tf_perfectprice.setText("");
		tf_maxcount.setText("");
		lb_error.setText("");
	}

}
