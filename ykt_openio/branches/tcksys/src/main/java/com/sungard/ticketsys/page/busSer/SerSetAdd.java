package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import com.sungard.ticketsys.common.Configuration;
import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.page.CalendarDlg;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.SerSetManager;

public class SerSetAdd extends JDialog  {

	private static final long serialVersionUID = 1L;

	private IndexFrame indexFrame = null;

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;

	private JLabel lb_startDate = null;
	private JLabel lb_endDate = null;
	private JLabel lb_week = null;
	private JLabel lb_serno = null;

	private JTextField tf_startDate = null;
	private JButton bt_startDate = null;
	private CalendarDlg StartcalendarDlg = new CalendarDlg(indexFrame);

	private JTextField tf_endDate = null;
	private JButton bt_endDate = null;
	private CalendarDlg endcalendarDlg = new CalendarDlg(indexFrame);

	private JCheckBox cb_monday = null;
	private JCheckBox cb_tuesday = null;
	private JCheckBox cb_wednesday = null;
	private JCheckBox cb_thursday = null;
	private JCheckBox cb_friday = null;
	private JCheckBox cb_saturday = null;
	private JCheckBox cb_sunday = null;

	// 班次列表
//	public JTable busSer = null;
	private JScrollPane busser_list = null;
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][3];
	private Object columnName[] = { "", "班次号", "发车时间" };

	private JButton bt_reset = null;
	private List<BusSer> busSers = null;

	// 输入的值
	Date startDate = null;
	Date endDate = null;
	Calendar cstart = Calendar.getInstance();
	Calendar cend = Calendar.getInstance();
	private List<BusSer> selbusSers = null;
	List<Integer> weekDays = null;

	private SerSetPanel serSetPanel = null;

	public SerSetAdd(JFrame parentFrame, SerSetPanel serSetPanel) {
		super(parentFrame, " ", true);
		this.serSetPanel = serSetPanel;
		this.setModal(true);
		setTitle("班次排版");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 480);
		this.setLocationRelativeTo(serSetPanel);
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
			lb_title.setText("班次排版");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 20));
			
			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 370, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);
			
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 400, 480));
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
			lb_startDate = new JLabel();
			lb_startDate.setBounds(new Rectangle(0, 0, 66, 26));
			lb_startDate.setText("起始日期：");
			lb_endDate = new JLabel();
			lb_endDate.setBounds(new Rectangle(0, 50, 66, 26));
			lb_endDate.setText("结束日期：");
			lb_week = new JLabel();
			lb_week.setBounds(new Rectangle(0, 100, 66, 26));
			lb_week.setText("星期：");
			lb_serno = new JLabel();
			lb_serno.setBounds(new Rectangle(0, 150, 66, 26));
			lb_serno.setText("班次：");

			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 300));
			left.add(lb_startDate, null);
			left.add(lb_endDate, null);
			left.add(lb_week, null);
			left.add(lb_serno, null);

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
			right.setBounds(new Rectangle(100, 60, 300, 300));
			right.add(getTf_startDate(), null);
			right.add(getBt_startDate(), null);
			right.add(getTf_endDate(), null);
			right.add(getBt_endDate(), null);
			right.add(getCb_sunday(), null);
			right.add(getCb_monday(), null);
			right.add(getCb_tuesday(), null);
			right.add(getCb_wednesday(), null);
			right.add(getCb_thursday(), null);
			right.add(getCb_friday(), null);
			right.add(getCb_saturday(), null);

			right.add(getBusser_list(), null);
		}
		return right;
	}

	private JCheckBox getCb_saturday() {
		if (cb_saturday == null) {
			cb_saturday = new JCheckBox();
			cb_saturday.setBounds(new Rectangle(240, 100, 40, 26));
			cb_saturday.setText("六");
			cb_saturday.setSelected(true);
		}
		return cb_saturday;
	}

	private JCheckBox getCb_friday() {
		if (cb_friday == null) {
			cb_friday = new JCheckBox();
			cb_friday.setBounds(new Rectangle(200, 100, 40, 26));
			cb_friday.setText("五");
			cb_friday.setSelected(true);
		}
		return cb_friday;
	}

	private JCheckBox getCb_thursday() {
		if (cb_thursday == null) {
			cb_thursday = new JCheckBox();
			cb_thursday.setBounds(new Rectangle(160, 100, 40, 26));
			cb_thursday.setText("四");
			cb_thursday.setSelected(true);
		}
		return cb_thursday;
	}

	private JCheckBox getCb_wednesday() {
		if (cb_wednesday == null) {
			cb_wednesday = new JCheckBox();
			cb_wednesday.setBounds(new Rectangle(120, 100, 40, 26));
			cb_wednesday.setText("三");
			cb_wednesday.setSelected(true);
		}
		return cb_wednesday;
	}

	private JCheckBox getCb_tuesday() {
		if (cb_tuesday == null) {
			cb_tuesday = new JCheckBox();
			cb_tuesday.setBounds(new Rectangle(80, 100, 40, 26));
			cb_tuesday.setText("二");
			cb_tuesday.setSelected(true);
		}
		return cb_tuesday;

	}
	
	private JCheckBox getCb_monday() {
		if (cb_monday == null) {
			cb_monday = new JCheckBox();
			cb_monday.setBounds(new Rectangle(40, 100, 40, 26));
			cb_monday.setText("一");
			cb_monday.setSelected(true);
		}
		return cb_monday;
	}

	private JCheckBox getCb_sunday() {
		if (cb_sunday == null) {
			cb_sunday = new JCheckBox();
			cb_sunday.setBounds(new Rectangle(0, 100, 40, 26));
			cb_sunday.setText("天");
			cb_sunday.setSelected(true);
		}
		return cb_sunday;
	}

	

	/**
	 * This method initializes user_list1
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getBusser_list() {
		if (busser_list == null) {
			busser_list = new JScrollPane();
			busser_list.setBounds(new Rectangle(0, 150, 250, 150));
		}
		busser_list.setViewportView(getBusser());
		return busser_list;
	}

	public JTable getBusser() {
		busSers = BusSerManager.getInstance().getAllBusSer();
		setData(busSers);
		JTable busSer = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < busSers.size()) {
						return true;
					} else {
						return false;
					}
				}

				public void setValueAt(Object value, int row, int col) {
					data[row][col] = value;
				}

				public Object getValueAt(int row, int col) {
					return data[row][col];
				}

			});

			busSer.setShowHorizontalLines(false);
			busSer.setShowVerticalLines(false);
			// 设置第一列类型为Boolean类型
			TableColumn column0 = busSer.getColumnModel().getColumn(0);
			column0.setCellEditor(busSer.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(busSer.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);

			TableColumn column1 = busSer.getColumnModel().getColumn(1);
			column1.setPreferredWidth(100);

			TableColumn column2 = busSer.getColumnModel().getColumn(2);
			column2.setPreferredWidth(130);
//		} else {
//			busSer.updateUI();
//			busSer.repaint();
//		}
		return busSer;
	}

	private void setData(List<BusSer> busSers) {
		if (busSers != null) {
			data = new Object[busSers.size()][3];
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
			}
			for (int i = 0; i < busSers.size(); i++) {
				data[i][0] = false;
				BusSer myBusSer = (BusSer) busSers.get(i);
				data[i][1] = myBusSer.getSerilNo();
				String oldDepartTime = myBusSer.getDepartTime();
				data[i][2] = oldDepartTime.substring(0, 2) + "时"
						+ oldDepartTime.substring(2, 4) + "分"
						+ oldDepartTime.substring(4, oldDepartTime.length())
						+ "秒";
			}
		} else {
			data = new Object[0][3];
		}
	}

	/**
	 * This method initializes tf_endDate
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_endDate() {
		if (tf_endDate == null) {
			tf_endDate = new JTextField();
			tf_endDate.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return tf_endDate;
	}

	private JButton getBt_endDate() {
		if (bt_endDate == null) {
			bt_endDate = new JButton();
			bt_endDate.setBounds(new Rectangle(250, 54, 20, 20));
			bt_endDate.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_endDate.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_endDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (endcalendarDlg == null) {
						endcalendarDlg = new CalendarDlg(indexFrame);
					}
					
					Point p =  bt_endDate.getLocationOnScreen(); 
					p.y = p.y + bt_endDate.getHeight(); 
					p.x = p.x-endcalendarDlg.getWidth();
					endcalendarDlg.setLocation(p);
					endcalendarDlg.show();
					SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
					if(endcalendarDlg.getValue()!=null){
						String date = sdf.format(endcalendarDlg.getValue());
						getTf_endDate().setText(date);
					}
					
				}
			});
		}
		return bt_endDate;
	}

	/**
	 * This method initializes tf_startDate
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_startDate() {
		if (tf_startDate == null) {
			tf_startDate = new JTextField();
			tf_startDate.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return tf_startDate;
	}

	private JButton getBt_startDate() {
		if (bt_startDate == null) {
			bt_startDate = new JButton();
			bt_startDate.setBounds(new Rectangle(250, 4, 20, 20));
			bt_startDate.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_startDate.setCursor(Cursor
					.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_startDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (StartcalendarDlg == null) {
						StartcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_startDate.getLocationOnScreen(); 
					p.y = p.y + bt_startDate.getHeight(); 
					p.x = p.x-StartcalendarDlg.getWidth();
					StartcalendarDlg.setLocation(p);
					StartcalendarDlg.show();
					SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
					if(StartcalendarDlg.getValue()!=null){
						String date = sdf.format(StartcalendarDlg.getValue());
						getTf_startDate().setText(date);
					}
					
				}
			});
		}
		return bt_startDate;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(60, 420, 63, 23));
			bt_submit.setText("提交");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean flag = true;
					SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
					Calendar cnow = Calendar.getInstance();
					cnow.setTime(new Date());

					if ("".equals(getTf_startDate().getText().trim())) {
						lb_error.setText("提交失败：起始日期不能为空，请重新输入!");
						flag = false;
					}

					if (flag && "".equals(getTf_endDate().getText().trim())) {
						lb_error.setText("提交失败：结束日期不能为空，请重新输入!");
						flag = false;
					}

					if (flag && !"".equals(getTf_startDate().getText().trim())
							&& !"".equals(getTf_endDate().getText().trim())) {

						try {
							startDate = format.parse(getTf_startDate()
									.getText());
							endDate = format.parse(getTf_endDate().getText());
						} catch (ParseException e1) {
							lb_error.setText("提交失败：日期格式不正确，正确格式为：yyyyMMdd，请重新输入!");
							flag = false;
						}
						cstart.setTime(startDate);
						cend.setTime(endDate);

						if (flag && !cnow.before(cstart)) {
							lb_error.setText("提交失败：只能排版今天之后的车次，请重新输入!");
							flag = false;
						}
						if (flag && !cnow.before(cend)) {
						    lb_error.setText("提交失败：只能排版今天之后的车次，请重新输入!");	
							flag = false;
						}
						if (flag && cstart.after(cend)) {
							if (cnow.after(cend)) {
								lb_error.setText("提交失败：结束日期不能在起始日期自前，请重新输入!");
								flag = false;
							}
						}
						
						long diffdate = MyFormat.dateDiff(getTf_startDate().getText().trim(), getTf_endDate().getText().trim(), "yyyyMMdd");
				        String quaDateS = Configuration.getProperty(Constants.QUA_DATE);
				        int quaDate = Integer.parseInt(quaDateS.trim());
						if(flag && diffdate>quaDate){
							lb_error.setText("提交失败：起始日期与结束日期间隔太长，请设置在["+quaDate+"]天内!");
							flag = false;
						}
						
					}

					// 获取星期列表
					flag = getweekDays(flag);

					boolean select_one = false; // 判断有没有选择的标志，至少要选择一项
					selbusSers = new ArrayList<BusSer>();
					for (int i = 0; i < data.length; i++) {
						if (flag && data[i][0] == Boolean.TRUE) {
							select_one = Boolean.TRUE;
							String serilNo = data[i][1].toString();
							@SuppressWarnings("unused")
							BusSer newBusSer = BusSerManager.getInstance()
									.getBusSer(serilNo);
							selbusSers.add(newBusSer);
						}
					}
					if (flag && select_one == Boolean.FALSE) { // 没有选择
						lb_error.setText("提交失败：至少选择一条班次，请重新输入!");
						flag = false;
					}

					if (flag) {
							try {
								SerSetManager.getInstance().setSerDay(cstart,cend, weekDays, selbusSers);
								
								//清空编辑页面
								getTf_startDate().setText("");
								getTf_endDate().setText("");
								cb_monday.setSelected(true);
								cb_tuesday.setSelected(true);
								cb_wednesday.setSelected(true);
								cb_thursday.setSelected(true);
								cb_friday.setSelected(true);
								cb_saturday.setSelected(true);
								cb_sunday.setSelected(true);
								// 清空班次列表选择
								removeSelectSerNo();
								

								//关闭对话框
								dispose();
								
								//提示新增成功
								JOptionPane.showMessageDialog(serSetPanel, "班次排版成功","SUCCESS", JOptionPane.NO_OPTION);

								
								// 返回查询页面
								serSetPanel.getSerSet();
								serSetPanel.getSelect_all().setSelected(false);
								
							} catch (Exception e1) {
								JOptionPane.showMessageDialog(indexFrame
										.getSerSetPanel(), "车次排版失败",
										"ERROE!!!", JOptionPane.ERROR_MESSAGE);
							}

							
						}
					}

			});
		}
		return bt_submit;
	}

	private Boolean getweekDays(boolean flag) {
		weekDays = new ArrayList<Integer>();
		if (cb_sunday.isSelected()) {
			weekDays.add(0);
		}
		if (cb_monday.isSelected()) {
			weekDays.add(1);
		}
		if (cb_tuesday.isSelected()) {
			weekDays.add(2);
		}
		if (cb_wednesday.isSelected()) {
			weekDays.add(3);
		}
		if (cb_thursday.isSelected()) {
			weekDays.add(4);
		}
		if (cb_friday.isSelected()) {
			weekDays.add(5);
		}
		if (cb_saturday.isSelected()) {
			weekDays.add(6);
		}
		if (weekDays == null || weekDays.size() < 1) {
			lb_error.setText("提交失败：请选择星期，请重新输入!");
			flag = false;
		}

		return flag;
	}

	/**
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(250, 420, 63, 23));
			bt_cancel.setText("取消");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_startDate().setText("");
					getTf_endDate().setText("");
					cb_monday.setSelected(true);
					cb_tuesday.setSelected(true);
					cb_wednesday.setSelected(true);
					cb_thursday.setSelected(true);
					cb_friday.setSelected(true);
					cb_saturday.setSelected(true);
					cb_sunday.setSelected(true);
					// 清空班次列表选择
					removeSelectSerNo();
					
					dispose();
				}
			});
		}
		return bt_cancel;
	}

	// 清空班次列表选择
	private void removeSelectSerNo() {
		for (int i = 0; i < data.length; i++) {
			data[i][0] = Boolean.FALSE;
		}
		// repaint()重画整个图，user.updateUI()刷新user表
		getBusser().repaint();
		getBusser_list().setVisible(false);
		getBusser_list().setVisible(true);
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(160, 420, 63, 23));
			bt_reset.setText("重置");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_startDate().setText("");
					getTf_endDate().setText("");
					StartcalendarDlg.setValue(null);
					endcalendarDlg.setValue(null);
					cb_monday.setSelected(true);
					cb_tuesday.setSelected(true);
					cb_wednesday.setSelected(true);
					cb_thursday.setSelected(true);
					cb_friday.setSelected(true);
					cb_saturday.setSelected(true);
					cb_sunday.setSelected(true);
					// 清空班次列表选择
					removeSelectSerNo();
				}
			});
		}
		return bt_reset;
	}
	
	/**
	 * 获取图片资源
	 * 
	 * @param url
	 * @return
	 */
	private ImageIcon getIcon(String url) {
		ClassLoader cl = this.getClass().getClassLoader();
		ImageIcon icon = new ImageIcon(cl.getResource(url));
		return icon;
	}

}
