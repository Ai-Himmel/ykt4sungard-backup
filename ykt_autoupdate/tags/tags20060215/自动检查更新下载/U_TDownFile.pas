///////////////////////////////////////////////////////////////////////////////
// �� �� �ƣ� �ļ�������
// ��    ���� TDownFile V0.1.2003.1006
// ��    �ߣ� gonghh
// ����ƽ̨�� win2000 ����ͨ��
// ����˵���� ���߳��ļ����� 
//
///////////////////////////////////////////////////////////////////////////////
unit U_TDownFile;

interface
  uses SysUtils, Windows, UrlMon, ActiveX,Classes,shellapi;

  type  //��������״̬�ص��ӿ���
    TOnProgressEvent = procedure(ulProgress, ulProgressMax, ulStatusCode: integer;szStatusText:String) of object;
    TOnCompleteEvent = procedure(Source_file,Dest_file:String;blStatus:boolean;ErrMessage:String) of object;

    TBindStatusCallback = class(TObject, IBindStatusCallback)
      protected // IUnknown
        FRefCount: Integer;
        function QueryInterface(const IID: TGUID; out Obj): Integer; stdcall;
        function _AddRef: Integer; stdcall;
        function _Release: Integer; stdcall;
      public  // IBindStatusCallback
        FProgress : TOnProgressEvent;
        FComplete : TOnCompleteEvent;
        function OnStartBinding(dwReserved: DWORD; pib: IBinding): HResult; stdcall;
        function GetPriority(out nPriority): HResult; stdcall;
        function OnLowResource(reserved: DWORD): HResult; stdcall;
        function OnProgress(ulProgress, ulProgressMax, ulStatusCode: ULONG;szStatusText: LPCWSTR): HResult; stdcall;
        function OnStopBinding(hresult: HResult; szError: LPCWSTR): HResult; stdcall;
        function GetBindInfo(out grfBINDF: DWORD; var bindinfo: TBindInfo): HResult; stdcall;
        function OnDataAvailable(grfBSCF: DWORD; dwSize: DWORD; formatetc: PFormatEtc;stgmed: PStgMedium): HResult; stdcall;
        function OnObjectAvailable(const iid: TGUID; punk: IUnknown): HResult; stdcall;
    end;


    TThreadDown =class(TThread) //�����߳��ࡣ
      private
        Source_file : string;
        Dest_file   : string;
        StatusCallback : TBindStatusCallback;
      protected
        procedure Execute; override;
      public
        constructor Create(URL,FileName: String ; StatusCB: TBindStatusCallback);overload;
    end;


    TDownFile=class(TComponent) //�ļ����ؿؼ�
      private
        FOnProgress: TOnProgressEvent;
        RevedByte  : TBindStatusCallback;
        FOnComplete: TOnCompleteEvent;
        procedure SetOnProgress(const Value: TOnProgressEvent);  //���ؽ���
        procedure SetOnComplete(const Value: TOnCompleteEvent);  //�������
      public
        constructor Create(AOwner: TComponent);reintroduce;
        destructor Destroy; reintroduce;
        procedure  ThreadDownFile(Source,Dest:string);
        procedure DownFile(Source,Dest:string);
      published
        property  OnComplete:TOnCompleteEvent read FOnComplete write SetOnComplete;
        property  OnProgress:TOnProgressEvent read FOnProgress write SetOnProgress;
    end;
implementation

{ TBindStatusCallback }
function TBindStatusCallback._AddRef: Integer;
begin
  Inc(FRefCount);
  Result := FRefCount;
end;

function TBindStatusCallback._Release: Integer;
begin
  Dec(FRefCount);
  Result := FRefCount;
end;

function TBindStatusCallback.GetBindInfo(out grfBINDF: DWORD;
  var bindinfo: TBindInfo): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.GetPriority(out nPriority): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.OnDataAvailable(grfBSCF, dwSize: DWORD;
  formatetc: PFormatEtc; stgmed: PStgMedium): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.OnLowResource(reserved: DWORD): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.OnObjectAvailable(const iid: TGUID;
  punk: IInterface): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.OnStartBinding(dwReserved: DWORD;
  pib: IBinding): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.OnStopBinding(hresult: HResult;
  szError: LPCWSTR): HResult;
begin
  Result := E_NOTIMPL;
end;

function TBindStatusCallback.QueryInterface(const IID: TGUID;
  out Obj): Integer;
begin
 if GetInterface(IID, Obj) then Result := S_OK
                           else Result := E_NOINTERFACE;
end;

function TBindStatusCallback.OnProgress(ulProgress, ulProgressMax,
  ulStatusCode: ULONG; szStatusText: LPCWSTR): HResult;
begin
  if Assigned(FProgress) then
    FProgress(ulProgress,ulProgressMax,ulStatusCode,szStatusText);
  Result := S_OK;
end;



//=============================================================================

{ TDownFile }

constructor TDownFile.Create(AOwner: TComponent);
begin
  RevedByte:=TBindStatusCallback.Create;
  inherited;
end;

destructor TDownFile.Destroy;
begin
  RevedByte.Free; 
end;

procedure TDownFile.SetOnComplete(const Value: TOnCompleteEvent);
begin
  FOnComplete := Value;
  if Assigned(FOnComplete) then ;
    RevedByte.FComplete := FOnComplete;
end;

procedure TDownFile.SetOnProgress(const Value: TOnProgressEvent);
begin
  FOnProgress := Value;
  if Assigned(FOnProgress) then  ;
    RevedByte.FProgress := FOnProgress;
end;

procedure TDownFile.ThreadDownFile(Source, Dest: string);
var
  ThreadDown:TThreadDown;
begin
  ThreadDown:=TThreadDown.Create(Source, Dest,RevedByte);
  ThreadDown.Resume;
end;

procedure TDownFile.DownFile(Source, Dest: string);
var
  blDownOK:boolean;
  ErrMessage:String;
begin
  ErrMessage:='';
  blDownOK:=false;
  try
    if UrlDownloadToFile(nil,Pchar(Source),Pchar(Dest),0,RevedByte)=0 then
      blDownOK:=true;
  except on e:exception do
    ErrMessage:=e.Message; 
  end;
  if Assigned(RevedByte.FComplete) then
     RevedByte.FComplete(Source,Dest,blDownOK,ErrMessage);
end;


//==============================================================================
{ TThreadDown }

constructor TThreadDown.Create(URL, FileName: String;StatusCB: TBindStatusCallback);
begin
  Source_file := URL;
  Dest_file   := FileName;
  StatusCallback := StatusCB;
  FreeOnTerminate:=true;
  inherited Create(true);
end;

procedure TThreadDown.Execute;
var
  blDownOK:boolean;
  ErrMessage:String;
begin
  ErrMessage:='';
  blDownOK:=false;
  try
    if UrlDownloadToFile(nil,Pchar(Source_file),Pchar(Dest_file),0,StatusCallback)=0 then
      blDownOK:=true;
  except on e:exception do
    ErrMessage:=e.Message; 
  end;
  if Assigned(StatusCallback.FComplete) then
     StatusCallback.FComplete(Source_file,Dest_file,blDownOK,ErrMessage);
end;

end.

