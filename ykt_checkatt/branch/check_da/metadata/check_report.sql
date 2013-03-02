-------------------------------------------------
-- Export file for user YKT_CK                 --
-- Created by Yiming.You on 2010-7-21, 0:04:47 --
T_UNPLANSTUDENT.CHECKTIME��T_TEA_STU_DAILYRPT. CHECKTIME�ֶ�ΪVARCHAR2(20),���⣬����T_UNPLANSTUDENT.CHECKTIME�ֶΣ������ǵ���ͳ�ƻ��Ǵ����ӳ��ϴ����ڼ�¼��������ȷ���ɶ�Ӧ��ˢ��ʱ��ֵ������T_TEA_STU_DAILYRPT. CHECKTIME�ֶΣ��ڵ���ͳ�Ƶ�ʱ������ȷ���ɶ�Ӧ��ˢ��ʱ��ֵ��������֮�����ӳ��ϴ����ڼ�¼ʱ����ʱû��ȥ����T_TEA_STU_DAILYRPT. CHECKTIME�ֶε�ֵ����������ӳ��ϴ��Ŀ��ڼ�¼����ô�ÿ��ڶ�Ӧ��T_TEA_STU_DAILYRPT. CHECKTIME�ֶ�ֵ��׼ȷ���ù����д��Ժ����ƣ����⣬��package�������������������������
--��ǰˢ����Чʱ�䣬���±�����ֵ��λΪ��
  lead_time number := 1 / 48;
  --�ӳ�ˢ����Чʱ��
  delay_time number := 1 / 144;
�������������ڿ�����Чˢ��ʱ�䣬Ŀǰ��Чˢ��ʱ���ǿ������Ͽ�ǰ30���Ӻ��¿κ�10�����ڣ����Ҫ�޸Ĺ�����ô�޸�������������ֵ���޸���֮�����±�������package

-------------------------------------------------

spool 1.log

prompt
prompt Creating package CHECK_REPORT
prompt =============================
prompt
CREATE OR REPLACE PACKAGE YKT_CK.check_report as
  type check_record_type is record(
    --ѧ��
    termid T_TEA_STU_DAILYRPT.Term_Id%type,
    --У��
    schoolarea T_TEA_STU_DAILYRPT.AREA_ID%type,
    --�༶
    deptcode T_TEA_STU_DAILYRPT.CLASS_ID%type,
    --�γ�
    courseid T_TEA_STU_DAILYRPT.COURSE_ID%type,
    --ѧ����
    stuempno T_TEA_STU_DAILYRPT.STUEMP_NO%type,
    --����
    custname T_TEA_STU_DAILYRPT.CUST_NAME%type,
    --Ӧ���δ�
    course_Num T_TEA_STU_DAILYRPT.COURSE_NUM%type,
    --ʵ���δ�
    check_Num T_TEA_STU_DAILYRPT.Check_Num%type,
    --�ٵ��δ�
    come_Late_Num T_TEA_STU_DAILYRPT.Come_Late_Num%type,
    --���˿δ�
    leave_Early_Num T_TEA_STU_DAILYRPT.Leave_Early_Num%type,
    --����
    custtype T_TEA_STU_DAILYRPT.Cust_Type%type,
    --������
    punchdate YKT_CUR.T_CHECKRECORD.Punchdate%type,
    --��ʱ��
    punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�γ̿�ʼʱ��
    begintime T_COURSEPLAN.Begintime%type,
    --�γ̽���ʱ��
    endtime T_COURSEPLAN.Endtime%type,
    --�����ʱ��
    earliest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�����ʱ��
    latest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�γ̼ƻ�ID
    planid T_COURSEPLAN.Id%type,
    --�γ�����
    usedate T_COURSEPLAN.Usedate%type);
  --��ǰˢ����Чʱ��
  lead_time number := 1 / 48;
  --�ӳ�ˢ����Чʱ��
  delay_time number := 1 / 144;

  type check_table_type is table of check_record_type index by varchar2(100);
  --��ڣ�ͳ�ƿ������ݲ����ɱ���
  PROCEDURE proc_check_report;
  --ˢ��ĳ��ʱ��ε�ʦ�����ڱ���
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2);
  --��������ĳ���γ̼ƻ���ʦ�����ڱ���
  PROCEDURE proc_refresh_single_report(plan_id in varchar2);
  --ͳ�ƿ������ݲ�����
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type;
  --���ɱ���
  FUNCTION process_result(check_table in check_table_type) RETURN int;
  --������ʷ����
  FUNCTION process_history_result(check_table in check_table_type) RETURN int;
  --ͳ�Ʋ��ڿγ̼ƻ���ѧ���Ŀ���
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int;
  --����ѧ��ѧ�ڿ��ڱ���
  FUNCTION generate_student_term_report RETURN int;
  --��������ĳ��ѧ�ڵ�ѧ�����ڱ���
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int;
  --���ɽ�ʦѧ�ڿ��ڱ���
  FUNCTION generate_teacher_term_report RETURN int;
  --��������ĳ��ѧ�ڵĽ�ʦ���ڱ���
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int;
  --���ɰ༶ѧ�ڿ��ڱ���
  FUNCTION generate_class_term_report RETURN int;
  --��������ĳ��ѧ�ڵİ༶���ڱ���
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int;
  --���ɰ༶�����ձ���
  FUNCTION generate_class_daily_report RETURN int;
  --ˢ��ĳ��ʱ��εİ༶�տ��ڱ���
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int;
END check_report;
/

prompt
prompt Creating package body CHECK_REPORT
prompt ==================================
prompt
CREATE OR REPLACE PACKAGE BODY YKT_CK.check_report AS
  --���ɱ���
  FUNCTION process_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --�����������������ݴ�ʱ��Ϳγ̿�ʼʱ�䡢����ʱ��ıȽϽ�������ֵ
    --ʵ������
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --�ٵ��δ�
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --���˿δ�
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
    --�������ˢ��ʱ�������ˢ��ʱ��
    checktime varchar2(14);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�����ʱ��������ʱ��ֻ�����ֿ��ܣ�ͬʱΪnull��ͬʱ��Ϊnull��ͬʱΪnull˵����ѧԱȱ��
      if check_record.earliest_punchtime is null then
        check_num       := 0;
        come_late_num   := 0;
        leave_early_num := 0;
      elsif check_record.earliest_punchtime = check_record.latest_punchtime then
      dbms_output.put(check_record.earliest_punchtime);
        --�������ʱ��������ʱ����ȣ����ѧԱ����һ�ÿ���ֻˢ��һ�ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --ˢ��ʱ����endtime֮����ȱ��
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
          --ˢ��ʱ����begintime-----endtime֮�䣬��ٵ�������
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --ˢ��ʱ����begintime֮ǰ��������
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --�������ʱ��������ʱ�䲻�ȣ�˵����ѧԱǩ����ǩ�˶�ˢ����
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
          --��������ʱ����endtime֮����ô��ȱ��
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --�¿�ǰ20����ˢ����������
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
          --����ˢ��ʱ����begintime��endtime֮����ٵ�
          come_late_num := 1;
        end if;
      end if;
      --��������
      --�����ˢ����¼����ô��¼�����ʱ��������ʱ��
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

  --������ʷ����
  FUNCTION process_history_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�ý����Ϊ�����ӽ�������������ʱ��������ʱ�䶼��Ϊnull
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --�������ʱ��������ʱ����ȣ���˵�����ڼ�¼��ֻ��һ��ˢ����¼
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --���������check_num=0����ôˢ��ʱ������endtime��ȱ�ڣ����������check_num=1����ôˢ��ʱ������endtime����ǩ��
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
          --ˢ��ʱ����endtime-20��endtime֮�䣬���������check_num=0����ô��ٵ������ˣ����������check_num=1����ô������ǩ��
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
          --ˢ��ʱ����begintime��endtime-20����֮�䣬���������check_num=0����ô��ٵ������ˣ����������check_num=1����ô������
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
          --��begintime֮ǰ�����check_num=0,��ô�����ˣ����check_num=1����ô����
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.come_late_num   = 0,
                 tsd.leave_early_num = 1
           where tsd.id = check_key;
        end if;
      else
        --�������ʱ��������ʱ�䲻��ȣ����ѧԱ����һ�ÿ���ˢ����ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --����ˢ��ʱ����endtime-20����֮��������ǩ��
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --����ˢ��ʱ����begintime֮ǰ��������ǩ��
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
            --����ˢ��ʱ����begintime��endtime֮�䣬������ʷcheck_num�ж�
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
            --����ˢ��ʱ����endtime֮��
            update t_tea_stu_dailyrpt tsd
               set tsd.leave_early_num = 0
             where tsd.id = check_key;
          end if;
        else
          --���ˢ��ʱ����endtime-20����֮ǰ��������
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --����ˢ��ʱ����begintime֮ǰ��������ǩ��
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          else
            --����ˢ��ʱ����begintime��endtime֮�䣬��ٵ�
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

  --Ϊδѡ��ѧ�����ɱ���
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --�����������������ݴ�ʱ��Ϳγ̿�ʼʱ�䡢����ʱ��ıȽϽ�������ֵ
    --ʵ������
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --�ٵ��δ�
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --���˿δ�
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�����ʱ��������ʱ��ͬʱ��Ϊnull
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --�������ʱ��������ʱ����ȣ����ѧԱ����һ�ÿ���ֻˢ��һ�ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --ˢ��ʱ����endtime֮����ȱ��
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
          --ˢ��ʱ����begintime-----endtime֮�䣬��ٵ�������
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --ˢ��ʱ����begintime֮ǰ��������
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --�������ʱ��������ʱ�䲻�ȣ�˵����ѧԱǩ����ǩ�˶�ˢ����
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
          --��������ʱ����endtime֮����ô��ȱ��
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --�¿�ǰ20����ˢ����������
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
          --����ˢ��ʱ����begintime��endtime֮����ٵ�
          come_late_num := 1;
        end if;
      end if;
      --��������
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

  --ͳ�ƿ��ڽ��
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type is
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --��ʱ���ڼ�¼
    temp_record check_record_type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --��ȡ���ڼ�¼
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
        --��check_table�д��ڶ�Ӧ�Ŀ��ڼ�¼��ʱ������ǰ��ʱ��ͼ�¼�е������ʱ�䡢�����ʱ����бȽϣ����޸Ķ�Ӧ��ֵ
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
        --��check_table�в����ڶ�Ӧ���ڼ�¼����ô���ÿ��ڼ�¼�������ʱ��������ʱ�䶼����Ϊ��ǰ�Ĵ�ʱ�䣬�����ü�¼����check_table��
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

  --���ɱ�������
  PROCEDURE proc_check_report IS
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  BEGIN
    --��ȡѧ�����ڼ�¼
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
    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);
  
    --��ձ�������ʼ��
    check_table.delete();
  
    --��ȡ��ʦ���ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);
    check_table.delete();
  
    --�����ӳٵĿ��ڼ�¼(ֻ����һ���ڵ�)
    --ͳ��ѧ����ʷ�������ϴ���ˢ��ʱ�����������ڣ�����
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
    --ͳ��ѧ����ʷ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ����ʷ���ڱ���
    result_code := process_history_result(check_table);
  
    check_table.delete();
  
    --ͳ�ƽ�ʦ��ʷ�������ϴ���ˢ��ʱ�����������ڣ�����
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
    --ͳ�ƽ�ʦ��ʷ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���½�ʦ��ʷ���ڱ���
    result_code := process_history_result(check_table);
    check_table.delete();
  
    --ͳ�Ʋ��ڿγ̼ƻ���ѧ���Ŀ�������
    --��ɾ������֮��ˢ���Ĳ��ڿγ̼ƻ���ѧ���Ŀ�������   
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD');
    --����ͳ������֮�ڴ򿨵�δ�ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --���ɰ༶���տ��ڱ���
    result_code := generate_class_daily_report;
    --����ѧ��ѧ�ڿ��ڱ���
    result_code := generate_student_term_report;
    --���ɽ�ʦѧ�ڿ��ڱ���
    result_code := generate_teacher_term_report;
    --���ɰ༶ѧ�ڿ��ڱ���
    result_code := generate_class_term_report;
  
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_check_report;

  --ˢ��ĳ��ʱ��ε�ʦ�����ڱ����༶�����ձ���
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2) is
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  begin
    --���ȣ�ɾ��ָ��ʱ��ε�ʦ�����ڼ�¼
    delete from t_tea_stu_dailyrpt tsd
     where to_date(tsd.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --��ȡѧ�����ڼ�¼
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
  
    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);
  
    --��ձ�������ʼ��
    check_table.delete();
  
    --��ȡ��ʦ���ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);
    check_table.delete();
  
    --��ɾ��ָ��ʱ�����ˢ���Ĳ��ڿγ̼ƻ���ѧ���Ŀ�������   
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --����ͳ�Ʋ���ʱ����ڴ򿨵�δ�ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --ˢ�°༶�����ձ���
    result_code := refresh_class_daily_report(start_date, end_date);
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end proc_refresh_check_report;

  --��������ĳ���γ̼ƻ��Ŀ��ڱ���
  PROCEDURE proc_refresh_single_report(plan_id in varchar2) IS
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  BEGIN
    --��ɾ���ÿγ̼ƻ���Ӧ�Ŀ��ڱ����¼
    delete from t_tea_stu_dailyrpt t where t.id like plan_id || '-%';
  
    --����planid����ȡѧ���Ŀ��ڼ�¼
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
    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);
  
    --��ձ�������ʼ��
    check_table.delete();
  
    --����planid��ȡ��ʦ�Ŀ��ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);
  
    --��ɾ��ָ���γ̼ƻ���Ӧ����ˢ�������ڿγ̼ƻ���ѧ���Ŀ�������   
    delete from t_unplanstudent tus where tus.id like plan_id || '-%';
    --����ͳ��ָ���γ̼ƻ���Ӧ����ˢ�������ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();
  
    --��Ϊt_class_check_dailyrpt����û��plan_id�ֶΣ���������ɾ�����������ɾ�Ϊ�Ǿ�ȷ�Ĵ�������ɾ����ָ��plan_id��Ӧ��termid,schoolarea,classno,courseid,usedate��ȵİ༶�����ձ���Ȼ����������ʱҲ����Щ�������޶�
    --ɾ����plan_id��Ӧ�İ༶�����ձ�������
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
  
    --�������ɸ�plan_id��Ӧ�İ༶�����ձ�������
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

  --����ѧ��ѧ�ڿ��ڱ���
  FUNCTION generate_student_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ�������ѧ������ѧ�ڱ���
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
    --��ѧ�ڽ�����������и���ѧ��ѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
    delete from t_student_term_rpt str where str.term_id = termid;
    --��������ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
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
  --���ɽ�ʦѧ�ڿ��ڱ���
  FUNCTION generate_teacher_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ������ɽ�ʦ����ѧ�ڱ���
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
    --��ѧ�ڽ�����������и��½�ʦѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
    delete from t_teacher_term_rpt ttr where ttr.term_id = termid;
    --��������ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
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
  --���ɰ༶ѧ�ڿ��ڱ���
  FUNCTION generate_class_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ������ɰ༶����ѧ�ڱ���
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
    --��ѧ�ڽ�����������и��°༶ѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
    delete from t_class_check_term_rpt cctr where cctr.term_id = termid;
    --��������ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
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
  --���ɰ༶�����ձ���
  FUNCTION generate_class_daily_report RETURN int is
  begin
    --���ɵ���༶�����ձ���
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
    --���°༶��ʷ�տ��ڱ�����Ϣ�������������ڵĿ��ڱ�����Ϣ�����������죬���ڴ����ڼ�¼�ӳ��ϴ��������
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
  --ˢ��ĳ��ʱ��εİ༶�տ��ڱ���
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int is
  begin
    --��ɾ��ָ��ʱ��εİ༶�տ��ڱ�����Ϣ
    delete from t_class_check_dailyrpt ccd
     where to_date(ccd.check_date, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --Ȼ����������ָ��ʱ��εİ༶�տ��ڱ�����Ϣ
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



//��ʦȨ�޽ű�

CREATE OR REPLACE PROCEDURE User_Permission
 IS
   role_id  varchar2(32);
   
  
BEGIN
  
  select id into role_id from ykt_ck.ico_role where role_name='�ο���ʦ';

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




