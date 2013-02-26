package com.sungard.ticketsys.page.ticket;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;

public class SerSetDetail extends JPanel {

	private static final long serialVersionUID = 1L;

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	// 字段名
	private JLabel lb_serdayId = null;
	private JLabel lb_busserNo = null; 
	private JLabel lb_Linename = null;
	private JLabel lb_startaddr = null;
	private JLabel lb_endaddr = null;
	private JLabel lb_departTime = null;
	private JLabel lb_price = null;
	private JLabel lb_perferPrice = null;
	private JLabel lb_maxCount = null;

	// 字段值
	private JLabel lb_serdayIdD = null;
	private JLabel lb_busserNoD = null;
	private JLabel lb_LinenameD = null;
	private JLabel lb_startaddrD = null;
	private JLabel lb_endaddrD = null;
	private JLabel lb_departTimeD = null;
	private JLabel lb_priceD = null;
	private JLabel lb_perferPriceD = null;
	private JLabel lb_maxCountD = null;

	private TickePanel tickePanel = null;

	// 车次信息
	private BusserDay sleBusserDay = null;
	private BusSer currBusSer = null;
	private Line currLine = null;

	protected SerSetDetail() {
	}

	/**
	 * This is the default constructor
	 */
	public SerSetDetail(TickePanel tickePanel) {
		super();
		this.tickePanel = tickePanel;
		initialize();
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(890, 630);
		this.setLayout(null);
		this.add(getNewuser(), null);
	}

	/**
	 * This method initializes detail
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getNewuser() {
		if (newuser == null) {
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(30, 26, 700, 50));
			lb_title.setText("车次详细信息");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 24));
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("车次详细信息"));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
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
			lb_serdayId = new JLabel();
			lb_serdayId.setBounds(new Rectangle(0, 0, 66, 26));
			lb_serdayId.setText("车次号：");
			
			lb_busserNo = new JLabel();
			lb_busserNo.setBounds(new Rectangle(0, 50, 66, 26));
			lb_busserNo.setText("班次号");
			
			lb_departTime = new JLabel();
			lb_departTime.setBounds(new Rectangle(0, 100, 66, 26));
			lb_departTime.setText("发车时间：");
			
			lb_Linename = new JLabel();
			lb_Linename.setBounds(new Rectangle(0, 150, 66, 26));
			lb_Linename.setText("路线名称：");
			
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(0, 200, 66, 26));
			lb_startaddr.setText("起点站：");
			
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(0, 250, 66, 26));
			lb_endaddr.setText("终点站：");
			
			lb_price = new JLabel();
			lb_price.setBounds(new Rectangle(0, 300, 66, 26));
			lb_price.setText("普通票价：");
			
			lb_perferPrice= new JLabel();
			lb_perferPrice.setBounds(new Rectangle(0, 350, 66, 26));
			lb_perferPrice.setText("内部票价：");
			
			lb_maxCount = new JLabel();
			lb_maxCount.setBounds(new Rectangle(0, 400, 66, 26));
			lb_maxCount.setText("总票数：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(220, 92, 68, 470));
			left.add(lb_serdayId, null);
			left.add(lb_busserNo, null);
			left.add(lb_departTime, null);
			left.add(lb_Linename, null);
			left.add(lb_startaddr, null);
			left.add(lb_endaddr, null);
			left.add(lb_price, null);
			left.add(lb_perferPrice, null);
			left.add(lb_maxCount,null);
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
			right.setBounds(new Rectangle(290, 92, 260, 470));
			right.add(getLb_serdayId(), null);
			right.add(getLb_busserNo(), null);
			right.add(getLb_departTime(), null);
			right.add(getLb_Linename(), null);
			right.add(getLb_startaddr(), null);
			right.add(getLb_endaddr(), null);
			right.add(getLb_price(), null);
			right.add(getLb_perferPrice(), null);
			right.add(getLb_maxCount(), null);
		}
		return right;
	}
	

	/**
	 * 车次号
	 * 
	 * @return
	 */
	private JLabel getLb_serdayId() {
		if (lb_serdayIdD == null) {
			lb_serdayIdD = new JLabel();
			lb_serdayIdD.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return lb_serdayIdD;
	}
	
	/**
	 * 班次号
	 * 
	 * @return
	 */
	private JLabel getLb_busserNo() {
		if (lb_busserNoD == null) {
			lb_busserNoD = new JLabel();
			lb_busserNoD.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return lb_busserNoD;
	}
	
	/**
	 * 发车时间
	 * 
	 * @return
	 */
	private JLabel getLb_departTime() {
		if (lb_departTimeD == null) {
			lb_departTimeD = new JLabel();
			lb_departTimeD.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return lb_departTimeD;
	}
	
	/**
	 * 路线名称
	 * 
	 * @return
	 */
	private JLabel getLb_Linename() {
		if (lb_LinenameD == null) {
			lb_LinenameD = new JLabel();
			lb_LinenameD.setBounds(new Rectangle(0, 150, 250, 26));
		}
		return lb_LinenameD;
	}

   
	/**
	 * 起始地点
	 * 
	 * @return
	 */
	private JLabel getLb_startaddr() {
		if (lb_startaddrD == null) {
			lb_startaddrD = new JLabel();
			lb_startaddrD.setBounds(new Rectangle(0, 200, 250, 26));
		}
		return lb_startaddrD;
	}

	/**
	 * 终点站
	 * 
	 * @return
	 */
	private JLabel getLb_endaddr() {
		if (lb_endaddrD == null) {
			lb_endaddrD = new JLabel();
			lb_endaddrD.setBounds(new Rectangle(0, 250, 250, 26));
		}
		return lb_endaddrD;
	}

	
	/**
	 * 普通价
	 * 
	 * @return
	 */
	private JLabel getLb_price() {
		if (lb_priceD == null) {
			lb_priceD = new JLabel();
			lb_priceD.setBounds(new Rectangle(0, 300, 250, 26));
		}
		return lb_priceD;
	}
	
	
	/**
	 * 内部价
	 * 
	 * @return
	 */
	private JLabel getLb_perferPrice() {
		if (lb_perferPriceD == null) {
			lb_perferPriceD = new JLabel();
			lb_perferPriceD.setBounds(new Rectangle(0, 350, 250, 26));
		}
		return lb_perferPriceD;
	}
	
	/**
	 * 总票数
	 * 
	 * @return
	 */
	private JLabel getLb_maxCount() {
		if (lb_maxCountD == null) {
			lb_maxCountD = new JLabel();
			lb_maxCountD.setBounds(new Rectangle(0, 400, 250, 26));
		}
		return lb_maxCountD;
	}





	

	/**
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(350, 570, 63, 23));
			bt_cancel.setText("返回");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					tickePanel.hideOtherPanel();
					tickePanel.getSerSet_search().setVisible(true);
					tickePanel.getSerSet_result().setVisible(true);
				}
			});
		}
		return bt_cancel;
	}

	public void setInfo_serSet(BusserDay sleBusserDay) {
		this.sleBusserDay = sleBusserDay;
		// 发车日期
		String departDate = sleBusserDay.getDepartDate();
		// 获取对应的班次信息
		this.currBusSer = BusSerManager.getInstance().getBusSer(
				sleBusserDay.getBusSerNo());
		// 发车时间
		String departTime = currBusSer.getDepartTime();
		// 获取路线信息
		this.currLine = LineManager.getInstance().getLine(
				currBusSer.getLineName());

		// 设置lable值
		getLb_serdayId().setText(sleBusserDay.getSerdayId());
		getLb_busserNo().setText(sleBusserDay.getBusSerNo());
		getLb_departTime().setText(
				departDate.substring(0, 4) + "-" + departDate.substring(4, 6)
						+ "-" + departDate.substring(6, departDate.length())
						+ " " + departTime.substring(0, 2) + ":"
						+ departTime.substring(2, 4) + ":"
						+ departTime.substring(4, departTime.length()));
		getLb_Linename().setText(currLine.getLineName());
		getLb_startaddr().setText(currLine.getStartAddr());
		getLb_endaddr().setText(currLine.getEndAddr());
		getLb_price().setText(currBusSer.getPrice());
		getLb_perferPrice().setText(currBusSer.getPerferPrice());
		getLb_maxCount().setText(currBusSer.getMaxCount()+"");
		
	}

}

