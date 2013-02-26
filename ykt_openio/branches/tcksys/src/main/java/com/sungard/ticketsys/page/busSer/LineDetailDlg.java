package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;

/**
 * 路线详细信息
 * @author Xuan.Zhou
 *
 */
public class LineDetailDlg extends JDialog {

	private static final long serialVersionUID = 1L;

	private JPanel detail = null;

	private JPanel left = null;

	private JPanel right = null;

	private JLabel lb_linename = null;

	private JLabel lb_startaddr = null;

	private JLabel lb_linename1 = null;
	
	private JLabel lb_endaddr = null;

	private JButton bt_submit = null;

	private JLabel lb_title = null;

	private JLabel lb_startaddr1 = null;
	
	private JLabel lb_endaddr1 = null;

	private LinePanel linePanel = null;

	public Line info_line=null;

	
	public LineDetailDlg(JFrame parentFrame,LinePanel linePanel) {
		super(parentFrame, " ", true);
		this.linePanel = linePanel;
		this.setModal(true);
		setTitle("路线详细信息");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
		this.setSize(400, 300);
//		setLocation((d.width - getWidth()) / 2, (d.height - getHeight()) / 2);
		this.setLocationRelativeTo(linePanel);

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
			lb_title.setText("路线详细信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			detail = new JPanel();
			detail.setLayout(null);
			detail.setBounds(new Rectangle(0, 0, 400, 300));
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
			lb_linename = new JLabel();
			lb_linename.setBounds(new Rectangle(0, 0,66, 26));
			lb_linename.setText("路线名称：");
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(0, 50, 66, 26));
			lb_startaddr.setText("起点站：");
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(0, 100, 66, 26));
			lb_endaddr.setText("终点站：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 130));
			left.add(lb_linename, null);
			left.add(lb_startaddr, null);
			left.add(lb_endaddr,null);
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
			right.add(getLb_linename1(), null);
			right.add(getLb_startaddr1(), null);
			right.add(getLb_endaddr1(), null);
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
			bt_submit.setBounds(new Rectangle(170, 200, 60, 27));
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

	/**
	 * This method initializes jTextPane_desc
	 *
	 * @return javax.swing.JTextPane
	 */
	private JLabel getLb_startaddr1() {
		if (lb_startaddr1 == null) {
			lb_startaddr1 = new JLabel();
			lb_startaddr1.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return lb_startaddr1;
	}

	public JLabel getLb_linename1() {
		if(lb_linename1==null) {
		   lb_linename1 = new JLabel();
		   lb_linename1.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return lb_linename1;
	}
	
	public JLabel getLb_endaddr1(){
		if(lb_endaddr1 == null){
			lb_endaddr1 = new JLabel(); 
			lb_endaddr1.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return lb_endaddr1;
	}
	

	public void setInfo_line(Line info_line) {
		this.info_line = info_line;
		getLb_linename1().setText(info_line.getLineName());
		getLb_startaddr1().setText(info_line.getStartAddr());
		getLb_endaddr1().setText(info_line.getEndAddr());
	}

}

