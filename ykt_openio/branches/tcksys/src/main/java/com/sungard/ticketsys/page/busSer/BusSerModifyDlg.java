package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.component.InputComboBox;
import com.sungard.ticketsys.component.InputComponet;
import com.sungard.ticketsys.component.InputTextField;
import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.component.TimeField;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.component.ValidateType;

public class BusSerModifyDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	
	private static final Logger logger = Logger.getLogger(BusSerModifyDlg.class);

	private JPanel globPanel = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;

	//字段名称
	private JLabel lb_busSerno = null;
	private JLabel lb_departtime = null;
	private JLabel lb_linename = null;
	private JLabel lb_price = null;
	private JLabel lb_perfectprice = null;
	private JLabel lb_maxcount = null;
	
	//输入字段
	private JLabel tf_busSerno = null;
	
	private TimeField tf_departtime = null;
	private InputComboBox cb_linename = null;
	private InputTextField tf_price = null;
	private InputTextField tf_perfectprice = null;
	private InputTextField tf_maxcount = null;
	
	private BusSerPanel busSerPanel = null;

	public BusSer info_busSer=null;
	
	public BusSerModifyDlg(JFrame parentFrame, BusSerPanel busSerPanel) {
		super(parentFrame, " ", true);
		this.busSerPanel = busSerPanel;
		this.setModal(true);
		setTitle("更新班次");
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
			lb_title.setText("更新班次信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 350, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);
			
			globPanel = new JPanel();
			globPanel.setLayout(null);
			globPanel.setBounds(new Rectangle(0, 0, 400, 450));
			globPanel.setBorder(BorderFactory.createTitledBorder("更新班次信息"));
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
			
			right.add(getTf_busSerno(), null);
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
	private InputComboBox  getCb_linename() {
		if (cb_linename == null) {
			cb_linename = new  InputComboBox ();
			cb_linename.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return cb_linename;
	}
	
	/**
	 * This method initializes tf_busSername
	 *
	 * @return javax.swing.JTextField
	 */
	private JLabel getTf_busSerno() {
		if (tf_busSerno == null) {
			tf_busSerno = new JLabel();
			tf_busSerno.setBounds(new Rectangle(0, 0,  250, 26));
		}
		return tf_busSerno;
	}

	/**
	 * This method initializes bt_submit
	 *
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(125, 390, 63, 23));
			bt_submit.setText("提交");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					
					// 验证输入的数据是否合法
					boolean flag = Validate.checkInputData(right, lb_error);
					if(flag && Integer.parseInt(tf_maxcount.getText().trim())>200){
						lb_error.setText("提交失败：票数上限不能大于200!");
						flag = false;
					}
					
					if (flag) {
						try {
							// 更新班次信息
							info_busSer.setDepartTime(tf_departtime.getDepartTime());
							info_busSer.setLineName(getCb_linename().getSelectedItem()+"");
							info_busSer.setPrice(tf_price.getText().trim());
							info_busSer.setPerferPrice(tf_perfectprice.getText().trim());
							info_busSer.setMaxCount(Integer.parseInt(tf_maxcount.getText().trim()));
							BusSerManager.getInstance().updateBusSer(info_busSer);
							
							//关闭对话框
							dispose();
							
							//提示新增成功
							JOptionPane.showMessageDialog(busSerPanel, "更新班次["+ info_busSer.getSerilNo()+ "]信息成功","SUCCESS", JOptionPane.NO_OPTION);

							// 返回查询页面
							busSerPanel.getBusSer();
							busSerPanel.getSelect_all().setSelected(false);
							
						} catch (Exception e2) {
							logger.error("更新班次["+ info_busSer.getSerilNo()+ "]信息失败，失败原因:" + e2.getMessage());
							dispose();
							JOptionPane.showMessageDialog(busSerPanel,"更新班次["+ info_busSer.getSerilNo()+ "]信息失败!",
									"ERROE!!!", JOptionPane.ERROR_MESSAGE);
						}
							
						}
					}

			});
		}
		return bt_submit;
	}
	

	public void setInfo_BusSer(BusSer info_busSer) {
		this.info_busSer = info_busSer;
		getTf_busSerno().setText(info_busSer.getSerilNo());
		String olddeparttime = info_busSer.getDepartTime();
		tf_departtime.setHourValue(olddeparttime.substring(0, 2));
		tf_departtime.setMinuteValue(olddeparttime.substring(2,4));
		tf_departtime.setSecondValue(olddeparttime.substring(4,olddeparttime.length()));
		//设置路径的值
		String lineName = info_busSer.getLineName();
		if(info_busSer != null) {
			//移除列表中的所有元素
			cb_linename.removeAllItems();
			
			//当前班次的路线
			Line line = LineManager.getInstance().getLine(lineName);
			List<Line> lines = LineManager.getInstance().getAllLine();
			for (int i = 0; i < lines.size(); i++) {
				Line myline = (Line) lines.get(i);
				cb_linename.addItem(myline.getLineName());
			}
			for (int i = 0; i < lines.size(); i++) {
				if (cb_linename.getItemAt(i).toString().equals(line.getLineName())) {
					cb_linename.setSelectedIndex(i);
				}
			}
		}
		tf_price.setText(MyFormat.moneySdf(Double.parseDouble(info_busSer.getPrice())));
		tf_perfectprice.setText(MyFormat.moneySdf(Double.parseDouble(info_busSer.getPerferPrice())));
		tf_maxcount.setText(info_busSer.getMaxCount()+"");
	}

	/**
	 * This method initializes bt_concel
	 *
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(230, 390, 63, 23));
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
	
}



