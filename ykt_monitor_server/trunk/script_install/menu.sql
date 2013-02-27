--安工大更新 需要执行此sql 才能增加新功能
insert into ykt_mon.ico_menu (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1406', '14', '终端设备状态统计', 'termdeviceStatus.do?method=caculateDeviceStatus', '', 'main', '', '', '', 420);

