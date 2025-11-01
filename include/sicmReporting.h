#ifndef __SICMREPORTING_H__
#define __SICMREPORTING_H__

class CsicmProcesses;

void InitColorDebugFile();
void InitInterpolatorFile();
void CloseColorDebugFiles();
void SaveMeasurementData (CsicmProcesses *Process, bool append);
void SavePerformanceData(CsicmProcesses *Process);
void GenerateCalibrationReportPrologue(CsicmProcesses *Process);
void GenerateCalibrationReport(CsicmProcesses *Process);

#endif