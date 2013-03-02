-------------------------------------------------
-- Export file for user YKT_CK                 --
-- Created by Yiming.You on 2010-7-21, 0:04:47 --
T_UNPLANSTUDENT.CHECKTIME和T_TEA_STU_DAILYRPT. CHECKTIME字段为VARCHAR2(20),另外，对于T_UNPLANSTUDENT.CHECKTIME字段，不管是当天统计还是处理延迟上传考勤记录，都能正确生成对应的刷卡时间值，对于T_TEA_STU_DAILYRPT. CHECKTIME字段，在当天统计的时候，能正确生成对应的刷卡时间值，但是在之后处理延迟上传考勤记录时，暂时没有去更新T_TEA_STU_DAILYRPT. CHECKTIME字段的值，即如果有延迟上传的考勤记录，那么该考勤对应的T_TEA_STU_DAILYRPT. CHECKTIME字段值不准确，该功能有待以后完善，另外，在package的声明处新添加了两个变量，
--提前刷卡有效时间，以下变量的值单位为天
  lead_time number := 1 / 48;
  --延迟刷卡有效时间
  delay_time number := 1 / 144;
这两个变量用于控制有效刷卡时间，目前有效刷卡时间是控制在上课前30分钟和下课后10分钟内，如果要修改规则，那么修改这两个变量的值，修改完之后重新编译整个package

-------------------------------------------------

spool 1.log

prompt
prompt Creating package CHECK_REPORT
prompt =============================
prompt
CREATE OR REPLACE PACKAGE YKT_CK.check_report as
  type check_record_type is record(
    --学期
    termid T_TEA_STU_DAILYRPT.Term_Id%type,
    --校区
    schoolarea T_TEA_STU_DAILYRPT.AREA_ID%type,
    --班级
    deptcode T_TEA_STU_DAILYRPT.CLASS_ID%type,
    --课程
    courseid T_TEA_STU_DAILYRPT.COURSE_ID%type,
    --学工号
    stuempno T_TEA_STU_DAILYRPT.STUEMP_NO%type,
    --姓名
    custname T_TEA_STU_DAILYRPT.CUST_NAME%type,
    --应到课次
    course_Num T_TEA_STU_DAILYRPT.COURSE_NUM%type,
    --实到课次
    check_Num T_TEA_STU_DAILYRPT.Check_Num%type,
    --迟到课次
    come_Late_Num T_TEA_STU_DAILYRPT.Come_Late_Num%type,
    --早退课次
    leave_Early_Num T_TEA_STU_DAILYRPT.Leave_Early_Num%type,
    --类型
    custtype T_TEA_STU_DAILYRPT.Cust_Type%type,
    --打卡日期
    punchdate YKT_CUR.T_CHECKRECORD.Punchdate%type,
    --打卡时间
    punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --课程开始时间
    begintime T_COURSEPLAN.Begintime%type,
    --课程结束时间
    endtime T_COURSEPLAN.Endtime%type,
    --最早打卡时间
    earliest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --最晚打卡时间
    latest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --课程计划ID
    planid T_COURSEPLAN.Id%type,
    --课程日期
    usedate T_COURSEPLAN.Usedate%type);
  --提前刷卡有效时间
  lead_time number := 1 / 48;
  --延迟刷卡有效时间
  delay_time number := 1 / 144;

  type check_table_type is table of check_record_type index by varchar2(100);
  --入口，统计考勤数据并生成报表
  PROCEDURE proc_check_report;
  --刷新某个时间段的师生考勤报表
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2);
  --重新生成某个课程计划的师生考勤报表
  PROCEDURE proc_refresh_single_report(plan_id in varchar2);
  --统计考勤数据并分析
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type;
  --生成报表
  FUNCTION process_result(check_table in check_table_type) RETURN int;
  --生成历史报表
  FUNCTION process_history_result(check_table in check_table_type) RETURN int;
  --统计不在课程计划中学生的考勤
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int;
  --生成学生学期考勤报表
  FUNCTION generate_student_term_report RETURN int;
  --重新生成某个学期的学生考勤报表
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int;
  --生成教师学期考勤报表
  FUNCTION generate_teacher_term_report RETURN int;
  --重新生成某个学期的教师考勤报表
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int;
  --生成班级学期考勤报表
  FUNCTION generate_class_term_report RETURN int;
  --重新生成某个学期的班级考勤报表
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int;
  --生成班级考勤日报表
  FUNCTION generate_class_daily_report RETURN int;
  --刷新某个时间段的班级日考勤报表
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int;
END check_report;
/

prompt
prompt Creating package body CHECK_REPORT
prompt ==================================
prompt
CREATE OR REPLACE PACKAGE BODY YKT_CK.check_report AS
  --生成报表
  FUNCTION process_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --以下三个变量将根据打卡时间和课程开始时间、结束时间的比较结果计算出值
    --实到次数
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --迟到课次
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --早退课次
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --标识check_record的唯一性
    check_key varchar2(200);
    --存放最早刷卡时间和最晚刷卡时间
    checktime varchar2(14);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --最早打卡时间和最晚打卡时间只有两种可能，同时为null或同时不为null，同时为null说明该学员缺勤
      if check_record.earliest_punchtime is null then
        check_num       := 0;
        come_late_num   := 0;
        leave_early_num := 0;
      elsif check_record.earliest_punchtime = check_record.latest_punchtime then
      dbms_output.put(check_record.earliest_punchtime);
        --当最早打卡时间和最晚打卡时间相等，则该学员在这一堂课中只刷过一次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --刷卡时间在endtime之后，算缺勤
          check_num       := 0;
          come_late_num   := 0;
          leave_early_num := 0;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.earliest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime-----endtime之间，算迟到，早退
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --刷卡时间在begintime之前，算早退
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不等，说明该学员签到和签退都刷过卡
        check_num       := 1;
        come_late_num   := 0;
        leave_early_num := 0;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果最早打卡时间在endtime之后，那么算缺勤
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --下课前20分钟刷卡不算早退
          leave_early_num := 1;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >
           to_date(check_record.punchdate || check_record.begintime,
                   'yyyymmddhh24:mi') and
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --最早刷卡时间在begintime和endtime之间算迟到
          come_late_num := 1;
        end if;
      end if;
      --生成数据
      --如果有刷卡记录，那么记录最早打卡时间和最晚打卡时间
      if check_record.earliest_punchtime is not null then
        checktime := check_record.earliest_punchtime || '--' ||
                     check_record.latest_punchtime;
      else
        checktime := null;
      end if;
      insert into t_tea_stu_dailyrpt tsd
        (tsd.id,
         tsd.term_id,
         tsd.area_id,
         tsd.class_id,
         tsd.course_id,
         tsd.stuemp_no,
         tsd.cust_name,
         tsd.course_num,
         tsd.check_num,
         tsd.come_late_num,
         tsd.leave_early_num,
         tsd.check_date,
         tsd.report_date,
         tsd.cust_type,
         tsd.usedate,
         tsd.checktime)
      values
        (check_key,
         check_record.termid,
         check_record.schoolarea,
         check_record.deptcode,
         check_record.courseid,
         check_record.stuempno,
         check_record.custname,
         1,
         check_num,
         come_late_num,
         leave_early_num,
         check_record.punchdate,
         to_char(sysdate, 'yyyymmdd'),
         check_record.custtype,
         check_record.usedate,
         checktime);
      check_key := check_table.next(check_key);
    end loop;
    return 1;
  
  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_result;

  --生成历史报表
  FUNCTION process_history_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --该结果集为内连接结果，所以最早打卡时间和最晚打卡时间都不为null
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --当最早打卡时间和最晚打卡时间相等，则说明考勤记录中只有一条刷卡记录
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果报表中check_num=0，那么刷卡时间晚于endtime算缺勤，如果报表中check_num=1，那么刷卡时间晚于endtime正常签退
          update t_tea_stu_dailyrpt tsd
             set tsd.leave_early_num = 0
           where tsd.id = check_key;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >=
              to_date(check_record.punchdate || check_record.endtime,
                      'yyyymmddhh24:mi') - 1 / 72 then
          --刷卡时间在endtime-20和endtime之间，如果报表中check_num=0，那么算迟到和早退，如果报表中check_num=1，那么算正常签退
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.leave_early_num = case tsd.check_num
                                         when 0 then
                                          1
                                         else
                                          0
                                       end,
                 tsd.come_late_num  =
                 (case tsd.check_num
                   when 0 then
                    1
                   else
                    tsd.come_late_num
                 end)
           where tsd.id = check_key;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime和endtime-20分钟之间，如果报表中check_num=0，那么算迟到和早退，如果报表中check_num=1，那么算早退
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.leave_early_num = 1,
                 tsd.come_late_num  =
                 (case tsd.check_num
                   when 0 then
                    1
                   else
                    tsd.come_late_num
                 end)
           where tsd.id = check_key;
        else
          --在begintime之前，如果check_num=0,那么算早退，如果check_num=1，那么不变
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.come_late_num   = 0,
                 tsd.leave_early_num = 1
           where tsd.id = check_key;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不相等，则该学员在这一堂课中刷过多次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --最晚刷卡时间在endtime-20分钟之后，算正常签退
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime之前，算正常签到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 0
             where tsd.id = check_key;
          elsif to_date(substr(check_record.punchdate ||
                               check_record.earliest_punchtime,
                               1,
                               12),
                        'yyyymmddhh24mi') <=
                to_date(check_record.punchdate || check_record.endtime,
                        'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime和endtime之间，根据历史check_num判断
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = case tsd.check_num
                                           when 0 then
                                            1
                                           else
                                            tsd.come_late_num
                                         end,
                   tsd.leave_early_num = 0
             where tsd.id = check_key;
          else
            --最早刷卡时间在endtime之后
            update t_tea_stu_dailyrpt tsd
               set tsd.leave_early_num = 0
             where tsd.id = check_key;
          end if;
        else
          --最后刷卡时间在endtime-20分钟之前，算早退
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime之前，算正常签到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          else
            --最早刷卡时间在begintime和endtime之间，算迟到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 1,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          end if;
        end if;
      end if;
      check_key := check_table.next(check_key);
    end loop;
    return 1;
  
  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_history_result;

  --为未选课学生生成报表
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --以下三个变量将根据打卡时间和课程开始时间、结束时间的比较结果计算出值
    --实到次数
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --迟到课次
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --早退课次
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --最早打卡时间和最晚打卡时间同时不为null
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --当最早打卡时间和最晚打卡时间相等，则该学员在这一堂课中只刷过一次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --刷卡时间在endtime之后，算缺勤
          check_num       := 0;
          come_late_num   := 0;
          leave_early_num := 0;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.earliest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime-----endtime之间，算迟到，早退
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --刷卡时间在begintime之前，算早退
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不等，说明该学员签到和签退都刷过卡
        check_num       := 1;
        come_late_num   := 0;
        leave_early_num := 0;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果最早打卡时间在endtime之后，那么算缺勤
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --下课前20分钟刷卡不算早退
          leave_early_num := 1;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >
           to_date(check_record.punchdate || check_record.begintime,
                   'yyyymmddhh24:mi') and
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --最早刷卡时间在begintime和endtime之间算迟到
          come_late_num := 1;
        end if;
      end if;
      --生成数据
      if check_num = 1 then
        insert into T_UNPLANSTUDENT tus
          (tus.id,
           tus.CLASSNO,
           tus.COURSEID,
           tus.STUEMPNO,
           tus.CUSTNAME,
           tus.come_late_num,
           tus.leave_early_num,
           tus.CHECKDATE,
           tus.REPORTDATE,
           tus.ISACTIVATE,
           tus.CHECKTIME,
           tus.usedate)
        values
          (check_key,
           check_record.deptcode,
           check_record.courseid,
           check_record.stuempno,
           check_record.custname,
           come_late_num,
           leave_early_num,
           check_record.punchdate,
           to_char(sysdate, 'yyyymmdd'),
           0,
           check_record.earliest_punchtime || '--' ||
           check_record.latest_punchtime,
           check_record.usedate);
      end if;
      check_key := check_table.next(check_key);
    end loop;
    return 1;
  
  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_unplan_result;

  --统计考勤结果
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type is
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    --已经统计过的考勤记录
    check_record check_record_type;
    --临时考勤记录
    temp_record check_record_type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --提取考勤记录
    loop
      fetch check_cursor
        into temp_record.termid,
             temp_record.schoolarea,
             temp_record.deptcode,
             temp_record.courseid,
             temp_record.stuempno,
             temp_record.custname,
             temp_record.punchdate,
             temp_record.punchtime,
             temp_record.planid,
             temp_record.begintime,
             temp_record.endtime,
             temp_record.usedate;
      exit when check_cursor%NOTFOUND;
      check_key := temp_record.planid || '-' || temp_record.stuempno;
    
      if check_table.exists(check_key) then
        --当check_table中存在对应的考勤记录事时，将当前打卡时间和记录中的最早打卡时间、最晚打卡时间进行比较，并修改对应的值
        check_record := check_table(check_key);
        if to_date(substr(temp_record.punchdate || temp_record.punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') then
          check_record.earliest_punchtime := temp_record.punchtime;
        elsif to_date(substr(temp_record.punchdate || temp_record.punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') then
          check_record.latest_punchtime := temp_record.punchtime;
        end if;
        check_table(check_key) := check_record;
      else
        --当check_table中不存在对应考勤记录，那么将该考勤记录的最早打卡时间和最晚打卡时间都设置为当前的打卡时间，并将该记录放入check_table中
        temp_record.earliest_punchtime := temp_record.punchtime;
        temp_record.latest_punchtime   := temp_record.punchtime;
        if temp_record.deptcode is null then
          temp_record.custtype := 1;
        else
          temp_record.custtype := 0;
        end if;
        check_table(check_key) := temp_record;
      end if;
    end loop;
    return check_table;
  
  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end extract_result;

  --生成报表的入口
  PROCEDURE proc_check_report IS
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  BEGIN
    --提取学生考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.id = cpc.planid
                         and cp.ischeck = 1
                         and cp.usedate = to_char(sysdate, 'yyyymmdd')) t1,
                     ykt_cur.t_customer c
               where c.classname = t1.classno) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.punchdate = to_char(sysdate, 'yyyymmdd')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);
  
    --清空变量，初始化
    check_table.delete();
  
    --提取教师考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.usedate = to_char(sysdate, 'yyyymmdd')) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.punchdate = to_char(sysdate, 'yyyymmdd')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);
    check_table.delete();
  
    --处理延迟的考勤记录(只处理一周内的)
    --统计学生历史（当天上传，刷卡时间在七天以内）考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and to_date(cp.usedate, 'yyyymmdd') >=
                             trunc(sysdate - 7, 'DD')
                         and to_date(cp.usedate, 'yyyymmdd') <
                             trunc(sysdate, 'DD')) t1,
                     ykt_cur.t_customer c
               where c.classname = t1.classno) t
       inner join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.coldate = to_char(sysdate, 'yyyymmdd')
                      and to_date(cr.punchdate, 'yyyymmdd') >=
                          trunc(sysdate - 7, 'DD')
                      and to_date(cr.punchdate, 'yyyymmdd') <
                          trunc(sysdate, 'DD')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生历史考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --更新学生历史考勤报表
    result_code := process_history_result(check_table);
  
    check_table.delete();
  
    --统计教师历史（当天上传，刷卡时间在七天以内）考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and to_date(cp.usedate, 'yyyymmdd') >=
                             trunc(sysdate - 7, 'DD')
                         and to_date(cp.usedate, 'yyyymmdd') <
                             trunc(sysdate, 'DD')) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
       inner join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.coldate = to_char(sysdate, 'yyyymmdd')
                      and to_date(cr.punchdate, 'yyyymmdd') >=
                          trunc(sysdate - 7, 'DD')
                      and to_date(cr.punchdate, 'yyyymmdd') <
                          trunc(sysdate, 'DD')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师历史考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --更新教师历史考勤报表
    result_code := process_history_result(check_table);
    check_table.delete();
  
    --统计不在课程计划中学生的考勤数据
    --先删除七天之内刷卡的不在课程计划中学生的考勤数据   
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD');
    --重新统计七天之内打卡的未在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and to_date(cp.usedate, 'yyyymmdd') between
                     trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD')) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null
                      and to_date(cr.punchdate, 'yyyymmdd') between
                          trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD')) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --生成班级当日考勤报表
    result_code := generate_class_daily_report;
    --生成学生学期考勤报表
    result_code := generate_student_term_report;
    --生成教师学期考勤报表
    result_code := generate_teacher_term_report;
    --生成班级学期考勤报表
    result_code := generate_class_term_report;
  
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_check_report;

  --刷新某个时间段的师生考勤报表、班级考勤日报表
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2) is
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  begin
    --首先，删除指定时间段的师生考勤记录
    delete from t_tea_stu_dailyrpt tsd
     where to_date(tsd.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --提取学生考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.id = cpc.planid) t1,
                     ykt_cur.t_customer c
               where c.classname = t1.classno) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
       where to_date(t.usedate, 'yyyymmdd') between
             to_date(start_date, 'yyyymmdd') and
             to_date(end_date, 'yyyymmdd');
  
    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);
  
    --清空变量，初始化
    check_table.delete();
  
    --提取教师考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
       where to_date(t.usedate, 'yyyymmdd') between
             to_date(start_date, 'yyyymmdd') and
             to_date(end_date, 'yyyymmdd');
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);
    check_table.delete();
  
    --先删除指定时间段内刷卡的不在课程计划中学生的考勤数据   
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --重新统计不在时间段内打卡的未在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and to_date(cp.usedate, 'yyyymmdd') between
                     to_date(start_date, 'yyyymmdd') and
                     to_date(end_date, 'yyyymmdd')) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null
                      and to_date(cr.punchdate, 'yyyymmdd') between
                          to_date(start_date, 'yyyymmdd') and
                          to_date(end_date, 'yyyymmdd')) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --刷新班级考勤日报表
    result_code := refresh_class_daily_report(start_date, end_date);
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end proc_refresh_check_report;

  --重新生成某个课程计划的考勤报表
  PROCEDURE proc_refresh_single_report(plan_id in varchar2) IS
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  BEGIN
    --先删除该课程计划对应的考勤报表记录
    delete from t_tea_stu_dailyrpt t where t.id like plan_id || '-%';
  
    --根据planid先提取学生的考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and cp.id = plan_id) t1,
                     ykt_cur.t_customer c
               where c.classname = t1.classno) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);
  
    --清空变量，初始化
    check_table.delete();
  
    --根据planid提取教师的考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = plan_id) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);
  
    --先删除指定课程计划对应的已刷卡但不在课程计划中学生的考勤数据   
    delete from t_unplanstudent tus where tus.id like plan_id || '-%';
    --重新统计指定课程计划对应的已刷卡但不在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and cp.id = plan_id) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') - 1 / 48 and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') + 1 / 144
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --因为t_class_check_dailyrpt表中没有plan_id字段，所以以下删除和重新生成均为非精确的处理，即先删除与指定plan_id对应的termid,schoolarea,classno,courseid,usedate相等的班级考勤日报表，然后重新生成时也以这些条件来限定
    --删除该plan_id对应的班级考勤日报表数据
    delete from t_class_check_dailyrpt ccd
     where (ccd.term_id, ccd.area_id, ccd.class_id, ccd.course_id,
            ccd.check_date) in
           (select cp.termid,
                   r.schoolarea,
                   cpc.classno,
                   cp.courseid,
                   cp.usedate
              from t_courseplan cp, t_courseplanclass cpc, t_room r
             where cp.id = plan_id
               and cp.id = cpc.planid
               and cp.roomid = r.roomid);
  
    --重新生成该plan_id对应的班级考勤日报表数据
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.cust_type = 0
                 and (tsd.term_id, tsd.area_id, tsd.class_id, tsd.course_id,
                      tsd.usedate) in
                     (select cp.termid,
                             r.schoolarea,
                             cpc.classno,
                             cp.courseid,
                             cp.usedate
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where cp.id = plan_id
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and cp.roomid = r.roomid)
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_refresh_single_report;

  --生成学生学期考勤报表
  FUNCTION generate_student_term_report RETURN int is
  begin
    --在学期结束的当天生成学生考勤学期报表
    insert into t_student_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    --在学期结束后的七天中更新学生学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_student_term_rpt str
       set (str.course_num,
            str.check_num,
            str.come_late_num,
            str.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 0
               and tsd.term_id = str.term_id
               and tsd.area_id = str.area_id
               and tsd.class_id = str.class_id
               and tsd.course_id = str.course_id
               and tsd.stuemp_no = str.stuemp_no
               and tsd.cust_name = str.cust_name
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.class_id,
                      tsd.course_id,
                      tsd.stuemp_no,
                      tsd.cust_name)
     where str.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_student_term_report;
  --重新生成指定termid对应的学生学期考勤报表
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的学生学期考勤报表
    delete from t_student_term_rpt str where str.term_id = termid;
    --重新生成指定termid对应的学生学期考勤报表
    insert into t_student_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    commit;
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_student_term_report;
  --生成教师学期考勤报表
  FUNCTION generate_teacher_term_report RETURN int is
  begin
    --在学期结束的当天生成教师考勤学期报表
    insert into t_teacher_term_rpt
      (id,
       term_id,
       area_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 1
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    --在学期结束后的七天中更新教师学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_teacher_term_rpt ttr
       set (ttr.course_num,
            ttr.check_num,
            ttr.come_late_num,
            ttr.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 1
               and tsd.term_id = ttr.term_id
               and tsd.area_id = ttr.area_id
               and tsd.course_id = ttr.course_id
               and tsd.stuemp_no = ttr.stuemp_no
               and tsd.cust_name = ttr.cust_name
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.course_id,
                      tsd.stuemp_no,
                      tsd.cust_name)
     where ttr.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_teacher_term_report;
  --重新生成指定termid对应的教师学期考勤报表
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的教师学期考勤报表
    delete from t_teacher_term_rpt ttr where ttr.term_id = termid;
    --重新生成指定termid对应的教师学期考勤报表
    insert into t_teacher_term_rpt
      (id,
       term_id,
       area_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 1
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    commit;
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_teacher_term_report;
  --生成班级学期考勤报表
  FUNCTION generate_class_term_report RETURN int is
  begin
    --在学期结束的当天生成班级考勤学期报表
    insert into t_class_check_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id) tmp;
    --在学期结束后的七天中更新班级学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_class_check_term_rpt cctr
       set (cctr.class_people_num,
            cctr.check_num,
            cctr.come_late_num,
            cctr.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 0
               and tsd.term_id = cctr.term_id
               and tsd.area_id = cctr.area_id
               and tsd.class_id = cctr.class_id
               and tsd.course_id = cctr.course_id
             group by tsd.term_id, tsd.area_id, tsd.class_id, tsd.course_id)
     where cctr.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_class_term_report;
  --重新生成指定termid对应的班级学期考勤报表
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的班级学期考勤报表
    delete from t_class_check_term_rpt cctr where cctr.term_id = termid;
    --重新生成指定termid对应的班级学期考勤报表
    insert into t_class_check_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id) tmp;
    commit;
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_class_term_report;
  --生成班级考勤日报表
  FUNCTION generate_class_daily_report RETURN int is
  begin
    --生成当天班级考勤日报表
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.usedate = to_char(sysdate, 'yyyymmdd')
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    --更新班级历史日考勤报表信息（仅更新七天内的考勤报表信息，不包括当天，用于处理考勤记录延迟上传的情况）
    update t_class_check_dailyrpt ccd
       set (ccd.class_people_num,
            ccd.check_num,
            ccd.come_late_num,
            ccd.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd
             where tsd.cust_type = 0
               and tsd.term_id = ccd.term_id
               and tsd.area_id = ccd.area_id
               and tsd.class_id = ccd.class_id
               and tsd.course_id = ccd.course_id
               and tsd.usedate = ccd.check_date
               and to_date(tsd.usedate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.class_id,
                      tsd.course_id,
                      tsd.usedate)
     where to_date(ccd.check_date, 'yyyymmdd') between sysdate - 8 and
           sysdate - 1;
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_class_daily_report;
  --刷新某个时间段的班级日考勤报表
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int is
  begin
    --先删除指定时间段的班级日考勤报表信息
    delete from t_class_check_dailyrpt ccd
     where to_date(ccd.check_date, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --然后重新生成指定时间段的班级日考勤报表信息
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.cust_type = 0
                 and to_date(tsd.usedate, 'yyyymmdd') between
                     to_date(start_date, 'yyyymmdd') and
                     to_date(end_date, 'yyyymmdd')
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    commit;
    return 0;
  
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_class_daily_report;

END check_report;
/


spool off



//教师权限脚本

CREATE OR REPLACE PROCEDURE User_Permission
 IS
   role_id  varchar2(32);
   
  
BEGIN
  
  select id into role_id from ykt_ck.ico_role where role_name='任课老师';

   insert into ykt_ck.usr_person (id,person_code ,person_name)
     select a.stuempno,a.stuempno,a.custname
     from( select t2.stuempno,t2.custname from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno,t2.custname
      having t2.stuempno not in (select id from ykt_ck.usr_person )
      ) A;
   
   insert into  ykt_ck.usr_account(id,account_name,password)
      select a.stuempno,a.stuempno,'96E79218965EB72C92A549DD5A330112'
      from( select t2.stuempno,t2.custname from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno,t2.custname
      having t2.stuempno not in (select id from ykt_ck.usr_account )
      ) A;
  
  
   insert into ykt_ck.ico_account_role 
      select a.stuempno ,role_id
      from( select t2.stuempno from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno 
      having t2.stuempno not in (select account_id from ykt_ck.ico_account_role )
      ) A;
      
      
      
COMMIT;
End    User_Permission ;




