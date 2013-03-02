-- 20091105 修改考勤统计报表，将其转入后台自动汇总 phy

drop table t_kq_result_month;
create table t_kq_result_month(
  ny varchar2(10),
  bm varchar2(100),
  gh varchar2(100),
  xm varchar2(30),
  kqlb varchar2(100),
  day01  varchar2(10),
  day02  varchar2(10),
  day03  varchar2(10),
  day04  varchar2(10),
  day05  varchar2(10),
  day06  varchar2(10),
  day07  varchar2(10),
  day08  varchar2(10),
  day09  varchar2(10),
  day10  varchar2(10),
  day11  varchar2(10),
  day12  varchar2(10),
  day13  varchar2(10),
  day14  varchar2(10),
  day15  varchar2(10),
  day16  varchar2(10),
  day17  varchar2(10),
  day18  varchar2(10),
  day19  varchar2(10),
  day20  varchar2(10),
  day21  varchar2(10),
  day22  varchar2(10),
  day23  varchar2(10),
  day24  varchar2(10),
  day25  varchar2(10),
  day26  varchar2(10),
  day27  varchar2(10),
  day28  varchar2(10),
  day29  varchar2(10),
  day30  varchar2(10),
  day31  varchar2(10),
  cs  varchar2(20),
  bt  varchar2(20)
);

create index idx_t_kq_result_month_ny on t_kq_result_month(ny);

create table T_ATTSERIAL_HIS as select * from T_ATTSERIAL;
alter table T_ATTSERIAL_HIS
  add constraint pk_t_attserial_his primary key (SERIAL_ID, DEVICE_ID, ATT_DATE);