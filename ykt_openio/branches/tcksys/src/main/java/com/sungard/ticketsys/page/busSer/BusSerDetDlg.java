package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.common.MyFormat;

public class BusSerDetDlg extends JDialog {

	private static final long serialVersionUID = 1L;

	private JPanel detail = null;

	private JPanel left = null;

	private JPanel right = null;

	// 字段名称
	private JLabel lb_busSerno = null;
	private JLabel lb_departtime = null;
	private JLabel lb_linename = null;
	private JLabel lb_price = null;
	private JLabel lb_perfectprice = null;
	private JLabel lb_maxcount = null;
	

	private JButton bt_submit = null;

	private JLabel lb_title = null;

	// 值
	private JLabel lb_busSerno1 = null;
	private JLabel lb_departtime1 = null;
	private JLabel lb_linename1 = null;
	private JLabel lb_price1 = null;
	private JLabel lb_perfectprice1 = null;
	private JLabel lb_maxcount1 = null;

	private BusSerPanel busSerPanel = null;

	public BusSer info_busSer = null;
	
	public BusSerDetDlg(JFrame parentFrame,BusSerPanel busSerPanel) {
		super(parentFrame, " ", true);
		this.busSerPanel = busSerPanel;
		this.setModal(true);
		setTitle("班次详细信息");
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
		this.add(getDetail(), null);
		this.requestFocus();
	}
	

	/**
	 * This method initializes detail
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getDetail() {
		if (detail == null) {
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(0, 15, 400, 30));
			lb_title.setText("班次详细信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			detail = new JPanel();
			detail.setLayout(null);
			detail.setBounds(new Rectangle(0, 0, 400, 450));
			detail.setBorder(BorderFactory.createTitledBorder("班次详细信息"));
			detail.add(getLeft(), null);
			detail.add(getRight(), null);
			detail.add(getBt_submit(), null);
			detail.add(lb_title, null);
		}
		return detail;
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
			right.setBounds(new Rectangle(100, 60, 260, 280));
			right.add(getLb_busSerno1(), null);
			right.add(getLb_departtime1(), null);
			right.add(getLb_linename1(), null);
			right.add(getLb_price1(), null);
			right.add(getLb_perfectprice1(), null);
			right.add(getLb_maxcount1(), null);
		}
		return right;
	}

	public JLabel getLb_busSerno1() {
		if (lb_busSerno1 == null) {
			lb_busSerno1 = new JLabel();
			lb_busSerno1.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return lb_busSerno1;
	}

	private JLabel getLb_departtime1() {
		if (lb_departtime1 == null) {
			lb_departtime1 = new JLabel();
			lb_departtime1.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return lb_departtime1;
	}

	public JLabel getLb_linename1() {
		if (lb_linename1 == null) {
			lb_linename1 = new JLabel();
			lb_linename1.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return lb_linename1;
	}

	public JLabel getLb_price1() {
		if (lb_price1 == null) {
			lb_price1 = new JLabel();
			lb_price1.setBounds(new Rectangle(0, 150, 250, 26));
		}
		return lb_price1;

	}

	public JLabel getLb_perfectprice1() {
		if (lb_perfectprice1 == null) {
			lb_perfectprice1 = new JLabel();
			lb_perfectprice1.setBounds(new Rectangle(0, 200, 250, 26));
		}
		return lb_perfectprice1;

	}
	
	public JLabel getLb_maxcount1() {
		if (lb_maxcount1 == null) {
			lb_maxcount1 = new JLabel();
			lb_maxcount1.setBounds(new Rectangle(0, 250, 250, 26));
		}
		return lb_maxcount1;

	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(170, 350, 60, 27));
			bt_submit.setText("确定");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					dispose();
				}
			});
		}
		return bt_submit;
	}

	public void setInfo_busSer(BusSer info_busSer) {
		this.info_busSer = info_busSer;
		getLb_busSerno1().setText(info_busSer.getSerilNo());
		String oldDepartTime = info_busSer.getDepartTime();
		getLb_departtime1().setText(
				oldDepartTime.substring(0, 2) + "时"
						+ oldDepartTime.substring(2, 4) + "分"
						+ oldDepartTime.substring(4, oldDepartTime.length())
						+ "秒");
		getLb_linename1().setText(info_busSer.getLineName());
		getLb_price1().setText(MyFormat.moneySdf(Double.parseDouble(info_busSer.getPrice()))+" 元");
		getLb_perfectprice1().setText(MyFormat.moneySdf(Double.parseDouble(info_busSer.getPerferPrice()))+" 元");
		getLb_maxcount1().setText(info_busSer.getMaxCount()+"");
	}

}
