unit UPrintTemplate;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UPrintMode
   <What>通用的查询结果打印的报表模版
   <Written By> 曾创能
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  RPCtrls, RPDB, RPDBVCL, RPEasyReports, RPProcessors;

type
  TfmPrintTemplate = class(TForm)
    RDReport1: TRDReport;
    HeaderBand: TRDSimpleBand;
    TitleBand: TRDSimpleBand;
    RDGroupBand1: TRDGroupBand;
    colHeaderBand: TRDSimpleBand;
    RDRepeatBand1: TRDRepeatBand;
    DataBand: TRDSimpleBand;
    FootBand: TRDSimpleBand;
    ReportProcessor1: TReportProcessor;
    RPDBDataset1: TRPDBDataset;
    RPDatasetController1: TRPDatasetController;
    RPDataEnvironment1: TRPDataEnvironment;
    RPEasyReport1: TRPEasyReport;
    L_0152C910: TRDLabel;
    L_00DE3BB8: TRDLabel;
    lbSysDate: TRDLabel;
    RDLabel1: TRDLabel;
    lbEmp: TRDLabel;
    lbHeaderTitle: TRDLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmPrintTemplate: TfmPrintTemplate;

implementation

{$R *.DFM}

end.
