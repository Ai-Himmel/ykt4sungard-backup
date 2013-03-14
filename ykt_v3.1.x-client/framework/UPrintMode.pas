unit UPrintMode;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UPrintMode
   <What>通用的查询结果打印
   <Written By> 曾创能、Huang YanLai (黄燕来)
   <History>
**********************************************}


{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit> UPrintMode
   <What> 为支持华斯上线，客户要求打印DBGrid需要网格线。
   <Written By> Zhu pengfei (朱朋飞)
   <History>
   <HowToDo>增加一个华斯的条件编译。
            每个打印的单元都负责打印它的边框。
            更正打印bottom的那条横线。
**********************************************}

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit> UPrintMode
   <What>  一卡通要求
   <Written By> wang suna (王苏娜)
   <History>
   <HowToDo> 客户要求打印DBGrid的header需要网格线
              打印listview的方法
              打印stringgrid的方法
              预览listview的方法
              预览stringgrid的方法
**********************************************}

{$DEFINE SHENZHENHUASI}

interface

uses Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
     RPDB,TextoutScripts,StdCtrls, Grids, DBGrids, Db,RPEasyReports,
     RPDBVCL,RPCtrls,RPDefines,RPProcessors, Buttons,ExtUtils,
     KSClientConsts,KsFrameWorks,FileCtrl, ImageCtrls, ExtCtrls, UICtrls,
     Spin,Printers,PrintDevices,comctrls, RzRadChk, RzButton;

const
  DefaultTextMargin = 15;
  DefaultCompanyHeadingTitleLeft = 50;
  //DefaultPrintDateTimeTitleWidth =

type
  TfmPrintMode = class(TForm)
    PrinterSetupDialog: TPrinterSetupDialog;
    SaveDialog: TSaveDialog;
    UIPanel1: TUIPanel;
    GroupBox1: TGroupBox;
    rbToPrinter: TRzRadioButton;
    rbToFile: TRzRadioButton;
    edFileName: TEdit;
    btnPrint: TBitBtn;
    btnPreview: TBitBtn;
    btnSetPrinter: TBitBtn;
    ImageButton4: TBitBtn;
    btnSave: TBitBtn;
    lbPrinterInfo: TLabel;
    Label3: TLabel;
    ckPageRange: TRzCheckBox;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    lbStartPage: TLabel;
    lbEndPage: TLabel;
    edStart: TSpinEdit;
    edEnd: TSpinEdit;
    rbToExcelFile: TRzRadioButton;
    SaveDialog1: TSaveDialog;
    rbToHTMLFile: TRzRadioButton;
    SaveDialog2: TSaveDialog;
    procedure btnPrintClick(Sender: TObject);
    procedure btnPreviewClick(Sender: TObject);
    procedure PrintModeChanged(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnSetPrinter1Click(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnSetPrinterClick(Sender: TObject);
    procedure edFileNameExit(Sender: TObject);
    procedure ckPageRangeClick(Sender: TObject);
    procedure frCustReportGetValue(const ParName: String;
      var ParValue: Variant);
  private
    { Private declarations }
    dbGridEx:TdbGrid;
    FPrinterInstalled : Boolean;

    //wsn 20041106 加入listview和stringgrid预览和打印哈哈
    FPrintListView: Boolean;
    FListView:TListView ;
    FDataSet : TDataSet;
    FStringGrid:TStringGrid;
    FPrintStringGrid:Boolean;
    
    RptTitleEx:string;
    LRptTitleEx:String;
    RRptTitleEx:String;
    RptDateSpotTitleEx:String;
    RptFootTitleEx:String;

    //hanjiwei 20080926新的报表预览打印变量
    RTitle_N:string;          //报表标题
    RDept_N:string;           //报表单位
    RDesc_N:string;           //报表描述
    RTitDate_N:string;        //报表标题日期
    RDate_N:string;           //报表日期
    ROper_N:string;           //操作员

    procedure UpdatePrinterInfo;
    function  GetDefaultOutputFileName(const FileExt : string) : string;
    {
    procedure previewDBGrid_new(
              dbGrid:TDBGrid;
              Title, Dept,Desc,TitDate,Date,oper:string);
    }
    //procedure createData_new(DbGrid:TDbGrid);
  public
    { Public declarations }

    procedure Execute(dbGrid:TdbGrid;const RptTitle:string;const LRptTitle:String;
        const RRptTitle:String;const RptDateSpotTitle:String);overload;

    procedure Execute(ListView:TListView;DataSet:TDataSet; const RptTitle : string;
        const LRptTitle:string;const RRptTitle:string;const RptDateSpotTitle:String);overload;

    procedure Execute(StringGrid:TStringGrid;const RptTitle:String;
        const LRptTitle:String;const RRptTitle:String;const RptDateSpotTitle:String);overload;
  end;

var
  fmPrintMode: TfmPrintMode;

implementation

uses UPrintTemplate, KSFrameWorkUtils, DataUsageUtils, LogFile;

{$R *.DFM}
const
  {$IFDEF SHENZHENHUASI}
    Delta=0;
  {$ELSE}
    Delta=5;
  {$ENDIF}

  
{wsn 20050111 调整页头标签的位置}
procedure RefreshHeadingTitlePositionInfo(FDialog:TfmPrintTemplate);
begin
  with FDialog do
  begin
    With HeaderBand do
    begin
      lbHeaderTitle.Left:=DefaultCompanyHeadingTitleLeft;
      lbSysDate.Left:= (HeaderBand.Width- lbSysDate.Width-DefaultCompanyHeadingTitleLeft);
    end;
  end;
end;


//  *****         Part PrintDBGrid      *****
procedure CreateTitle(FTitleBand:TRDSimpleBand;const FTitle:string;const FLTitle:String;
    const FRTitle:String;const FSpotTitle:String);
begin
  with TRDlabel.create(FTitleBand) do
  begin
    Name:='CurrentMainTitle';
    Parent:=FtitleBand;
    Valign:=VaTop;
    HAlign:=HaCenter;
    caption:=Ftitle;
    parentFont:=true;
    width:=FtitleBand.width;
    height:=Trunc(FtitleBand.height/3);
    top:=0;
  end;
  if  Trim(FSpotTitle)<>'' then
  begin
    with TRDlabel.create(FTitleBand) do
    begin             //wsn 20041113 增加打印时间段的label
      Name:='CurrentSpotTitle';
      Parent:=FtitleBand;
      Valign:=VaCenter;
      HAlign:=HaCenter;
      caption:=FSpotTitle;
      parentFont:=False;
      Font.Size:=9;
      width:=FtitleBand.width;
      height:=Trunc(FtitleBand.height/3);
      top:= Trunc(FtitleBand.height/3);
    end;
  end;
  if  Trim(FLTitle)<>'' then
  begin           //wsn 20041110 增加打印左标题
    with TRDlabel.create(FTitleBand) do
    begin
      Name:='CurrentLeftTitle';
      Parent:=FtitleBand;
      Valign:=VaCenter;
      HAlign:=HaLeft;
      caption:=FLTitle;
      parentFont:=False;
      Font.Size:=9;
      Font.Style:=[];
      top:= Trunc(FtitleBand.height*2/3);
      width:=Trunc(FtitleBand.width/2);
      height:=Trunc(FtitleBand.height/3);
      left:=0;
    end;
  end;
  if Trim(FRTitle)<>'' then
  begin           //wsn 20041110 增加打印右标题
    with TRDlabel.create(FTitleBand) do
    begin
      Name:='CurrentRightTitle';
      Parent:=FtitleBand;
      Valign:=VaCenter;
      HAlign:=HaRight;
      caption:=FRTitle;
      parentFont:=False;
      Font.Size:=9;
      Font.Style:=[];
      top:= Trunc(FtitleBand.height*2/3);
      Left:= Trunc(FtitleBand.width/2);
      width:=Trunc(FtitleBand.width/2)-100;
      height:=Trunc(FtitleBand.height/3);
    end;
  end;
end;


procedure CreateStringGridData(ColHeaderBand,DataBand:TRDSimpleBand;StringGrid:TStringGrid);
var
  i,j,FCurLeft,Fcount,FDisplayWidth:integer;
  FRDLabel:TRDLabel;
  FRowCount:Integer;
  FDefaultHeadHeight:Integer;
  FDefaultDataHeight:Integer;
begin

  FcurLeft:=0;
  Fcount:=StringGrid.ColCount;
  FRowCount:= StringGrid.RowCount;
  FDefaultHeadHeight:= ColHeaderBand.Height-4;
  ColHeaderBand.Height:=ColHeaderBand.Height;

  FDefaultDataHeight:=Databand.Height-4;
  Databand.Height:=Databand.Height*(FRowCount-1);

  for I:=1 to Fcount-1 do
  begin
   if StringGrid.ColWidths[I]<0 then
      Continue;

    //生成报表的列标题
    FDisplayWidth:=ColHeaderBand.Width-FcurLeft;
    //如果显示不下就不打印该列
    if (FDisplayWidth < StringGrid.ColWidths[I]) then FDisplayWidth:=-1
    else FDisplayWidth :=StringGrid.ColWidths[I];
    if FDisplayWidth<0 then exit;

    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
      Color:=StringGrid.FixedColor;
      Parent:=ColHeaderBand;
      Font.Assign(StringGrid.Font);
      caption:=Trim(StringGrid.Cells[I,0]);
      height:=FDefaultHeadHeight;
      width:=FDisplayWidth;
      HAlign:=haCenter;
      VAlign:=vaCenter;
      Frame.Bottom :=0;
      left:=FCurLeft;
      Top:=0* FDefaultHeadHeight;
      //wsn 增加－－为header增加band
      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := 0;
         Right := 0;
       end;
      {$ENDIF}
    end;


    for j:=1 to FRowCount-1 do
    begin
    FRDLabel:=TRDlabel.create(DataBand);
    with FRDLabel do
    begin
      if j=0 then  Color:=StringGrid.FixedColor;
      Parent:=ColHeaderBand;
      Font.Assign(StringGrid.Font);
      caption:=Trim(StringGrid.Cells[I,j]);
      height:=FDefaultDataHeight;
      width:=FDisplayWidth;
      HAlign:=haCenter;
      VAlign:=vaCenter;
      Frame.Bottom :=0;
      left:=FCurLeft;
      Top:=j* FDefaultDataHeight;
      //wsn 增加－－为header增加band
      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := 0;
         Right := 0;
       end;
      {$ENDIF}
    end;
    end;
    Fcurleft:=FcurLeft+FDisplayWidth+Delta;
  end;
end;


//wsn 20041014 为了打印listview中的内容
procedure CreateListViewData(ColHeaderBand,DataBand:TRDSimpleBand;ListView:TListView;DataSet:TDataSet);
var
  i,FCurLeft,Fcount,FDisplayWidth:integer;
  FRDLabel:TRDLabel;
  j:Integer;
  FRowCount:Integer;
  FDefaultHeight:Integer;
begin
  ShowMessage('打印listview中的内容');
  FcurLeft:=0;
  Fcount:=2;

  FRowCount:= DataSet.FieldCount;  {字段的数目}
  FDefaultHeight:= ColHeaderBand.Height;
  ColHeaderBand.Height:=ColHeaderBand.Height*FRowCount;


    //生成报表的列标题
    FDisplayWidth:=ColHeaderBand.Width-FcurLeft;
    if FDisplayWidth<0 then exit;

    j:=0;
//－－－－－－－－－－－－打印第一列标题栏－－－－－－－－－－－－－
    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
    Parent:=ColHeaderBand;
    caption:='项目';
    height:=FDefaultHeight;
    width:=FDisplayWidth;
    HAlign:=haCenter;
    VAlign:=vaCenter;
    Frame.Bottom :=0;
    left:=FCurLeft;
    Top:=j* FDefaultHeight;
    //wsn 增加－－为header增加band
    {$IFDEF SHENZHENHUASI}
     with Frame do
     begin
       Left := 0;
       Top := 0;
       Bottom := 0;
       Right := 0;
     end;
    {$ENDIF}
    end;

    for j:=0 to FRowCount-1 do
    begin
    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
      //if j=0 then  Color:=StringGrid.FixedColor;
      Parent:=ColHeaderBand;
      Font.Assign(ListView.Font);
      caption:=Trim(DataSet.DataSetField.Fields[j].FieldName);
      height:=FDefaultHeight;
      width:=FDisplayWidth;
      HAlign:=haCenter;
      VAlign:=vaCenter;
      Frame.Bottom :=0;
      left:=FCurLeft;
      Top:=(j+1)* FDefaultHeight;
      //wsn 增加－－为header增加band
      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := 0;
         Right := 0;
       end;
      {$ENDIF}
    end;
    end;
//－－－－－－－－－－－－打印第一列标题栏 －－－－－－－－－－－－
   Fcurleft:=FcurLeft+FDisplayWidth+Delta;

//－－－－－－－－－－－－打印第二列标题栏－－－－－－－－－－－－－
    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
    Parent:=ColHeaderBand;
    caption:=Trim(ListView.Items.Item[i].Caption);
    height:=FDefaultHeight;
    width:=FDisplayWidth;
    HAlign:=haCenter;
    VAlign:=vaCenter;
    Frame.Bottom :=0;
    left:=FCurLeft;
    Top:=j* FDefaultHeight;
    //wsn 增加－－为header增加band
    {$IFDEF SHENZHENHUASI}
     with Frame do
     begin
       Left := 0;
       Top := 0;
       Bottom := 0;
       Right := 0;
     end;
    {$ENDIF}
    end;
//－－－－－－－－－－－－打印第二列标题栏 －－－－－－－－－－－－

    for j:=0 to FRowCount-1 do
    begin
    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
      //if j=0 then  Color:=StringGrid.FixedColor;
      Parent:=ColHeaderBand;
      Font.Assign(ListView.Font);
      caption:=Trim(ListView.Items.Item[i].SubItems[j]);
      height:=FDefaultHeight;
      width:=FDisplayWidth;
      HAlign:=haCenter;
      VAlign:=vaCenter;
      Frame.Bottom :=0;
      left:=FCurLeft;
      Top:=(j+1)* FDefaultHeight;
      //wsn 增加－－为header增加band
      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := 0;
         Right := 0;
       end;
      {$ENDIF}
    end;
    end;

    Fcurleft:=FcurLeft+FDisplayWidth+Delta;
end;

procedure CreateData(ColHeaderBand,DataBand:TRDSimpleBand;DbGrid:TDbGrid);
var
  i,FCurLeft,Fcount,FDisplayWidth:integer;
  FRDLabel:TRDLabel;
begin
  FcurLeft:=0;
  Fcount:=dbGrid.Columns.Count;

  for i:=0 to Fcount-1 do
  begin
    if dbGrid.Columns[I].Color<>dbGrid.Color then
      Continue;

    if dbGrid.Columns[I].Visible=False then
      Continue;

    if dbGrid.Columns[I].Width<0 then
      Continue;

    //生成报表的列标题
    FDisplayWidth:=ColHeaderBand.Width -FcurLeft;
    //如果显示不下就不打印该列
    if (FDisplayWidth < dbGrid.Columns[i].Width) then FDisplayWidth:=-1
    else FDisplayWidth :=dbGrid.Columns[i].Width;
    if FDisplayWidth<0 then exit;

    FRDLabel:=TRDlabel.create(ColHeaderBand);
    with FRDLabel do
    begin
      Color:=dbGrid.FixedColor;
      Parent:=ColHeaderBand;
      Font.Assign(dbGrid.Columns[i].Title.Font);
      caption:=dbGrid.Columns[i].Title.Caption ;
      height:=ColHeaderBand.Height;
      width:=FDisplayWidth;
      HAlign:=haCenter;
      VAlign:=vaCenter;
      Frame.Bottom :=0;
      left:=FCurLeft;
      //wsn 增加－－为header增加band
      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := -1;
         Right := 0;
       end;
      {$ENDIF}
    end;


    // 生成报表的具体数据
    FDisplayWidth:=ColHeaderBand.Width -FcurLeft;
    //如果显示不下就不打印该列
    if (FDisplayWidth < dbGrid.Columns[i].Width) then FDisplayWidth:=-1
    else FDisplayWidth :=dbGrid.Columns[i].Width;
    if FDisplayWidth<0 then exit;

    FRDlabel:=TRDlabel.create(DataBand);
    with FRDlabel do
    begin
      Parent:=DataBand;
      Font.Assign(dbGrid.Columns[i].Font);
      fieldName:=dbGrid.Columns[i].FieldName;
      height:=DataBand.Height ;
      width:=FDisplayWidth;
      case dbGrid.Columns[i].Alignment of
        Classes.taLeftJustify:  begin
                                  HAlign:=haLeft;
                                  Margin.Left := DefaultTextMargin;
                                end;

        Classes.taRightJustify: begin
                                  HAlign:=haRight;
                                  Margin.Right := DefaultTextMargin;
                                end;
        Classes.taCenter:
           HAlign:=haCenter;
      end;
      VAlign:=vaCenter;
      left:=FCurLeft;
      Fcurleft:=FcurLeft+width+Delta-1;

      {$IFDEF SHENZHENHUASI}
       with Frame do
       begin
         Left := 0;
         Top := 0;
         Bottom := -1;
         Right := 0;
       end;
      {$ENDIF}  
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    alignCenter设置表格居中对齐
  作者:      hanjiwei
  日期:      2008.10.07
  参数:      ColHeaderBand,DataBand:TRDSimpleBand
  返回值:    无
-------------------------------------------------------------------------------}
procedure alignCenter(ColHeaderBand,DataBand,FootBand:TRDSimpleBand);
var
  i,movePos:Integer;
  lblWidth,bandWidth,ss:Integer;
begin
  for i := 0 to ColHeaderBand.ComponentCount-1 do
  begin
    if ColHeaderBand.Components[i] is TRDLabel then
      lblWidth := lblWidth + TRDLabel(ColHeaderBand.Components[i]).Width;
  end;
  ss := lblWidth;
  bandWidth := ColHeaderBand.Width;
  movePos := Round((bandWidth-lblwidth)/2);
  for i := 0 to ColHeaderBand.ComponentCount-1 do
  begin
    if ColHeaderBand.Components[i] is TRDLabel then
      TRDLabel(ColHeaderBand.Components[i]).Left := TRDLabel(ColHeaderBand.Components[i]).Left+movepos;
  end;
  for i := 0 to DataBand.ComponentCount-1 do
  begin
    if DataBand.Components[i] is TRDLabel then
      TRDLabel(DataBand.Components[i]).Left := TRDLabel(DataBand.Components[i]).Left+movepos;
  end;
  for i := 0 to FootBand.ComponentCount-1 do
  begin
    if FootBand.Components[i] is TRDShape then
    begin
      TRDShape(FootBand.Components[i]).Left := movePos;
      TRDShape(FootBand.Components[i]).Width := ss-8;

    end;
  end;

end;

procedure CreateFoot(FFootBand:TRDSimpleBand);
var
  Fshap:TRDShape;
begin
  Fshap := TRDShape.Create(FFootBand);
  with Fshap do
  begin
    Parent:=FFootBand;
    Shape := rdstHLine;
    //Valign:=VaCenter;
    //HAlign:=HaCenter;
    //Caption:='';
    //parentFont:=true;
    Top := 0;
    height:=1;
  end;
end;


procedure PrintDBGrid(dbGrid:TDBGrid;const Title:String;const LTitle:String;
    const RTitle:String;const SpotTitle:string;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      RPDBDataset1.DataSource :=DbGrid.DataSource ;
      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      with FootBand do
        lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
   {   with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'  '
                      +Context.ParamData(svOperatorNameName).AsString;   }
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateData(colHeaderBand,DataBand,DbGrid);
      CreateFoot(FootBand);

      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1  ;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Print ;
    end
  finally
    dialog.Free;
  end;
end;


//wsn 20041121 添加打印stringgrid中数据
procedure PrintStringGrid(StringGrid:TStringGrid;const Title:String;const LTitle:String;
   const RTitle:String;const SpotTitle:String;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      //RPDBDataset1.DataSource :=DbGrid.DataSource ;
      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      with FootBand do
        lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
      {with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'  '
                      +Context.ParamData(svOperatorNameName).AsString;  }
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateStringGridData(colHeaderBand,DataBand,StringGrid);
      CreateFoot(FootBand);
      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Preview(StartPage,EndPage);
    end
  finally
    dialog.Free;
  end;
end;




//wsn 20041113 添加预览stringgrid中数据
procedure PreviewStringGrid(StringGrid:TStringGrid;const Title:String;const LTitle:String;
   const RTitle:String;const SpotTitle:String;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      //RPDBDataset1.DataSource :=DbGrid.DataSource ;
      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      with FootBand do
        lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
      {with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'  '
                      +Context.ParamData(svOperatorNameName).AsString;  }
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateStringGridData(colHeaderBand,DataBand,StringGrid);
      CreateFoot(FootBand);
      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Preview(StartPage,EndPage);
    end
  finally
    dialog.Free;
  end;
end;

procedure PreviewDBGrid(dbGrid:TDBGrid;const Title:String;const LTitle:String;
   const RTitle:String;const SpotTitle:String;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      RPDBDataset1.DataSource :=DbGrid.DataSource ;
      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      lbHeaderTitle.Left:=20;
      lbSysDate.Left:=HeaderBand.Width-lbSysDate.Width-20;

      //with FootBand do
        //lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
      with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'-'
                      +Context.ParamData(svOperatorNameName).AsString;
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateData(colHeaderBand,DataBand,DbGrid);
      CreateFoot(FootBand);
      //各表格居中对齐，hanjiwei add it 20081007
      alignCenter(colHeaderBand,DataBand,FootBand);
      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Preview(StartPage,EndPage);
    end
  finally
    dialog.Free;
  end;
end;


procedure PreviewListView(ListView:TListView;DataSet:TDataSet;const Title:String;
   const LTitle:String;const RTitle:String;const SpotTitle:String;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      RPDBDataset1.DataSource:=DataSet.DataSource ;
      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      with FootBand do
        lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
      {with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'  '
                      +Context.ParamData(svOperatorNameName).AsString;  }
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateListViewData(colHeaderBand,DataBand,ListView,DataSet);
      CreateFoot(FootBand);

      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1  ;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Preview(StartPage,EndPage);
    end
  finally
    dialog.Free;
  end;
end;


//wsn 20041122 添加打印listview的方法
procedure PrintListView(ListView:TListView;DataSet:TDataSet;const Title:String;
   const LTitle:String;const RTitle:String;const SpotTitle:String;StartPage,EndPage:integer);
var
  dialog:TfmPrintTemplate;
  StdPrinter:TStandardPrinter;
begin
  dialog:=TfmPrintTemplate.create(application);
  try
    with dialog do
    begin
      StdPrinter:=TStandardPrinter.Create(Application);
      try
        RDReport1.PaperWidth := StdPrinter.PaperWidth ;
        RDReport1.PaperHeight := StdPrinter.PaperHeight ;
      finally
        StdPrinter.Free;
      end;

      RDReport1.ReportName :=Title;
      with HeaderBand do
      begin
        lbHeaderTitle.caption:=CompanyName+CurrentDepartment.Name;
        lbSysDate.caption:='制表时间：'+GetSystemDateStr;
      end;
      with FootBand do
        lbEmp.Caption:=Context.ParamData(svOperatorNameName).AsString;
   {   with FootBand do
        lbEmp.caption:=Context.ParamData(svOperatorNoName).AsString+'  '
                      +Context.ParamData(svOperatorNameName).AsString;   }
      CreateTitle(TitleBand,Title,LTitle,RTitle,SpotTitle);
      CreateListViewData(colHeaderBand,DataBand,ListView,DataSet);
      CreateFoot(FootBand);

      RefreshHeadingTitlePositionInfo(dialog);
      RPEasyReport1.Processor := nil;
      RPEasyReport1.Processor := ReportProcessor1  ;
      RPEasyReport1.Processor.CreateReportFromDesign;
      RPEasyReport1.Print ;
    end
  finally
    dialog.Free;
  end;
end;

//*****   Part  PrintToText       *****

//重复字母n次
function RepeatChar(ABC:char;Count:integer):string;
var i:integer;
begin
  result:='';
  if count<0 then
    begin
      result:='';
      exit
    end;
  for i:=1 to Count do
    result:=result+ABC;
end;



// Ranamed from "TextTag" to "GetTagForTextFormat"
// 生成用文本标记语言编写的报表源代码
// 入口参数
//   DbGrid--     报表数据的来源DbGrid
//   RptTitle--   报表的标题
// 出口参数
//    Result--    源代码
// 编写 曾创能
function GetTagForTextFormat(DbGrid:TDbGrid;const RptTitle:string):string;
var
  TitleHeader,DataString,context:String;
  i:integer;
  TotalWidth:integer;
  AlignStr:string;
begin
  TotalWidth:=0;
  context:=RptTitle;
  context:=context+'<%'+#13#10;
  context:=context+'DataEntry("'+'DatasetName'+'","'+'DataSetName'+'");'+#13#10+'%>'+#13#10;
  for i:=0 to dbGrid.Columns.Count -1 do
    begin
      if dbGrid.Columns[I].Field=nil then
        Continue;

      //hanjiwei add it 20061031
      //不导出不显示的表格
      if DbGrid.Columns[I].Visible=False then
        Continue;
      if DbGrid.Columns[I].Width<0 then
        Continue;

      case ord(dbGrid.Columns[i].Alignment) of
        0:AlignStr:='Left';
        1:AlignStr:='Right';
        2:AlignStr:='Center';
      end;
      TitleHeader:=TitleHeader+dbGrid.Columns[i].Title.Caption+
                   RepeatChar(' ',(dbGrid.Columns[i].Width div 6)-length(DbGrid.columns[i].Title.caption)+1) ;
      DataString:=DataString+'<%FieldValue("'+dbGrid.Columns[i].FieldName+'","'+inttostr(dbGrid.Columns[i].width div 6)
                  +'","'+AlignStr+'")%> ';
      TotalWidth:=TotalWidth+dbGrid.Columns[i].Width;
    end;
    //TitleHeader := 'hjw';
  context:=context+TitleHeader+#13#10
           +RepeatChar('-',TotalWidth div 6)
          //+'--------------------------------'
          +#13#10;
  context:=context+'<%ForLoop("'+'DataSetName'+'")%>'+DataString+#13#10
          +'<%EndLoop()%>'+#13#10
          //+'--------------------------------';
          +RepeatChar('-',TotalWidth div 6);
  Result:=Context;
end;

function  EncodeHTMLText(const S : string) : string;
var
  I : Integer;
begin
  Result := '';
  for I:=1 to Length(S) do
  begin
    case S[I] of
      '<' : Result := Result + '&gt;';
      '>' : Result := Result + '&lt;';
      '&' : Result := Result + '&amp;';
    else
      Result := Result + S[I];
    end;
  end;
end;

{
  <Function>GetTagForHTMLFormat
  <What>生成用文本标记语言编写的报表源代码，用于产生HTML格式的输出
  <Params>
    -
  <Return>
  <Exception>
}
function GetTagForHTMLFormat(DbGrid:TDbGrid;const RptTitle:string):string;
var
  TitleHeader,DataString:String;
  i:integer;
  Title : string;
  CellWidth, TableWidth : Integer;
  FontHeight : Integer;
  TdClass : string;
  TdAlign : string;
begin
  Assert((DbGrid.DataSource<>nil) and (DbGrid.DataSource.Dataset<>nil));
  FontHeight := Abs(DbGrid.Font.Height);
  Title := EncodeHTMLText(RptTitle);
  Result := Format(
    '<html>'#13#10
    +'<head>'#13#10
    +'<title>%s</title>'#13#10
    +'<meta http-equiv="Content-Type" content="text/html; charset=gb2312">'#13#10
    +'<style>'#13#10
    +'.str {'#13#10
	  +'mso-number-format:"\@"'#13#10
    +'}'#13#10
    +'td {'#13#10
  	+'font-family: "宋体";'#13#10
	  +'font-size: %dpx;'#13#10
    +'}'#13#10
    +'</style>'#13#10
    +'</head>'#13#10
    +'<body>'#13#10
    +'<h1>%s</h1>'#13#10
    +'<%%DataEntry("DatasetName","DataSetName");%%>'#13#10,
    [Title, FontHeight, Title]
    );
  TitleHeader:='';
  DataString:='';
  TableWidth := 4;
  for i:=0 to dbGrid.Columns.Count -1 do
  begin
    if dbGrid.Columns[I].Field=nil then
      Continue;

    //hanjiwei add it 20061031
    //不导出不显示的表格内容
    if DbGrid.Columns[I].Visible=False then
      Continue;
    if DbGrid.Columns[I].Width<0 then
      Continue;

    if dbGrid.Columns[I].Field.DataType in
      [ftSmallint, ftInteger, ftWord, ftFloat, ftCurrency, ftBCD, ftAutoInc, ftLargeint] then
    begin
      // field as number
      TdClass := '';
      TdAlign := 'align="right"';
    end
    else
    begin
      // field as string
      TdClass := 'class="str"';
      TdAlign := '';
    end;
    CellWidth := dbGrid.Columns[i].Width+4;
    TitleHeader:=Format(
      '%s  <td width=%d><strong>%s</strong></td>'#13#10,
      [TitleHeader, CellWidth, EncodeHTMLText(dbGrid.Columns[i].Title.Caption)]
    );
    DataString:= Format(
      '%s  <td %s %s><%%FieldValue("%s")%%></td>'#13#10,
      [DataString, TdClass, TdAlign, dbGrid.Columns[i].FieldName]
    );
    Inc(TableWidth,CellWidth);
  end;
  Result := Format(
    '%s<table width=%d border="1" cellspacing="0">'
    +'  <tr>'#13#10'%s</tr>'#13#10
    +'  <%%ForLoop("DataSetName")%%>'#13#10
    +'  <tr>'#13#10'%s</tr>'#13#10
    +'<%%EndLoop()%%>'#13#10
    +'</table>'#13#10
    +'</body>'#13#10
    +'</html>'#13#10,
    [Result, TableWidth, TitleHeader, DataString]
  );
  WriteLog(Result,lcKSClient);
end;

type
  TTextFormat = (tfPlain, tfHTML);

//将DbGrid中的内容输出到文本文件中
// 增加了TextFormat参数
procedure PrintToText(DbGrid:TDbGrid;const RptTitle,FileName:String;
  TextFormat : TTextFormat=tfPlain); //OutPut PROC
var
  FTextTag:string;
  FContext : TScriptContext;
  Environment:TRPDataEnvironment;
  FStream:TMemorystream;
  FStrs:Tstrings;
begin
  if not DirectoryExists(ExTractFileDir(FileName)) then
    begin
      Application.MessageBox(pchar('文件路径不存在，请检查！'),pchar('提示'),MB_OK);
      exit;
    end;
  Fstrs:=Tstringlist.Create;
  FStream:=TMemorystream.Create;
  Environment:=TRPDataEnvironment.Create(application);
  FContext := TScriptContext.Create(application);
  FContext.Environment := Environment;
  //ShowMessage('ddd');
  case TextFormat of
    tfPlain : FTextTag:=GetTagForTextFormat(DbGrid,RptTitle);
    tfHTML : FTextTag:=GetTagForHTMLFormat(DbGrid,RptTitle);
  else
    FTextTag:='';
  end;
  //ShowMessage(FtextTag);
  Fstrs.Add(FtextTag);
  Fstrs.SaveToStream(FStream);
  Fstream.Position:=0;
  FContext.LoadScripts(FStream); //载入报表源代码

  if FContext.DataEntries.IndexOfDataset('DataSetName')>=0 then
    FContext.DataEntries.AddDatasource('DataSetName',DbGrid.datasource);
  try
    FContext.Output(FileName); //输出
    Context.GetDialogSystem.ShowMessage('操作成功！');
  except
    Context.GetDialogSystem.ShowError('输出到文本错误！');
  end;
  FStream.Free ;
  Fstrs.Free;
  Environment.free;
end;

procedure TfmPrintMode.btnPrintClick(Sender: TObject);
var
  StartPage, EndPage : Integer;
begin
  if rbToPrinter.Checked then
  begin
    if ckPageRange.Checked then
    begin
      StartPage := edStart.Value;
      EndPage := edEnd.Value;
    end else
    begin
      StartPage := 0;
      EndPage := 0;
    end;

    if (edEnd.Value<>0) and (edEnd.Value<edStart.Value) then
    begin
      Context.GetDialogSystem.ShowWarning(SEndPageTooSmall);
      Exit;
    end;
    if FPrintStringGrid then
      PrintStringGrid(FStringGrid,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage)
    else if FPrintListView then
      PrintListView(FListView,FDataSet,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage)
    else
      PrintDBGrid(dbGridEx,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage);
  end
  else if rbToFile.Checked then
    PrintToText(DbGridEx,RptTitleEx,edFileName.text, tfPlain)
  else if rbToExcelFile.Checked then
    PrintToText(DbGridEx,RptTitleEx,edFileName.text, tfHTML)
  else if rbToHTMLFile.Checked then
    PrintToText(DbGridEx,RptTitleEx,edFileName.text, tfHTML);
  close;
end;

procedure TfmPrintMode.btnPreviewClick(Sender: TObject);
var
  StartPage, EndPage : Integer;
begin
  if ckPageRange.Checked then
  begin
    StartPage := edStart.Value;
    EndPage := edEnd.Value;
  end else
  begin
    StartPage := 0;
    EndPage := 0;
  end;
  if (EndPage=0) or (EndPage-StartPage>MaxPreviewPageCount) then
          EndPage := StartPage+MaxPreviewPageCount;

  if (edEnd.Value<>0) and (edEnd.Value<edStart.Value) then
  begin
    Context.GetDialogSystem.ShowWarning(SEndPageTooSmall);
    Exit;
  end;

  if FPrintListView then
  begin
    PreviewListView(FListView,FDataSet,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage);
  end
  else if FPrintStringGrid then
  begin
    PreviewStringGrid(FStringGrid,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage);
  end
  else
    PreviewDBGrid(dbGridEx,RptTitleEx,LRptTitleEx,RRptTitleEx,RptDateSpotTitleEx,StartPage,EndPage);
    //previewDBGrid_new(dbGridEx,'hjw测试题头', 'ykt部门','desc咳咳咳','20080906-52215412','报表日期:20080980','操作员:韩纪伟');
  close;
end;

procedure TfmPrintMode.PrintModeChanged(Sender: TObject);
var
  ToPrinter, ToFile : Boolean;
begin
  ToPrinter := rbToPrinter.Checked;
  ToFile := rbToFile.Checked or rbToHTMLFile.Checked or rbToExcelFile.Checked;
  //hanjiwei add it
  if ToFile then
  begin
    btnPrint.Caption := '&E 导出';
    btnPrint.Hint:='导出';
  end
  else
  begin
    btnPrint.Caption := '&P 打印';
    btnPrint.Hint:='打印';
  end;
  if not ToPrinter and not ToFile then
  begin
    rbToPrinter.Checked := True;
    ToFile := True;
  end;
  btnPreview.Enabled := ToPrinter;
  ckPageRange.Enabled := ToPrinter;
  edFileName.Enabled:= ToFile;
  btnSave.Enabled := ToFile;
  btnPrint.Enabled := True;
  if ToFile then
  begin
    if rbToFile.Checked then
      edFileName.text := GetDefaultOutputFileName('.txt')
    else if rbToExcelFile.Checked then
      edFileName.text := GetDefaultOutputFileName('.xls')
    else
      edFileName.text := GetDefaultOutputFileName('.html')
  end;
  ckPageRangeClick(Self);
end;

procedure TfmPrintMode.FormShow(Sender: TObject);
begin
  edFileName.Enabled :=False;
  btnSave.Enabled :=False;
  edStart.Enabled := False;
  edEnd.Enabled := False;
end;

procedure TfmPrintMode.btnSetPrinter1Click(Sender: TObject);
begin
  PrinterSetupDialog.Execute ;
end;


procedure TfmPrintMode.btnSaveClick(Sender: TObject);
var
  Dialog : TSaveDialog;
begin
  if rbToFile.Checked then
    Dialog := SaveDialog
  else if rbToExcelFile.Checked then
    Dialog := SaveDialog1
  else
    Dialog := SaveDialog2;
  Dialog.FileName := edFileName.Text;
  if Dialog.Execute then
    edFileName.Text := Dialog.FileName;
end;

procedure TfmPrintMode.btnSetPrinterClick(Sender: TObject);
begin
  PrinterSetupDialog.Execute ;
  UpdatePrinterInfo;
end;


procedure TfmPrintMode.Execute(StringGrid:TStringGrid;const RptTitle:String;
   const LRptTitle:String;const RRptTitle:String;
   const RptDateSpotTitle:String);
begin
  FPrintListView:=False;
  FPrintStringGrid:=True;

  FStringGrid:=StringGrid;
  RptTitleEx:=RptTitle;
  LRptTitleEx:= LRptTitle;
  RRptTitleEx:= RRptTitle;
  RptDateSpotTitleEx:= RptDateSpotTitle;
  UpdatePrinterInfo;
  ShowModal;
end;



procedure  TfmPrintMode.Execute(dbGrid:TdbGrid;const RptTitle:string;
  const LRptTitle:string;const RRptTitle:string;const RptDateSpotTitle:String);
begin
  if dbGrid.DataSource=nil then
  begin
    showmessage('该功能不支持此操作！');
    exit;
  end;
  FPrintListView:=False;
  FPrintStringGrid:=False;

  dbGridEx:=dbGrid;
  RptTitleEx:=RptTitle;
  LRptTitleEx:=LRptTitle;
  RRptTitleEx:=RRptTitle;
  RptDateSpotTitleEx:=RptDateSpotTitle;
  UpdatePrinterInfo;
  ShowModal;
end;
       

procedure TfmPrintMode.Execute(ListView:TListView;DataSet:TDataSet;
  const RptTitle: string;const LRptTitle:string;const RRptTitle:string;
  const RptDateSpotTitle:String);
begin
  FPrintListView:=True;
  FPrintStringGrid:=False;
  
  FListView:=ListView;
  FDataSet:=DataSet;
  RptTitleEx:=RptTitle;
  LRptTitleEx:=LRptTitle;
  RRptTitleEx:=RRptTitle;
  RptDateSpotTitleEx:= RptDateSpotTitle;
  UpdatePrinterInfo;
  ShowModal;
end;



procedure TfmPrintMode.edFileNameExit(Sender: TObject);
begin
  if (trim(edFileName.text)='') and rbToFile.Checked  then
    btnPrint.Enabled :=false;
end;

procedure TfmPrintMode.UpdatePrinterInfo;
begin
  FPrinterInstalled := GetPrinterInfoToLabel(lbPrinterInfo);
  btnPrint.Enabled := FPrinterInstalled;
  btnPreview.Enabled := FPrinterInstalled;
end;

procedure TfmPrintMode.ckPageRangeClick(Sender: TObject);
begin
  edStart.Enabled := ckPageRange.Enabled and ckPageRange.Checked;
  edEnd.Enabled := ckPageRange.Enabled and ckPageRange.Checked;
end;

function  TfmPrintMode.GetDefaultOutputFileName(const FileExt : string) : string;
var
  DateStr:String;
begin
  DateStr:=FormatDateTime('yymmdd',now);
  Result := Context.GetDir(dkOutput)+RptTitleEx+DateStr+FileExt;
end;
{
procedure TfmPrintMode.previewDBGrid_new(dbGrid: TDBGrid; Title,
  Dept, Desc, TitDate, Date, oper: string);
var
  pntPreview:TfrmPreview;
  Report: TfrReport;
  Page: TfrPage;
begin
  RTitle_N := Title;
  RDept_N:=Dept;
  RDesc_N := Desc;
  RTitDate_N := TitDate;
  RDate_N := Date;
  ROper_N := oper;
  Report := frCustReport;
  Report.LoadFromFile(ExtractFilePath(Application.ExeName)+'..\Report\reportTemp.frf');
  frdb.DataSource := dbGrid.DataSource;
  //Report.ShowReport;
  try
    pntPreview := TfrmPreview.Create(Application);
    //加入数据项
    //createData_new(dbGrid);
    Report.Preview := pntPreview.frPreview;
    if Report.PrepareReport then
    begin
      Report.ShowPreparedReport;
      pntPreview.ShowModal;
    end;

  finally
    pntPreview.Free;
  end;
end;
}
procedure TfmPrintMode.frCustReportGetValue(const ParName: String;
  var ParValue: Variant);
begin
  if ParName='RDept' then
    ParValue := RDept_N;
  if ParName='RTitle' then
    ParValue := RTitle_N;
  if ParName='RDesc' then
    ParValue := RDesc_N;
  if ParName='RTitleDate' then
    ParValue := RTitDate_N;
  if ParName='RDate' then
    ParValue := RDate_N;
  if ParName='ROper' then
    ParValue := ROper_N;
end;

end.
