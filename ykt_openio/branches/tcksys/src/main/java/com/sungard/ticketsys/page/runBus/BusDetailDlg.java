package com.sungard.ticketsys.page.runBus;

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
import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.busSer.BusSerPanel;

public class BusDetailDlg extends JDialog  {

	private static final long serialVersionUID = 1L;

	private JPanel detail = null;

	private JPanel left = null;

	private JPanel right = null;

	private JLabel lb_busno = null;

	private JLabel lb_bustype = null;
	
	private JLabel lb_seatcount = null;
	
	private JLabel lb_busstate = null;

	private JButton bt_submit = null;

	private JLabel lb_title = null;
	
	private JLabel lb_busno1 = null;

	private JLabel lb_bustype1 = null;
	
	private JLabel lb_seatcount1 = null;
	
	private JLabel lb_busstate1 = null;

	private BusPanel busPanel = null;

	public Bus info_bus=null;

	public BusDetailDlg(JFrame parentFrame,BusPanel busPanel) {
		super(parentFrame, " ", true);
		this.busPanel = busPanel;
		this.setModal(true);
		setTitle("车辆详细信息");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 350);
		this.setLocationRelativeTo(busPanel);
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
			lb_title.setText("车辆详细信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			detail = new JPanel();
			detail.setLayout(null);
			detail.setBounds(new Rectangle(0, 0, 400, 350));
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
			lb_busno = new JLabel();
			lb_busno.setBounds(new Rectangle(0, 0, 66, 26));
			lb_busno.setText("车牌号：");
			lb_bustype = new JLabel();
			lb_bustype.setBounds(new Rectangle(0, 50, 66, 26));
			lb_bustype.setText("车型：");
			lb_seatcount = new JLabel();
			lb_seatcount.setBounds(new Rectangle(0, 100, 66, 26));
			lb_seatcount.setText("座位数：");
			lb_busstate = new JLabel();
			lb_busstate.setBounds(new Rectangle(0, 150, 66, 26));
			lb_busstate.setText("使用状态：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 180));
			left.add(lb_busno, null);
			left.add(lb_bustype, null);
			left.add(lb_seatcount,null);
			left.add(lb_busstate,null);
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
			right.setBounds(new Rectangle(100, 60, 260, 180));
			right.add(getLb_busno1(), null);
			right.add(getLb_bustype1(), null);
			right.add(getLb_seatcount1(), null);
			right.add(getLb_busstate1(), null);
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
			bt_submit.setBounds(new Rectangle(170, 250, 60, 27));
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


	public JLabel getLb_busno1() {
		if(lb_busno1==null) {
		   lb_busno1 = new JLabel();
		   lb_busno1.setBounds(new Rectangle(0, 0,  250, 26));
		}
		return lb_busno1;
	}
	
	private JLabel getLb_bustype1() {
		if (lb_bustype1 == null) {
			lb_bustype1 = new JLabel();
			lb_bustype1.setBounds(new Rectangle(0, 50,  250, 26));
		}
		return lb_bustype1;
	}
	
	public JLabel getLb_seatcount1(){
		if(lb_seatcount1 == null){
			lb_seatcount1 = new JLabel(); 
			lb_seatcount1.setBounds(new Rectangle(0, 100,  250, 26));
		}
		return lb_seatcount1;
	}
	
	public JLabel getLb_busstate1(){
		if(lb_busstate1 == null){
			lb_busstate1 = new JLabel(); 
			lb_busstate1.setBounds(new Rectangle(0, 150,  250, 26));
		}
		return lb_busstate1;
		
	}

	public void setInfo_bus(Bus info_bus) {
		this.info_bus = info_bus;
		getLb_busno1().setText(info_bus.getBusNo());
		getLb_bustype1().setText(info_bus.getBusType());
		getLb_seatcount1().setText(info_bus.getSeatCount()+"");
		getLb_busstate1().setText(info_bus.getBusState());
	}

}


