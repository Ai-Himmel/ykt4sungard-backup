-- ����ƽ̨����
insert into t_syskey(keycode,keyname,keyval,maxval,keytype) values('T_PKG','��������',1,99999999,0);

delete from t_unit;
insert into t_unit(unitno,unitname,enabled,begindate,lastdate)values('190121012','�������޹���ƽ̨',1,20101201,20101222);
insert into t_unit(unitno,unitname,enabled,begindate,lastdate)values('190216018','�۵۹���ƽ̨',1,20101201,20101222);

delete from t_unitcfg;
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrip','192.168.103.64','��������ǰ��IP');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrport','4000','��������ǰ��PORT');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrmainfunc','7000','��������ƽ̨ǰ�����ط����ܺ�');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.processcmd','python ./busposparse.py','����������������');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.processdir','./busdtl','������������·��');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.feedbackcmd','python ./genbusresult.py','����������������');

insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrip','192.168.103.64','�۵۹���ǰ��IP');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrport','4000','�۵۹���ǰ��PORT');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrmainfunc','7000','�۵۹���ƽ̨ǰ�����ط����ܺ�');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.processcmd','python ./busposparse.py','�۵۹�����������');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.processdir','./busdtl','�۵۹�������·��');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.feedbackcmd','python ./genbusresult.py','�۵۹�����������');

commit;
