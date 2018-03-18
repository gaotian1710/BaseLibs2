/*!
\description Provisioning unit tests
    [1] BLSfo : unit test for BLSfo_xxx() methods.
\param Arguments(0) [in] test project const data folder
\param Arguments(1) [in] test project working folder
*/

var fso = WScript.CreateObject("Scripting.FileSystemObject");
var projectConstData = WScript.Arguments(0);
var projectWorkData = WScript.Arguments(1);
var wsh = WScript.CreateObject("WScript.Shell");
var wnw = WScript.CreateObject("WScript.Network");
ProvisionAll();

/*!
\brief provisioning test data for BLSfo
\param constData [in] folder path of test class constant data 
\param workFolder [in] folder path of working data folder of the test class
*/
function BLSfo(constData, workFolder)
{
    var BLSfoWorkData = workFolder + "\\BLSfo";
    var BLSfoConstData = constData + "\\BLSfo";
    fso.CreateFolder(BLSfoWorkData);
    fso.CopyFile(BLSfoConstData + "\\CopySrc0.dat", BLSfoWorkData + "\\CopySrc0.dat");
    fso.CopyFile(BLSfoConstData + "\\CopySrc0.dat", BLSfoWorkData + "\\DeleteTarget0.dat");
    var DeleteTarget1 = BLSfoWorkData + "\\DeleteTarget1.dat";
    fso.CopyFile(BLSfoConstData + "\\CopySrc0.dat", DeleteTarget1);
    var strCommand = "icacls " + DeleteTarget1 + " /deny \"" + wnw.UserName + "\":W";
    wsh.Run(strCommand, 0, true);
}

function ProvisionAll()
{
    var deleteTarget1 = projectWorkData + "\\BLSfo\\DeleteTarget1.dat";
    if (fso.FileExists(deleteTarget1))
    {
        var strCommand = "icacls " + deleteTarget1 + " /grant \"" + wnw.UserName + "\":W";
        var oExec = wsh.Exec(strCommand);
        while (oExec.Status == 0)
        {
            WScript.Sleep(100);
        }
    }
    if (fso.FolderExists(projectWorkData))
    {
        var strCommand = "cmd /C rd /S/Q " + projectWorkData;
        WScript.Echo(strCommand);
        var oExec = wsh.Exec(strCommand);
        while (oExec.Status == 0)
        {
            WScript.Sleep(100);
        }
        WScript.Echo("rd command done. " + projectWorkData);
        while (fso.FolderExists(projectWorkData))
        {
            WScript.Sleep(100);
        }
        WScript.Echo("folder deleted: " + projectWorkData);
    }
    fso.CreateFolder(projectWorkData);
    BLSfo(projectConstData, projectWorkData);
}