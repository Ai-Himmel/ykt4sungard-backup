-- 公交平台数据
insert into t_syskey(keycode,keyname,keyval,maxval,keytype) values('T_PKG','包裹单号',1,99999999,0);

delete from t_unit;
insert into t_unit(unitno,unitname,enabled,begindate,lastdate)values('190121012','大明五洲公交平台',1,20101201,20101222);
insert into t_unit(unitno,unitname,enabled,begindate,lastdate)values('190216018','雄帝公交平台',1,20101201,20101222);

delete from t_unitcfg;
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrip','192.168.103.64','大明公交前置IP');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrport','4000','大明公交前置PORT');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.svrmainfunc','7000','大明公交平台前置下载服务功能号');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.processcmd','python ./busposparse.py','大明公交分析命令');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.processdir','./busdtl','大明公交数据路径');
insert into t_unitcfg(paraname,paraval,paradesc)values('190121012.feedbackcmd','python ./genbusresult.py','大明公交回盘命令');

insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrip','192.168.103.64','雄帝公交前置IP');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrport','4000','雄帝公交前置PORT');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.svrmainfunc','7000','雄帝公交平台前置下载服务功能号');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.processcmd','python ./busposparse.py','雄帝公交分析命令');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.processdir','./busdtl','雄帝公交数据路径');
insert into t_unitcfg(paraname,paraval,paradesc)values('190216018.feedbackcmd','python ./genbusresult.py','雄帝公交回盘命令');

commit;
