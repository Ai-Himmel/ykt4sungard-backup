rem echo off

set dir=..\cardlib_%date%
md %dir%
md %dir%\logs

copy /y bccclt.dll						%dir%
copy /y boost_thread.dll				%dir%
copy /y dcrf32.dll                      %dir%
copy /y drtplib.dll                     %dir%
copy /y kk_crypt32.dll                  %dir%
copy /y kscard.dll                      %dir%
copy /y ks_amass_reader.dll             %dir%
copy /y ks_cardtype.dll                 %dir%
copy /y ks_cardtype_mobile.dll          %dir%
copy /y ks_cmccpsamcard.dll             %dir%
copy /y ks_cmcc_cardtype.dll            %dir%
copy /y ks_cpumf_cardtype.dll           %dir%
copy /y ks_cqzy_cardtype.dll            %dir%
copy /y ks_ctcardtype.dll               %dir%
copy /y ks_ct_liaoning.dll              %dir%
copy /y KS_DECARD.dll                   %dir%
copy /y ks_decardt10.dll                %dir%
copy /y ks_dongguan_cardtype.dll        %dir%
copy /y ks_dongguan_psam.dll            %dir%
copy /y ks_elitel_reader.dll            %dir%
copy /y ks_mfcard.dll                   %dir%
copy /y ks_mf_newcapec.dll              %dir%
copy /y ks_newcapec.dll                 %dir%
copy /y ks_ntcard.dll                   %dir%
copy /y ks_psamcard.dll                 %dir%
copy /y ks_yncs_cardtype.dll            %dir%
copy /y ks_ztc800.dll                   %dir%
copy /y libeay32.dll                    %dir%
copy /y NT_ReaderLib.dll                %dir%
copy /y sqlite3.dll                     %dir%
copy /y Trf32.dll                       %dir%
copy /y WltRS.dll                       %dir%

copy /y cpack.dat                       %dir%
copy /y pub.key                         %dir%

copy /y kscard_sample.ini               %dir%\kscard.ini

copy /y kscardinterface_online.dll      %dir%
copy /y kscardinterface_online.lib      %dir%
copy /y KsCardInterFace.ini             %dir%
copy /y KsCardInterfaceDemo.exe         %dir%
copy /y ..\KsCardInterFace\KsCardInterFace.h       %dir%


copy /y Mwrf32.dll                      %dir%
copy /y mwrf32_org.dll                  %dir%
copy /y ztc800.dll                      %dir%
copy /y cpucard.exe                     %dir%
copy /y cpucard_sample.ini              %dir%\cpucard.ini

xcopy  Microsoft.VC90.CRT              %dir%\Microsoft.VC90.CRT\
xcopy  Microsoft.VC90.MFC              %dir%\Microsoft.VC90.MFC\


copy /y ks_zjvcc_cardtype.dll           %dir%

copy /y libcurl.dll                     %dir%
copy /y ssleay32.dll                    %dir%
copy /y libeay32.dll                    %dir%
copy /y RF35OCX.ocx                     %dir%

copy /y wxmsw28d_core_vc.dll                    %dir%
copy /y wxmsw28_vc.dll                    %dir%
copy /y wxcode_msw28_wxsqlite3.dll                     %dir%





pause
