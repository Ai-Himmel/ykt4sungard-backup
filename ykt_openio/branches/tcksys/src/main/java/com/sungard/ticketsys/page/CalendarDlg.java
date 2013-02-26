package com.sungard.ticketsys.page;

import java.awt.*;
import java.awt.event.*;
import javax.swing.table.*;
import java.util.Calendar;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.GregorianCalendar;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;

public class CalendarDlg extends JDialog{
	
	private static final long serialVersionUID = 1L;
	private GregorianCalendar calendar = new GregorianCalendar(); // 日期
	private int intYear = 2000; // 年
	private int intMonth = 1; // 月
	private int intDay = 1; // 日
	private String FinallyDate = " "; // 输出的日期字符窜
	private boolean isRun = true; // 是否在运行
	private int doubleClickedRow = 0;
	private int doubleClickedColumn = 0;
	private boolean isDoubleClicked = false;
	private Date dateValue = null;
	// protected DataComponent m_dataComponent = null; // 关联的用户输入组件

	// 构造一个不可编辑的表模型 model
	private DefaultTableModel model = new DefaultTableModel(new Object[6][7],
			new Object[] { "日 ", "一 ", "二 ", "三 ", "四 ", "五 ", "六 " }) {
		public boolean isCellEditable(int row, int column) {
			return false;
		}
	};

	private TitledBorder titledBorder1;
	private JPanel jPanel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private JSpinner MonthChoice = null; // 月份选择框
	private JSpinner YearScrollbar = null; // 年份选择框
	private JLabel label3 = new JLabel();
	private JLabel label2 = new JLabel();

	private JTable table = new JTable(model) { // 日期表格
		public TableCellRenderer getCellRenderer(int row, int column) {
			return new DefaultTableCellRenderer() { // 日期表格填充并设定组件
				public Component getTableCellRendererComponent(JTable table,
						Object value, boolean isSelected, boolean hasFocus,
						int row, int column) {
					JLabel label = null;
					if (value != null) {
						label = new JLabel(value.toString(), JLabel.CENTER);
						label.setOpaque(true);
						label.setFont(table.getFont());
						if (isSelected) { // 选择日期
							label.setForeground(Color.white);
							label.setBackground(Color.green);
							label.setBorder(BorderFactory
									.createLineBorder(Color.yellow));
						} else { // 没有选择
							label.setForeground(Color.black);
							label.setBackground(Color.white);
						}
						if (isDoubleClicked && doubleClickedRow == row
								&& doubleClickedColumn == column) {
							label.setForeground(Color.white);
							label.setBackground(Color.blue);
							isDoubleClicked = false;
						}
					}
					return label;
				}
			};
		}
	};

	private JScrollPane jScrollPane1 = new JScrollPane(table);
	private JPanel jPanel2 = new JPanel();
	private JLabel TimeLabel = new JLabel();
	private BorderLayout borderLayout2 = new BorderLayout();
	private BorderLayout borderLayout3 = new BorderLayout();
	private BorderLayout borderLayout1 = new BorderLayout();
	private boolean isConfirm = false;

	public CalendarDlg(JFrame parentFrame) {
		super(parentFrame, " ", true);
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
//		Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
		this.setSize(280, 190);
//		setLocation((d.width - getWidth()) / 2, (d.height - getHeight()) / 2);
	}
	
	private void jbInit() throws Exception {
		titledBorder1 = new TitledBorder(" ");
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
//		this.setUndecorated(true);
		this.setModal(true);
		this.setResizable(false);
		this.getContentPane().setLayout(borderLayout3);
		intYear = calendar.get(Calendar.YEAR);
		intMonth = calendar.get(Calendar.MONTH);
		intDay = calendar.get(Calendar.DATE);

		SpinnerDateModel yearModel = new SpinnerDateModel();
		yearModel.setCalendarField(Calendar.YEAR);
		YearScrollbar = new JSpinner(yearModel);
		JSpinner.DateEditor editor2 = new JSpinner.DateEditor(YearScrollbar,
				"yyyy ");
		YearScrollbar.setEditor(editor2);
		YearScrollbar.setBorder(BorderFactory.createEmptyBorder());

		SpinnerDateModel monthModel = new SpinnerDateModel();
		monthModel.setCalendarField(Calendar.MONTH);
		MonthChoice = new JSpinner(monthModel);
		JSpinner.DateEditor editor3 = new JSpinner.DateEditor(MonthChoice,
				"MM ");
		MonthChoice.setEditor(editor3);
		MonthChoice.setBorder(BorderFactory.createEmptyBorder());

		label2.setText("年   ");
		label3.setText("月 ");

		table.getTableHeader().setDefaultRenderer(
				new DefaultTableCellRenderer() {
					public Component getTableCellRendererComponent(
							JTable table, Object value, boolean isSelected,
							boolean hasFocus, int row, int column) {
						if (value != null)
							return new JLabel(value.toString(), JLabel.CENTER);
						else
							return new JLabel();
					}
				});

		table.getTableHeader().setResizingAllowed(false);
		table.getTableHeader().setReorderingAllowed(false);
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		table.setCellSelectionEnabled(true);
		table.setColumnSelectionAllowed(true);
		table.setRowSelectionAllowed(true);
		table.setShowHorizontalLines(false);
		table.setShowVerticalLines(false);
		table.setGridColor(Color.white);
		table.setRowMargin(3);
		table.setAlignmentX((float) 0.0);
		table.setAlignmentY((float) 0.0);
		table.setAutoResizeMode(JTable.AUTO_RESIZE_NEXT_COLUMN);

		jPanel1.setLayout(borderLayout1);
		TimeLabel.setText(" ");
		jPanel2.setLayout(borderLayout2);
		jScrollPane1
				.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		jScrollPane1
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
		jScrollPane1.setBorder(BorderFactory.createLoweredBevelBorder());
		jPanel1.setBorder(BorderFactory.createLineBorder(Color.black));

		this.getContentPane().add(jPanel1, BorderLayout.CENTER);
		jPanel1.add(panel2, BorderLayout.NORTH);

		panel2.add(YearScrollbar);
		panel2.add(label2);
		panel2.add(MonthChoice);
		panel2.add(label3);

		jPanel1.add(jPanel2, BorderLayout.SOUTH);
		jPanel2.add(TimeLabel, BorderLayout.WEST);
		jPanel1.add(jScrollPane1, BorderLayout.CENTER);
		table.setSelectionMode(0);

		MonthChoice.addChangeListener(new javax.swing.event.ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				try {
					java.text.SimpleDateFormat dateFormater = new java.text.SimpleDateFormat(
							"MM");
					intMonth = Integer.parseInt(dateFormater.format(MonthChoice
							.getValue())) - 1;
				} catch (NumberFormatException ex) {
					intMonth = calendar.get(Calendar.MONTH);
					ex.printStackTrace();
				}
				fillDate(intYear, intMonth, intDay);
			}
		});

		YearScrollbar.addChangeListener(new javax.swing.event.ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				try {
					java.text.SimpleDateFormat dateFormater = new java.text.SimpleDateFormat(
							"yyyy");
					intYear = Integer.parseInt(dateFormater
							.format(YearScrollbar.getValue()));
				} catch (NumberFormatException ex) {
					intYear = calendar.get(Calendar.YEAR);
					ex.printStackTrace();
				}
				fillDate(intYear, intMonth, intDay);
			}
		});

		// 日期表格键盘事件处理
		table.addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent e) {
				if (e.getKeyChar() == '\n') {
					if (table.getRowCount() > 0 && table.getSelectedRow() >= 0) {
						int row = table.getSelectedRow() - 1;
						if (row < 0)
							row = table.getRowCount() - 1;
						table.setRowSelectionInterval(row, row);
					}
				}
			}

			public void keyReleased(KeyEvent e) {
				if (table.getRowCount() > 0 && table.getSelectedRow() >= 0) {
					if (e.getKeyChar() == '\n') {
						selectOk();
					} else {
						changeDate();
					}
					SimpleDateFormat sdf = new SimpleDateFormat(
							"yyyy '- 'MM '- 'dd ");
					FinallyDate = sdf.format(calendar.getTime());
					TimeLabel.setText(FinallyDate);
				}
			}

		});

		// 日期表格鼠标动作处理
		table.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				if (e.getClickCount() > 1) { // 不单击
					selectOk();
				} else { // 单击更改日期
					changeDate();
				}

			}
		});
		this.requestFocus();
		table.requestFocus();
		fillDate(intYear, intMonth, intDay);
	}

	private void changeDate() {
		try {
			intDay = Integer.parseInt(table.getValueAt(table.getSelectedRow(),
					table.getSelectedColumn()).toString());
			calendar = new GregorianCalendar(intYear, intMonth, intDay);
		} catch (NumberFormatException ex) {
		} catch (NullPointerException ex) {
		}
	}

	private void selectOk() {
		try {
			Integer.parseInt(table.getValueAt(table.getSelectedRow(),
					table.getSelectedColumn()).toString());
			isConfirm = true;
			isDoubleClicked = true;
			doubleClickedRow = table.getSelectedRow();
			doubleClickedColumn = table.getSelectedColumn();
			table.repaint();
		} catch (Exception ex) {
		}
		setValue(calendar.getTime());
		dispose();
	}

	private void resetData() {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy '- 'MM '- 'dd ");
		FinallyDate = sdf.format(calendar.getTime());
		TimeLabel.setText(FinallyDate);
	}

	// 给 model 添加日期
	private void fillDate(int pYear, int pMonth, int pDay) {
		try {
			calendar = new GregorianCalendar(pYear, pMonth, 1);
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy '- 'MM '- 'dd ");
			FinallyDate = sdf.format(new GregorianCalendar(pYear, pMonth, pDay)
					.getTime()); // 获得当前日期
			TimeLabel.setText(FinallyDate); // 下面显示日期 label

			int maxDayCount = calendar.getActualMaximum(Calendar.DAY_OF_MONTH);
			if (pDay > maxDayCount)
				pDay = maxDayCount;
			int dayOfWeek = calendar.get(Calendar.DAY_OF_WEEK);
			int selectRow = 0;
			int selectCol = dayOfWeek;
			int count = 0;
			int num = 0;

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 7; j++) {
					count++;
					if (count >= dayOfWeek && count < maxDayCount + dayOfWeek) {
						model.setValueAt(String.valueOf(++num), i, j);
						if (num == pDay) {
							selectRow = i;
							selectCol = j;
						}
					} else
						model.setValueAt(null, i, j);
				}
			}
			table.setRowSelectionInterval(selectRow, selectRow);
			table.setColumnSelectionInterval(selectCol, selectCol);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	// 得到选择日期
	public String getFinallyDate() {
		return FinallyDate;
	}

	public void show() {
		isConfirm = false;
		super.show();
	}

	/** 如果选择了日期 */
	public boolean isConfirm() {
		return isConfirm;
	}

	protected void processWindowEvent(WindowEvent e) {
		if (e.getID() == WindowEvent.WINDOW_CLOSING) {
			cancel();
		}
		super.processWindowEvent(e);
	}

	private void cancel() {
		dispose();
	}

	public void run() {
	}

	// 接口实现
	// public void setInputCompnent(DataComponent p_dataComponent) {
	// this.m_dataComponent = p_dataComponent;
	// }

	public void setValue(Object p_value) throws ClassCastException {
		this.dateValue = (Date) p_value;
	}

	public Object getValue() {
		return this.dateValue;
	}

//	public static void main(String[] args) {
//		CalendarDlg calendarDlg = new CalendarDlg(new JFrame());
//		calendarDlg.show();
//	}
}